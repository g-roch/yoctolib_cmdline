/*********************************************************************
 *
 *  $Id: YColorLed.cpp 33710 2018-12-14 14:18:53Z seb $
 *
 *  Implements commands to handle ColorLed functions
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
#include "YColorLed.h"
#include "yocto_api.h"
#include "yocto_colorled.h"

using namespace std;

//--- (YColorLed definitions)

//--- (end of YColorLed definitions)


//--- (YColorLed implementation)
bool   YColorLedCmdLine::isModule(void)      { return false; }
string YColorLedCmdLine::YFunctionName(void) { return "YColorLed"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of rgbColor is int (U24Color)
// type of hslColor is int (U24Color)
// type of rgbColorAtPowerOn is int (U24Color)
// type of blinkSeqSize is int (UInt31)
// type of blinkSeqMaxSize is int (UInt31)
// type of blinkSeqSignature is int (UInt31)
// type of command is string (Text)
/**
 * Returns the logical name of the RGB LED.
 *
 * @return a string corresponding to the logical name of the RGB LED
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class ColorLed_get_logicalName : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the RGB LED.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
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
 * Changes the logical name of the RGB LED. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the RGB LED
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  ColorLed_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the RGB LED.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the RGB LED", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the RGB LED.
 *
 * @return a string corresponding to a short string representing the current state of the RGB LED
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class ColorLed_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the RGB LED.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
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
 * Returns the current RGB color of the LED.
 *
 * @return an integer corresponding to the current RGB color of the LED
 *
 * On failure, throws an exception or returns Y_RGBCOLOR_INVALID.
 */
