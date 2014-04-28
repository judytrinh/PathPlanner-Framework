#include "stdafx.h"
#include "Seek.h"


Seek::Seek(vec3& target) : Behavior("seek"), m_pTarget(target)
{
}

Seek::~Seek()
{
    m_pTarget = vec3(0,0,0);
}

Seek::Seek(const Seek& orig) : Behavior(orig), m_pTarget(orig.m_pTarget)
{
}

Behavior* Seek::Clone() const
{
    return new Seek(*this);
}

// Given the actor, return a desired velocity in world coordinates
// Seek returns a maximum velocity towards the target
vec3 Seek::CalculateDesiredVelocity(Actor& actor)
{
    vec3 actorPos = actor.globalPosition;
    vec3 desiredDirection = m_pTarget - actorPos;
    desiredDirection.Normalize();

    vec3 desiredVelocity = desiredDirection * g_fMaxSpeed;
	return desiredVelocity;	
}

