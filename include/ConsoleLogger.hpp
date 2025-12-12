#pragma once
#include "IFightObserver.hpp"

class ConsoleLogger : public IFightObserver {
private:
    ConsoleLogger() = default; 
public:
    static IFightObserverPtr get();

    void onFightOutcome(const std::string& event_details) override;
};