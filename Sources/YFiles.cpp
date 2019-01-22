/*********************************************************************
 *
 * $Id: YFiles.cpp 33903 2018-12-28 08:49:26Z seb $
 *
 * Implements commands to handle Files functions
 *
 * - - - - - - - - - License information: - - - - - - - - -
 *
 * Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 * 1) If you have obtained this file from www.yoctopuce.com,
 *    Yoctopuce Sarl licenses to you (hereafter Licensee) the
 *    right to use, modify, copy, and integrate this source file
 *    into your own solution for the sole purpose of interfacing
 *    a Yoctopuce product with Licensee's solution.
 *
 *    The use of this file and all relationship between Yoctopuce
 *    and Licensee are governed by Yoctopuce General Terms and
 *    Conditions.
 *
 *    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 *    WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS
 *    FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *    EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 *    COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR
 *    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
 *    LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *    CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *    BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *    WARRANTY, OR OTHERWISE.
 *
 * 2) If your intent is not to interface with Yoctopuce products,
 *    you are not entitled to use, read or create any derived
 *    material from this source file.
 *
 *********************************************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "YFiles.h"
#include "yocto_api.h"
#include "yocto_files.h"

using namespace std;

//--- (generated code: YFiles definitions)

//--- (end of generated code: YFiles definitions)


//--- (generated code: YFiles implementation)
bool   YFilesCmdLine::isModule(void)      { return false; }
string YFilesCmdLine::YFunctionName(void) { return "YFiles"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of filesCount is int (UInt31)
// type of freeSpace is int (UInt31)
/**
 * Returns the logical name of the filesystem.
 *
 * @return a string corresponding to the logical name of the filesystem
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Files_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Files_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the filesystem.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
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
 * Changes the logical name of the filesystem. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the filesystem
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Files_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Files_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the filesystem.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the filesystem", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the filesystem.
 *
 * @return a string corresponding to a short string representing the current state of the filesystem
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Files_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  Files_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the filesystem.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
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
 * Returns the number of files currently loaded in the filesystem.
 *
 * @return an integer corresponding to the number of files currently loaded in the filesystem
 *
 * On failure, throws an exception or returns Y_FILESCOUNT_INVALID.
 */
