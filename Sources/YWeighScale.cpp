/*********************************************************************
 *
 *  $Id: YWeighScale.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle WeighScale functions
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
#include "YWeighScale.h"
#include "yocto_api.h"
#include "yocto_weighscale.h"

using namespace std;

//--- (YWeighScale definitions)

static const char *enumExcitationMode[] = {
    "OFF",
    "DC",
    "AC",
    NULL
};

static const char *enumAdvertisingMode[] = {
    "IMMEDIATE",
    "PERIOD_AVG",
    "PERIOD_MIN",
    "PERIOD_MAX",
    NULL
};

//--- (end of YWeighScale definitions)


//--- (YWeighScale implementation)
bool   YWeighScaleCmdLine::isModule(void)      { return false; }
string YWeighScaleCmdLine::YFunctionName(void) { return "YWeighScale"; }

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
// type of excitation is int (ExcitationMode)
// type of tempAvgAdaptRatio is double (MeasureVal)
// type of tempChgAdaptRatio is double (MeasureVal)
// type of compTempAvg is double (MeasureVal)
// type of compTempChg is double (MeasureVal)
// type of compensation is double (MeasureVal)
// type of zeroTracking is double (MeasureVal)
// type of command is string (Text)
/**
 * Returns the logical name of the weighing scale sensor.
 *
 * @return a string corresponding to the logical name of the weighing scale sensor
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class WeighScale_get_logicalName : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the weighing scale sensor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
 * Changes the logical name of the weighing scale sensor. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the weighing scale sensor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WeighScale_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the weighing scale sensor.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the weighing scale sensor", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the weighing scale sensor.
 *
 * @return a string corresponding to a short string representing the current state of the weighing scale sensor
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class WeighScale_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the weighing scale sensor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
 * Returns the measuring unit for the measure.
 *
 * @return a string corresponding to the measuring unit for the measure
 *
 * On failure, throws an exception or returns Y_UNIT_INVALID.
 */
