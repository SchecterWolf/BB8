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

#include "LogLevel.h"

using namespace std;

/** 
 * Get readable Level string
 * 
 * @param eLogLevel     Level enum
 * 
 * @return Level string
 */
string LogLevel::getLevelStr(enum LogLevel::Level eLogLevel) const
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
        case None:
        default:
            break;
    }

    return strRet;
}
