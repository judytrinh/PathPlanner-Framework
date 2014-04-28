#ifndef COHESION_H_
#define COHESION_H_

#include "Behavior.h"
#include <vector>

class Cohesion : public Behavior
{
public:
	Cohesion(const std::vector<Actor>& agents);
    Cohesion(const Cohesion& orig);
    virtual Behavior* Clone() const;
	virtual ~Cohesion();

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

public:
	// behavior constants
	static float g_fKCohesion;

protected:
    const std::vector<Actor>& m_pAgents;
};

#endif
