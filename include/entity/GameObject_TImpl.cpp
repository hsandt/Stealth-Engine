//
// Created by wing on 17/01/15.
//

#include <iostream>
#include "factory/FactoryUtils.h"
#include "component/Component.h"
#include "component/ActorComponent.h"
#include "component/RenderComponent.h"
#include "debug/Logger.h"
#include "geometry/Vector3.h"
#include "utils/ExceptionUtil.h"

//#include "GameObject.h"


using namespace std;

// REFACTOR: prefer shared pointers?
template<class T>
typename std::enable_if<std::is_base_of<Component, T>::value, T>::type*
GameObject::getComponent() {
	// TODO: static test with is_base_of,
	// iterating on all component
	for (auto* component : components)
	{
		// a. use dynamic cast to check component type (a bit expensive on cast)
//		T* castComponent = dynamic_cast<T*>(component);
//		if (castComponent != nullptr)
//			return castComponent;

		// b. use string id to identify component type clearly
		// (a bit expensive until we replace strings with special classes)
		if (component->getClassStringID() == T::getStringID())
			return dynamic_cast<T*>(component);
	}
	return nullptr;
}

template<class T>
typename std::enable_if<!std::is_base_of<ActorComponent, T>::value, T>::type*
GameObject::addComponent () {
	return addComponent_Internal<T>();
}

template<class T>
T* GameObject::addComponent_Internal () {
	T* component = CreateComponent<T>();
	component->setGameObject(this);
	components.push_back(component);
	component->onAddedToGameObject();
	return component;
}