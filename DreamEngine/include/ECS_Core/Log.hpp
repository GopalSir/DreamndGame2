#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <chrono>
#include <filesystem>
#include <iomanip>

enum LogLevel{
    INFO_LEVEL,
    ERROR_LEVEL
};

class Log
{
    static std::fstream infoFileStream,errorFileStream;
    static std::string infoFileName,errorFileName;
    static std::stringstream infoStream,errorStream;
    static std::chrono::time_point<std::chrono::system_clock> start_time;
    static std::string str_start_time;
    
    
    public:
    static void Initialize();
    static void LogMessage(std::string _message, LogLevel _logLevel=LogLevel::INFO_LEVEL);
    static void setInfoFilename();
    static void setErrorFilename();
    ~Log();
};