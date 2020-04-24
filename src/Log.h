#pragma once

#include "string"
#define error(s,...) _error(s, __LINE__,__FILE__,__func__)
class Log {
public:
    enum LogLevel{
        DEBUG = 5,
        MESSAGE= 4,
        STATUS = 3,
        WARNING = 2,
        ERROR = 1,
        NOTHING = 0,
    };
private:
    static LogLevel log_level;
public:
    static void logLevel(LogLevel level);

    static void debug(const std::string &s);

    static void message(const std::string &s);

    static void status(const std::string &s);

    static void warning(const std::string &s);

    static void _error(const std::string &s,unsigned int line,std::string file,std::string function);


};
