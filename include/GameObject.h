//
//  GameObject.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include "Object.h"
#include "Renderer.h"
#include "geometry/Vector3.h"

class Component;
class Scene;

class GameObject : public Object
{

public:
    GameObject(const std::string &name);
    virtual ~GameObject();
    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) & = delete;

	void onAddedToScene(Scene* newScene);

	template<class T>
	T* GetComponent();

	template<class T>
	T* addComponent();

	/// Remove a component from this game object
	void removeComponent(Component *component);

    // update
    virtual void update(double dt) {}

    // render (will soon be replaced by Component render)
//    virtual void render(Renderer *renderer) {}

	std::string getName() const {
		return name;
	}

	void setName(const std::string &newName) {
		name = newName;
	}

	Vector3 getPosition() const {
        return position;
    }

    void setPosition(const Vector3 &pos) {
        GameObject::position = pos;
    }

protected:
	/// Name
	std::string name;

	std::vector<Component*> components;
	Scene* scene;

    Vector3 position = {0, 0, 0};  // must initialize, else garbage

    // below not required as we inherit from enable_shared_from_this with *public*
    // http://stackoverflow.com/questions/657155/how-to-enable-shared-from-this-of-both-parend-and-derived
//    template<typename Derived>
//    std::shared_ptr<Derived> shared_from_base()
//    {
//        return std::static_pointer_cast<Derived>(shared_from_this());
//    }
};


#include "GameObject_TImpl.cpp"