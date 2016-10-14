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

#include "LogTimeFormat.h"
#include "NoError.h"
#include "Time.h"

using namespace std;

/** 
 * Get the priority number in relation to other formatters
 * 
 * @return PriorityTime
 */
int LogTimeFormat::getFormatOrder() const
{
    return LogFormat::PriorityTime;
}

/** 
 * Add a time section to the log
 * 
 * @param tLogContext   Context info
 * @param strLog        Log message
 */
void LogTimeFormat::formatLog(const LogContext &tLogContext, string &strLog) const
{
    UNUSED(tLogContext);
    strLog.insert(0, "[" + Time().getTimeString() + "] ");
}
