/*********************************************************************
 *
 *  $Id: YVoltageOutput.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle VoltageOutput functions
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
#include "YVoltageOutput.h"
#include "yocto_api.h"
#include "yocto_voltageoutput.h"

using namespace std;

//--- (YVoltageOutput definitions)

//--- (end of YVoltageOutput definitions)


//--- (YVoltageOutput implementation)
bool   YVoltageOutputCmdLine::isModule(void)      { return false; }
string YVoltageOutputCmdLine::YFunctionName(void) { return "YVoltageOutput"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of currentVoltage is double (MeasureVal)
// type of voltageTransition is string (AnyFloatTransition)
// type of voltageAtStartUp is double (MeasureVal)
/**
 * Returns the logical name of the voltage output.
 *
 * @return a string corresponding to the logical name of the voltage output
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class VoltageOutput_get_logicalName : public YapiCommand /* arguments: */
{
public:
  VoltageOutput_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the voltage output.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
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
 * Changes the logical name of the voltage output. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the voltage output
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class VoltageOutput_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  VoltageOutput_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the voltage output.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the voltage output", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the voltage output.
 *
 * @return a string corresponding to a short string representing the current state of the voltage output
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class VoltageOutput_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  VoltageOutput_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the voltage output.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
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
 * Changes the output voltage, in V. Valid range is from 0 to 10V.
 *
 * @param newval : a floating point number corresponding to the output voltage, in V
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class VoltageOutput_set_currentVoltage : public YapiCommand /* arguments: newval */
{
public:
  VoltageOutput_set_currentVoltage(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_currentVoltage";
  }

  string getDescription()
  {
    return "Changes the output voltage, in V.";
  }

  string getMoreInfo()
  {
    return "Valid range is from 0 to 10V.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the output voltage, in V", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_currentVoltage(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the output voltage set point, in V.
 *
 * @return a floating point number corresponding to the output voltage set point, in V
 *
 * On failure, throws an exception or returns Y_CURRENTVOLTAGE_INVALID.
 */
class VoltageOutput_get_currentVoltage : public YapiCommand /* arguments: */
{
public:
  VoltageOutput_get_currentVoltage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentVoltage";
  }

  string getDescription()
  {
    return "Returns the output voltage set point, in V.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentVoltage();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the output voltage at device start up. Remember to call the matching
 * module saveToFlash() method, otherwise this call has no effect.
 *
 * @param newval : a floating point number corresponding to the output voltage at device start up
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class VoltageOutput_set_voltageAtStartUp : public YapiCommand /* arguments: newval */
{
public:
  VoltageOutput_set_voltageAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_voltageAtStartUp";
  }

  string getDescription()
  {
    return "Changes the output voltage at device start up.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call has no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the output voltage at device start up", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_voltageAtStartUp(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the selected voltage output at device startup, in V.
 *
 * @return a floating point number corresponding to the selected voltage output at device startup, in V
 *
 * On failure, throws an exception or returns Y_VOLTAGEATSTARTUP_INVALID.
 */
class VoltageOutput_get_voltageAtStartUp : public YapiCommand /* arguments: */
{
public:
  VoltageOutput_get_voltageAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_voltageAtStartUp";
  }

  string getDescription()
  {
    return "Returns the selected voltage output at device startup, in V.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_voltageAtStartUp();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackVoltageOutput is YVoltageOutputValueCallback* (YVoltageOutputValueCallback)
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
class apifun_VoltageOutput_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_VoltageOutput_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
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
class apifun_VoltageOutput_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_VoltageOutput_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
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
class apifun_VoltageOutput_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_VoltageOutput_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Performs a smooth transition of output voltage. Any explicit voltage
 * change cancels any ongoing transition process.
 *
 * @param V_target   : new output voltage value at the end of the transition
 *         (floating-point number, representing the end voltage in V)
 * @param ms_duration : total duration of the transition, in milliseconds
 *
 * @return YAPI_SUCCESS when the call succeeds.
 */
class apifun_VoltageOutput_voltageMove : public YapiCommand /* arguments: V_target ms_duration */
{
public:
  apifun_VoltageOutput_voltageMove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "voltageMove";
  }

  string getDescription()
  {
    return "Performs a smooth transition of output voltage.";
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
    vector<YVoltageOutput*>* list = enumerateTargets<YVoltageOutput>(_function, target, modulelist);
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

//--- (end of YVoltageOutput implementation)

//--- (YVoltageOutput functions)
void YVoltageOutputCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YVoltageOutput>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new VoltageOutput_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new VoltageOutput_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new VoltageOutput_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new VoltageOutput_set_currentVoltage(this)));
    cmdList->push_back((YapiCommand*) (new VoltageOutput_get_currentVoltage(this)));
    cmdList->push_back((YapiCommand*) (new VoltageOutput_set_voltageAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new VoltageOutput_get_voltageAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new apifun_VoltageOutput_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_VoltageOutput_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_VoltageOutput_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_VoltageOutput_voltageMove(this)));
  }

//--- (end of YVoltageOutput functions)
