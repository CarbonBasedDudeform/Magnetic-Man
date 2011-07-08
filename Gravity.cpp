#include "Gravity.h"

Gravity::Gravity(void)
{
	_gravity = 9.81;
	
	for (int i = 0; i < sizeof(_collisionObjects); i++)
	{
		_collisionObjects[i] = NULL;
	}
	
	_curNumCollisionObjects = 0;
}

Gravity::~Gravity(void)
{
}

void Gravity::update()
{
	for (int i = 0; i < _curNumCollisionObjects; i++)
	{
		if (_collisionObjects[i].isGravityApplied() && !collisionDetection(_collisionObjects[i]))
			_collisionObjects[i].moveDown();
	}
}

bool Gravity::collisionDetection(Sprite sprite)
{
	for (int i = 0; i < _curNumCollisionObjects; i++)
	{
		for (int j = 0; j < _curNumCollisionObjects; j++)
		{
			if (_collsionObjects[i].intersects(_collisionObjects[j]) && i != j)
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Gravity::addSpriteToEngine(Sprite sprite)
{
	if (_curNumCollisionObjects >= 100) return false;
	
	_collisionObjects[_curNumCollisionObjects] = sprite
	_curNumCollisionObjects++;
	
	return true;
}