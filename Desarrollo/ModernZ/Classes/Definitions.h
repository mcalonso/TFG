#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//Define times transition scenes
#define DISPLAY_TIME_SPLASH_SCENE	1
#define DISPLAY_TIME_SPLASH_MENU	2
#define DISPLAY_TIME_SPLASH_SCENEV	2
#define TRANSITION_TIME				0.5
#define TRANSITION_TIME_MENU		0.5

//Define step world
#define VELOCITY_ITINERATIONS		8   //how strongly to correct velocity
#define POSITIONS_ITINERATIONS		3   //how strongly to correct position

//Define conversion box2d unit
#define PPM 32.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

//Define player and bot
#define velPlayer 200
#define jumpForce 350

//Define Sprites
#define Sprite_Ignatius "playerOriginal1.png"
#define Sprite_Nereita "girlStop.png"
#define Sprite_Zombi1 "zStop.png"

//Define user data body
#define DATA_PLATFORM				1
#define DATA_PLAYER					2
#define DATA_PLAYER_SENSOR1			3
#define DATA_PLAYER_SENSOR2			4
#define DATA_VOID					5
#define DATA_DESTROYABLE			6

//Define id cllision mask
#define M_PLAYER					0x0001
#define M_SUELO						0x0002

#endif // __DEFINITIONS_H__
