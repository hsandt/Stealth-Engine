//
//  WindowManager.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

enum class KeyStaticState;

struct GameConfig;

class GameApplication;

class WindowManager
{
public:
    /// Generic callback method on error
    virtual void errorCallback(int error, const char* description) = 0;

    /// Initialize window manager with game config
    virtual void init(const GameConfig & gameConfig) = 0;

	/// Process all the pending events
	virtual void pollEvents() = 0;

	/// Should the window be closed? (when the close button has been clicked, etc.)
	virtual int windowShouldClose() = 0;

	/// Swap the front and back buffers
	virtual void swapBuffers() = 0;

	/// Return the state of the key for the given keycode
	virtual int getKey(int key) = 0;

	/// Return a key static state from a window-manager-specific key state code
	/// This function is not static so that it can be virtual, so at least it is made const
	virtual KeyStaticState toKeyStaticState(int keyStateCode) const = 0;

	/// Set screenWidth and screenHeight to the size of the frame buffer, in screen coordinates
	virtual void getFramebufferSize(int* screenWidth, int* screenHeight) = 0;

};
