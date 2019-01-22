/*********************************************************************
 *
 *  $Id: YMotor.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle Motor functions
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
#include "YMotor.h"
#include "yocto_api.h"
#include "yocto_motor.h"

using namespace std;

//--- (YMotor definitions)

static const char *enumMotorState[] = {
    "IDLE",
    "BRAKE",
    "FORWD",
    "BACKWD",
    "LOVOLT",
    "HICURR",
    "HIHEAT",
    "FAILSF",
    NULL
};

//--- (end of YMotor definitions)


//--- (YMotor implementation)
bool   YMotorCmdLine::isModule(void)      { return false; }
string YMotorCmdLine::YFunctionName(void) { return "YMotor"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of motorStatus is int (MotorState)
// type of drivingForce is double (MeasureVal)
// type of brakingForce is double (MeasureVal)
// type of cutOffVoltage is double (MeasureVal)
// type of overCurrentLimit is int (Int)
// type of frequency is double (MeasureVal)
// type of starterTime is int (Int)
// type of failSafeTimeout is int (UInt31)
// type of command is string (Text)
/**
 * Returns the logical name of the motor.
 *
 * @return a string corresponding to the logical name of the motor
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Motor_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Motor_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the motor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
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
 * Changes the logical name of the motor. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the motor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the motor.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the motor", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the motor.
 *
 * @return a string corresponding to a short string representing the current state of the motor
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Motor_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  Motor_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the motor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
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
 * Return the controller state. Possible states are:
 * IDLE   when the motor is stopped/in free wheel, ready to start;
 * FORWD  when the controller is driving the motor forward;
 * BACKWD when the controller is driving the motor backward;
 * BRAKE  when the controller is braking;
 * LOVOLT when the controller has detected a low voltage condition;
 * HICURR when the controller has detected an over current condition;
 * HIHEAT when the controller has detected an overheat condition;
 * FAILSF when the controller switched on the failsafe security.
 *
 * When an error condition occurred (LOVOLT, HICURR, HIHEAT, FAILSF), the controller
 * status must be explicitly reset using the resetStatus function.
 *
 * @return a value among Y_MOTORSTATUS_IDLE, Y_MOTORSTATUS_BRAKE, Y_MOTORSTATUS_FORWD,
 * Y_MOTORSTATUS_BACKWD, Y_MOTORSTATUS_LOVOLT, Y_MOTORSTATUS_HICURR, Y_MOTORSTATUS_HIHEAT and Y_MOTORSTATUS_FAILSF
 *
 * On failure, throws an exception or returns Y_MOTORSTATUS_INVALID.
 */
class Motor_get_motorStatus : public YapiCommand /* arguments: */
{
public:
  Motor_get_motorStatus(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_motorStatus";
  }

  string getDescription()
  {
    return "Return the controller state.";
  }

