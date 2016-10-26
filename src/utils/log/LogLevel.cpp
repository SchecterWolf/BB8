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

#include <algorithm>

#include "LogLevel.h"

using namespace std;

/** 
 * Get readable Level string
 * 
 * @param eLogLevel     Level enum
 * 
 * @return Level string
 */
string LogLevel::getStrFromLevel(enum LogLevel::Level eLogLevel) const
{
    string strRet;

    switch (eLogLevel)
    {
        case Info:
            strRet = "info";
            break;
        case Warn:
            strRet = "warn";
            break;
        case Error:
            strRet = "error";
            break;
        case Critical:
            strRet = "CRITICAL";
            break;
        case Debug:
            strRet = "Debug";
            break;
        default:
            break;
    }

    return strRet;
}

/** 
 * Get the level enum from a string
 * 
 * @param strLevel  Level string
 * 
 * @return Level enum
 */
enum LogLevel::Level LogLevel::getLevelFromStr(const string &strLevel) const
{
    enum Level eLevel = None;
    string strLevelLower = strLevel;

    // We want a case insensitive comparison
    transform(strLevelLower.begin(), strLevelLower.end(), strLevelLower.begin(), ::tolower);

    for (int i = None + 1; eLevel == None && i < LevelCount; i++)
    {
        string strLower = getStrFromLevel((enum Level)i);
        transform(strLower.begin(), strLower.end(), strLower.begin(), ::tolower);

        if (strLower == strLevelLower)
            eLevel = (enum Level)i;
    }

    return eLevel;
}
