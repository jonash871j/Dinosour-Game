#pragma once
#include "Console.h"

static class Input
{
public:
	// Keyboard section ************************************************
	// Returns true if keystate is true
	static bool KeyState(int key);

	// Input key hold delayed loop
	static bool KeyStateDelayedLoop(int key);

	// Returns true if keystate is true and after the delay
	static bool KeyStateDelayed(int key, int delay);

	// Returns true if key is pressed
	static bool KeyPressed(int key);

	// Returns true if key is released
	static bool KeyReleased(int key);

	// Mouse section ***************************************************
	static int MouseGetX();
	static int MouseGetY();

	// Other section ***************************************************
	// Used to press key with code
	static void AutoPress(int key);

	// Used to clear all keystates
	static void ClearKeyBuffer();
};
