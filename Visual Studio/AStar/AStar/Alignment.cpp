#include "stdafx.h"
#include "Alignment.h"
#include "Arrival.h"

float Alignment::g_fKAlignment = 5.0f;

Alignment::Alignment(vec3 target, const std::vector<Actor>& agents) : 
    Behavior("alignment"), m_pAgents(agents), m_pTarget(target)
{
}

Alignment::~Alignment()
{
}

Alignment::Alignment(const Alignment& orig) : 
    Behavior(orig), m_pAgents(orig.m_pAgents), m_pTarget(orig.m_pTarget)
{
}

Behavior* Alignment::Clone() const
{
    return new Alignment(*this);
}

// Given the actor, return a desired velocity in world coordinates
// Alignment returns an average velocity of all active agents
vec3 Alignment::CalculateDesiredVelocity(Actor& actor)
{
	return vec3(0,0,0);
}

