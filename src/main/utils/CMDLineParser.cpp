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

#include <stdlib.h>

#include "CMDLineParser.h"
#include "Version.h"

//#define DEBUG_PRINT
#define DEFAULT_CONFIG_FILE "/etc/BB8/BB.config"

/** 
 * CMDLineParser constructor
 * 
 * @param argc  Arg num given from main
 * @param argv  Args given from main
 */
CMDLineParser::CMDLineParser(int argc, char **argv)
{
    argp_program_version = pszBB8Version;
    argp_program_bug_address = pszBugInfo;
    initDefaultProgramOptions();
    initCommandLineOptions();

    // We don't have any mandatory arguments as of now
    args_doc = NULL;

    tArgp = {ptOptions, parse_opt, args_doc, pszDoc};

    // Parse them args
    argp_parse(&tArgp, argc, argv, 0, 0, &tGivenArgs);

#ifdef DEBUG_PRINT
    printDebug();
#endif
}

/** 
 * CMDLineParser destructor
 */
CMDLineParser::~CMDLineParser()
{
    if (ptOptions)
        free(ptOptions);
}

/** 
 * Get the parsed command line args that were issued
 * 
 * @return Parsed args struct
 */
const T_Arguments CMDLineParser::getArgs() const
{
    return tGivenArgs;
}

/** 
 * Argument parser callback function
 * 
 * @param iKey      Key from this argp_option's key field
 * @param pszArg    Arg value
 * @param ptState   Context info
 * 
 * @return  0 for success, ARGP_ERR_UNKNOWN if the value of key is not handled, or a unix error code
 */
error_t CMDLineParser::parse_opt(int iKey, char *pszArg, struct argp_state *ptState)
{
    error_t iRet = 0;
    T_Arguments *ptArgs = reinterpret_cast<T_Arguments *>(ptState->input);

    // Process args base on key
    switch (iKey)
    {
        case 'v':
            ptArgs->iVerbose = 1;
            break;
        case 'q':
            ptArgs->iQuiet = 1;
            break;
        case 'c':
            ptArgs->pszConfigFile = pszArg;
            break;
        default:
            iRet = ARGP_ERR_UNKNOWN;
    }

    return iRet;
}

/** 
 * Initialize the parser options that shall be interpreted
 * by this program.
 * Note: make sure to update the struct arguments and parseOpt callback as well
 */
void CMDLineParser::initCommandLineOptions()
{
    int iNumOptions = 0;

    // See link for filling out a new argp_option
    // https://www.gnu.org/software/libc/manual/html_node/Argp-Option-Vectors.html
    struct argp_option atTempArgs[] =
    {
        {"verbose", 'v', NULL,   0, "Produce verbose output"},
        {"quiet",   'q', NULL,   0, "Don't produce any output"},
        {"config",  'c', "FILE", 0, "Specify a config FILE (default " DEFAULT_CONFIG_FILE ")"},
        NULL
    };

    // Count the options
    while (atTempArgs[iNumOptions].name)
        iNumOptions++;

    // Add one for the NULL terminated array
    iNumOptions++;

    // Add to the global options array
    ptOptions = (struct argp_option *)malloc(iNumOptions * (sizeof(struct argp_option)));
    for (int i = 0; i < iNumOptions; i++)
        ptOptions[i] = atTempArgs[i];
}

/** 
 * Initialize the default argument values
 */
void CMDLineParser::initDefaultProgramOptions()
{
    tGivenArgs.iVerbose = 0;
    tGivenArgs.iQuiet = 0;
    tGivenArgs.pszConfigFile = DEFAULT_CONFIG_FILE;
}

/** 
 * Debug print the command line args the has been parsed
 */
void CMDLineParser::printDebug() const
{
    fprintf(stderr, "Printing parsed command line args:\n");
    fprintf(stderr, "Verbose:\t%d\n" \
                    "Quite:\t\t%d\n" \
                    "Config File:\t%s\n\n",
                    tGivenArgs.iVerbose, tGivenArgs.iQuiet, tGivenArgs.pszConfigFile);
}
