#include "Sprite.h"

const int MAX_JUMP_HEIGHT = 100;
const int SCREEN_WIDTH = 480;

Sprite::Sprite(float x, float y, int width, int height, char *texture, bool gravityApplied) 
{
	_texture = oslLoadImageFilePNG(texture, OSL_IN_RAM, OSL_PF_5551);
	_texture->x = x;
	_x = x;
	_texture->y= y;
	_y = y;
	_width = width;
	_height = height;
	_jumping = false;
	_jumpHeight = MAX_JUMP_HEIGHT;
	_gravityApplied = gravityApplied;
	physicsId= -1;
	_speed = 5;
	_isMagnetic = false;
	_draw = true;
	
	if (_texture)
	{
		oslSetImageTileSize(_texture, 0, 0, _width, _height);
	}
}

Sprite::Sprite(void)
{
}

Sprite::~Sprite(void)
{
	oslDeleteImage(_texture);
}

void Sprite::checkErrors()
{
	if(!_texture) {
		oslDebug("Failed to load a texture");
		_error = true;
	}
}

bool Sprite::setSpeed(float speed)
{
	_speed = speed;
	
	if (_speed != speed) return false;
	
	return true;
}

float Sprite::getSpeed()
{
	return _speed;
}

int Sprite::moveLeft()
{
	_x -= _speed;
	_texture->x = _x;
	
	if (_texture->x != _x) return -1;
	
	return _x;
}

int Sprite::moveRight()
{
	_x += _speed;
	_texture->x = _x;
	
	if (_texture->x != _x) return -1;
	
	return _x;
}

int Sprite::moveLeft(int amount)
{
	_x -= amount;
	_texture->x = _x;
	
	if (_texture->x != _x) return -1;
	
	return _x;
}

int Sprite::moveRight(int amount)
{
	_x += amount;
	_texture->x = _x;
	
	if (_texture->x != _x) return -1;
	
	return _x;
}

int Sprite::moveDown(int speed)
{
	_y += speed;
	_texture->y= _y;
	
	return _y;
}

int Sprite::moveDown()
{
	_y += _speed;
	_texture->y= _y;
	
	return _y;
}

int Sprite::moveUp()
{
	_y -= _speed;
	_texture->y= _y;
	
	return _y;
}

int Sprite::jump()
{
	if (_jumping) return 1;
	
	_jumping = true;
	return 0;
}

bool Sprite::isGravityApplied()
{
	return _gravityApplied;
}

float Sprite::getX()
{
	return _texture->x;
}

float Sprite::getY()
{
	return _texture->y;
}

int Sprite::getWidth()
{
	return _width;
}

int Sprite::getHeight()
{
	return _height;
}

bool Sprite::collisionDetection(Sprite &sprite)
{
	if (_draw == false) return false;
	
	sprite.updatePos();
	if (intersects(sprite.getX(), sprite.getY(), sprite.getWidth(), sprite.getHeight()))
	{
		_jumpHeight = MAX_JUMP_HEIGHT;
		_jumping = false;
		
		return true;
	}
	
	return false;
}

bool Sprite::intersects(float X, float Y, int Width, int Height)
{
	if (_x + _width >= X && _x < (X + Width) &&
		_y + _height >= Y && _y < Y + Height)
			return true;
	
	return false;
}

bool Sprite::intersects(Sprite &sprite)
{
	float X = sprite.getX();
	float Y = sprite.getY();
	int Width = sprite.getWidth();
	int Height = sprite.getHeight();
	
	if (_x + _width >= X && _x < (X + Width) &&
		_y + _height >= Y && _y < Y + Height)
			return true;
	
	return false;
}

void Sprite::update()
{
	_texture->x = _x;
	_texture->y= _y;
	
	if(_jumping) {
		if (_jumpHeight > 0)
		{
			_jumpHeight -= _speed;
			_y -= _speed;
			_texture->y -= _speed;
			
		}
	}
}

void Sprite::updatePos()
{
	_x = _texture->x;
	_y = _texture->y;
}

void Sprite::draw()
{
	if (!_error && _draw)
	{
		oslDrawImage(_texture);
	}
}

bool Sprite::destroy()
{
	if (_draw)
		_draw = false;
}

bool Sprite::exists()
{
	return _draw;
}

bool Sprite::checkNearRight()
{
	if (_x > SCREEN_WIDTH - 50) return true;
	
	return false;
}

bool Sprite::checkNearLeft()
{
	if (_x < 50) return true;
	
	return false;
}

void Sprite::makeMagnetic()
{
	_isMagnetic = true;
}

bool Sprite::isMagnetic()
{
	return _isMagnetic;
}