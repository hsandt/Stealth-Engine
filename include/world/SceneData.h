//
// Created by wing on 17/04/13.
//

#pragma once

#include <string>

struct SceneData
{
public:
	SceneData();
	virtual ~SceneData();

//	SceneData(const SceneData &) = default;
//	SceneData & operator=(const SceneData &) = default;

	std::string name;
};


