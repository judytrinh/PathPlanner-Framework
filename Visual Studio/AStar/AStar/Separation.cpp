#include "stdafx.h"
#include "Separation.h"

float Separation::g_fKSeparation = 5.0f;

Separation::Separation(vec3 target, const std::vector<Actor>& agents) : 
    Behavior("separation"), m_pAgents(agents), m_pTarget(target)
{
}

Separation::~Separation()
{
}

Separation::Separation(const Separation& orig) :
    Behavior(orig), m_pAgents(orig.m_pAgents), m_pTarget(orig.m_pTarget)
{
}

Behavior* Separation::Clone() const
{
    return new Separation(*this);
}

// Given the actor, return a desired velocity in world coordinates
// Separation tries to maintain a constant distance between all agents
// within the neighborhood of the agent
vec3 Separation::CalculateDesiredVelocity(Actor& actor)
{
   return vec3(0,0,0);
}

