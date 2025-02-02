#pragma once
#include "Gui.h"
#include <functional>


#define EMIT(func, ...) if (func != nullptr) { func(__VA_ARGS__); }

template < typename ...Args>
using Signal = std::function<void(Args...)>;

template <class A, class B, typename ...Args>
void connect(B* receiver, void (B::* slot)(Args...), Signal<Args...>& signal) {

	signal = [=](Args... args) {
		
		std::invoke(slot, receiver, std::forward<Args>(args)...);
	};
}