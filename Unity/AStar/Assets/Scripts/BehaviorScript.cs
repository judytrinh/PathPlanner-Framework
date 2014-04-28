using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;

public class BehaviorScript : MonoBehaviour 
{
	enum Behaviors {alignment, arrival, avoid, cohesion, departure, flee, flocking, followpath, leader, seek, separation, wander};
	
	[DllImport("AStar")]
	public static extern void CalculateForce(int agentID, float[] target, float[] force);
	
	[DllImport("AStar")]
	public static extern void CalculateTorque(int agentID, float[] target, float[] torque);
	
	[DllImport("AStar")]
	public static extern void SetPath(int agentID, float[] startP, float[] targetP);
	
	public GameObject target; 
	public GameObject player;
	public int agentID;
	public int behavior;
	
	bool idleSet = false;
	string idleAnimation;
	
	GlobalScript gscript;
	MapScript mscript;
	
	float[] result;		
	float[] targetPos;		
	float[] startPos;
	
	Vector3 oldTargetPos;

	void Start () 
	{
		gscript = GameObject.Find("Global").GetComponent<GlobalScript>(); 
		mscript = GameObject.Find("Global").GetComponent<MapScript>();
		idleAnimation = "look";
		
		result = new float[3];
		targetPos = new float[3];
		startPos = new float[3];
		oldTargetPos = new Vector3(0,0,0);
		
		target = GameObject.Find("Target");
		player = GameObject.Find("Player");
		
		behavior = (int)Behaviors.followpath;
		
	}
	
	void FixedUpdate () 
	{	
		behavior = (int)Behaviors.followpath;
		target = GameObject.Find("Target");
		if (target.transform.position != oldTargetPos)
			computePath();
		
		for (int i=0; i<3; i++)
			targetPos[i] = target.transform.position[i];
		
		gscript.transferData();
	
		CalculateForce(agentID, targetPos, result);
		rigidbody.AddForce(result[0], result[1], result[2]);
		
		CalculateTorque(agentID, targetPos, result);
		rigidbody.AddTorque(result[0], result[1], result[2]); 
		
		oldTargetPos = target.transform.position;
	}
	
	void Update()
	{
		float vel = rigidbody.velocity.magnitude;
		ParticleEmitter pe = gameObject.GetComponentInChildren<ParticleEmitter>();
		
		if (vel < 0.1)
		{
			pe.emit = false;	
			if (!idleSet)
			{
				idleSet = true;
				int r = UnityEngine.Random.Range(1,6);
				if (r==1)
					idleAnimation = "look";
				if (r==2)
					idleAnimation = "kick";
				if (r==3)
					idleAnimation = "handstand";
				if (r==4)
					idleAnimation = "dance";
				if (r==5)
					idleAnimation = "jump";
			}
			animation.CrossFade(idleAnimation);
		}
		if (vel > 0.1 && vel < 2)
		{
			pe.emit = true;
			pe.maxEmission = 10;
			animation.CrossFade("walk");
			idleSet = false;
			
			gameObject.GetComponentInChildren<ParticleEmitter>().emit = true;
			gameObject.GetComponentInChildren<ParticleEmitter>().maxEmission = 10;
			
		}
		if (vel >= 2)
		{
			pe.emit = true;
			pe.maxEmission = 20;
			animation["run"].speed = 0.8f;
			animation.CrossFade("run");
			idleSet = false;
			
			
			gameObject.GetComponentInChildren<ParticleEmitter>().emit = true;
			gameObject.GetComponentInChildren<ParticleEmitter>().maxEmission = 20;
			
		}
	}
	public void computePath()
	{
		for (int i=0; i<3; i++)
		{
			targetPos[i] = target.transform.position[i];
			startPos[i] = transform.position[i];
		}
		SetPath(agentID, startPos, targetPos);
	}
	
}