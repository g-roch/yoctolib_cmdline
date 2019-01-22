/*********************************************************************
 *
 *  $Id: YPowerSupply.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle PowerSupply functions
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
#include "YPowerSupply.h"
#include "yocto_api.h"
#include "yocto_powersupply.h"

using namespace std;

//--- (YPowerSupply definitions)

static const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

static const char *enumVoltageSense[] = {
    "INT",
    "EXT",
    NULL
};

//--- (end of YPowerSupply definitions)


//--- (YPowerSupply implementation)
bool   YPowerSupplyCmdLine::isModule(void)      { return false; }
string YPowerSupplyCmdLine::YFunctionName(void) { return "YPowerSupply"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of voltageSetPoint is double (MeasureVal)
// type of currentLimit is double (MeasureVal)
// type of powerOutput is int (OnOff)
// type of voltageSense is int (VoltageSense)
// type of measuredVoltage is double (MeasureVal)
// type of measuredCurrent is double (MeasureVal)
// type of inputVoltage is double (MeasureVal)
// type of vInt is double (MeasureVal)
// type of ldoTemperature is double (MeasureVal)
// type of voltageTransition is string (AnyFloatTransition)
// type of voltageAtStartUp is double (MeasureVal)
// type of currentAtStartUp is double (MeasureVal)
// type of command is string (Text)
/**
 * Returns the logical name of the regulated power supply.
 *
 * @return a string corresponding to the logical name of the regulated power supply
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class PowerSupply_get_logicalName : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the regulated power supply.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
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
 * Changes the logical name of the regulated power supply. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the regulated power supply
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerSupply_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  PowerSupply_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the regulated power supply.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the regulated power supply", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the regulated power supply.
 *
 * @return a string corresponding to a short string representing the current state of the regulated power supply
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class PowerSupply_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the regulated power supply.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
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
 * Changes the voltage set point, in V.
 *
 * @param newval : a floating point number corresponding to the voltage set point, in V
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerSupply_set_voltageSetPoint : public YapiCommand /* arguments: newval */
{
public:
  PowerSupply_set_voltageSetPoint(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_voltageSetPoint";
  }

  string getDescription()
  {
    return "Changes the voltage set point, in V.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the voltage set point, in V", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_voltageSetPoint(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the voltage set point, in V.
 *
 * @return a floating point number corresponding to the voltage set point, in V
 *
 * On failure, throws an exception or returns Y_VOLTAGESETPOINT_INVALID.
 */
class PowerSupply_get_voltageSetPoint : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_voltageSetPoint(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_voltageSetPoint";
  }

  string getDescription()
  {
    return "Returns the voltage set point, in V.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_voltageSetPoint();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current limit, in mA.
 *
 * @param newval : a floating point number corresponding to the current limit, in mA
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerSupply_set_currentLimit : public YapiCommand /* arguments: newval */
{
public:
  PowerSupply_set_currentLimit(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_currentLimit";
  }

  string getDescription()
  {
    return "Changes the current limit, in mA.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the current limit, in mA", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_currentLimit(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current limit, in mA.
 *
 * @return a floating point number corresponding to the current limit, in mA
 *
 * On failure, throws an exception or returns Y_CURRENTLIMIT_INVALID.
 */
class PowerSupply_get_currentLimit : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_currentLimit(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentLimit";
  }

  string getDescription()
  {
    return "Returns the current limit, in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentLimit();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the power supply output switch state.
 *
 * @return either Y_POWEROUTPUT_OFF or Y_POWEROUTPUT_ON, according to the power supply output switch state
 *
 * On failure, throws an exception or returns Y_POWEROUTPUT_INVALID.
 */
class PowerSupply_get_powerOutput : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_powerOutput(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_powerOutput";
  }

  string getDescription()
  {
    return "Returns the power supply output switch state.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_powerOutput();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the power supply output switch state.
 *
 * @param newval : either Y_POWEROUTPUT_OFF or Y_POWEROUTPUT_ON, according to the power supply output switch state
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerSupply_set_powerOutput : public YapiCommand /* arguments: newval */
{
public:
  PowerSupply_set_powerOutput(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_powerOutput";
  }

  string getDescription()
  {
    return "Changes the power supply output switch state.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON, according to the power supply output switch state", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_powerOutput(Y_POWEROUTPUT_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the output voltage control point.
 *
 * @return either Y_VOLTAGESENSE_INT or Y_VOLTAGESENSE_EXT, according to the output voltage control point
 *
 * On failure, throws an exception or returns Y_VOLTAGESENSE_INVALID.
 */
class PowerSupply_get_voltageSense : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_voltageSense(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_voltageSense";
  }

  string getDescription()
  {
    return "Returns the output voltage control point.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_voltageSense();
        string strval =  enumString(attrval,enumVoltageSense);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the voltage control point.
 *
 * @param newval : either Y_VOLTAGESENSE_INT or Y_VOLTAGESENSE_EXT, according to the voltage control point
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerSupply_set_voltageSense : public YapiCommand /* arguments: newval */
{
public:
  PowerSupply_set_voltageSense(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_voltageSense";
  }

  string getDescription()
  {
    return "Changes the voltage control point.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either INT or EXT, according to the voltage control point", "INT=0,EXT=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_voltageSense(Y_VOLTAGESENSE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the measured output voltage, in V.
 *
 * @return a floating point number corresponding to the measured output voltage, in V
 *
 * On failure, throws an exception or returns Y_MEASUREDVOLTAGE_INVALID.
 */
class PowerSupply_get_measuredVoltage : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_measuredVoltage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_measuredVoltage";
  }

  string getDescription()
  {
    return "Returns the measured output voltage, in V.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_measuredVoltage();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the measured output current, in mA.
 *
 * @return a floating point number corresponding to the measured output current, in mA
 *
 * On failure, throws an exception or returns Y_MEASUREDCURRENT_INVALID.
 */
class PowerSupply_get_measuredCurrent : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_measuredCurrent(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_measuredCurrent";
  }

  string getDescription()
  {
    return "Returns the measured output current, in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_measuredCurrent();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the measured input voltage, in V.
 *
 * @return a floating point number corresponding to the measured input voltage, in V
 *
 * On failure, throws an exception or returns Y_INPUTVOLTAGE_INVALID.
 */
class PowerSupply_get_inputVoltage : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_inputVoltage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_inputVoltage";
  }

  string getDescription()
  {
    return "Returns the measured input voltage, in V.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_inputVoltage();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the internal voltage, in V.
 *
 * @return a floating point number corresponding to the internal voltage, in V
 *
 * On failure, throws an exception or returns Y_VINT_INVALID.
 */
class PowerSupply_get_vInt : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_vInt(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_vInt";
  }

  string getDescription()
  {
    return "Returns the internal voltage, in V.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_vInt();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the LDO temperature, in Celsius.
 *
 * @return a floating point number corresponding to the LDO temperature, in Celsius
 *
 * On failure, throws an exception or returns Y_LDOTEMPERATURE_INVALID.
 */
class PowerSupply_get_ldoTemperature : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_ldoTemperature(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_ldoTemperature";
  }

  string getDescription()
  {
    return "Returns the LDO temperature, in Celsius.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_ldoTemperature();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the voltage set point at device start up. Remember to call the matching
 * module saveToFlash() method, otherwise this call has no effect.
 *
 * @param newval : a floating point number corresponding to the voltage set point at device start up
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerSupply_set_voltageAtStartUp : public YapiCommand /* arguments: newval */
{
public:
  PowerSupply_set_voltageAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_voltageAtStartUp";
  }

  string getDescription()
  {
    return "Changes the voltage set point at device start up.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call has no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the voltage set point at device start up", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_voltageAtStartUp(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the selected voltage set point at device startup, in V.
 *
 * @return a floating point number corresponding to the selected voltage set point at device startup, in V
 *
 * On failure, throws an exception or returns Y_VOLTAGEATSTARTUP_INVALID.
 */
class PowerSupply_get_voltageAtStartUp : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_voltageAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_voltageAtStartUp";
  }

  string getDescription()
  {
    return "Returns the selected voltage set point at device startup, in V.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_voltageAtStartUp();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current limit at device start up. Remember to call the matching
 * module saveToFlash() method, otherwise this call has no effect.
 *
 * @param newval : a floating point number corresponding to the current limit at device start up
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerSupply_set_currentAtStartUp : public YapiCommand /* arguments: newval */
{
public:
  PowerSupply_set_currentAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_currentAtStartUp";
  }

  string getDescription()
  {
    return "Changes the current limit at device start up.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call has no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the current limit at device start up", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_currentAtStartUp(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the selected current limit at device startup, in mA.
 *
 * @return a floating point number corresponding to the selected current limit at device startup, in mA
 *
 * On failure, throws an exception or returns Y_CURRENTATSTARTUP_INVALID.
 */
class PowerSupply_get_currentAtStartUp : public YapiCommand /* arguments: */
{
public:
  PowerSupply_get_currentAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentAtStartUp";
  }

  string getDescription()
  {
    return "Returns the selected current limit at device startup, in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentAtStartUp();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackPowerSupply is YPowerSupplyValueCallback* (YPowerSupplyValueCallback)
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
class apifun_PowerSupply_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_PowerSupply_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
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
class apifun_PowerSupply_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_PowerSupply_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
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
class apifun_PowerSupply_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_PowerSupply_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Performs a smooth transistion of output voltage. Any explicit voltage
 * change cancels any ongoing transition process.
 *
 * @param V_target   : new output voltage value at the end of the transition
 *         (floating-point number, representing the end voltage in V)
 * @param ms_duration : total duration of the transition, in milliseconds
 *
 * @return YAPI_SUCCESS when the call succeeds.
 */
class apifun_PowerSupply_voltageMove : public YapiCommand /* arguments: V_target ms_duration */
{
public:
  apifun_PowerSupply_voltageMove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "voltageMove";
  }

  string getDescription()
  {
    return "Performs a smooth transistion of output voltage.";
  }

  string getMoreInfo()
  {
    return "Any explicit voltage change cancels any ongoing transition process.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "V_target", "new output voltage value at the end of the transition (floating-point number, representing the end voltage in V)", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "total duration of the transition, in milliseconds", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YPowerSupply*>* list = enumerateTargets<YPowerSupply>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->voltageMove((*args)[0]->get_doubleValue(),
                                (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YPowerSupply implementation)

//--- (YPowerSupply functions)
void YPowerSupplyCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YPowerSupply>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_set_voltageSetPoint(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_voltageSetPoint(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_set_currentLimit(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_currentLimit(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_powerOutput(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_set_powerOutput(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_voltageSense(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_set_voltageSense(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_measuredVoltage(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_measuredCurrent(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_inputVoltage(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_vInt(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_ldoTemperature(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_set_voltageAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_voltageAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_set_currentAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new PowerSupply_get_currentAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new apifun_PowerSupply_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_PowerSupply_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_PowerSupply_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_PowerSupply_voltageMove(this)));
  }

//--- (end of YPowerSupply functions)
