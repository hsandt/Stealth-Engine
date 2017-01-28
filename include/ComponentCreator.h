//
// Created by wing on 17/01/14.
//

#pragma once

#include "Creator.h"
#include "Object.h"

class ComponentCreator : public Creator {
public:
//	template<class T>
//	std::shared_ptr<T> Create(const int id);

	template<class T>
	T* Create(const int id) {
		T* component = new T();
		component->id = id;
		return component;
	}
};
