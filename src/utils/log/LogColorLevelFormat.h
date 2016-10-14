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

#ifndef _LOGCOLORLEVELFORMAT_H
#define _LOGCOLORLEVELFORMAT_H

#include "LogLevelFormat.h"
#include "ColorString.h"

/**
 * Same as with LogLevelFormat, except with color
 */
class LogColorLevelFormat : public LogLevelFormat
{
    public:
        virtual ~LogColorLevelFormat() {};

        // LogLevelFormat virtuals
        virtual void formatLog(const LogContext &tLogContext, std::string &strLog) const override;

    private:
        enum ColorString::Color getColorFromLevel(enum LogLevel::Level eLevel) const;
};

#endif
