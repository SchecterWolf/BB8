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

#include "DroidMain.h"
#include "ConfigHandler.h"
#include "ConsoleLogger.h"
#include "Log.h"
#include "StringUtils.h"

using namespace std;

/** 
 * DroidMain constructor
 * Main class for the droid program. Initializes base structures before the main functions of the bot
 * are started
 * 
 * @param tArgs     Parsed args given from the command line
 */
DroidMain::DroidMain(const T_Arguments &tArgs)
{
    this->tArgs = tArgs;
    ptConfig = nullptr;

    initGlobalLogger();
}

/** 
 * DroidMain destructor
 */
DroidMain::~DroidMain()
{
    delete ptConfig;
}

/** 
 * Start the BB8 for operations
 * 
 * @return program exit code
 */
int DroidMain::run()
{
    readConfig();
    initGlobalLogger();

    return 0;
}

/** 
 * Initializes the global logger using either the command line args or the config file
 */
void DroidMain::initGlobalLogger() const
{
    if (!tArgs.iQuiet)
    {
        LogManager::gtLog.clearLoggers();

        // Create a verbose logger
        if (tArgs.iVerbose)
        {
            LogManager::gtLog.addLogger(new ConsoleLogger());
            LogManager::gtLog.setLogLevel(LogLevel::Info);
        }
        // Create a logger from the config file
        else if (ptConfig)
        {
            ConfigSector *ptLogSector = ptConfig->getSector("log");
            if (ptLogSector)
            {
                // Console logger
                if (StringUtils().getStringBool(ptLogSector->getValue("console")))
                    LogManager::gtLog.addLogger(new ConsoleLogger());

                // TODO File logger

                // Logger level
                LogManager::gtLog.setLogLevel(LogLevel().getLevelFromStr(ptLogSector->getValue("level")));
            }
        }
    }
}

/** 
 * Read in the config file
 */
void DroidMain::readConfig()
{
    ptConfig = ConfigHandler().readConfigFile(tArgs.pszConfigFile);

    // Use an empty config if we couldnt read one in
    if (!ptConfig)
    {
        logWarn(General, "Failed to read in config file \"%s\"", tArgs.pszConfigFile);
        ptConfig = new BBConfig();
    }
}

