#pragma once
#include "Console.h"
#include "Object.h"
#include "Font.h"

static class Draw
{
public:
	// Draw font section *************************************************

	// Used to draw a char, string or int with a font
	static void Text(Font font, int x, int y, char character, byte color);
	static void Text(Font font, int x, int y, std::string text, char direction, byte color);
	static void Text(Font font, int x, int y, int intValue, char direction, byte color);

	// Draw premade scenes ***********************************************

	// Used to draw splash screen
	static void SplashScreen(int duration);

	// Draw scene section

	// Used to draw map of scene in full scale
	static void ScenePlain(Scene scene, int xOff, int yOff);

	// Used to draw map array of scene
	static void SceneArray(Scene scene, int xOff, int yOff, byte color);


	// Draw sprite section **********************************************

	// Used to draw sprite
	static void SpritePlain(Sprite sprite, int xPos, int yPos);
	static void SpritePlain(Object object, int xOff, int yOff);

	// Used to draw sprite of object that can flip and rotate
	static void SpriteDirection(Sprite sprite, int xPos, int yPos, bool flip, int rotation);
	static void SpriteDirection(Object object, int xOff, int yOff);

	// Used to draw sprite of object that only haves a single color
	static void SpriteSingleColor(Sprite sprite, int xPos, int yPos, byte color);
	static void SpriteSingleColor(Object object, int xOff, int yOff, byte color);

	// Used to draw sprite of object that only haves a single character
	static void SpriteSingleCharacter(Sprite sprite, int xPos, int yPos, char character);
	static void SpriteSingleCharacter(Object object, int xOff, int yOff, char character);

	// Used to draw sprite of object that only haves a single character and color
	static void SpriteShape(Sprite sprite, int xPos, int yPos, char character, byte color);
	static void SpriteShape(Object object, int xOff, int yOff, char character, byte color);

	// Used to draw a background with sprite
	static void SpriteBackground(Sprite sprite);

	// Draw shape section ************************************************

	// Used to draw a background 
	static void Background(char character, byte color);

	// Used to draw a rectanlge
	static void Rectangle(int x1, int y1, int x2, int y2, char character, byte color, bool outline);

	// Used to draw a line
	static void Line(int x1, int y1, int x2, int y2, char character, byte color);

	// Used to draw a triangle
	static void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, char character, byte color);

	// Used to draw a circle
	static void Circle(int x, int y, int radius, char character, byte color);
};