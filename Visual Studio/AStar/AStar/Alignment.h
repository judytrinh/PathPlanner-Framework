#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include "Behavior.h"
#include <vector>

class Alignment : public Behavior
{
public:
    Alignment(vec3 target, const std::vector<Actor>& agents);
    Alignment(const Alignment& orig);
    virtual Behavior* Clone() const;
	virtual ~Alignment();

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

public:

	// behavior constants
	static float g_fKAlignment;

protected:
	const std::vector<Actor>& m_pAgents;
    vec3 m_pTarget;
};

#endif