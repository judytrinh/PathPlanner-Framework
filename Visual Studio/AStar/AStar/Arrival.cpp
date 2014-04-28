#include "stdafx.h"
#include "Arrival.h"

float Arrival::g_fKArrival = 0.5f;

Arrival::Arrival(vec3 target) : Behavior("arrival"), m_pTarget(target)
{
}

Arrival::Arrival(const Arrival& orig) :
    Behavior(orig), m_pTarget(orig.m_pTarget)
{
}

Arrival::~Arrival()
{
    m_pTarget = vec3(0,0,0);
}

Behavior* Arrival::Clone() const
{
    return new Arrival(*this);
}

// Given the actor, return a desired velocity in world coordinates
// Arrival returns a velocity whose speed is proportional to the actors distance
// from the target
vec3 Arrival::CalculateDesiredVelocity(Actor& actor)
{
	// error vector
	vec3 e = m_pTarget - actor.globalPosition;

	// v_{arrival} equation
	vec3 vArrival = g_fKArrival * e;

	// desired speed vd
	float vd = vArrival.Length();

	// calculate desired theta and clamp to [-M_PI, M_PI]
	float thetad = atan2(e[2], e[0]);
	if (thetad > M_PI) thetad = -(2*M_PI - fmod(thetad, 2*M_PI));
	else if (thetad < -M_PI) thetad = 2*M_PI - fmod(fabs(thetad), 2*M_PI);

	// create vector pointing in direction of thetad with magnitude of vd
	return vec3(vd*cos(thetad), 0, vd*sin(thetad));
}
