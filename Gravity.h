#include "Sprite.h"

class Physics
{
private:
	_gravity;
	Sprite _collisionObjects[100];
	int _curNumCollisionObjects;
	
public:
	Physics(void);
	~Physics(void);
	
	void update();
	bool collisionDetection(Sprite sprite);
	bool addSpriteToEngine(Sprite sprite);
};