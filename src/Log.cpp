//
// Created by User on 2020-01-17.
//

#include <stdexcept>
#include "Log.h"
#include "iostream"

Log::LogLevel Log::log_level = Log::DEBUG;

void Log::logLevel(Log::LogLevel level) {
    Log::log_level = level;
}

void Log::debug(const std::string &s) {
    if (Log::log_level >= DEBUG) {
        std::clog<< "[DEBUG]" << s << std::endl;
    }
}

void Log::message(const std::string &s) {
    if (Log::log_level >= MESSAGE) {
        std::clog << "[MESSAGE]" << s << std::endl;
    }
}

void Log::status(const std::string &s) {
    if (Log::log_level >= STATUS) {
        std::clog << "[STATUS]" << s << std::endl;
    }
}
void Log::_error(const std::string &s, unsigned int line, std::string file, std::string function) {
    if (Log::log_level >= ERROR) {
        throw std::runtime_error("[ERROR]file :"+file+" at "+std::to_string(line)+":\n"+s) ;
    }
}

void Log::warning(const std::string &s) {
    if (Log::log_level >= WARNING) {
        std::clog << "[WARNING]" << s << std::endl;
    }
}






