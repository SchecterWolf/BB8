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

#ifndef _THREADABLE_H
#define _THREADABLE_H

#include <pthread.h>

typedef void *(*ThreadFunc)(void*);

/**
 * Inherit this class to make a class function as a thread.
 * Threadable classes can be "run", which will trigger the start of a new thread.
 */
class Threadable
{
    public:
        typedef void (Threadable::*ThreadFunction)(void);

        Threadable(Threadable::ThreadFunction pfEntryFunct);
        virtual ~Threadable();

        bool run();
        bool join();
        bool kill();

    private:
        Threadable::ThreadFunction pfEntryFunct;
        pthread_t uiThreadID;

        static void *threadEntry(void *pvThread);
};

#endif
