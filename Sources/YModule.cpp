/*********************************************************************
 *
 * $Id: YModule.cpp 33710 2018-12-14 14:18:53Z seb $
 *
 * Implements commands to handle Module functions
 *
 * - - - - - - - - - License information: - - - - - - - - -
 *
 * Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 * 1) If you have obtained this file from www.yoctopuce.com,
 *    Yoctopuce Sarl licenses to you (hereafter Licensee) the
 *    right to use, modify, copy, and integrate this source file
 *    into your own solution for the sole purpose of interfacing
 *    a Yoctopuce product with Licensee's solution.
 *
 *    The use of this file and all relationship between Yoctopuce
 *    and Licensee are governed by Yoctopuce General Terms and
 *    Conditions.
 *
 *    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 *    WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS
 *    FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *    EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 *    COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR
 *    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
 *    LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *    CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *    BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *    WARRANTY, OR OTHERWISE.
 *
 * 2) If your intent is not to interface with Yoctopuce products,
 *    you are not entitled to use, read or create any derived
 *    material from this source file.
 *
 *********************************************************************/


#include <stdio.h>
#include "YModule.h"
#include "yocto_api.h"

using namespace std;

//--- (generated code: YModule definitions)

static const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

static const char *enumFlashSettings[] = {
    "LOADED",
    "SAVED",
    "MODIFIED",
    NULL
};

//--- (end of generated code: YModule definitions)


//--- (generated code: YModule implementation)
bool   YModuleCmdLine::isModule(void)      { return true; }
string YModuleCmdLine::YFunctionName(void) { return "YModule"; }

// type of productName is string (Text)
// type of serialNumber is string (Text)
// type of logicalName is string (Text)
// type of productId is int (XWord)
// type of productRelease is int (XWord)
// type of firmwareRelease is string (Text)
// type of persistentSettings is int (FlashSettings)
// type of luminosity is int (Percent)
// type of beacon is int (OnOff)
// type of upTime is s64 (Time)
// type of usbCurrent is int (UsedCurrent)
// type of rebootCountdown is int (Int)
// type of userVar is int (Int)
/**
 * Returns the commercial name of the module, as set by the factory.
 *
 * @return a string corresponding to the commercial name of the module, as set by the factory
 *
 * On failure, throws an exception or returns Y_PRODUCTNAME_INVALID.
 */
