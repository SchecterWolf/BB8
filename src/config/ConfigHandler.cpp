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

#include "ConfigHandler.h"
#include "FileUtils.h"
#include "Log.h"

using namespace std;

/** 
 * Read in a config file and parse it into a config container
 * 
 * @param strFileName   Config file name
 * 
 * @return Filled config container
 */
BBConfig *ConfigHandler::readConfigFile(const string &strFileName) const
{
    BBConfig *ptConfig = nullptr;
    string strFileData;

    logDebug(General, "Attempting to read in config file \"%s\"", strFileName.c_str());
    if (FileUtils().readFile(strFileName, strFileData))
    {
        unsigned int uiOffset = 0;
        ptConfig = new BBConfig();

        // Parse all the sectors in the config file and add them to the config
        while (uiOffset < strFileData.size())
        {
            ConfigSector *ptSector = new ConfigSector();
            if (ptSector->parseSector(strFileData, &uiOffset))
            {
                ptConfig->addSector(unique_ptr<ConfigSector>(ptSector));
                ptSector = nullptr;
            }

            delete ptSector;
        }
    }

    return ptConfig;
}

/** 
 * Save the config container into a config file
 * 
 * @param tConfig       Config container
 * @param strFileName   Config file name
 * 
 * @return true on success, false if not
 */
bool ConfigHandler::saveConfigFile(const BBConfig &tConfig, const string &strFileName) const
{
    string strOutout;

    for (auto ptSector : tConfig.getAllSectors())
        strOutout += ptSector->serializeSector() + "\n";

    return FileUtils().writeFile(strFileName, strOutout);
}
