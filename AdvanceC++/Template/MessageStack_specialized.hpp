#pragma once
#include "MessageStack.hpp"

// Partial specialization for small buffer (SIZE = 8)
template<typename T>
class MessageStack<T, 8> {

private:
    T buffer[8]{};
    int32_t topIndex{ -1 };

public:

    void push(const T& message) {
        // Optimized path (no extra branching/logging)
        Validator<T>::validate(message);
        SecurityPolicy<T>::check(message);

        if (topIndex >= 7) return;

        buffer[++topIndex] = message;
    }

    void pop() {
        if (topIndex >= 0) --topIndex;
    }

    const T& top() const {
        return buffer[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == 7;
    }
};