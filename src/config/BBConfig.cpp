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

#include "BBConfig.h"
#include "StdLibUtils.h"

using namespace std;

/** 
 * BBConfig constructor
 */
BBConfig::BBConfig()
{

}

/** 
 * BBConfig destuctor
 */
BBConfig::~BBConfig()
{
    StdLibUtils().freeObjects(vecSectors);
}

/** 
 * Adds a config sector to the config container
 * 
 * @param ptSector  Config sector to add
 */
void BBConfig::addSector(unique_ptr<ConfigSector> ptSector)
{
    if (ptSector)
        vecSectors.push_back(ptSector.release());
}

/** 
 * Remove all sectors with a specific index value (defaults to sector name)
 * 
 * @param strVal    Sector with this value to remove
 * @param iIndex    The index value to match
 * 
 * @return true on success, false otherwise
 */
bool BBConfig::removeSector(const string &strVal, int iIndex)
{
    bool bRemoved = false;

    // Delete all with value
    for (auto iter = vecSectors.begin(); !bRemoved && iter != vecSectors.end(); ++iter)
    {
        ConfigSector *ptSector = *iter;
        
        bRemoved = ptSector->getIndexValue(iIndex) == strVal;
        if (bRemoved)
        {
            delete ptSector;
            vecSectors.erase(iter++);
        }
    }

    return bRemoved;
}

/** 
 * Gets the first of the sectors that match a name. This is good for when you know there
 * can(should) only be one sector of a particular name.
 * 
 * @param strVal    Value to match
 * @param iIndex    Index for which the value should match
 * 
 * @return ConfigSector ptr, or nullptr if not found
 */
ConfigSector *BBConfig::getSector(const string &strVal, int iIndex)
{
    ConfigSector *ptRet = nullptr;

    for (auto ptSector : vecSectors)
    {
        if (ptSector->getIndexValue(iIndex) == strVal)
        {
            ptRet = ptSector;
            break;
        }
    }

    return ptRet;
}

/** 
 * Gets all of the vector whos index value matches
 * 
 * @param strVal    Value to match
 * @param iIndex    Index for which the value should match
 * 
 * @return vector of sectors
 */
vector<ConfigSector *> BBConfig::getSectors(const string &strVal, int iIndex)
{
    vector<ConfigSector *> vecRet;

    for (auto ptSector : vecSectors)
    {
        if (ptSector->getIndexValue(iIndex) == strVal)
            vecRet.push_back(ptSector);
    }

    return vecRet;
}

/** 
 * Get all config sectors in this config container
 * 
 * @return Config sector
 */
const vector<ConfigSector *> BBConfig::getAllSectors() const
{
    return vecSectors;
}
