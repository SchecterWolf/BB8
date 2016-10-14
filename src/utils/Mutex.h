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

#ifndef _BB8_MUTEX_H
#define _BB8_MUTEX_H

#include <pthread.h>

/**
 * Normal style mutexes
 * TODO <2016-10-23> maybe add other style mutexes if we need it (recursive, etc)
 */
class Mutex
{
    public:
        Mutex();
        virtual ~Mutex();

        void lock();
        void unlock();

        bool tryToLock(unsigned int uiMilliseconds = 0);

    private:
        pthread_mutex_t *ptMTX;
};

#endif
