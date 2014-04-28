#ifndef DEPARTURE_H_
#define DEPARTURE_H_

#include "Behavior.h"

class Departure : public Behavior
{
public:
	Departure(vec3 target);
    Departure(const Departure& orig);
    virtual Behavior* Clone() const;
	virtual ~Departure();

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

protected:
    vec3 m_pTarget;

public:
	// behavior constants
	static float g_fKDeparture;
};

#endif
