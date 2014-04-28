#include "StdAfx.h"
#include "Behavior.h"
#include <math.h> 

#include "Alignment.h"
#include "Arrival.h"
#include "Avoid.h"
#include "Cohesion.h"
#include "Departure.h"
#include "Flee.h"
#include "Flocking.h"
#include "Leader.h"
#include "Seek.h"
#include "Separation.h"
#include "Wander.h"

float Behavior::g_fMaxSpeed = 4.0f;
float Behavior::g_fMaxAccel = 10.0f;
float Behavior::g_fKNeighborhood = 100.0f;
float Behavior::g_fOriKv = 1000.0f;//256.0;  // Orientation
float Behavior::g_fOriKp = 320.0f;//32.0; 
float Behavior::g_fVelKv = 10.0;  // Velocity
float Behavior::g_fAgentRadius = 2.0;


Behavior::Behavior(const char* name) : m_name(name)
{
}

Behavior::Behavior(const Behavior& orig) : m_name(orig.m_name)
{
}

const std::string& Behavior::GetName() const
{
    return m_name;
}

// Given an actor and desired velocity, calculate a corresponding force
vec3 Behavior::CalculateForce(Actor& actor, const vec3& dvel)
{
	//your code goes here
	float m = actor.mass;
	vec3 v = actor.linearVelocity;

	// see equation in handout
	vec3 force = m * (g_fVelKv * (dvel - v));
	
	return force;
}

// Given an actor and desired velocity, calculate a corresponding torque
vec3 Behavior::CalculateTorque(Actor &actor, const vec3& dvel)
{   
	//if (dvel.Length() < 0.0001f) return vec3(0,0,0);

	// 1. Get current rotation matrix
	mat3 R = actor.globalOrientation;
	// 2. Construct desired rotation matrix 
    // (This corresponds to facing in the direction of our desired velocity)
	// Note: Z points forwards; Y Points UP; and X points left
	/*vec3 yCol = vec3(0, 1.0f, 0);
	vec3 zCol = vec3(dvel).Normalize();
	vec3 xCol = yCol.Cross(zCol).Normalize();*/
	//mat3 dR = mat3(xCol, yCol, zCol);
	/*vec3 row1 = vec3(xCol[0], yCol[0], zCol[0]);
	vec3 row2 = vec3(xCol[1], yCol[1], zCol[1]);
	vec3 row3 = vec3(xCol[2], yCol[2], zCol[2]);
	*/
	/*vec3 row1 = vec3(xCol[0], xCol[1], xCol[2]);
	vec3 row2 = vec3(yCol[0], yCol[1], yCol[2]);
	vec3 row3 = vec3(zCol[0], zCol[1], zCol[2]);
	/*

	//mat3 dR = mat3(row1, row2, row3);

	// 3. Compute the change in rotation matrix that will
	// rotate the actor towards our desired rotation
	//mat3 deltaR = dR * R.Transpose(); // THIS HAS TO BE CORRECT

	
	// 4. Construct quaternion to get axis and angle from dr
	// From writeup: deltaTheta = AxisAngle(R_{d} * R^{T})
	/*Quaternion dQuat = deltaR.ToQuaternion();
	vec3 axis(0,0,0);
	float angleRad = 0;
	dQuat.ToAxisAngle(axis, angleRad);
	*/
	vec3 deltaR = R.Transpose() * dvel;
	float thetad = atan2(deltaR[0],deltaR[2]);
	// put angle on Y axis
	vec3 deltaTheta = vec3(0,thetad,0);
	// find torque
	vec3 omega = actor.angularVelocity;
	mat3 I = actor.globalInertialTensor;
	float Kp = g_fOriKp;
	float Kv = g_fOriKv;
	//vec3 deltaTheta = angleRad * axis; //??
	vec3 torque = omega.Cross(I * omega) + I * (Kp*deltaTheta - Kv*omega);

	return torque;
}