#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <uzebox.h>
#include <defines.h>

#include "StarterKit.h"
#include "data/font-6x12-full.inc"

#define FOLLOWER_TIME_INTERVAL 300

int rnd(int max);
void init();
void update();
void draw();
void MoveHero(int x, int y);
void drawRectangle(int x, int y, int width, int height, char c);
bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
		int width2, int height2);

static int heroX = 0;
static int heroY = 0;

static int heroWidth = 3;
static int heroHeight = 3;
static int enemyX = 0;
static int enemyY = 0;
static int enemyWidth = 3;
static int enemyHeight = 3;
static int followerX = 0;
static int followerY = 0;
static int followerWidth = 5;
static int followerHeight = 3;
static int followerThinkInterval = 300;
static int followerThinkTime = 0;
static int score = 0;
static int health = 50;
static int enemyHealth = 100;
static int money = 0;
static bool shop = false;
static bool beTrue = true;
static bool game = false;
static bool instruc = false;
static bool haveArmour = false;
static bool gameEnd = false;
static bool playerWin = false;
static bool hideText = false;

//Controller Variables
static int buttonHeld = 0;
static int buttonPressed = 0;
static int buttonReleased = 0;
static int buttonPrevious = 0;

int main() {
	//Set font and tiles to be used, and call prior to ClearVram();
	SetFontTable(font);

	init(); // Initialise Game

	while (1) {
		WaitVsync(1);
		//Update the controller Variables
		buttonHeld = ReadJoypad(0);
		buttonPressed = buttonHeld & (buttonHeld ^ buttonPrevious);
		buttonReleased = buttonPrevious & (buttonHeld ^ buttonPrevious);
		update();
		draw();
	}
}

int rnd(int max) {
	int result = rand() % max;
	return result;
}

void init() {
	heroX = rnd(SCREEN_TILES_H);
	heroY = rnd(SCREEN_TILES_V);
	enemyY = 0;

	enemyX = rnd(SCREEN_TILES_V);
	followerY = rnd(SCREEN_TILES_V);
	followerX = rnd(SCREEN_TILES_H);
}

void update() {

	switch(buttonPressed){
		case BTN_UP:{
			if(game)
			{MoveHero(0, -1);}
			if(!game || instruc)
			{
				game = setTrue(game,beTrue);
			}
			break;
		}
		case BTN_DOWN:{
			if(game)
			{MoveHero(0, 1);}
			if(!game && !instruc)
			{
				instruc = setTrue(instruc,beTrue);
				}
			break;
		}
		case BTN_LEFT:{
			MoveHero(-1, 0);
			break;
		}
		case BTN_RIGHT:{
			MoveHero(1, 0);
			break;
		}
		case BTN_A:{
			MoveHero(0, -1);
			break;
		}
		case BTN_B:{
			MoveHero(0, 1);
			break;
		}
		case BTN_X:{
			MoveHero(-1, 0);
			if(shop && !haveArmour)
			{
				hideText = setTrue(hideText,beTrue);
				money = getMoney(money,-10);
				haveArmour = setTrue(haveArmour,beTrue);
			}
			break;
		}
		case BTN_Y:{
			MoveHero(1, 0);
			break;
		}
		default:
			break;
	}


	buttonPrevious = buttonHeld;
	buttonPrevious = buttonHeld;
if(game){
	followerThinkTime++;
	if (followerThinkTime > followerThinkInterval) {
		if (followerX < heroX)
			followerX++;
		if (followerX > heroX)
			followerX--;
		if (followerY < heroY)
			followerY++;
		if (followerY > heroY)
			followerY--;
		followerThinkTime = 0;
	}
	if (score > 3 && followerThinkInterval > 0) {
		followerThinkInterval--;
	}

	if (score == 0 && followerThinkInterval <= 0){
		followerThinkInterval = FOLLOWER_TIME_INTERVAL;
	}

	//write code to move the enemy down screen
	enemyY++;

	// check if the enemy has reached the bottom of the screen
	if (enemyY >= SCREEN_TILES_V - enemyHeight) {
		// reset enemy here..
		// to top of screen and a random y
		enemyX = rnd(SCREEN_TILES_H - enemyWidth);
		enemyY = 0;
	}
	if (checkCollision(heroX, heroY, heroWidth, heroHeight, enemyX, enemyY,
			enemyWidth, enemyHeight) == true) {
		// write code to add score and reset enemy
		score = getScore(score, 1);
		if(score >= 7)
		{
			score = getScore(score,-7);
			money = getMoney(money,1);
		}
		enemyX = rnd(SCREEN_TILES_H - enemyWidth);
		enemyY = 0;
	}

	if (checkCollision(heroX, heroY, heroWidth, heroHeight, followerX,
			followerY, followerWidth, followerHeight) == true) {
		// write code to add score and reset enemy
		if(!haveArmour)
		{score = getScore(score, -1);
		health = getHealth(health, -1);}
		else{
			enemyHealth = getHealth(enemyHealth,-5);
		}
		if(score <= 0 )
		{
			score = 0;
		}
		followerX = rnd(SCREEN_TILES_H - followerWidth);
		followerY = 0;
	}
	if(money == 10)
	{
		shop = setTrue(shop,beTrue);
	}

	if(enemyHealth <= 0 || health <= 0)
	{
		gameEnd = setTrue(gameEnd,beTrue);
		if(enemyHealth <= 0){
			playerWin = setTrue(playerWin,beTrue);
		}
	}
}
}

