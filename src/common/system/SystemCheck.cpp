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

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <sensors/sensors.h>
#include <string.h>
#include <unistd.h>

#include "SystemCheck.h"
#include "ColorString.h"
#include "Log.h"

using namespace std;

/** 
 * SystemCheck constructor
 */
SystemCheck::SystemCheck()
{

}

/** 
 * SystemCheck destructor
 */
SystemCheck::~SystemCheck()
{

}

/** 
 * Check system features
 * 
 * @return true if system checks pass, false on error (error msg set)
 */
bool SystemCheck::runCheck()
{
    bool bRet = true;

    logInfo(General, "Performing system check...");

    bRet = checkTemps() && checkBattery() && checkBluetooth() && checkGPIO();;

    if (!bRet)
        logCritical(General, "System check has failed");

    return bRet;
}

/** 
 * Checks the CPU cores to make sure they are not in danger of overheating
 * 
 * @return true if temps are acceptable, false if not
 */
bool SystemCheck::checkTemps()
{
    // Init libsensors and use the default config files (NULL)
    if (sensors_init(NULL) != 0)
        setError("Failed to intialize sensors lib");
    else
    {
        int iCount = 0;
        const sensors_chip_name *ptCPU = sensors_get_detected_chips(NULL, &iCount);
        
        // For each core
        while (ptCPU)
        {
            string strOutput = string("Checking CPU core temperature ") + ptCPU->path + ".............";

            // Get each tempurature feature
            int iFeat = 0;
            const sensors_feature *ptFeature = sensors_get_features(ptCPU, &iFeat);
            while (ptFeature)
            {
                #define SENSOR_TYPE_INPUT 512
                #define SENSOR_TYPE_CRIT 516

                const sensors_subfeature *ptFeatInput = sensors_get_subfeature(ptCPU, ptFeature, (sensors_subfeature_type)SENSOR_TYPE_INPUT);
                const sensors_subfeature *ptFeatCrit = sensors_get_subfeature(ptCPU, ptFeature, (sensors_subfeature_type)SENSOR_TYPE_CRIT);

                // Make sure the reading isnt at the crit level
                if (!ptFeatInput)
                    logWarn(General, "Could not get input reading for feature %s", ptFeature->name);
                else if (!ptFeatCrit)
                    logWarn(General, "Could not get crit reading for feature %s", ptFeature->name);
                else
                {
                    double dInputVal = 0;
                    double dCritVal = 0;

                    sensors_get_value(ptCPU, ptFeatInput->number, &dInputVal);
                    sensors_get_value(ptCPU, ptFeatCrit->number, &dCritVal);
                    ptFeature = NULL;

                    // Trigger temp error if the reading is withing 90% of the crit value
                    if (dInputVal >= (dCritVal * .9))
                        setError("Core \"" +  string(ptCPU->path) + "\" is too hot " + to_string(dInputVal) + "(" + to_string(dCritVal) + ")");
                    // Otherwise, get the next readings
                    else
                        ptFeature = sensors_get_features(ptCPU, &iFeat);
                }
            }

            // Set the status result
            if (isOK())
            {
                strOutput += ColorString(ColorString::Green, "OK");
                logInfo(General, "%s", strOutput.c_str());
            }
            else
            {
                strOutput += ColorString(ColorString::Red, "ERROR ") + getError();
                logError(General, "%s", strOutput.c_str());
            }

            // Get next CPU
            ptCPU = sensors_get_detected_chips(NULL, &iCount);
        }
    }

    // Cleanup
    sensors_cleanup();

    return isOK();
}

/** 
 * Checks if the battery levels are at acceptable levels
 * 
 * @return true if batteries are charged enough, false otherwise
 */
bool SystemCheck::checkBattery()
{
    /**
     * TODO
     * The Raspberry pi doesnt natively have a way to check battery levels.
     * Solutions involve using external boards and GPIO pins to measure battery levels.
     * Will probably need the PGIO pins for somethings else.
     * Instead, I could maybe delegate this task to another Raspberry pi,
     * which will somehow have to communicate with this "main" pi
     */
    logInfo(General, "Checking power levels.......");

#ifdef IS_PI3
    logWarn(General, "Power level checks not yet implemented");
#else
    logInfo(General, "Skipping power level checks on desktop environment");
#endif

    return isOK();
}

/** 
 * Checks the the bluetooth receiver is functioning
 * 
 * @return true on success, false otherwise
 */
bool SystemCheck::checkBluetooth()
{
    string strOuput = "Checking Bluetooth adaptor.....";
    int iAdaptorID = -1;
    int iBlueSocket = -1;
    inquiry_info tBlueInquiry = {'\0'};
    inquiry_info *ptInquiry = &tBlueInquiry;

    // Get the resource number of the first available Bluetooth adaptor
    iAdaptorID = hci_get_route(NULL);
    iBlueSocket = hci_open_dev(iAdaptorID);
    if (iAdaptorID < 0 || iBlueSocket < 0)
        setError("Could not find an available bluetooth adaptor");

    // Check that the adaptor is able to scan
    if (isOK())
    {
        int iRsp = hci_inquiry(iAdaptorID, 1, 1, NULL, &ptInquiry, IREQ_CACHE_FLUSH);
        if (iRsp < 0)
        {
            int iErr = errno;
            setError(strerror(iErr));
        }
    }

    // Show the result
    if (isOK())
    {
        strOuput += ColorString(ColorString::Green, "OK");
        logInfo(General, "%s", strOuput.c_str());
    }
    else
    {
        strOuput += ColorString(ColorString::Red, "ERROR ") + getError();
        logError(General, "%s", strOuput.c_str());
    }

    // Cleanup BlueZ
    close(iBlueSocket);

    return isOK();
}

/** 
 * Checks GPIO abilities
 * 
 * @return true on success, false otherwise
 */
bool SystemCheck::checkGPIO()
{
    logInfo(General, "Checking GPIO abilities........");

#ifdef IS_PI3
    logError(General, "Implement GPIO checks");
#else
    logInfo(General, "Skipping GPIO checks on desktop environment");
#endif

    return isOK();
}
