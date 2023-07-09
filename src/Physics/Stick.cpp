//#include "Stick.h"
//#include "Particle_varlet.h"
//
//Stick::Stick(ParticleVarlet* p0, ParticleVarlet* p1, float length) {
//	this->p0 = p0;
//	this->p1 = p1;
//	this->length = length;
//}
////Stick::Stick(ParticleVarlet* p0, ParticleVarlet* p1, float length) : p0(p0), p1(p1), length(length) {}
//
//Vec2 Stick::getDifference() {
//    float diffX = this->p0->position.x - this->p1->position.x;
//    float diffY = this->p0->position.y - this->p1->position.y;
//    return Vec2(diffX,diffY);
//}
//
//float Stick::getLength(Vec2 v) {
//    //Pythagoras
//    return sqrt((v.x * v.x) + (v.y * v.y));
//}
//void Stick::Draw() {
//	if (!isActive)
//		return;
//	Graphics::DrawLine(this->p0->position.x, this->p0->position.y, this->p1->position.x, this->p1->position.y, 0xFFFFFFFF);
//}
//
//void Stick::Break()
//{
//	isActive = false;
//}
//
//void Stick::SetIsSelected(bool value)
//{
//	isSelected = value;
//}
//void Stick::Update() 
//{
//		if (!isActive)
//			return;
//
//		Vec2 p0Pos = this->p0->position;
//		Vec2 p1Pos = this->p1->position;
//
//		Vec2 diff = p0Pos - p1Pos;
//		float dist = sqrtf(diff.x * diff.x + diff.y * diff.y);
//		float diffFactor = (length - dist) / dist;
//		Vec2 offset = diff * diffFactor * 0.5f;
//
//		this->p0->SetPosition(p0Pos.x + offset.x, p0Pos.y + offset.y);
//		this->p1->SetPosition(p1Pos.x - offset.x, p1Pos.y - offset.y);
//}
