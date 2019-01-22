/*********************************************************************
 *
 *  $Id: YDigitalIO.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle DigitalIO functions
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
#include "YDigitalIO.h"
#include "yocto_api.h"
#include "yocto_digitalio.h"

using namespace std;

//--- (YDigitalIO definitions)

static const char *enumIOVoltage[] = {
    "USB_5V",
    "USB_3V",
    "EXT_V",
    NULL
};

//--- (end of YDigitalIO definitions)


//--- (YDigitalIO implementation)
bool   YDigitalIOCmdLine::isModule(void)      { return false; }
string YDigitalIOCmdLine::YFunctionName(void) { return "YDigitalIO"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of portState is int (BitByte)
// type of portDirection is int (BitByte)
// type of portOpenDrain is int (BitByte)
// type of portPolarity is int (BitByte)
// type of portDiags is int (DigitalIODiags)
// type of portSize is int (UInt31)
// type of outputVoltage is int (IOVoltage)
// type of command is string (Text)
/**
 * Returns the logical name of the digital IO port.
 *
 * @return a string corresponding to the logical name of the digital IO port
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class DigitalIO_get_logicalName : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the digital IO port.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
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
 * Changes the logical name of the digital IO port. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the digital IO port
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DigitalIO_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  DigitalIO_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the digital IO port.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the digital IO port", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the digital IO port.
 *
 * @return a string corresponding to a short string representing the current state of the digital IO port
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class DigitalIO_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the digital IO port.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
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
 * Returns the digital IO port state as an integer with each bit
 * representing a channel
 * value 0 = 0b00000000 -> all channels are OFF
 * value 1 = 0b00000001 -> channel #0 is ON
 * value 2 = 0b00000010 -> channel #1 is ON
 * value 3 = 0b00000011 -> channels #0 and #1 are ON
 * value 4 = 0b00000100 -> channel #2 is ON
 * and so on...
 *
 * @return an integer corresponding to the digital IO port state as an integer with each bit
 *         representing a channel
 *         value 0 = 0b00000000 -> all channels are OFF
 *         value 1 = 0b00000001 -> channel #0 is ON
 *         value 2 = 0b00000010 -> channel #1 is ON
 *         value 3 = 0b00000011 -> channels #0 and #1 are ON
 *         value 4 = 0b00000100 -> channel #2 is ON
 *         and so on.
 *
 * On failure, throws an exception or returns Y_PORTSTATE_INVALID.
 */
