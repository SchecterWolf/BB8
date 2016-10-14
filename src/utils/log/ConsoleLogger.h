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

#ifndef _CONSOLELOGGER_H
#define _CONSOLELOGGER_H

#include "Logger.h"

/**
 * This logger will log to the console
 */
class ConsoleLogger : public Logger
{
    public:
        ConsoleLogger();
        ConsoleLogger(std::list<LogFormat *> &listInitFormatters);
        virtual ~ConsoleLogger();

        virtual void log(const LogContext &tLogContext, const std::string &strLog) override;
};

#endif

