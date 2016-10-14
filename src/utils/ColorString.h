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

#ifndef _COLORSTRING_H
#define _COLORSTRING_H

#include <string>

/**
 * Is a color string
 */
class ColorString : public std::string
{
    public:
        enum Color
        {
            None        = 0x00,
            Black       = 0x30,
            Red         = 0x31,
            Green       = 0x32,
            Yellow      = 0x33,
            Blue        = 0x34,
            Pink        = 0x35,
            LightBlue   = 0x36,
            White       = 0x37,

            FirstColor = Black,
            LastColor = White
        };

        ColorString(const std::string &str = "");
        ColorString(enum Color eColor, const std::string &str = "");

        virtual std::string &operator+=(const std::string &strRHS);

    private:
        std::string strContents;
        Color eColor;

        std::string format(enum Color eColor, const std::string &str) const;
};

#endif

