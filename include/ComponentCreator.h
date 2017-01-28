//
// Created by wing on 17/01/14.
//

#pragma once

#include <memory>

#include "Creator.h"
#include "Object.h"

class ComponentCreator : public Creator {
public:
//	template<class T>
//	std::shared_ptr<T> Create(const int id);

	template<class T>
	std::shared_ptr<T> Create(const int id) {
		auto component = std::make_shared<T>();
		component->id = id;
		return component;
	}
};

