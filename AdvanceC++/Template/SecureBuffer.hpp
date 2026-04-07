#pragma once
#include <iostream>
#include "MessageTypes.hpp"

// Generic security policy
template<typename T>
struct SecurityPolicy {
    static void check(const T&) {
        // default: no security checks
    }
};

// Diagnostic specialization (UDS Security Access)
template<>
struct SecurityPolicy<DiagnosticMessage> {
    static void check(const DiagnosticMessage& msg) {
        if (msg.serviceID == 0x27) {
            std::cout << "[SECURITY] UDS Security Access detected!\n";
        }
    }
};