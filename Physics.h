#include "Sprite.h"

class Physics
{
private:
	int _gravity;
	Sprite *_collisionObjects[20];
	int _curNumCollisionObjects;
	int _cameraSpeed;
	
public:
	Physics(void);
	~Physics(void);
	
	void update();
	void update(int ID, Sprite &sprite);
	bool collisionDetection(Sprite &sprite);
	bool collisionDetectionMagnets(Sprite &sprite);
	int addSpriteToEngine(Sprite &sprite);
	
	void moveWorldLeft();
	void moveWorldRight();
	void setCameraSpeed(int speed);
	int getCameraSpeed();
};