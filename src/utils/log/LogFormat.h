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

#ifndef _LOGFORMAT_H
#define _LOGFORMAT_H

#include <string>

#include "LogContext.h"

/**
 * Interface for any log class that will "format" the a message
 */
class LogFormat
{
    public:
        virtual ~LogFormat() {};

        virtual int getFormatOrder() const = 0;
        virtual void formatLog(const LogContext &tLogContext, std::string &strLog) const = 0;

    protected:
        enum LogPriority
        {
            PriorityTime = 0,
            PriorityLevel,
            PriorityCategory,
            PrioritySource
        };
};

#endif

