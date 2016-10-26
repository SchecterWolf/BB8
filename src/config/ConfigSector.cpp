/* Copyright (C) 
 * 2016 - John Torres <Schecterwolfe@gmail.com>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

#include "ConfigSector.h"

using namespace std;

/** 
 * ConfigSector constructor
 */
ConfigSector::ConfigSector()
{

}

/** 
 * ConfigSector named constructor
 * 
 * @param strSecName    Sector name
 */
ConfigSector::ConfigSector(const string &strSecName)
{
    this->strSecName = strSecName;
}

/** 
 * ConfigSector destructor
 */
ConfigSector::~ConfigSector()
{

}

/** 
 * Set this sector's name
 * 
 * @param strSecName    Sector name
 */
void ConfigSector::setSectorName(const string &strSecName)
{
    this->strSecName = strSecName;
}

/** 
 * Get this sector's name
 * 
 * @return Sector name
 */
const string &ConfigSector::getSectorName() const
{
    return strSecName;
}

/** 
 * Add an option value entry into this sector
 * 
 * @param strOption     Option name
 * @param strVal        Value
 */
void ConfigSector::addOption(const string &strOption, const string &strVal)
{
    if (!strOption.empty())
        mapOptionToValue[strOption] = strVal;
}

/** 
 * Remove and option from this sector
 * 
 * @param strOption     Option name to remove
 * 
 * @return true if removed, false otherwise
 */
bool ConfigSector::removeOption(const string &strOption)
{
    return mapOptionToValue.erase(strOption);
}

/** 
 * Get the value of an option
 * 
 * @param strOption     Option name
 * 
 * @return Option's value
 */
string &ConfigSector::getValue(const string &strOption)
{
    auto iter = mapOptionToValue.find(strOption);
    return (iter != mapOptionToValue.end()) ? iter->second : strStaticEmpty;
}

/** 
 * Get the indexed value for this sector. By default its the sector name, but it can be
 * a different value if we want this sector to be identified by something other than its name
 * 
 * @param iIndex    Indexed value
 * 
 * @return Value denoted but iIndex
 */
string &ConfigSector::getIndexValue(int iIndex)
{
    string &strRet = strStaticEmpty;

    // Sane index
    if (iIndex < 0 || iIndex >= IndexCount)
        return strRet;

    switch (iIndex)
    {
        case IndexSectorName:
            strRet = strSecName;
            break;
        default:
            break;
    }

    return strRet;
}

/** 
 * Get all of the option values for this sector
 * 
 * @return All option values
 */
const map<string, string> &ConfigSector::getOptionValues() const
{
    return mapOptionToValue;
}

/** 
 * Fill out this sector from a formatted string (usually read in from the config file)
 * 
 * @param strSector     Formatted string
 * @param puiOffset     The offset index into strSector that has been parsed
 * 
 * @return true on success, false if not
 */
bool ConfigSector::parseSector(const string &strSector, unsigned int *puiOffset)
{
    bool bRet = true;
    size_t uiIndex = (puiOffset) ? *puiOffset : 0;

    // Sane
    if (uiIndex >= strSector.size())
        return false;

    // Skip comments
    skipFileComment(strSector, &uiIndex);
    bRet = uiIndex < strSector.size();

    // Get sector name
    if (bRet)
    {
        size_t uiPos = 0;

        uiIndex = strSector.find_first_of('<', uiIndex);
        uiPos = strSector.find_first_of('>', uiIndex);
        if (uiPos != string::npos)
            strSecName = strSector.substr(uiIndex + 1, uiPos - uiIndex - 1);

        // Make sure we have a sector name
        bRet = !strSecName.empty();
        if (bRet)
            uiIndex = uiPos + 1;
    }

    // Exctract option: values
    if (bRet)
    {
        // Skip comments
        skipFileComment(strSecName, &uiIndex);

        while (uiIndex != string::npos)
        {
            size_t uiPos = strSector.find_first_of(":", uiIndex);

            if (uiPos == string::npos)
                uiIndex = uiPos;
            else
            {
                // Option
                string strOption = strSector.substr(uiIndex + 1, uiPos - uiIndex - 1);

                // Skip white spaces after ':'
                while (++uiPos < strSector.size() && strSector[uiPos] == ' ');

                // Value
                uiIndex = strSector.find_first_of('\n', uiPos);
                string strVal = strSector.substr(uiPos, uiIndex - uiPos);

                // Insert option value
                if (uiIndex != string::npos)
                    mapOptionToValue[strOption] = strVal;
            }

            // Skip comments
            skipFileComment(strSecName, &uiIndex);

            // Check if this is the start of a new section
            if (uiIndex < strSector.size() && strSector[uiIndex] == '<')
                break;
        }
    }

    // Reassign the current offset
    if (puiOffset)
        *puiOffset = (uiIndex == string::npos) ? strSector.size() : uiIndex;

    return bRet;
}

/** 
 * Skip the comment lines
 * 
 * @param strSector     Sector string input
 * @param puiOffset     input offset
 */
void ConfigSector::skipFileComment(const string &strSector, size_t *puiOffset) const
{
    size_t uiIndex = 0;

    // Sane
    if (!puiOffset || *puiOffset > strSector.size())
        return;

    uiIndex = *puiOffset;

    // Move index past all of the comment lines
    bool bContinue = true;
    uiIndex = strSector.find_first_of('\n', uiIndex);
    while (uiIndex != string::npos && bContinue)
    {
        bContinue = ++uiIndex < strSector.size() && strSector[uiIndex] == '#';
        if (bContinue)
            uiIndex = strSector.find_first_of('\n', uiIndex);
    }

    *puiOffset = uiIndex;
}

/** 
 * Serializes this sector into a string
 * 
 * @return serialized string
 */
string ConfigSector::serializeSector() const
{
    string strRet = "<" + getSectorName() + ">\n";

    for (auto optionVal : mapOptionToValue)
        strRet += optionVal.first + ":" + optionVal.second + "\n";

    return strRet;
}
