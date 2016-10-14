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

#include "ColorString.h"

using namespace std;

/** 
 * Default ColorString constructor
 * 
 * @param str String, if any
 */
ColorString::ColorString(const string &str) : string(str)
{
    strContents = str;
    eColor = None;
}

/** 
 * ColorString constructor with a color
 * 
 * @param eColor    Color
 * @param str       String, if any
 */
ColorString::ColorString(enum ColorString::Color eColor, const string &str)
{
    this->eColor = eColor;
    (*this) = format(eColor, str);
    strContents = str;
}

/** 
 * Allows concatination to a colored string
 * 
 * @param strRHS String concat
 *  
 * @return Color concatinated string
 */
string &ColorString::operator+=(const string &strRHS)
{
    string strTemp = strContents + strRHS;
    (*this) = format(eColor, strTemp);

    return *this;
}

/** 
 * Inserts the color prefix and suffix sequences around a string
 * 
 * @param eColor    Color
 * @param str       The string
 * 
 * @return The color encoded string
 */
string ColorString::format(enum ColorString::Color eColor, const string &str) const
{
    unsigned char aucPrefix[] = {0x1B, 0x5B, 0x30, 0x3B, 0x33, (unsigned char)eColor, 0x6D};
    unsigned char aucSuffix[] = {0x1B, 0x5B, 0x6D};

    string strRet;
    if (eColor >= FirstColor && eColor <= LastColor)
        strRet = string((const char *)aucPrefix, sizeof(aucPrefix)) + str + string((const char *)aucSuffix, sizeof(aucSuffix));

    return strRet;
}
