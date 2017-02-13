//==============================================================================
// Key.h
// Copyright 27 Heisei L Nguyen Huu. All rights reserved.
//==============================================================================

#pragma once

#include <array>

enum class Key
{
	SPACE,
	APOSTROPHE,     /* ' */
	COMMA,          /* , */
	MINUS,          /* - */
	PERIOD,         /* . */
	SLASH,          /* / */
	ALPHA_0,
	ALPHA_1,
	ALPHA_2,
	ALPHA_3,
	ALPHA_4,
	ALPHA_5,
	ALPHA_6,
	ALPHA_7,
	ALPHA_8,
	ALPHA_9,
	SEMICOLON,      /* ; */
	EQUAL,          /* = */
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	LEFT_BRACKET,   /* [ */
	BACKSLASH,      /* \ */
	RIGHT_BRACKET,  /* ] */
	GRAVE_ACCENT,   /* ` */
	WORLD_1,        /* non-US #1 */
	WORLD_2,        /* non-US #2 */
	ESCAPE,
	ENTER,
	TAB,
	BACKSPACE,
	INSERT,
	DELETE,
	RIGHT,
	LEFT,
	DOWN,
	UP,
	PAGE_UP,
	PAGE_DOWN,
	HOME,
	END,
	CAPS_LOCK,
	SCROLL_LOCK,
	NUM_LOCK,
	PRINT_SCREEN,
	PAUSE,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	F25,
	KP_0,
	KP_1,
	KP_2,
	KP_3,
	KP_4,
	KP_5,
	KP_6,
	KP_7,
	KP_8,
	KP_9,
	KP_DECIMAL,
	KP_DIVIDE,
	KP_MULTIPLY,
	KP_SUBTRACT,
	KP_ADD,
	KP_ENTER,
	KP_EQUAL,
	LEFT_SHIFT,
	LEFT_CONTROL,
	LEFT_ALT,
	LEFT_SUPER,
	RIGHT_SHIFT,
	RIGHT_CONTROL,
	RIGHT_ALT,
	RIGHT_SUPER,
	MENU,
    COUNTER  // only used to count values; must start at value 0
};

/*
/// Array of all buttons, can be used to iterate, otherwise convert int to enum above
constexpr std::array<Key, static_cast<int>(Key::COUNTER)> allButtons = {
    Key::HELP_UP,
    Key::HELD_DOWN,
    Key::LEFT,
    Key::RIGHT,
    Key::QUIT
};
 */