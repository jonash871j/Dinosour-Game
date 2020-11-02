#pragma once
#include "Console.h"

static class Sound
{
public:
	// Used to play a sound
	static void Play(const char* sound);

	// Used to play a beep
	static void PlayBeep(int frequency, int duration);

	// Used to stop sound
	static void Stop();

	// Used to toggle sound on/off
	static void SwitchEnableSound(bool soundState);
};