  string getMoreInfo()
  {
    return "Possible states are: IDLE when the motor is stopped/in free wheel, ready to start; FORWD when the controller is driving the motor forward; BACKWD when the controller is driving the motor backward; BRAKE when the controller is braking; LOVOLT when the controller has detected a low voltage condition; HICURR when the controller has detected an over current condition; HIHEAT when the controller has detected an overheat condition; FAILSF when the controller switched on the failsafe security.\nWhen an error condition occurred (LOVOLT, HICURR, HIHEAT, FAILSF), the controller status must be explicitly reset using the resetStatus function.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_motorStatus();
        string strval =  enumString(attrval,enumMotorState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes immediately the power sent to the motor. The value is a percentage between -100%
 * to 100%. If you want go easy on your mechanics and avoid excessive current consumption,
 * try to avoid brutal power changes. For example, immediate transition from forward full power
 * to reverse full power is a very bad idea. Each time the driving power is modified, the
 * braking power is set to zero.
 *
 * @param newval : a floating point number corresponding to immediately the power sent to the motor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_drivingForce : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_drivingForce(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_drivingForce";
  }

  string getDescription()
  {
    return "Changes immediately the power sent to the motor.";
  }

  string getMoreInfo()
  {
    return "The value is a percentage between -100% to 100%. If you want go easy on your mechanics and avoid excessive current consumption, try to avoid brutal power changes. For example, immediate transition from forward full power to reverse full power is a very bad idea. Each time the driving power is modified, the braking power is set to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to immediately the power sent to the motor", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_drivingForce(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the power sent to the motor, as a percentage between -100% and +100%.
 *
 * @return a floating point number corresponding to the power sent to the motor, as a percentage
 * between -100% and +100%
 *
 * On failure, throws an exception or returns Y_DRIVINGFORCE_INVALID.
 */
class Motor_get_drivingForce : public YapiCommand /* arguments: */
{
public:
  Motor_get_drivingForce(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_drivingForce";
  }

  string getDescription()
  {
    return "Returns the power sent to the motor, as a percentage between -100% and +100%.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_drivingForce();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes immediately the braking force applied to the motor (in percents).
 * The value 0 corresponds to no braking (free wheel). When the braking force
 * is changed, the driving power is set to zero. The value is a percentage.
 *
 * @param newval : a floating point number corresponding to immediately the braking force applied to
 * the motor (in percents)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_brakingForce : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_brakingForce(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_brakingForce";
  }

  string getDescription()
  {
    return "Changes immediately the braking force applied to the motor (in percents).";
  }

  string getMoreInfo()
  {
    return "The value 0 corresponds to no braking (free wheel). When the braking force is changed, the driving power is set to zero. The value is a percentage.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to immediately the braking force applied to the motor (in percents)", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_brakingForce(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the braking force applied to the motor, as a percentage.
 * The value 0 corresponds to no braking (free wheel).
 *
 * @return a floating point number corresponding to the braking force applied to the motor, as a percentage
 *
 * On failure, throws an exception or returns Y_BRAKINGFORCE_INVALID.
 */
class Motor_get_brakingForce : public YapiCommand /* arguments: */
{
public:
  Motor_get_brakingForce(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_brakingForce";
  }

  string getDescription()
  {
    return "Returns the braking force applied to the motor, as a percentage.";
  }

  string getMoreInfo()
  {
    return "The value 0 corresponds to no braking (free wheel).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_brakingForce();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the threshold voltage under which the controller automatically switches to error state
 * and prevents further current draw. This setting prevent damage to a battery that can
 * occur when drawing current from an "empty" battery.
 * Note that whatever the cutoff threshold, the controller switches to undervoltage
 * error state if the power supply goes under 3V, even for a very brief time.
 *
 * @param newval : a floating point number corresponding to the threshold voltage under which the
 * controller automatically switches to error state
 *         and prevents further current draw
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_cutOffVoltage : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_cutOffVoltage(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_cutOffVoltage";
  }

  string getDescription()
  {
    return "Changes the threshold voltage under which the controller automatically switches to error stateand prevents further current draw.";
  }

  string getMoreInfo()
  {
    return "This setting prevent damage to a battery that can occur when drawing current from an \"empty\" battery. Note that whatever the cutoff threshold, the controller switches to undervoltage error state if the power supply goes under 3V, even for a very brief time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the threshold voltage under which the controller automatically switches to error state and prevents further current draw", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_cutOffVoltage(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the threshold voltage under which the controller automatically switches to error state
 * and prevents further current draw. This setting prevents damage to a battery that can
 * occur when drawing current from an "empty" battery.
 *
 * @return a floating point number corresponding to the threshold voltage under which the controller
 * automatically switches to error state
 *         and prevents further current draw
 *
 * On failure, throws an exception or returns Y_CUTOFFVOLTAGE_INVALID.
 */
class Motor_get_cutOffVoltage : public YapiCommand /* arguments: */
{
public:
  Motor_get_cutOffVoltage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_cutOffVoltage";
  }

  string getDescription()
  {
    return "Returns the threshold voltage under which the controller automatically switches to error stateand prevents further current draw.";
  }

  string getMoreInfo()
  {
    return "This setting prevents damage to a battery that can occur when drawing current from an \"empty\" battery.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_cutOffVoltage();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current threshold (in mA) above which the controller automatically
 * switches to error state. A zero value means that there is no limit.
 *
 * @return an integer corresponding to the current threshold (in mA) above which the controller automatically
 *         switches to error state
 *
 * On failure, throws an exception or returns Y_OVERCURRENTLIMIT_INVALID.
 */
class Motor_get_overCurrentLimit : public YapiCommand /* arguments: */
{
public:
  Motor_get_overCurrentLimit(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_overCurrentLimit";
  }

  string getDescription()
  {
    return "Returns the current threshold (in mA) above which the controller automaticallyswitches to error state.";
  }

  string getMoreInfo()
  {
    return "A zero value means that there is no limit.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_overCurrentLimit();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current threshold (in mA) above which the controller automatically
 * switches to error state. A zero value means that there is no limit. Note that whatever the
 * current limit is, the controller switches to OVERCURRENT status if the current
 * goes above 32A, even for a very brief time.
 *
 * @param newval : an integer corresponding to the current threshold (in mA) above which the
 * controller automatically
 *         switches to error state
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_overCurrentLimit : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_overCurrentLimit(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_overCurrentLimit";
  }

  string getDescription()
  {
    return "Changes the current threshold (in mA) above which the controller automaticallyswitches to error state.";
  }

  string getMoreInfo()
  {
    return "A zero value means that there is no limit. Note that whatever the current limit is, the controller switches to OVERCURRENT status if the current goes above 32A, even for a very brief time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the current threshold (in mA) above which the controller automatically switches to error state", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_overCurrentLimit(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Changes the PWM frequency used to control the motor. Low frequency is usually
 * more efficient and may help the motor to start, but an audible noise might be
 * generated. A higher frequency reduces the noise, but more energy is converted
 * into heat.
 *
 * @param newval : a floating point number corresponding to the PWM frequency used to control the motor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_frequency : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_frequency(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_frequency";
  }

  string getDescription()
  {
    return "Changes the PWM frequency used to control the motor.";
  }

  string getMoreInfo()
  {
    return "Low frequency is usually more efficient and may help the motor to start, but an audible noise might be generated. A higher frequency reduces the noise, but more energy is converted into heat.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the PWM frequency used to control the motor", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_frequency(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the PWM frequency used to control the motor.
 *
 * @return a floating point number corresponding to the PWM frequency used to control the motor
 *
 * On failure, throws an exception or returns Y_FREQUENCY_INVALID.
 */
class Motor_get_frequency : public YapiCommand /* arguments: */
{
public:
  Motor_get_frequency(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_frequency";
  }

  string getDescription()
  {
    return "Returns the PWM frequency used to control the motor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_frequency();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the duration (in ms) during which the motor is driven at low frequency to help
 * it start up.
 *
 * @return an integer corresponding to the duration (in ms) during which the motor is driven at low
 * frequency to help
 *         it start up
 *
 * On failure, throws an exception or returns Y_STARTERTIME_INVALID.
 */
class Motor_get_starterTime : public YapiCommand /* arguments: */
{
public:
  Motor_get_starterTime(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_starterTime";
  }

  string getDescription()
  {
    return "Returns the duration (in ms) during which the motor is driven at low frequency to helpit start up.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_starterTime();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the duration (in ms) during which the motor is driven at low frequency to help
 * it start up.
 *
 * @param newval : an integer corresponding to the duration (in ms) during which the motor is driven
 * at low frequency to help
 *         it start up
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_starterTime : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_starterTime(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_starterTime";
  }

  string getDescription()
  {
    return "Changes the duration (in ms) during which the motor is driven at low frequency to helpit start up.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the duration (in ms) during which the motor is driven at low frequency to help it start up", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_starterTime(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the delay in milliseconds allowed for the controller to run autonomously without
 * receiving any instruction from the control process. When this delay has elapsed,
 * the controller automatically stops the motor and switches to FAILSAFE error.
 * Failsafe security is disabled when the value is zero.
 *
 * @return an integer corresponding to the delay in milliseconds allowed for the controller to run
 * autonomously without
 *         receiving any instruction from the control process
 *
 * On failure, throws an exception or returns Y_FAILSAFETIMEOUT_INVALID.
 */
class Motor_get_failSafeTimeout : public YapiCommand /* arguments: */
{
public:
  Motor_get_failSafeTimeout(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_failSafeTimeout";
  }

  string getDescription()
  {
    return "Returns the delay in milliseconds allowed for the controller to run autonomously withoutreceiving any instruction from the control process.";
  }

  string getMoreInfo()
  {
    return "When this delay has elapsed, the controller automatically stops the motor and switches to FAILSAFE error. Failsafe security is disabled when the value is zero.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_failSafeTimeout();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the delay in milliseconds allowed for the controller to run autonomously without
 * receiving any instruction from the control process. When this delay has elapsed,
 * the controller automatically stops the motor and switches to FAILSAFE error.
 * Failsafe security is disabled when the value is zero.
 *
 * @param newval : an integer corresponding to the delay in milliseconds allowed for the controller to
 * run autonomously without
 *         receiving any instruction from the control process
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Motor_set_failSafeTimeout : public YapiCommand /* arguments: newval */
{
public:
  Motor_set_failSafeTimeout(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_failSafeTimeout";
  }

  string getDescription()
  {
    return "Changes the delay in milliseconds allowed for the controller to run autonomously withoutreceiving any instruction from the control process.";
  }

  string getMoreInfo()
  {
    return "When this delay has elapsed, the controller automatically stops the motor and switches to FAILSAFE error. Failsafe security is disabled when the value is zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the delay in milliseconds allowed for the controller to run autonomously without receiving any instruction from the control process", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_failSafeTimeout(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackMotor is YMotorValueCallback* (YMotorValueCallback)
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
class apifun_Motor_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Motor_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
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
class apifun_Motor_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Motor_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
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
class apifun_Motor_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_Motor_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Rearms the controller failsafe timer. When the motor is running and the failsafe feature
 * is active, this function should be called periodically to prove that the control process
 * is running properly. Otherwise, the motor is automatically stopped after the specified
 * timeout. Calling a motor <i>set</i> function implicitly rearms the failsafe timer.
 */
class apifun_Motor_keepALive : public YapiCommand /* arguments: */
{
public:
  apifun_Motor_keepALive(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "keepALive";
  }

  string getDescription()
  {
    return "Rearms the controller failsafe timer.";
  }

  string getMoreInfo()
  {
    return "When the motor is running and the failsafe feature is active, this function should be called periodically to prove that the control process is running properly. Otherwise, the motor is automatically stopped after the specified timeout. Calling a motor <i>set</i> function implicitly rearms the failsafe timer.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->keepALive();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reset the controller state to IDLE. This function must be invoked explicitly
 * after any error condition is signaled.
 */
class apifun_Motor_resetStatus : public YapiCommand /* arguments: */
{
public:
  apifun_Motor_resetStatus(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "resetStatus";
  }

  string getDescription()
  {
    return "Reset the controller state to IDLE.";
  }

  string getMoreInfo()
  {
    return "This function must be invoked explicitly after any error condition is signaled.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetStatus();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes progressively the power sent to the motor for a specific duration.
 *
 * @param targetPower : desired motor power, in percents (between -100% and +100%)
 * @param delay : duration (in ms) of the transition
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Motor_drivingForceMove : public YapiCommand /* arguments: targetPower delay */
{
public:
  apifun_Motor_drivingForceMove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "drivingForceMove";
  }

  string getDescription()
  {
    return "Changes progressively the power sent to the motor for a specific duration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "targetPower", "desired motor power, in percents (between -100% and +100%)", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "duration (in ms) of the transition", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->drivingForceMove((*args)[0]->get_doubleValue(),
                                     (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes progressively the braking force applied to the motor for a specific duration.
 *
 * @param targetPower : desired braking force, in percents
 * @param delay : duration (in ms) of the transition
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Motor_brakingForceMove : public YapiCommand /* arguments: targetPower delay */
{
public:
  apifun_Motor_brakingForceMove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "brakingForceMove";
  }

  string getDescription()
  {
    return "Changes progressively the braking force applied to the motor for a specific duration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "targetPower", "desired braking force, in percents", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(INT_ARG, "delay", "duration (in ms) of the transition", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMotor*>* list = enumerateTargets<YMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->brakingForceMove((*args)[0]->get_doubleValue(),
                                     (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YMotor implementation)

//--- (YMotor functions)
void YMotorCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YMotor>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Motor_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_motorStatus(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_drivingForce(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_drivingForce(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_brakingForce(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_brakingForce(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_cutOffVoltage(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_cutOffVoltage(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_overCurrentLimit(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_overCurrentLimit(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_frequency(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_frequency(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_starterTime(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_starterTime(this)));
    cmdList->push_back((YapiCommand*) (new Motor_get_failSafeTimeout(this)));
    cmdList->push_back((YapiCommand*) (new Motor_set_failSafeTimeout(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Motor_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Motor_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Motor_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Motor_keepALive(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Motor_resetStatus(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Motor_drivingForceMove(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Motor_brakingForceMove(this)));
  }

//--- (end of YMotor functions)
