#ifndef Leader_H_
#define Leader_H_

#include "Behavior.h"
#include <vector>

class Leader : public Behavior
{
public:
    Leader(vec3 target, std::vector<Actor>& agents);
    Leader(const Leader& orig);
    virtual Behavior* Clone() const;
    virtual ~Leader();

    virtual vec3 CalculateDesiredVelocity(Actor& actor);

protected:
    std::vector<Actor>& m_pAgents;
    vec3 m_pTarget;
};

#endif
