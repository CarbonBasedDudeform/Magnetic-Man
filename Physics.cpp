#include "Physics.h"

const int MAX_OBJECTS = 20;

Physics::Physics(void)
{
	_gravity = 2;
	_cameraSpeed = 5;
	
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		_collisionObjects[i] = NULL;
	}
	
	_curNumCollisionObjects = 0;
}

Physics::~Physics(void)
{
}

void Physics::update()
{
	for (int i = 0; i < _curNumCollisionObjects; i++)
	{
		if (_collisionObjects[i]->isGravityApplied())
		{		
			if (collisionDetection(*_collisionObjects[i]) == false)
			{
				_collisionObjects[i]->moveDown(_gravity);
			}
		}
	}
}

void Physics::update(int Id, Sprite &sprite)
{
	_collisionObjects[Id] = &sprite;
}

bool Physics::collisionDetection(Sprite &sprite)
{
	for (int i = 0; i < _curNumCollisionObjects; i++)
	{
		if (sprite.physicsId != i) //&sprite != &_collisionObjects[i]
		{
			if (sprite.collisionDetection(*_collisionObjects[i]))
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Physics::collisionDetectionMagnets(Sprite &sprite)
{
	for (int i = 0; i < _curNumCollisionObjects; i++)
	{
		if (sprite.physicsId != i) //&sprite != &_collisionObjects[i]
		{
			if (sprite.collisionDetection(*_collisionObjects[i]))
			{
				if (_collisionObjects[i]->isMagnetic())
				{
					return true;
				}
			}
		}
	}
	
	return false;
}

int Physics::addSpriteToEngine(Sprite &sprite)
{
	if (_curNumCollisionObjects >= MAX_OBJECTS) return -1;
	
	_collisionObjects[_curNumCollisionObjects] = &sprite;
	int toRtn = _curNumCollisionObjects;
	_curNumCollisionObjects++;
	
	return toRtn;
}

void Physics::moveWorldLeft()
{
	for (int i = 0; i < _curNumCollisionObjects; i++)
	{
		_collisionObjects[i]->moveLeft();
	}
}

void Physics::moveWorldRight()
{
	for (int i = 0; i < _curNumCollisionObjects; i++)
	{
		_collisionObjects[i]->moveRight(_cameraSpeed);
	}
}

void Physics::setCameraSpeed(int amount)
{
	_cameraSpeed = amount;
}

int Physics::getCameraSpeed()
{
	return _cameraSpeed;
}