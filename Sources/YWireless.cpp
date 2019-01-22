/*********************************************************************
 *
 * $Id: YWireless.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 * Implements commands to handle Wireless functions
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


#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "YWireless.h"
#include "yocto_api.h"
#include "yocto_wireless.h"

using namespace std;

//--- (generated code: YWireless definitions)

static const char *enumWLANState[] = {
    "DOWN",
    "SCANNING",
    "CONNECTED",
    "REJECTED",
    NULL
};

static const char *enumWLANSec[] = {
    "UNKNOWN",
    "OPEN",
    "WEP",
    "WPA",
    "WPA2",
    NULL
};

//--- (end of generated code: YWireless definitions)


//--- (generated code: YWireless implementation)
bool   YWirelessCmdLine::isModule(void)      { return false; }
string YWirelessCmdLine::YFunctionName(void) { return "YWireless"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of linkQuality is int (Percent)
// type of ssid is string (Text)
// type of channel is int (UInt31)
// type of security is int (WLANSec)
// type of message is string (YFSText)
// type of wlanConfig is string (WLANConfig)
// type of wlanState is int (WLANState)
/**
 * Returns the logical name of the wireless lan interface.
 *
 * @return a string corresponding to the logical name of the wireless lan interface
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Wireless_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Wireless_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the wireless lan interface.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
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
 * Changes the logical name of the wireless lan interface. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the wireless lan interface
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Wireless_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Wireless_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the wireless lan interface.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the wireless lan interface", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the wireless lan interface.
 *
 * @return a string corresponding to a short string representing the current state of the wireless lan interface
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Wireless_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  Wireless_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the wireless lan interface.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
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
 * Returns the link quality, expressed in percent.
 *
 * @return an integer corresponding to the link quality, expressed in percent
 *
 * On failure, throws an exception or returns Y_LINKQUALITY_INVALID.
 */
class Wireless_get_linkQuality : public YapiCommand /* arguments: */
{
public:
  Wireless_get_linkQuality(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_linkQuality";
  }

