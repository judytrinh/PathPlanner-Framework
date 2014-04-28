#include "StdAfx.h"
#include "Leader.h"
#include "Arrival.h"
#include "Separation.h"


Leader::Leader(vec3 target, std::vector<Actor>& agents) : 
    Behavior("leader"), m_pTarget(target), m_pAgents(agents)
{
}

Leader::Leader(const Leader& orig) : 
    Behavior(orig), m_pTarget(orig.m_pTarget), m_pAgents(orig.m_pAgents)
{
}

Behavior* Leader::Clone() const
{
    return new Leader(*this);
}

Leader::~Leader()
{
}

// Given the actor, return a desired velocity in world coordinates
// If the actor is the leader, move towards the target; otherwise, 
// follow the leader without bunching together
vec3 Leader::CalculateDesiredVelocity(Actor& actor)
{
	return vec3(0,0,0);
}
