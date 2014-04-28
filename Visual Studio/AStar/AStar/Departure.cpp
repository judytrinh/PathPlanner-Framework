#include "stdafx.h"
#include "Departure.h"

float Departure::g_fKDeparture = 1.0f;

Departure::Departure(vec3 target) : Behavior("departure"), m_pTarget(target)
{
}

Departure::~Departure()
{
    m_pTarget = vec3(0,0,0);
}

Departure::Departure(const Departure& orig) : 
    Behavior(orig), m_pTarget(orig.m_pTarget)
{
}

Behavior* Departure::Clone() const
{
    return new Departure(*this);
}

// Given the actor, return a desired velocity in world coordinates
// Departure calculates a repelent velocity based on the actor's 
// distance from the target
vec3 Departure::CalculateDesiredVelocity(Actor& actor)
{
	return vec3(0,0,0);
}