#include "ConsoleLogger.hpp"
#include <iostream>

IFightObserverPtr ConsoleLogger::get() {
    static ConsoleLogger instance;
    return IFightObserverPtr(&instance, [](IFightObserver*){});
}

void ConsoleLogger::onFightOutcome(const std::string& event_details) {
    std::cout << "[FIGHT LOG] " << event_details << std::endl;
}                                                                                                                                                                                                                                           