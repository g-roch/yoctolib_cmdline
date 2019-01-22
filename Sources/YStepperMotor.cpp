/*********************************************************************
 *
 *  $Id: YStepperMotor.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle StepperMotor functions
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
#include "YStepperMotor.h"
#include "yocto_api.h"
#include "yocto_steppermotor.h"

using namespace std;

//--- (YStepperMotor definitions)

static const char *enumStepperState[] = {
    "ABSENT",
    "ALERT",
    "HI_Z",
    "STOP",
    "RUN",
    "BATCH",
    NULL
};

static const char *enumSteppingMode[] = {
    "MICROSTEP16",
    "MICROSTEP8",
    "MICROSTEP4",
    "HALFSTEP",
    "FULLSTEP",
    NULL
};

//--- (end of YStepperMotor definitions)


//--- (YStepperMotor implementation)
bool   YStepperMotorCmdLine::isModule(void)      { return false; }
string YStepperMotorCmdLine::YFunctionName(void) { return "YStepperMotor"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of motorState is int (StepperState)
// type of diags is int (StepperDiags)
// type of stepPos is double (StepPos)
// type of speed is double (MeasureVal)
// type of pullinSpeed is double (MeasureVal)
// type of maxAccel is double (MeasureVal)
// type of maxSpeed is double (MeasureVal)
// type of stepping is int (SteppingMode)
// type of overcurrent is int (UInt31)
// type of tCurrStop is int (UInt31)
// type of tCurrRun is int (UInt31)
// type of alertMode is string (AlertMode)
// type of auxMode is string (AuxMode)
// type of auxSignal is int (Int)
// type of command is string (Text)
/**
 * Returns the logical name of the stepper motor.
 *
 * @return a string corresponding to the logical name of the stepper motor
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class StepperMotor_get_logicalName : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the stepper motor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
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
 * Changes the logical name of the stepper motor. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the stepper motor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the stepper motor.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the stepper motor", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the stepper motor.
 *
 * @return a string corresponding to a short string representing the current state of the stepper motor
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class StepperMotor_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the stepper motor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
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
 * Returns the motor working state.
 *
 * @return a value among Y_MOTORSTATE_ABSENT, Y_MOTORSTATE_ALERT, Y_MOTORSTATE_HI_Z,
 * Y_MOTORSTATE_STOP, Y_MOTORSTATE_RUN and Y_MOTORSTATE_BATCH corresponding to the motor working state
 *
 * On failure, throws an exception or returns Y_MOTORSTATE_INVALID.
 */
