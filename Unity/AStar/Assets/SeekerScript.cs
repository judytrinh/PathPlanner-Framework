using UnityEngine;
using System.Collections;

public class SeekerScript : MonoBehaviour {

	//-----------------------------------------------------------------------------------
	// This script defines seeking conditions/line of sight for the main player Lenguino.
	//-----------------------------------------------------------------------------------
	GameObject[] agents;
	float lineOfSightLength;
	public LayerMask agentLayer;

	// Use this for initialization
	void Start () {
		agents = GameObject.Find("Global").GetComponent<GlobalScript>().agents;
		lineOfSightLength = 7.5f;
	}
	
	// Update is called once per frame
	void Update () {
		DetectAgent();
	}

	// detect agent when in line of sight
	public GameObject DetectAgent() {
		Debug.Log (gameObject.transform.forward);
		//foreach (GameObject a in agents) {
		Vector3 start = gameObject.transform.position;
		start.y += 1.0f;
		Vector3 dir = gameObject.transform.forward;
		Debug.DrawRay(start, dir * lineOfSightLength, Color.red);
		RaycastHit hit;
		if (Physics.Raycast(start, dir, out hit, lineOfSightLength, agentLayer)) {
			print("There is something in front of the object!");
			return hit.rigidbody.gameObject;
		}
			//Debug.DrawLine(gameObject.transform.position, a.transform.position, Color.red);

		//}
		return null;
	}
}
