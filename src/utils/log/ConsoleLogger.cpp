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

#include <iostream>

#include "ConsoleLogger.h"
#include "LogCategoryFormat.h"
#include "LogColorLevelFormat.h"
#include "LogSourceFormat.h"
#include "LogTimeFormat.h"

using namespace std;

/** 
 * ConsoleLogger constructor
 */
ConsoleLogger::ConsoleLogger()
{
    // Default formatters for the console loger
    addFormatter(new LogTimeFormat());
    addFormatter(new LogColorLevelFormat());
    addFormatter(new LogCategoryFormat());
    addFormatter(new LogSourceFormat());
}

/** 
 * ConsoleLogger with a list of log formatters
 * 
 * @param listInitFormatters    List of formatters that this log will use
 */
ConsoleLogger::ConsoleLogger(list<LogFormat *> &listInitFormatters) : Logger(listInitFormatters)
{

}

/** 
 * ConsoleLogger destructor
 */
ConsoleLogger::~ConsoleLogger()
{

}

/** 
 * Log a message
 * 
 * @param tLogContext   Context info
 * @param strLog        Log message
 */
void ConsoleLogger::log(const LogContext &tLogContext, const string &strLog)
{
    string str = strLog;

    // Apply each format rule to the log string
    for (auto formatter : listFormatters)
        formatter->formatLog(tLogContext, str);

    cout << str << "\n";
}
