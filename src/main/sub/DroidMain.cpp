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
#include "ConsoleLogger.h"
#include "Log.h"

DroidMain::DroidMain(const T_Arguments &tArgs)
{
    this->tArgs = tArgs;
    initGlobalLogger();
}

DroidMain::~DroidMain()
{

}

void DroidMain::initGlobalLogger() const
{
    // Create a consol logger is verbose is given on the command line
    if (!tArgs.iQuiet && tArgs.iVerbose)
    {
        LogManager::gtLog.addLogger(new ConsoleLogger());
        LogManager::gtLog.setLogLevel(LogLevel::Debug);
    }

    // TODO use the config file to initialize the logger
}

int DroidMain::run()
{

    return 0;
}
