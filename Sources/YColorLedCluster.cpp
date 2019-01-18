/*********************************************************************
 *
 *  $Id: YColorLedCluster.cpp 33710 2018-12-14 14:18:53Z seb $
 *
 *  Implements commands to handle ColorLedCluster functions
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
#include "YColorLedCluster.h"
#include "yocto_api.h"
#include "yocto_colorledcluster.h"

using namespace std;

//--- (YColorLedCluster definitions)

static const char *enumLedType[] = {
    "RGB",
    "RGBW",
    NULL
};

//--- (end of YColorLedCluster definitions)


//--- (YColorLedCluster implementation)
bool   YColorLedClusterCmdLine::isModule(void)      { return false; }
string YColorLedClusterCmdLine::YFunctionName(void) { return "YColorLedCluster"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of activeLedCount is int (UInt31)
// type of ledType is int (LedType)
// type of maxLedCount is int (UInt31)
// type of blinkSeqMaxCount is int (UInt31)
// type of blinkSeqMaxSize is int (UInt31)
// type of command is string (Text)
/**
 * Returns the logical name of the RGB LED cluster.
 *
 * @return a string corresponding to the logical name of the RGB LED cluster
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class ColorLedCluster_get_logicalName : public YapiCommand /* arguments: */
{
public:
  ColorLedCluster_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the RGB LED cluster.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
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
 * Changes the logical name of the RGB LED cluster. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the RGB LED cluster
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLedCluster_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  ColorLedCluster_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the RGB LED cluster.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the RGB LED cluster", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the RGB LED cluster.
 *
 * @return a string corresponding to a short string representing the current state of the RGB LED cluster
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class ColorLedCluster_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  ColorLedCluster_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the RGB LED cluster.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
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
 * Returns the number of LEDs currently handled by the device.
 *
 * @return an integer corresponding to the number of LEDs currently handled by the device
 *
 * On failure, throws an exception or returns Y_ACTIVELEDCOUNT_INVALID.
 */
class ColorLedCluster_get_activeLedCount : public YapiCommand /* arguments: */
{
public:
  ColorLedCluster_get_activeLedCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_activeLedCount";
  }

  string getDescription()
  {
    return "Returns the number of LEDs currently handled by the device.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_activeLedCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the number of LEDs currently handled by the device.
 *
 * @param newval : an integer corresponding to the number of LEDs currently handled by the device
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLedCluster_set_activeLedCount : public YapiCommand /* arguments: newval */
{
public:
  ColorLedCluster_set_activeLedCount(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_activeLedCount";
  }

  string getDescription()
  {
    return "Changes the number of LEDs currently handled by the device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the number of LEDs currently handled by the device", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_activeLedCount(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the RGB LED type currently handled by the device.
 *
 * @return either Y_LEDTYPE_RGB or Y_LEDTYPE_RGBW, according to the RGB LED type currently handled by the device
 *
 * On failure, throws an exception or returns Y_LEDTYPE_INVALID.
 */
class ColorLedCluster_get_ledType : public YapiCommand /* arguments: */
{
public:
  ColorLedCluster_get_ledType(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_ledType";
  }

  string getDescription()
  {
    return "Returns the RGB LED type currently handled by the device.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_ledType();
        string strval =  enumString(attrval,enumLedType);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the RGB LED type currently handled by the device.
 *
 * @param newval : either Y_LEDTYPE_RGB or Y_LEDTYPE_RGBW, according to the RGB LED type currently
 * handled by the device
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLedCluster_set_ledType : public YapiCommand /* arguments: newval */
{
public:
  ColorLedCluster_set_ledType(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_ledType";
  }

  string getDescription()
  {
    return "Changes the RGB LED type currently handled by the device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either RGB or RGBW, according to the RGB LED type currently handled by the device", "RGB=0,RGBW=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_ledType(Y_LEDTYPE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximum number of LEDs that the device can handle.
 *
 * @return an integer corresponding to the maximum number of LEDs that the device can handle
 *
 * On failure, throws an exception or returns Y_MAXLEDCOUNT_INVALID.
 */
class ColorLedCluster_get_maxLedCount : public YapiCommand /* arguments: */
{
public:
  ColorLedCluster_get_maxLedCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_maxLedCount";
  }

  string getDescription()
  {
    return "Returns the maximum number of LEDs that the device can handle.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_maxLedCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the maximum number of sequences that the device can handle.
 *
 * @return an integer corresponding to the maximum number of sequences that the device can handle
 *
 * On failure, throws an exception or returns Y_BLINKSEQMAXCOUNT_INVALID.
 */
class ColorLedCluster_get_blinkSeqMaxCount : public YapiCommand /* arguments: */
{
public:
  ColorLedCluster_get_blinkSeqMaxCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqMaxCount";
  }

  string getDescription()
  {
    return "Returns the maximum number of sequences that the device can handle.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_blinkSeqMaxCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the maximum length of sequences.
 *
 * @return an integer corresponding to the maximum length of sequences
 *
 * On failure, throws an exception or returns Y_BLINKSEQMAXSIZE_INVALID.
 */
class ColorLedCluster_get_blinkSeqMaxSize : public YapiCommand /* arguments: */
{
public:
  ColorLedCluster_get_blinkSeqMaxSize(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqMaxSize";
  }

  string getDescription()
  {
    return "Returns the maximum length of sequences.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_blinkSeqMaxSize();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackColorLedCluster is YColorLedClusterValueCallback* (YColorLedClusterValueCallback)
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
class apifun_ColorLedCluster_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLedCluster_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
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
class apifun_ColorLedCluster_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLedCluster_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
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
 * Changes the current color of consecutive LEDs in the cluster, using a RGB color. Encoding is done
 * as follows: 0xRRGGBB.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param rgbValue :  new color.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_rgbColor : public YapiCommand /* arguments: ledIndex count rgbValue */
{
public:
  apifun_ColorLedCluster_set_rgbColor(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_rgbColor";
  }

  string getDescription()
  {
    return "Changes the current color of consecutive LEDs in the cluster, using a RGB color.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xRRGGBB.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "rgbValue", "new color.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_rgbColor((int)(*args)[0]->get_intValue(),
                                 (int)(*args)[1]->get_intValue(),
                                 (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the  color at device startup of consecutive LEDs in the cluster, using a RGB color.
 * Encoding is done as follows: 0xRRGGBB.
 * Don't forget to call saveLedsConfigAtPowerOn() to make sure the modification is saved in the device
 * flash memory.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param rgbValue :  new color.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_rgbColorAtPowerOn : public YapiCommand /* arguments: ledIndex count rgbValue */
{
public:
  apifun_ColorLedCluster_set_rgbColorAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_rgbColorAtPowerOn";
  }

  string getDescription()
  {
    return "Changes the color at device startup of consecutive LEDs in the cluster, using a RGB color.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xRRGGBB. Don't forget to call saveLedsConfigAtPowerOn() to make sure the modification is saved in the device flash memory.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "rgbValue", "new color.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_rgbColorAtPowerOn((int)(*args)[0]->get_intValue(),
                                          (int)(*args)[1]->get_intValue(),
                                          (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the  color at device startup of consecutive LEDs in the cluster, using a HSL color.
 * Encoding is done as follows: 0xHHSSLL.
 * Don't forget to call saveLedsConfigAtPowerOn() to make sure the modification is saved in the device
 * flash memory.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param hslValue :  new color.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_hslColorAtPowerOn : public YapiCommand /* arguments: ledIndex count hslValue */
{
public:
  apifun_ColorLedCluster_set_hslColorAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_hslColorAtPowerOn";
  }

  string getDescription()
  {
    return "Changes the color at device startup of consecutive LEDs in the cluster, using a HSL color.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xHHSSLL. Don't forget to call saveLedsConfigAtPowerOn() to make sure the modification is saved in the device flash memory.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "hslValue", "new color.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_hslColorAtPowerOn((int)(*args)[0]->get_intValue(),
                                          (int)(*args)[1]->get_intValue(),
                                          (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the current color of consecutive LEDs in the cluster, using a HSL color. Encoding is done
 * as follows: 0xHHSSLL.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param hslValue :  new color.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_hslColor : public YapiCommand /* arguments: ledIndex count hslValue */
{
public:
  apifun_ColorLedCluster_set_hslColor(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_hslColor";
  }

  string getDescription()
  {
    return "Changes the current color of consecutive LEDs in the cluster, using a HSL color.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xHHSSLL.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "hslValue", "new color.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_hslColor((int)(*args)[0]->get_intValue(),
                                 (int)(*args)[1]->get_intValue(),
                                 (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Allows you to modify the current color of a group of adjacent LEDs to another color, in a seamless and
 * autonomous manner. The transition is performed in the RGB space.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param rgbValue :  new color (0xRRGGBB).
 * @param delay    :  transition duration in ms
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_rgb_move : public YapiCommand /* arguments: ledIndex count rgbValue delay */
{
public:
  apifun_ColorLedCluster_rgb_move(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "rgb_move";
  }

  string getDescription()
  {
    return "Allows you to modify the current color of a group of adjacent LEDs to another color, in a seamless andautonomous manner.";
  }

  string getMoreInfo()
  {
    return "The transition is performed in the RGB space.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "rgbValue", "new color (0xRRGGBB).", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->rgb_move((int)(*args)[0]->get_intValue(),
                             (int)(*args)[1]->get_intValue(),
                             (int)(*args)[2]->get_intValue(),
                             (int)(*args)[3]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Allows you to modify the current color of a group of adjacent LEDs  to another color, in a seamless and
 * autonomous manner. The transition is performed in the HSL space. In HSL, hue is a circular
 * value (0..360°). There are always two paths to perform the transition: by increasing
 * or by decreasing the hue. The module selects the shortest transition.
 * If the difference is exactly 180°, the module selects the transition which increases
 * the hue.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param hslValue :  new color (0xHHSSLL).
 * @param delay    :  transition duration in ms
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_hsl_move : public YapiCommand /* arguments: ledIndex count hslValue delay */
{
public:
  apifun_ColorLedCluster_hsl_move(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "hsl_move";
  }

  string getDescription()
  {
    return "Allows you to modify the current color of a group of adjacent LEDs to another color, in a seamless andautonomous manner.";
  }

  string getMoreInfo()
  {
    return "The transition is performed in the HSL space. In HSL, hue is a circular value (0..360\302\260). There are always two paths to perform the transition: by increasing or by decreasing the hue. The module selects the shortest transition. If the difference is exactly 180\302\260, the module selects the transition which increases the hue.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "hslValue", "new color (0xHHSSLL).", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->hsl_move((int)(*args)[0]->get_intValue(),
                             (int)(*args)[1]->get_intValue(),
                             (int)(*args)[2]->get_intValue(),
                             (int)(*args)[3]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds an RGB transition to a sequence. A sequence is a transition list, which can
 * be executed in loop by a group of LEDs.  Sequences are persistent and are saved
 * in the device flash memory as soon as the saveBlinkSeq() method is called.
 *
 * @param seqIndex :  sequence index.
 * @param rgbValue :  target color (0xRRGGBB)
 * @param delay    :  transition duration in ms
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_addRgbMoveToBlinkSeq : public YapiCommand /* arguments: seqIndex rgbValue delay */
{
public:
  apifun_ColorLedCluster_addRgbMoveToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "addRgbMoveToBlinkSeq";
  }

  string getDescription()
  {
    return "Adds an RGB transition to a sequence.";
  }

  string getMoreInfo()
  {
    return "A sequence is a transition list, which can be executed in loop by a group of LEDs. Sequences are persistent and are saved in the device flash memory as soon as the saveBlinkSeq() method is called.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "rgbValue", "target color (0xRRGGBB)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addRgbMoveToBlinkSeq((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue(),
                                         (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds an HSL transition to a sequence. A sequence is a transition list, which can
 * be executed in loop by an group of LEDs.  Sequences are persistent and are saved
 * in the device flash memory as soon as the saveBlinkSeq() method is called.
 *
 * @param seqIndex : sequence index.
 * @param hslValue : target color (0xHHSSLL)
 * @param delay    : transition duration in ms
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_addHslMoveToBlinkSeq : public YapiCommand /* arguments: seqIndex hslValue delay */
{
public:
  apifun_ColorLedCluster_addHslMoveToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "addHslMoveToBlinkSeq";
  }

  string getDescription()
  {
    return "Adds an HSL transition to a sequence.";
  }

  string getMoreInfo()
  {
    return "A sequence is a transition list, which can be executed in loop by an group of LEDs. Sequences are persistent and are saved in the device flash memory as soon as the saveBlinkSeq() method is called.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "hslValue", "target color (0xHHSSLL)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addHslMoveToBlinkSeq((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue(),
                                         (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds a mirror ending to a sequence. When the sequence will reach the end of the last
 * transition, its running speed will automatically be reversed so that the sequence plays
 * in the reverse direction, like in a mirror. After the first transition of the sequence
 * is played at the end of the reverse execution, the sequence starts again in
 * the initial direction.
 *
 * @param seqIndex : sequence index.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_addMirrorToBlinkSeq : public YapiCommand /* arguments: seqIndex */
{
public:
  apifun_ColorLedCluster_addMirrorToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "addMirrorToBlinkSeq";
  }

  string getDescription()
  {
    return "Adds a mirror ending to a sequence.";
  }

  string getMoreInfo()
  {
    return "When the sequence will reach the end of the last transition, its running speed will automatically be reversed so that the sequence plays in the reverse direction, like in a mirror. After the first transition of the sequence is played at the end of the reverse execution, the sequence starts again in the initial direction.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addMirrorToBlinkSeq((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds to a sequence a jump to another sequence. When a pixel will reach this jump,
 * it will be automatically relinked to the new sequence, and will run it starting
 * from the beginning.
 *
 * @param seqIndex : sequence index.
 * @param linkSeqIndex : index of the sequence to chain.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_addJumpToBlinkSeq : public YapiCommand /* arguments: seqIndex linkSeqIndex */
{
public:
  apifun_ColorLedCluster_addJumpToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "addJumpToBlinkSeq";
  }

  string getDescription()
  {
    return "Adds to a sequence a jump to another sequence.";
  }

  string getMoreInfo()
  {
    return "When a pixel will reach this jump, it will be automatically relinked to the new sequence, and will run it starting from the beginning.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "linkSeqIndex", "index of the sequence to chain.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addJumpToBlinkSeq((int)(*args)[0]->get_intValue(),
                                      (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds a to a sequence a hard stop code. When a pixel will reach this stop code,
 * instead of restarting the sequence in a loop it will automatically be unlinked
 * from the sequence.
 *
 * @param seqIndex : sequence index.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_addUnlinkToBlinkSeq : public YapiCommand /* arguments: seqIndex */
{
public:
  apifun_ColorLedCluster_addUnlinkToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "addUnlinkToBlinkSeq";
  }

  string getDescription()
  {
    return "Adds a to a sequence a hard stop code.";
  }

  string getMoreInfo()
  {
    return "When a pixel will reach this stop code, instead of restarting the sequence in a loop it will automatically be unlinked from the sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addUnlinkToBlinkSeq((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Links adjacent LEDs to a specific sequence. These LEDs start to execute
 * the sequence as soon as  startBlinkSeq is called. It is possible to add an offset
 * in the execution: that way we  can have several groups of LED executing the same
 * sequence, with a  temporal offset. A LED cannot be linked to more than one sequence.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param seqIndex :  sequence index.
 * @param offset   :  execution offset in ms.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_linkLedToBlinkSeq : public YapiCommand /* arguments: ledIndex count seqIndex offset */
{
public:
  apifun_ColorLedCluster_linkLedToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "linkLedToBlinkSeq";
  }

  string getDescription()
  {
    return "Links adjacent LEDs to a specific sequence.";
  }

  string getMoreInfo()
  {
    return "These LEDs start to execute the sequence as soon as startBlinkSeq is called. It is possible to add an offset in the execution: that way we can have several groups of LED executing the same sequence, with a temporal offset. A LED cannot be linked to more than one sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "offset", "execution offset in ms.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->linkLedToBlinkSeq((int)(*args)[0]->get_intValue(),
                                      (int)(*args)[1]->get_intValue(),
                                      (int)(*args)[2]->get_intValue(),
                                      (int)(*args)[3]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Links adjacent LEDs to a specific sequence at device power-on. Don't forget to configure
 * the sequence auto start flag as well and call saveLedsConfigAtPowerOn(). It is possible to add an offset
 * in the execution: that way we  can have several groups of LEDs executing the same
 * sequence, with a  temporal offset. A LED cannot be linked to more than one sequence.
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param seqIndex :  sequence index.
 * @param offset   :  execution offset in ms.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_linkLedToBlinkSeqAtPowerOn : public YapiCommand /* arguments: ledIndex count seqIndex offset */
{
public:
  apifun_ColorLedCluster_linkLedToBlinkSeqAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "linkLedToBlinkSeqAtPowerOn";
  }

  string getDescription()
  {
    return "Links adjacent LEDs to a specific sequence at device power-on.";
  }

  string getMoreInfo()
  {
    return "Don't forget to configure the sequence auto start flag as well and call saveLedsConfigAtPowerOn(). It is possible to add an offset in the execution: that way we can have several groups of LEDs executing the same sequence, with a temporal offset. A LED cannot be linked to more than one sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "offset", "execution offset in ms.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->linkLedToBlinkSeqAtPowerOn((int)(*args)[0]->get_intValue(),
                                               (int)(*args)[1]->get_intValue(),
                                               (int)(*args)[2]->get_intValue(),
                                               (int)(*args)[3]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Links adjacent LEDs to a specific sequence. These LED start to execute
 * the sequence as soon as  startBlinkSeq is called. This function automatically
 * introduces a shift between LEDs so that the specified number of sequence periods
 * appears on the group of LEDs (wave effect).
 *
 * @param ledIndex :  index of the first affected LED.
 * @param count    :  affected LED count.
 * @param seqIndex :  sequence index.
 * @param periods  :  number of periods to show on LEDs.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_linkLedToPeriodicBlinkSeq : public YapiCommand /* arguments: ledIndex count seqIndex periods */
{
public:
  apifun_ColorLedCluster_linkLedToPeriodicBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "linkLedToPeriodicBlinkSeq";
  }

  string getDescription()
  {
    return "Links adjacent LEDs to a specific sequence.";
  }

  string getMoreInfo()
  {
    return "These LED start to execute the sequence as soon as startBlinkSeq is called. This function automatically introduces a shift between LEDs so that the specified number of sequence periods appears on the group of LEDs (wave effect).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "sequence index.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "periods", "number of periods to show on LEDs.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->linkLedToPeriodicBlinkSeq((int)(*args)[0]->get_intValue(),
                                              (int)(*args)[1]->get_intValue(),
                                              (int)(*args)[2]->get_intValue(),
                                              (int)(*args)[3]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Unlinks adjacent LEDs from a  sequence.
 *
 * @param ledIndex  :  index of the first affected LED.
 * @param count     :  affected LED count.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_unlinkLedFromBlinkSeq : public YapiCommand /* arguments: ledIndex count */
{
public:
  apifun_ColorLedCluster_unlinkLedFromBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "unlinkLedFromBlinkSeq";
  }

  string getDescription()
  {
    return "Unlinks adjacent LEDs from a sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first affected LED.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "affected LED count.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->unlinkLedFromBlinkSeq((int)(*args)[0]->get_intValue(),
                                          (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts a sequence execution: every LED linked to that sequence starts to
 * run it in a loop. Note that a sequence with a zero duration can't be started.
 *
 * @param seqIndex :  index of the sequence to start.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_startBlinkSeq : public YapiCommand /* arguments: seqIndex */
{
public:
  apifun_ColorLedCluster_startBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "startBlinkSeq";
  }

  string getDescription()
  {
    return "Starts a sequence execution: every LED linked to that sequence starts torun it in a loop.";
  }

  string getMoreInfo()
  {
    return "Note that a sequence with a zero duration can't be started.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the sequence to start.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->startBlinkSeq((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops a sequence execution. If started again, the execution
 * restarts from the beginning.
 *
 * @param seqIndex :  index of the sequence to stop.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_stopBlinkSeq : public YapiCommand /* arguments: seqIndex */
{
public:
  apifun_ColorLedCluster_stopBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "stopBlinkSeq";
  }

  string getDescription()
  {
    return "Stops a sequence execution.";
  }

  string getMoreInfo()
  {
    return "If started again, the execution restarts from the beginning.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the sequence to stop.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->stopBlinkSeq((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops a sequence execution and resets its contents. LEDs linked to this
 * sequence are not automatically updated anymore.
 *
 * @param seqIndex :  index of the sequence to reset
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_resetBlinkSeq : public YapiCommand /* arguments: seqIndex */
{
public:
  apifun_ColorLedCluster_resetBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "resetBlinkSeq";
  }

  string getDescription()
  {
    return "Stops a sequence execution and resets its contents.";
  }

  string getMoreInfo()
  {
    return "LEDs linked to this sequence are not automatically updated anymore.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the sequence to reset", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetBlinkSeq((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Configures a sequence to make it start automatically at device
 * startup. Note that a sequence with a zero duration can't be started.
 * Don't forget to call saveBlinkSeq() to make sure the
 * modification is saved in the device flash memory.
 *
 * @param seqIndex :  index of the sequence to reset.
 * @param autostart : 0 to keep the sequence turned off and 1 to start it automatically.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_blinkSeqStateAtPowerOn : public YapiCommand /* arguments: seqIndex autostart */
{
public:
  apifun_ColorLedCluster_set_blinkSeqStateAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_blinkSeqStateAtPowerOn";
  }

  string getDescription()
  {
    return "Configures a sequence to make it start automatically at devicestartup.";
  }

  string getMoreInfo()
  {
    return "Note that a sequence with a zero duration can't be started. Don't forget to call saveBlinkSeq() to make sure the modification is saved in the device flash memory.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the sequence to reset.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "autostart", "0 to keep the sequence turned off and 1 to start it automatically.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_blinkSeqStateAtPowerOn((int)(*args)[0]->get_intValue(),
                                               (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the execution speed of a sequence. The natural execution speed is 1000 per
 * thousand. If you configure a slower speed, you can play the sequence in slow-motion.
 * If you set a negative speed, you can play the sequence in reverse direction.
 *
 * @param seqIndex :  index of the sequence to start.
 * @param speed :     sequence running speed (-1000...1000).
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_blinkSeqSpeed : public YapiCommand /* arguments: seqIndex speed */
{
public:
  apifun_ColorLedCluster_set_blinkSeqSpeed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_blinkSeqSpeed";
  }

  string getDescription()
  {
    return "Changes the execution speed of a sequence.";
  }

  string getMoreInfo()
  {
    return "The natural execution speed is 1000 per thousand. If you configure a slower speed, you can play the sequence in slow-motion. If you set a negative speed, you can play the sequence in reverse direction.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the sequence to start.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "speed", "sequence running speed (-1000...1000).", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_blinkSeqSpeed((int)(*args)[0]->get_intValue(),
                                      (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Saves the LEDs power-on configuration. This includes the start-up color or
 * sequence binding for all LEDs. Warning: if some LEDs are linked to a sequence, the
 * method saveBlinkSeq() must also be called to save the sequence definition.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_saveLedsConfigAtPowerOn : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLedCluster_saveLedsConfigAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "saveLedsConfigAtPowerOn";
  }

  string getDescription()
  {
    return "Saves the LEDs power-on configuration.";
  }

  string getMoreInfo()
  {
    return "This includes the start-up color or sequence binding for all LEDs. Warning: if some LEDs are linked to a sequence, the method saveBlinkSeq() must also be called to save the sequence definition.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->saveLedsConfigAtPowerOn();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Saves the definition of a sequence. Warning: only sequence steps and flags are saved.
 * to save the LEDs startup bindings, the method saveLedsConfigAtPowerOn()
 * must be called.
 *
 * @param seqIndex :  index of the sequence to start.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_saveBlinkSeq : public YapiCommand /* arguments: seqIndex */
{
public:
  apifun_ColorLedCluster_saveBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "saveBlinkSeq";
  }

  string getDescription()
  {
    return "Saves the definition of a sequence.";
  }

  string getMoreInfo()
  {
    return "Warning: only sequence steps and flags are saved. to save the LEDs startup bindings, the method saveLedsConfigAtPowerOn() must be called.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the sequence to start.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->saveBlinkSeq((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a binary buffer to the LED RGB buffer, as is.
 * First three bytes are RGB components for LED specified as parameter, the
 * next three bytes for the next LED, etc.
 *
 * @param ledIndex : index of the first LED which should be updated
 * @param buff : the binary buffer to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_rgbColorBuffer : public YapiCommand /* arguments: ledIndex buff */
{
public:
  apifun_ColorLedCluster_set_rgbColorBuffer(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_rgbColorBuffer";
  }

  string getDescription()
  {
    return "Sends a binary buffer to the LED RGB buffer, as is.";
  }

  string getMoreInfo()
  {
    return "First three bytes are RGB components for LED specified as parameter, the next three bytes for the next LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be updated", "_INT", false));
    res->push_back(new ArgumentDesc(BIN_ARG, "buff", "the binary buffer to send", "_BIN", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_rgbColorBuffer((int)(*args)[0]->get_intValue(),
                                       (*args)[1]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends 24bit RGB colors (provided as a list of integers) to the LED RGB buffer, as is.
 * The first number represents the RGB value of the LED specified as parameter, the second
 * number represents the RGB value of the next LED, etc.
 *
 * @param ledIndex : index of the first LED which should be updated
 * @param rgbList : a list of 24bit RGB codes, in the form 0xRRGGBB
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_rgbColorArray : public YapiCommand /* arguments: ledIndex rgbList */
{
public:
  apifun_ColorLedCluster_set_rgbColorArray(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_rgbColorArray";
  }

  string getDescription()
  {
    return "Sends 24bit RGB colors (provided as a list of integers) to the LED RGB buffer, as is.";
  }

  string getMoreInfo()
  {
    return "The first number represents the RGB value of the LED specified as parameter, the second number represents the RGB value of the next LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be updated", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "rgbList", "a list of 24bit RGB codes, in the form 0xRRGGBB", "_INTARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_rgbColorArray((int)(*args)[0]->get_intValue(),
                                      (*args)[1]->get_intArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets up a smooth RGB color transition to the specified pixel-by-pixel list of RGB
 * color codes. The first color code represents the target RGB value of the first LED,
 * the next color code represents the target value of the next LED, etc.
 *
 * @param ledIndex : index of the first LED which should be updated
 * @param rgbList : a list of target 24bit RGB codes, in the form 0xRRGGBB
 * @param delay   : transition duration in ms
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_rgbArrayOfs_move : public YapiCommand /* arguments: ledIndex rgbList delay */
{
public:
  apifun_ColorLedCluster_rgbArrayOfs_move(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "rgbArrayOfs_move";
  }

  string getDescription()
  {
    return "Sets up a smooth RGB color transition to the specified pixel-by-pixel list of RGBcolor codes.";
  }

  string getMoreInfo()
  {
    return "The first color code represents the target RGB value of the first LED, the next color code represents the target value of the next LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be updated", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "rgbList", "a list of target 24bit RGB codes, in the form 0xRRGGBB", "_INTARR", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->rgbArrayOfs_move((int)(*args)[0]->get_intValue(),
                                     (*args)[1]->get_intArrValue(),
                                     (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets up a smooth RGB color transition to the specified pixel-by-pixel list of RGB
 * color codes. The first color code represents the target RGB value of the first LED,
 * the next color code represents the target value of the next LED, etc.
 *
 * @param rgbList : a list of target 24bit RGB codes, in the form 0xRRGGBB
 * @param delay   : transition duration in ms
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_rgbArray_move : public YapiCommand /* arguments: rgbList delay */
{
public:
  apifun_ColorLedCluster_rgbArray_move(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "rgbArray_move";
  }

  string getDescription()
  {
    return "Sets up a smooth RGB color transition to the specified pixel-by-pixel list of RGBcolor codes.";
  }

  string getMoreInfo()
  {
    return "The first color code represents the target RGB value of the first LED, the next color code represents the target value of the next LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INTARR_ARG, "rgbList", "a list of target 24bit RGB codes, in the form 0xRRGGBB", "_INTARR", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->rgbArray_move((*args)[0]->get_intArrValue(),
                                  (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a binary buffer to the LED HSL buffer, as is.
 * First three bytes are HSL components for the LED specified as parameter, the
 * next three bytes for the second LED, etc.
 *
 * @param ledIndex : index of the first LED which should be updated
 * @param buff : the binary buffer to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_hslColorBuffer : public YapiCommand /* arguments: ledIndex buff */
{
public:
  apifun_ColorLedCluster_set_hslColorBuffer(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_hslColorBuffer";
  }

  string getDescription()
  {
    return "Sends a binary buffer to the LED HSL buffer, as is.";
  }

  string getMoreInfo()
  {
    return "First three bytes are HSL components for the LED specified as parameter, the next three bytes for the second LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be updated", "_INT", false));
    res->push_back(new ArgumentDesc(BIN_ARG, "buff", "the binary buffer to send", "_BIN", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_hslColorBuffer((int)(*args)[0]->get_intValue(),
                                       (*args)[1]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends 24bit HSL colors (provided as a list of integers) to the LED HSL buffer, as is.
 * The first number represents the HSL value of the LED specified as parameter, the second number represents
 * the HSL value of the second LED, etc.
 *
 * @param ledIndex : index of the first LED which should be updated
 * @param hslList : a list of 24bit HSL codes, in the form 0xHHSSLL
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_set_hslColorArray : public YapiCommand /* arguments: ledIndex hslList */
{
public:
  apifun_ColorLedCluster_set_hslColorArray(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_hslColorArray";
  }

  string getDescription()
  {
    return "Sends 24bit HSL colors (provided as a list of integers) to the LED HSL buffer, as is.";
  }

  string getMoreInfo()
  {
    return "The first number represents the HSL value of the LED specified as parameter, the second number represents the HSL value of the second LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be updated", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "hslList", "a list of 24bit HSL codes, in the form 0xHHSSLL", "_INTARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_hslColorArray((int)(*args)[0]->get_intValue(),
                                      (*args)[1]->get_intArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets up a smooth HSL color transition to the specified pixel-by-pixel list of HSL
 * color codes. The first color code represents the target HSL value of the first LED,
 * the second color code represents the target value of the second LED, etc.
 *
 * @param hslList : a list of target 24bit HSL codes, in the form 0xHHSSLL
 * @param delay   : transition duration in ms
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_hslArray_move : public YapiCommand /* arguments: hslList delay */
{
public:
  apifun_ColorLedCluster_hslArray_move(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "hslArray_move";
  }

  string getDescription()
  {
    return "Sets up a smooth HSL color transition to the specified pixel-by-pixel list of HSLcolor codes.";
  }

  string getMoreInfo()
  {
    return "The first color code represents the target HSL value of the first LED, the second color code represents the target value of the second LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INTARR_ARG, "hslList", "a list of target 24bit HSL codes, in the form 0xHHSSLL", "_INTARR", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->hslArray_move((*args)[0]->get_intArrValue(),
                                  (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets up a smooth HSL color transition to the specified pixel-by-pixel list of HSL
 * color codes. The first color code represents the target HSL value of the first LED,
 * the second color code represents the target value of the second LED, etc.
 *
 * @param ledIndex : index of the first LED which should be updated
 * @param hslList : a list of target 24bit HSL codes, in the form 0xHHSSLL
 * @param delay   : transition duration in ms
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLedCluster_hslArrayOfs_move : public YapiCommand /* arguments: ledIndex hslList delay */
{
public:
  apifun_ColorLedCluster_hslArrayOfs_move(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "hslArrayOfs_move";
  }

  string getDescription()
  {
    return "Sets up a smooth HSL color transition to the specified pixel-by-pixel list of HSLcolor codes.";
  }

  string getMoreInfo()
  {
    return "The first color code represents the target HSL value of the first LED, the second color code represents the target value of the second LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be updated", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "hslList", "a list of target 24bit HSL codes, in the form 0xHHSSLL", "_INTARR", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "transition duration in ms", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->hslArrayOfs_move((int)(*args)[0]->get_intValue(),
                                     (*args)[1]->get_intArrValue(),
                                     (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a binary buffer with content from the LED RGB buffer, as is.
 * First three bytes are RGB components for the first LED in the interval,
 * the next three bytes for the second LED in the interval, etc.
 *
 * @param ledIndex : index of the first LED which should be returned
 * @param count    : number of LEDs which should be returned
 *
 * @return a binary buffer with RGB components of selected LEDs.
 *
 * On failure, throws an exception or returns an empty binary buffer.
 */
class apifun_ColorLedCluster_get_rgbColorBuffer : public YapiCommand /* arguments: ledIndex count */
{
public:
  apifun_ColorLedCluster_get_rgbColorBuffer(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rgbColorBuffer";
  }

  string getDescription()
  {
    return "Returns a binary buffer with content from the LED RGB buffer, as is.";
  }

  string getMoreInfo()
  {
    return "First three bytes are RGB components for the first LED in the interval, the next three bytes for the second LED in the interval, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of LEDs which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_rgbColorBuffer((int)(*args)[0]->get_intValue(),
                                                      (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list on 24bit RGB color values with the current colors displayed on
 * the RGB LEDs. The first number represents the RGB value of the first LED,
 * the second number represents the RGB value of the second LED, etc.
 *
 * @param ledIndex : index of the first LED which should be returned
 * @param count    : number of LEDs which should be returned
 *
 * @return a list of 24bit color codes with RGB components of selected LEDs, as 0xRRGGBB.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_ColorLedCluster_get_rgbColorArray : public YapiCommand /* arguments: ledIndex count */
{
public:
  apifun_ColorLedCluster_get_rgbColorArray(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rgbColorArray";
  }

  string getDescription()
  {
    return "Returns a list on 24bit RGB color values with the current colors displayed onthe RGB LEDs.";
  }

  string getMoreInfo()
  {
    return "The first number represents the RGB value of the first LED, the second number represents the RGB value of the second LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of LEDs which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->get_rgbColorArray((int)(*args)[0]->get_intValue(),
                                                          (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list on 24bit RGB color values with the RGB LEDs startup colors.
 * The first number represents the startup RGB value of the first LED,
 * the second number represents the RGB value of the second LED, etc.
 *
 * @param ledIndex : index of the first LED  which should be returned
 * @param count    : number of LEDs which should be returned
 *
 * @return a list of 24bit color codes with RGB components of selected LEDs, as 0xRRGGBB.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_ColorLedCluster_get_rgbColorArrayAtPowerOn : public YapiCommand /* arguments: ledIndex count */
{
public:
  apifun_ColorLedCluster_get_rgbColorArrayAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rgbColorArrayAtPowerOn";
  }

  string getDescription()
  {
    return "Returns a list on 24bit RGB color values with the RGB LEDs startup colors.";
  }

  string getMoreInfo()
  {
    return "The first number represents the startup RGB value of the first LED, the second number represents the RGB value of the second LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of LEDs which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->get_rgbColorArrayAtPowerOn((int)(*args)[0]->get_intValue(),
                                                                   (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list on sequence index for each RGB LED. The first number represents the
 * sequence index for the the first LED, the second number represents the sequence
 * index for the second LED, etc.
 *
 * @param ledIndex : index of the first LED which should be returned
 * @param count    : number of LEDs which should be returned
 *
 * @return a list of integers with sequence index
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_ColorLedCluster_get_linkedSeqArray : public YapiCommand /* arguments: ledIndex count */
{
public:
  apifun_ColorLedCluster_get_linkedSeqArray(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_linkedSeqArray";
  }

  string getDescription()
  {
    return "Returns a list on sequence index for each RGB LED.";
  }

  string getMoreInfo()
  {
    return "The first number represents the sequence index for the the first LED, the second number represents the sequence index for the second LED, etc.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ledIndex", "index of the first LED which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of LEDs which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->get_linkedSeqArray((int)(*args)[0]->get_intValue(),
                                                           (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list on 32 bit signatures for specified blinking sequences.
 * Since blinking sequences cannot be read from the device, this can be used
 * to detect if a specific blinking sequence is already programmed.
 *
 * @param seqIndex : index of the first blinking sequence which should be returned
 * @param count    : number of blinking sequences which should be returned
 *
 * @return a list of 32 bit integer signatures
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_ColorLedCluster_get_blinkSeqSignatures : public YapiCommand /* arguments: seqIndex count */
{
public:
  apifun_ColorLedCluster_get_blinkSeqSignatures(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqSignatures";
  }

  string getDescription()
  {
    return "Returns a list on 32 bit signatures for specified blinking sequences.";
  }

  string getMoreInfo()
  {
    return "Since blinking sequences cannot be read from the device, this can be used to detect if a specific blinking sequence is already programmed.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the first blinking sequence which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of blinking sequences which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->get_blinkSeqSignatures((int)(*args)[0]->get_intValue(),
                                                               (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of integers with the current speed for specified blinking sequences.
 *
 * @param seqIndex : index of the first sequence speed which should be returned
 * @param count    : number of sequence speeds which should be returned
 *
 * @return a list of integers, 0 for sequences turned off and 1 for sequences running
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_ColorLedCluster_get_blinkSeqStateSpeed : public YapiCommand /* arguments: seqIndex count */
{
public:
  apifun_ColorLedCluster_get_blinkSeqStateSpeed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqStateSpeed";
  }

  string getDescription()
  {
    return "Returns a list of integers with the current speed for specified blinking sequences.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the first sequence speed which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of sequence speeds which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->get_blinkSeqStateSpeed((int)(*args)[0]->get_intValue(),
                                                               (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of integers with the "auto-start at power on" flag state for specified blinking sequences.
 *
 * @param seqIndex : index of the first blinking sequence which should be returned
 * @param count    : number of blinking sequences which should be returned
 *
 * @return a list of integers, 0 for sequences turned off and 1 for sequences running
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_ColorLedCluster_get_blinkSeqStateAtPowerOn : public YapiCommand /* arguments: seqIndex count */
{
public:
  apifun_ColorLedCluster_get_blinkSeqStateAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqStateAtPowerOn";
  }

  string getDescription()
  {
    return "Returns a list of integers with the \"auto-start at power on\" flag state for specified blinking sequences.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the first blinking sequence which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of blinking sequences which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->get_blinkSeqStateAtPowerOn((int)(*args)[0]->get_intValue(),
                                                                   (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of integers with the started state for specified blinking sequences.
 *
 * @param seqIndex : index of the first blinking sequence which should be returned
 * @param count    : number of blinking sequences which should be returned
 *
 * @return a list of integers, 0 for sequences turned off and 1 for sequences running
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_ColorLedCluster_get_blinkSeqState : public YapiCommand /* arguments: seqIndex count */
{
public:
  apifun_ColorLedCluster_get_blinkSeqState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqState";
  }

  string getDescription()
  {
    return "Returns a list of integers with the started state for specified blinking sequences.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "seqIndex", "index of the first blinking sequence which should be returned", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "count", "number of blinking sequences which should be returned", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLedCluster*>* list = enumerateTargets<YColorLedCluster>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->get_blinkSeqState((int)(*args)[0]->get_intValue(),
                                                          (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YColorLedCluster implementation)

//--- (YColorLedCluster functions)
void YColorLedClusterCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YColorLedCluster>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_get_activeLedCount(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_set_activeLedCount(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_get_ledType(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_set_ledType(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_get_maxLedCount(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_get_blinkSeqMaxCount(this)));
    cmdList->push_back((YapiCommand*) (new ColorLedCluster_get_blinkSeqMaxSize(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_rgbColor(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_rgbColorAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_hslColorAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_hslColor(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_rgb_move(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_hsl_move(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_addRgbMoveToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_addHslMoveToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_addMirrorToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_addJumpToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_addUnlinkToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_linkLedToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_linkLedToBlinkSeqAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_linkLedToPeriodicBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_unlinkLedFromBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_startBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_stopBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_resetBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_blinkSeqStateAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_blinkSeqSpeed(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_saveLedsConfigAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_saveBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_rgbColorBuffer(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_rgbColorArray(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_rgbArrayOfs_move(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_rgbArray_move(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_hslColorBuffer(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_set_hslColorArray(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_hslArray_move(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_hslArrayOfs_move(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_rgbColorBuffer(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_rgbColorArray(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_rgbColorArrayAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_linkedSeqArray(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_blinkSeqSignatures(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_blinkSeqStateSpeed(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_blinkSeqStateAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLedCluster_get_blinkSeqState(this)));
  }

//--- (end of YColorLedCluster functions)