  string getDescription()
  {
    return "Returns the link quality, expressed in percent.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_linkQuality();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the wireless network name (SSID).
 *
 * @return a string corresponding to the wireless network name (SSID)
 *
 * On failure, throws an exception or returns Y_SSID_INVALID.
 */
class Wireless_get_ssid : public YapiCommand /* arguments: */
{
public:
  Wireless_get_ssid(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_ssid";
  }

  string getDescription()
  {
    return "Returns the wireless network name (SSID).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_ssid();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the 802.11 channel currently used, or 0 when the selected network has not been found.
 *
 * @return an integer corresponding to the 802.11 channel currently used, or 0 when the selected
 * network has not been found
 *
 * On failure, throws an exception or returns Y_CHANNEL_INVALID.
 */
class Wireless_get_channel : public YapiCommand /* arguments: */
{
public:
  Wireless_get_channel(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_channel";
  }

  string getDescription()
  {
    return "Returns the 802.";
  }

  string getMoreInfo()
  {
    return "11 channel currently used, or 0 when the selected network has not been found.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_channel();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the security algorithm used by the selected wireless network.
 *
 * @return a value among Y_SECURITY_UNKNOWN, Y_SECURITY_OPEN, Y_SECURITY_WEP, Y_SECURITY_WPA and
 * Y_SECURITY_WPA2 corresponding to the security algorithm used by the selected wireless network
 *
 * On failure, throws an exception or returns Y_SECURITY_INVALID.
 */
class Wireless_get_security : public YapiCommand /* arguments: */
{
public:
  Wireless_get_security(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_security";
  }

  string getDescription()
  {
    return "Returns the security algorithm used by the selected wireless network.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_security();
        string strval =  enumString(attrval,enumWLANSec);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the latest status message from the wireless interface.
 *
 * @return a string corresponding to the latest status message from the wireless interface
 *
 * On failure, throws an exception or returns Y_MESSAGE_INVALID.
 */
class Wireless_get_message : public YapiCommand /* arguments: */
{
public:
  Wireless_get_message(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_message";
  }

  string getDescription()
  {
    return "Returns the latest status message from the wireless interface.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_message();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current state of the wireless interface. The state Y_WLANSTATE_DOWN means that the
 * network interface is
 * not connected to a network. The state Y_WLANSTATE_SCANNING means that the network interface is
 * scanning available
 * frequencies. During this stage, the device is not reachable, and the network settings are not yet
 * applied. The state
 * Y_WLANSTATE_CONNECTED means that the network settings have been successfully applied ant that the
 * device is reachable
 * from the wireless network. If the device is configured to use ad-hoc or Soft AP mode, it means that
 * the wireless network
 * is up and that other devices can join the network. The state Y_WLANSTATE_REJECTED means that the
 * network interface has
 * not been able to join the requested network. The description of the error can be obtain with the
 * get_message() method.
 *
 * @return a value among Y_WLANSTATE_DOWN, Y_WLANSTATE_SCANNING, Y_WLANSTATE_CONNECTED and
 * Y_WLANSTATE_REJECTED corresponding to the current state of the wireless interface
 *
 * On failure, throws an exception or returns Y_WLANSTATE_INVALID.
 */
class Wireless_get_wlanState : public YapiCommand /* arguments: */
{
public:
  Wireless_get_wlanState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_wlanState";
  }

  string getDescription()
  {
    return "Returns the current state of the wireless interface.";
  }

  string getMoreInfo()
  {
    return "The state DOWN means that the network interface is not connected to a network. The state SCANNING means that the network interface is scanning available frequencies. During this stage, the device is not reachable, and the network settings are not yet applied. The state CONNECTED means that the network settings have been successfully applied ant that the device is reachable from the wireless network. If the device is configured to use ad-hoc or Soft AP mode, it means that the wireless network is up and that other devices can join the network. The state REJECTED means that the network interface has not been able to join the requested network. The description of the error can be obtain with the get_message() method.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_wlanState();
        string strval =  enumString(attrval,enumWLANState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackWireless is YWirelessValueCallback* (YWirelessValueCallback)
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
class apifun_Wireless_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Wireless_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
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
class apifun_Wireless_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Wireless_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
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
class apifun_Wireless_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_Wireless_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Triggers a scan of the wireless frequency and builds the list of available networks.
 * The scan forces a disconnection from the current network. At then end of the process, the
 * the network interface attempts to reconnect to the previous network. During the scan, the wlanState
 * switches to Y_WLANSTATE_DOWN, then to Y_WLANSTATE_SCANNING. When the scan is completed,
 * get_wlanState() returns either Y_WLANSTATE_DOWN or Y_WLANSTATE_SCANNING. At this
 * point, the list of detected network can be retrieved with the get_detectedWlans() method.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Wireless_startWlanScan : public YapiCommand /* arguments: */
{
public:
  apifun_Wireless_startWlanScan(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "startWlanScan";
  }

  string getDescription()
  {
    return "Triggers a scan of the wireless frequency and builds the list of available networks.";
  }

  string getMoreInfo()
  {
    return "The scan forces a disconnection from the current network. At then end of the process, the the network interface attempts to reconnect to the previous network. During the scan, the wlanState switches to WLANSTATE_DOWN, then to WLANSTATE_SCANNING. When the scan is completed, get_wlanState() returns either WLANSTATE_DOWN or WLANSTATE_SCANNING. At this point, the list of detected network can be retrieved with the get_detectedWlans() method.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->startWlanScan();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the configuration of the wireless lan interface to connect to an existing
 * access point (infrastructure mode).
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 *
 * @param ssid : the name of the network to connect to
 * @param securityKey : the network key, as a character string
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Wireless_joinNetwork : public YapiCommand /* arguments: ssid securityKey */
{
public:
  apifun_Wireless_joinNetwork(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "joinNetwork";
  }

  string getDescription()
  {
    return "Changes the configuration of the wireless lan interface to connect to an existingaccess point (infrastructure mode).";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "ssid", "the name of the network to connect to", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "securityKey", "the network key, as a character string", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->joinNetwork((*args)[0]->get_stringValue(),
                                (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the configuration of the wireless lan interface to create an ad-hoc
 * wireless network, without using an access point. On the YoctoHub-Wireless-g,
 * it is best to use softAPNetworkInstead(), which emulates an access point
 * (Soft AP) which is more efficient and more widely supported than ad-hoc networks.
 *
 * When a security key is specified for an ad-hoc network, the network is protected
 * by a WEP40 key (5 characters or 10 hexadecimal digits) or WEP128 key (13 characters
 * or 26 hexadecimal digits). It is recommended to use a well-randomized WEP128 key
 * using 26 hexadecimal digits to maximize security.
 * Remember to call the saveToFlash() method and then to reboot the module
 * to apply this setting.
 *
 * @param ssid : the name of the network to connect to
 * @param securityKey : the network key, as a character string
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Wireless_adhocNetwork : public YapiCommand /* arguments: ssid securityKey */
{
public:
  apifun_Wireless_adhocNetwork(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "adhocNetwork";
  }

  string getDescription()
  {
    return "Changes the configuration of the wireless lan interface to create an ad-hocwireless network, without using an access point.";
  }

  string getMoreInfo()
  {
    return "On the YoctoHub-Wireless-g, it is best to use softAPNetworkInstead(), which emulates an access point (Soft AP) which is more efficient and more widely supported than ad-hoc networks.\nWhen a security key is specified for an ad-hoc network, the network is protected by a WEP40 key (5 characters or 10 hexadecimal digits) or WEP128 key (13 characters or 26 hexadecimal digits). It is recommended to use a well-randomized WEP128 key using 26 hexadecimal digits to maximize security. Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "ssid", "the name of the network to connect to", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "securityKey", "the network key, as a character string", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->adhocNetwork((*args)[0]->get_stringValue(),
                                 (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the configuration of the wireless lan interface to create a new wireless
 * network by emulating a WiFi access point (Soft AP). This function can only be
 * used with the YoctoHub-Wireless-g.
 *
 * When a security key is specified for a SoftAP network, the network is protected
 * by a WEP40 key (5 characters or 10 hexadecimal digits) or WEP128 key (13 characters
 * or 26 hexadecimal digits). It is recommended to use a well-randomized WEP128 key
 * using 26 hexadecimal digits to maximize security.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 *
 * @param ssid : the name of the network to connect to
 * @param securityKey : the network key, as a character string
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Wireless_softAPNetwork : public YapiCommand /* arguments: ssid securityKey */
{
public:
  apifun_Wireless_softAPNetwork(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "softAPNetwork";
  }

  string getDescription()
  {
    return "Changes the configuration of the wireless lan interface to create a new wirelessnetwork by emulating a WiFi access point (Soft AP).";
  }

  string getMoreInfo()
  {
    return "This function can only be used with the YoctoHub-Wireless-g.\nWhen a security key is specified for a SoftAP network, the network is protected by a WEP40 key (5 characters or 10 hexadecimal digits) or WEP128 key (13 characters or 26 hexadecimal digits). It is recommended to use a well-randomized WEP128 key using 26 hexadecimal digits to maximize security. Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "ssid", "the name of the network to connect to", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "securityKey", "the network key, as a character string", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->softAPNetwork((*args)[0]->get_stringValue(),
                                  (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of YWlanRecord objects that describe detected Wireless networks.
 * This list is not updated when the module is already connected to an access point (infrastructure mode).
 * To force an update of this list, startWlanScan() must be called.
 * Note that an languages without garbage collections, the returned list must be freed by the caller.
 *
 * @return a list of YWlanRecord objects, containing the SSID, channel,
 *         link quality and the type of security of the wireless network.
 *
 * On failure, throws an exception or returns an empty list.
 */
class apifun_Wireless_get_detectedWlans : public YapiCommand /* arguments: */
{
public:
  apifun_Wireless_get_detectedWlans(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_detectedWlans";
  }

  string getDescription()
  {
    return "Returns a list of YWlanRecord objects that describe detected Wireless networks.";
  }

  string getMoreInfo()
  {
    return "This list is not updated when the module is already connected to an access point (infrastructure mode). To force an update of this list, startWlanScan() must be called. Note that an languages without garbage collections, the returned list must be freed by the caller.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YWireless*>* list = enumerateTargets<YWireless>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<YWlanRecord> value = (*list)[i]->get_detectedWlans();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YWireless implementation)

//--- (generated code: YWireless functions)
void YWirelessCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YWireless>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Wireless_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_get_linkQuality(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_get_ssid(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_get_channel(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_get_security(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_get_message(this)));
    cmdList->push_back((YapiCommand*) (new Wireless_get_wlanState(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_startWlanScan(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_joinNetwork(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_adhocNetwork(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_softAPNetwork(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Wireless_get_detectedWlans(this)));
  }

//--- (end of generated code: YWireless functions)
