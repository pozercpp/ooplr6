#include "FileLogger.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

FileLogger::FileLogger() {
    file_.open(filename_, std::ios::app);
    if (!file_.is_open()) {
        std::cerr << "Error: Could not open log file: " << filename_ << std::endl;
    }
}

FileLogger::~FileLogger() {
    if (file_.is_open()) {
        file_.close();
    }
}

std::shared_ptr<IFightObserver> FileLogger::get() {
    static FileLogger instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void FileLogger::onFightOutcome(const std::string& event_details) {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);
    std::stringstream ss;
    ss << "[" << std::put_time(ltm, "%Y-%m-%d %H:%M:%S") << "] " << event_details << "\n";

    if (file_.is_open()) {
        file_ << ss.str();
    }
}