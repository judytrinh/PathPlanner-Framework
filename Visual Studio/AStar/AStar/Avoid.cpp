#include "StdAfx.h"
#include "Avoid.h"
#include "Arrival.h"

float Avoid::g_fKAvoid = 1000.0f;
float Avoid::g_fTAvoid = 5.0f;

Avoid::Avoid(vec3 target, const std::vector<Obstacle>& obstacles) : 
	Behavior("avoid"), m_pTarget(target), m_pObstacles(obstacles)
{
}

Avoid::Avoid(const Avoid& orig) : 
	Behavior(orig), m_pTarget(orig.m_pTarget), m_pObstacles(orig.m_pObstacles)
{
}

Behavior* Avoid::Clone() const
{
    return new Avoid(*this);
}

Avoid::~Avoid()
{
	 m_pTarget = vec3(0,0,0);
}

// Given the actor, return a desired velocity in world coordinates
// If an actor is near an obstacle, avoid adds either a tangential or
// normal response velocity
vec3 Avoid::CalculateDesiredVelocity(Actor& actor)
{
	return vec3(0,0,0);
}

