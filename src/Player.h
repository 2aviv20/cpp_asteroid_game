#pragma once
#include "Physics/Body.h"
#include "Graphics.h"
class Player
{
public:
	Body* playerBody;
	Player(int windowWidth, int windowHeight);
	~Player();
	void rotate(Vec2 direction);
	void move(Vec2 direction);
	void shoot();
	void Update(float dt);
	void Draw();
};

