/*********************************************************************
 *
 *  $Id: YSpiPort.cpp 33722 2018-12-14 15:04:43Z seb $
 *
 *  Implements commands to handle SpiPort functions
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
#include "YSpiPort.h"
#include "yocto_api.h"
#include "yocto_spiport.h"

using namespace std;

//--- (YSpiPort definitions)

static const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

static const char *enumSerialVoltageLevel[] = {
    "OFF",
    "TTL3V",
    "TTL3VR",
    "TTL5V",
    "TTL5VR",
    "RS232",
    "RS485",
    NULL
};

static const char *enumPolarity[] = {
    "ACTIVE_LOW",
    "ACTIVE_HIGH",
    NULL
};

//--- (end of YSpiPort definitions)


//--- (YSpiPort implementation)
bool   YSpiPortCmdLine::isModule(void)      { return false; }
string YSpiPortCmdLine::YFunctionName(void) { return "YSpiPort"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of rxCount is int (UInt31)
// type of txCount is int (UInt31)
// type of errCount is int (UInt31)
// type of rxMsgCount is int (UInt31)
// type of txMsgCount is int (UInt31)
// type of lastMsg is string (Text)
// type of currentJob is string (Text)
// type of startupJob is string (Text)
// type of command is string (Text)
// type of voltageLevel is int (SerialVoltageLevel)
// type of protocol is string (Protocol)
// type of spiMode is string (SpiMode)
// type of ssPolarity is int (Polarity)
// type of shiftSampling is int (OnOff)
/**
 * Returns the logical name of the SPI port.
 *
 * @return a string corresponding to the logical name of the SPI port
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class SpiPort_get_logicalName : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the SPI port.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
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
 * Changes the logical name of the SPI port. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the SPI port
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the SPI port.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the SPI port", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the SPI port.
 *
 * @return a string corresponding to a short string representing the current state of the SPI port
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class SpiPort_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the SPI port.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
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
 * Returns the total number of bytes received since last reset.
 *
 * @return an integer corresponding to the total number of bytes received since last reset
 *
 * On failure, throws an exception or returns Y_RXCOUNT_INVALID.
 */
