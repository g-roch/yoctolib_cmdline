/*********************************************************************
 *
 *  $Id: YTemperature.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle Temperature functions
 *
 *  - - - - - - - - - License information: - - - - - - - - -
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
#include "YTemperature.h"
#include "yocto_api.h"
#include "yocto_temperature.h"

using namespace std;

//--- (YTemperature definitions)

static const char *enumTempSensorTypeAll[] = {
    "DIGITAL",
    "TYPE_K",
    "TYPE_E",
    "TYPE_J",
    "TYPE_N",
    "TYPE_R",
    "TYPE_S",
    "TYPE_T",
    "PT100_4WIRES",
    "PT100_3WIRES",
    "PT100_2WIRES",
    "RES_OHM",
    "RES_NTC",
    "RES_LINEAR",
    "RES_INTERNAL",
    "IR",
    NULL
};

static const char *enumAdvertisingMode[] = {
    "IMMEDIATE",
    "PERIOD_AVG",
    "PERIOD_MIN",
    "PERIOD_MAX",
    NULL
};

//--- (end of YTemperature definitions)


//--- (YTemperature implementation)
bool   YTemperatureCmdLine::isModule(void)      { return false; }
string YTemperatureCmdLine::YFunctionName(void) { return "YTemperature"; }

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
// type of sensorType is int (TempSensorTypeAll)
// type of signalValue is double (MeasureVal)
// type of signalUnit is string (Text)
// type of command is string (Text)
/**
 * Returns the logical name of the temperature sensor.
 *
 * @return a string corresponding to the logical name of the temperature sensor
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Temperature_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Temperature_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the temperature sensor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
 * Changes the logical name of the temperature sensor. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the temperature sensor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Temperature_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the temperature sensor.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the temperature sensor", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the temperature sensor.
 *
 * @return a string corresponding to a short string representing the current state of the temperature sensor
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Temperature_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  Temperature_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the temperature sensor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
 * Returns the measuring unit for the temperature.
 *
 * @return a string corresponding to the measuring unit for the temperature
 *
 * On failure, throws an exception or returns Y_UNIT_INVALID.
 */
class Temperature_get_unit : public YapiCommand /* arguments: */
{
public:
  Temperature_get_unit(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_unit";
  }

