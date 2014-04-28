#ifndef WANDER_H_
#define WANDER_H_

#include "Behavior.h"

class Wander : public Behavior
{
public:
	Wander();
	Wander(vec3 mvw);
    Wander(const Wander& orig);
    virtual Behavior* Clone() const;
	virtual ~Wander();

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

public:

	// behavior constants
	static float g_fKNoise;
	static float g_fKWander;

	// the current direction
	vec3 m_vWander;
};

#endif