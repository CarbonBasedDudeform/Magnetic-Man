#include <oslib/oslib.h>

class Sprite
{
private:
	float _x, _y;
	int _width, _height;
	int _speed;
	OSL_IMAGE *_texture;
	bool _jumping;
	int _jumpHeight;
	bool _error;
	bool _gravityApplied;
	bool _isMagnetic;
	bool _draw;
	
public:
	Sprite(float x, float y, int width, int height, char *texture, bool gravityApplied);
	Sprite(void);
	~Sprite(void);
	
	void checkErrors();
	
	bool setSpeed(float speed);
	float getSpeed();
	
	int moveLeft();
	int moveLeft(int amount);
	int moveRight(int amount);
	int moveRight();
	int moveDown(int speed);
	int moveDown();
	int moveUp();
	
	int jump();
	bool isGravityApplied();
	
	float getX();
	float getY();
	int getWidth();
	int getHeight();
	bool intersects(float X, float Y, int Width, int Height);
	bool intersects(Sprite &sprite);
	bool collisionDetection(Sprite &sprite);
	
	void draw();
	bool destroy();
	bool exists();
	
	void update();
	void updatePos();
	
	int physicsId;
	bool checkNearRight();
	bool checkNearLeft();
	
	void makeMagnetic();
	bool isMagnetic();
};