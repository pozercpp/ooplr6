#pragma once
#include <string>
#include <memory>

class IFightObserver {
public:
    virtual ~IFightObserver() = default;
    
    virtual void onFightOutcome(const std::string& event_details) = 0; 
};

using IFightObserverPtr = std::shared_ptr<IFightObserver>;