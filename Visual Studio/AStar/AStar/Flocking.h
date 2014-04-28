#ifndef Flocking_H_
#define Flocking_H_

#include "Behavior.h"
#include <vector>

class Flocking : public Behavior
{
public:
    Flocking(vec3 target, const std::vector<Actor>& agents);
    Flocking(const Flocking& orig);
    virtual ~Flocking();
    virtual Behavior* Clone() const;

    virtual vec3 CalculateDesiredVelocity(Actor& actor);

protected:
    vec3 m_pTarget;
    const std::vector<Actor>& m_pAgents;
};

#endif