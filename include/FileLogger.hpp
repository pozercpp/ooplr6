#pragma once
#include "IFightObserver.hpp"
#include <fstream>
#include <memory>

class FileLogger : public IFightObserver {
private:
    std::ofstream file_;
    const std::string filename_ = "log.txt";

    FileLogger(); 
    
public:
    static std::shared_ptr<IFightObserver> get();
    ~FileLogger() override;

    void onFightOutcome(const std::string& event_details) override;
};