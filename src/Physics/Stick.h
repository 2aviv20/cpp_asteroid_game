#ifndef STICK_H
#define STICK_H

#include "../Graphics.h"
#include "Vec2.h"
#include <math.h>   

class ParticleVarlet;
class Stick {
	public:
		ParticleVarlet* p0 = nullptr;
		ParticleVarlet* p1 = nullptr;
		float length;
		bool isActive = true;
		bool isSelected = false;
		Stick(ParticleVarlet* p0, ParticleVarlet* p1, float length);
		void Draw();
		void Update();
		Vec2 getDifference();
		float getLength(Vec2 v);
		void Break();
		void SetIsSelected(bool value);
};
#endif
