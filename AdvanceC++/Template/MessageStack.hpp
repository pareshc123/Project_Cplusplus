#include<cstdint>
#include<iostream>

using std::cout;

template <typename T, size_t SIZE>
class MessageStack {

	T Buffer[SIZE] = {};
	int idx_pos{ -1 };

public:

	MessageStack() {
		cout << "MessageStack: Default constructor Invoked\n";
	}

	void push(const T& message) {
		if (idx_pos >= SIZE) {
			cout << "Stack Overflow!\n";
			return;
		}
		Buffer[++idx_pos] = message;
	}

	void pop();

	const T& top() const {
		if (idx_pos < 0) {
			throw std::out_of_range("Stack is empty");
		}
		return Buffer[idx_pos];
		
	}

	bool isEmpty() {

		if (idx_pos == -1) {
			cout << "The Message Stack is currently empty.\n";
			return true;
		}
		else {
			cout << "The Message Stack is not empty.\n";
			return false;
		}
	}
};


/*
	Outside the class the compiler doesn't know template parameters. Hence we use  -- Longhand Template Types 
		e.g: return_type className<template_param>::func_name(){} --> void MessageStack<T, SIZE>::pop(){}
	
	Functions defined inside the class are called as Shorthand Template Types e.g: top(), push() isEmpty() etc..
*/

template <typename T, size_t SIZE>
void MessageStack<T, SIZE>::pop() {
	if (idx_pos < 0) {
		std::cout << "Stack underflow!\n";
		return;
	}
	--idx_pos;
}