void draw() {
	//Clear the screen (fills Vram with tile zero)
	ClearVram();
	if(!game)
	{
		if(!instruc)
		{Print(13, 3, PSTR("Welcome to Game"));
		Print(12, 5, PSTR("Please enjoy Game"));
		Print(13, 9, PSTR("UP - Start Game"));
		Print(12, 11, PSTR("DOWN - Instructions"));
		Print(17, 16, PSTR("Please"));}
		else{
			Print(8, 3, PSTR("Collect falling artefacts"));
			Print(7, 5, PSTR("Avoid artefact loving Boss"));
			Print(6, 7, PSTR("7 artefacts give you 1 money"));
			Print(2, 9, PSTR("Collect 20 money to get thorns armour"));
			Print(2, 11, PSTR("Run into boss to kill him with thorns"));
			Print(13, 15, PSTR("UP - Start Game"));
		}
	}
	if(game)
	{
		if(gameEnd){
			Print(15, 7, PSTR("Game Over"));
			if(playerWin)
			{
				Print(15, 9, PSTR("You win"));
			}
			else{
				Print(15, 9, PSTR("You lose"));
			}
		}
		else{
		Print(1, 0, PSTR("Artefacts"));
		PrintInt(14, 0, score, false);
		if(shop && !hideText)
		{
			Print(25, 15, PSTR("Buy Thorns - X"));
		}
		PrintInt(19, 0, heroX, false);
		PrintInt(24, 0, heroY, false);

	if(!haveArmour){
		Print(27, 0, PSTR("Health"));
		PrintInt(37, 0, health, false);}
		Print(1, 17, PSTR("EnemyHealth"));
		PrintInt(16, 17, enemyHealth, false);
		Print(27,17,PSTR("Money"));
		PrintInt (37,17,money,false);
		drawRectangle(heroX, heroY, heroWidth, heroHeight, '0');
		drawRectangle(enemyX, enemyY, enemyWidth, enemyHeight, '$');
		drawRectangle(followerX, followerY, followerWidth, followerHeight, 'X');
	}	
	}
}
bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
		int width2, int height2) {
	// write the code to return true if collided.
	if (x1 + width1 < x2 || y1 + height1 < y2 || x1 > x2 + width2
			|| y1 > y2 + height2) {
		return false;
	} else {
		return true;
	}
}

void MoveHero(int x, int y) {
	// write code to move hero
	heroX = heroX + x;
	heroY = heroY + y;

	// write code to check if the hero is inside the window
	if (heroX < 0 || heroX + (TILE_WIDTH / heroWidth) >= SCREEN_TILES_H || heroY < 0
			|| heroY + (TILE_HEIGHT / heroWidth) >= SCREEN_TILES_V ) {
		heroX = heroX - x;
		heroY = heroY - y;
	}
}

void drawRectangle(int x, int y, int width, int height, char c) {
	if (x < SCREEN_TILES_H && y < SCREEN_TILES_V) {

		for (int i = 0; i < width; i++) {
			if (x + i < SCREEN_TILES_H && y < SCREEN_TILES_V) {
				PrintChar(x + i, y, c);
			}
			if (y + height - 1 < SCREEN_TILES_V) {
				PrintChar(x + i, y + height - 1, c);
			}
		}
		for (int i = 1; i < height; i++) {
			PrintChar(x, y + i, c);
			PrintChar(x + width - 1, y + i, c);
		}
	}
}
