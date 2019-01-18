/*********************************************************************
 *
 *  $Id: YGps.cpp 32610 2018-10-10 06:52:20Z seb $
 *
 *  Implements commands to handle Gps functions
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
#include "YGps.h"
#include "yocto_api.h"
#include "yocto_gps.h"

using namespace std;

//--- (YGps definitions)

static const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

static const char *enumGPSCoordinateSystem[] = {
    "GPS_DMS",
    "GPS_DM",
    "GPS_D",
    NULL
};

//--- (end of YGps definitions)


//--- (YGps implementation)
bool   YGpsCmdLine::isModule(void)      { return false; }
string YGpsCmdLine::YFunctionName(void) { return "YGps"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of isFixed is int (Bool)
// type of satCount is s64 (UInt)
// type of coordSystem is int (GPSCoordinateSystem)
// type of latitude is string (Text)
// type of longitude is string (Text)
// type of dilution is double (MeasureVal)
// type of altitude is double (MeasureVal)
// type of groundSpeed is double (MeasureVal)
// type of direction is double (MeasureVal)
// type of unixTime is s64 (UTCTime)
// type of dateTime is string (Text)
// type of utcOffset is int (Int)
// type of command is string (Text)
/**
 * Returns the logical name of the GPS.
 *
 * @return a string corresponding to the logical name of the GPS
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Gps_get_logicalName : public YapiCommand /* arguments: */
{
public:
  Gps_get_logicalName(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the GPS.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
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
 * Changes the logical name of the GPS. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the GPS
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gps_set_logicalName : public YapiCommand /* arguments: newval */
{
public:
  Gps_set_logicalName(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the GPS.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the GPS", "_LOGICAL", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
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
 * Returns a short string representing the current state of the GPS.
 *
 * @return a string corresponding to a short string representing the current state of the GPS
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Gps_get_advertisedValue : public YapiCommand /* arguments: */
{
public:
  Gps_get_advertisedValue(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the GPS.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
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
 * Returns TRUE if the receiver has found enough satellites to work.
 *
 * @return either Y_ISFIXED_FALSE or Y_ISFIXED_TRUE, according to TRUE if the receiver has found
 * enough satellites to work
 *
 * On failure, throws an exception or returns Y_ISFIXED_INVALID.
 */
class Gps_get_isFixed : public YapiCommand /* arguments: */
{
public:
  Gps_get_isFixed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_isFixed";
  }

  string getDescription()
  {
    return "Returns TRUE if the receiver has found enough satellites to work.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_isFixed();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the count of visible satellites.
 *
 * @return an integer corresponding to the count of visible satellites
 *
 * On failure, throws an exception or returns Y_SATCOUNT_INVALID.
 */
class Gps_get_satCount : public YapiCommand /* arguments: */
{
public:
  Gps_get_satCount(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_satCount";
  }

  string getDescription()
  {
    return "Returns the count of visible satellites.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_satCount();
        char buf[32]; snprintf(buf, 32, "%u", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the representation system used for positioning data.
 *
 * @return a value among Y_COORDSYSTEM_GPS_DMS, Y_COORDSYSTEM_GPS_DM and Y_COORDSYSTEM_GPS_D
 * corresponding to the representation system used for positioning data
 *
 * On failure, throws an exception or returns Y_COORDSYSTEM_INVALID.
 */
class Gps_get_coordSystem : public YapiCommand /* arguments: */
{
public:
  Gps_get_coordSystem(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_coordSystem";
  }

  string getDescription()
  {
    return "Returns the representation system used for positioning data.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_coordSystem();
        string strval =  enumString(attrval,enumGPSCoordinateSystem);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the representation system used for positioning data.
 *
 * @param newval : a value among Y_COORDSYSTEM_GPS_DMS, Y_COORDSYSTEM_GPS_DM and Y_COORDSYSTEM_GPS_D
 * corresponding to the representation system used for positioning data
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gps_set_coordSystem : public YapiCommand /* arguments: newval */
{
public:
  Gps_set_coordSystem(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_coordSystem";
  }

  string getDescription()
  {
    return "Changes the representation system used for positioning data.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among GPS_DMS, GPS_DM and GPS_D corresponding to the representation system used for positioning data", "GPS_DMS=0,GPS_DM=1,GPS_D=2", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_coordSystem(Y_COORDSYSTEM_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

/**
 * Returns the current latitude.
 *
 * @return a string corresponding to the current latitude
 *
 * On failure, throws an exception or returns Y_LATITUDE_INVALID.
 */
class Gps_get_latitude : public YapiCommand /* arguments: */
{
public:
  Gps_get_latitude(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_latitude";
  }

  string getDescription()
  {
    return "Returns the current latitude.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_latitude();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current longitude.
 *
 * @return a string corresponding to the current longitude
 *
 * On failure, throws an exception or returns Y_LONGITUDE_INVALID.
 */
class Gps_get_longitude : public YapiCommand /* arguments: */
{
public:
  Gps_get_longitude(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_longitude";
  }

  string getDescription()
  {
    return "Returns the current longitude.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_longitude();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current horizontal dilution of precision,
 * the smaller that number is, the better .
 *
 * @return a floating point number corresponding to the current horizontal dilution of precision,
 *         the smaller that number is, the better
 *
 * On failure, throws an exception or returns Y_DILUTION_INVALID.
 */
class Gps_get_dilution : public YapiCommand /* arguments: */
{
public:
  Gps_get_dilution(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_dilution";
  }

  string getDescription()
  {
    return "Returns the current horizontal dilution of precision,the smaller that number is, the better .";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_dilution();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current altitude. Beware:  GPS technology
 * is very inaccurate regarding altitude.
 *
 * @return a floating point number corresponding to the current altitude
 *
 * On failure, throws an exception or returns Y_ALTITUDE_INVALID.
 */
class Gps_get_altitude : public YapiCommand /* arguments: */
{
public:
  Gps_get_altitude(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_altitude";
  }

  string getDescription()
  {
    return "Returns the current altitude.";
  }

  string getMoreInfo()
  {
    return "Beware: GPS technology is very inaccurate regarding altitude.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_altitude();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current ground speed in Km/h.
 *
 * @return a floating point number corresponding to the current ground speed in Km/h
 *
 * On failure, throws an exception or returns Y_GROUNDSPEED_INVALID.
 */
class Gps_get_groundSpeed : public YapiCommand /* arguments: */
{
public:
  Gps_get_groundSpeed(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_groundSpeed";
  }

  string getDescription()
  {
    return "Returns the current ground speed in Km/h.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_groundSpeed();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current move bearing in degrees, zero
 * is the true (geographic) north.
 *
 * @return a floating point number corresponding to the current move bearing in degrees, zero
 *         is the true (geographic) north
 *
 * On failure, throws an exception or returns Y_DIRECTION_INVALID.
 */
class Gps_get_direction : public YapiCommand /* arguments: */
{
public:
  Gps_get_direction(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_direction";
  }

  string getDescription()
  {
    return "Returns the current move bearing in degrees, zerois the true (geographic) north.";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_direction();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current time in Unix format (number of
 * seconds elapsed since Jan 1st, 1970).
 *
 * @return an integer corresponding to the current time in Unix format (number of
 *         seconds elapsed since Jan 1st, 1970)
 *
 * On failure, throws an exception or returns Y_UNIXTIME_INVALID.
 */
class Gps_get_unixTime : public YapiCommand /* arguments: */
{
public:
  Gps_get_unixTime(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_unixTime";
  }

  string getDescription()
  {
    return "Returns the current time in Unix format (number ofseconds elapsed since Jan 1st, 1970).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_unixTime();
        char buf[64]; snprintf(buf, 64, "%u [s] since Jan 1, 1970", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current time in the form "YYYY/MM/DD hh:mm:ss".
 *
 * @return a string corresponding to the current time in the form "YYYY/MM/DD hh:mm:ss"
 *
 * On failure, throws an exception or returns Y_DATETIME_INVALID.
 */
class Gps_get_dateTime : public YapiCommand /* arguments: */
{
public:
  Gps_get_dateTime(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_dateTime";
  }

  string getDescription()
  {
    return "Returns the current time in the form \"YYYY/MM/DD hh:mm:ss\".";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_dateTime();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of seconds between current time and UTC time (time zone).
 *
 * @return an integer corresponding to the number of seconds between current time and UTC time (time zone)
 *
 * On failure, throws an exception or returns Y_UTCOFFSET_INVALID.
 */
class Gps_get_utcOffset : public YapiCommand /* arguments: */
{
public:
  Gps_get_utcOffset(YFunctionCmdLine *function):YapiCommand(function){}

  string getName()
  {
    return "get_utcOffset";
  }

  string getDescription()
  {
    return "Returns the number of seconds between current time and UTC time (time zone).";
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_utcOffset();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the number of seconds between current time and UTC time (time zone).
 * The timezone is automatically rounded to the nearest multiple of 15 minutes.
 * If current UTC time is known, the current time is automatically be updated according to the selected time zone.
 *
 * @param newval : an integer corresponding to the number of seconds between current time and UTC time (time zone)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Gps_set_utcOffset : public YapiCommand /* arguments: newval */
{
public:
  Gps_set_utcOffset(YFunctionCmdLine *function):YapiCommand(function){}
  string getName()
  {
    return "set_utcOffset";
  }

  string getDescription()
  {
    return "Changes the number of seconds between current time and UTC time (time zone).";
  }

  string getMoreInfo()
  {
    return "The timezone is automatically rounded to the nearest multiple of 15 minutes. If current UTC time is known, the current time is automatically be updated according to the selected time zone.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the number of seconds between current time and UTC time (time zone)", "_INT", false));
    return res;
  }

  void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
  {
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++) {
        (*list)[i]->set_utcOffset(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
    }
  }
};

// type of valueCallbackGps is YGpsValueCallback* (YGpsValueCallback)
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
class apifun_Gps_muteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Gps_muteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
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
class apifun_Gps_unmuteValueCallbacks : public YapiCommand /* arguments: */
{
public:
  apifun_Gps_unmuteValueCallbacks(YFunctionCmdLine *function):YapiCommand(function){}

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
    vector<YGps*>* list = enumerateTargets<YGps>(_function, target, modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->unmuteValueCallbacks();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YGps implementation)

//--- (YGps functions)
void YGpsCmdLine::RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YGps>(this, cmdList);
    cmdList->push_back((YapiCommand*) (new Gps_get_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Gps_set_logicalName(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_advertisedValue(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_isFixed(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_satCount(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_coordSystem(this)));
    cmdList->push_back((YapiCommand*) (new Gps_set_coordSystem(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_latitude(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_longitude(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_dilution(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_altitude(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_groundSpeed(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_direction(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_unixTime(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_dateTime(this)));
    cmdList->push_back((YapiCommand*) (new Gps_get_utcOffset(this)));
    cmdList->push_back((YapiCommand*) (new Gps_set_utcOffset(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gps_muteValueCallbacks(this)));
    cmdList->push_back((YapiCommand*) (new apifun_Gps_unmuteValueCallbacks(this)));
  }

//--- (end of YGps functions)
