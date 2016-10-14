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

#include "LogColorLevelFormat.h"

using namespace std;

/** 
 * Adds a colored log level to the log
 * 
 * @param tLogContext   Context info
 * @param strLog        Log message
 */
void LogColorLevelFormat::formatLog(const LogContext &tLogContext, string &strLog) const
{
    ColorString strLevelColor(getColorFromLevel(tLogContext.getLogLevel()), LogLevel().getLevelStr(tLogContext.getLogLevel()));
    strLog.insert(0, strLevelColor + " | ");
}

/** 
 * Gets the appropriate color for a log level
 * 
 * @param eLevel    Log level
 * 
 * @return Log level color
 */
enum ColorString::Color LogColorLevelFormat::getColorFromLevel(enum LogLevel::Level eLevel) const
{
    enum ColorString::Color eColor = ColorString::None;

    switch (eLevel)
    {
        case LogLevel::Info:
            eColor = ColorString::White;
            break;
        case LogLevel::Warn:
            eColor = ColorString::Yellow;
            break;
        case LogLevel::Error:
        case LogLevel::Critical:
            eColor = ColorString::Red;
            break;
        case LogLevel::Debug:
            eColor = ColorString::LightBlue;
            break;
        default:
            break;
    }

    return eColor;
}
