#ifndef SEPARATION_H_
#define SEPARATION_H_

#include "Behavior.h"
#include <vector>

class Separation : public Behavior
{
public:
	Separation(vec3 target, const std::vector<Actor>& agents);
    Separation(const Separation& orig);
    virtual Behavior* Clone() const;
	virtual ~Separation();

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

public:

	// behavior constants
	static float g_fKSeparation;

protected:
    const std::vector<Actor>& m_pAgents;
    vec3 m_pTarget;
};

#endif
