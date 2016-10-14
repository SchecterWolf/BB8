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

#include "LogManager.h"
#include "StdLibUtils.h"
#include "VarArgs.h"

using namespace std;

LogManager LogManager::gtLog;

/** 
 * LogManager constructor
 */
LogManager::LogManager()
{
    eCappedLevel = LogLevel::None;
}

/** 
 * LogManager destructor
 */
LogManager::~LogManager()
{
    clearLoggers();
}

/** 
 * Clear loggers
 */
void LogManager::clearLoggers()
{
    StdLibUtils().freeObjects(listLoggers);
}

/** 
 * Add a logger
 * 
 * @param ptLogger  The logger
 */
void LogManager::addLogger(Logger *ptLogger)
{
    if (ptLogger)
        listLoggers.push_back(ptLogger);
}

/** 
 * Set the "maximum" log level that we will log
 * 
 * @param eLevel Log level
 */
void LogManager::setLogLevel(enum LogLevel::Level eLevel)
{
    eCappedLevel = eLevel;
}

/** 
 * Wrapper for var args logs
 * 
 * @param tContext  Log info
 * @param pszFormat Format string
 * @param ...       string args
 */
void LogManager::log(const LogContext &tContext, const char *pszFormat, ...)
{
    string strLog;
    VARARGS(strLog, pszFormat);
    log(tContext, strLog);
}

/** 
 * Log a message
 * 
 * @param tContext  Log ingfo
 * @param strLog    Log message
 */
void LogManager::log(const LogContext &tContext, const string strLog)
{
    // Dont log if this level has not been enabled
    if (!enabledLevel(tContext.getLogLevel()))
        return;

    for (auto ptLogger : listLoggers)
        ptLogger->log(tContext, strLog);
}

/** 
 * Check of a log level is enabled
 * 
 * @param eLevel    Log level
 * 
 * @return true if enabled, false if not
 */
bool LogManager::enabledLevel(enum LogLevel::Level eLevel)
{
    return eLevel <= eCappedLevel;
}
