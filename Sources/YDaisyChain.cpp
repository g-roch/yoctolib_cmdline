/*********************************************************************
 *
 *  $Id: YDaisyChain.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 *  Implements commands to handle DaisyChain functions
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
#include "YDaisyChain.h"
#include "yocto_api.h"
#include "yocto_daisychain.h"

using namespace std;

//--- (YDaisyChain definitions)

static const char *enumDaisyState[] = {
    "READY",
    "IS_CHILD",
    "FIRMWARE_MISMATCH",
    "CHILD_MISSING",
    "CHILD_LOST",
    NULL
};

//--- (end of YDaisyChain definitions)


//--- (YDaisyChain implementation)
bool   YDaisyChainCmdLine::isModule(void)      { return false; }
string YDaisyChainCmdLine::YFunctionName(void) { return "YDaisyChain"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of daisyState is int (DaisyState)
// type of childCount is int (UInt31)
// type of requiredChildCount is int (UInt31)
/**
 * Returns the logical name of the module chain.
 *
 * @return a string corresponding to the logical name of the module chain
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class DaisyChain_get_logicalName : public YapiCommand /* arguments: */
{
public:
  DaisyChain_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the module chain.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
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
 * Changes the logical name of the module chain. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the module chain
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DaisyChain_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  DaisyChain_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the module chain.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the module chain", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the module chain.
 *
 * @return a string corresponding to a short string representing the current state of the module chain
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class DaisyChain_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  DaisyChain_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the module chain.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
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
 * Returns the state of the daisy-link between modules.
 *
 * @return a value among Y_DAISYSTATE_READY, Y_DAISYSTATE_IS_CHILD, Y_DAISYSTATE_FIRMWARE_MISMATCH,
 * Y_DAISYSTATE_CHILD_MISSING and Y_DAISYSTATE_CHILD_LOST corresponding to the state of the daisy-link
 * between modules
 *
 * On failure, throws an exception or returns Y_DAISYSTATE_INVALID.
 */
class DaisyChain_get_daisyState : public YapiCommand /* arguments: */
{
public:
  DaisyChain_get_daisyState(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_daisyState";
  }

  string getDescription()
  {
    return "Returns the state of the daisy-link between modules.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_daisyState();
        string strval =  enumString(attrval,enumDaisyState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of child nodes currently detected.
 *
 * @return an integer corresponding to the number of child nodes currently detected
 *
 * On failure, throws an exception or returns Y_CHILDCOUNT_INVALID.
 */
class DaisyChain_get_childCount : public YapiCommand /* arguments: */
{
public:
  DaisyChain_get_childCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_childCount";
  }

  string getDescription()
  {
    return "Returns the number of child nodes currently detected.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_childCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of child nodes expected in normal conditions.
 *
 * @return an integer corresponding to the number of child nodes expected in normal conditions
 *
 * On failure, throws an exception or returns Y_REQUIREDCHILDCOUNT_INVALID.
 */
class DaisyChain_get_requiredChildCount : public YapiCommand /* arguments: */
{
public:
  DaisyChain_get_requiredChildCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_requiredChildCount";
  }

  string getDescription()
  {
    return "Returns the number of child nodes expected in normal conditions.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_requiredChildCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the number of child nodes expected in normal conditions.
 * If the value is zero, no check is performed. If it is non-zero, the number
 * child nodes is checked on startup and the status will change to error if
 * the count does not match.
 *
 * @param newval : an integer corresponding to the number of child nodes expected in normal conditions
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DaisyChain_set_requiredChildCount : public YapiCommand /* arguments: newval */
{
public:
  DaisyChain_set_requiredChildCount(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_requiredChildCount";
  }

  string getDescription()
  {
    return "Changes the number of child nodes expected in normal conditions.";
  }

  string getMoreInfo()
  {
    return "If the value is zero, no check is performed. If it is non-zero, the number child nodes is checked on startup and the status will change to error if the count does not match.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the number of child nodes expected in normal conditions", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_requiredChildCount(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackDaisyChain is YDaisyChainValueCallback* (YDaisyChainValueCallback)
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
class apifun_DaisyChain_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_DaisyChain_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
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
class apifun_DaisyChain_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_DaisyChain_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
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
class apifun_DaisyChain_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_DaisyChain_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YDaisyChain*>* list = enumerateTargets<YDaisyChain>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YDaisyChain implementation)

//--- (YDaisyChain functions)
void YDaisyChainCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YDaisyChain>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new DaisyChain_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new DaisyChain_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new DaisyChain_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new DaisyChain_get_daisyState(this)));
    cmdList->push_back((YapiCommand*) (new DaisyChain_get_childCount(this)));
    cmdList->push_back((YapiCommand*) (new DaisyChain_get_requiredChildCount(this)));
    cmdList->push_back((YapiCommand*) (new DaisyChain_set_requiredChildCount(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DaisyChain_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DaisyChain_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_DaisyChain_get_serialNumber(this)));
  }

//--- (end of YDaisyChain functions)
