/*********************************************************************
 *
 *  $Id: YAnButton.cpp 32610 2018-10-10 06:52:20Z seb $
 *
 *  Implements commands to handle AnButton functions
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
#include "YAnButton.h"
#include "yocto_api.h"
#include "yocto_anbutton.h"

using namespace std;

//--- (YAnButton definitions)

static const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

static const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

//--- (end of YAnButton definitions)


//--- (YAnButton implementation)
bool   YAnButtonCmdLine::isModule(void)      { return false; }
string YAnButtonCmdLine::YFunctionName(void) { return "YAnButton"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of calibratedValue is int (UInt31)
// type of rawValue is int (UInt31)
// type of analogCalibration is int (OnOff)
// type of calibrationMax is int (UInt31)
// type of calibrationMin is int (UInt31)
// type of sensitivity is int (UInt31)
// type of isPressed is int (Bool)
// type of lastTimePressed is s64 (Time)
// type of lastTimeReleased is s64 (Time)
// type of pulseCounter is s64 (UInt)
// type of pulseTimer is s64 (Time)
/**
 * Returns the logical name of the analog input.
 *
 * @return a string corresponding to the logical name of the analog input
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class AnButton_get_logicalName : public YapiCommand /* arguments: */
{
public:
  AnButton_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the analog input.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
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
 * Changes the logical name of the analog input. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the analog input
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AnButton_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  AnButton_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the analog input.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the analog input", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the analog input.
 *
 * @return a string corresponding to a short string representing the current state of the analog input
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class AnButton_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  AnButton_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the analog input.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
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
 * Returns the current calibrated input value (between 0 and 1000, included).
 *
 * @return an integer corresponding to the current calibrated input value (between 0 and 1000, included)
 *
 * On failure, throws an exception or returns Y_CALIBRATEDVALUE_INVALID.
 */
class AnButton_get_calibratedValue : public YapiCommand /* arguments: */
{
public:
  AnButton_get_calibratedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_calibratedValue";
  }

  string getDescription()
  {
    return "Returns the current calibrated input value (between 0 and 1000, included).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_calibratedValue();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current measured input value as-is (between 0 and 4095, included).
 *
 * @return an integer corresponding to the current measured input value as-is (between 0 and 4095, included)
 *
 * On failure, throws an exception or returns Y_RAWVALUE_INVALID.
 */
class AnButton_get_rawValue : public YapiCommand /* arguments: */
{
public:
  AnButton_get_rawValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rawValue";
  }

  string getDescription()
  {
    return "Returns the current measured input value as-is (between 0 and 4095, included).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rawValue();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Tells if a calibration process is currently ongoing.
 *
 * @return either Y_ANALOGCALIBRATION_OFF or Y_ANALOGCALIBRATION_ON
 *
 * On failure, throws an exception or returns Y_ANALOGCALIBRATION_INVALID.
 */
class AnButton_get_analogCalibration : public YapiCommand /* arguments: */
{
public:
  AnButton_get_analogCalibration(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_analogCalibration";
  }

  string getDescription()
  {
    return "Tells if a calibration process is currently ongoing.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_analogCalibration();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Starts or stops the calibration process. Remember to call the saveToFlash()
 * method of the module at the end of the calibration if the modification must be kept.
 *
 * @param newval : either Y_ANALOGCALIBRATION_OFF or Y_ANALOGCALIBRATION_ON
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AnButton_set_analogCalibration : public YapiCommand /* arguments: newval */
{
public:
  AnButton_set_analogCalibration(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_analogCalibration";
  }

  string getDescription()
  {
    return "Starts or stops the calibration process.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method of the module at the end of the calibration if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_analogCalibration(Y_ANALOGCALIBRATION_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximal value measured during the calibration (between 0 and 4095, included).
 *
 * @return an integer corresponding to the maximal value measured during the calibration (between 0
 * and 4095, included)
 *
 * On failure, throws an exception or returns Y_CALIBRATIONMAX_INVALID.
 */
class AnButton_get_calibrationMax : public YapiCommand /* arguments: */
{
public:
  AnButton_get_calibrationMax(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_calibrationMax";
  }

  string getDescription()
  {
    return "Returns the maximal value measured during the calibration (between 0 and 4095, included).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_calibrationMax();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the maximal calibration value for the input (between 0 and 4095, included), without actually
 * starting the automated calibration.  Remember to call the saveToFlash()
 * method of the module if the modification must be kept.
 *
 * @param newval : an integer corresponding to the maximal calibration value for the input (between 0
 * and 4095, included), without actually
 *         starting the automated calibration
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AnButton_set_calibrationMax : public YapiCommand /* arguments: newval */
{
public:
  AnButton_set_calibrationMax(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_calibrationMax";
  }

  string getDescription()
  {
    return "Changes the maximal calibration value for the input (between 0 and 4095, included), without actuallystarting the automated calibration.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method of the module if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the maximal calibration value for the input (between 0 and 4095, included), without actually starting the automated calibration", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_calibrationMax(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the minimal value measured during the calibration (between 0 and 4095, included).
 *
 * @return an integer corresponding to the minimal value measured during the calibration (between 0
 * and 4095, included)
 *
 * On failure, throws an exception or returns Y_CALIBRATIONMIN_INVALID.
 */
class AnButton_get_calibrationMin : public YapiCommand /* arguments: */
{
public:
  AnButton_get_calibrationMin(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_calibrationMin";
  }

  string getDescription()
  {
    return "Returns the minimal value measured during the calibration (between 0 and 4095, included).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_calibrationMin();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the minimal calibration value for the input (between 0 and 4095, included), without actually
 * starting the automated calibration.  Remember to call the saveToFlash()
 * method of the module if the modification must be kept.
 *
 * @param newval : an integer corresponding to the minimal calibration value for the input (between 0
 * and 4095, included), without actually
 *         starting the automated calibration
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AnButton_set_calibrationMin : public YapiCommand /* arguments: newval */
{
public:
  AnButton_set_calibrationMin(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_calibrationMin";
  }

  string getDescription()
  {
    return "Changes the minimal calibration value for the input (between 0 and 4095, included), without actuallystarting the automated calibration.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method of the module if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the minimal calibration value for the input (between 0 and 4095, included), without actually starting the automated calibration", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_calibrationMin(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the sensibility for the input (between 1 and 1000) for triggering user callbacks.
 *
 * @return an integer corresponding to the sensibility for the input (between 1 and 1000) for
 * triggering user callbacks
 *
 * On failure, throws an exception or returns Y_SENSITIVITY_INVALID.
 */
class AnButton_get_sensitivity : public YapiCommand /* arguments: */
{
public:
  AnButton_get_sensitivity(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_sensitivity";
  }

  string getDescription()
  {
    return "Returns the sensibility for the input (between 1 and 1000) for triggering user callbacks.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_sensitivity();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the sensibility for the input (between 1 and 1000) for triggering user callbacks.
 * The sensibility is used to filter variations around a fixed value, but does not preclude the
 * transmission of events when the input value evolves constantly in the same direction.
 * Special case: when the value 1000 is used, the callback will only be thrown when the logical state
 * of the input switches from pressed to released and back.
 * Remember to call the saveToFlash() method of the module if the modification must be kept.
 *
 * @param newval : an integer corresponding to the sensibility for the input (between 1 and 1000) for
 * triggering user callbacks
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AnButton_set_sensitivity : public YapiCommand /* arguments: newval */
{
public:
  AnButton_set_sensitivity(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_sensitivity";
  }

  string getDescription()
  {
    return "Changes the sensibility for the input (between 1 and 1000) for triggering user callbacks.";
  }

  string getMoreInfo()
  {
    return "The sensibility is used to filter variations around a fixed value, but does not preclude the transmission of events when the input value evolves constantly in the same direction. Special case: when the value 1000 is used, the callback will only be thrown when the logical state of the input switches from pressed to released and back. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the sensibility for the input (between 1 and 1000) for triggering user callbacks", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_sensitivity(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns true if the input (considered as binary) is active (closed contact), and false otherwise.
 *
 * @return either Y_ISPRESSED_FALSE or Y_ISPRESSED_TRUE, according to true if the input (considered as
 * binary) is active (closed contact), and false otherwise
 *
 * On failure, throws an exception or returns Y_ISPRESSED_INVALID.
 */
class AnButton_get_isPressed : public YapiCommand /* arguments: */
{
public:
  AnButton_get_isPressed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_isPressed";
  }

  string getDescription()
  {
    return "Returns true if the input (considered as binary) is active (closed contact), and false otherwise.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_isPressed();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of elapsed milliseconds between the module power on and the last time
 * the input button was pressed (the input contact transitioned from open to closed).
 *
 * @return an integer corresponding to the number of elapsed milliseconds between the module power on
 * and the last time
 *         the input button was pressed (the input contact transitioned from open to closed)
 *
 * On failure, throws an exception or returns Y_LASTTIMEPRESSED_INVALID.
 */
class AnButton_get_lastTimePressed : public YapiCommand /* arguments: */
{
public:
  AnButton_get_lastTimePressed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_lastTimePressed";
  }

  string getDescription()
  {
    return "Returns the number of elapsed milliseconds between the module power on and the last timethe input button was pressed (the input contact transitioned from open to closed).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_lastTimePressed();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of elapsed milliseconds between the module power on and the last time
 * the input button was released (the input contact transitioned from closed to open).
 *
 * @return an integer corresponding to the number of elapsed milliseconds between the module power on
 * and the last time
 *         the input button was released (the input contact transitioned from closed to open)
 *
 * On failure, throws an exception or returns Y_LASTTIMERELEASED_INVALID.
 */
class AnButton_get_lastTimeReleased : public YapiCommand /* arguments: */
{
public:
  AnButton_get_lastTimeReleased(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_lastTimeReleased";
  }

  string getDescription()
  {
    return "Returns the number of elapsed milliseconds between the module power on and the last timethe input button was released (the input contact transitioned from closed to open).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_lastTimeReleased();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the pulse counter value. The value is a 32 bit integer. In case
 * of overflow (>=2^32), the counter will wrap. To reset the counter, just
 * call the resetCounter() method.
 *
 * @return an integer corresponding to the pulse counter value
 *
 * On failure, throws an exception or returns Y_PULSECOUNTER_INVALID.
 */
class AnButton_get_pulseCounter : public YapiCommand /* arguments: */
{
public:
  AnButton_get_pulseCounter(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_pulseCounter";
  }

  string getDescription()
  {
    return "Returns the pulse counter value.";
  }

  string getMoreInfo()
  {
    return "The value is a 32 bit integer. In case of overflow (>=2^32), the counter will wrap. To reset the counter, just call the resetCounter() method.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_pulseCounter();
        char buf[32]; snprintf(buf, 32, "%u", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the timer of the pulses counter (ms).
 *
 * @return an integer corresponding to the timer of the pulses counter (ms)
 *
 * On failure, throws an exception or returns Y_PULSETIMER_INVALID.
 */
class AnButton_get_pulseTimer : public YapiCommand /* arguments: */
{
public:
  AnButton_get_pulseTimer(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_pulseTimer";
  }

  string getDescription()
  {
    return "Returns the timer of the pulses counter (ms).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_pulseTimer();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackAnButton is YAnButtonValueCallback* (YAnButtonValueCallback)
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
class apifun_AnButton_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_AnButton_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
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
class apifun_AnButton_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_AnButton_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
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
 * Returns the pulse counter value as well as its timer.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_AnButton_resetCounter : public YapiCommand /* arguments: */
{
public:
  apifun_AnButton_resetCounter(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "resetCounter";
  }

  string getDescription()
  {
    return "Returns the pulse counter value as well as its timer.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YAnButton*>* list = enumerateTargets<YAnButton>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetCounter();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YAnButton implementation)

//--- (YAnButton functions)
void YAnButtonCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YAnButton>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new AnButton_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_calibratedValue(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_rawValue(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_analogCalibration(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_set_analogCalibration(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_calibrationMax(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_set_calibrationMax(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_calibrationMin(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_set_calibrationMin(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_sensitivity(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_set_sensitivity(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_isPressed(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_lastTimePressed(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_lastTimeReleased(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_pulseCounter(this)));
    cmdList->push_back((YapiCommand*) (new AnButton_get_pulseTimer(this)));
    cmdList->push_back((YapiCommand*) (new apifun_AnButton_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_AnButton_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_AnButton_resetCounter(this)));
  }

//--- (end of YAnButton functions)
