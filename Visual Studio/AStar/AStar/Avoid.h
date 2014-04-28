#ifndef Avoid_H_
#define Avoid_H_

#include "Behavior.h"
#include <vector>

class Avoid : public Behavior
{
public:
    Avoid(vec3 target, const std::vector<Obstacle>& obstacles);
    Avoid(const Avoid& orig);
    virtual Behavior* Clone() const;
	virtual ~Avoid();

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

public:
	static float g_fKAvoid;
	static float g_fTAvoid;

protected:

	const std::vector<Obstacle>& m_pObstacles;
    vec3 m_pTarget;
};

#endif