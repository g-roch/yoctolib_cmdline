/*********************************************************************
 *
 *  $Id: YMultiSensController.cpp 33710 2018-12-14 14:18:53Z seb $
 *
 *  Implements commands to handle MultiSensController functions
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
#include "YMultiSensController.h"
#include "yocto_api.h"
#include "yocto_multisenscontroller.h"

using namespace std;

//--- (YMultiSensController definitions)

static const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

//--- (end of YMultiSensController definitions)


//--- (YMultiSensController implementation)
bool   YMultiSensControllerCmdLine::isModule(void)      { return false; }
string YMultiSensControllerCmdLine::YFunctionName(void) { return "YMultiSensController"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of nSensors is int (UInt31)
// type of maxSensors is int (UInt31)
// type of maintenanceMode is int (Bool)
// type of command is string (Text)
/**
 * Returns the logical name of the multi-sensor controller.
 *
 * @return a string corresponding to the logical name of the multi-sensor controller
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class MultiSensController_get_logicalName : public YapiCommand /* arguments: */
{
public:
  MultiSensController_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the multi-sensor controller.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
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
 * Changes the logical name of the multi-sensor controller. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the multi-sensor controller
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MultiSensController_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  MultiSensController_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the multi-sensor controller.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the multi-sensor controller", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the multi-sensor controller.
 *
 * @return a string corresponding to a short string representing the current state of the multi-sensor controller
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class MultiSensController_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  MultiSensController_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the multi-sensor controller.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
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
 * Returns the number of sensors to poll.
 *
 * @return an integer corresponding to the number of sensors to poll
 *
 * On failure, throws an exception or returns Y_NSENSORS_INVALID.
 */
class MultiSensController_get_nSensors : public YapiCommand /* arguments: */
{
public:
  MultiSensController_get_nSensors(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_nSensors";
  }

  string getDescription()
  {
    return "Returns the number of sensors to poll.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_nSensors();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the number of sensors to poll. Remember to call the
 * saveToFlash() method of the module if the
 * modification must be kept. It's recommended to restart the
 * device with  module->reboot() after modifying
 * (and saving) this settings
 *
 * @param newval : an integer corresponding to the number of sensors to poll
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MultiSensController_set_nSensors : public YapiCommand /* arguments: newval */
{
public:
  MultiSensController_set_nSensors(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_nSensors";
  }

  string getDescription()
  {
    return "Changes the number of sensors to poll.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method of the module if the modification must be kept. It's recommended to restart the device with module->reboot() after modifying (and saving) this settings";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the number of sensors to poll", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_nSensors(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximum configurable sensor count allowed on this device.
 *
 * @return an integer corresponding to the maximum configurable sensor count allowed on this device
 *
 * On failure, throws an exception or returns Y_MAXSENSORS_INVALID.
 */
class MultiSensController_get_maxSensors : public YapiCommand /* arguments: */
{
public:
  MultiSensController_get_maxSensors(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_maxSensors";
  }

  string getDescription()
  {
    return "Returns the maximum configurable sensor count allowed on this device.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_maxSensors();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns true when the device is in maintenance mode.
 *
 * @return either Y_MAINTENANCEMODE_FALSE or Y_MAINTENANCEMODE_TRUE, according to true when the device
 * is in maintenance mode
 *
 * On failure, throws an exception or returns Y_MAINTENANCEMODE_INVALID.
 */
class MultiSensController_get_maintenanceMode : public YapiCommand /* arguments: */
{
public:
  MultiSensController_get_maintenanceMode(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_maintenanceMode";
  }

  string getDescription()
  {
    return "Returns true when the device is in maintenance mode.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_maintenanceMode();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the device mode to enable maintenance and stop sensors polling.
 * This way, the device will not restart automatically in case it cannot
 * communicate with one of the sensors.
 *
 * @param newval : either Y_MAINTENANCEMODE_FALSE or Y_MAINTENANCEMODE_TRUE, according to the device
 * mode to enable maintenance and stop sensors polling
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MultiSensController_set_maintenanceMode : public YapiCommand /* arguments: newval */
{
public:
  MultiSensController_set_maintenanceMode(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_maintenanceMode";
  }

  string getDescription()
  {
    return "Changes the device mode to enable maintenance and stop sensors polling.";
  }

  string getMoreInfo()
  {
    return "This way, the device will not restart automatically in case it cannot communicate with one of the sensors.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE, according to the device mode to enable maintenance and stop sensors polling", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_maintenanceMode(Y_MAINTENANCEMODE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackMultiSensController is YMultiSensControllerValueCallback* (YMultiSensControllerValueCallback)
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
class apifun_MultiSensController_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_MultiSensController_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
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
class apifun_MultiSensController_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_MultiSensController_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
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
 * Configure the I2C address of the only sensor connected to the device.
 * It is recommended to put the the device in maintenance mode before
 * changing Sensors addresses.  This method is only intended to work with a single
 * sensor connected to the device, if several sensors are connected, result
 * is unpredictable.
 * Note that the device is probably expecting to find a string of sensors with specific
 * addresses. Check the device documentation to find out which addresses should be used.
 *
 * @param addr : new address of the connected sensor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_MultiSensController_setupAddress : public YapiCommand /* arguments: addr */
{
public:
  apifun_MultiSensController_setupAddress(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "setupAddress";
  }

  string getDescription()
  {
    return "Configure the I2C address of the only sensor connected to the device.";
  }

  string getMoreInfo()
  {
    return "It is recommended to put the the device in maintenance mode before changing Sensors addresses. This method is only intended to work with a single sensor connected to the device, if several sensors are connected, result is unpredictable. Note that the device is probably expecting to find a string of sensors with specific addresses. Check the device documentation to find out which addresses should be used.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "addr", "new address of the connected sensor", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMultiSensController*>* list = enumerateTargets<YMultiSensController>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->setupAddress((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YMultiSensController implementation)

//--- (YMultiSensController functions)
void YMultiSensControllerCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YMultiSensController>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new MultiSensController_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new MultiSensController_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new MultiSensController_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new MultiSensController_get_nSensors(this)));
    cmdList->push_back((YapiCommand*) (new MultiSensController_set_nSensors(this)));
    cmdList->push_back((YapiCommand*) (new MultiSensController_get_maxSensors(this)));
    cmdList->push_back((YapiCommand*) (new MultiSensController_get_maintenanceMode(this)));
    cmdList->push_back((YapiCommand*) (new MultiSensController_set_maintenanceMode(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiSensController_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiSensController_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MultiSensController_setupAddress(this)));
  }

//--- (end of YMultiSensController functions)
