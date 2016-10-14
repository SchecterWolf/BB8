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

#ifndef _VARARGS_H
#define _VARARGS_H

#include <stdarg.h>

// Variable args to c++ string
#define VARARGS(__str, _pszFormat) \
do { \
    va_list _vaAP; \
    /* Get length of args buffer */ \
    va_start(_vaAP, _pszFormat); \
    char _cBuf = '\0'; \
    unsigned int _uiLen = (unsigned int)vsnprintf(&_cBuf, sizeof(_cBuf), _pszFormat, _vaAP); \
    va_end(_vaAP); \
    /* Make message*/ \
    char *__pszBuf = (char *)malloc(_uiLen +1); \
    va_start(_vaAP, _pszFormat); \
    vsnprintf(__pszBuf, _uiLen + 1, _pszFormat, _vaAP); \
    va_end(_vaAP); \
    __str = string(__pszBuf); \
    free(__pszBuf); \
} while (0)

#endif
