#pragma once
#include <cstdint>
#include <iostream>
#include <type_traits>
#include "Validator.hpp"
#include "MessageTypes.hpp"
#include "SecureBuffer.hpp"

using std::cout;

template <typename T>
using ValidatorFunc = void (*)(const T&);


template <typename T, size_t SIZE>
class MessageStack {
	static_assert(std::is_trivially_copyable<T>::value,
		"MessageStack requires trivially copyable types");
	static_assert(SIZE > 0, "Stack size must be > 0");
	T Buffer[SIZE] = {};
	int32_t idx_pos{ -1 };

public:

	MessageStack() {
		cout << "MessageStack: Default constructor Invoked\n";
	}

	// copy constructor fo safe copying
	MessageStack(const MessageStack& other) : idx_pos(other.idx_pos) 
	{
		for (int i = 0; i <= idx_pos; ++i) {
			Buffer[i] = other.Buffer[i];
		}
	}

	// generic push --> Enforces mandatory rules, cannot be skipped e.g. This is ECU-level safety validation
	void push(const T& message) {

		// 1. core validation (mandatory)
		Validator<T>::validate(message);    
		SecurityPolicy<T>::check(message);   

		if (isFull()) {
			std::cout << "Stack Overflow!\n";
			return;
		}

		Buffer[++idx_pos] = message;
	}

	/*
	Why we need callbaks ?
		Role of Callback(Flexible Layer)
			Custom / optional logic
			Example :
		Debug checks
			Logging
			Feature - specific rules  
		This is application - level behavior
	*/

	// callback -> function pointer 
	void push(const T& message, ValidatorFunc<T> validator) {

		validator(message);  // callback
		Validator<T>::validate(message);
		SecurityPolicy<T>::check(message);

		if (isFull()) {
			std::cout << "Stack Overflow!\n";
			return;
		}

		Buffer[++idx_pos] = message;
	}

	// callback -> functor --> inline, faster and can provide state logics like 'count'
	template<typename CAllbackFuncObj>
	void push(const T& message, CAllbackFuncObj validator) {
		validator(message);
		Validator<T>::validate(message);
		SecurityPolicy<T>::check(message);

		if (isFull()) {
			std::cout << "Stack Overflow!\n";
			return;
		}

		Buffer[++idx_pos] = message;
	}

	void pop();

	const T& top() const {
		if (isEmpty()) {
			throw std::out_of_range("Stack is empty");
		}
		return Buffer[idx_pos];
		
	}

	bool isEmpty() const {
		return idx_pos == -1;
	}

	bool isFull() const {
		return idx_pos == static_cast<int32_t>(SIZE) - 1;
	}

	static MessageStack Create() {
		return MessageStack();
	}

};


/*
	Outside the class the compiler doesn't know template parameters. Hence we use  -- Longhand Template Types 
		e.g: return_type className<template_param>::func_name(){} --> void MessageStack<T, SIZE>::pop(){}
	
	Functions defined inside the class are called as Shorthand Template Types e.g: top(), push() isEmpty() etc..
*/

template <typename T, size_t SIZE>
void MessageStack<T, SIZE>::pop() {
	if (MessageStack::isEmpty()) {
		std::cout << "Stack Underflow!\n";
		return;
	}
	--idx_pos;
}