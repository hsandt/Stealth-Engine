//
// Created by wing on 17/01/14.
//

#pragma once

class ComponentCreator {
public:

	template<class T>  // T : Component
	T* Create(const int id) {
		T* component = new T();
		component->id = id;
		component->init();
		return component;
	}

};
