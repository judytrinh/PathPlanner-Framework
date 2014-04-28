#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H

#include "Transformation.h"
#include <string>
#include <float.h>

typedef struct
{
	vec3 globalPosition;
	vec3 linearVelocity;
	vec3 angularVelocity;
	mat3 globalOrientation;
	mat3 globalInertialTensor;
	vec3 wander;
	float mass;
	int agentID;
	int behavior;

} Actor;

typedef struct
{
	vec3 globalPosition;
	float radius;

} Obstacle;

// Behavior is an abstract base class for all behaviors

class Behavior
{
public:
    Behavior(const Behavior& orig);
    virtual ~Behavior() {}
    virtual const std::string& GetName() const;
    virtual Behavior* Clone() const = 0;

    // Given an actor and behavior parameters, return a desired
    // velocity in world coordinates
    virtual vec3 CalculateDesiredVelocity(Actor &actor) = 0;

    Behavior(const char* name);

    // Given an actor and desired velocity, calculate a corresponding torque
    virtual vec3 CalculateTorque(Actor &actor, const vec3& dvel);

    // Given an actor and desired velocity, calculate a corresponding force
    virtual vec3 CalculateForce(Actor &actor, const vec3& dvel);

    std::string m_name;

public:

    // Globals used by all behaviors
    static float g_fMaxSpeed;
    static float g_fMaxAccel;
   
    static float g_fVelKv;
    static float g_fOriKv;
    static float g_fOriKp;

    static float g_fKNeighborhood;
    static float g_fAgentRadius;
};

#endif