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

#ifndef _BB8_TIME_H
#define _BB8_TIME_H

#include <string>
#include <time.h>

// ISO 8601 standard
#define DEFAULT_TIME_FORMAT     "%Y-%m-%d %H:%M:%S"

/**
 * Time managing class. Always assumes local time
 */
class Time
{
    public:
        enum TimeUnit
        {
            UnitNone = -1,
            Millisecond,
            Second,
            Minute,
            Hour,
            Day,
            Week,
            Month,
            Year
        };

        Time();
        Time(const struct tm &tTM);
        Time(const std::string &strTime, const std::string &strFormat = DEFAULT_TIME_FORMAT);

        Time &changeTime(enum TimeUnit eUnit, long long ullQuantity);
        std::string getTimeString(const std::string &strFormat = DEFAULT_TIME_FORMAT) const;

        // Convenient operator overrides
#if 0 // TODO <2016-10-15> implement these when we need them
        bool operator!=(const Time &tRHS) const;
        bool operator==(const Time &tRHS) const;
        bool operator<(const Time &tRHS) const;
        bool operator>(const Time &tRHS) const;
        bool operator<=(const Time &tRHS) const;
        bool operator>=(const Time &tRHS) const;
        unsigned long long operator-(const Time &tRHS) const;
        long long operator+(const Time &tRHS) const;
#endif

    private:
        struct tm tTM;

        void reset();
};

#endif

