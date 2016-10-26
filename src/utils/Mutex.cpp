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

#include "Mutex.h"
#include "Log.h"

/** 
 * Mutex constructor
 */
Mutex::Mutex()
{
    pthread_mutexattr_t tAttr;
    pthread_mutexattr_init(&tAttr);
    pthread_mutexattr_settype(&tAttr, PTHREAD_MUTEX_NORMAL);
    ptMTX = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));

    if (pthread_mutex_init(ptMTX, &tAttr) != 0)
    {
        free(ptMTX);
        ptMTX= nullptr;
    }

    if (!ptMTX)
        logError(General, "Failed to create mutex");
}

/** 
 * Mutex destructor
 */
Mutex::~Mutex()
{

}

/** 
 * Lock mutex
 */
void Mutex::lock()
{
    if (ptMTX && pthread_mutex_lock(ptMTX) != 0)
        logError(General, "Could not lock mutex");
}

/** 
 * Unlock mutex
 */
void Mutex::unlock()
{
    if (ptMTX && pthread_mutex_unlock(ptMTX) != 0)
        logError(General, "Could not unlock mutex");
}

/** 
 * Try to lock a mutex with a timeout
 * 
 * @param uiMilliseconds    Timeout
 * 
 * @return true if locked, false othewise
 */
bool Mutex::tryToLock(unsigned int uiMilliseconds)
{
    if (!ptMTX)
        return false;

    bool bRet = false;

    // Timed lock
    struct timespec tTimeout = {0, 0};
    if (clock_gettime(CLOCK_REALTIME, &tTimeout) < 0)
        logError(General, "Could not get time");

    tTimeout.tv_sec += uiMilliseconds / 1000;
    uiMilliseconds = uiMilliseconds % 1000;

    unsigned long long ullTemp = tTimeout.tv_nsec + ((unsigned long long)uiMilliseconds * 1000ULL * 1000ULL);
    tTimeout.tv_sec += ullTemp / 1000000000ULL;
    tTimeout.tv_nsec = ullTemp % 1000000000ULL;

    if (pthread_mutex_timedlock(ptMTX, &tTimeout) == 0)
        bRet = true;

    return bRet;
}
