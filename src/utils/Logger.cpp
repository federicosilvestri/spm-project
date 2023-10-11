//
// Created by federicosilvestri on 11/10/23.
//

/*
// Copyright (c) 2019 Onur Dundar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#include "Logger.hpp"

std::shared_ptr<Logger> Logger::loggerInstance;


/**
* Configure Logger Preferences
* @param logFile
* @param level: LogLevel::ERROR by Default
* @param output: LogOutput::CONSOLE by Default
* @return void
*/
void Logger::SetLogPreferences(LogLevel level = LogLevel::ERROR) {
    logLevel = level;

}

/**
* Get Single Logger Instance or Create new Object if Not Created
* @return std::shared_ptr<Logger>
*/
std::shared_ptr<Logger> Logger::GetInstance() {
    if (loggerInstance == nullptr) {
        loggerInstance = std::shared_ptr<Logger>(new Logger());
    }

    return loggerInstance;
}

/**
* Log given message with defined parameters and generate message to pass on Console or File
* @param message: Log Message
* @param messageLevel: Log Level, LogLevel::DEBUG by default
*/
void Logger::Log(std::string message, LogLevel messageLevel = LogLevel::DEBUG) {
    if (messageLevel <= logLevel) {
        std::string logType;
        //Set Log Level Name
        switch (messageLevel) {
            case LogLevel::DEBUG:
                logType = "DEBUG: ";
                break;
            case LogLevel::INFO:
                logType = "INFO: ";
                break;
            case LogLevel::WARN:
                logType = "WARN: ";
                break;
            case LogLevel::ERROR:
                logType = "ERROR: ";
                break;
            default:
                logType = "NONE: ";
                break;
        }
        message = logType + message;

        LogMessage(message);
    }
}

/**
* Convert String Representation of Log Level to LogLevel Type
* @param logLevel : String log level
* @return LogLevel
*/
LogLevel Logger::GetLogLevel(const std::string &logLevel) {
    if (logLevel == "DEBUG") {
        return LogLevel::DEBUG;
    } else if (logLevel == "INFO") {
        return LogLevel::INFO;
    } else if (logLevel == "WARN") {
        return LogLevel::ERROR;
    } else if (logLevel == "ERROR") {
        return LogLevel::ERROR;
    }
    return LogLevel::NONE;
}

/**
 * Write out the message to target output
 * @param message : String message
 * @return void
 */
void Logger::LogMessage(const std::string &message) {
    std::cout << message << std::endl;

}
