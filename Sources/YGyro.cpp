/*********************************************************************
 *
 * $Id: YGyro.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 * Implements commands to handle Gyro functions
 *
 * - - - - - - - - - License information: - - - - - - - - -
 *
 *  Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 *  Yoctopuce Sarl (hereafter Licensor) grants to you a perpetual
 *  non-exclusive license to use, modify, copy and integrate this
 *  file into your software for the sole purpose of interfacing
 *  with Yoctopuce products.
 *
 *  You may reproduce and distribute copies of this file in
 *  source or object form, as long as the sole purpose of this
 *  code is to interface with Yoctopuce products. You must retain
 *  this notice in the distributed source file.
 *
 *  You should refer to Yoctopuce General Terms and Conditions
 *  for additional information regarding your rights and
 *  obligations.
 *
 *  THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *  WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *  EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *  INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 *  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR
 *  SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
 *  LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *  CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *  BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *  WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "YGyro.h"
#include "yocto_api.h"
#include "yocto_gyro.h"

using namespace std;

//--- (generated code: YGyro definitions)

static const char *enumAdvertisingMode[] = {
    "IMMEDIATE",
    "PERIOD_AVG",
    "PERIOD_MIN",
    "PERIOD_MAX",
    NULL
};

//--- (end of generated code: YGyro definitions)

//--- (generated code: YGyro implementation)
bool   YGyroCmdLine::isModule(void)      { return false; }
string YGyroCmdLine::YFunctionName(void) { return "YGyro"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of unit is string (Text)
// type of currentValue is double (MeasureVal)
// type of lowestValue is double (MeasureVal)
// type of highestValue is double (MeasureVal)
// type of currentRawValue is double (MeasureVal)
// type of logFrequency is string (YFrequency)
// type of reportFrequency is string (YFrequency)
// type of advMode is int (AdvertisingMode)
// type of calibrationParam is string (CalibParams)
// type of resolution is double (MeasureVal)
// type of sensorState is int (Int)
// type of bandwidth is int (Int)
// type of xValue is double (MeasureVal)
// type of yValue is double (MeasureVal)
// type of zValue is double (MeasureVal)
/**
 * Returns the logical name of the gyroscope.
 *
 * @return a string corresponding to the logical name of the gyroscope
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Gyro_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Gyro_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the gyroscope.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_logicalName();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the logical name of the gyroscope. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the gyroscope
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the gyroscope.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the gyroscope", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    if (!YAPI::CheckLogicalName((*args)[0]->get_stringValue())) {
        throw std::string("Invalid name :" + (*args)[0]->get_stringValue());
    }
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_logicalName(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns a short string representing the current state of the gyroscope.
 *
 * @return a string corresponding to a short string representing the current state of the gyroscope
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Gyro_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the gyroscope.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_advertisedValue();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the measuring unit for the angular velocity.
 *
 * @return a string corresponding to the measuring unit for the angular velocity
 *
 * On failure, throws an exception or returns Y_UNIT_INVALID.
 */
class Gyro_get_unit : public YapiCommand /* arguments: */
{
public:
  Gyro_get_unit(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_unit";
  }

  string getDescription()
  {
    return "Returns the measuring unit for the angular velocity.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_unit();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current value of the angular velocity, in degrees per second, as a floating point number.
 * Note that a get_currentValue() call will *not* start a measure in the device, it
 * will just return the last measure that occurred in the device. Indeed, internally, each Yoctopuce
 * devices is continuously making measurements at a hardware specific frequency.
 *
 * If continuously calling  get_currentValue() leads you to performances issues, then
 * you might consider to switch to callback programming model. Check the "advanced
 * programming" chapter in in your device user manual for more information.
 *
 * @return a floating point number corresponding to the current value of the angular velocity, in
 * degrees per second, as a floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTVALUE_INVALID.
 */
class Gyro_get_currentValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_currentValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentValue";
  }

  string getDescription()
  {
    return "Returns the current value of the angular velocity, in degrees per second, as a floating point number.";
  }

