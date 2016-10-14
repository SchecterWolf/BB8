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

/**
 * BB-8 controller program
 *
 * Description:
 *  Main entry point into the BB-8 control routines.
 *  The controler should initialize all BB-8 resources needed
 *  by the various control directives.
 *  The main controller will listen on localhost for vairous commands
 *  that will control the overall behaviour of the BB-8.
 *  See the README for details of these commands
 *
 * Directives:
 *  These are the various modes that the BB-8 will operate in.
 *  The modes are mutually exclusive with other modes
 *      1. Followme - Directs the BB-8 to follow a bluetooth signal
 *      2. Remote control - BB-8 can be controlled with a remot control
 *                         via a bluetooth teather to an Android phone.
 *      3. Patrol - BB-8 will "wonder" around within a certain perimeter.
 *                  TODO havent decided what other functionality will
 *                       pair with this directive.
 *      4. Game - TODO Think of some cool games that can be played
 *                with the BB-8 (jousting)
 *
 * Functions:
 *  These MAY be enabled for any of the previously mentioned directive
 *  modes
 *      1. Projector - Will activate an on-board pocket project and
 *                     display videos, feeds, etc
 *      2. Speaker - Functions as a bluetooth speaker would
 *      3. Record - Enables an on-board camera and records
 *      4. Live stream - Will record and live stream through an internet
 *                       connection
 *      5. Access point - Functions as a wireless hotspot
 *      6. Camera - Takes photos
 *      7. Interactive - Tries to recognize human shape/gestures and
 *                       reacts to them
 *
 * Features:
 *  Various capabilities
 *      1. Bluetooth
 *      2. Wifi
 *      3. Web interface
 *      4. SSH
 *      5. Access point
 *      6. chassy lights
 *      7. speaker, voice module
 *      8. Camera
 *      9. various sensors
 */

#include <stdio.h>

#include "CMDLineParser.h"
#include "DroidMain.h"

int main (int argc, char **argv) {
    DroidMain tMain(CMDLineParser(argc, argv).getArgs());

    int iRet = tMain.run();

    printf("Droid operations completed.\n");
    return iRet;
}
