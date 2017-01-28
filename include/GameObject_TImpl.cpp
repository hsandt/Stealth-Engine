//
// Created by wing on 17/01/15.
//

#include <iostream>
#include "FactoryUtils.h"
#include "Component.h"
#include "RenderComponent.h"
#include "geometry/Vec3.h"

#include "GameObject.h"


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
T* GameObject::GetComponent() {
	// TODO: static test with is_base_of,
	// iterating on all components
    cout << "GetComponent<T>" << endl;
    return nullptr;
}

template<class T>
T* GameObject::addComponent () {
	T* component = CreateComponent<T>();
	component->gameObject = this;
	components.push_back(component);
	component->onAddedToGameObject();
}


// NOT NEEDED?
//template<>
//shared_ptr<Component> GameObject::GetComponent<Component>() {
//    cout << "GetComponent<Component>" << endl;
//    return nullptr;
//}

//template<>
//shared_ptr<RenderComponent> GameObject::GetComponent<RenderComponent>() {
//    cout << "GetComponent<RenderComponent>" << endl;
////	return dynamic_pointer_cast<RenderComponent>(components[0]);  // ultra-cheat to test
//    return nullptr;
//
//}
