/*********************************************************************
*
* $Id: cmdline_linker.cpp 34056 2019-01-21 10:08:43Z seb $
*
* implementation of cmdline  API generic class & functions
*
* - - - - - - - - - License information: - - - - - - - - -
*
* Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
*
* 1) If you have obtained this file from www.yoctopuce.com,
*    Yoctopuce Sarl licenses to you (hereafter Licensee) the
*    right to use, modify, copy, and integrate this source file
*    into your own solution for the sole purpose of interfacing
*    a Yoctopuce product with Licensee's solution.
*
*    The use of this file and all relationship between Yoctopuce
*    and Licensee are governed by Yoctopuce General Terms and
*    Conditions.
*
*    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
*    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
*    WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS
*    FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
*    EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
*    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
*    COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR
*    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
*    LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
*    CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
*    BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
*    WARRANTY, OR OTHERWISE.
*
* 2) If your intent is not to interface with Yoctopuce products,
*    you are not entitled to use, read or create any derived
*    material from this source file.
*
*********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "cmdline_common.h"


#if defined(CMD_YSH) || defined(CMD_YAccelerometer)
#include "YAccelerometer.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YAltitude)
#include "YAltitude.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YAnButton)
#include "YAnButton.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YBuzzer)
#include "YBuzzer.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YCarbonDioxide)
#include "YCarbonDioxide.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YCellular)
#include "YCellular.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YColorLed)
#include "YColorLed.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YColorLedCluster)
#include "YColorLedCluster.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YCompass)
#include "YCompass.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YCurrent)
#include "YCurrent.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YCurrentLoopOutput)
#include "YCurrentLoopOutput.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YDaisyChain)
#include "YDaisyChain.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YDataLogger)
#include "YDataLogger.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YDigitalIO)
#include "YDigitalIO.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YDisplay)
#include "YDisplay.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YDualPower)
#include "YDualPower.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YFiles)
#include "YFiles.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YGenericSensor)
#include "YGenericSensor.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YGps)
#include "YGps.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YGroundSpeed)
#include "YGroundSpeed.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YGyro)
#include "YGyro.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YHubPort)
#include "YHubPort.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YHumidity)
#include "YHumidity.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YLatitude)
#include "YLatitude.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YLongitude)
#include "YLongitude.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YLed)
#include "YLed.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YLightSensor)
#include "YLightSensor.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YMagnetometer)
#include "YMagnetometer.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YMessageBox)
#include "YMessageBox.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YMotor)
#include "YMotor.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YNetwork)
#include "YNetwork.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YPower)
#include "YPower.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YPressure)
#include "YPressure.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YProximity)
#include "YProximity.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YPowerOutput)
#include "YPowerOutput.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YPowerSupply)
#include "YPowerSupply.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YPwmInput)
#include "YPwmInput.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YPwmOutput)
#include "YPwmOutput.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YPwmPowerSource)
#include "YPwmPowerSource.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YQuadratureDecoder)
#include "YQuadratureDecoder.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YRangeFinder)
#include "YRangeFinder.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YRealTimeClock)
#include "YRealTimeClock.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YRefFrame)
#include "YRefFrame.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YRelay)
#include "YRelay.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YSegmentedDisplay)
#include "YSegmentedDisplay.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YSerialPort)
#include "YSerialPort.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YServo)
#include "YServo.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YSpiPort)
#include "YSpiPort.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YStepperMotor)
#include "YStepperMotor.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YMultiAxisController)
#include "YMultiAxisController.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YMultiCellWeighScale)
#include "YMultiCellWeighScale.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YMultiSensController)
#include "YMultiSensController.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YTemperature)
#include "YTemperature.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YTilt)
#include "YTilt.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YTvoc)
#include "YTvoc.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YVoc)
#include "YVoc.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YVoltage)
#include "YVoltage.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YVoltageOutput)
#include "YVoltageOutput.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YWakeUpMonitor)
#include "YWakeUpMonitor.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YWakeUpSchedule)
#include "YWakeUpSchedule.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YWatchdog)
#include "YWatchdog.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YWeighScale)
#include "YWeighScale.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YWireless)
#include "YWireless.h"
#endif

#if defined(CMD_YSH) || defined(CMD_YSensor)
#include "YSensor.h"
#endif
#if defined(CMD_YSH) || defined(CMD_YModule)
#include "YModule.h"
#endif

void linkYFunctionsCmdLine(vector<YFunctionCmdLine*> *allCmdlines)
{


    // register specific commands
#if defined(CMD_YSH) || defined(CMD_YAccelerometer)
    allCmdlines->push_back(new YAccelerometerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YAltitude)
    allCmdlines->push_back(new YAltitudeCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YAnButton)
    allCmdlines->push_back(new YAnButtonCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YBuzzer)
    allCmdlines->push_back(new YBuzzerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YCarbonDioxide)
    allCmdlines->push_back(new YCarbonDioxideCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YCellular)
    allCmdlines->push_back(new YCellularCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YColorLed)
    allCmdlines->push_back(new YColorLedCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YColorLedCluster)
    allCmdlines->push_back(new YColorLedClusterCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YCompass)
    allCmdlines->push_back(new YCompassCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YCurrent)
    allCmdlines->push_back(new YCurrentCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YCurrentLoopOutput)
    allCmdlines->push_back(new YCurrentLoopOutputCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YDaisyChain)
    allCmdlines->push_back(new YDaisyChainCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YDataLogger)
    allCmdlines->push_back(new YDataLoggerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YDigitalIO)
    allCmdlines->push_back(new YDigitalIOCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YDisplay)
    allCmdlines->push_back(new YDisplayCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YDualPower)
    allCmdlines->push_back(new YDualPowerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YFiles)
    allCmdlines->push_back(new YFilesCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YGenericSensor)
    allCmdlines->push_back(new YGenericSensorCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YGps)
    allCmdlines->push_back(new YGpsCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YGroundSpeed)
    allCmdlines->push_back(new YGroundSpeedCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YGyro)
    allCmdlines->push_back(new YGyroCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YHubPort)
    allCmdlines->push_back(new YHubPortCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YHumidity)
    allCmdlines->push_back(new YHumidityCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YLatitude)
    allCmdlines->push_back(new YLatitudeCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YLongitude)
    allCmdlines->push_back(new YLongitudeCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YLed)
    allCmdlines->push_back(new YLedCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YLightSensor)
    allCmdlines->push_back(new YLightSensorCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YMagnetometer)
    allCmdlines->push_back(new YMagnetometerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YMessageBox)
    allCmdlines->push_back(new YMessageBoxCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YMotor)
    allCmdlines->push_back(new YMotorCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YMultiAxisController)
    allCmdlines->push_back(new YMultiAxisControllerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YMultiCellWeighScale)
    allCmdlines->push_back(new YMultiCellWeighScaleCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YMultiSensController)
    allCmdlines->push_back(new YMultiSensControllerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YNetwork)
    allCmdlines->push_back(new YNetworkCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YPower)
    allCmdlines->push_back(new YPowerCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YPressure)
    allCmdlines->push_back(new YPressureCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YProximity)
    allCmdlines->push_back(new YProximityCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YPowerOutput)
    allCmdlines->push_back(new YPowerOutputCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YPowerSupply)
    allCmdlines->push_back(new YPowerSupplyCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YPwmInput)
    allCmdlines->push_back(new YPwmInputCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YPwmOutput)
    allCmdlines->push_back(new YPwmOutputCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YPwmPowerSource)
    allCmdlines->push_back(new YPwmPowerSourceCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YQuadratureDecoder)
    allCmdlines->push_back(new YQuadratureDecoderCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YRangeFinder)
    allCmdlines->push_back(new YRangeFinderCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YRealTimeClock)
    allCmdlines->push_back(new YRealTimeClockCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YRefFrame)
    allCmdlines->push_back(new YRefFrameCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YRelay)
    allCmdlines->push_back(new YRelayCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YSegmentedDisplay)
    allCmdlines->push_back(new YSegmentedDisplayCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YSerialPort)
    allCmdlines->push_back(new YSerialPortCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YServo)
    allCmdlines->push_back(new YServoCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YSpiPort)
    allCmdlines->push_back(new YSpiPortCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YStepperMotor)
    allCmdlines->push_back(new YStepperMotorCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YTemperature)
    allCmdlines->push_back(new YTemperatureCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YTilt)
    allCmdlines->push_back(new YTiltCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YTvoc)
    allCmdlines->push_back(new YTvocCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YVoc)
    allCmdlines->push_back(new YVocCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YVoltage)
    allCmdlines->push_back(new YVoltageCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YVoltageOutput)
    allCmdlines->push_back(new YVoltageOutputCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YWakeUpMonitor)
    allCmdlines->push_back(new YWakeUpMonitorCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YWakeUpSchedule)
    allCmdlines->push_back(new YWakeUpScheduleCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YWatchdog)
    allCmdlines->push_back(new YWatchdogCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YWeighScale)
    allCmdlines->push_back(new YWeighScaleCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YWireless)
    allCmdlines->push_back(new YWirelessCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YModule)
    allCmdlines->push_back(new YModuleCmdLine());
#endif

#if defined(CMD_YSH) || defined(CMD_YSensor)
    allCmdlines->push_back(new YSensorCmdLine());
#endif

}
