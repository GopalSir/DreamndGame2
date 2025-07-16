#include "../../include/ECS_Core/Log.hpp"

 std::fstream Log::infoFileStream;
 std::fstream Log::errorFileStream;

 std::string Log::infoFileName;
std::string Log::errorFileName;

std::stringstream Log::infoStream;
std::stringstream Log::errorStream;

std::chrono::time_point<std::chrono::system_clock> Log::start_time;
std::string Log::str_start_time;

void Log::Initialize()
{
    infoStream<<"Initializing Log Class\n";
    infoStream.str("");

    infoFileName = "InfoFile.txt";
    errorFileName = "ErrorFile.txt";

    start_time = std::chrono::system_clock::now();
    time_t start_time_t = std::chrono::system_clock::to_time_t(start_time);

    std::tm* lt = std::localtime(&start_time_t);
    
    str_start_time = str_start_time + std::to_string(lt->tm_year + 1900) + "_";
    str_start_time = str_start_time + std::to_string(lt->tm_mon+1) + "_";
    str_start_time = str_start_time + std::to_string(lt->tm_mday) + "_";;
    str_start_time = str_start_time + std::to_string(lt->tm_hour) + "_";
    str_start_time = str_start_time + std::to_string(lt->tm_min) + "_";
    str_start_time = str_start_time + std::to_string(lt->tm_sec);


    //Open file with given name
    infoFileName = "Info_" + str_start_time + ".txt";
    errorFileName = "Error_" + str_start_time + ".txt";

    

    std::filesystem::create_directories("Logs/"+ str_start_time);

    infoFileStream.open("Logs/"+ str_start_time+"/"+ infoFileName,std::ios::out|std::ios::app);
    
    if(infoFileStream.is_open()==false)
    {
       throw std::runtime_error("Failed to open log file: "+ infoFileName); 
       int x;
       std::cin>>x; 
       exit(0);
    }

    errorFileStream.open("Logs/"+ str_start_time+"/"+ errorFileName,std::ios::out|std::ios::app);


    if(errorFileStream.is_open()==false)
    {
       throw std::runtime_error("Failed to open log file: "+ errorFileName); 
       int x;
       std::cin>>x; 
       exit(0);
    }
}

void Log::LogMessage(std::string _message,LogLevel _logLevel)
{
    if(_logLevel == LogLevel::INFO_LEVEL)
    {
        infoStream<<std::endl<<_message;
        
        /*Will flush to file if size exceeds*/
        if(true)
        {
            infoFileStream << infoStream.str()<<std::flush;
            infoStream.str("");
        }
    }
    else if(_logLevel == LogLevel::ERROR_LEVEL)
    {
        errorStream<<std::endl<<_message;
        if(true)
        {
            errorFileStream << errorStream.str()<<std::flush;
            errorStream.str("");
        }
    }
}

Log::~Log()
{

    infoFileStream << infoStream.str()<<std::flush;
    errorFileStream << errorStream.str()<<std::flush;

    LogMessage("Log Destructor Called",LogLevel::INFO_LEVEL);
    infoFileStream.close();
    errorFileStream.close();

}