  string getDescription()
  {
    return "Returns the measuring unit for the temperature.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
 * Changes the measuring unit for the measured temperature. That unit is a string.
 * If that strings end with the letter F all temperatures values will returned in
 * Fahrenheit degrees. If that String ends with the letter K all values will be
 * returned in Kelvin degrees. If that string ends with the letter C all values will be
 * returned in Celsius degrees.  If the string ends with any other character the
 * change will be ignored. Remember to call the
 * saveToFlash() method of the module if the modification must be kept.
 * WARNING: if a specific calibration is defined for the temperature function, a
 * unit system change will probably break it.
 *
 * @param newval : a string corresponding to the measuring unit for the measured temperature
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Temperature_set_unit : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_unit(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_unit";
  }

  string getDescription()
  {
    return "Changes the measuring unit for the measured temperature.";
  }

  string getMoreInfo()
  {
    return "That unit is a string. If that strings end with the letter F all temperatures values will returned in Fahrenheit degrees. If that String ends with the letter K all values will be returned in Kelvin degrees. If that string ends with the letter C all values will be returned in Celsius degrees. If the string ends with any other character the change will be ignored. Remember to call the saveToFlash() method of the module if the modification must be kept. WARNING: if a specific calibration is defined for the temperature function, a unit system change will probably break it.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the measuring unit for the measured temperature", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_unit(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current value of the temperature, in Celsius, as a floating point number.
 * Note that a get_currentValue() call will *not* start a measure in the device, it
 * will just return the last measure that occurred in the device. Indeed, internally, each Yoctopuce
 * devices is continuously making measurements at a hardware specific frequency.
 *
 * If continuously calling  get_currentValue() leads you to performances issues, then
 * you might consider to switch to callback programming model. Check the "advanced
 * programming" chapter in in your device user manual for more information.
 *
 * @return a floating point number corresponding to the current value of the temperature, in Celsius,
 * as a floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTVALUE_INVALID.
 */
class Temperature_get_currentValue : public YapiCommand /* arguments: */
{
public:
  Temperature_get_currentValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentValue";
  }

  string getDescription()
  {
    return "Returns the current value of the temperature, in Celsius, as a floating point number.";
  }

  string getMoreInfo()
  {
    return "Note that a get_currentValue() call will *not* start a measure in the device, it will just return the last measure that occurred in the device. Indeed, internally, each Yoctopuce devices is continuously making measurements at a hardware specific frequency.\nIf continuously calling get_currentValue() leads you to performances issues, then you might consider to switch to callback programming model. Check the \"advanced programming\" chapter in in your device user manual for more information.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_set_lowestValue : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_lowestValue(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_lowestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the minimal value observed for the temperature since the device was started.
 * Can be reset to an arbitrary value thanks to set_lowestValue().
 *
 * @return a floating point number corresponding to the minimal value observed for the temperature
 * since the device was started
 *
 * On failure, throws an exception or returns Y_LOWESTVALUE_INVALID.
 */
class Temperature_get_lowestValue : public YapiCommand /* arguments: */
{
public:
  Temperature_get_lowestValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_lowestValue";
  }

  string getDescription()
  {
    return "Returns the minimal value observed for the temperature since the device was started.";
  }

  string getMoreInfo()
  {
    return "Can be reset to an arbitrary value thanks to set_lowestValue().";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_set_highestValue : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_highestValue(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_highestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximal value observed for the temperature since the device was started.
 * Can be reset to an arbitrary value thanks to set_highestValue().
 *
 * @return a floating point number corresponding to the maximal value observed for the temperature
 * since the device was started
 *
 * On failure, throws an exception or returns Y_HIGHESTVALUE_INVALID.
 */
class Temperature_get_highestValue : public YapiCommand /* arguments: */
{
public:
  Temperature_get_highestValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_highestValue";
  }

  string getDescription()
  {
    return "Returns the maximal value observed for the temperature since the device was started.";
  }

  string getMoreInfo()
  {
    return "Can be reset to an arbitrary value thanks to set_highestValue().";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
 * Returns the uncalibrated, unrounded raw value returned by the sensor, in Celsius, as a floating point number.
 *
 * @return a floating point number corresponding to the uncalibrated, unrounded raw value returned by
 * the sensor, in Celsius, as a floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTRAWVALUE_INVALID.
 */
class Temperature_get_currentRawValue : public YapiCommand /* arguments: */
{
public:
  Temperature_get_currentRawValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentRawValue";
  }

  string getDescription()
  {
    return "Returns the uncalibrated, unrounded raw value returned by the sensor, in Celsius, as a floating point number.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_get_logFrequency : public YapiCommand /* arguments: */
{
public:
  Temperature_get_logFrequency(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_set_logFrequency : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_logFrequency(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_get_reportFrequency : public YapiCommand /* arguments: */
{
public:
  Temperature_get_reportFrequency(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_set_reportFrequency : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_reportFrequency(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_get_advMode : public YapiCommand /* arguments: */
{
public:
  Temperature_get_advMode(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_set_advMode : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_advMode(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_set_resolution : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_resolution(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_get_resolution : public YapiCommand /* arguments: */
{
public:
  Temperature_get_resolution(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class Temperature_get_sensorState : public YapiCommand /* arguments: */
{
public:
  Temperature_get_sensorState(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
 * Returns the temperature sensor type.
 *
 * @return a value among Y_SENSORTYPE_DIGITAL, Y_SENSORTYPE_TYPE_K, Y_SENSORTYPE_TYPE_E,
 * Y_SENSORTYPE_TYPE_J, Y_SENSORTYPE_TYPE_N, Y_SENSORTYPE_TYPE_R, Y_SENSORTYPE_TYPE_S,
 * Y_SENSORTYPE_TYPE_T, Y_SENSORTYPE_PT100_4WIRES, Y_SENSORTYPE_PT100_3WIRES,
 * Y_SENSORTYPE_PT100_2WIRES, Y_SENSORTYPE_RES_OHM, Y_SENSORTYPE_RES_NTC, Y_SENSORTYPE_RES_LINEAR,
 * Y_SENSORTYPE_RES_INTERNAL and Y_SENSORTYPE_IR corresponding to the temperature sensor type
 *
 * On failure, throws an exception or returns Y_SENSORTYPE_INVALID.
 */
class Temperature_get_sensorType : public YapiCommand /* arguments: */
{
public:
  Temperature_get_sensorType(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_sensorType";
  }

  string getDescription()
  {
    return "Returns the temperature sensor type.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_sensorType();
        string strval =  enumString(attrval,enumTempSensorTypeAll);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the temperature sensor type.  This function is used
 * to define the type of thermocouple (K,E...) used with the device.
 * It has no effect if module is using a digital sensor or a thermistor.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a value among Y_SENSORTYPE_DIGITAL, Y_SENSORTYPE_TYPE_K, Y_SENSORTYPE_TYPE_E,
 * Y_SENSORTYPE_TYPE_J, Y_SENSORTYPE_TYPE_N, Y_SENSORTYPE_TYPE_R, Y_SENSORTYPE_TYPE_S,
 * Y_SENSORTYPE_TYPE_T, Y_SENSORTYPE_PT100_4WIRES, Y_SENSORTYPE_PT100_3WIRES,
 * Y_SENSORTYPE_PT100_2WIRES, Y_SENSORTYPE_RES_OHM, Y_SENSORTYPE_RES_NTC, Y_SENSORTYPE_RES_LINEAR,
 * Y_SENSORTYPE_RES_INTERNAL and Y_SENSORTYPE_IR corresponding to the temperature sensor type
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Temperature_set_sensorType : public YapiCommand /* arguments: newval */
{
public:
  Temperature_set_sensorType(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_sensorType";
  }

  string getDescription()
  {
    return "Changes the temperature sensor type.";
  }

  string getMoreInfo()
  {
    return "This function is used to define the type of thermocouple (K,E...) used with the device. It has no effect if module is using a digital sensor or a thermistor. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among DIGITAL, TYPE_K, TYPE_E, TYPE_J, TYPE_N, TYPE_R, TYPE_S, TYPE_T, PT100_4WIRES, PT100_3WIRES, PT100_2WIRES, RES_OHM, RES_NTC, RES_LINEAR, RES_INTERNAL and IR corresponding to the temperature sensor type", "DIGITAL=0,TYPE_K=1,TYPE_E=2,TYPE_J=3,TYPE_N=4,TYPE_R=5,TYPE_S=6,TYPE_T=7,PT100_4WIRES=8,PT100_3WIRES=9,PT100_2WIRES=10,RES_OHM=11,RES_NTC=12,RES_LINEAR=13,RES_INTERNAL=14,IR=15", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_sensorType(Y_SENSORTYPE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current value of the electrical signal measured by the sensor.
 *
 * @return a floating point number corresponding to the current value of the electrical signal
 * measured by the sensor
 *
 * On failure, throws an exception or returns Y_SIGNALVALUE_INVALID.
 */
class Temperature_get_signalValue : public YapiCommand /* arguments: */
{
public:
  Temperature_get_signalValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_signalValue";
  }

  string getDescription()
  {
    return "Returns the current value of the electrical signal measured by the sensor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_signalValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the measuring unit of the electrical signal used by the sensor.
 *
 * @return a string corresponding to the measuring unit of the electrical signal used by the sensor
 *
 * On failure, throws an exception or returns Y_SIGNALUNIT_INVALID.
 */
class Temperature_get_signalUnit : public YapiCommand /* arguments: */
{
public:
  Temperature_get_signalUnit(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_signalUnit";
  }

  string getDescription()
  {
    return "Returns the measuring unit of the electrical signal used by the sensor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_signalUnit();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackTemperature is YTemperatureValueCallback* (YTemperatureValueCallback)
// type of timedReportCallbackTemperature is YTemperatureTimedReportCallback* (YTemperatureTimedReportCallback)
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
class apifun_Temperature_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Temperature_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Temperature_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_Temperature_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_isSensorReady : public YapiCommand /* arguments: */
{
public:
  apifun_Temperature_isSensorReady(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_startDataLogger : public YapiCommand /* arguments: */
{
public:
  apifun_Temperature_startDataLogger(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_stopDataLogger : public YapiCommand /* arguments: */
{
public:
  apifun_Temperature_stopDataLogger(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_get_recordedData : public YapiCommand /* arguments: startTime endTime */
{
public:
  apifun_Temperature_get_recordedData(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_calibrateFromPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:
  apifun_Temperature_calibrateFromPoints(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
class apifun_Temperature_loadCalibrationPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:
  apifun_Temperature_loadCalibrationPoints(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
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
 * Configures NTC thermistor parameters in order to properly compute the temperature from
 * the measured resistance. For increased precision, you can enter a complete mapping
 * table using set_thermistorResponseTable. This function can only be used with a
 * temperature sensor based on thermistors.
 *
 * @param res25 : thermistor resistance at 25 degrees Celsius
 * @param beta : Beta value
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Temperature_set_ntcParameters : public YapiCommand /* arguments: res25 beta */
{
public:
  apifun_Temperature_set_ntcParameters(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_ntcParameters";
  }

  string getDescription()
  {
    return "Configures NTC thermistor parameters in order to properly compute the temperature fromthe measured resistance.";
  }

  string getMoreInfo()
  {
    return "For increased precision, you can enter a complete mapping table using set_thermistorResponseTable. This function can only be used with a temperature sensor based on thermistors.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "res25", "thermistor resistance at 25 degrees Celsius", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "beta", "Beta value", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_ntcParameters((*args)[0]->get_doubleValue(),
                                      (*args)[1]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Records a thermistor response table, in order to interpolate the temperature from
 * the measured resistance. This function can only be used with a temperature
 * sensor based on thermistors.
 *
 * @param tempValues : array of floating point numbers, corresponding to all
 *         temperatures (in degrees Celsius) for which the resistance of the
 *         thermistor is specified.
 * @param resValues : array of floating point numbers, corresponding to the resistance
 *         values (in Ohms) for each of the temperature included in the first
 *         argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Temperature_set_thermistorResponseTable : public YapiCommand /* arguments: tempValues resValues */
{
public:
  apifun_Temperature_set_thermistorResponseTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_thermistorResponseTable";
  }

  string getDescription()
  {
    return "Records a thermistor response table, in order to interpolate the temperature fromthe measured resistance.";
  }

  string getMoreInfo()
  {
    return "This function can only be used with a temperature sensor based on thermistors.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "tempValues", "array of floating point numbers, corresponding to all temperatures (in degrees Celsius) for which the resistance of the thermistor is specified.", "_FLOATARR", false));
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "resValues", "array of floating point numbers, corresponding to the resistance values (in Ohms) for each of the temperature included in the first argument, index by index.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_thermistorResponseTable((*args)[0]->get_floatArrValue(),
                                                (*args)[1]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves the thermistor response table previously configured using the
 * set_thermistorResponseTable function. This function can only be used with a
 * temperature sensor based on thermistors.
 *
 * @param tempValues : array of floating point numbers, that is filled by the function
 *         with all temperatures (in degrees Celsius) for which the resistance
 *         of the thermistor is specified.
 * @param resValues : array of floating point numbers, that is filled by the function
 *         with the value (in Ohms) for each of the temperature included in the
 *         first argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Temperature_loadThermistorResponseTable : public YapiCommand /* arguments: tempValues resValues */
{
public:
  apifun_Temperature_loadThermistorResponseTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "loadThermistorResponseTable";
  }

  string getDescription()
  {
    return "Retrieves the thermistor response table previously configured using theset_thermistorResponseTable function.";
  }

  string getMoreInfo()
  {
    return "This function can only be used with a temperature sensor based on thermistors.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        vector<double> tempValues;
        vector<double> resValues;
        (*list)[i]->loadThermistorResponseTable(tempValues,
                                                resValues);
        PrintResult(resultformat, this->getName()+".tempValues",YFunctionInfoCache((*list)[i]), tempValues, true);
        PrintResult(resultformat, this->getName()+".resValues",YFunctionInfoCache((*list)[i]), resValues, true);
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
class apifun_Temperature_get_timedReport : public YapiCommand /* arguments: minWait maxWait */
{
public:
  apifun_Temperature_get_timedReport(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YTemperature*>* list = enumerateTargets<YTemperature>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->registerTimedReportCallback(cmdlineTimedReportCallback);
      }
    waitForCallbacks((*args)[0]->get_intValue(), (*args)[1]->get_intValue());
  }
};

//--- (end of YTemperature implementation)

//--- (YTemperature functions)
void YTemperatureCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YTemperature>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Temperature_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_unit(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_unit(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_currentValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_lowestValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_lowestValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_highestValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_highestValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_currentRawValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_logFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_logFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_reportFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_reportFrequency(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_advMode(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_advMode(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_resolution(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_resolution(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_sensorState(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_sensorType(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_set_sensorType(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_signalValue(this)));
    cmdList->push_back((YapiCommand*) (new Temperature_get_signalUnit(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_isSensorReady(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_startDataLogger(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_stopDataLogger(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_get_recordedData(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_calibrateFromPoints(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_loadCalibrationPoints(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_set_ntcParameters(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_set_thermistorResponseTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_loadThermistorResponseTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Temperature_get_timedReport(this)));
  }

//--- (end of YTemperature functions)
