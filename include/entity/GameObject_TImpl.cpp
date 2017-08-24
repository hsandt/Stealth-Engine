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

//template<class T>
//void GameObject::AddComponent() {
//    cout << "AddComponent<T>" << endl;
//}

//template<>
//void GameObject::AddComponent<Component>() {
//    cout << "AddComponent<Component>" << endl;
//    // TODO
//}

// REFACTOR: prefer shared pointers?
template<class T>
T* GameObject::getComponent() {
	// TODO: static test with is_base_of,
	// iterating on all component
    cout << "GetComponent<T>" << endl;
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
	component->gameObject = this;
	components.push_back(component);
	component->init();
	component->registerComponent();
	return component;
}