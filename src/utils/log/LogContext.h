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

#ifndef _LOGCONTEXT_H
#define _LOGCONTEXT_H

#include "LogLevel.h"
#include "LogCategory.h"

/**
 * Log info that the loggers and formatters may use
 */
class LogContext
{
    public:
        LogContext(enum LogLevel::Level eLevel, enum LogCategory::Category eCategory, const std::string &strSource, int iLine);
        virtual ~LogContext();

        void setLogLevel(enum LogLevel::Level eLevel);
        enum LogLevel::Level getLogLevel() const;

        void setLogCategory(enum LogCategory::Category eCategory);
        enum LogCategory::Category getLogCategory() const;

        void setSource(const std::string strSource);
        const std::string &getSource() const;

        void setLine(int iLine);
        int getLine() const;

    private:
        std::string strSource;
        int iLine;
        enum LogLevel::Level eLevel;
        enum LogCategory::Category eCategory;
};

#endif

