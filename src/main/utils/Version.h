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

#ifndef _VERSION_H
#define _VERSION_H

/**
 * Versioning information about the BB8 control program
 */

#define PROG_VERSION "0.0.1"

const char *pszBB8Version = "BB8 " PROG_VERSION " BETA\n" \
                            "Copyright (C) 2016 Free Software Foundation, Inc.\n" \
                            "This is free software; see the source for copying conditions.  There is NO\n" \
                            "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.";

const char *pszBugInfo = "<schecterwolfe@gmail.com>";

const char *pszDoc = "BB8 program that controls, initializes, and maintains\n" \
                     "all of the droid's functions, abilities, and peripherals.\n\n" \
                     "Created by: Schecter wolfe.";
#endif