class StepperMotor_get_motorState : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_motorState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_motorState";
  }

  string getDescription()
  {
    return "Returns the motor working state.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_motorState();
        string strval =  enumString(attrval,enumStepperState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the stepper motor controller diagnostics, as a bitmap.
 *
 * @return an integer corresponding to the stepper motor controller diagnostics, as a bitmap
 *
 * On failure, throws an exception or returns Y_DIAGS_INVALID.
 */
class StepperMotor_get_diags : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_diags(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_diags";
  }

  string getDescription()
  {
    return "Returns the stepper motor controller diagnostics, as a bitmap.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_diags();
        string strval =  bitString("VCTXLHOStho!", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current logical motor position, measured in steps.
 * This command does not cause any motor move, as its purpose is only to setup
 * the origin of the position counter. The fractional part of the position,
 * that corresponds to the physical position of the rotor, is not changed.
 * To trigger a motor move, use methods moveTo() or moveRel()
 * instead.
 *
 * @param newval : a floating point number corresponding to the current logical motor position, measured in steps
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_stepPos : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_stepPos(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_stepPos";
  }

  string getDescription()
  {
    return "Changes the current logical motor position, measured in steps.";
  }

  string getMoreInfo()
  {
    return "This command does not cause any motor move, as its purpose is only to setup the origin of the position counter. The fractional part of the position, that corresponds to the physical position of the rotor, is not changed. To trigger a motor move, use methods moveTo() or moveRel() instead.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the current logical motor position, measured in steps", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_stepPos(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current logical motor position, measured in steps.
 * The value may include a fractional part when micro-stepping is in use.
 *
 * @return a floating point number corresponding to the current logical motor position, measured in steps
 *
 * On failure, throws an exception or returns Y_STEPPOS_INVALID.
 */
class StepperMotor_get_stepPos : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_stepPos(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_stepPos";
  }

  string getDescription()
  {
    return "Returns the current logical motor position, measured in steps.";
  }

  string getMoreInfo()
  {
    return "The value may include a fractional part when micro-stepping is in use.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_stepPos();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns current motor speed, measured in steps per second.
 * To change speed, use method changeSpeed().
 *
 * @return a floating point number corresponding to current motor speed, measured in steps per second
 *
 * On failure, throws an exception or returns Y_SPEED_INVALID.
 */
class StepperMotor_get_speed : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_speed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_speed";
  }

  string getDescription()
  {
    return "Returns current motor speed, measured in steps per second.";
  }

  string getMoreInfo()
  {
    return "To change speed, use method changeSpeed().";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_speed();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the motor speed immediately reachable from stop state, measured in steps per second.
 *
 * @param newval : a floating point number corresponding to the motor speed immediately reachable from
 * stop state, measured in steps per second
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_pullinSpeed : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_pullinSpeed(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_pullinSpeed";
  }

  string getDescription()
  {
    return "Changes the motor speed immediately reachable from stop state, measured in steps per second.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the motor speed immediately reachable from stop state, measured in steps per second", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_pullinSpeed(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the motor speed immediately reachable from stop state, measured in steps per second.
 *
 * @return a floating point number corresponding to the motor speed immediately reachable from stop
 * state, measured in steps per second
 *
 * On failure, throws an exception or returns Y_PULLINSPEED_INVALID.
 */
class StepperMotor_get_pullinSpeed : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_pullinSpeed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_pullinSpeed";
  }

  string getDescription()
  {
    return "Returns the motor speed immediately reachable from stop state, measured in steps per second.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_pullinSpeed();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the maximal motor acceleration, measured in steps per second^2.
 *
 * @param newval : a floating point number corresponding to the maximal motor acceleration, measured
 * in steps per second^2
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_maxAccel : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_maxAccel(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_maxAccel";
  }

  string getDescription()
  {
    return "Changes the maximal motor acceleration, measured in steps per second^2.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the maximal motor acceleration, measured in steps per second^2", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_maxAccel(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximal motor acceleration, measured in steps per second^2.
 *
 * @return a floating point number corresponding to the maximal motor acceleration, measured in steps per second^2
 *
 * On failure, throws an exception or returns Y_MAXACCEL_INVALID.
 */
class StepperMotor_get_maxAccel : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_maxAccel(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_maxAccel";
  }

  string getDescription()
  {
    return "Returns the maximal motor acceleration, measured in steps per second^2.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_maxAccel();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the maximal motor speed, measured in steps per second.
 *
 * @param newval : a floating point number corresponding to the maximal motor speed, measured in steps per second
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_maxSpeed : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_maxSpeed(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_maxSpeed";
  }

  string getDescription()
  {
    return "Changes the maximal motor speed, measured in steps per second.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the maximal motor speed, measured in steps per second", "_DOUBLE", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_maxSpeed(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the maximal motor speed, measured in steps per second.
 *
 * @return a floating point number corresponding to the maximal motor speed, measured in steps per second
 *
 * On failure, throws an exception or returns Y_MAXSPEED_INVALID.
 */
class StepperMotor_get_maxSpeed : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_maxSpeed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_maxSpeed";
  }

  string getDescription()
  {
    return "Returns the maximal motor speed, measured in steps per second.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_maxSpeed();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the stepping mode used to drive the motor.
 *
 * @return a value among Y_STEPPING_MICROSTEP16, Y_STEPPING_MICROSTEP8, Y_STEPPING_MICROSTEP4,
 * Y_STEPPING_HALFSTEP and Y_STEPPING_FULLSTEP corresponding to the stepping mode used to drive the motor
 *
 * On failure, throws an exception or returns Y_STEPPING_INVALID.
 */
class StepperMotor_get_stepping : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_stepping(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_stepping";
  }

  string getDescription()
  {
    return "Returns the stepping mode used to drive the motor.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_stepping();
        string strval =  enumString(attrval,enumSteppingMode);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the stepping mode used to drive the motor.
 *
 * @param newval : a value among Y_STEPPING_MICROSTEP16, Y_STEPPING_MICROSTEP8, Y_STEPPING_MICROSTEP4,
 * Y_STEPPING_HALFSTEP and Y_STEPPING_FULLSTEP corresponding to the stepping mode used to drive the motor
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_stepping : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_stepping(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_stepping";
  }

  string getDescription()
  {
    return "Changes the stepping mode used to drive the motor.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among MICROSTEP16, MICROSTEP8, MICROSTEP4, HALFSTEP and FULLSTEP corresponding to the stepping mode used to drive the motor", "MICROSTEP16=0,MICROSTEP8=1,MICROSTEP4=2,HALFSTEP=3,FULLSTEP=4", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_stepping(Y_STEPPING_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the overcurrent alert and emergency stop threshold, measured in mA.
 *
 * @return an integer corresponding to the overcurrent alert and emergency stop threshold, measured in mA
 *
 * On failure, throws an exception or returns Y_OVERCURRENT_INVALID.
 */
class StepperMotor_get_overcurrent : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_overcurrent(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_overcurrent";
  }

  string getDescription()
  {
    return "Returns the overcurrent alert and emergency stop threshold, measured in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_overcurrent();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the overcurrent alert and emergency stop threshold, measured in mA.
 *
 * @param newval : an integer corresponding to the overcurrent alert and emergency stop threshold, measured in mA
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_overcurrent : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_overcurrent(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_overcurrent";
  }

  string getDescription()
  {
    return "Changes the overcurrent alert and emergency stop threshold, measured in mA.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the overcurrent alert and emergency stop threshold, measured in mA", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_overcurrent(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the torque regulation current when the motor is stopped, measured in mA.
 *
 * @return an integer corresponding to the torque regulation current when the motor is stopped, measured in mA
 *
 * On failure, throws an exception or returns Y_TCURRSTOP_INVALID.
 */
class StepperMotor_get_tCurrStop : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_tCurrStop(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_tCurrStop";
  }

  string getDescription()
  {
    return "Returns the torque regulation current when the motor is stopped, measured in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_tCurrStop();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the torque regulation current when the motor is stopped, measured in mA.
 *
 * @param newval : an integer corresponding to the torque regulation current when the motor is
 * stopped, measured in mA
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_tCurrStop : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_tCurrStop(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_tCurrStop";
  }

  string getDescription()
  {
    return "Changes the torque regulation current when the motor is stopped, measured in mA.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the torque regulation current when the motor is stopped, measured in mA", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_tCurrStop(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the torque regulation current when the motor is running, measured in mA.
 *
 * @return an integer corresponding to the torque regulation current when the motor is running, measured in mA
 *
 * On failure, throws an exception or returns Y_TCURRRUN_INVALID.
 */
class StepperMotor_get_tCurrRun : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_tCurrRun(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_tCurrRun";
  }

  string getDescription()
  {
    return "Returns the torque regulation current when the motor is running, measured in mA.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_tCurrRun();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the torque regulation current when the motor is running, measured in mA.
 *
 * @param newval : an integer corresponding to the torque regulation current when the motor is
 * running, measured in mA
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_tCurrRun : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_tCurrRun(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_tCurrRun";
  }

  string getDescription()
  {
    return "Changes the torque regulation current when the motor is running, measured in mA.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the torque regulation current when the motor is running, measured in mA", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_tCurrRun(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current value of the signal generated on the auxiliary output.
 *
 * @return an integer corresponding to the current value of the signal generated on the auxiliary output
 *
 * On failure, throws an exception or returns Y_AUXSIGNAL_INVALID.
 */
class StepperMotor_get_auxSignal : public YapiCommand /* arguments: */
{
public:
  StepperMotor_get_auxSignal(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_auxSignal";
  }

  string getDescription()
  {
    return "Returns the current value of the signal generated on the auxiliary output.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_auxSignal();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the value of the signal generated on the auxiliary output.
 * Acceptable values depend on the auxiliary output signal type configured.
 *
 * @param newval : an integer corresponding to the value of the signal generated on the auxiliary output
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class StepperMotor_set_auxSignal : public YapiCommand /* arguments: newval */
{
public:
  StepperMotor_set_auxSignal(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_auxSignal";
  }

  string getDescription()
  {
    return "Changes the value of the signal generated on the auxiliary output.";
  }

  string getMoreInfo()
  {
    return "Acceptable values depend on the auxiliary output signal type configured.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the value of the signal generated on the auxiliary output", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_auxSignal(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackStepperMotor is YStepperMotorValueCallback* (YStepperMotorValueCallback)
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
class apifun_StepperMotor_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
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
class apifun_StepperMotor_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
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
class apifun_StepperMotor_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reinitialize the controller and clear all alert flags.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_reset : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_reset(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "reset";
  }

  string getDescription()
  {
    return "Reinitialize the controller and clear all alert flags.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->reset();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the motor backward at the specified speed, to search for the motor home position.
 *
 * @param speed : desired speed, in steps per second.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_findHomePosition : public YapiCommand /* arguments: speed */
{
public:
  apifun_StepperMotor_findHomePosition(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "findHomePosition";
  }

  string getDescription()
  {
    return "Starts the motor backward at the specified speed, to search for the motor home position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "speed", "desired speed, in steps per second.", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->findHomePosition((*args)[0]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the motor at a given speed. The time needed to reach the requested speed
 * will depend on the acceleration parameters configured for the motor.
 *
 * @param speed : desired speed, in steps per second. The minimal non-zero speed
 *         is 0.001 pulse per second.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_changeSpeed : public YapiCommand /* arguments: speed */
{
public:
  apifun_StepperMotor_changeSpeed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "changeSpeed";
  }

  string getDescription()
  {
    return "Starts the motor at a given speed.";
  }

  string getMoreInfo()
  {
    return "The time needed to reach the requested speed will depend on the acceleration parameters configured for the motor.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "speed", "desired speed, in steps per second. The minimal non-zero speed is 0.001 pulse per second.", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->changeSpeed((*args)[0]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the motor to reach a given absolute position. The time needed to reach the requested
 * position will depend on the acceleration and max speed parameters configured for
 * the motor.
 *
 * @param absPos : absolute position, measured in steps from the origin.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_moveTo : public YapiCommand /* arguments: absPos */
{
public:
  apifun_StepperMotor_moveTo(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "moveTo";
  }

  string getDescription()
  {
    return "Starts the motor to reach a given absolute position.";
  }

  string getMoreInfo()
  {
    return "The time needed to reach the requested position will depend on the acceleration and max speed parameters configured for the motor.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "absPos", "absolute position, measured in steps from the origin.", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->moveTo((*args)[0]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the motor to reach a given relative position. The time needed to reach the requested
 * position will depend on the acceleration and max speed parameters configured for
 * the motor.
 *
 * @param relPos : relative position, measured in steps from the current position.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_moveRel : public YapiCommand /* arguments: relPos */
{
public:
  apifun_StepperMotor_moveRel(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "moveRel";
  }

  string getDescription()
  {
    return "Starts the motor to reach a given relative position.";
  }

  string getMoreInfo()
  {
    return "The time needed to reach the requested position will depend on the acceleration and max speed parameters configured for the motor.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "relPos", "relative position, measured in steps from the current position.", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->moveRel((*args)[0]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the motor to reach a given relative position, keeping the speed under the
 * specified limit. The time needed to reach the requested position will depend on
 * the acceleration parameters configured for the motor.
 *
 * @param relPos : relative position, measured in steps from the current position.
 * @param maxSpeed : limit speed, in steps per second.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_moveRelSlow : public YapiCommand /* arguments: relPos maxSpeed */
{
public:
  apifun_StepperMotor_moveRelSlow(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "moveRelSlow";
  }

  string getDescription()
  {
    return "Starts the motor to reach a given relative position, keeping the speed under thespecified limit.";
  }

  string getMoreInfo()
  {
    return "The time needed to reach the requested position will depend on the acceleration parameters configured for the motor.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "relPos", "relative position, measured in steps from the current position.", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "maxSpeed", "limit speed, in steps per second.", "_DOUBLE", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->moveRelSlow((*args)[0]->get_doubleValue(),
                                (*args)[1]->get_doubleValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Keep the motor in the same state for the specified amount of time, before processing next command.
 *
 * @param waitMs : wait time, specified in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_pause : public YapiCommand /* arguments: waitMs */
{
public:
  apifun_StepperMotor_pause(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "pause";
  }

  string getDescription()
  {
    return "Keep the motor in the same state for the specified amount of time, before processing next command.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "waitMs", "wait time, specified in milliseconds.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->pause((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the motor with an emergency alert, without taking any additional precaution.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_emergencyStop : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_emergencyStop(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "emergencyStop";
  }

  string getDescription()
  {
    return "Stops the motor with an emergency alert, without taking any additional precaution.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->emergencyStop();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Move one step in the direction opposite the direction set when the most recent alert was raised.
 * The move occurs even if the system is still in alert mode (end switch depressed). Caution.
 * use this function with great care as it may cause mechanical damages !
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_alertStepOut : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_alertStepOut(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "alertStepOut";
  }

  string getDescription()
  {
    return "Move one step in the direction opposite the direction set when the most recent alert was raised.";
  }

  string getMoreInfo()
  {
    return "The move occurs even if the system is still in alert mode (end switch depressed). Caution. use this function with great care as it may cause mechanical damages !";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->alertStepOut();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Move one single step in the selected direction without regards to end switches.
 * The move occurs even if the system is still in alert mode (end switch depressed). Caution.
 * use this function with great care as it may cause mechanical damages !
 *
 * @param dir : Value +1 or -1, according to the desired direction of the move
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_alertStepDir : public YapiCommand /* arguments: dir */
{
public:
  apifun_StepperMotor_alertStepDir(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "alertStepDir";
  }

  string getDescription()
  {
    return "Move one single step in the selected direction without regards to end switches.";
  }

  string getMoreInfo()
  {
    return "The move occurs even if the system is still in alert mode (end switch depressed). Caution. use this function with great care as it may cause mechanical damages !";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "dir", "Value +1 or -1, according to the desired direction of the move", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->alertStepDir((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the motor smoothly as soon as possible, without waiting for ongoing move completion.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_abortAndBrake : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_abortAndBrake(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "abortAndBrake";
  }

  string getDescription()
  {
    return "Stops the motor smoothly as soon as possible, without waiting for ongoing move completion.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->abortAndBrake();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Turn the controller into Hi-Z mode immediately, without waiting for ongoing move completion.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_StepperMotor_abortAndHiZ : public YapiCommand /* arguments: */
{
public:
  apifun_StepperMotor_abortAndHiZ(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "abortAndHiZ";
  }

  string getDescription()
  {
    return "Turn the controller into Hi-Z mode immediately, without waiting for ongoing move completion.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YStepperMotor*>* list = enumerateTargets<YStepperMotor>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->abortAndHiZ();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YStepperMotor implementation)

//--- (YStepperMotor functions)
void YStepperMotorCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YStepperMotor>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_motorState(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_diags(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_stepPos(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_stepPos(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_speed(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_pullinSpeed(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_pullinSpeed(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_maxAccel(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_maxAccel(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_maxSpeed(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_maxSpeed(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_stepping(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_stepping(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_overcurrent(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_overcurrent(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_tCurrStop(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_tCurrStop(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_tCurrRun(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_tCurrRun(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_get_auxSignal(this)));
    cmdList->push_back((YapiCommand*) (new StepperMotor_set_auxSignal(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_reset(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_findHomePosition(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_changeSpeed(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_moveTo(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_moveRel(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_moveRelSlow(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_pause(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_emergencyStop(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_alertStepOut(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_alertStepDir(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_abortAndBrake(this)));
    cmdList->push_back((YapiCommand*) (new apifun_StepperMotor_abortAndHiZ(this)));
  }

//--- (end of YStepperMotor functions)
