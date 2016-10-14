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

#ifndef _CMDPARSER_H
#define _CMDPARSER_H

#include <argp.h>

/**
 * This class handles that command line args given to the program
 * It also defines which type of args we will handle
 */
class CMDParser
{
    typedef struct arguments
    {
        int iVerbose;
        int iQuiet;
        const char *pszConfigFile;
    } T_Arguments;

    public:
        CMDParser(int argc, char **argv); 
        ~CMDParser();

        // argp globals
        const char *args_doc;

        struct argp_option *ptOptions;
        struct argp tArgp;

        static error_t parse_opt(int iKey, char *pszArg, struct argp_state *ptState);
 
    private:
        T_Arguments tGivenArgs;

        void initCommandLineOptions();
        void initDefaultProgramOptions();
        void printDebug() const; 
};
#endif
