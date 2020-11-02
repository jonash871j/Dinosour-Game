#include "Engine.h"
#include "Main.h"

FileConfig fileConfig("./", "config.ini");
Object objDino(3, 8, 8);
Object objCactus(1, 8, 8);
Object objCloud(1, 8, 8);
bool jumpState = false;
float jumpCount = 0;
float score = 0;
float best = 0;
float mSpeed = 0.75f;

void DrawGame()
{
	Draw::Background(0, BLACK);
	Draw::Text(fntNormal, 0, 0, "Score", 0, WHITE);
	Draw::Text(fntNormal, 0, 4, score, 0, WHITE);
	Draw::Text(fntNormal, 32, 0, "Best", 0, WHITE);
	Draw::Text(fntNormal, 32, 4, best, 0, WHITE);
	Draw::Line(0, SCREENHEIGHT - 8, SCREENWIDTH, SCREENHEIGHT - 8, 219, WHITE);
	Draw::SpritePlain(objCactus, 0, 0);
	Draw::SpritePlain(objCloud, 0, 0);
	Draw::SpritePlain(objDino, 0, 0);
	Console::Update();
	Console::Delay(10);
}

void start()
{
	// Startup
	Console::Create(64, 48);
	Console::SetFont(L"Terminal", 16, 16);
	Console::SetColorPalette(cpDefault);

	// Resources
	objDino.YPos = SCREENHEIGHT - 16;
	objDino.XPos = 4;
	objDino.sprite.ImportLayer("./Sprite/spr_dino01", 0);
	objDino.sprite.ImportLayer("./Sprite/spr_dino02", 1);
	objDino.sprite.ImportLayer("./Sprite/spr_dino03", 2);

	objCactus.sprite.ImportLayer("./Sprite/spr_cactus", 0);
	objCactus.YPos = SCREENHEIGHT - 16;
	objCactus.XPos = SCREENWIDTH + 32;

	objCloud.sprite.ImportLayer("./Sprite/spr_cloud", 0);
	objCloud.YPos = SCREENHEIGHT - 23;
	objCloud.XPos = SCREENWIDTH + 64;

	best = fileConfig.ReadInt("best");

	// Splash
	Draw::Background(32, WHITE);
	Draw::SplashScreen(250);
	cpDefault.FadeOut(1, 4);
	Console::SetColorPalette(cpDefault);
}

void update()
{
	// Logic
	if (Input::KeyPressed(VK_ESCAPE)) 
		terminateConsole = true;

	objDino.sprite.ChangeSpriteLayer(0);
	if ((Input::KeyPressed(VK_UP)) && (jumpState == false))
	{
		Sound::Play("./Sound/sndJump.wav");
		objDino.YPos -= 12;
		jumpState = true;
	}
	if (jumpState == true)
	{
		jumpCount++;
		if (jumpCount >= (20.0f / mSpeed))
		{
			Sound::Play("./Sound/sndGround.wav");
			objDino.YPos += 12;
			jumpState = false;
			jumpCount = 0;
		}
	}
	if ((Input::KeyState(VK_DOWN)) && (jumpState == false))
	{
		score -= 1 * mSpeed;
		objDino.sprite.ChangeSpriteLayer(1);
	}

	// Cactus
	objCactus.XPos -= mSpeed;
	if (objCactus.XPos < -16)
		objCactus.XPos = SCREENWIDTH + 8 + Random(0, 80);

	// Cactus
	objCloud.XPos -= mSpeed;
	if (objCloud.XPos < -16)
		objCloud.XPos = SCREENWIDTH + 96 + Random(0, 80);

	if (objCloud.ObjectDistance(objCactus) < 32)
		objCactus.XPos = SCREENWIDTH + 8 + Random(0, 80);

	// Score
	mSpeed += 0.0001f;
	score += 1 * mSpeed;

	if ((objDino.ObjectCollide(objCactus, 0, 0)) || (objDino.ObjectCollide(objCloud, 0, 0)))
	{
		if (score > best)
		{
			best = score;
			fileConfig.WriteInt(best, "best");
			fileConfig.FileSave();
		}

		objDino.sprite.ChangeSpriteLayer(2);
		score = 0;
		mSpeed = 0.75f;

		// Draw
		DrawGame();

		objCactus.XPos = SCREENWIDTH + 8 + Random(0, 80);
		objCloud.XPos = SCREENWIDTH + 96 + Random(0, 80);
		Sound::Play("./Sound/sndDead.wav");
		Console::Delay(1000);
	}
	// Draw
	DrawGame();
}