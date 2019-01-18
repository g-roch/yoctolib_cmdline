/*********************************************************************
 *
 *  $Id: YHubPort.cpp 32610 2018-10-10 06:52:20Z seb $
 *
 *  Implements commands to handle HubPort functions
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
#include "YHubPort.h"
#include "yocto_api.h"
#include "yocto_hubport.h"

using namespace std;

//--- (YHubPort definitions)

static const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

static const char *enumPortState[] = {
    "OFF",
    "OVRLD",
    "ON",
    "RUN",
    "PROG",
    NULL
};

//--- (end of YHubPort definitions)


//--- (YHubPort implementation)
bool   YHubPortCmdLine::isModule(void)      { return false; }
string YHubPortCmdLine::YFunctionName(void) { return "YHubPort"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of enabled is int (Bool)
// type of portState is int (PortState)
// type of baudRate is int (BaudRate)
/**
 * Returns the logical name of the Yocto-hub port, which is always the serial number of the
 * connected module.
 *
 * @return a string corresponding to the logical name of the Yocto-hub port, which is always the
 * serial number of the
 *         connected module
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class HubPort_get_logicalName : public YapiCommand /* arguments: */
{
public:
  HubPort_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the Yocto-hub port, which is always the serial number of theconnected module.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
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
 * It is not possible to configure the logical name of a Yocto-hub port. The logical
 * name is automatically set to the serial number of the connected module.
 *
 * @param newval : a string
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class HubPort_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  HubPort_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "It is not possible to configure the logical name of a Yocto-hub port.";
  }

  string getMoreInfo()
  {
    return "The logical name is automatically set to the serial number of the connected module.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the Yocto-hub port.
 *
 * @return a string corresponding to a short string representing the current state of the Yocto-hub port
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class HubPort_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  HubPort_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the Yocto-hub port.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
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
 * Returns true if the Yocto-hub port is powered, false otherwise.
 *
 * @return either Y_ENABLED_FALSE or Y_ENABLED_TRUE, according to true if the Yocto-hub port is
 * powered, false otherwise
 *
 * On failure, throws an exception or returns Y_ENABLED_INVALID.
 */
class HubPort_get_enabled : public YapiCommand /* arguments: */
{
public:
  HubPort_get_enabled(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_enabled";
  }

  string getDescription()
  {
    return "Returns true if the Yocto-hub port is powered, false otherwise.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_enabled();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the activation of the Yocto-hub port. If the port is enabled, the
 * connected module is powered. Otherwise, port power is shut down.
 *
 * @param newval : either Y_ENABLED_FALSE or Y_ENABLED_TRUE, according to the activation of the Yocto-hub port
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class HubPort_set_enabled : public YapiCommand /* arguments: newval */
{
public:
  HubPort_set_enabled(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_enabled";
  }

  string getDescription()
  {
    return "Changes the activation of the Yocto-hub port.";
  }

  string getMoreInfo()
  {
    return "If the port is enabled, the connected module is powered. Otherwise, port power is shut down.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE, according to the activation of the Yocto-hub port", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_enabled(Y_ENABLED_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current state of the Yocto-hub port.
 *
 * @return a value among Y_PORTSTATE_OFF, Y_PORTSTATE_OVRLD, Y_PORTSTATE_ON, Y_PORTSTATE_RUN and
 * Y_PORTSTATE_PROG corresponding to the current state of the Yocto-hub port
 *
 * On failure, throws an exception or returns Y_PORTSTATE_INVALID.
 */
class HubPort_get_portState : public YapiCommand /* arguments: */
{
public:
  HubPort_get_portState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_portState";
  }

  string getDescription()
  {
    return "Returns the current state of the Yocto-hub port.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_portState();
        string strval =  enumString(attrval,enumPortState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current baud rate used by this Yocto-hub port, in kbps.
 * The default value is 1000 kbps, but a slower rate may be used if communication
 * problems are encountered.
 *
 * @return an integer corresponding to the current baud rate used by this Yocto-hub port, in kbps
 *
 * On failure, throws an exception or returns Y_BAUDRATE_INVALID.
 */
class HubPort_get_baudRate : public YapiCommand /* arguments: */
{
public:
  HubPort_get_baudRate(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_baudRate";
  }

  string getDescription()
  {
    return "Returns the current baud rate used by this Yocto-hub port, in kbps.";
  }

  string getMoreInfo()
  {
    return "The default value is 1000 kbps, but a slower rate may be used if communication problems are encountered.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_baudRate();
        char buf[32]; snprintf(buf, 32, "%u [kbps]", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackHubPort is YHubPortValueCallback* (YHubPortValueCallback)
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
class apifun_HubPort_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_HubPort_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
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
class apifun_HubPort_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_HubPort_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YHubPort*>* list = enumerateTargets<YHubPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->unmuteValueCallbacks();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YHubPort implementation)

//--- (YHubPort functions)
void YHubPortCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YHubPort>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new HubPort_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new HubPort_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new HubPort_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new HubPort_get_enabled(this)));
    cmdList->push_back((YapiCommand*) (new HubPort_set_enabled(this)));
    cmdList->push_back((YapiCommand*) (new HubPort_get_portState(this)));
    cmdList->push_back((YapiCommand*) (new HubPort_get_baudRate(this)));
    cmdList->push_back((YapiCommand*) (new apifun_HubPort_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_HubPort_unmuteValueCallbacks(this)));
  }

//--- (end of YHubPort functions)
