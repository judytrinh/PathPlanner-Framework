using UnityEngine;
using System.Collections;

public class BulletScript : MonoBehaviour {
	GameObject player;
	Vector3 dir;
	float height;
	// Use this for initialization
	void Start () {
		player = GameObject.Find ("Player");
		dir = player.transform.forward;
		height = 1.0f;
		Invoke ("kill", 4);
	}

	// Update is called once per frame
	void Update () {
		Vector3 pos = gameObject.transform.position;
		Vector3 newPos = pos + (dir * 0.7f);
		newPos.y = height;
		gameObject.transform.position = newPos;
	}

	void kill() {
		Destroy(gameObject);
	}

	void OnCollisionEnter(Collision col) {
		Destroy (gameObject);
	}
}
