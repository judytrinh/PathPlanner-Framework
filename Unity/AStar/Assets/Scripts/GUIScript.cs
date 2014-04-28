using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class GUIScript : MonoBehaviour 
{	
	Camera topCam;
	Camera perspCam;
	Camera marioCam;
	
	MapScript mscript;
	GlobalScript gscript;
	
	void Start()
	{
		topCam = GameObject.Find("Top Camera").GetComponent<Camera>();
		perspCam = GameObject.Find("Persp Camera").GetComponent<Camera>();
		marioCam = GameObject.Find("Mario Camera").GetComponent<Camera>();
		
		mscript = GameObject.Find("Global").GetComponent<MapScript>();
		gscript = GameObject.Find("Global").GetComponent<GlobalScript>();
	}
	
	void OnGUI() 
	{	
		
		if (GUI.Button(new Rect(40, 20, 100, 30), "Perspective"))
		{
			topCam.camera.enabled = false;
		 	perspCam.camera.enabled = true;
		 	marioCam.camera.enabled = false;
		}
		if (GUI.Button(new Rect(40, 60, 100, 30), "Mario Mode"))
		{
			topCam.camera.enabled = false;
		 	perspCam.camera.enabled = false;
		 	marioCam.camera.enabled = true;
		}
		if (GUI.Button(new Rect(40, 100, 100, 30), "Top View"))
		{
			topCam.camera.enabled = true;
		 	perspCam.camera.enabled = false;
		 	marioCam.camera.enabled = false;
		}
		
		if (GUI.Button(new Rect(Screen.width/2 - 100 - 15, 10, 100, 30), "Path Planner"))	
			gscript.hsmode = false;
		
		if (GUI.Button(new Rect(Screen.width/2 + 15, 10, 100, 30), "Hide & Seek"))
			gscript.hsmode = true;
		
		
		
		if (GUI.Button(new Rect(Screen.width*0.85f, 20, 100, 30), "Clear Map"))
			mscript.clearMap();
		
		if (GUI.Button(new Rect(Screen.width*0.85f, 60, 100, 30), "Save Map"))
			mscript.saveMap();
		
		if (GUI.Button(new Rect(Screen.width*0.85f, 100, 100, 30), "Load Map"))
			mscript.loadMap();
	}	
}