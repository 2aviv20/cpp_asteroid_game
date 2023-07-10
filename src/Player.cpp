#include "Player.h"

Player::Player(int windowWidth,int windowHeight)
{
	this->playerBody = new Body(PolygonShape({ Vec2(-20, 0), Vec2(0, 20),Vec2(20, 0) }), windowWidth / 2,windowHeight / 2,1.0f);
}

Player::~Player()
{
	delete this->playerBody;
}

void Player::rotate(Vec2 direction)
{

}

void Player::move(Vec2 direction)
{
	this->playerBody->velocity + direction;
}

void Player::shoot()
{
}

void Player::Update(float dt)
{

}

void Player::Draw()
{
	PolygonShape* polygon = (PolygonShape*)this->playerBody->shape;
	Graphics::DrawPolygon(this->playerBody->position.x, this->playerBody->position.y, polygon->worldVertices, 0xFFFFFFFF);
}
