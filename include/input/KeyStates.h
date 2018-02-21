//
// Created by Long Nguyen Huu on 2016/06/21.
//

#pragma once

enum class KeyStaticState
{
	NONE,
	UP,
	DOWN
};

enum class KeyDynamicState
{
	RELEASED,
	HELD_UP,
	PRESSED,
	HELD_DOWN
};
