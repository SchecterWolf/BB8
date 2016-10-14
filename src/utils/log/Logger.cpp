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

#include "Logger.h"
#include "StdLibUtils.h"

using namespace std;

/** 
 * Logger constructor default
 */
Logger::Logger()
{

}

/** 
 * Logger constructor with a list of log formatters
 * 
 * @param listInitFormatters    List of formatters that this log will use
 */
Logger::Logger(list<LogFormat *> &listInitFormatters)
{
    for (auto ptFormatter : listInitFormatters)
        addFormatter(ptFormatter);
}

/** 
 * Logger destructor
 */
Logger::~Logger()
{
    StdLibUtils().freeObjects(listFormatters);
}

/** 
 * Adds log formatters to this logger in priority oder
 * 
 * @param ptFormat  Log formatter to add
 */
void Logger::addFormatter(LogFormat *ptFormat)
{
    if (!ptFormat)
        return;

    // Insert in priority order
    auto iter = listFormatters.begin();
    for ( ; iter != listFormatters.end(); ++iter)
    {
        if (ptFormat->getFormatOrder() > (*iter)->getFormatOrder())
            break;
    }

    listFormatters.insert(iter, ptFormat);
}
