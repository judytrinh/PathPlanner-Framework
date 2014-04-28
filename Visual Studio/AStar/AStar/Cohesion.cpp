#include "StdAfx.h"
#include "Cohesion.h"

float Cohesion::g_fKCohesion = 3.0f;

Cohesion::Cohesion(const std::vector<Actor>& agents) : 
    Behavior("cohesion"), m_pAgents(agents)
{
}

Cohesion::~Cohesion()
{
}

Cohesion::Cohesion(const Cohesion& orig) : Behavior(orig), m_pAgents(orig.m_pAgents)
{
}

Behavior* Cohesion::Clone() const
{
    return new Cohesion(*this);
}

// Given the actor, return a desired velocity in world coordinates
// Cohesion moves actors towards the center of a group of agents
vec3 Cohesion::CalculateDesiredVelocity(Actor& actor)
{
    return vec3(0,0,0);
}