class WeighScale_get_unit : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_unit(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_unit";
  }

  string getDescription()
  {
    return "Returns the measuring unit for the measure.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
 * Changes the measuring unit for the weight.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the measuring unit for the weight
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WeighScale_set_unit : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_unit(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_unit";
  }

  string getDescription()
  {
    return "Changes the measuring unit for the weight.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the measuring unit for the weight", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_unit(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current value of the measure, in the specified unit, as a floating point number.
 * Note that a get_currentValue() call will *not* start a measure in the device, it
 * will just return the last measure that occurred in the device. Indeed, internally, each Yoctopuce
 * devices is continuously making measurements at a hardware specific frequency.
 *
 * If continuously calling  get_currentValue() leads you to performances issues, then
 * you might consider to switch to callback programming model. Check the "advanced
 * programming" chapter in in your device user manual for more information.
 *
 * @return a floating point number corresponding to the current value of the measure, in the specified
 * unit, as a floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTVALUE_INVALID.
 */
class WeighScale_get_currentValue : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_currentValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentValue";
  }

  string getDescription()
  {
    return "Returns the current value of the measure, in the specified unit, as a floating point number.";
  }

  string getMoreInfo()
  {
    return "Note that a get_currentValue() call will *not* start a measure in the device, it will just return the last measure that occurred in the device. Indeed, internally, each Yoctopuce devices is continuously making measurements at a hardware specific frequency.\nIf continuously calling get_currentValue() leads you to performances issues, then you might consider to switch to callback programming model. Check the \"advanced programming\" chapter in in your device user manual for more information.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_set_lowestValue : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_lowestValue(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_lowestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the minimal value observed for the measure since the device was started.
 * Can be reset to an arbitrary value thanks to set_lowestValue().
 *
 * @return a floating point number corresponding to the minimal value observed for the measure since
 * the device was started
 *
 * On failure, throws an exception or returns Y_LOWESTVALUE_INVALID.
 */
class WeighScale_get_lowestValue : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_lowestValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_lowestValue";
  }

  string getDescription()
  {
    return "Returns the minimal value observed for the measure since the device was started.";
  }

  string getMoreInfo()
  {
    return "Can be reset to an arbitrary value thanks to set_lowestValue().";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_set_highestValue : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_highestValue(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_highestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximal value observed for the measure since the device was started.
 * Can be reset to an arbitrary value thanks to set_highestValue().
 *
 * @return a floating point number corresponding to the maximal value observed for the measure since
 * the device was started
 *
 * On failure, throws an exception or returns Y_HIGHESTVALUE_INVALID.
 */
class WeighScale_get_highestValue : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_highestValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_highestValue";
  }

  string getDescription()
  {
    return "Returns the maximal value observed for the measure since the device was started.";
  }

  string getMoreInfo()
  {
    return "Can be reset to an arbitrary value thanks to set_highestValue().";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
 * Returns the uncalibrated, unrounded raw value returned by the sensor, in the specified unit, as a
 * floating point number.
 *
 * @return a floating point number corresponding to the uncalibrated, unrounded raw value returned by
 * the sensor, in the specified unit, as a floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTRAWVALUE_INVALID.
 */
class WeighScale_get_currentRawValue : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_currentRawValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentRawValue";
  }

  string getDescription()
  {
    return "Returns the uncalibrated, unrounded raw value returned by the sensor, in the specified unit, as a floating point number.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_get_logFrequency : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_logFrequency(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_set_logFrequency : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_logFrequency(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_get_reportFrequency : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_reportFrequency(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_set_reportFrequency : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_reportFrequency(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_get_advMode : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_advMode(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_set_advMode : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_advMode(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_set_resolution : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_resolution(YFunctionCmdLine *function):YapiCommand(function){}
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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_get_resolution : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_resolution(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class WeighScale_get_sensorState : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_sensorState(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
 * Returns the current load cell bridge excitation method.
 *
 * @return a value among Y_EXCITATION_OFF, Y_EXCITATION_DC and Y_EXCITATION_AC corresponding to the
 * current load cell bridge excitation method
 *
 * On failure, throws an exception or returns Y_EXCITATION_INVALID.
 */
class WeighScale_get_excitation : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_excitation(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_excitation";
  }

  string getDescription()
  {
    return "Returns the current load cell bridge excitation method.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_excitation();
        string strval =  enumString(attrval,enumExcitationMode);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current load cell bridge excitation method.
 *
 * @param newval : a value among Y_EXCITATION_OFF, Y_EXCITATION_DC and Y_EXCITATION_AC corresponding
 * to the current load cell bridge excitation method
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WeighScale_set_excitation : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_excitation(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_excitation";
  }

  string getDescription()
  {
    return "Changes the current load cell bridge excitation method.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among OFF, DC and AC corresponding to the current load cell bridge excitation method", "OFF=0,DC=1,AC=2", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_excitation(Y_EXCITATION_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Changes the averaged temperature update rate, in per mille.
 * The purpose of this adaptation ratio is to model the thermal inertia of the load cell.
 * The averaged temperature is updated every 10 seconds, by applying this adaptation rate
 * to the difference between the measures ambient temperature and the current compensation
 * temperature. The standard rate is 0.2 per mille, and the maximal rate is 65 per mille.
 *
 * @param newval : a floating point number corresponding to the averaged temperature update rate, in per mille
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WeighScale_set_tempAvgAdaptRatio : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_tempAvgAdaptRatio(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_tempAvgAdaptRatio";
  }

  string getDescription()
  {
    return "Changes the averaged temperature update rate, in per mille.";
  }

  string getMoreInfo()
  {
    return "The purpose of this adaptation ratio is to model the thermal inertia of the load cell. The averaged temperature is updated every 10 seconds, by applying this adaptation rate to the difference between the measures ambient temperature and the current compensation temperature. The standard rate is 0.2 per mille, and the maximal rate is 65 per mille.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the averaged temperature update rate, in per mille", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_tempAvgAdaptRatio(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the averaged temperature update rate, in per mille.
 * The purpose of this adaptation ratio is to model the thermal inertia of the load cell.
 * The averaged temperature is updated every 10 seconds, by applying this adaptation rate
 * to the difference between the measures ambient temperature and the current compensation
 * temperature. The standard rate is 0.2 per mille, and the maximal rate is 65 per mille.
 *
 * @return a floating point number corresponding to the averaged temperature update rate, in per mille
 *
 * On failure, throws an exception or returns Y_TEMPAVGADAPTRATIO_INVALID.
 */
class WeighScale_get_tempAvgAdaptRatio : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_tempAvgAdaptRatio(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_tempAvgAdaptRatio";
  }

  string getDescription()
  {
    return "Returns the averaged temperature update rate, in per mille.";
  }

  string getMoreInfo()
  {
    return "The purpose of this adaptation ratio is to model the thermal inertia of the load cell. The averaged temperature is updated every 10 seconds, by applying this adaptation rate to the difference between the measures ambient temperature and the current compensation temperature. The standard rate is 0.2 per mille, and the maximal rate is 65 per mille.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_tempAvgAdaptRatio();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the temperature change update rate, in per mille.
 * The temperature change is updated every 10 seconds, by applying this adaptation rate
 * to the difference between the measures ambient temperature and the current temperature used for
 * change compensation. The standard rate is 0.6 per mille, and the maximal rate is 65 pour mille.
 *
 * @param newval : a floating point number corresponding to the temperature change update rate, in per mille
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WeighScale_set_tempChgAdaptRatio : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_tempChgAdaptRatio(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_tempChgAdaptRatio";
  }

  string getDescription()
  {
    return "Changes the temperature change update rate, in per mille.";
  }

  string getMoreInfo()
  {
    return "The temperature change is updated every 10 seconds, by applying this adaptation rate to the difference between the measures ambient temperature and the current temperature used for change compensation. The standard rate is 0.6 per mille, and the maximal rate is 65 pour mille.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the temperature change update rate, in per mille", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_tempChgAdaptRatio(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the temperature change update rate, in per mille.
 * The temperature change is updated every 10 seconds, by applying this adaptation rate
 * to the difference between the measures ambient temperature and the current temperature used for
 * change compensation. The standard rate is 0.6 per mille, and the maximal rate is 65 pour mille.
 *
 * @return a floating point number corresponding to the temperature change update rate, in per mille
 *
 * On failure, throws an exception or returns Y_TEMPCHGADAPTRATIO_INVALID.
 */
class WeighScale_get_tempChgAdaptRatio : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_tempChgAdaptRatio(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_tempChgAdaptRatio";
  }

  string getDescription()
  {
    return "Returns the temperature change update rate, in per mille.";
  }

  string getMoreInfo()
  {
    return "The temperature change is updated every 10 seconds, by applying this adaptation rate to the difference between the measures ambient temperature and the current temperature used for change compensation. The standard rate is 0.6 per mille, and the maximal rate is 65 pour mille.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_tempChgAdaptRatio();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current averaged temperature, used for thermal compensation.
 *
 * @return a floating point number corresponding to the current averaged temperature, used for thermal compensation
 *
 * On failure, throws an exception or returns Y_COMPTEMPAVG_INVALID.
 */
class WeighScale_get_compTempAvg : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_compTempAvg(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_compTempAvg";
  }

  string getDescription()
  {
    return "Returns the current averaged temperature, used for thermal compensation.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_compTempAvg();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current temperature variation, used for thermal compensation.
 *
 * @return a floating point number corresponding to the current temperature variation, used for
 * thermal compensation
 *
 * On failure, throws an exception or returns Y_COMPTEMPCHG_INVALID.
 */
class WeighScale_get_compTempChg : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_compTempChg(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_compTempChg";
  }

  string getDescription()
  {
    return "Returns the current temperature variation, used for thermal compensation.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_compTempChg();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current current thermal compensation value.
 *
 * @return a floating point number corresponding to the current current thermal compensation value
 *
 * On failure, throws an exception or returns Y_COMPENSATION_INVALID.
 */
class WeighScale_get_compensation : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_compensation(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_compensation";
  }

  string getDescription()
  {
    return "Returns the current current thermal compensation value.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_compensation();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the zero tracking threshold value. When this threshold is larger than
 * zero, any measure under the threshold will automatically be ignored and the
 * zero compensation will be updated.
 *
 * @param newval : a floating point number corresponding to the zero tracking threshold value
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WeighScale_set_zeroTracking : public YapiCommand /* arguments: newval */
{
public:
  WeighScale_set_zeroTracking(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_zeroTracking";
  }

  string getDescription()
  {
    return "Changes the zero tracking threshold value.";
  }

  string getMoreInfo()
  {
    return "When this threshold is larger than zero, any measure under the threshold will automatically be ignored and the zero compensation will be updated.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the zero tracking threshold value", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_zeroTracking(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the zero tracking threshold value. When this threshold is larger than
 * zero, any measure under the threshold will automatically be ignored and the
 * zero compensation will be updated.
 *
 * @return a floating point number corresponding to the zero tracking threshold value
 *
 * On failure, throws an exception or returns Y_ZEROTRACKING_INVALID.
 */
class WeighScale_get_zeroTracking : public YapiCommand /* arguments: */
{
public:
  WeighScale_get_zeroTracking(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_zeroTracking";
  }

  string getDescription()
  {
    return "Returns the zero tracking threshold value.";
  }

  string getMoreInfo()
  {
    return "When this threshold is larger than zero, any measure under the threshold will automatically be ignored and the zero compensation will be updated.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_zeroTracking();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackWeighScale is YWeighScaleValueCallback* (YWeighScaleValueCallback)
// type of timedReportCallbackWeighScale is YWeighScaleTimedReportCallback* (YWeighScaleTimedReportCallback)
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
class apifun_WeighScale_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_WeighScale_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_WeighScale_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_WeighScale_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_isSensorReady : public YapiCommand /* arguments: */
{
public:
  apifun_WeighScale_isSensorReady(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_startDataLogger : public YapiCommand /* arguments: */
{
public:
  apifun_WeighScale_startDataLogger(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_stopDataLogger : public YapiCommand /* arguments: */
{
public:
  apifun_WeighScale_stopDataLogger(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_get_recordedData : public YapiCommand /* arguments: startTime endTime */
{
public:
  apifun_WeighScale_get_recordedData(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_calibrateFromPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:
  apifun_WeighScale_calibrateFromPoints(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
class apifun_WeighScale_loadCalibrationPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:
  apifun_WeighScale_loadCalibrationPoints(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
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
 * Adapts the load cell signal bias (stored in the corresponding genericSensor)
 * so that the current signal corresponds to a zero weight.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_tare : public YapiCommand /* arguments: */
{
public:
  apifun_WeighScale_tare(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "tare";
  }

  string getDescription()
  {
    return "Adapts the load cell signal bias (stored in the corresponding genericSensor)so that the current signal corresponds to a zero weight.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->tare();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Configures the load cell span parameters (stored in the corresponding genericSensor)
 * so that the current signal corresponds to the specified reference weight.
 *
 * @param currWeight : reference weight presently on the load cell.
 * @param maxWeight : maximum weight to be expected on the load cell.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_setupSpan : public YapiCommand /* arguments: currWeight maxWeight */
{
public:
  apifun_WeighScale_setupSpan(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "setupSpan";
  }

  string getDescription()
  {
    return "Configures the load cell span parameters (stored in the corresponding genericSensor)so that the current signal corresponds to the specified reference weight.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "currWeight", "reference weight presently on the load cell.", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "maxWeight", "maximum weight to be expected on the load cell.", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->setupSpan((*args)[0]->get_doubleValue(),
                              (*args)[1]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Records a weight offset thermal compensation table, in order to automatically correct the
 * measured weight based on the averaged compensation temperature.
 * The weight correction will be applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, corresponding to all averaged
 *         temperatures for which an offset correction is specified.
 * @param compValues : array of floating point numbers, corresponding to the offset correction
 *         to apply for each of the temperature included in the first
 *         argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_set_offsetAvgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_set_offsetAvgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_offsetAvgCompensationTable";
  }

  string getDescription()
  {
    return "Records a weight offset thermal compensation table, in order to automatically correct themeasured weight based on the averaged compensation temperature.";
  }

  string getMoreInfo()
  {
    return "The weight correction will be applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "tempValues", "array of floating point numbers, corresponding to all averaged temperatures for which an offset correction is specified.", "_FLOATARR", false));
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "compValues", "array of floating point numbers, corresponding to the offset correction to apply for each of the temperature included in the first argument, index by index.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_offsetAvgCompensationTable((*args)[0]->get_floatArrValue(),
                                                   (*args)[1]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves the weight offset thermal compensation table previously configured using the
 * set_offsetAvgCompensationTable function.
 * The weight correction is applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, that is filled by the function
 *         with all averaged temperatures for which an offset correction is specified.
 * @param compValues : array of floating point numbers, that is filled by the function
 *         with the offset correction applied for each of the temperature
 *         included in the first argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_loadOffsetAvgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_loadOffsetAvgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "loadOffsetAvgCompensationTable";
  }

  string getDescription()
  {
    return "Retrieves the weight offset thermal compensation table previously configured using theset_offsetAvgCompensationTable function.";
  }

  string getMoreInfo()
  {
    return "The weight correction is applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        vector<double> tempValues;
        vector<double> compValues;
        (*list)[i]->loadOffsetAvgCompensationTable(tempValues,
                                                   compValues);
        PrintResult(resultformat, this->getName()+".tempValues",YFunctionInfoCache((*list)[i]), tempValues, true);
        PrintResult(resultformat, this->getName()+".compValues",YFunctionInfoCache((*list)[i]), compValues, true);
      }
  }
};

/**
 * Records a weight offset thermal compensation table, in order to automatically correct the
 * measured weight based on the variation of temperature.
 * The weight correction will be applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, corresponding to temperature
 *         variations for which an offset correction is specified.
 * @param compValues : array of floating point numbers, corresponding to the offset correction
 *         to apply for each of the temperature variation included in the first
 *         argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_set_offsetChgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_set_offsetChgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_offsetChgCompensationTable";
  }

  string getDescription()
  {
    return "Records a weight offset thermal compensation table, in order to automatically correct themeasured weight based on the variation of temperature.";
  }

  string getMoreInfo()
  {
    return "The weight correction will be applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "tempValues", "array of floating point numbers, corresponding to temperature variations for which an offset correction is specified.", "_FLOATARR", false));
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "compValues", "array of floating point numbers, corresponding to the offset correction to apply for each of the temperature variation included in the first argument, index by index.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_offsetChgCompensationTable((*args)[0]->get_floatArrValue(),
                                                   (*args)[1]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves the weight offset thermal compensation table previously configured using the
 * set_offsetChgCompensationTable function.
 * The weight correction is applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, that is filled by the function
 *         with all temperature variations for which an offset correction is specified.
 * @param compValues : array of floating point numbers, that is filled by the function
 *         with the offset correction applied for each of the temperature
 *         variation included in the first argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_loadOffsetChgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_loadOffsetChgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "loadOffsetChgCompensationTable";
  }

  string getDescription()
  {
    return "Retrieves the weight offset thermal compensation table previously configured using theset_offsetChgCompensationTable function.";
  }

  string getMoreInfo()
  {
    return "The weight correction is applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        vector<double> tempValues;
        vector<double> compValues;
        (*list)[i]->loadOffsetChgCompensationTable(tempValues,
                                                   compValues);
        PrintResult(resultformat, this->getName()+".tempValues",YFunctionInfoCache((*list)[i]), tempValues, true);
        PrintResult(resultformat, this->getName()+".compValues",YFunctionInfoCache((*list)[i]), compValues, true);
      }
  }
};

/**
 * Records a weight span thermal compensation table, in order to automatically correct the
 * measured weight based on the compensation temperature.
 * The weight correction will be applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, corresponding to all averaged
 *         temperatures for which a span correction is specified.
 * @param compValues : array of floating point numbers, corresponding to the span correction
 *         (in percents) to apply for each of the temperature included in the first
 *         argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_set_spanAvgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_set_spanAvgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_spanAvgCompensationTable";
  }

  string getDescription()
  {
    return "Records a weight span thermal compensation table, in order to automatically correct themeasured weight based on the compensation temperature.";
  }

  string getMoreInfo()
  {
    return "The weight correction will be applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "tempValues", "array of floating point numbers, corresponding to all averaged temperatures for which a span correction is specified.", "_FLOATARR", false));
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "compValues", "array of floating point numbers, corresponding to the span correction (in percents) to apply for each of the temperature included in the first argument, index by index.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_spanAvgCompensationTable((*args)[0]->get_floatArrValue(),
                                                 (*args)[1]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves the weight span thermal compensation table previously configured using the
 * set_spanAvgCompensationTable function.
 * The weight correction is applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, that is filled by the function
 *         with all averaged temperatures for which an span correction is specified.
 * @param compValues : array of floating point numbers, that is filled by the function
 *         with the span correction applied for each of the temperature
 *         included in the first argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_loadSpanAvgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_loadSpanAvgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "loadSpanAvgCompensationTable";
  }

  string getDescription()
  {
    return "Retrieves the weight span thermal compensation table previously configured using theset_spanAvgCompensationTable function.";
  }

  string getMoreInfo()
  {
    return "The weight correction is applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        vector<double> tempValues;
        vector<double> compValues;
        (*list)[i]->loadSpanAvgCompensationTable(tempValues,
                                                 compValues);
        PrintResult(resultformat, this->getName()+".tempValues",YFunctionInfoCache((*list)[i]), tempValues, true);
        PrintResult(resultformat, this->getName()+".compValues",YFunctionInfoCache((*list)[i]), compValues, true);
      }
  }
};

/**
 * Records a weight span thermal compensation table, in order to automatically correct the
 * measured weight based on the variation of temperature.
 * The weight correction will be applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, corresponding to all variations of
 *         temperatures for which a span correction is specified.
 * @param compValues : array of floating point numbers, corresponding to the span correction
 *         (in percents) to apply for each of the temperature variation included
 *         in the first argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_set_spanChgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_set_spanChgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_spanChgCompensationTable";
  }

  string getDescription()
  {
    return "Records a weight span thermal compensation table, in order to automatically correct themeasured weight based on the variation of temperature.";
  }

  string getMoreInfo()
  {
    return "The weight correction will be applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "tempValues", "array of floating point numbers, corresponding to all variations of temperatures for which a span correction is specified.", "_FLOATARR", false));
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "compValues", "array of floating point numbers, corresponding to the span correction (in percents) to apply for each of the temperature variation included in the first argument, index by index.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_spanChgCompensationTable((*args)[0]->get_floatArrValue(),
                                                 (*args)[1]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves the weight span thermal compensation table previously configured using the
 * set_spanChgCompensationTable function.
 * The weight correction is applied by linear interpolation between specified points.
 *
 * @param tempValues : array of floating point numbers, that is filled by the function
 *         with all variation of temperature for which an span correction is specified.
 * @param compValues : array of floating point numbers, that is filled by the function
 *         with the span correction applied for each of variation of temperature
 *         included in the first argument, index by index.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WeighScale_loadSpanChgCompensationTable : public YapiCommand /* arguments: tempValues compValues */
{
public:
  apifun_WeighScale_loadSpanChgCompensationTable(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "loadSpanChgCompensationTable";
  }

  string getDescription()
  {
    return "Retrieves the weight span thermal compensation table previously configured using theset_spanChgCompensationTable function.";
  }

  string getMoreInfo()
  {
    return "The weight correction is applied by linear interpolation between specified points.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        vector<double> tempValues;
        vector<double> compValues;
        (*list)[i]->loadSpanChgCompensationTable(tempValues,
                                                 compValues);
        PrintResult(resultformat, this->getName()+".tempValues",YFunctionInfoCache((*list)[i]), tempValues, true);
        PrintResult(resultformat, this->getName()+".compValues",YFunctionInfoCache((*list)[i]), compValues, true);
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
class apifun_WeighScale_get_timedReport : public YapiCommand /* arguments: minWait maxWait */
{
public:
  apifun_WeighScale_get_timedReport(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWeighScale*>* list = enumerateTargets<YWeighScale>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->registerTimedReportCallback(cmdlineTimedReportCallback);
      }
    waitForCallbacks((*args)[0]->get_intValue(), (*args)[1]->get_intValue());
  }
};

//--- (end of YWeighScale implementation)

//--- (YWeighScale functions)
void YWeighScaleCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YWeighScale>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new WeighScale_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_unit(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_unit(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_currentValue(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_lowestValue(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_lowestValue(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_highestValue(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_highestValue(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_currentRawValue(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_logFrequency(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_logFrequency(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_reportFrequency(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_reportFrequency(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_advMode(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_advMode(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_resolution(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_resolution(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_sensorState(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_excitation(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_excitation(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_tempAvgAdaptRatio(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_tempAvgAdaptRatio(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_tempChgAdaptRatio(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_tempChgAdaptRatio(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_compTempAvg(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_compTempChg(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_compensation(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_set_zeroTracking(this)));
    cmdList->push_back((YapiCommand*) (new WeighScale_get_zeroTracking(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_isSensorReady(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_startDataLogger(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_stopDataLogger(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_get_recordedData(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_calibrateFromPoints(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_loadCalibrationPoints(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_tare(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_setupSpan(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_set_offsetAvgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_loadOffsetAvgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_set_offsetChgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_loadOffsetChgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_set_spanAvgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_loadSpanAvgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_set_spanChgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_loadSpanChgCompensationTable(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WeighScale_get_timedReport(this)));
  }

//--- (end of YWeighScale functions)