class Module_get_productName : public YapiCommand /* arguments: */
{
public:
  Module_get_productName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_productName";
  }

  string getDescription()
  {
    return "Returns the commercial name of the module, as set by the factory.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_productName();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the serial number of the module, as set by the factory.
 *
 * @return a string corresponding to the serial number of the module, as set by the factory
 *
 * On failure, throws an exception or returns Y_SERIALNUMBER_INVALID.
 */
class Module_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  Module_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_serialNumber";
  }

  string getDescription()
  {
    return "Returns the serial number of the module, as set by the factory.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_serialNumber();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the logical name of the module.
 *
 * @return a string corresponding to the logical name of the module
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Module_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Module_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the module.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
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
 * Changes the logical name of the module. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the module
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Module_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the module.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the module", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
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
 * Returns the USB device identifier of the module.
 *
 * @return an integer corresponding to the USB device identifier of the module
 *
 * On failure, throws an exception or returns Y_PRODUCTID_INVALID.
 */
class Module_get_productId : public YapiCommand /* arguments: */
{
public:
  Module_get_productId(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_productId";
  }

  string getDescription()
  {
    return "Returns the USB device identifier of the module.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_productId();
        char buf[32]; snprintf(buf,32,"0x%04x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the hardware release version of the module.
 *
 * @return an integer corresponding to the hardware release version of the module
 *
 * On failure, throws an exception or returns Y_PRODUCTRELEASE_INVALID.
 */
class Module_get_productRelease : public YapiCommand /* arguments: */
{
public:
  Module_get_productRelease(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_productRelease";
  }

  string getDescription()
  {
    return "Returns the hardware release version of the module.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_productRelease();
        char buf[32]; snprintf(buf,32,"0x%04x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the version of the firmware embedded in the module.
 *
 * @return a string corresponding to the version of the firmware embedded in the module
 *
 * On failure, throws an exception or returns Y_FIRMWARERELEASE_INVALID.
 */
class Module_get_firmwareRelease : public YapiCommand /* arguments: */
{
public:
  Module_get_firmwareRelease(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_firmwareRelease";
  }

  string getDescription()
  {
    return "Returns the version of the firmware embedded in the module.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_firmwareRelease();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current state of persistent module settings.
 *
 * @return a value among Y_PERSISTENTSETTINGS_LOADED, Y_PERSISTENTSETTINGS_SAVED and
 * Y_PERSISTENTSETTINGS_MODIFIED corresponding to the current state of persistent module settings
 *
 * On failure, throws an exception or returns Y_PERSISTENTSETTINGS_INVALID.
 */
class Module_get_persistentSettings : public YapiCommand /* arguments: */
{
public:
  Module_get_persistentSettings(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_persistentSettings";
  }

  string getDescription()
  {
    return "Returns the current state of persistent module settings.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_persistentSettings();
        string strval =  enumString(attrval,enumFlashSettings);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the luminosity of the  module informative LEDs (from 0 to 100).
 *
 * @return an integer corresponding to the luminosity of the  module informative LEDs (from 0 to 100)
 *
 * On failure, throws an exception or returns Y_LUMINOSITY_INVALID.
 */
class Module_get_luminosity : public YapiCommand /* arguments: */
{
public:
  Module_get_luminosity(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_luminosity";
  }

  string getDescription()
  {
    return "Returns the luminosity of the module informative LEDs (from 0 to 100).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_luminosity();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the luminosity of the module informative leds. The parameter is a
 * value between 0 and 100.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : an integer corresponding to the luminosity of the module informative leds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_luminosity : public YapiCommand /* arguments: newval */
{
public:
  Module_set_luminosity(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_luminosity";
  }

  string getDescription()
  {
    return "Changes the luminosity of the module informative leds.";
  }

  string getMoreInfo()
  {
    return "The parameter is a value between 0 and 100. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the luminosity of the module informative leds", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_luminosity(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the state of the localization beacon.
 *
 * @return either Y_BEACON_OFF or Y_BEACON_ON, according to the state of the localization beacon
 *
 * On failure, throws an exception or returns Y_BEACON_INVALID.
 */
class Module_get_beacon : public YapiCommand /* arguments: */
{
public:
  Module_get_beacon(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_beacon";
  }

  string getDescription()
  {
    return "Returns the state of the localization beacon.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_beacon();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Turns on or off the module localization beacon.
 *
 * @param newval : either Y_BEACON_OFF or Y_BEACON_ON
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_beacon : public YapiCommand /* arguments: newval */
{
public:
  Module_set_beacon(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_beacon";
  }

  string getDescription()
  {
    return "Turns on or off the module localization beacon.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_beacon(Y_BEACON_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the number of milliseconds spent since the module was powered on.
 *
 * @return an integer corresponding to the number of milliseconds spent since the module was powered on
 *
 * On failure, throws an exception or returns Y_UPTIME_INVALID.
 */
class Module_get_upTime : public YapiCommand /* arguments: */
{
public:
  Module_get_upTime(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_upTime";
  }

  string getDescription()
  {
    return "Returns the number of milliseconds spent since the module was powered on.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_upTime();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current consumed by the module on the USB bus, in milli-amps.
 *
 * @return an integer corresponding to the current consumed by the module on the USB bus, in milli-amps
 *
 * On failure, throws an exception or returns Y_USBCURRENT_INVALID.
 */
class Module_get_usbCurrent : public YapiCommand /* arguments: */
{
public:
  Module_get_usbCurrent(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_usbCurrent";
  }

  string getDescription()
  {
    return "Returns the current consumed by the module on the USB bus, in milli-amps.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_usbCurrent();
        char buf[32]; snprintf(buf, 32, "%d [mA]", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the remaining number of seconds before the module restarts, or zero when no
 * reboot has been scheduled.
 *
 * @return an integer corresponding to the remaining number of seconds before the module restarts, or zero when no
 *         reboot has been scheduled
 *
 * On failure, throws an exception or returns Y_REBOOTCOUNTDOWN_INVALID.
 */
class Module_get_rebootCountdown : public YapiCommand /* arguments: */
{
public:
  Module_get_rebootCountdown(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rebootCountdown";
  }

  string getDescription()
  {
    return "Returns the remaining number of seconds before the module restarts, or zero when noreboot has been scheduled.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rebootCountdown();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the value previously stored in this attribute.
 * On startup and after a device reboot, the value is always reset to zero.
 *
 * @return an integer corresponding to the value previously stored in this attribute
 *
 * On failure, throws an exception or returns Y_USERVAR_INVALID.
 */
class Module_get_userVar : public YapiCommand /* arguments: */
{
public:
  Module_get_userVar(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_userVar";
  }

  string getDescription()
  {
    return "Returns the value previously stored in this attribute.";
  }

  string getMoreInfo()
  {
    return "On startup and after a device reboot, the value is always reset to zero.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_userVar();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Stores a 32 bit value in the device RAM. This attribute is at programmer disposal,
 * should he need to store a state variable.
 * On startup and after a device reboot, the value is always reset to zero.
 *
 * @param newval : an integer
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_userVar : public YapiCommand /* arguments: newval */
{
public:
  Module_set_userVar(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_userVar";
  }

  string getDescription()
  {
    return "Stores a 32 bit value in the device RAM.";
  }

  string getMoreInfo()
  {
    return "This attribute is at programmer disposal, should he need to store a state variable. On startup and after a device reboot, the value is always reset to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_userVar(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackModule is YModuleValueCallback* (YModuleValueCallback)
// type of logCallback is YModuleLogCallback* (YModuleLogCallback)
// type of confChangeCallback is YModuleConfigChangeCallback* (YModuleConfigChangeCallback)
// type of beaconCallback is YModuleBeaconCallback* (YModuleBeaconCallback)
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
class apifun_Module_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Module_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
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
class apifun_Module_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Module_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
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
 * Saves current settings in the nonvolatile memory of the module.
 * Warning: the number of allowed save operations during a module life is
 * limited (about 100000 cycles). Do not call this function within a loop.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_saveToFlash : public YapiCommand /* arguments: */
{
public:
  apifun_Module_saveToFlash(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "saveToFlash";
  }

  string getDescription()
  {
    return "Saves current settings in the nonvolatile memory of the module.";
  }

  string getMoreInfo()
  {
    return "Warning: the number of allowed save operations during a module life is limited (about 100000 cycles). Do not call this function within a loop.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->saveToFlash();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reloads the settings stored in the nonvolatile memory, as
 * when the module is powered on.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_revertFromFlash : public YapiCommand /* arguments: */
{
public:
  apifun_Module_revertFromFlash(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "revertFromFlash";
  }

  string getDescription()
  {
    return "Reloads the settings stored in the nonvolatile memory, aswhen the module is powered on.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->revertFromFlash();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Schedules a simple module reboot after the given number of seconds.
 *
 * @param secBeforeReboot : number of seconds before rebooting
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_reboot : public YapiCommand /* arguments: secBeforeReboot */
{
public:
  apifun_Module_reboot(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "reboot";
  }

  string getDescription()
  {
    return "Schedules a simple module reboot after the given number of seconds.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "secBeforeReboot", "number of seconds before rebooting", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->reboot((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Schedules a module reboot into special firmware update mode.
 *
 * @param secBeforeReboot : number of seconds before rebooting
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_triggerFirmwareUpdate : public YapiCommand /* arguments: secBeforeReboot */
{
public:
  apifun_Module_triggerFirmwareUpdate(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "triggerFirmwareUpdate";
  }

  string getDescription()
  {
    return "Schedules a module reboot into special firmware update mode.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "secBeforeReboot", "number of seconds before rebooting", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->triggerFirmwareUpdate((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Triggers a configuration change callback, to check if they are supported or not.
 */
class apifun_Module_triggerConfigChangeCallback : public YapiCommand /* arguments: */
{
public:
  apifun_Module_triggerConfigChangeCallback(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "triggerConfigChangeCallback";
  }

  string getDescription()
  {
    return "Triggers a configuration change callback, to check if they are supported or not.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->triggerConfigChangeCallback();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Tests whether the byn file is valid for this module. This method is useful to test if the module
 * needs to be updated.
 * It is possible to pass a directory as argument instead of a file. In this case, this method returns
 * the path of the most recent
 * appropriate .byn file. If the parameter onlynew is true, the function discards firmwares that are older or
 * equal to the installed firmware.
 *
 * @param path : the path of a byn file or a directory that contains byn files
 * @param onlynew : returns only files that are strictly newer
 *
 * @return the path of the byn file to use or a empty string if no byn files matches the requirement
 *
 * On failure, throws an exception or returns a string that start with "error:".
 */
class apifun_Module_checkFirmware : public YapiCommand /* arguments: path onlynew */
{
public:
  apifun_Module_checkFirmware(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "checkFirmware";
  }

  string getDescription()
  {
    return "Tests whether the byn file is valid for this module.";
  }

  string getMoreInfo()
  {
    return "This method is useful to test if the module needs to be updated. It is possible to pass a directory as argument instead of a file. In this case, this method returns the path of the most recent appropriate .byn file. If the parameter onlynew is true, the function discards firmwares that are older or equal to the installed firmware.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "path", "the path of a byn file or a directory that contains byn files", "_STRING", false));
    res->push_back(new ArgumentDesc(BOOL_ARG, "onlynew", "returns only files that are strictly newer", "_BOOL", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->checkFirmware((*args)[0]->get_stringValue(),
                                                 (bool)(*args)[1]->get_boolValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Prepares a firmware update of the module. This method returns a YFirmwareUpdate object which
 * handles the firmware update process.
 *
 * @param path : the path of the .byn file to use.
 * @param force : true to force the firmware update even if some prerequisites appear not to be met
 *
 * @return a YFirmwareUpdate object or NULL on error.
 */
class apifun_Module_updateFirmwareEx : public YapiCommand /* arguments: path force */
{
public:
  apifun_Module_updateFirmwareEx(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "updateFirmwareEx";
  }

  string getDescription()
  {
    return "Prepares a firmware update of the module.";
  }

  string getMoreInfo()
  {
    return "This method returns a YFirmwareUpdate object which handles the firmware update process.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "path", "the path of the .byn file to use.", "_STRING", false));
    res->push_back(new ArgumentDesc(BOOL_ARG, "force", "true to force the firmware update even if some prerequisites appear not to be met", "_BOOL", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YFirmwareUpdate value = (*list)[i]->updateFirmwareEx((*args)[0]->get_stringValue(),
                                                             (bool)(*args)[1]->get_boolValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Prepares a firmware update of the module. This method returns a YFirmwareUpdate object which
 * handles the firmware update process.
 *
 * @param path : the path of the .byn file to use.
 *
 * @return a YFirmwareUpdate object or NULL on error.
 */
class apifun_Module_updateFirmware : public YapiCommand /* arguments: path */
{
public:
  apifun_Module_updateFirmware(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "updateFirmware";
  }

  string getDescription()
  {
    return "Prepares a firmware update of the module.";
  }

  string getMoreInfo()
  {
    return "This method returns a YFirmwareUpdate object which handles the firmware update process.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "path", "the path of the .byn file to use.", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YFirmwareUpdate value = (*list)[i]->updateFirmware((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns all the settings and uploaded files of the module. Useful to backup all the
 * logical names, calibrations parameters, and uploaded files of a device.
 *
 * @return a binary buffer with all the settings.
 *
 * On failure, throws an exception or returns an binary object of size 0.
 */
class apifun_Module_get_allSettings : public YapiCommand /* arguments: */
{
public:
  apifun_Module_get_allSettings(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_allSettings";
  }

  string getDescription()
  {
    return "Returns all the settings and uploaded files of the module.";
  }

  string getMoreInfo()
  {
    return "Useful to backup all the logical names, calibrations parameters, and uploaded files of a device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_allSettings();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Restores all the settings and uploaded files to the module.
 * This method is useful to restore all the logical names and calibrations parameters,
 * uploaded files etc. of a device from a backup.
 * Remember to call the saveToFlash() method of the module if the
 * modifications must be kept.
 *
 * @param settings : a binary buffer with all the settings.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_set_allSettingsAndFiles : public YapiCommand /* arguments: settings */
{
public:
  apifun_Module_set_allSettingsAndFiles(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_allSettingsAndFiles";
  }

  string getDescription()
  {
    return "Restores all the settings and uploaded files to the module.";
  }

  string getMoreInfo()
  {
    return "This method is useful to restore all the logical names and calibrations parameters, uploaded files etc. of a device from a backup. Remember to call \"YModule {target} saveToFlash\" if the modifications must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(BIN_ARG, "settings", "a binary buffer with all the settings.", "_BIN", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_allSettingsAndFiles((*args)[0]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Tests if the device includes a specific function. This method takes a function identifier
 * and returns a boolean.
 *
 * @param funcId : the requested function identifier
 *
 * @return true if the device has the function identifier
 */
class apifun_Module_hasFunction : public YapiCommand /* arguments: funcId */
{
public:
  apifun_Module_hasFunction(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "hasFunction";
  }

  string getDescription()
  {
    return "Tests if the device includes a specific function.";
  }

  string getMoreInfo()
  {
    return "This method takes a function identifier and returns a boolean.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "funcId", "the requested function identifier", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        bool value = (*list)[i]->hasFunction((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieve all hardware identifier that match the type passed in argument.
 *
 * @param funType : The type of function (Relay, LightSensor, Voltage,...)
 *
 * @return an array of strings.
 */
class apifun_Module_get_functionIds : public YapiCommand /* arguments: funType */
{
public:
  apifun_Module_get_functionIds(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_functionIds";
  }

  string getDescription()
  {
    return "Retrieve all hardware identifier that match the type passed in argument.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "funType", "The type of function (Relay, LightSensor, Voltage,...)", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<string> value = (*list)[i]->get_functionIds((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Restores all the settings of the device. Useful to restore all the logical names and calibrations parameters
 * of a module from a backup.Remember to call the saveToFlash() method of the module if the
 * modifications must be kept.
 *
 * @param settings : a binary buffer with all the settings.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_set_allSettings : public YapiCommand /* arguments: settings */
{
public:
  apifun_Module_set_allSettings(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_allSettings";
  }

  string getDescription()
  {
    return "Restores all the settings of the device.";
  }

  string getMoreInfo()
  {
    return "Useful to restore all the logical names and calibrations parameters of a module from a backup.Remember to call \"YModule {target} saveToFlash\" if the modifications must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(BIN_ARG, "settings", "a binary buffer with all the settings.", "_BIN", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_allSettings((*args)[0]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the unique hardware identifier of the module.
 * The unique hardware identifier is made of the device serial
 * number followed by string ".module".
 *
 * @return a string that uniquely identifies the module
 */
class apifun_Module_get_hardwareId : public YapiCommand /* arguments: */
{
public:
  apifun_Module_get_hardwareId(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_hardwareId";
  }

  string getDescription()
  {
    return "Returns the unique hardware identifier of the module.";
  }

  string getMoreInfo()
  {
    return "The unique hardware identifier is made of the device serial number followed by string \".module\".";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_hardwareId();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Downloads the specified built-in file and returns a binary buffer with its content.
 *
 * @param pathname : name of the new file to load
 *
 * @return a binary buffer with the file content
 *
 * On failure, throws an exception or returns  YAPI_INVALID_STRING.
 */
class apifun_Module_download : public YapiCommand /* arguments: pathname */
{
public:
  apifun_Module_download(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "download";
  }

  string getDescription()
  {
    return "Downloads the specified built-in file and returns a binary buffer with its content.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pathname", "name of the new file to load", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->download((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the icon of the module. The icon is a PNG image and does not
 * exceeds 1536 bytes.
 *
 * @return a binary buffer with module icon, in png format.
 *         On failure, throws an exception or returns  YAPI_INVALID_STRING.
 */
class apifun_Module_get_icon2d : public YapiCommand /* arguments: */
{
public:
  apifun_Module_get_icon2d(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_icon2d";
  }

  string getDescription()
  {
    return "Returns the icon of the module.";
  }

  string getMoreInfo()
  {
    return "The icon is a PNG image and does not exceeds 1536 bytes.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_icon2d();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a string with last logs of the module. This method return only
 * logs that are still in the module.
 *
 * @return a string with last logs of the module.
 *         On failure, throws an exception or returns  YAPI_INVALID_STRING.
 */
class apifun_Module_get_lastLogs : public YapiCommand /* arguments: */
{
public:
  apifun_Module_get_lastLogs(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_lastLogs";
  }

  string getDescription()
  {
    return "Returns a string with last logs of the module.";
  }

  string getMoreInfo()
  {
    return "This method return only logs that are still in the module.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_lastLogs();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds a text message to the device logs. This function is useful in
 * particular to trace the execution of HTTP callbacks. If a newline
 * is desired after the message, it must be included in the string.
 *
 * @param text : the string to append to the logs.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_log : public YapiCommand /* arguments: text */
{
public:
  apifun_Module_log(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "log";
  }

  string getDescription()
  {
    return "Adds a text message to the device logs.";
  }

  string getMoreInfo()
  {
    return "This function is useful in particular to trace the execution of HTTP callbacks. If a newline is desired after the message, it must be included in the string.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "text", "the string to append to the logs.", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->log((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of all the modules that are plugged into the current module.
 * This method only makes sense when called for a YoctoHub/VirtualHub.
 * Otherwise, an empty array will be returned.
 *
 * @return an array of strings containing the sub modules.
 */
class apifun_Module_get_subDevices : public YapiCommand /* arguments: */
{
public:
  apifun_Module_get_subDevices(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_subDevices";
  }

  string getDescription()
  {
    return "Returns a list of all the modules that are plugged into the current module.";
  }

  string getMoreInfo()
  {
    return "This method only makes sense when called for a YoctoHub/VirtualHub. Otherwise, an empty array will be returned.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<string> value = (*list)[i]->get_subDevices();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the serial number of the YoctoHub on which this module is connected.
 * If the module is connected by USB, or if the module is the root YoctoHub, an
 * empty string is returned.
 *
 * @return a string with the serial number of the YoctoHub or an empty string
 */
class apifun_Module_get_parentHub : public YapiCommand /* arguments: */
{
public:
  apifun_Module_get_parentHub(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_parentHub";
  }

  string getDescription()
  {
    return "Returns the serial number of the YoctoHub on which this module is connected.";
  }

  string getMoreInfo()
  {
    return "If the module is connected by USB, or if the module is the root YoctoHub, an empty string is returned.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_parentHub();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the URL used to access the module. If the module is connected by USB, the
 * string 'usb' is returned.
 *
 * @return a string with the URL of the module.
 */
class apifun_Module_get_url : public YapiCommand /* arguments: */
{
public:
  apifun_Module_get_url(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_url";
  }

  string getDescription()
  {
    return "Returns the URL used to access the module.";
  }

  string getMoreInfo()
  {
    return "If the module is connected by USB, the string 'usb' is returned.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_url();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YModule implementation)

//--- (generated code: YModule functions)
void YModuleCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YModule>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Module_get_productName(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Module_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_productId(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_productRelease(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_firmwareRelease(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_persistentSettings(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_luminosity(this)));
    cmdList->push_back((YapiCommand*) (new Module_set_luminosity(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_beacon(this)));
    cmdList->push_back((YapiCommand*) (new Module_set_beacon(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_upTime(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_usbCurrent(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_rebootCountdown(this)));
    cmdList->push_back((YapiCommand*) (new Module_get_userVar(this)));
    cmdList->push_back((YapiCommand*) (new Module_set_userVar(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_saveToFlash(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_revertFromFlash(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_reboot(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_triggerFirmwareUpdate(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_triggerConfigChangeCallback(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_checkFirmware(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_updateFirmwareEx(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_updateFirmware(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_allSettings(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_set_allSettingsAndFiles(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_hasFunction(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_functionIds(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_set_allSettings(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_hardwareId(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_download(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_icon2d(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_lastLogs(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_log(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_subDevices(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_parentHub(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_url(this)));
  }

//--- (end of generated code: YModule functions)
