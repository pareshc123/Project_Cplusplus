#pragma once
#include <stdexcept>
#include "MessageTypes.hpp"

// generic Validator
template<typename T>
struct Validator {
    static void validate(const T&) {
        // default: do nothing
    }
};

// Explicit specialization for CANFrame
template<>
struct Validator<CANFrame> {
    static void validate(const CANFrame& message) {
        if (message.dlc > 8) {
            throw std::runtime_error("Invalid DLC for CAN");
        }
    }
};