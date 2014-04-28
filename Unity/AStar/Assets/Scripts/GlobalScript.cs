using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;

public class GlobalScript : MonoBehaviour 
{
	enum Behaviors {alignment, arrival, avoid, cohesion, departure, flee, flocking, followpath, leader, seek, separation, wander};
	
	//struct used to exchange agent data between script and DLL
	[StructLayout(LayoutKind.Sequential, Pack = 1)]
	public struct actorParameter
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public float[] gPos;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public float[] lVel;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public float[] aVel;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public float[] gOrient;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public float[] gITens;
		public float mass;
		public float agentID;
		public int behavior;
	}
	
	[DllImport("AStar")]
	public static extern void initialize(int numAgents); 
	
	[DllImport("AStar")]
	public static extern void transferActorData([MarshalAs(UnmanagedType.LPArray, SizeParamIndex=1)] 
	                                           actorParameter[] agents, int agentcount);
	
	
	public GameObject[] agents;
	public actorParameter[] agentData;
	public int numAgents;
	public bool hsmode = false;

	void Start () 
	{
		initialize(numAgents);
		
		agentData = new actorParameter[numAgents];
		for (int i=0; i<numAgents; i++)
		{
			agentData[i].gPos = new float[3];
			agentData[i].aVel = new float[3];
			agentData[i].lVel = new float[3];
			agentData[i].gOrient = new float[4];
			agentData[i].gITens = new float[4];
			agentData[i].agentID = i;
		}
	}
	
	//copy transform and rigidbody data into actorParameter struct
	public void updateAgentData(int index)
	{	
		for (int i=0; i<3; i++)
		{
			agentData[index].gPos[i] = agents[index].transform.position[i];
			agentData[index].lVel[i] = agents[index].rigidbody.velocity[i];
			agentData[index].aVel[i] = agents[index].rigidbody.angularVelocity[i];
		}
		for (int i=0; i<4; i++)
		{
			agentData[index].gOrient[i] = agents[index].rigidbody.rotation[i];
			agentData[index].gITens[i] = agents[index].rigidbody.inertiaTensorRotation[i];
		}
		agentData[index].mass = agents[index].rigidbody.mass;
		agentData[index].behavior = agents[index].GetComponent<BehaviorScript>().behavior;
	}
	
	//transfer all actor data from Unity to DLL 
	public void transferData()
	{
		for (int i=0; i<numAgents; i++)
			updateAgentData(i);
		
		transferActorData(agentData, numAgents);
	}
}
