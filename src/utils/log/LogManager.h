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

#ifndef _LOGMANAGER_H
#define _LOGMANAGER_H

#include "LogContext.h"
#include "Logger.h"

/**
 * For now, we will have each individual thread be responsible for its own logging.
 * TODO <2016-10-18> If we need to reduce latency, make this also function as a logger thread
 */
class LogManager final
{
    public:
        LogManager();
        ~LogManager();

        void addLogger(Logger *ptLogger);
        void setLogLevel(enum LogLevel::Level eLevel);
        void clearLoggers();
        void log(const LogContext &tContext, const std::string &strLog);
        void log(const LogContext &tContext, const char *pszFormat, ...);

        // Log singleton
        static LogManager gtLog;

    private:
        LogLevel::Level eCappedLevel;
        std::list<Logger *> listLoggers;

        bool enabledLevel(enum LogLevel::Level eLevel);
};

#endif
