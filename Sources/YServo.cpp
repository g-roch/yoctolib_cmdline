/*********************************************************************
 *
 *  $Id: YServo.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle Servo functions
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
#include "YServo.h"
#include "yocto_api.h"
#include "yocto_servo.h"

using namespace std;

//--- (YServo definitions)

static const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

//--- (end of YServo definitions)


//--- (YServo implementation)
bool   YServoCmdLine::isModule(void)      { return false; }
string YServoCmdLine::YFunctionName(void) { return "YServo"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of position is int (Int)
// type of enabled is int (Bool)
// type of range is int (Percent)
// type of neutral is int (MicroSeconds)
// type of positionAtPowerOn is int (Int)
// type of enabledAtPowerOn is int (Bool)
/**
 * Returns the logical name of the servo.
 *
 * @return a string corresponding to the logical name of the servo
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Servo_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Servo_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the servo.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
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
 * Changes the logical name of the servo. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the servo
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Servo_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Servo_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the servo.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the servo", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the servo.
 *
 * @return a string corresponding to a short string representing the current state of the servo
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Servo_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  Servo_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the servo.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
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
 * Returns the current servo position.
 *
 * @return an integer corresponding to the current servo position
 *
 * On failure, throws an exception or returns Y_POSITION_INVALID.
 */
class Servo_get_position : public YapiCommand /* arguments: */
{
public:
  Servo_get_position(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_position";
  }

