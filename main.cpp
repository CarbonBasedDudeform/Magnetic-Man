#include <oslib/oslib.h>
#include "Physics.h"

PSP_MODULE_INFO("Magnetic Man", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 272;
int curMagnetism = 10;
int timer = 0;

int main()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	
	oslSetTransparentColor(RGB(255,0, 255));
	
	Physics physicsEngine;
	physicsEngine.setCameraSpeed(5);
	
	Sprite background(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "Images/background.png", false);
	Sprite floor(0, SCREEN_HEIGHT - 20, 800, 20, "Images/floor.png", false); 
	Sprite magneticman(100, SCREEN_HEIGHT - 51, 30, 31, "Images/magneticman.png", true);
	Sprite magnet(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 50, 50, "Images/magnet.png", true);
	Sprite aim(0, 0, 20, 20, "Images/aim.png", false);
	Sprite magnetism(0, 0, 10, 10, "Images/magnetism.png", true);
	
	magnet.makeMagnetic();
	magnetism.makeMagnetic();
	
	oslDisableTransparentColor();
	
	background.checkErrors();
	floor.checkErrors();
	magneticman.checkErrors();
	magnet.checkErrors();
	aim.checkErrors();
	magnetism.checkErrors();
	
	magneticman.setSpeed(5);
	
	magneticman.physicsId = physicsEngine.addSpriteToEngine(magneticman);
	floor.physicsId = physicsEngine.addSpriteToEngine(floor);
	magnet.physicsId = physicsEngine.addSpriteToEngine(magnet);
	magnetism.physicsId = physicsEngine.addSpriteToEngine(magnetism);
	
	while (!osl_quit)
	{
		++timer;
		
		if (curMagnetism > 0 && timer >= 500) 
		{
			--curMagnetism;
			timer = 0;
		}
		
		oslStartDrawing();
		
		oslReadKeys();
		
		magneticman.update();
		
		physicsEngine.update();
		
		if(magneticman.checkNearRight())
		{		
			physicsEngine.moveWorldLeft();
		} else if(magneticman.checkNearLeft())
		{
			physicsEngine.moveWorldRight();
		}
		
		if (osl_keys->held.left && !physicsEngine.collisionDetectionMagnets(magneticman)) magneticman.moveLeft();
		if (osl_keys->held.right && !physicsEngine.collisionDetectionMagnets(magneticman)) magneticman.moveRight();
		if (osl_keys->pressed.cross) magneticman.jump();
		
		if (osl_keys->analogX >= 120) 
		{
			aim.moveRight();
		} else if (osl_keys->analogX <= -120) 
		{
			aim.moveLeft();
		}
		
		if (osl_keys->analogY >= 120) 
		{
			aim.moveDown();
		} else if (osl_keys->analogY <= -120) 
		{
			aim.moveUp();
		}
		
		if (aim.intersects(magnet))
		{
			if (osl_keys->held.square) {
				magnet.moveLeft(curMagnetism);
			} 
		
			if (osl_keys->held.circle) {
				magnet.moveRight(curMagnetism);
			}
		}
		
		if (magnetism.exists() && aim.intersects(magnetism))
		{
			if (osl_keys->held.square) {
				magnetism.moveLeft(curMagnetism);
			} 
		
			if (osl_keys->held.circle) {
				magnetism.moveRight(curMagnetism);
			}
		}
		
		if(magnetism.exists() && magneticman.intersects(magnetism))
		{
			curMagnetism += 10 - curMagnetism;
			magnetism.destroy();
		}
		
		background.draw();
		floor.draw();
		magnet.draw();
		magnetism.draw();
		
		magneticman.draw();
		aim.draw();
		
		oslDrawFillRect(SCREEN_WIDTH - 100, 0, SCREEN_WIDTH - 100 + curMagnetism * 10, 10, RGB(0, 0, 255));
		
		oslEndDrawing();
		
		oslSyncFrame();
	}
	
	oslEndGfx();
	oslQuit();
	
	return 0;
}