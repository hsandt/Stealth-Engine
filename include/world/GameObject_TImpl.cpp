//
// Created by wing on 17/01/15.
//

#include <iostream>
#include "core/factory/FactoryUtils.h"
#include "Component.h"
#include "component/ActorComponent.h"
#include "component/RenderComponent.h"
#include "core/Logger.h"
#include "core/math/Vector3.h"
#include "core/ExceptionUtil.h"

//#include "GameObject.h"


using namespace std;

// REFACTOR: prefer shared pointers?
template<class T>
typename std::enable_if<std::is_base_of<Component, T>::value, T>::type*
GameObject::getComponent() {
	// TODO: static tests with is_base_of,
	// iterating on all components
	for (auto* component : components)
	{
		// a. (for now) use dynamic cast to check components type (require RTTI)
		// b. (incomplete) use string id to identify components type clearly
		// (requires custom RTTI, a bit expensive until we replace strings with CRC, hashstrings...)
		// FIXME: to support base class detection, you need to iterate upward over class string IDs

		// a.
		T* castComponent = dynamic_cast<T*>(component);
		if (castComponent != nullptr)
		{
			return castComponent;
		}

		// b.
		/*
		if (components->getClassStringID() == T::getStringID())
		{
			// safety for bad class string IDs (use standard RTTI)
			T* castComponent = dynamic_cast<T*>(components);
			if (castComponent == nullptr)
			{
				LOGERRF("components is not of type T, T::getStringID() or components->getClassStringID() is wrong (both"
					        " are %s)",
				        T::getStringID().c_str());
			}
			// redundant
			assert(castComponent != nullptr);

			// we are pretty sure components is of type T now, so we static cast
			return static_cast<T*>(components);
		}
		*/
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