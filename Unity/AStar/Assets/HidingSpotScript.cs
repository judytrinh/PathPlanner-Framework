using UnityEngine;
using System.Collections;

public class HidingSpotScript : MonoBehaviour {

	public bool occupied;

	// Use this for initialization
	void Start () {
		occupied = false;
	}

	public void SetOccupied(bool oc) {
		occupied = oc;
	}

	public bool IsOccupied() {
		return occupied;
	}
}
