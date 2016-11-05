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

#include <string.h>

#include "Threadable.h"
#include "Log.h"

/** 
 * Threadable constructor
 * 
 * @param pfEntryFunct  Thread entry point function pointer
 */
Threadable::Threadable(Threadable::ThreadFunction pfEntryFunct)
{
    this->pfEntryFunct = pfEntryFunct;
    uiThreadID = 0;
}

/** 
 * Threadable destructor
 */
Threadable::~Threadable()
{
    join();
}

/** 
 * Spawn a thread to run asynchronously
 * 
 * @return true on successfull spawn, false otherwise
 */
bool Threadable::run()
{
    bool bRet = true;

    // Spawn thread
    if (uiThreadID != 0)
        bRet = logError(General, "Cannot start a thread that has already been started");
    else if (!pfEntryFunct)
        bRet = logError(General, "Cannot start thread that has an empty entry point");
    else
    {
        int iStatus = pthread_create(&uiThreadID, NULL, (ThreadFunc)&threadEntry, reinterpret_cast<void *>(this));
        if (iStatus != 0)
            bRet = logError(General, "Failed to create thread: %s", strerror(iStatus));
    }

    // Make sure indicate no thread is running if there's an error
    if (bRet)
        uiThreadID = 0;

    return bRet;
}

/** 
 * Wrapper for calling the thread entry point function
 * 
 * @param pvThread  this
 * 
 * @return nullptr
 */
void *Threadable::threadEntry(void *pvThread)
{
    Threadable *ptThread = reinterpret_cast<Threadable *>(pvThread);
    (ptThread->*(ptThread->pfEntryFunct))();
    
    return nullptr;
}

bool Threadable::join()
{
    bool bRet = (bool)uiThreadID;

    if (!bRet)
        logWarn(General, "unable to join a non running thread");
    else
    {
        int iStatus = pthread_join(uiThreadID, NULL);
        if (iStatus != 0)
            bRet = logError(General, "Failed to join thread %s", strerror(iStatus));
    }

    uiThreadID = 0;
    return bRet;
}

bool Threadable::kill()
{
    bool bRet = (bool)uiThreadID;

    if (!bRet)
        logWarn(General, "Unable to kill a non running thread");
    else
    {
        int iStatus = pthread_cancel(uiThreadID);
        if (iStatus != 0)
            bRet = logError(General, "Failed to kill thread: %s", strerror(iStatus));
    }

    uiThreadID = 0;
    return bRet;
}
