#pragma once

#include "../Singleton.h"
using namespace std;

class Logger : public Singleton<Logger> {
    friend class Singleton<Logger>;
    
public:
    static const string OPEN;
    static const string CLOSE;
    static const string CORRECT;
    static const string WRONG;
    static const string WIN;
    static const string LOSE;
    void logEvent(string scene, string action, string param);
    void logSession();
    string getTimestamp(string fieldToReturn);
    
protected:
    Logger();
    
private:
    void saveToFile(string stringToSave);
    
    string separator;
    
    string sessionName;
    string sessionDate;
    string sessionStart;
    
    time_t sessionStartTime;
    time_t sessionEndTime;
    
    string formatSeconds(double seconds);
};