class DigitalIO_get_portState : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_portState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_portState";
  }

  string getDescription()
  {
    return "Returns the digital IO port state as an integer with each bit representing a channel value 0 = 0b00000000 -> all channels are OFF value 1 = 0b00000001 -> channel #0 is ON value 2 = 0b00000010 -> channel #1 is ON value 3 = 0b00000011 -> channels #0 and #1 are ON value 4 = 0b00000100 -> channel #2 is ONand so on.";
  }

  string getMoreInfo()
  {
    return "..";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_portState();
        string strval =  bitString("11111111", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the state of all digital IO port's channels at once,
 * the parameter is an integer with  each bit representing a channel.
 * Bit 0 matches channel #0. So:
 * To set all channels to  0 -> 0b00000000 -> parameter = 0
 * To set channel #0 to 1 -> 0b00000001 -> parameter =  1
 * To set channel #1 to  1 -> 0b00000010 -> parameter = 2
 * To set channel #0 and #1 -> 0b00000011 -> parameter =  3
 * To set channel #2 to 1 -> 0b00000100 -> parameter =  4
 * an so on....
 * Only channels configured as output, thanks to portDirection,
 * are affected.
 *
 * @param newval : an integer corresponding to the state of all digital IO port's channels at once,
 *         the parameter is an integer with  each bit representing a channel
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DigitalIO_set_portState : public YapiCommand /* arguments: newval */
{
public:
  DigitalIO_set_portState(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_portState";
  }

  string getDescription()
  {
    return "Changes the state of all digital IO port's channels at once,the parameter is an integer with each bit representing a channel.";
  }

  string getMoreInfo()
  {
    return "Bit 0 matches channel #0. So: To set all channels to 0 -> 0b00000000 -> parameter = 0 To set channel #0 to 1 -> 0b00000001 -> parameter = 1 To set channel #1 to 1 -> 0b00000010 -> parameter = 2 To set channel #0 and #1 -> 0b00000011 -> parameter = 3 To set channel #2 to 1 -> 0b00000100 -> parameter = 4 an so on.... Only channels configured as output, thanks to portDirection, are affected.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the state of all digital IO port's channels at once, the parameter is an integer with each bit representing a channel", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_portState(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the IO direction of all bits (i.e. channels) of the port: 0 makes a bit an input, 1 makes it an output.
 *
 * @return an integer corresponding to the IO direction of all bits (i.e
 *
 * On failure, throws an exception or returns Y_PORTDIRECTION_INVALID.
 */
class DigitalIO_get_portDirection : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_portDirection(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_portDirection";
  }

  string getDescription()
  {
    return "Returns the IO direction of all bits (i.";
  }

  string getMoreInfo()
  {
    return "e. channels) of the port: 0 makes a bit an input, 1 makes it an output.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_portDirection();
        string strval =  bitString("11111111", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the IO direction of all bits (i.e. channels) of the port: 0 makes a bit an input, 1 makes it an output.
 * Remember to call the saveToFlash() method  to make sure the setting is kept after a reboot.
 *
 * @param newval : an integer corresponding to the IO direction of all bits (i.e
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DigitalIO_set_portDirection : public YapiCommand /* arguments: newval */
{
public:
  DigitalIO_set_portDirection(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_portDirection";
  }

  string getDescription()
  {
    return "Changes the IO direction of all bits (i.";
  }

  string getMoreInfo()
  {
    return "e. channels) of the port: 0 makes a bit an input, 1 makes it an output. Remember to call the saveToFlash() method to make sure the setting is kept after a reboot.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the IO direction of all bits (i.e", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_portDirection(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the electrical interface for each bit of the port. For each bit set to 0  the matching I/O
 * works in the regular,
 * intuitive way, for each bit set to 1, the I/O works in reverse mode.
 *
 * @return an integer corresponding to the electrical interface for each bit of the port
 *
 * On failure, throws an exception or returns Y_PORTOPENDRAIN_INVALID.
 */
class DigitalIO_get_portOpenDrain : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_portOpenDrain(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_portOpenDrain";
  }

  string getDescription()
  {
    return "Returns the electrical interface for each bit of the port.";
  }

  string getMoreInfo()
  {
    return "For each bit set to 0 the matching I/O works in the regular, intuitive way, for each bit set to 1, the I/O works in reverse mode.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_portOpenDrain();
        string strval =  bitString("11111111", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the electrical interface for each bit of the port. 0 makes a bit a regular input/output, 1 makes
 * it an open-drain (open-collector) input/output. Remember to call the
 * saveToFlash() method  to make sure the setting is kept after a reboot.
 *
 * @param newval : an integer corresponding to the electrical interface for each bit of the port
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DigitalIO_set_portOpenDrain : public YapiCommand /* arguments: newval */
{
public:
  DigitalIO_set_portOpenDrain(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_portOpenDrain";
  }

  string getDescription()
  {
    return "Changes the electrical interface for each bit of the port.";
  }

  string getMoreInfo()
  {
    return "0 makes a bit a regular input/output, 1 makes it an open-drain (open-collector) input/output. Remember to call the saveToFlash() method to make sure the setting is kept after a reboot.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the electrical interface for each bit of the port", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_portOpenDrain(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the polarity of all the bits of the port.  For each bit set to 0, the matching I/O works the regular,
 * intuitive way; for each bit set to 1, the I/O works in reverse mode.
 *
 * @return an integer corresponding to the polarity of all the bits of the port
 *
 * On failure, throws an exception or returns Y_PORTPOLARITY_INVALID.
 */
class DigitalIO_get_portPolarity : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_portPolarity(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_portPolarity";
  }

  string getDescription()
  {
    return "Returns the polarity of all the bits of the port.";
  }

  string getMoreInfo()
  {
    return "For each bit set to 0, the matching I/O works the regular, intuitive way; for each bit set to 1, the I/O works in reverse mode.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_portPolarity();
        string strval =  bitString("11111111", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the polarity of all the bits of the port: For each bit set to 0, the matching I/O works the regular,
 * intuitive way; for each bit set to 1, the I/O works in reverse mode.
 * Remember to call the saveToFlash() method  to make sure the setting will be kept after a reboot.
 *
 * @param newval : an integer corresponding to the polarity of all the bits of the port: For each bit
 * set to 0, the matching I/O works the regular,
 *         intuitive way; for each bit set to 1, the I/O works in reverse mode
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DigitalIO_set_portPolarity : public YapiCommand /* arguments: newval */
{
public:
  DigitalIO_set_portPolarity(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_portPolarity";
  }

  string getDescription()
  {
    return "Changes the polarity of all the bits of the port: For each bit set to 0, the matching I/O works the regular,intuitive way; for each bit set to 1, the I/O works in reverse mode.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method to make sure the setting will be kept after a reboot.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the polarity of all the bits of the port: For each bit set to 0, the matching I/O works the regular, intuitive way; for each bit set to 1, the I/O works in reverse mode", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_portPolarity(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the port state diagnostics (Yocto-IO and Yocto-MaxiIO-V2 only). Bit 0 indicates a shortcut on
 * output 0, etc. Bit 8 indicates a power failure, and bit 9 signals overheating (overcurrent).
 * During normal use, all diagnostic bits should stay clear.
 *
 * @return an integer corresponding to the port state diagnostics (Yocto-IO and Yocto-MaxiIO-V2 only)
 *
 * On failure, throws an exception or returns Y_PORTDIAGS_INVALID.
 */
class DigitalIO_get_portDiags : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_portDiags(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_portDiags";
  }

  string getDescription()
  {
    return "Returns the port state diagnostics (Yocto-IO and Yocto-MaxiIO-V2 only).";
  }

  string getMoreInfo()
  {
    return "Bit 0 indicates a shortcut on output 0, etc. Bit 8 indicates a power failure, and bit 9 signals overheating (overcurrent). During normal use, all diagnostic bits should stay clear.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_portDiags();
        string strval =  bitString("012345678TP", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of bits (i.e. channels)implemented in the I/O port.
 *
 * @return an integer corresponding to the number of bits (i.e
 *
 * On failure, throws an exception or returns Y_PORTSIZE_INVALID.
 */
class DigitalIO_get_portSize : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_portSize(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_portSize";
  }

  string getDescription()
  {
    return "Returns the number of bits (i.";
  }

  string getMoreInfo()
  {
    return "e. channels)implemented in the I/O port.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_portSize();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the voltage source used to drive output bits.
 *
 * @return a value among Y_OUTPUTVOLTAGE_USB_5V, Y_OUTPUTVOLTAGE_USB_3V and Y_OUTPUTVOLTAGE_EXT_V
 * corresponding to the voltage source used to drive output bits
 *
 * On failure, throws an exception or returns Y_OUTPUTVOLTAGE_INVALID.
 */
class DigitalIO_get_outputVoltage : public YapiCommand /* arguments: */
{
public:
  DigitalIO_get_outputVoltage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_outputVoltage";
  }

  string getDescription()
  {
    return "Returns the voltage source used to drive output bits.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_outputVoltage();
        string strval =  enumString(attrval,enumIOVoltage);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the voltage source used to drive output bits.
 * Remember to call the saveToFlash() method  to make sure the setting is kept after a reboot.
 *
 * @param newval : a value among Y_OUTPUTVOLTAGE_USB_5V, Y_OUTPUTVOLTAGE_USB_3V and
 * Y_OUTPUTVOLTAGE_EXT_V corresponding to the voltage source used to drive output bits
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DigitalIO_set_outputVoltage : public YapiCommand /* arguments: newval */
{
public:
  DigitalIO_set_outputVoltage(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_outputVoltage";
  }

  string getDescription()
  {
    return "Changes the voltage source used to drive output bits.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method to make sure the setting is kept after a reboot.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among USB_5V, USB_3V and EXT_V corresponding to the voltage source used to drive output bits", "USB_5V=0,USB_3V=1,EXT_V=2", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_outputVoltage(Y_OUTPUTVOLTAGE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackDigitalIO is YDigitalIOValueCallback* (YDigitalIOValueCallback)
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
class apifun_DigitalIO_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_DigitalIO_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
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
class apifun_DigitalIO_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_DigitalIO_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
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
class apifun_DigitalIO_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_DigitalIO_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets a single bit (i.e. channel) of the I/O port.
 *
 * @param bitno : the bit number; lowest bit has index 0
 * @param bitstate : the state of the bit (1 or 0)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_set_bitState : public YapiCommand /* arguments: bitno bitstate */
{
public:
  apifun_DigitalIO_set_bitState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_bitState";
  }

  string getDescription()
  {
    return "Sets a single bit (i.";
  }

  string getMoreInfo()
  {
    return "e. channel) of the I/O port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "bitstate", "the state of the bit (1 or 0)", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_bitState((int)(*args)[0]->get_intValue(),
                                 (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the state of a single bit (i.e. channel)  of the I/O port.
 *
 * @param bitno : the bit number; lowest bit has index 0
 *
 * @return the bit state (0 or 1)
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_get_bitState : public YapiCommand /* arguments: bitno */
{
public:
  apifun_DigitalIO_get_bitState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_bitState";
  }

  string getDescription()
  {
    return "Returns the state of a single bit (i.";
  }

  string getMoreInfo()
  {
    return "e. channel) of the I/O port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_bitState((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reverts a single bit (i.e. channel) of the I/O port.
 *
 * @param bitno : the bit number; lowest bit has index 0
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_toggle_bitState : public YapiCommand /* arguments: bitno */
{
public:
  apifun_DigitalIO_toggle_bitState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "toggle_bitState";
  }

  string getDescription()
  {
    return "Reverts a single bit (i.";
  }

  string getMoreInfo()
  {
    return "e. channel) of the I/O port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->toggle_bitState((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes  the direction of a single bit (i.e. channel) from the I/O port.
 *
 * @param bitno : the bit number; lowest bit has index 0
 * @param bitdirection : direction to set, 0 makes the bit an input, 1 makes it an output.
 *         Remember to call the   saveToFlash() method to make sure the setting is kept after a reboot.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_set_bitDirection : public YapiCommand /* arguments: bitno bitdirection */
{
public:
  apifun_DigitalIO_set_bitDirection(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_bitDirection";
  }

  string getDescription()
  {
    return "Changes the direction of a single bit (i.";
  }

  string getMoreInfo()
  {
    return "e. channel) from the I/O port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "bitdirection", "direction to set, 0 makes the bit an input, 1 makes it an output. Remember to call the saveToFlash() method to make sure the setting is kept after a reboot.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_bitDirection((int)(*args)[0]->get_intValue(),
                                     (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the direction of a single bit (i.e. channel) from the I/O port (0 means the bit is an
 * input, 1  an output).
 *
 * @param bitno : the bit number; lowest bit has index 0
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_get_bitDirection : public YapiCommand /* arguments: bitno */
{
public:
  apifun_DigitalIO_get_bitDirection(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_bitDirection";
  }

  string getDescription()
  {
    return "Returns the direction of a single bit (i.";
  }

  string getMoreInfo()
  {
    return "e. channel) from the I/O port (0 means the bit is an input, 1 an output).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_bitDirection((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the polarity of a single bit from the I/O port.
 *
 * @param bitno : the bit number; lowest bit has index 0.
 * @param bitpolarity : polarity to set, 0 makes the I/O work in regular mode, 1 makes the I/O  works
 * in reverse mode.
 *         Remember to call the   saveToFlash() method to make sure the setting is kept after a reboot.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_set_bitPolarity : public YapiCommand /* arguments: bitno bitpolarity */
{
public:
  apifun_DigitalIO_set_bitPolarity(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_bitPolarity";
  }

  string getDescription()
  {
    return "Changes the polarity of a single bit from the I/O port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "bitpolarity", "polarity to set, 0 makes the I/O work in regular mode, 1 makes the I/O works in reverse mode. Remember to call the saveToFlash() method to make sure the setting is kept after a reboot.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_bitPolarity((int)(*args)[0]->get_intValue(),
                                    (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the polarity of a single bit from the I/O port (0 means the I/O works in regular mode, 1
 * means the I/O  works in reverse mode).
 *
 * @param bitno : the bit number; lowest bit has index 0
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_get_bitPolarity : public YapiCommand /* arguments: bitno */
{
public:
  apifun_DigitalIO_get_bitPolarity(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_bitPolarity";
  }

  string getDescription()
  {
    return "Returns the polarity of a single bit from the I/O port (0 means the I/O works in regular mode, 1 means the I/O works in reverse mode).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_bitPolarity((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes  the electrical interface of a single bit from the I/O port.
 *
 * @param bitno : the bit number; lowest bit has index 0
 * @param opendrain : 0 makes a bit a regular input/output, 1 makes
 *         it an open-drain (open-collector) input/output. Remember to call the
 *         saveToFlash() method to make sure the setting is kept after a reboot.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_set_bitOpenDrain : public YapiCommand /* arguments: bitno opendrain */
{
public:
  apifun_DigitalIO_set_bitOpenDrain(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "set_bitOpenDrain";
  }

  string getDescription()
  {
    return "Changes the electrical interface of a single bit from the I/O port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "opendrain", "0 makes a bit a regular input/output, 1 makes it an open-drain (open-collector) input/output. Remember to call the saveToFlash() method to make sure the setting is kept after a reboot.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_bitOpenDrain((int)(*args)[0]->get_intValue(),
                                     (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the type of electrical interface of a single bit from the I/O port. (0 means the bit is an
 * input, 1  an output).
 *
 * @param bitno : the bit number; lowest bit has index 0
 *
 * @return   0 means the a bit is a regular input/output, 1 means the bit is an open-drain
 *         (open-collector) input/output.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_get_bitOpenDrain : public YapiCommand /* arguments: bitno */
{
public:
  apifun_DigitalIO_get_bitOpenDrain(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_bitOpenDrain";
  }

  string getDescription()
  {
    return "Returns the type of electrical interface of a single bit from the I/O port.";
  }

  string getMoreInfo()
  {
    return "(0 means the bit is an input, 1 an output).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_bitOpenDrain((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Triggers a pulse on a single bit for a specified duration. The specified bit
 * will be turned to 1, and then back to 0 after the given duration.
 *
 * @param bitno : the bit number; lowest bit has index 0
 * @param ms_duration : desired pulse duration in milliseconds. Be aware that the device time
 *         resolution is not guaranteed up to the millisecond.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_pulse : public YapiCommand /* arguments: bitno ms_duration */
{
public:
  apifun_DigitalIO_pulse(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "pulse";
  }

  string getDescription()
  {
    return "Triggers a pulse on a single bit for a specified duration.";
  }

  string getMoreInfo()
  {
    return "The specified bit will be turned to 1, and then back to 0 after the given duration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "desired pulse duration in milliseconds. Be aware that the device time resolution is not guaranteed up to the millisecond.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->pulse((int)(*args)[0]->get_intValue(),
                          (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Schedules a pulse on a single bit for a specified duration. The specified bit
 * will be turned to 1, and then back to 0 after the given duration.
 *
 * @param bitno : the bit number; lowest bit has index 0
 * @param ms_delay : waiting time before the pulse, in milliseconds
 * @param ms_duration : desired pulse duration in milliseconds. Be aware that the device time
 *         resolution is not guaranteed up to the millisecond.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DigitalIO_delayedPulse : public YapiCommand /* arguments: bitno ms_delay ms_duration */
{
public:
  apifun_DigitalIO_delayedPulse(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "delayedPulse";
  }

  string getDescription()
  {
    return "Schedules a pulse on a single bit for a specified duration.";
  }

  string getMoreInfo()
  {
    return "The specified bit will be turned to 1, and then back to 0 after the given duration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bitno", "the bit number; lowest bit has index 0", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_delay", "waiting time before the pulse, in milliseconds", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "desired pulse duration in milliseconds. Be aware that the device time resolution is not guaranteed up to the millisecond.", "_INT", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDigitalIO*>* list = enumerateTargets<YDigitalIO>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->delayedPulse((int)(*args)[0]->get_intValue(),
                                 (int)(*args)[1]->get_intValue(),
                                 (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YDigitalIO implementation)

//--- (YDigitalIO functions)
void YDigitalIOCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YDigitalIO>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_portState(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_set_portState(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_portDirection(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_set_portDirection(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_portOpenDrain(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_set_portOpenDrain(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_portPolarity(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_set_portPolarity(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_portDiags(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_portSize(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_get_outputVoltage(this)));
    cmdList->push_back((YapiCommand*) (new DigitalIO_set_outputVoltage(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_set_bitState(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_get_bitState(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_toggle_bitState(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_set_bitDirection(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_get_bitDirection(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_set_bitPolarity(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_get_bitPolarity(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_set_bitOpenDrain(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_get_bitOpenDrain(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_pulse(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DigitalIO_delayedPulse(this)));
  }

//--- (end of YDigitalIO functions)
