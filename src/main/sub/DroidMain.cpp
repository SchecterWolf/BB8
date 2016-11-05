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
    : tInterfaceCtrl(tArgs)
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
    enum ControllerInterface::ReturnStatus eRet = ControllerInterface::StatusError;

    if (readConfig())
    {
        initGlobalLogger();
        eRet = tInterfaceCtrl.run();
    }

    return interpretReturn(eRet);
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
 *
 * @return true if successfully read in config file, false if not
 */
bool DroidMain::readConfig()
{
    ptConfig = ConfigHandler().readConfigFile(tArgs.pszConfigFile);

    // Something went wrong reading in the config file
    if (!ptConfig)
        logCritical(General, "Failed to read in config file \"%s\"", tArgs.pszConfigFile);

    return (bool)ptConfig;
}

/** 
 * Interpret the return status of the control interface
 * 
 * @param eRet  Return status
 * 
 * @return shell return code
 */
int DroidMain::interpretReturn(enum ControllerInterface::ReturnStatus eRet) const
{
    int iRet = 0;

    switch(eRet)
    {
        case ControllerInterface::StatusShutdown:
            iRet = system("sudo halt -p");
            break;
        case ControllerInterface::StatusRestart:
            iRet = system("sudo reboot");
            break;
        case ControllerInterface::StatusOK:
            break;
        case ControllerInterface::StatusError:
            iRet = 1;
            break;
        default:
            iRet = 10;
            break;
    }

    return iRet;
}
