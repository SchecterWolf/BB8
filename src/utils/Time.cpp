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

#include <string.h>

#include "Time.h"

using namespace std;

/** 
 * Time default constructor that sets time to current
 */
Time::Time()
{
    reset();

    // Current calendar time as a time_t object
    time_t _tTime = time(NULL);
    localtime_r(&_tTime, &tTM);
}

/** 
 * Sets Time from a tm struct
 * 
 * @param tTM   tm struct
 */
Time::Time(const struct tm &tTM)
{
    reset();
    memcpy(&this->tTM, &tTM, sizeof(tTM));
}

/** 
 * Sets Time for a formatted time string
 * 
 * @param strTime   Time string
 * @param strFormat Format that strTime is in
 */
Time::Time(const string &strTime, const string &strFormat)
{
    reset();
    strptime(strTime.c_str(), strFormat.c_str(), &tTM);
}

/** 
 * Resets the internal time structure
 */
void Time::reset()
{
    tTM = {0};
}

/** 
 * Add or subtract time with respect to a time unit
 * 
 * @param eUnit         Time unit
 * @param ullQuantity   Quantity to change
 * 
 * @return This
 */
Time &Time::changeTime(enum TimeUnit eUnit, long long ullQuantity)
{
    switch(eUnit)
    {
        case Millisecond:
            tTM.tm_sec += (ullQuantity / 1000);
            break;
        case Second:
            tTM.tm_sec += ullQuantity;
            break;
        case Minute:
            tTM.tm_min += ullQuantity;
            break;
        case Hour:
            tTM.tm_hour += ullQuantity;
            break;
        case Day:
            tTM.tm_mday += ullQuantity;
            break;
        case Week:
            tTM.tm_mday += ullQuantity * 7;
            break;
        case Month:
            tTM.tm_mon += ullQuantity;
            break;
        case Year:
            tTM.tm_year += ullQuantity;
            break;
        case UnitNone:
        default:
            break;
    };

    return (*this);
}

/** 
 * Get a formatted time string
 * 
 * @param strFormat     Time format
 * 
 * @return Time string
 */
string Time::getTimeString(const string &strFormat) const
{
    #define TIME_LEN_MAX 128
    char szBuff[TIME_LEN_MAX] = {'\0'};
    strftime(szBuff, sizeof(szBuff) - 1, strFormat.c_str(), &tTM);

    return szBuff;
}