  string getDescription()
  {
    return "Returns the current servo position.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_position();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes immediately the servo driving position.
 *
 * @param newval : an integer corresponding to immediately the servo driving position
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Servo_set_position : public YapiCommand /* arguments: newval */
{
public:
  Servo_set_position(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_position";
  }

  string getDescription()
  {
    return "Changes immediately the servo driving position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to immediately the servo driving position", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_position(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the state of the servos.
 *
 * @return either Y_ENABLED_FALSE or Y_ENABLED_TRUE, according to the state of the servos
 *
 * On failure, throws an exception or returns Y_ENABLED_INVALID.
 */
class Servo_get_enabled : public YapiCommand /* arguments: */
{
public:
  Servo_get_enabled(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_enabled";
  }

  string getDescription()
  {
    return "Returns the state of the servos.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
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
 * Stops or starts the servo.
 *
 * @param newval : either Y_ENABLED_FALSE or Y_ENABLED_TRUE
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Servo_set_enabled : public YapiCommand /* arguments: newval */
{
public:
  Servo_set_enabled(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_enabled";
  }

  string getDescription()
  {
    return "Stops or starts the servo.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_enabled(Y_ENABLED_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current range of use of the servo.
 *
 * @return an integer corresponding to the current range of use of the servo
 *
 * On failure, throws an exception or returns Y_RANGE_INVALID.
 */
class Servo_get_range : public YapiCommand /* arguments: */
{
public:
  Servo_get_range(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_range";
  }

  string getDescription()
  {
    return "Returns the current range of use of the servo.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_range();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the range of use of the servo, specified in per cents.
 * A range of 100% corresponds to a standard control signal, that varies
 * from 1 [ms] to 2 [ms], When using a servo that supports a double range,
 * from 0.5 [ms] to 2.5 [ms], you can select a range of 200%.
 * Be aware that using a range higher than what is supported by the servo
 * is likely to damage the servo. Remember to call the matching module
 * saveToFlash() method, otherwise this call will have no effect.
 *
 * @param newval : an integer corresponding to the range of use of the servo, specified in per cents
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Servo_set_range : public YapiCommand /* arguments: newval */
{
public:
  Servo_set_range(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_range";
  }

  string getDescription()
  {
    return "Changes the range of use of the servo, specified in per cents.";
  }

  string getMoreInfo()
  {
    return "A range of 100% corresponds to a standard control signal, that varies from 1 [ms] to 2 [ms], When using a servo that supports a double range, from 0.5 [ms] to 2.5 [ms], you can select a range of 200%. Be aware that using a range higher than what is supported by the servo is likely to damage the servo. Remember to call the matching module saveToFlash() method, otherwise this call will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the range of use of the servo, specified in per cents", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_range(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the duration in microseconds of a neutral pulse for the servo.
 *
 * @return an integer corresponding to the duration in microseconds of a neutral pulse for the servo
 *
 * On failure, throws an exception or returns Y_NEUTRAL_INVALID.
 */
class Servo_get_neutral : public YapiCommand /* arguments: */
{
public:
  Servo_get_neutral(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_neutral";
  }

  string getDescription()
  {
    return "Returns the duration in microseconds of a neutral pulse for the servo.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_neutral();
        char buf[32]; snprintf(buf, 32, "%u [us]", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the duration of the pulse corresponding to the neutral position of the servo.
 * The duration is specified in microseconds, and the standard value is 1500 [us].
 * This setting makes it possible to shift the range of use of the servo.
 * Be aware that using a range higher than what is supported by the servo is
 * likely to damage the servo. Remember to call the matching module
 * saveToFlash() method, otherwise this call will have no effect.
 *
 * @param newval : an integer corresponding to the duration of the pulse corresponding to the neutral
 * position of the servo
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Servo_set_neutral : public YapiCommand /* arguments: newval */
{
public:
  Servo_set_neutral(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_neutral";
  }

  string getDescription()
  {
    return "Changes the duration of the pulse corresponding to the neutral position of the servo.";
  }

  string getMoreInfo()
  {
    return "The duration is specified in microseconds, and the standard value is 1500 [us]. This setting makes it possible to shift the range of use of the servo. Be aware that using a range higher than what is supported by the servo is likely to damage the servo. Remember to call the matching module saveToFlash() method, otherwise this call will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the duration of the pulse corresponding to the neutral position of the servo", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_neutral(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Performs a smooth move at constant speed toward a given position.
 *
 * @param target      : new position at the end of the move
 * @param ms_duration : total duration of the move, in milliseconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_Servo_move : public YapiCommand /* arguments: target ms_duration */
{
public:
  alias_Servo_move(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "move";
  }

  string getDescription()
  {
    return "Performs a smooth move at constant speed toward a given position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "target", "new position at the end of the move", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "total duration of the move, in milliseconds", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->move((int)(*args)[0]->get_intValue(),
                         (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the servo position at device power up.
 *
 * @return an integer corresponding to the servo position at device power up
 *
 * On failure, throws an exception or returns Y_POSITIONATPOWERON_INVALID.
 */
class Servo_get_positionAtPowerOn : public YapiCommand /* arguments: */
{
public:
  Servo_get_positionAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_positionAtPowerOn";
  }

  string getDescription()
  {
    return "Returns the servo position at device power up.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_positionAtPowerOn();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Configure the servo position at device power up. Remember to call the matching
 * module saveToFlash() method, otherwise this call will have no effect.
 *
 * @param newval : an integer
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Servo_set_positionAtPowerOn : public YapiCommand /* arguments: newval */
{
public:
  Servo_set_positionAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_positionAtPowerOn";
  }

  string getDescription()
  {
    return "Configure the servo position at device power up.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_positionAtPowerOn(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the servo signal generator state at power up.
 *
 * @return either Y_ENABLEDATPOWERON_FALSE or Y_ENABLEDATPOWERON_TRUE, according to the servo signal
 * generator state at power up
 *
 * On failure, throws an exception or returns Y_ENABLEDATPOWERON_INVALID.
 */
class Servo_get_enabledAtPowerOn : public YapiCommand /* arguments: */
{
public:
  Servo_get_enabledAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_enabledAtPowerOn";
  }

  string getDescription()
  {
    return "Returns the servo signal generator state at power up.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_enabledAtPowerOn();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Configure the servo signal generator state at power up. Remember to call the matching module saveToFlash()
 * method, otherwise this call will have no effect.
 *
 * @param newval : either Y_ENABLEDATPOWERON_FALSE or Y_ENABLEDATPOWERON_TRUE
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Servo_set_enabledAtPowerOn : public YapiCommand /* arguments: newval */
{
public:
  Servo_set_enabledAtPowerOn(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_enabledAtPowerOn";
  }

  string getDescription()
  {
    return "Configure the servo signal generator state at power up.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_enabledAtPowerOn(Y_ENABLEDATPOWERON_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackServo is YServoValueCallback* (YServoValueCallback)
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
class apifun_Servo_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Servo_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
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
class apifun_Servo_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Servo_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
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
class apifun_Servo_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_Servo_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YServo*>* list = enumerateTargets<YServo>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YServo implementation)

//--- (YServo functions)
void YServoCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YServo>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Servo_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Servo_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Servo_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new Servo_get_position(this)));
    cmdList->push_back((YapiCommand*) (new Servo_set_position(this)));
    cmdList->push_back((YapiCommand*) (new Servo_get_enabled(this)));
    cmdList->push_back((YapiCommand*) (new Servo_set_enabled(this)));
    cmdList->push_back((YapiCommand*) (new Servo_get_range(this)));
    cmdList->push_back((YapiCommand*) (new Servo_set_range(this)));
    cmdList->push_back((YapiCommand*) (new Servo_get_neutral(this)));
    cmdList->push_back((YapiCommand*) (new Servo_set_neutral(this)));
    cmdList->push_back((YapiCommand*) (new alias_Servo_move(this)));
    cmdList->push_back((YapiCommand*) (new Servo_get_positionAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new Servo_set_positionAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new Servo_get_enabledAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new Servo_set_enabledAtPowerOn(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Servo_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Servo_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Servo_get_serialNumber(this)));
  }

//--- (end of YServo functions)
