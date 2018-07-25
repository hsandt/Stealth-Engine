//
// Created by wing on 17/01/14.
//

#pragma once

#include <iostream>

class GameObjectCreator {
public:

	// defined in header, else include templ_impl.cpp at the end of the file
	template<class T>
	T* Create(const int id) {
		auto go = new T();
		go->id = id;
		go->setNameToDefault();
		go->init();
		return go;
	}

};

