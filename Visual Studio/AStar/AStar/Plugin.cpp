#include "stdafx.h"
#include "Behavior.h"
#include "Environment.h"
#include "Alignment.h"
#include "Arrival.h"
#include "Avoid.h"
#include "Cohesion.h"
#include "Departure.h"
#include "Flee.h"
#include "Flocking.h"
#include "FollowPath.h"
#include "Leader.h"
#include "Seek.h"
#include "Separation.h"
#include "Wander.h"


#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

extern "C"
{

	enum Behaviors { alignment, arrival, avoid, cohesion, departure, flee, 
					flocking, followpath, leader, seek, separation, wander};

	//struct used to get actor data from Unity
	typedef struct
	{
		float gPos[3];
		float lVel[3];
		float aVel[3];
		float gOrient[4];
		float gITens[4];
		float mass;
		int agentID;
		int behavior;

	} actorParameter;

	//copies data from actorParameter to Actor struct
	void copy(actorParameter& ap, Actor& A)
	{
		A.globalPosition = vec3(ap.gPos[0], ap.gPos[1], ap.gPos[2]);
		A.linearVelocity = vec3(ap.lVel[0], ap.lVel[1], ap.lVel[2]);
		A.angularVelocity = vec3(ap.aVel[0], ap.aVel[1], ap.aVel[2]);

		Quaternion q1(ap.gOrient[3], ap.gOrient[0], ap.gOrient[1], ap.gOrient[2]);
		A.globalOrientation.FromQuaternion(q1);
		Quaternion q2(ap.gITens[3], ap.gITens[0], ap.gITens[1], ap.gITens[2]);
		A.globalInertialTensor.FromQuaternion(q2);

		A.mass = ap.mass;
		A.agentID = ap.agentID;
		A.behavior = ap.behavior;
	}

	static Environment ENV;
	static vector<Actor> AgentList;
	static FollowPath* FPList;

	void EXPORT_API initialize(int agentcount)
	{
		ENV.clearObstacles();
		FPList = new FollowPath[agentcount];
	}

	//store all actor data from Unity in AgentList 
	void EXPORT_API transferActorData(actorParameter agents[], int agentcount)
	{
		AgentList.clear();
		for (int i=0; i<agentcount; i++)
		{
			Actor A;
			copy(agents[i], A);
			AgentList.push_back(A);
		}
	}

	void CalculateDesiredVelocity(int agentID, vec3 target, vec3& dvel)
	{
		vec3 dv(0,0,0);
		Actor A = AgentList[agentID];
		int behavior = A.behavior;

		if (behavior == followpath)
		{
			dv = FPList[agentID].CalculateDesiredVelocity(A);
		}
		
		if (dv.Length() > Behavior::g_fMaxSpeed)
 		{
			dv.Normalize();
			dv *= Behavior::g_fMaxSpeed;
 		}

		dvel = dv;
	}

	//wrapper function for Behavior::CalculateForce
	void EXPORT_API CalculateForce(int agentID, float* target, float* force)
	{
		vec3 dv;
		CalculateDesiredVelocity(agentID, vec3(target[0], target[1], target[2]), dv);
		
		Seek s(vec3(0,0,0));
		vec3 f = s.CalculateForce(AgentList[agentID], dv);

		for (int i=0; i<3; i++)
			force[i] = f[i];
	}

	//wrapper function for Behavior::CalculateTorque
	void EXPORT_API CalculateTorque(int agentID, float* target, float* torque)
	{
		vec3 dv;
		CalculateDesiredVelocity(agentID, vec3(target[0], target[1], target[2]), dv);
		
		Seek s(vec3(0,0,0));
		vec3 t = s.CalculateTorque(AgentList[agentID], dv);

		for (int i=0; i<3; i++)
			torque[i] = t[i];
	}


	//AStar DLL functions

	void EXPORT_API SetOccupied(float x, float z)
	{
		int i, j;
		ENV.posToCell(x, z, i, j);
		ENV.setOccupied(i, j, true);
	}

	bool EXPORT_API IsOccupied(float x, float z)
	{
		int i, j;
		ENV.posToCell(x, z, i, j);
		return ENV.isOccupied(i, j);
	}

	void EXPORT_API ClearObstacles()
	{
		ENV.clearObstacles();
	}

	void EXPORT_API SetPath(int agentID, float* startP, float* targetP)
	{
		vec3 s(startP[0], startP[1], startP[2]);
		vec3 t(targetP[0], targetP[1], targetP[2]);
		FPList[agentID].SetPath(ENV.findPath(s, t));
	}

	void EXPORT_API SaveMap(char* filename)
	{
		ENV.saveMap(filename);
	}

}