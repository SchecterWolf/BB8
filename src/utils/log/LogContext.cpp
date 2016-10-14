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

#include "LogContext.h"

using namespace std;

/** 
 * LogContext constructor
 * 
 * @param eLevel        Log level
 * @param eCategory     Log category
 * @param strSource     Log source file
 * @param iLine         Log line number
 */
LogContext::LogContext(enum LogLevel::Level eLevel, enum LogCategory::Category eCategory, const string &strSource, int iLine)
{
    this->eLevel = eLevel;
    this->eCategory = eCategory;
    this->strSource = strSource;
    this->iLine = iLine;
}

/** 
 * LogContext destructor
 */
LogContext::~LogContext()
{

}

/** 
 * Set the log level
 * 
 * @param eLevel    Log level
 */
void LogContext::setLogLevel(enum LogLevel::Level eLevel)
{
    this->eLevel = eLevel;
}

/** 
 * Get the log level
 * 
 * @return Log level
 */
enum LogLevel::Level LogContext::getLogLevel() const
{
    return eLevel;
}

/** 
 * Set the log category
 * 
 * @param eCategory     Log category
 */
void LogContext::setLogCategory(enum LogCategory::Category eCategory)
{
    this->eCategory = eCategory;
}

/** 
 * Get the log category
 * 
 * @return Log category
 */
enum LogCategory::Category LogContext::getLogCategory() const
{
    return eCategory;
}

/** 
 * Set the log source
 * 
 * @param strSource     Log source
 */
void LogContext::setSource(const string strSource)
{
    this->strSource = strSource;
}

/** 
 * Get the log source
 * 
 * @return Log source
 */
const string &LogContext::getSource() const
{
    return strSource;
}

/** 
 * Set the log line
 * 
 * @param iLine     Log line
 */
void LogContext::setLine(int iLine)
{
    this->iLine = iLine;
}

/** 
 * Get the log line
 * 
 * @return Log line
 */
int LogContext::getLine() const
{
    return iLine;
}
