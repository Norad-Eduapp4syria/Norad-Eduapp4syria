#include "Logger.h"
#include "../StringUtility.h"
#include "../CocosCamera/CocosCamera.h"


using namespace std;

const string Logger::OPEN = "Open";
const string Logger::CLOSE = "Close";
const string Logger::CORRECT = "Correct";
const string Logger::WRONG = "Error";
const string Logger::WIN = "Win";
const string Logger::LOSE = "Lose";

Logger::Logger() {
    
    CCLOG("Logger()");
  
    
}

void Logger::logEvent(string scene, string action, string param ) {

    // RIGA DI LOG:
    // nomeDevice? - timestamp - scena/gioco - Azione (apertura/chiusura) - parametro
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    
    separator = "  \t";
    string timestamp = getTimestamp("all");
    string deviceName = userDef->getStringForKey("DEVICE_NAME", "DeviceName");
    string session = "Session_" + StringUtility::toString( userDef->getIntegerForKey("Session") );
    string toSave = deviceName + separator + session + separator + timestamp + separator + scene + separator + action + separator + param + string("\n");
    
    
    if ( (scene == "APP") && (action == "Foreground") ) {
        // new session starts..
        time(&sessionStartTime); // save sessionStartTime
        sessionName = session;
        sessionDate = getTimestamp("date");
        sessionStart = getTimestamp("time");
    }
    
    CCLOG("LOG> %s", toSave.c_str());
    saveToFile(toSave);
    
    
}

void Logger::saveToFile(string stringToSave) {
    
#if ( CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS )
    return;
#endif
    
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
        FILE* fp = fopen("/sdcard/Kukua/Logs/KukuaLOG.csv","a+"); // http://www.decompile.com/cpp/faq/fopen_write_append.htm
    
    
        fwrite(stringToSave.c_str(), 1, sizeof(char) * (stringToSave.length() + 1), fp);
    
        // fwrite(stringToSave.c_str(), 1, sizeof(char) * (stringToSave.length() + 1), fp); // TODO controllare come mai questa riga era doppia
    
        fclose(fp);
    
    #elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
        string filePath = cocos2d::FileUtils::getInstance()->getWritablePath();
        /*
         string filePath = "";
        filePath.append( getenv("HOME") );
        filePath.append("/Documents/");
         */
    
        filePath.append("KukuaLOG.csv");
    
    
        FILE *fp = fopen(filePath.c_str(), "a+");
    
        fwrite(stringToSave.c_str(), 1, sizeof(char) * (stringToSave.length() + 1), fp);
    
        fclose(fp);
    
    #else
        CCLOG("LOG> NO LOG!!!");
    #endif
    
    
}



string Logger::getTimestamp(string fieldToReturn) {
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    
    //CCLOG("year------->%04d",timeinfo->);
    
    
    
    /*
    CCLOG("year------->%04d",timeinfo->tm_year+1900);
    CCLOG("month------->%02d",timeinfo->tm_mon+1);
    CCLOG("day------->%02d",timeinfo->tm_mday);
    
    CCLOG("hour------->%02d",timeinfo->tm_hour);
    CCLOG("minutes------->%02d",timeinfo->tm_min);
    CCLOG("seconds------->%02d",timeinfo->tm_sec);
    */
    string separator1 = "/";
    string separator2 = ":";
    
    string toRet;
    
    if (fieldToReturn == "all") {
        toRet = StringUtility::toString(timeinfo->tm_year+1900) + separator1 + StringUtility::toString(timeinfo->tm_mon+1) + separator1 + StringUtility::toString(timeinfo->tm_mday) + separator + StringUtility::toString(timeinfo->tm_hour) + separator2 + StringUtility::toString(timeinfo->tm_min) + separator2 + StringUtility::toString(timeinfo->tm_sec);
    }
    else if (fieldToReturn == "date") {
        toRet = StringUtility::toString(timeinfo->tm_year+1900) + separator1 + StringUtility::toString(timeinfo->tm_mon+1) + separator1 + StringUtility::toString(timeinfo->tm_mday);
    }
    else if (fieldToReturn == "time") {
        toRet = StringUtility::toString(timeinfo->tm_hour) + separator2 + StringUtility::toString(timeinfo->tm_min) + separator2 + StringUtility::toString(timeinfo->tm_sec);
    }
    
    return toRet;
    
}


void Logger::logSession() {

#if ( CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS )
    return;
#endif
    
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    string deviceName = userDef->getStringForKey("DEVICE_NAME", "DeviceName");
    
    string stringToSave = deviceName;
    stringToSave += "\n";

    stringToSave += sessionName;
    stringToSave += "\n";
    
    stringToSave += "Session Date:";
    stringToSave += separator;
    stringToSave += sessionDate;
    stringToSave += "\n";
    
    stringToSave += "Session Start:";
    stringToSave += separator;
    stringToSave += sessionStart;
    stringToSave += "\n";
    
    stringToSave += "Session End:";
    stringToSave += separator;
    stringToSave += getTimestamp("time");
    stringToSave += "\n";
    
    time(&sessionEndTime); // save sessionEndTime
    double seconds = difftime(sessionEndTime, sessionStartTime);
    
    stringToSave += "Session Duration:";
    stringToSave += separator;
    stringToSave += formatSeconds(seconds);
    stringToSave += "\n";
    
    stringToSave += "\n";
    
    CCLOG("LOG_session> %s", stringToSave.c_str());
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        
    FILE* fp = fopen("/sdcard/Kukua/Logs/KukuaLOG_Session.csv","a+");
    
    fwrite(stringToSave.c_str(), 1, sizeof(char) * (stringToSave.length() + 1), fp);
    
    
    fclose(fp);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    string filePath = cocos2d::FileUtils::getInstance()->getWritablePath();
    
    filePath.append("KukuaLOG_Session.csv");
    
    
    FILE *fp = fopen(filePath.c_str(), "a+");
    
    fwrite(stringToSave.c_str(), 1, sizeof(char) * (stringToSave.length() + 1), fp);
    
    fclose(fp);
    
#else
    CCLOG("LOG_session> NO LOG!!!");
#endif
    
    
}

string Logger::formatSeconds(double seconds) {
    int secondsInt = (int)round(seconds);
    int minutes = secondsInt / 60;
    int hours = minutes / 60;
    string toRet;
    toRet = StringUtility::toString(int(hours)) + ":" + StringUtility::toString(int(minutes%60)) + ":" + StringUtility::toString(int(secondsInt%60));
    return toRet;
}



