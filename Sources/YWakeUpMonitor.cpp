/*********************************************************************
 *
 *  $Id: YWakeUpMonitor.cpp 32610 2018-10-10 06:52:20Z seb $
 *
 *  Implements commands to handle WakeUpMonitor functions
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
#include "YWakeUpMonitor.h"
#include "yocto_api.h"
#include "yocto_wakeupmonitor.h"

using namespace std;

//--- (YWakeUpMonitor definitions)

static const char *enumWakeUpReason[] = {
    "USBPOWER",
    "EXTPOWER",
    "ENDOFSLEEP",
    "EXTSIG1",
    "SCHEDULE1",
    "SCHEDULE2",
    NULL
};

static const char *enumWakeUpState[] = {
    "SLEEPING",
    "AWAKE",
    NULL
};

//--- (end of YWakeUpMonitor definitions)


//--- (YWakeUpMonitor implementation)
bool   YWakeUpMonitorCmdLine::isModule(void)      { return false; }
string YWakeUpMonitorCmdLine::YFunctionName(void) { return "YWakeUpMonitor"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of powerDuration is int (Int)
// type of sleepCountdown is int (Int)
// type of nextWakeUp is s64 (UTCTime)
// type of wakeUpReason is int (WakeUpReason)
// type of wakeUpState is int (WakeUpState)
// type of rtcTime is s64 (UTCTime)
// type of endOfTime is int (UInt31)
/**
 * Returns the logical name of the monitor.
 *
 * @return a string corresponding to the logical name of the monitor
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class WakeUpMonitor_get_logicalName : public YapiCommand /* arguments: */
{
public:
  WakeUpMonitor_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the monitor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
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
 * Changes the logical name of the monitor. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the monitor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpMonitor_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  WakeUpMonitor_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the monitor.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the monitor", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the monitor.
 *
 * @return a string corresponding to a short string representing the current state of the monitor
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class WakeUpMonitor_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  WakeUpMonitor_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the monitor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
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
 * Returns the maximal wake up time (in seconds) before automatically going to sleep.
 *
 * @return an integer corresponding to the maximal wake up time (in seconds) before automatically going to sleep
 *
 * On failure, throws an exception or returns Y_POWERDURATION_INVALID.
 */
class WakeUpMonitor_get_powerDuration : public YapiCommand /* arguments: */
{
public:
  WakeUpMonitor_get_powerDuration(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_powerDuration";
  }

  string getDescription()
  {
    return "Returns the maximal wake up time (in seconds) before automatically going to sleep.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_powerDuration();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the maximal wake up time (seconds) before automatically going to sleep.
 *
 * @param newval : an integer corresponding to the maximal wake up time (seconds) before automatically
 * going to sleep
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpMonitor_set_powerDuration : public YapiCommand /* arguments: newval */
{
public:
  WakeUpMonitor_set_powerDuration(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_powerDuration";
  }

  string getDescription()
  {
    return "Changes the maximal wake up time (seconds) before automatically going to sleep.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the maximal wake up time (seconds) before automatically going to sleep", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_powerDuration(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the delay before the  next sleep period.
 *
 * @return an integer corresponding to the delay before the  next sleep period
 *
 * On failure, throws an exception or returns Y_SLEEPCOUNTDOWN_INVALID.
 */
class WakeUpMonitor_get_sleepCountdown : public YapiCommand /* arguments: */
{
public:
  WakeUpMonitor_get_sleepCountdown(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_sleepCountdown";
  }

  string getDescription()
  {
    return "Returns the delay before the next sleep period.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_sleepCountdown();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the delay before the next sleep period.
 *
 * @param newval : an integer corresponding to the delay before the next sleep period
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpMonitor_set_sleepCountdown : public YapiCommand /* arguments: newval */
{
public:
  WakeUpMonitor_set_sleepCountdown(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_sleepCountdown";
  }

  string getDescription()
  {
    return "Changes the delay before the next sleep period.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the delay before the next sleep period", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_sleepCountdown(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the next scheduled wake up date/time (UNIX format).
 *
 * @return an integer corresponding to the next scheduled wake up date/time (UNIX format)
 *
 * On failure, throws an exception or returns Y_NEXTWAKEUP_INVALID.
 */
class WakeUpMonitor_get_nextWakeUp : public YapiCommand /* arguments: */
{
public:
  WakeUpMonitor_get_nextWakeUp(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_nextWakeUp";
  }

  string getDescription()
  {
    return "Returns the next scheduled wake up date/time (UNIX format).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_nextWakeUp();
        char buf[64]; snprintf(buf, 64, "%u [s] since Jan 1, 1970", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the days of the week when a wake up must take place.
 *
 * @param newval : an integer corresponding to the days of the week when a wake up must take place
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpMonitor_set_nextWakeUp : public YapiCommand /* arguments: newval */
{
public:
  WakeUpMonitor_set_nextWakeUp(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_nextWakeUp";
  }

  string getDescription()
  {
    return "Changes the days of the week when a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(S64_ARG, "newval", "an integer corresponding to the days of the week when a wake up must take place", "_S64", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_nextWakeUp(s64((*args)[0]->get_s64Value()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the latest wake up reason.
 *
 * @return a value among Y_WAKEUPREASON_USBPOWER, Y_WAKEUPREASON_EXTPOWER, Y_WAKEUPREASON_ENDOFSLEEP,
 * Y_WAKEUPREASON_EXTSIG1, Y_WAKEUPREASON_SCHEDULE1 and Y_WAKEUPREASON_SCHEDULE2 corresponding to the
 * latest wake up reason
 *
 * On failure, throws an exception or returns Y_WAKEUPREASON_INVALID.
 */
class WakeUpMonitor_get_wakeUpReason : public YapiCommand /* arguments: */
{
public:
  WakeUpMonitor_get_wakeUpReason(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_wakeUpReason";
  }

  string getDescription()
  {
    return "Returns the latest wake up reason.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_wakeUpReason();
        string strval =  enumString(attrval,enumWakeUpReason);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns  the current state of the monitor.
 *
 * @return either Y_WAKEUPSTATE_SLEEPING or Y_WAKEUPSTATE_AWAKE, according to  the current state of the monitor
 *
 * On failure, throws an exception or returns Y_WAKEUPSTATE_INVALID.
 */
class WakeUpMonitor_get_wakeUpState : public YapiCommand /* arguments: */
{
public:
  WakeUpMonitor_get_wakeUpState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_wakeUpState";
  }

  string getDescription()
  {
    return "Returns the current state of the monitor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_wakeUpState();
        string strval =  enumString(attrval,enumWakeUpState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackWakeUpMonitor is YWakeUpMonitorValueCallback* (YWakeUpMonitorValueCallback)
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
class apifun_WakeUpMonitor_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_WakeUpMonitor_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
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
class apifun_WakeUpMonitor_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_WakeUpMonitor_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
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
 * Forces a wake up.
 */
class apifun_WakeUpMonitor_wakeUp : public YapiCommand /* arguments: */
{
public:
  apifun_WakeUpMonitor_wakeUp(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "wakeUp";
  }

  string getDescription()
  {
    return "Forces a wake up.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->wakeUp();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Goes to sleep until the next wake up condition is met,  the
 * RTC time must have been set before calling this function.
 *
 * @param secBeforeSleep : number of seconds before going into sleep mode,
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WakeUpMonitor_sleep : public YapiCommand /* arguments: secBeforeSleep */
{
public:
  apifun_WakeUpMonitor_sleep(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "sleep";
  }

  string getDescription()
  {
    return "Goes to sleep until the next wake up condition is met, theRTC time must have been set before calling this function.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "secBeforeSleep", "number of seconds before going into sleep mode,", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->sleep((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Goes to sleep for a specific duration or until the next wake up condition is met, the
 * RTC time must have been set before calling this function. The count down before sleep
 * can be canceled with resetSleepCountDown.
 *
 * @param secUntilWakeUp : number of seconds before next wake up
 * @param secBeforeSleep : number of seconds before going into sleep mode
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WakeUpMonitor_sleepFor : public YapiCommand /* arguments: secUntilWakeUp secBeforeSleep */
{
public:
  apifun_WakeUpMonitor_sleepFor(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "sleepFor";
  }

  string getDescription()
  {
    return "Goes to sleep for a specific duration or until the next wake up condition is met, theRTC time must have been set before calling this function.";
  }

  string getMoreInfo()
  {
    return "The count down before sleep can be canceled with resetSleepCountDown.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "secUntilWakeUp", "number of seconds before next wake up", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "secBeforeSleep", "number of seconds before going into sleep mode", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->sleepFor((int)(*args)[0]->get_intValue(),
                             (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Go to sleep until a specific date is reached or until the next wake up condition is met, the
 * RTC time must have been set before calling this function. The count down before sleep
 * can be canceled with resetSleepCountDown.
 *
 * @param wakeUpTime : wake-up datetime (UNIX format)
 * @param secBeforeSleep : number of seconds before going into sleep mode
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WakeUpMonitor_sleepUntil : public YapiCommand /* arguments: wakeUpTime secBeforeSleep */
{
public:
  apifun_WakeUpMonitor_sleepUntil(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "sleepUntil";
  }

  string getDescription()
  {
    return "Go to sleep until a specific date is reached or until the next wake up condition is met, theRTC time must have been set before calling this function.";
  }

  string getMoreInfo()
  {
    return "The count down before sleep can be canceled with resetSleepCountDown.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "wakeUpTime", "wake-up datetime (UNIX format)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "secBeforeSleep", "number of seconds before going into sleep mode", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->sleepUntil((int)(*args)[0]->get_intValue(),
                               (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Resets the sleep countdown.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_WakeUpMonitor_resetSleepCountDown : public YapiCommand /* arguments: */
{
public:
  apifun_WakeUpMonitor_resetSleepCountDown(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "resetSleepCountDown";
  }

  string getDescription()
  {
    return "Resets the sleep countdown.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpMonitor*>* list = enumerateTargets<YWakeUpMonitor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetSleepCountDown();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YWakeUpMonitor implementation)

//--- (YWakeUpMonitor functions)
void YWakeUpMonitorCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YWakeUpMonitor>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_get_powerDuration(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_set_powerDuration(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_get_sleepCountdown(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_set_sleepCountdown(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_get_nextWakeUp(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_set_nextWakeUp(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_get_wakeUpReason(this)));
    cmdList->push_back((YapiCommand*) (new WakeUpMonitor_get_wakeUpState(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpMonitor_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpMonitor_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpMonitor_wakeUp(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpMonitor_sleep(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpMonitor_sleepFor(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpMonitor_sleepUntil(this)));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpMonitor_resetSleepCountDown(this)));
  }

//--- (end of YWakeUpMonitor functions)
