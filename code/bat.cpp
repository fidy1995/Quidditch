#include "bat.h"

void Bat::hit(Sphere &s)
{
	s.setVelocity(-force / FORCE_TO_VELO);
}