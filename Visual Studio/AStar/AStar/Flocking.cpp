#include "StdAfx.h"
#include "Flocking.h"
#include "Cohesion.h"
#include "Separation.h"
#include "Alignment.h"

Flocking::Flocking(vec3 target, const std::vector<Actor>& agents) :
    Behavior("flocking"), m_pTarget(target), m_pAgents(agents)
{
}

Flocking::Flocking(const Flocking& orig) :
    Behavior(orig), m_pAgents(orig.m_pAgents), m_pTarget(orig.m_pTarget)
{
}

Flocking::~Flocking()
{
}

Behavior* Flocking::Clone() const
{
    return new Flocking(*this);
}

// Given the actor, return a desired velocity in world coordinates
// Flocking combines separation, cohesion, and alignment
vec3 Flocking::CalculateDesiredVelocity(Actor& actor)
{
	return vec3(0,0,0);
}
