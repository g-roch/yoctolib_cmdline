/*********************************************************************
 *
 *  $Id: YCurrentLoopOutput.cpp 33710 2018-12-14 14:18:53Z seb $
 *
 *  Implements commands to handle CurrentLoopOutput functions
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
#include "YCurrentLoopOutput.h"
#include "yocto_api.h"
#include "yocto_currentloopoutput.h"

using namespace std;

//--- (YCurrentLoopOutput definitions)

static const char *enumLoopPwrState[] = {
    "NOPWR",
    "LOWPWR",
    "POWEROK",
    NULL
};

//--- (end of YCurrentLoopOutput definitions)


//--- (YCurrentLoopOutput implementation)
bool   YCurrentLoopOutputCmdLine::isModule(void)      { return false; }
string YCurrentLoopOutputCmdLine::YFunctionName(void) { return "YCurrentLoopOutput"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of current is double (MeasureVal)
// type of currentTransition is string (AnyFloatTransition)
// type of currentAtStartUp is double (MeasureVal)
// type of loopPower is int (LoopPwrState)
/**
 * Returns the logical name of the 4-20mA output.
 *
 * @return a string corresponding to the logical name of the 4-20mA output
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class CurrentLoopOutput_get_logicalName : public YapiCommand /* arguments: */
{
public:
  CurrentLoopOutput_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the 4-20mA output.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
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
 * Changes the logical name of the 4-20mA output. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the 4-20mA output
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class CurrentLoopOutput_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  CurrentLoopOutput_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the 4-20mA output.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the 4-20mA output", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the 4-20mA output.
 *
 * @return a string corresponding to a short string representing the current state of the 4-20mA output
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class CurrentLoopOutput_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  CurrentLoopOutput_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the 4-20mA output.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
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
 * Changes the current loop, the valid range is from 3 to 21mA. If the loop is
 * not properly powered, the  target current is not reached and
 * loopPower is set to LOWPWR.
 *
 * @param newval : a floating point number corresponding to the current loop, the valid range is from 3 to 21mA
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class CurrentLoopOutput_set_current : public YapiCommand /* arguments: newval */
{
public:
  CurrentLoopOutput_set_current(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_current";
  }

  string getDescription()
  {
    return "Changes the current loop, the valid range is from 3 to 21mA.";
  }

  string getMoreInfo()
  {
    return "If the loop is not properly powered, the target current is not reached and loopPower is set to LOWPWR.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the current loop, the valid range is from 3 to 21mA", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_current(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the loop current set point in mA.
 *
 * @return a floating point number corresponding to the loop current set point in mA
 *
 * On failure, throws an exception or returns Y_CURRENT_INVALID.
 */
class CurrentLoopOutput_get_current : public YapiCommand /* arguments: */
{
public:
  CurrentLoopOutput_get_current(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_current";
  }

  string getDescription()
  {
    return "Returns the loop current set point in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_current();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the loop current at device start up. Remember to call the matching
 * module saveToFlash() method, otherwise this call has no effect.
 *
 * @param newval : a floating point number corresponding to the loop current at device start up
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class CurrentLoopOutput_set_currentAtStartUp : public YapiCommand /* arguments: newval */
{
public:
  CurrentLoopOutput_set_currentAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_currentAtStartUp";
  }

  string getDescription()
  {
    return "Changes the loop current at device start up.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call has no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the loop current at device start up", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_currentAtStartUp(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current in the loop at device startup, in mA.
 *
 * @return a floating point number corresponding to the current in the loop at device startup, in mA
 *
 * On failure, throws an exception or returns Y_CURRENTATSTARTUP_INVALID.
 */
class CurrentLoopOutput_get_currentAtStartUp : public YapiCommand /* arguments: */
{
public:
  CurrentLoopOutput_get_currentAtStartUp(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentAtStartUp";
  }

  string getDescription()
  {
    return "Returns the current in the loop at device startup, in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentAtStartUp();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the loop powerstate.  POWEROK: the loop
 * is powered. NOPWR: the loop in not powered. LOWPWR: the loop is not
 * powered enough to maintain the current required (insufficient voltage).
 *
 * @return a value among Y_LOOPPOWER_NOPWR, Y_LOOPPOWER_LOWPWR and Y_LOOPPOWER_POWEROK corresponding
 * to the loop powerstate
 *
 * On failure, throws an exception or returns Y_LOOPPOWER_INVALID.
 */
class CurrentLoopOutput_get_loopPower : public YapiCommand /* arguments: */
{
public:
  CurrentLoopOutput_get_loopPower(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_loopPower";
  }

  string getDescription()
  {
    return "Returns the loop powerstate.";
  }

  string getMoreInfo()
  {
    return "POWEROK: the loop is powered. NOPWR: the loop in not powered. LOWPWR: the loop is not powered enough to maintain the current required (insufficient voltage).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_loopPower();
        string strval =  enumString(attrval,enumLoopPwrState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackCurrentLoopOutput is YCurrentLoopOutputValueCallback* (YCurrentLoopOutputValueCallback)
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
class apifun_CurrentLoopOutput_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_CurrentLoopOutput_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
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
class apifun_CurrentLoopOutput_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_CurrentLoopOutput_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
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
 * Performs a smooth transition of current flowing in the loop. Any current explicit
 * change cancels any ongoing transition process.
 *
 * @param mA_target   : new current value at the end of the transition
 *         (floating-point number, representing the end current in mA)
 * @param ms_duration : total duration of the transition, in milliseconds
 *
 * @return YAPI_SUCCESS when the call succeeds.
 */
class apifun_CurrentLoopOutput_currentMove : public YapiCommand /* arguments: mA_target ms_duration */
{
public:
  apifun_CurrentLoopOutput_currentMove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "currentMove";
  }

  string getDescription()
  {
    return "Performs a smooth transition of current flowing in the loop.";
  }

  string getMoreInfo()
  {
    return "Any current explicit change cancels any ongoing transition process.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "mA_target", "new current value at the end of the transition (floating-point number, representing the end current in mA)", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "total duration of the transition, in milliseconds", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YCurrentLoopOutput*>* list = enumerateTargets<YCurrentLoopOutput>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->currentMove((*args)[0]->get_doubleValue(),
                                (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YCurrentLoopOutput implementation)

//--- (YCurrentLoopOutput functions)
void YCurrentLoopOutputCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YCurrentLoopOutput>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_set_current(this)));
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_get_current(this)));
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_set_currentAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_get_currentAtStartUp(this)));
    cmdList->push_back((YapiCommand*) (new CurrentLoopOutput_get_loopPower(this)));
    cmdList->push_back((YapiCommand*) (new apifun_CurrentLoopOutput_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_CurrentLoopOutput_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_CurrentLoopOutput_currentMove(this)));
  }

//--- (end of YCurrentLoopOutput functions)