class SpiPort_get_rxCount : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_rxCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rxCount";
  }

  string getDescription()
  {
    return "Returns the total number of bytes received since last reset.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rxCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of bytes transmitted since last reset.
 *
 * @return an integer corresponding to the total number of bytes transmitted since last reset
 *
 * On failure, throws an exception or returns Y_TXCOUNT_INVALID.
 */
class SpiPort_get_txCount : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_txCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_txCount";
  }

  string getDescription()
  {
    return "Returns the total number of bytes transmitted since last reset.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_txCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of communication errors detected since last reset.
 *
 * @return an integer corresponding to the total number of communication errors detected since last reset
 *
 * On failure, throws an exception or returns Y_ERRCOUNT_INVALID.
 */
class SpiPort_get_errCount : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_errCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_errCount";
  }

  string getDescription()
  {
    return "Returns the total number of communication errors detected since last reset.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_errCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of messages received since last reset.
 *
 * @return an integer corresponding to the total number of messages received since last reset
 *
 * On failure, throws an exception or returns Y_RXMSGCOUNT_INVALID.
 */
class SpiPort_get_rxMsgCount : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_rxMsgCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_rxMsgCount";
  }

  string getDescription()
  {
    return "Returns the total number of messages received since last reset.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rxMsgCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of messages send since last reset.
 *
 * @return an integer corresponding to the total number of messages send since last reset
 *
 * On failure, throws an exception or returns Y_TXMSGCOUNT_INVALID.
 */
class SpiPort_get_txMsgCount : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_txMsgCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_txMsgCount";
  }

  string getDescription()
  {
    return "Returns the total number of messages send since last reset.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_txMsgCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the latest message fully received (for Line and Frame protocols).
 *
 * @return a string corresponding to the latest message fully received (for Line and Frame protocols)
 *
 * On failure, throws an exception or returns Y_LASTMSG_INVALID.
 */
class SpiPort_get_lastMsg : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_lastMsg(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_lastMsg";
  }

  string getDescription()
  {
    return "Returns the latest message fully received (for Line and Frame protocols).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_lastMsg();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the name of the job file currently in use.
 *
 * @return a string corresponding to the name of the job file currently in use
 *
 * On failure, throws an exception or returns Y_CURRENTJOB_INVALID.
 */
class SpiPort_get_currentJob : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_currentJob(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_currentJob";
  }

  string getDescription()
  {
    return "Returns the name of the job file currently in use.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_currentJob();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the job to use when the device is powered on.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the job to use when the device is powered on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_currentJob : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_currentJob(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_currentJob";
  }

  string getDescription()
  {
    return "Changes the job to use when the device is powered on.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the job to use when the device is powered on", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_currentJob(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the job file to use when the device is powered on.
 *
 * @return a string corresponding to the job file to use when the device is powered on
 *
 * On failure, throws an exception or returns Y_STARTUPJOB_INVALID.
 */
class SpiPort_get_startupJob : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_startupJob(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_startupJob";
  }

  string getDescription()
  {
    return "Returns the job file to use when the device is powered on.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_startupJob();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the job to use when the device is powered on.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the job to use when the device is powered on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_startupJob : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_startupJob(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_startupJob";
  }

  string getDescription()
  {
    return "Changes the job to use when the device is powered on.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the job to use when the device is powered on", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_startupJob(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the voltage level used on the serial line.
 *
 * @return a value among Y_VOLTAGELEVEL_OFF, Y_VOLTAGELEVEL_TTL3V, Y_VOLTAGELEVEL_TTL3VR,
 * Y_VOLTAGELEVEL_TTL5V, Y_VOLTAGELEVEL_TTL5VR, Y_VOLTAGELEVEL_RS232 and Y_VOLTAGELEVEL_RS485
 * corresponding to the voltage level used on the serial line
 *
 * On failure, throws an exception or returns Y_VOLTAGELEVEL_INVALID.
 */
class SpiPort_get_voltageLevel : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_voltageLevel(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_voltageLevel";
  }

  string getDescription()
  {
    return "Returns the voltage level used on the serial line.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_voltageLevel();
        string strval =  enumString(attrval,enumSerialVoltageLevel);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the voltage type used on the serial line. Valid
 * values  will depend on the Yoctopuce device model featuring
 * the serial port feature.  Check your device documentation
 * to find out which values are valid for that specific model.
 * Trying to set an invalid value will have no effect.
 *
 * @param newval : a value among Y_VOLTAGELEVEL_OFF, Y_VOLTAGELEVEL_TTL3V, Y_VOLTAGELEVEL_TTL3VR,
 * Y_VOLTAGELEVEL_TTL5V, Y_VOLTAGELEVEL_TTL5VR, Y_VOLTAGELEVEL_RS232 and Y_VOLTAGELEVEL_RS485
 * corresponding to the voltage type used on the serial line
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_voltageLevel : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_voltageLevel(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_voltageLevel";
  }

  string getDescription()
  {
    return "Changes the voltage type used on the serial line.";
  }

  string getMoreInfo()
  {
    return "Valid values will depend on the Yoctopuce device model featuring the serial port feature. Check your device documentation to find out which values are valid for that specific model. Trying to set an invalid value will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among OFF, TTL3V, TTL3VR, TTL5V, TTL5VR, RS232 and RS485 corresponding to the voltage type used on the serial line", "OFF=0,TTL3V=1,TTL3VR=2,TTL5V=3,TTL5VR=4,RS232=5,RS485=6", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_voltageLevel(Y_VOLTAGELEVEL_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the type of protocol used over the serial line, as a string.
 * Possible values are "Line" for ASCII messages separated by CR and/or LF,
 * "Frame:[timeout]ms" for binary messages separated by a delay time,
 * "Char" for a continuous ASCII stream or
 * "Byte" for a continuous binary stream.
 *
 * @return a string corresponding to the type of protocol used over the serial line, as a string
 *
 * On failure, throws an exception or returns Y_PROTOCOL_INVALID.
 */
class SpiPort_get_protocol : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_protocol(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_protocol";
  }

  string getDescription()
  {
    return "Returns the type of protocol used over the serial line, as a string.";
  }

  string getMoreInfo()
  {
    return "Possible values are \"Line\" for ASCII messages separated by CR and/or LF, \"Frame:[timeout]ms\" for binary messages separated by a delay time, \"Char\" for a continuous ASCII stream or \"Byte\" for a continuous binary stream.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_protocol();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the type of protocol used over the serial line.
 * Possible values are "Line" for ASCII messages separated by CR and/or LF,
 * "Frame:[timeout]ms" for binary messages separated by a delay time,
 * "Char" for a continuous ASCII stream or
 * "Byte" for a continuous binary stream.
 * The suffix "/[wait]ms" can be added to reduce the transmit rate so that there
 * is always at lest the specified number of milliseconds between each bytes sent.
 *
 * @param newval : a string corresponding to the type of protocol used over the serial line
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_protocol : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_protocol(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_protocol";
  }

  string getDescription()
  {
    return "Changes the type of protocol used over the serial line.";
  }

  string getMoreInfo()
  {
    return "Possible values are \"Line\" for ASCII messages separated by CR and/or LF, \"Frame:[timeout]ms\" for binary messages separated by a delay time, \"Char\" for a continuous ASCII stream or \"Byte\" for a continuous binary stream. The suffix \"/[wait]ms\" can be added to reduce the transmit rate so that there is always at lest the specified number of milliseconds between each bytes sent.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the type of protocol used over the serial line", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_protocol(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the SPI port communication parameters, as a string such as
 * "125000,0,msb". The string includes the baud rate, the SPI mode (between
 * 0 and 3) and the bit order.
 *
 * @return a string corresponding to the SPI port communication parameters, as a string such as
 *         "125000,0,msb"
 *
 * On failure, throws an exception or returns Y_SPIMODE_INVALID.
 */
class SpiPort_get_spiMode : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_spiMode(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_spiMode";
  }

  string getDescription()
  {
    return "Returns the SPI port communication parameters, as a string such as\"125000,0,msb\".";
  }

  string getMoreInfo()
  {
    return "The string includes the baud rate, the SPI mode (between 0 and 3) and the bit order.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_spiMode();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the SPI port communication parameters, with a string such as
 * "125000,0,msb". The string includes the baud rate, the SPI mode (between
 * 0 and 3) and the bit order.
 *
 * @param newval : a string corresponding to the SPI port communication parameters, with a string such as
 *         "125000,0,msb"
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_spiMode : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_spiMode(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_spiMode";
  }

  string getDescription()
  {
    return "Changes the SPI port communication parameters, with a string such as\"125000,0,msb\".";
  }

  string getMoreInfo()
  {
    return "The string includes the baud rate, the SPI mode (between 0 and 3) and the bit order.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the SPI port communication parameters, with a string such as \"125000,0,msb\"", "_STRING", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_spiMode(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the SS line polarity.
 *
 * @return either Y_SSPOLARITY_ACTIVE_LOW or Y_SSPOLARITY_ACTIVE_HIGH, according to the SS line polarity
 *
 * On failure, throws an exception or returns Y_SSPOLARITY_INVALID.
 */
class SpiPort_get_ssPolarity : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_ssPolarity(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_ssPolarity";
  }

  string getDescription()
  {
    return "Returns the SS line polarity.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_ssPolarity();
        string strval =  enumString(attrval,enumPolarity);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the SS line polarity.
 *
 * @param newval : either Y_SSPOLARITY_ACTIVE_LOW or Y_SSPOLARITY_ACTIVE_HIGH, according to the SS line polarity
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_ssPolarity : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_ssPolarity(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_ssPolarity";
  }

  string getDescription()
  {
    return "Changes the SS line polarity.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either ACTIVE_LOW or ACTIVE_HIGH, according to the SS line polarity", "ACTIVE_LOW=0,ACTIVE_HIGH=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_ssPolarity(Y_SSPOLARITY_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns true when the SDI line phase is shifted with regards to the SDO line.
 *
 * @return either Y_SHIFTSAMPLING_OFF or Y_SHIFTSAMPLING_ON, according to true when the SDI line phase
 * is shifted with regards to the SDO line
 *
 * On failure, throws an exception or returns Y_SHIFTSAMPLING_INVALID.
 */
class SpiPort_get_shiftSampling : public YapiCommand /* arguments: */
{
public:
  SpiPort_get_shiftSampling(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_shiftSampling";
  }

  string getDescription()
  {
    return "Returns true when the SDI line phase is shifted with regards to the SDO line.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_shiftSampling();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the SDI line sampling shift. When disabled, SDI line is
 * sampled in the middle of data output time. When enabled, SDI line is
 * samples at the end of data output time.
 *
 * @param newval : either Y_SHIFTSAMPLING_OFF or Y_SHIFTSAMPLING_ON, according to the SDI line sampling shift
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SpiPort_set_shiftSampling : public YapiCommand /* arguments: newval */
{
public:
  SpiPort_set_shiftSampling(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_shiftSampling";
  }

  string getDescription()
  {
    return "Changes the SDI line sampling shift.";
  }

  string getMoreInfo()
  {
    return "When disabled, SDI line is sampled in the middle of data output time. When enabled, SDI line is samples at the end of data output time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON, according to the SDI line sampling shift", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_shiftSampling(Y_SHIFTSAMPLING_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackSpiPort is YSpiPortValueCallback* (YSpiPortValueCallback)
// type of rxptr is int (int)
// type of rxbuff is bin (bin)
// type of rxbuffptr is int (int)
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
class apifun_SpiPort_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_SpiPort_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
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
class apifun_SpiPort_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_SpiPort_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
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
 * Clears the serial port buffer and resets counters to zero.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_reset : public YapiCommand /* arguments: */
{
public:
  apifun_SpiPort_reset(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "reset";
  }

  string getDescription()
  {
    return "Clears the serial port buffer and resets counters to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
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
 * Sends a single byte to the serial port.
 *
 * @param code : the byte to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_writeByte : public YapiCommand /* arguments: code */
{
public:
  apifun_SpiPort_writeByte(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "writeByte";
  }

  string getDescription()
  {
    return "Sends a single byte to the serial port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "code", "the byte to send", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeByte((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends an ASCII string to the serial port, as is.
 *
 * @param text : the text string to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_writeStr : public YapiCommand /* arguments: text */
{
public:
  apifun_SpiPort_writeStr(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "writeStr";
  }

  string getDescription()
  {
    return "Sends an ASCII string to the serial port, as is.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "text", "the text string to send", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeStr((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a binary buffer to the serial port, as is.
 *
 * @param buff : the binary buffer to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_writeBin : public YapiCommand /* arguments: buff */
{
public:
  apifun_SpiPort_writeBin(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "writeBin";
  }

  string getDescription()
  {
    return "Sends a binary buffer to the serial port, as is.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(BIN_ARG, "buff", "the binary buffer to send", "_BIN", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeBin((*args)[0]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a byte sequence (provided as a list of bytes) to the serial port.
 *
 * @param byteList : a list of byte codes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_writeArray : public YapiCommand /* arguments: byteList */
{
public:
  apifun_SpiPort_writeArray(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "writeArray";
  }

  string getDescription()
  {
    return "Sends a byte sequence (provided as a list of bytes) to the serial port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INTARR_ARG, "byteList", "a list of byte codes", "_INTARR", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeArray((*args)[0]->get_intArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a byte sequence (provided as a hexadecimal string) to the serial port.
 *
 * @param hexString : a string of hexadecimal byte codes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_writeHex : public YapiCommand /* arguments: hexString */
{
public:
  apifun_SpiPort_writeHex(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "writeHex";
  }

  string getDescription()
  {
    return "Sends a byte sequence (provided as a hexadecimal string) to the serial port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "hexString", "a string of hexadecimal byte codes", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeHex((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends an ASCII string to the serial port, followed by a line break (CR LF).
 *
 * @param text : the text string to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_writeLine : public YapiCommand /* arguments: text */
{
public:
  apifun_SpiPort_writeLine(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "writeLine";
  }

  string getDescription()
  {
    return "Sends an ASCII string to the serial port, followed by a line break (CR LF).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "text", "the text string to send", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeLine((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads one byte from the receive buffer, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer,
 * or if there is no data available yet, the function returns YAPI_NO_MORE_DATA.
 *
 * @return the next byte
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_readByte : public YapiCommand /* arguments: */
{
public:
  apifun_SpiPort_readByte(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "readByte";
  }

  string getDescription()
  {
    return "Reads one byte from the receive buffer, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, or if there is no data available yet, the function returns YAPI_NO_MORE_DATA.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->readByte();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a string, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nChars : the maximum number of characters to read
 *
 * @return a string with receive buffer contents
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_readStr : public YapiCommand /* arguments: nChars */
{
public:
  apifun_SpiPort_readStr(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "readStr";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a string, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nChars", "the maximum number of characters to read", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readStr((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a binary buffer, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nChars : the maximum number of bytes to read
 *
 * @return a binary object with receive buffer contents
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_readBin : public YapiCommand /* arguments: nChars */
{
public:
  apifun_SpiPort_readBin(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "readBin";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a binary buffer, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nChars", "the maximum number of bytes to read", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readBin((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a list of bytes, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nChars : the maximum number of bytes to read
 *
 * @return a sequence of bytes with receive buffer contents
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_readArray : public YapiCommand /* arguments: nChars */
{
public:
  apifun_SpiPort_readArray(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "readArray";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a list of bytes, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nChars", "the maximum number of bytes to read", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->readArray((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a hexadecimal string, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nBytes : the maximum number of bytes to read
 *
 * @return a string with receive buffer contents, encoded in hexadecimal
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_readHex : public YapiCommand /* arguments: nBytes */
{
public:
  apifun_SpiPort_readHex(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "readHex";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a hexadecimal string, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nBytes", "the maximum number of bytes to read", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readHex((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads a single line (or message) from the receive buffer, starting at current stream position.
 * This function is intended to be used when the serial port is configured for a message protocol,
 * such as 'Line' mode or frame protocols.
 *
 * If data at current stream position is not available anymore in the receive buffer,
 * the function returns the oldest available line and moves the stream position just after.
 * If no new full line is received, the function returns an empty line.
 *
 * @return a string with a single line of text
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_readLine : public YapiCommand /* arguments: */
{
public:
  apifun_SpiPort_readLine(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "readLine";
  }

  string getDescription()
  {
    return "Reads a single line (or message) from the receive buffer, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "This function is intended to be used when the serial port is configured for a message protocol, such as 'Line' mode or frame protocols.\nIf data at current stream position is not available anymore in the receive buffer, the function returns the oldest available line and moves the stream position just after. If no new full line is received, the function returns an empty line.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readLine();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Searches for incoming messages in the serial port receive buffer matching a given pattern,
 * starting at current position. This function will only compare and return printable characters
 * in the message strings. Binary protocols are handled as hexadecimal strings.
 *
 * The search returns all messages matching the expression provided as argument in the buffer.
 * If no matching message is found, the search waits for one up to the specified maximum timeout
 * (in milliseconds).
 *
 * @param pattern : a limited regular expression describing the expected message format,
 *         or an empty string if all messages should be returned (no filtering).
 *         When using binary protocols, the format applies to the hexadecimal
 *         representation of the message.
 * @param maxWait : the maximum number of milliseconds to wait for a message if none is found
 *         in the receive buffer.
 *
 * @return an array of strings containing the messages found, if any.
 *         Binary messages are converted to hexadecimal representation.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SpiPort_readMessages : public YapiCommand /* arguments: pattern maxWait */
{
public:
  apifun_SpiPort_readMessages(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "readMessages";
  }

  string getDescription()
  {
    return "Searches for incoming messages in the serial port receive buffer matching a given pattern,starting at current position.";
  }

  string getMoreInfo()
  {
    return "This function will only compare and return printable characters in the message strings. Binary protocols are handled as hexadecimal strings.\nThe search returns all messages matching the expression provided as argument in the buffer. If no matching message is found, the search waits for one up to the specified maximum timeout (in milliseconds).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pattern", "a limited regular expression describing the expected message format, or an empty string if all messages should be returned (no filtering). When using binary protocols, the format applies to the hexadecimal representation of the message.", "_STRING", false));
    res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum number of milliseconds to wait for a message if none is found in the receive buffer.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<string> value = (*list)[i]->readMessages((*args)[0]->get_stringValue(),
                                                        (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the current internal stream position to the specified value. This function
 * does not affect the device, it only changes the value stored in the API object
 * for the next read operations.
 *
 * @param absPos : the absolute position index for next read operations.
 *
 * @return nothing.
 */
class apifun_SpiPort_read_seek : public YapiCommand /* arguments: absPos */
{
public:
  apifun_SpiPort_read_seek(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "read_seek";
  }

  string getDescription()
  {
    return "Changes the current internal stream position to the specified value.";
  }

  string getMoreInfo()
  {
    return "This function does not affect the device, it only changes the value stored in the API object for the next read operations.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "absPos", "the absolute position index for next read operations.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->read_seek((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the current absolute stream position pointer of the API object.
 *
 * @return the absolute position index for next read operations.
 */
class apifun_SpiPort_read_tell : public YapiCommand /* arguments: */
{
public:
  apifun_SpiPort_read_tell(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "read_tell";
  }

  string getDescription()
  {
    return "Returns the current absolute stream position pointer of the API object.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->read_tell();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the number of bytes available to read in the input buffer starting from the
 * current absolute stream position pointer of the API object.
 *
 * @return the number of bytes available to read
 */
class apifun_SpiPort_read_avail : public YapiCommand /* arguments: */
{
public:
  apifun_SpiPort_read_avail(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "read_avail";
  }

  string getDescription()
  {
    return "Returns the number of bytes available to read in the input buffer starting from thecurrent absolute stream position pointer of the API object.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->read_avail();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a text line query to the serial port, and reads the reply, if any.
 * This function is intended to be used when the serial port is configured for 'Line' protocol.
 *
 * @param query : the line query to send (without CR/LF)
 * @param maxWait : the maximum number of milliseconds to wait for a reply.
 *
 * @return the next text line received after sending the text query, as a string.
 *         Additional lines can be obtained by calling readLine or readMessages.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SpiPort_queryLine : public YapiCommand /* arguments: query maxWait */
{
public:
  apifun_SpiPort_queryLine(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "queryLine";
  }

  string getDescription()
  {
    return "Sends a text line query to the serial port, and reads the reply, if any.";
  }

  string getMoreInfo()
  {
    return "This function is intended to be used when the serial port is configured for 'Line' protocol.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "query", "the line query to send (without CR/LF)", "_STRING", false));
    res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum number of milliseconds to wait for a reply.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->queryLine((*args)[0]->get_stringValue(),
                                             (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Saves the job definition string (JSON data) into a job file.
 * The job file can be later enabled using selectJob().
 *
 * @param jobfile : name of the job file to save on the device filesystem
 * @param jsonDef : a string containing a JSON definition of the job
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_uploadJob : public YapiCommand /* arguments: jobfile jsonDef */
{
public:
  apifun_SpiPort_uploadJob(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "uploadJob";
  }

  string getDescription()
  {
    return "Saves the job definition string (JSON data) into a job file.";
  }

  string getMoreInfo()
  {
    return "The job file can be later enabled using selectJob().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "jobfile", "name of the job file to save on the device filesystem", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "jsonDef", "a string containing a JSON definition of the job", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->uploadJob((*args)[0]->get_stringValue(),
                              (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Load and start processing the specified job file. The file must have
 * been previously created using the user interface or uploaded on the
 * device filesystem using the uploadJob() function.
 *
 * @param jobfile : name of the job file (on the device filesystem)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_selectJob : public YapiCommand /* arguments: jobfile */
{
public:
  apifun_SpiPort_selectJob(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "selectJob";
  }

  string getDescription()
  {
    return "Load and start processing the specified job file.";
  }

  string getMoreInfo()
  {
    return "The file must have been previously created using the user interface or uploaded on the device filesystem using the uploadJob() function.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "jobfile", "name of the job file (on the device filesystem)", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->selectJob((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Manually sets the state of the SS line. This function has no effect when
 * the SS line is handled automatically.
 *
 * @param val : 1 to turn SS active, 0 to release SS.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SpiPort_set_SS : public YapiCommand /* arguments: val */
{
public:
  apifun_SpiPort_set_SS(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_SS";
  }

  string getDescription()
  {
    return "Manually sets the state of the SS line.";
  }

  string getMoreInfo()
  {
    return "This function has no effect when the SS line is handled automatically.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "val", "1 to turn SS active, 0 to release SS.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YSpiPort*>* list = enumerateTargets<YSpiPort>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_SS((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YSpiPort implementation)

//--- (YSpiPort functions)
void YSpiPortCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YSpiPort>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new SpiPort_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_rxCount(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_txCount(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_errCount(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_rxMsgCount(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_txMsgCount(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_lastMsg(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_currentJob(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_currentJob(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_startupJob(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_startupJob(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_voltageLevel(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_voltageLevel(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_protocol(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_protocol(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_spiMode(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_spiMode(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_ssPolarity(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_ssPolarity(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_get_shiftSampling(this)));
    cmdList->push_back((YapiCommand*) (new SpiPort_set_shiftSampling(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_reset(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_writeByte(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_writeStr(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_writeBin(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_writeArray(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_writeHex(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_writeLine(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_readByte(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_readStr(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_readBin(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_readArray(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_readHex(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_readLine(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_readMessages(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_read_seek(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_read_tell(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_read_avail(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_queryLine(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_uploadJob(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_selectJob(this)));
    cmdList->push_back((YapiCommand*) (new apifun_SpiPort_set_SS(this)));
  }

//--- (end of YSpiPort functions)
