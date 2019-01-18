/*********************************************************************
 *
 * $Id: YMessageBox.cpp 28749 2017-10-03 08:31:33Z seb $
 *
 * Implements commands to handle MessageBox functions
 *
 * - - - - - - - - - License information: - - - - - - - - -
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
#include "YMessageBox.h"
#include "yocto_api.h"
#include "yocto_messagebox.h"

using namespace std;

//--- (generated code: YMessageBox definitions)

//--- (end of generated code: YMessageBox definitions)


//--- (generated code: YMessageBox implementation)
bool   YMessageBoxCmdLine::isModule(void)      { return false; }
string YMessageBoxCmdLine::YFunctionName(void) { return "YMessageBox"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of slotsInUse is int (UInt31)
// type of slotsCount is int (UInt31)
// type of slotsBitmap is string (BinaryBuffer)
// type of pduSent is int (UInt31)
// type of pduReceived is int (UInt31)
// type of command is string (Text)
/**
 * Returns the logical name of the MessageBox interface.
 *
 * @return a string corresponding to the logical name of the MessageBox interface
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class MessageBox_get_logicalName : public YapiCommand /* arguments: */
{
public:
  MessageBox_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the MessageBox interface.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
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
 * Changes the logical name of the MessageBox interface. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the MessageBox interface
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MessageBox_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  MessageBox_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the MessageBox interface.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the MessageBox interface", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the MessageBox interface.
 *
 * @return a string corresponding to a short string representing the current state of the MessageBox interface
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class MessageBox_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  MessageBox_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the MessageBox interface.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
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
 * Returns the number of message storage slots currently in use.
 *
 * @return an integer corresponding to the number of message storage slots currently in use
 *
 * On failure, throws an exception or returns Y_SLOTSINUSE_INVALID.
 */
class MessageBox_get_slotsInUse : public YapiCommand /* arguments: */
{
public:
  MessageBox_get_slotsInUse(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_slotsInUse";
  }

  string getDescription()
  {
    return "Returns the number of message storage slots currently in use.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_slotsInUse();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of message storage slots on the SIM card.
 *
 * @return an integer corresponding to the total number of message storage slots on the SIM card
 *
 * On failure, throws an exception or returns Y_SLOTSCOUNT_INVALID.
 */
class MessageBox_get_slotsCount : public YapiCommand /* arguments: */
{
public:
  MessageBox_get_slotsCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_slotsCount";
  }

  string getDescription()
  {
    return "Returns the total number of message storage slots on the SIM card.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_slotsCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of SMS units sent so far.
 *
 * @return an integer corresponding to the number of SMS units sent so far
 *
 * On failure, throws an exception or returns Y_PDUSENT_INVALID.
 */
class MessageBox_get_pduSent : public YapiCommand /* arguments: */
{
public:
  MessageBox_get_pduSent(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_pduSent";
  }

  string getDescription()
  {
    return "Returns the number of SMS units sent so far.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_pduSent();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the value of the outgoing SMS units counter.
 *
 * @param newval : an integer corresponding to the value of the outgoing SMS units counter
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MessageBox_set_pduSent : public YapiCommand /* arguments: newval */
{
public:
  MessageBox_set_pduSent(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_pduSent";
  }

  string getDescription()
  {
    return "Changes the value of the outgoing SMS units counter.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the value of the outgoing SMS units counter", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_pduSent(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the number of SMS units received so far.
 *
 * @return an integer corresponding to the number of SMS units received so far
 *
 * On failure, throws an exception or returns Y_PDURECEIVED_INVALID.
 */
class MessageBox_get_pduReceived : public YapiCommand /* arguments: */
{
public:
  MessageBox_get_pduReceived(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_pduReceived";
  }

  string getDescription()
  {
    return "Returns the number of SMS units received so far.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_pduReceived();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the value of the incoming SMS units counter.
 *
 * @param newval : an integer corresponding to the value of the incoming SMS units counter
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class MessageBox_set_pduReceived : public YapiCommand /* arguments: newval */
{
public:
  MessageBox_set_pduReceived(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_pduReceived";
  }

  string getDescription()
  {
    return "Changes the value of the incoming SMS units counter.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the value of the incoming SMS units counter", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_pduReceived(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackMessageBox is YMessageBoxValueCallback* (YMessageBoxValueCallback)
// type of nextMsgRef is int (int)
// type of prevBitmapStr is string (str)
// type of pdus is vector<YSms> (YSmsArr)
// type of messages is vector<YSms> (YSmsArr)
// type of gsm2unicodeReady is bool (bool)
// type of gsm2unicode is vector<int> (intArr)
// type of iso2gsm is bin (bin)
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
class apifun_MessageBox_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_MessageBox_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
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
class apifun_MessageBox_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_MessageBox_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
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
 * Clear the SMS units counters.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_MessageBox_clearPduCounters : public YapiCommand /* arguments: */
{
public:
  apifun_MessageBox_clearPduCounters(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "clearPduCounters";
  }

  string getDescription()
  {
    return "Clear the SMS units counters.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->clearPduCounters();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a regular text SMS, with standard parameters. This function can send messages
 * of more than 160 characters, using SMS concatenation. ISO-latin accented characters
 * are supported. For sending messages with special unicode characters such as asian
 * characters and emoticons, use newMessage to create a new message and define
 * the content of using methods addText and addUnicodeData.
 *
 * @param recipient : a text string with the recipient phone number, either as a
 *         national number, or in international format starting with a plus sign
 * @param message : the text to be sent in the message
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_MessageBox_sendTextMessage : public YapiCommand /* arguments: recipient message */
{
public:
  apifun_MessageBox_sendTextMessage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "sendTextMessage";
  }

  string getDescription()
  {
    return "Sends a regular text SMS, with standard parameters.";
  }

  string getMoreInfo()
  {
    return "This function can send messages of more than 160 characters, using SMS concatenation. ISO-latin accented characters are supported. For sending messages with special unicode characters such as asian characters and emoticons, use newMessage to create a new message and define the content of using methods addText and addUnicodeData.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "recipient", "a text string with the recipient phone number, either as a national number, or in international format starting with a plus sign", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "message", "the text to be sent in the message", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->sendTextMessage((*args)[0]->get_stringValue(),
                                    (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a Flash SMS (class 0 message). Flash messages are displayed on the handset
 * immediately and are usually not saved on the SIM card. This function can send messages
 * of more than 160 characters, using SMS concatenation. ISO-latin accented characters
 * are supported. For sending messages with special unicode characters such as asian
 * characters and emoticons, use newMessage to create a new message and define
 * the content of using methods addText et addUnicodeData.
 *
 * @param recipient : a text string with the recipient phone number, either as a
 *         national number, or in international format starting with a plus sign
 * @param message : the text to be sent in the message
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_MessageBox_sendFlashMessage : public YapiCommand /* arguments: recipient message */
{
public:
  apifun_MessageBox_sendFlashMessage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "sendFlashMessage";
  }

  string getDescription()
  {
    return "Sends a Flash SMS (class 0 message).";
  }

  string getMoreInfo()
  {
    return "Flash messages are displayed on the handset immediately and are usually not saved on the SIM card. This function can send messages of more than 160 characters, using SMS concatenation. ISO-latin accented characters are supported. For sending messages with special unicode characters such as asian characters and emoticons, use newMessage to create a new message and define the content of using methods addText et addUnicodeData.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "recipient", "a text string with the recipient phone number, either as a national number, or in international format starting with a plus sign", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "message", "the text to be sent in the message", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->sendFlashMessage((*args)[0]->get_stringValue(),
                                     (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Creates a new empty SMS message, to be configured and sent later on.
 *
 * @param recipient : a text string with the recipient phone number, either as a
 *         national number, or in international format starting with a plus sign
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_MessageBox_newMessage : public YapiCommand /* arguments: recipient */
{
public:
  apifun_MessageBox_newMessage(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "newMessage";
  }

  string getDescription()
  {
    return "Creates a new empty SMS message, to be configured and sent later on.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "recipient", "a text string with the recipient phone number, either as a national number, or in international format starting with a plus sign", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YSms value = (*list)[i]->newMessage((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the list of messages received and not deleted. This function
 * will automatically decode concatenated SMS.
 *
 * @return an YSms object list.
 *
 * On failure, throws an exception or returns an empty list.
 */
class apifun_MessageBox_get_messages : public YapiCommand /* arguments: */
{
public:
  apifun_MessageBox_get_messages(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_messages";
  }

  string getDescription()
  {
    return "Returns the list of messages received and not deleted.";
  }

  string getMoreInfo()
  {
    return "This function will automatically decode concatenated SMS.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YMessageBox*>* list = enumerateTargets<YMessageBox>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<YSms> value = (*list)[i]->get_messages();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YMessageBox implementation)

//--- (generated code: YMessageBox functions)
void YMessageBoxCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YMessageBox>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new MessageBox_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_get_slotsInUse(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_get_slotsCount(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_get_pduSent(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_set_pduSent(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_get_pduReceived(this)));
    cmdList->push_back((YapiCommand*) (new MessageBox_set_pduReceived(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MessageBox_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MessageBox_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MessageBox_clearPduCounters(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MessageBox_sendTextMessage(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MessageBox_sendFlashMessage(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MessageBox_newMessage(this)));
    cmdList->push_back((YapiCommand*) (new apifun_MessageBox_get_messages(this)));
  }

//--- (end of generated code: YMessageBox functions)
