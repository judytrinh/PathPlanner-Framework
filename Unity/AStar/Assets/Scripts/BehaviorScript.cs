using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

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

	GameObject seekTarget; // the big red one
	bool occupying;
	bool seen;

	void Start () 
	{
		gscript = GameObject.Find("Global").GetComponent<GlobalScript>(); 
		mscript = GameObject.Find("Global").GetComponent<MapScript>();
		idleAnimation = "look";
		
		result = new float[3];
		targetPos = new float[3];
		startPos = new float[3];
		oldTargetPos = new Vector3(0,0,0);

		
		seekTarget = GameObject.Find("Target");

		target = seekTarget;
		occupying = false;
		seen = false;
		//GameObject hidingSpot = GameObject.Find("HidingSpot(Clone)");
		//if (hidingSpot != null) {
		//	target = hidingSpot;
		//}

		player = GameObject.Find("Player");
		
		behavior = (int)Behaviors.followpath;

		InvokeRepeating ("moveTargetAround", 1, 1);
	}
	
	void FixedUpdate () 
	{	
		behavior = (int)Behaviors.followpath;
		//target = GameObject.Find("Target");
		if (seen) {
			SeekClosestSpot();
			if (target.transform.position != oldTargetPos)
				computePath();
		}
		else {
			target = seekTarget;
		}
		//GameObject hidingSpot = GameObject.Find("HidingSpot(Clone)");
		//if (hidingSpot != null) {
		//	target = hidingSpot;
		//}
		
		
		for (int i=0; i<3; i++)
			targetPos[i] = target.transform.position[i];
		
		gscript.transferData();
	
		CalculateForce(agentID, targetPos, result);
		rigidbody.AddForce(result[0], result[1], result[2]);
		
		CalculateTorque(agentID, targetPos, result);
		rigidbody.AddTorque(result[0], result[1], result[2]); 
		
		oldTargetPos = target.transform.position;
	}

	void moveTargetAround() {
		seekTarget.transform.position = new Vector3(UnityEngine.Random.Range(-39,39),0,UnityEngine.Random.Range(-39,39));
		if (target.transform.position != oldTargetPos)
			computePath();
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

	public void SetSeen(bool se) {
		seen = se;
	}

	public bool WasSeen() {
		return seen;
	}

	// seeks closest hiding spot. return the closest hiding spot.
	public GameObject SeekClosestSpot() {
		List<GameObject> spots = mscript.HPList;
		// If there are no hiding spots, do nuthin
		if (spots.Count == 0) return null;
		if (occupying) return null;

		// otherwise calculate the closest
		GameObject closestUnoccupied = null;
		float closestUnoccupiedDist = Mathf.Infinity;
		for (int i = 0; i < spots.Count; i++) {
			float dist = (gameObject.transform.position - spots[i].transform.position).magnitude;
			if (dist < closestUnoccupiedDist && !spots[i].GetComponent<HidingSpotScript>().IsOccupied()) {
				closestUnoccupied = spots[i];
				closestUnoccupiedDist = dist;
			}
		}
		if (closestUnoccupied != null) target = closestUnoccupied;
		else if (!occupying) target = seekTarget;
		//Debug.Log (closestUnoccupiedDist);
		if (closestUnoccupiedDist < 1.0f) {
			closestUnoccupied.GetComponent<HidingSpotScript>().SetOccupied(true);
			occupying = true;
		}
		//Debug.Log (closestUnoccupied.GetComponent<HidingSpotScript>().IsOccupied());
		return closestUnoccupied;
	}
}