class Files_get_filesCount : public YapiCommand /* arguments: */
{
public:
  Files_get_filesCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_filesCount";
  }

  string getDescription()
  {
    return "Returns the number of files currently loaded in the filesystem.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_filesCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the free space for uploading new files to the filesystem, in bytes.
 *
 * @return an integer corresponding to the free space for uploading new files to the filesystem, in bytes
 *
 * On failure, throws an exception or returns Y_FREESPACE_INVALID.
 */
class Files_get_freeSpace : public YapiCommand /* arguments: */
{
public:
  Files_get_freeSpace(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_freeSpace";
  }

  string getDescription()
  {
    return "Returns the free space for uploading new files to the filesystem, in bytes.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_freeSpace();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackFiles is YFilesValueCallback* (YFilesValueCallback)
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
class apifun_Files_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Files_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
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
class apifun_Files_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Files_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
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
class apifun_Files_get_serialNumber : public YapiCommand /* arguments: */
{
public:
  apifun_Files_get_serialNumber(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_serialNumber();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reinitialize the filesystem to its clean, unfragmented, empty state.
 * All files previously uploaded are permanently lost.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Files_format_fs : public YapiCommand /* arguments: */
{
public:
  apifun_Files_format_fs(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "format_fs";
  }

  string getDescription()
  {
    return "Reinitialize the filesystem to its clean, unfragmented, empty state.";
  }

  string getMoreInfo()
  {
    return "All files previously uploaded are permanently lost.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->format_fs();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of YFileRecord objects that describe files currently loaded
 * in the filesystem.
 *
 * @param pattern : an optional filter pattern, using star and question marks
 *         as wild cards. When an empty pattern is provided, all file records
 *         are returned.
 *
 * @return a list of YFileRecord objects, containing the file path
 *         and name, byte size and 32-bit CRC of the file content.
 *
 * On failure, throws an exception or returns an empty list.
 */
class apifun_Files_get_list : public YapiCommand /* arguments: pattern */
{
public:
  apifun_Files_get_list(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_list";
  }

  string getDescription()
  {
    return "Returns a list of YFileRecord objects that describe files currently loadedin the filesystem.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pattern", "an optional filter pattern, using star and question marks as wild cards. When an empty pattern is provided, all file records are returned.", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<YFileRecord> value = (*list)[i]->get_list((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Test if a file exist on the filesystem of the module.
 *
 * @param filename : the file name to test.
 *
 * @return a true if the file exist, false otherwise.
 *
 * On failure, throws an exception.
 */
class apifun_Files_fileExist : public YapiCommand /* arguments: filename */
{
public:
  apifun_Files_fileExist(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "fileExist";
  }

  string getDescription()
  {
    return "Test if a file exist on the filesystem of the module.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "filename", "the file name to test.", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        bool value = (*list)[i]->fileExist((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Downloads the requested file and returns a binary buffer with its content.
 *
 * @param pathname : path and name of the file to download
 *
 * @return a binary buffer with the file content
 *
 * On failure, throws an exception or returns an empty content.
 */
class apifun_Files_download : public YapiCommand /* arguments: pathname */
{
public:
  apifun_Files_download(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "download";
  }

  string getDescription()
  {
    return "Downloads the requested file and returns a binary buffer with its content.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pathname", "path and name of the file to download", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->download((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Uploads a file to the filesystem, to the specified full path name.
 * If a file already exists with the same path name, its content is overwritten.
 *
 * @param pathname : path and name of the new file to create
 * @param content : binary buffer with the content to set
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Files_upload : public YapiCommand /* arguments: pathname content */
{
public:
  apifun_Files_upload(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "upload";
  }

  string getDescription()
  {
    return "Uploads a file to the filesystem, to the specified full path name.";
  }

  string getMoreInfo()
  {
    return "If a file already exists with the same path name, its content is overwritten.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pathname", "path and name of the new file to create", "_STRING", false));
    res->push_back(new ArgumentDesc(BIN_ARG, "content", "binary buffer with the content to set", "_BIN", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->upload((*args)[0]->get_stringValue(),
                           (*args)[1]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Deletes a file, given by its full path name, from the filesystem.
 * Because of filesystem fragmentation, deleting a file may not always
 * free up the whole space used by the file. However, rewriting a file
 * with the same path name will always reuse any space not freed previously.
 * If you need to ensure that no space is taken by previously deleted files,
 * you can use format_fs to fully reinitialize the filesystem.
 *
 * @param pathname : path and name of the file to remove.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Files_remove : public YapiCommand /* arguments: pathname */
{
public:
  apifun_Files_remove(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "remove";
  }

  string getDescription()
  {
    return "Deletes a file, given by its full path name, from the filesystem.";
  }

  string getMoreInfo()
  {
    return "Because of filesystem fragmentation, deleting a file may not always free up the whole space used by the file. However, rewriting a file with the same path name will always reuse any space not freed previously. If you need to ensure that no space is taken by previously deleted files, you can use format_fs to fully reinitialize the filesystem.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pathname", "path and name of the file to remove.", "_STRING", false));
    return res;
  }

  virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YFiles*>* list = enumerateTargets<YFiles>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->remove((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YFiles implementation)

//--- (generated code: YFiles functions)
void YFilesCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YFiles>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Files_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Files_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Files_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new Files_get_filesCount(this)));
    cmdList->push_back((YapiCommand*) (new Files_get_freeSpace(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_unmuteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_get_serialNumber(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_format_fs(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_get_list(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_fileExist(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_download(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_upload(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Files_remove(this)));
  }

//--- (end of generated code: YFiles functions)