  string getMoreInfo()
  {
    return "Note that a get_currentValue() call will *not* start a measure in the device, it will just return the last measure that occurred in the device. Indeed, internally, each Yoctopuce devices is continuously making measurements at a hardware specific frequency.\nIf continuously calling get_currentValue() leads you to performances issues, then you might consider to switch to callback programming model. Check the \"advanced programming\" chapter in in your device user manual for more information.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the recorded minimal value observed. Can be used to reset the value returned
 * by get_lowestValue().
 *
 * @param newval : a floating point number corresponding to the recorded minimal value observed
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_lowestValue : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_lowestValue(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_lowestValue";
  }

  string getDescription()
  {
    return "Changes the recorded minimal value observed.";
  }

  string getMoreInfo()
  {
    return "Can be used to reset the value returned by get_lowestValue().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the recorded minimal value observed", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_lowestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the minimal value observed for the angular velocity since the device was started.
 * Can be reset to an arbitrary value thanks to set_lowestValue().
 *
 * @return a floating point number corresponding to the minimal value observed for the angular
 * velocity since the device was started
 *
 * On failure, throws an exception or returns Y_LOWESTVALUE_INVALID.
 */
class Gyro_get_lowestValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_lowestValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_lowestValue";
  }

  string getDescription()
  {
    return "Returns the minimal value observed for the angular velocity since the device was started.";
  }

  string getMoreInfo()
  {
    return "Can be reset to an arbitrary value thanks to set_lowestValue().";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_lowestValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the recorded maximal value observed. Can be used to reset the value returned
 * by get_lowestValue().
 *
 * @param newval : a floating point number corresponding to the recorded maximal value observed
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_highestValue : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_highestValue(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_highestValue";
  }

  string getDescription()
  {
    return "Changes the recorded maximal value observed.";
  }

  string getMoreInfo()
  {
    return "Can be used to reset the value returned by get_lowestValue().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the recorded maximal value observed", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_highestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximal value observed for the angular velocity since the device was started.
 * Can be reset to an arbitrary value thanks to set_highestValue().
 *
 * @return a floating point number corresponding to the maximal value observed for the angular
 * velocity since the device was started
 *
 * On failure, throws an exception or returns Y_HIGHESTVALUE_INVALID.
 */
class Gyro_get_highestValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_highestValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_highestValue";
  }

  string getDescription()
  {
    return "Returns the maximal value observed for the angular velocity since the device was started.";
  }

  string getMoreInfo()
  {
    return "Can be reset to an arbitrary value thanks to set_highestValue().";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_highestValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the uncalibrated, unrounded raw value returned by the sensor, in degrees per second, as a
 * floating point number.
 *
 * @return a floating point number corresponding to the uncalibrated, unrounded raw value returned by
 * the sensor, in degrees per second, as a floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTRAWVALUE_INVALID.
 */
class Gyro_get_currentRawValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_currentRawValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentRawValue";
  }

  string getDescription()
  {
    return "Returns the uncalibrated, unrounded raw value returned by the sensor, in degrees per second, as a floating point number.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentRawValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the datalogger recording frequency for this function, or "OFF"
 * when measures are not stored in the data logger flash memory.
 *
 * @return a string corresponding to the datalogger recording frequency for this function, or "OFF"
 *         when measures are not stored in the data logger flash memory
 *
 * On failure, throws an exception or returns Y_LOGFREQUENCY_INVALID.
 */
class Gyro_get_logFrequency : public YapiCommand /* arguments: */
{
public:
  Gyro_get_logFrequency(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logFrequency";
  }

  string getDescription()
  {
    return "Returns the datalogger recording frequency for this function, or \"OFF\"when measures are not stored in the data logger flash memory.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_logFrequency();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the datalogger recording frequency for this function.
 * The frequency can be specified as samples per second,
 * as sample per minute (for instance "15/m") or in samples per
 * hour (eg. "4/h"). To disable recording for this function, use
 * the value "OFF". Note that setting the  datalogger recording frequency
 * to a greater value than the sensor native sampling frequency is useless,
 * and even counterproductive: those two frequencies are not related.
 *
 * @param newval : a string corresponding to the datalogger recording frequency for this function
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_logFrequency : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_logFrequency(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logFrequency";
  }

  string getDescription()
  {
    return "Changes the datalogger recording frequency for this function.";
  }

  string getMoreInfo()
  {
    return "The frequency can be specified as samples per second, as sample per minute (for instance \"15/m\") or in samples per hour (eg. \"4/h\"). To disable recording for this function, use the value \"OFF\". Note that setting the datalogger recording frequency to a greater value than the sensor native sampling frequency is useless, and even counterproductive: those two frequencies are not related.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the datalogger recording frequency for this function", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_logFrequency(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the timed value notification frequency, or "OFF" if timed
 * value notifications are disabled for this function.
 *
 * @return a string corresponding to the timed value notification frequency, or "OFF" if timed
 *         value notifications are disabled for this function
 *
 * On failure, throws an exception or returns Y_REPORTFREQUENCY_INVALID.
 */
class Gyro_get_reportFrequency : public YapiCommand /* arguments: */
{
public:
  Gyro_get_reportFrequency(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_reportFrequency";
  }

  string getDescription()
  {
    return "Returns the timed value notification frequency, or \"OFF\" if timedvalue notifications are disabled for this function.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_reportFrequency();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the timed value notification frequency for this function.
 * The frequency can be specified as samples per second,
 * as sample per minute (for instance "15/m") or in samples per
 * hour (e.g. "4/h"). To disable timed value notifications for this
 * function, use the value "OFF". Note that setting the  timed value
 * notification frequency to a greater value than the sensor native
 * sampling frequency is unless, and even counterproductive: those two
 * frequencies are not related.
 *
 * @param newval : a string corresponding to the timed value notification frequency for this function
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_reportFrequency : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_reportFrequency(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_reportFrequency";
  }

  string getDescription()
  {
    return "Changes the timed value notification frequency for this function.";
  }

  string getMoreInfo()
  {
    return "The frequency can be specified as samples per second, as sample per minute (for instance \"15/m\") or in samples per hour (e.g. \"4/h\"). To disable timed value notifications for this function, use the value \"OFF\". Note that setting the timed value notification frequency to a greater value than the sensor native sampling frequency is unless, and even counterproductive: those two frequencies are not related.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the timed value notification frequency for this function", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_reportFrequency(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the measuring mode used for the advertised value pushed to the parent hub.
 *
 * @return a value among Y_ADVMODE_IMMEDIATE, Y_ADVMODE_PERIOD_AVG, Y_ADVMODE_PERIOD_MIN and
 * Y_ADVMODE_PERIOD_MAX corresponding to the measuring mode used for the advertised value pushed to the parent hub
 *
 * On failure, throws an exception or returns Y_ADVMODE_INVALID.
 */
class Gyro_get_advMode : public YapiCommand /* arguments: */
{
public:
  Gyro_get_advMode(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advMode";
  }

  string getDescription()
  {
    return "Returns the measuring mode used for the advertised value pushed to the parent hub.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_advMode();
        string strval =  enumString(attrval,enumAdvertisingMode);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the measuring mode used for the advertised value pushed to the parent hub.
 *
 * @param newval : a value among Y_ADVMODE_IMMEDIATE, Y_ADVMODE_PERIOD_AVG, Y_ADVMODE_PERIOD_MIN and
 * Y_ADVMODE_PERIOD_MAX corresponding to the measuring mode used for the advertised value pushed to the parent hub
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_advMode : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_advMode(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_advMode";
  }

  string getDescription()
  {
    return "Changes the measuring mode used for the advertised value pushed to the parent hub.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among IMMEDIATE, PERIOD_AVG, PERIOD_MIN and PERIOD_MAX corresponding to the measuring mode used for the advertised value pushed to the parent hub", "IMMEDIATE=0,PERIOD_AVG=1,PERIOD_MIN=2,PERIOD_MAX=3", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_advMode(Y_ADVMODE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Changes the resolution of the measured physical values. The resolution corresponds to the numerical precision
 * when displaying value. It does not change the precision of the measure itself.
 *
 * @param newval : a floating point number corresponding to the resolution of the measured physical values
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_resolution : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_resolution(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_resolution";
  }

  string getDescription()
  {
    return "Changes the resolution of the measured physical values.";
  }

  string getMoreInfo()
  {
    return "The resolution corresponds to the numerical precision when displaying value. It does not change the precision of the measure itself.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the resolution of the measured physical values", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_resolution(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the resolution of the measured values. The resolution corresponds to the numerical precision
 * of the measures, which is not always the same as the actual precision of the sensor.
 *
 * @return a floating point number corresponding to the resolution of the measured values
 *
 * On failure, throws an exception or returns Y_RESOLUTION_INVALID.
 */
class Gyro_get_resolution : public YapiCommand /* arguments: */
{
public:
  Gyro_get_resolution(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_resolution";
  }

  string getDescription()
  {
    return "Returns the resolution of the measured values.";
  }

  string getMoreInfo()
  {
    return "The resolution corresponds to the numerical precision of the measures, which is not always the same as the actual precision of the sensor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_resolution();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the sensor health state code, which is zero when there is an up-to-date measure
 * available or a positive code if the sensor is not able to provide a measure right now.
 *
 * @return an integer corresponding to the sensor health state code, which is zero when there is an
 * up-to-date measure
 *         available or a positive code if the sensor is not able to provide a measure right now
 *
 * On failure, throws an exception or returns Y_SENSORSTATE_INVALID.
 */
class Gyro_get_sensorState : public YapiCommand /* arguments: */
{
public:
  Gyro_get_sensorState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_sensorState";
  }

  string getDescription()
  {
    return "Returns the sensor health state code, which is zero when there is an up-to-date measureavailable or a positive code if the sensor is not able to provide a measure right now.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_sensorState();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the measure update frequency, measured in Hz (Yocto-3D-V2 only).
 *
 * @return an integer corresponding to the measure update frequency, measured in Hz (Yocto-3D-V2 only)
 *
 * On failure, throws an exception or returns Y_BANDWIDTH_INVALID.
 */
class Gyro_get_bandwidth : public YapiCommand /* arguments: */
{
public:
  Gyro_get_bandwidth(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_bandwidth";
  }

  string getDescription()
  {
    return "Returns the measure update frequency, measured in Hz (Yocto-3D-V2 only).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_bandwidth();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the measure update frequency, measured in Hz (Yocto-3D-V2 only). When the
 * frequency is lower, the device performs averaging.
 *
 * @param newval : an integer corresponding to the measure update frequency, measured in Hz (Yocto-3D-V2 only)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gyro_set_bandwidth : public YapiCommand /* arguments: newval */
{
public:
  Gyro_set_bandwidth(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_bandwidth";
  }

  string getDescription()
  {
    return "Changes the measure update frequency, measured in Hz (Yocto-3D-V2 only).";
  }

  string getMoreInfo()
  {
    return "When the frequency is lower, the device performs averaging.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the measure update frequency, measured in Hz (Yocto-3D-V2 only)", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_bandwidth(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the angular velocity around the X axis of the device, as a floating point number.
 *
 * @return a floating point number corresponding to the angular velocity around the X axis of the
 * device, as a floating point number
 *
 * On failure, throws an exception or returns Y_XVALUE_INVALID.
 */
class Gyro_get_xValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_xValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_xValue";
  }

  string getDescription()
  {
    return "Returns the angular velocity around the X axis of the device, as a floating point number.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_xValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the angular velocity around the Y axis of the device, as a floating point number.
 *
 * @return a floating point number corresponding to the angular velocity around the Y axis of the
 * device, as a floating point number
 *
 * On failure, throws an exception or returns Y_YVALUE_INVALID.
 */
class Gyro_get_yValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_yValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_yValue";
  }

  string getDescription()
  {
    return "Returns the angular velocity around the Y axis of the device, as a floating point number.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_yValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the angular velocity around the Z axis of the device, as a floating point number.
 *
 * @return a floating point number corresponding to the angular velocity around the Z axis of the
 * device, as a floating point number
 *
 * On failure, throws an exception or returns Y_ZVALUE_INVALID.
 */
class Gyro_get_zValue : public YapiCommand /* arguments: */
{
public:
  Gyro_get_zValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_zValue";
  }

  string getDescription()
  {
    return "Returns the angular velocity around the Z axis of the device, as a floating point number.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_zValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackGyro is YGyroValueCallback* (YGyroValueCallback)
// type of timedReportCallbackGyro is YGyroTimedReportCallback* (YGyroTimedReportCallback)
// type of qt_stamp is int (int)
// type of qt_w is YQt* (YQt)
// type of qt_x is YQt* (YQt)
// type of qt_y is YQt* (YQt)
// type of qt_z is YQt* (YQt)
// type of w is double (float)
// type of x is double (float)
// type of y is double (float)
// type of z is double (float)
// type of angles_stamp is int (int)
// type of head is double (float)
// type of pitch is double (float)
// type of roll is double (float)
// type of quatCallback is YQuatCallback* (YQuatCallback)
// type of anglesCallback is YAnglesCallback* (YAnglesCallback)
/**
 * Disables the propagation of every new advertised value to the parent hub.
 * You can use this function to save bandwidth and CPU on computers with limited
 * resources, or to prevent unwanted invocations of the HTTP callback.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Gyro_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "muteValueCallbacks";
  }

  string getDescription()
  {
    return "Disables the propagation of every new advertised value to the parent hub.";
  }

  string getMoreInfo()
  {
    return "You can use this function to save bandwidth and CPU on computers with limited resources, or to prevent unwanted invocations of the HTTP callback. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->muteValueCallbacks();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Re-enables the propagation of every new advertised value to the parent hub.
 * This function reverts the effect of a previous call to muteValueCallbacks().
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Gyro_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "unmuteValueCallbacks";
  }

  string getDescription()
  {
    return "Re-enables the propagation of every new advertised value to the parent hub.";
  }

  string getMoreInfo()
  {
    return "This function reverts the effect of a previous call to muteValueCallbacks(). Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->unmuteValueCallbacks();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the serial number of the module, as set by the factory.
 *
 * @return a string corresponding to the serial number of the module, as set by the factory.
 *
 * On failure, throws an exception or returns YModule.SERIALNUMBER_INVALID.
 */
class apifun_Gyro_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_serialNumber";
  }

  string getDescription()
  {
    return "Returns the serial number of the module, as set by the factory.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Checks if the sensor is currently able to provide an up-to-date measure.
 * Returns false if the device is unreachable, or if the sensor does not have
 * a current measure to transmit. No exception is raised if there is an error
 * while trying to contact the device hosting $THEFUNCTION$.
 *
 * @return true if the sensor can provide an up-to-date measure, and false otherwise
 */
class apifun_Gyro_isSensorReady : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_isSensorReady(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "isSensorReady";
  }

  string getDescription()
  {
    return "Checks if the sensor is currently able to provide an up-to-date measure.";
  }

  string getMoreInfo()
  {
    return "Returns false if the device is unreachable, or if the sensor does not have a current measure to transmit. No exception is raised if there is an error while trying to contact the device hosting $THEFUNCTION$.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        bool value = (*list)[i]->isSensorReady();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the data logger on the device. Note that the data logger
 * will only save the measures on this sensor if the logFrequency
 * is not set to "OFF".
 *
 * @return YAPI_SUCCESS if the call succeeds.
 */
class apifun_Gyro_startDataLogger : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_startDataLogger(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "startDataLogger";
  }

  string getDescription()
  {
    return "Starts the data logger on the device.";
  }

  string getMoreInfo()
  {
    return "Note that the data logger will only save the measures on this sensor if the logFrequency is not set to \"OFF\".";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->startDataLogger();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the datalogger on the device.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 */
class apifun_Gyro_stopDataLogger : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_stopDataLogger(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "stopDataLogger";
  }

  string getDescription()
  {
    return "Stops the datalogger on the device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->stopDataLogger();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves a DataSet object holding historical data for this
 * sensor, for a specified time interval. The measures will be
 * retrieved from the data logger, which must have been turned
 * on at the desired time. See the documentation of the DataSet
 * class for information on how to get an overview of the
 * recorded data, and how to load progressively a large set
 * of measures from the data logger.
 *
 * This function only works if the device uses a recent firmware,
 * as DataSet objects are not supported by firmwares older than
 * version 13000.
 *
 * @param startTime : the start of the desired measure time interval,
 *         as a Unix timestamp, i.e. the number of seconds since
 *         January 1, 1970 UTC. The special value 0 can be used
 *         to include any measure, without initial limit.
 * @param endTime : the end of the desired measure time interval,
 *         as a Unix timestamp, i.e. the number of seconds since
 *         January 1, 1970 UTC. The special value 0 can be used
 *         to include any measure, without ending limit.
 *
 * @return an instance of YDataSet, providing access to historical
 *         data. Past measures can be loaded progressively
 *         using methods from the YDataSet object.
 */
class apifun_Gyro_get_recordedData : public YapiCommand /* arguments: startTime endTime */
{
public:
  apifun_Gyro_get_recordedData(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_recordedData";
  }

  string getDescription()
  {
    return "Retrieves a DataSet object holding historical data for thissensor, for a specified time interval.";
  }

  string getMoreInfo()
  {
    return "The measures will be retrieved from the data logger, which must have been turned on at the desired time. See the documentation of the DataSet class for information on how to get an overview of the recorded data, and how to load progressively a large set of measures from the data logger.\nThis function only works if the device uses a recent firmware, as DataSet objects are not supported by firmwares older than version 13000.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "startTime", "the start of the desired measure time interval, as a Unix timestamp, i.e. the number of seconds since January 1, 1970 UTC. The special value 0 can be used to include any measure, without initial limit.", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "endTime", "the end of the desired measure time interval, as a Unix timestamp, i.e. the number of seconds since January 1, 1970 UTC. The special value 0 can be used to include any measure, without ending limit.", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YDataSet value = (*list)[i]->get_recordedData((*args)[0]->get_doubleValue(),
                                                      (*args)[1]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Configures error correction data points, in particular to compensate for
 * a possible perturbation of the measure caused by an enclosure. It is possible
 * to configure up to five correction points. Correction points must be provided
 * in ascending order, and be in the range of the sensor. The device will automatically
 * perform a linear interpolation of the error correction between specified
 * points. Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * For more information on advanced capabilities to refine the calibration of
 * sensors, please contact support@yoctopuce.com.
 *
 * @param rawValues : array of floating point numbers, corresponding to the raw
 *         values returned by the sensor for the correction points.
 * @param refValues : array of floating point numbers, corresponding to the corrected
 *         values for the correction points.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Gyro_calibrateFromPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:
  apifun_Gyro_calibrateFromPoints(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "calibrateFromPoints";
  }

  string getDescription()
  {
    return "Configures error correction data points, in particular to compensate fora possible perturbation of the measure caused by an enclosure.";
  }

  string getMoreInfo()
  {
    return "It is possible to configure up to five correction points. Correction points must be provided in ascending order, and be in the range of the sensor. The device will automatically perform a linear interpolation of the error correction between specified points. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.\nFor more information on advanced capabilities to refine the calibration of sensors, please contact support@yoctopuce.com.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "rawValues", "array of floating point numbers, corresponding to the raw values returned by the sensor for the correction points.", "_FLOATARR", false));
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "refValues", "array of floating point numbers, corresponding to the corrected values for the correction points.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->calibrateFromPoints((*args)[0]->get_floatArrValue(),
                                        (*args)[1]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves error correction data points previously entered using the method
 * calibrateFromPoints.
 *
 * @param rawValues : array of floating point numbers, that will be filled by the
 *         function with the raw sensor values for the correction points.
 * @param refValues : array of floating point numbers, that will be filled by the
 *         function with the desired values for the correction points.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Gyro_loadCalibrationPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:
  apifun_Gyro_loadCalibrationPoints(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "loadCalibrationPoints";
  }

  string getDescription()
  {
    return "Retrieves error correction data points previously entered using the methodcalibrateFromPoints.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        vector<double> rawValues;
        vector<double> refValues;
        (*list)[i]->loadCalibrationPoints(rawValues,
                                          refValues);
        PrintResult(resultformat, this->getName()+".rawValues",YFunctionInfoCache((*list)[i]), rawValues, true);
        PrintResult(resultformat, this->getName()+".refValues",YFunctionInfoCache((*list)[i]), refValues, true);
      }
  }
};

/**
 * Returns the estimated roll angle, based on the integration of
 * gyroscopic measures combined with acceleration and
 * magnetic field measurements.
 * The axis corresponding to the roll angle can be mapped to any
 * of the device X, Y or Z physical directions using methods of
 * the class YRefFrame.
 *
 * @return a floating-point number corresponding to roll angle
 *         in degrees, between -180 and +180.
 */
class apifun_Gyro_get_roll : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_roll(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_roll";
  }

  string getDescription()
  {
    return "Returns the estimated roll angle, based on the integration of gyroscopic measures combined with acceleration andmagnetic field measurements.";
  }

  string getMoreInfo()
  {
    return "The axis corresponding to the roll angle can be mapped to any of the device X, Y or Z physical directions using methods of the class YRefFrame.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double value = (*list)[i]->get_roll();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the estimated pitch angle, based on the integration of
 * gyroscopic measures combined with acceleration and
 * magnetic field measurements.
 * The axis corresponding to the pitch angle can be mapped to any
 * of the device X, Y or Z physical directions using methods of
 * the class YRefFrame.
 *
 * @return a floating-point number corresponding to pitch angle
 *         in degrees, between -90 and +90.
 */
class apifun_Gyro_get_pitch : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_pitch(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_pitch";
  }

  string getDescription()
  {
    return "Returns the estimated pitch angle, based on the integration of gyroscopic measures combined with acceleration andmagnetic field measurements.";
  }

  string getMoreInfo()
  {
    return "The axis corresponding to the pitch angle can be mapped to any of the device X, Y or Z physical directions using methods of the class YRefFrame.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double value = (*list)[i]->get_pitch();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the estimated heading angle, based on the integration of
 * gyroscopic measures combined with acceleration and
 * magnetic field measurements.
 * The axis corresponding to the heading can be mapped to any
 * of the device X, Y or Z physical directions using methods of
 * the class YRefFrame.
 *
 * @return a floating-point number corresponding to heading
 *         in degrees, between 0 and 360.
 */
class apifun_Gyro_get_heading : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_heading(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_heading";
  }

  string getDescription()
  {
    return "Returns the estimated heading angle, based on the integration of gyroscopic measures combined with acceleration andmagnetic field measurements.";
  }

  string getMoreInfo()
  {
    return "The axis corresponding to the heading can be mapped to any of the device X, Y or Z physical directions using methods of the class YRefFrame.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double value = (*list)[i]->get_heading();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the w component (real part) of the quaternion
 * describing the device estimated orientation, based on the
 * integration of gyroscopic measures combined with acceleration and
 * magnetic field measurements.
 *
 * @return a floating-point number corresponding to the w
 *         component of the quaternion.
 */
class apifun_Gyro_get_quaternionW : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_quaternionW(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_quaternionW";
  }

  string getDescription()
  {
    return "Returns the w component (real part) of the quaternion describing the device estimated orientation, based on the integration of gyroscopic measures combined with acceleration andmagnetic field measurements.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double value = (*list)[i]->get_quaternionW();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the x component of the quaternion
 * describing the device estimated orientation, based on the
 * integration of gyroscopic measures combined with acceleration and
 * magnetic field measurements. The x component is
 * mostly correlated with rotations on the roll axis.
 *
 * @return a floating-point number corresponding to the x
 *         component of the quaternion.
 */
class apifun_Gyro_get_quaternionX : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_quaternionX(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_quaternionX";
  }

  string getDescription()
  {
    return "Returns the x component of the quaternion describing the device estimated orientation, based on the integration of gyroscopic measures combined with acceleration andmagnetic field measurements.";
  }

  string getMoreInfo()
  {
    return "The x component is mostly correlated with rotations on the roll axis.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double value = (*list)[i]->get_quaternionX();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the y component of the quaternion
 * describing the device estimated orientation, based on the
 * integration of gyroscopic measures combined with acceleration and
 * magnetic field measurements. The y component is
 * mostly correlated with rotations on the pitch axis.
 *
 * @return a floating-point number corresponding to the y
 *         component of the quaternion.
 */
class apifun_Gyro_get_quaternionY : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_quaternionY(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_quaternionY";
  }

  string getDescription()
  {
    return "Returns the y component of the quaternion describing the device estimated orientation, based on the integration of gyroscopic measures combined with acceleration andmagnetic field measurements.";
  }

  string getMoreInfo()
  {
    return "The y component is mostly correlated with rotations on the pitch axis.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double value = (*list)[i]->get_quaternionY();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the x component of the quaternion
 * describing the device estimated orientation, based on the
 * integration of gyroscopic measures combined with acceleration and
 * magnetic field measurements. The x component is
 * mostly correlated with changes of heading.
 *
 * @return a floating-point number corresponding to the z
 *         component of the quaternion.
 */
class apifun_Gyro_get_quaternionZ : public YapiCommand /* arguments: */
{
public:
  apifun_Gyro_get_quaternionZ(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_quaternionZ";
  }

  string getDescription()
  {
    return "Returns the x component of the quaternion describing the device estimated orientation, based on the integration of gyroscopic measures combined with acceleration andmagnetic field measurements.";
  }

  string getMoreInfo()
  {
    return "The x component is mostly correlated with changes of heading.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double value = (*list)[i]->get_quaternionZ();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves any available timed report from the functions.
 *
 * @param minWait: the minimum time to wait for a timed report,
 *         or zero to wait at least up to the first timed report.
 * @param maxWait: the maximum time to wait for a timed report,
 *         or zero to wait no more than up to the first timed report.
 *
 */
class apifun_Gyro_get_timedReport : public YapiCommand /* arguments: minWait maxWait */
{
public:
  apifun_Gyro_get_timedReport(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_timedReport";
  }

  string getDescription()
  {
    return "Retrieves any available timed report from the functions.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "minWait", "the minimum time to wait for a timed report, or zero to wait at least up to the first timed report.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum time to wait for a timed report, or zero to wait no more than up to the first timed report.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->registerTimedReportCallback(cmdlineTimedReportCallback);
      }
    waitForCallbacks((*args)[0]->get_intValue(), (*args)[1]->get_intValue());
  }
};

//--- (end of generated code: YGyro implementation)

/**
 * Notify all chanhes to the position quaternion as soon as they appear
 *
 * @param minWait: the minimum time to wait for a timed report,
 *         or zero to wait at least up to the first timed report.
 * @param maxWait: the maximum time to wait for a timed report,
 *         or zero to wait no more than up to the first timed report.
 *
 */
class apifun_Gyro_get_quaternionChange : public YapiCommand { /* arguments: minWait maxWait */

public:
    apifun_Gyro_get_quaternionChange(YGyroCmdLine *function) :YapiCommand(function) {}
    string getName()
    {
        return "get_quaternionChange";
    }

    string getDescription()
    {
        return "Retrieves any change in position quaternion as soon as it appears";
    }

    vector<ArgumentDesc*>* getArgumentDesc()
    {
        vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
        res->push_back(new ArgumentDesc(INT_ARG, "minWait", "the minimum time to wait for a timed report, or zero to wait at least up to the first timed report.", "_INT", false));
        res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum time to wait for a timed report, or zero to wait no more than up to the first timed report.", "_INT", false));
        return res;
    }

    void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
    {
        vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
        unsigned int i;
        for (i = 0; i < list->size(); i++)
        {
            (*list)[i]->registerQuaternionCallback(cmdlineQuaternionCallback);
        }
        waitForCallbacks((*args)[0]->get_intValue(), (*args)[1]->get_intValue());
    }
};

/**
 * Notify all chanhes to the orientation angles as soon as they appear
 *
 * @param minWait: the minimum time to wait for a timed report,
 *         or zero to wait at least up to the first timed report.
 * @param maxWait: the maximum time to wait for a timed report,
 *         or zero to wait no more than up to the first timed report.
 *
 */
class apifun_Gyro_get_anglesChange : public YapiCommand { /* arguments: minWait maxWait */

public:
    apifun_Gyro_get_anglesChange(YGyroCmdLine *function) :YapiCommand(function) {}
    string getName()
    {
        return "get_anglesChange";
    }

    string getDescription()
    {
        return "Retrieves any change in orientation angles as soon as it appears";
    }

    vector<ArgumentDesc*>* getArgumentDesc()
    {
        vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
        res->push_back(new ArgumentDesc(INT_ARG, "minWait", "the minimum time to wait for a timed report, or zero to wait at least up to the first timed report.", "_INT", false));
        res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum time to wait for a timed report, or zero to wait no more than up to the first timed report.", "_INT", false));
        return res;
    }

    void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
    {
        vector<YGyro*>* list = enumerateTargets<YGyro>(_function, target, modulelist);
        unsigned int i;
        for (i = 0; i < list->size(); i++)
        {
            (*list)[i]->registerAnglesCallback(cmdlineAnglesCallback);
        }
        waitForCallbacks((*args)[0]->get_intValue(), (*args)[1]->get_intValue());
    }
};


//--- (generated code: YGyro functions)
void YGyroCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YGyro>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Gyro_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_unit(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_currentValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_lowestValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_lowestValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_highestValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_highestValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_currentRawValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_logFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_logFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_reportFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_reportFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_advMode(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_advMode(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_resolution(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_resolution(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_sensorState(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_bandwidth(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_set_bandwidth(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_xValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_yValue(this)));
    cmdList->push_back((YapiCommand*) (new Gyro_get_zValue(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_isSensorReady(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_startDataLogger(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_stopDataLogger(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_recordedData(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_calibrateFromPoints(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_loadCalibrationPoints(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_roll(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_pitch(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_heading(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_quaternionW(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_quaternionX(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_quaternionY(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_quaternionZ(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_timedReport(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_quaternionChange(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gyro_get_anglesChange(this)));
  }

//--- (end of generated code: YGyro functions)
