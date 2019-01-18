/*********************************************************************
 *
 *  $Id: YMultiAxisController.cpp 32610 2018-10-10 06:52:20Z seb $
 *
 *  Implements commands to handle MultiAxisController functions
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
#include "YMultiAxisController.h"
#include "yocto_api.h"
#include "yocto_multiaxiscontroller.h"

using namespace std;

//--- (YMultiAxisController definitions)

static const char *enumStepperState[] = {
    "ABSENT",
    "ALERT",
    "HI_Z",
    "STOP",
    "RUN",
    "BATCH",
    NULL
};

//--- (end of YMultiAxisController definitions)


//--- (YMultiAxisController implementation)
bool   YMultiAxisControllerCmdLine::isModule(void)      { return false; }
string YMultiAxisControllerCmdLine::YFunctionName(void) { return "YMultiAxisController"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of nAxis is int (UInt31)
// type of globalState is int (StepperState)
// type of command is string (Text)
/**
 * Returns the logical name of the multi-axis controller.
 *
 * @return a string corresponding to the logical name of the multi-axis controller
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class MultiAxisController_get_logicalName : public YapiCommand /* arguments: */
{
public:
  MultiAxisController_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the multi-axis controller.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
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
 * Changes the logical name of the multi-axis controller. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the multi-axis controller
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MultiAxisController_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  MultiAxisController_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the multi-axis controller.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the multi-axis controller", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the multi-axis controller.
 *
 * @return a string corresponding to a short string representing the current state of the multi-axis controller
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class MultiAxisController_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  MultiAxisController_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the multi-axis controller.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
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
 * Returns the number of synchronized controllers.
 *
 * @return an integer corresponding to the number of synchronized controllers
 *
 * On failure, throws an exception or returns Y_NAXIS_INVALID.
 */
class MultiAxisController_get_nAxis : public YapiCommand /* arguments: */
{
public:
  MultiAxisController_get_nAxis(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_nAxis";
  }

  string getDescription()
  {
    return "Returns the number of synchronized controllers.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_nAxis();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the number of synchronized controllers.
 *
 * @param newval : an integer corresponding to the number of synchronized controllers
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MultiAxisController_set_nAxis : public YapiCommand /* arguments: newval */
{
public:
  MultiAxisController_set_nAxis(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_nAxis";
  }

  string getDescription()
  {
    return "Changes the number of synchronized controllers.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the number of synchronized controllers", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_nAxis(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the stepper motor set overall state.
 *
 * @return a value among Y_GLOBALSTATE_ABSENT, Y_GLOBALSTATE_ALERT, Y_GLOBALSTATE_HI_Z,
 * Y_GLOBALSTATE_STOP, Y_GLOBALSTATE_RUN and Y_GLOBALSTATE_BATCH corresponding to the stepper motor
 * set overall state
 *
 * On failure, throws an exception or returns Y_GLOBALSTATE_INVALID.
 */
class MultiAxisController_get_globalState : public YapiCommand /* arguments: */
{
public:
  MultiAxisController_get_globalState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_globalState";
  }

  string getDescription()
  {
    return "Returns the stepper motor set overall state.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_globalState();
        string strval =  enumString(attrval,enumStepperState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackMultiAxisController is YMultiAxisControllerValueCallback* (YMultiAxisControllerValueCallback)
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
class apifun_MultiAxisController_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_MultiAxisController_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
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
class apifun_MultiAxisController_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_MultiAxisController_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
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
 * Reinitialize all controllers and clear all alert flags.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_reset : public YapiCommand /* arguments: */
{
public:
  apifun_MultiAxisController_reset(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "reset";
  }

  string getDescription()
  {
    return "Reinitialize all controllers and clear all alert flags.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->reset();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts all motors backward at the specified speeds, to search for the motor home position.
 *
 * @param speed : desired speed for all axis, in steps per second.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_findHomePosition : public YapiCommand /* arguments: speed */
{
public:
  apifun_MultiAxisController_findHomePosition(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "findHomePosition";
  }

  string getDescription()
  {
    return "Starts all motors backward at the specified speeds, to search for the motor home position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "speed", "desired speed for all axis, in steps per second.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->findHomePosition((*args)[0]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts all motors synchronously to reach a given absolute position.
 * The time needed to reach the requested position will depend on the lowest
 * acceleration and max speed parameters configured for all motors.
 * The final position will be reached on all axis at the same time.
 *
 * @param absPos : absolute position, measured in steps from each origin.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_moveTo : public YapiCommand /* arguments: absPos */
{
public:
  apifun_MultiAxisController_moveTo(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "moveTo";
  }

  string getDescription()
  {
    return "Starts all motors synchronously to reach a given absolute position.";
  }

  string getMoreInfo()
  {
    return "The time needed to reach the requested position will depend on the lowest acceleration and max speed parameters configured for all motors. The final position will be reached on all axis at the same time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "absPos", "absolute position, measured in steps from each origin.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->moveTo((*args)[0]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts all motors synchronously to reach a given relative position.
 * The time needed to reach the requested position will depend on the lowest
 * acceleration and max speed parameters configured for all motors.
 * The final position will be reached on all axis at the same time.
 *
 * @param relPos : relative position, measured in steps from the current position.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_moveRel : public YapiCommand /* arguments: relPos */
{
public:
  apifun_MultiAxisController_moveRel(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "moveRel";
  }

  string getDescription()
  {
    return "Starts all motors synchronously to reach a given relative position.";
  }

  string getMoreInfo()
  {
    return "The time needed to reach the requested position will depend on the lowest acceleration and max speed parameters configured for all motors. The final position will be reached on all axis at the same time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "relPos", "relative position, measured in steps from the current position.", "_FLOATARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->moveRel((*args)[0]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Keep the motor in the same state for the specified amount of time, before processing next command.
 *
 * @param waitMs : wait time, specified in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_pause : public YapiCommand /* arguments: waitMs */
{
public:
  apifun_MultiAxisController_pause(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "pause";
  }

  string getDescription()
  {
    return "Keep the motor in the same state for the specified amount of time, before processing next command.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "waitMs", "wait time, specified in milliseconds.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->pause((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the motor with an emergency alert, without taking any additional precaution.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_emergencyStop : public YapiCommand /* arguments: */
{
public:
  apifun_MultiAxisController_emergencyStop(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "emergencyStop";
  }

  string getDescription()
  {
    return "Stops the motor with an emergency alert, without taking any additional precaution.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->emergencyStop();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the motor smoothly as soon as possible, without waiting for ongoing move completion.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_abortAndBrake : public YapiCommand /* arguments: */
{
public:
  apifun_MultiAxisController_abortAndBrake(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "abortAndBrake";
  }

  string getDescription()
  {
    return "Stops the motor smoothly as soon as possible, without waiting for ongoing move completion.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->abortAndBrake();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Turn the controller into Hi-Z mode immediately, without waiting for ongoing move completion.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiAxisController_abortAndHiZ : public YapiCommand /* arguments: */
{
public:
  apifun_MultiAxisController_abortAndHiZ(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "abortAndHiZ";
  }

  string getDescription()
  {
    return "Turn the controller into Hi-Z mode immediately, without waiting for ongoing move completion.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiAxisController*>* list = enumerateTargets<YMultiAxisController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->abortAndHiZ();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YMultiAxisController implementation)

//--- (YMultiAxisController functions)
void YMultiAxisControllerCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YMultiAxisController>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new MultiAxisController_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new MultiAxisController_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new MultiAxisController_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new MultiAxisController_get_nAxis(this)));
    cmdList->push_back((YapiCommand*) (new MultiAxisController_set_nAxis(this)));
    cmdList->push_back((YapiCommand*) (new MultiAxisController_get_globalState(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_reset(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_findHomePosition(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_moveTo(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_moveRel(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_pause(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_emergencyStop(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_abortAndBrake(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiAxisController_abortAndHiZ(this)));
  }

//--- (end of YMultiAxisController functions)
