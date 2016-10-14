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

#ifndef _BB8_LOGGER_H
#define _BB8_LOGGER_H

#include <list>
#include <string>

#include "LogContext.h"
#include "LogFormat.h"

/**
 * Abstract class for all log classes that wish to perform logging
 */
class Logger
{
    public:
        Logger();
        Logger(std::list<LogFormat *> &listInitFormatters);
        virtual ~Logger();

        virtual void log(const LogContext &tLogContext, const std::string &strLog) = 0;

    protected:
        std::list<LogFormat *> listFormatters;

        void addFormatter(LogFormat *ptFormat);
};
#endif
