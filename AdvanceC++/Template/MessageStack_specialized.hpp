#pragma once
#include "MessageStack.hpp"

// Partial specialization for small buffer (SIZE = 8)
template<typename T>
class MessageStack<T, 8> {

private:
    T buffer[8]{};
    int32_t idx_pos{ -1 };

public:

    MessageStack() = default;

    MessageStack(const MessageStack& other) : idx_pos(other.idx_pos) {
        for (int i = 0; i <= idx_pos; ++i) {
            buffer[i] = other.buffer[i];
        }
    }

    void push(const T& message) {
        // Optimized path (no extra branching/logging)
        Validator<T>::validate(message);
        SecurityPolicy<T>::check(message);

        if (idx_pos >= 7) return;

        buffer[++idx_pos] = message;
    }

    void pop() {
        if (idx_pos >= 0) --idx_pos;
    }

    const T& top() const {
        return buffer[idx_pos];
    }

    bool isEmpty() const {
        return idx_pos == -1;
    }

    bool isFull() const {
        return idx_pos == 7;
    }
};