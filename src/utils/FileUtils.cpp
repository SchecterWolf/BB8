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

#include <fstream>
#include <cerrno>
#include <cstring>

#include "FileUtils.h"
#include "Log.h"

using namespace std;

/** 
 * Read the contents of a file and store it in a string
 * Should be mutex wrapped, if needed
 * TODO this can potentially throw exceptions, may want this to be a lower level IO
 * 
 * @param strFileName   File to read
 * @param strOutput     Save buffer
 * 
 * @return true on success, false otherwise
 */
bool FileUtils::readFile(const string &strFileName, string &strOutput) const
{
    bool bRet = false;
    int iError = 0;
    ifstream fsRead(strFileName, ifstream::in | ifstream::binary);

    // Check if opened
    bRet = fsRead.is_open();
    if (!bRet)
    {
        iError = errno;
        logError(General, "Unable to open file \"%s\": %s", strFileName.c_str(), strerror(iError));
    }
    // Read in file
    else
    {
        strOutput.clear();
        while (fsRead.good() && !fsRead.eof())
            strOutput.push_back(fsRead.get());

        // Check if there was an error while reading the file
        if (fsRead.bad())
        {
            iError = errno;
            strOutput.clear();
            bRet = logError(General, "Error while reading file \"%s\": %s", strFileName.c_str(), strerror(iError));
        }
    }

    return bRet;
}

/** 
 * Write contents into a file.
 * Should be mutex wrapped, if needed
 * 
 * @param strFileName   File to save too
 * @param strInput      Data to save
 * 
 * @return true on success, false otherwise
 */
bool FileUtils::writeFile(const string &strFileName, const string &strInput) const
{
    bool bRet = false;
    int iError = 0;
    ofstream fsWrite(strFileName, ofstream::in | ofstream::binary);

    // Check if opened
    if (!fsWrite.is_open())
    {
        iError = errno;
        bRet = logError(General, "Unable to open file \"%s\": %s", strFileName.c_str(), strerror(iError));
    }
    // Write file
    else
    {
        int i = 0;
        while (fsWrite.good())
            fsWrite.put(strInput[i++]);

        // Check if there was an error while writing the file
        if (fsWrite.bad())
        {
            iError = 0;
            bRet = logError(General, "Error while writing to file \"%s\": %s", strFileName.c_str(), strerror(iError));
        }
    }

    return bRet;
}