class ColorLed_get_rgbColor : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_rgbColor(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rgbColor";
  }

  string getDescription()
  {
    return "Returns the current RGB color of the LED.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rgbColor();
        char buf[32]; snprintf(buf,32,"#%06x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current color of the LED, using an RGB color. Encoding is done as follows: 0xRRGGBB.
 *
 * @param newval : an integer corresponding to the current color of the LED, using an RGB color
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_rgbColor : public YapiCommand /* arguments: newval */
{
public:
  ColorLed_set_rgbColor(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_rgbColor";
  }

  string getDescription()
  {
    return "Changes the current color of the LED, using an RGB color.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xRRGGBB.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the current color of the LED, using an RGB color", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_rgbColor(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current HSL color of the LED.
 *
 * @return an integer corresponding to the current HSL color of the LED
 *
 * On failure, throws an exception or returns Y_HSLCOLOR_INVALID.
 */
class ColorLed_get_hslColor : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_hslColor(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_hslColor";
  }

  string getDescription()
  {
    return "Returns the current HSL color of the LED.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_hslColor();
        char buf[32]; snprintf(buf,32,"#%06x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current color of the LED, using a color HSL. Encoding is done as follows: 0xHHSSLL.
 *
 * @param newval : an integer corresponding to the current color of the LED, using a color HSL
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_hslColor : public YapiCommand /* arguments: newval */
{
public:
  ColorLed_set_hslColor(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_hslColor";
  }

  string getDescription()
  {
    return "Changes the current color of the LED, using a color HSL.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xHHSSLL.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the current color of the LED, using a color HSL", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_hslColor(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Performs a smooth transition in the RGB color space between the current color and a target color.
 *
 * @param rgb_target  : desired RGB color at the end of the transition
 * @param ms_duration : duration of the transition, in millisecond
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_ColorLed_rgbMove : public YapiCommand /* arguments: rgb_target ms_duration */
{
public:
  alias_ColorLed_rgbMove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "rgbMove";
  }

  string getDescription()
  {
    return "Performs a smooth transition in the RGB color space between the current color and a target color.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "rgb_target", "desired RGB color at the end of the transition", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "duration of the transition, in millisecond", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->rgbMove((int)(*args)[0]->get_intValue(),
                            (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Performs a smooth transition in the HSL color space between the current color and a target color.
 *
 * @param hsl_target  : desired HSL color at the end of the transition
 * @param ms_duration : duration of the transition, in millisecond
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_ColorLed_hslMove : public YapiCommand /* arguments: hsl_target ms_duration */
{
public:
  alias_ColorLed_hslMove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "hslMove";
  }

  string getDescription()
  {
    return "Performs a smooth transition in the HSL color space between the current color and a target color.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "hsl_target", "desired HSL color at the end of the transition", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "duration of the transition, in millisecond", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->hslMove((int)(*args)[0]->get_intValue(),
                            (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the configured color to be displayed when the module is turned on.
 *
 * @return an integer corresponding to the configured color to be displayed when the module is turned on
 *
 * On failure, throws an exception or returns Y_RGBCOLORATPOWERON_INVALID.
 */
class ColorLed_get_rgbColorAtPowerOn : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_rgbColorAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rgbColorAtPowerOn";
  }

  string getDescription()
  {
    return "Returns the configured color to be displayed when the module is turned on.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rgbColorAtPowerOn();
        char buf[32]; snprintf(buf,32,"#%06x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the color that the LED will display by default when the module is turned on.
 *
 * @param newval : an integer corresponding to the color that the LED will display by default when the
 * module is turned on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_rgbColorAtPowerOn : public YapiCommand /* arguments: newval */
{
public:
  ColorLed_set_rgbColorAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_rgbColorAtPowerOn";
  }

  string getDescription()
  {
    return "Changes the color that the LED will display by default when the module is turned on.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the color that the LED will display by default when the module is turned on", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_rgbColorAtPowerOn(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current length of the blinking sequence.
 *
 * @return an integer corresponding to the current length of the blinking sequence
 *
 * On failure, throws an exception or returns Y_BLINKSEQSIZE_INVALID.
 */
class ColorLed_get_blinkSeqSize : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_blinkSeqSize(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqSize";
  }

  string getDescription()
  {
    return "Returns the current length of the blinking sequence.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_blinkSeqSize();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the maximum length of the blinking sequence.
 *
 * @return an integer corresponding to the maximum length of the blinking sequence
 *
 * On failure, throws an exception or returns Y_BLINKSEQMAXSIZE_INVALID.
 */
class ColorLed_get_blinkSeqMaxSize : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_blinkSeqMaxSize(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqMaxSize";
  }

  string getDescription()
  {
    return "Returns the maximum length of the blinking sequence.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_blinkSeqMaxSize();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Return the blinking sequence signature. Since blinking
 * sequences cannot be read from the device, this can be used
 * to detect if a specific blinking sequence is already
 * programmed.
 *
 * @return an integer
 *
 * On failure, throws an exception or returns Y_BLINKSEQSIGNATURE_INVALID.
 */
class ColorLed_get_blinkSeqSignature : public YapiCommand /* arguments: */
{
public:
  ColorLed_get_blinkSeqSignature(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_blinkSeqSignature";
  }

  string getDescription()
  {
    return "Return the blinking sequence signature.";
  }

  string getMoreInfo()
  {
    return "Since blinking sequences cannot be read from the device, this can be used to detect if a specific blinking sequence is already programmed.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_blinkSeqSignature();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackColorLed is YColorLedValueCallback* (YColorLedValueCallback)
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
class apifun_ColorLed_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLed_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
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
class apifun_ColorLed_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLed_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
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
 * Add a new transition to the blinking sequence, the move will
 * be performed in the HSL space.
 *
 * @param HSLcolor : desired HSL color when the transition is completed
 * @param msDelay : duration of the color transition, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_addHslMoveToBlinkSeq : public YapiCommand /* arguments: HSLcolor msDelay */
{
public:
  apifun_ColorLed_addHslMoveToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "addHslMoveToBlinkSeq";
  }

  string getDescription()
  {
    return "Add a new transition to the blinking sequence, the move willbe performed in the HSL space.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "HSLcolor", "desired HSL color when the transition is completed", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "msDelay", "duration of the color transition, in milliseconds.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addHslMoveToBlinkSeq((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds a new transition to the blinking sequence, the move is
 * performed in the RGB space.
 *
 * @param RGBcolor : desired RGB color when the transition is completed
 * @param msDelay : duration of the color transition, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_addRgbMoveToBlinkSeq : public YapiCommand /* arguments: RGBcolor msDelay */
{
public:
  apifun_ColorLed_addRgbMoveToBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "addRgbMoveToBlinkSeq";
  }

  string getDescription()
  {
    return "Adds a new transition to the blinking sequence, the move isperformed in the RGB space.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "RGBcolor", "desired RGB color when the transition is completed", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "msDelay", "duration of the color transition, in milliseconds.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addRgbMoveToBlinkSeq((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the preprogrammed blinking sequence. The sequence is
 * run in a loop until it is stopped by stopBlinkSeq or an explicit
 * change.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_startBlinkSeq : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLed_startBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "startBlinkSeq";
  }

  string getDescription()
  {
    return "Starts the preprogrammed blinking sequence.";
  }

  string getMoreInfo()
  {
    return "The sequence is run in a loop until it is stopped by stopBlinkSeq or an explicit change.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->startBlinkSeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the preprogrammed blinking sequence.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_stopBlinkSeq : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLed_stopBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "stopBlinkSeq";
  }

  string getDescription()
  {
    return "Stops the preprogrammed blinking sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->stopBlinkSeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Resets the preprogrammed blinking sequence.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_resetBlinkSeq : public YapiCommand /* arguments: */
{
public:
  apifun_ColorLed_resetBlinkSeq(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "resetBlinkSeq";
  }

  string getDescription()
  {
    return "Resets the preprogrammed blinking sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetBlinkSeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YColorLed implementation)

//--- (YColorLed functions)
void YColorLedCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YColorLed>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new ColorLed_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_rgbColor(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_rgbColor(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_hslColor(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_hslColor(this)));
    cmdList->push_back((YapiCommand*) (new alias_ColorLed_rgbMove(this)));
    cmdList->push_back((YapiCommand*) (new alias_ColorLed_hslMove(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_rgbColorAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_rgbColorAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_blinkSeqSize(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_blinkSeqMaxSize(this)));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_blinkSeqSignature(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_addHslMoveToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_addRgbMoveToBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_startBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_stopBlinkSeq(this)));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_resetBlinkSeq(this)));
  }

//--- (end of YColorLed functions)
