#pragma once
#pragma once

// class InputManager provides information about pressed key on Windows OS.
class InputManager
{
public:

	// Every enumerator has its own Windows code of a key.

	enum class Key
	{
		Back = 8,
		Enter = 13,
		Escape = 27,
		MINUS = 45,
		NUM_0 = 48,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
		ArrowUp = 72,
		ArrowLeft = 75,
		ArrowRight = 77,
		ArrowDown = 80,
		Arrow = 224,
		None = -1
	};

	static bool UserPressedKey();
	static Key PressedKey();

private:
	static Key pressedKey;
};

