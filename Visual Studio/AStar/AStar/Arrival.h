#ifndef ARRIVAL_H_
#define ARRIVAL_H_

#include "Behavior.h"

class Arrival : public Behavior
{
public:
	Arrival(vec3 target);
    Arrival(const Arrival& orig);
	virtual ~Arrival();
    virtual Behavior* Clone() const;

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

protected:
    
    vec3 m_pTarget;

public:
	// behavior constants
	static float g_fKArrival;
};

#endif