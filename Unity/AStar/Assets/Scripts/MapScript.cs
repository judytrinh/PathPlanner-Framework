using UnityEngine;
using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

public class MapScript : MonoBehaviour 
{
	[DllImport("AStar")]
	public static extern void SetOccupied(float x, float z);
	
	[DllImport("AStar")]
	public static extern bool IsOccupied(float x, float z);
	
	[DllImport("AStar")]
	public static extern void ClearObstacles();
	
	[DllImport("AStar")]
	public static extern void SaveMap(string filename);
	
	public GameObject target;
	public GameObject mushroom;
	public GameObject bMushroom;
	public GameObject hidingspot;
	public Camera perspCamera;
	public Camera topCamera;
	public Camera marioCamera;
	public int Width;
	public int Length;
	
	public List<GameObject> HPList;	//list of hiding spots
	
	StreamReader reader;
	StreamWriter writer;
	int obstacleCount = 0;
	Ray ray;
	RaycastHit hitInfo;
	
	void Start () 
	{
		topCamera.camera.enabled = false;
	 	perspCamera.camera.enabled = true;
	 	marioCamera.camera.enabled = false;
		
		instantiateBoundary();
	}
	
	void Update () 
	{
		if (perspCamera.camera.enabled)
			ray = perspCamera.ScreenPointToRay(Input.mousePosition);
		else if (marioCamera.camera.enabled)
			ray = marioCamera.ScreenPointToRay(Input.mousePosition);
		else
			ray = topCamera.ScreenPointToRay(Input.mousePosition);
		
		//set hiding spot
		if (Input.GetKey(KeyCode.LeftShift) && Input.GetMouseButtonDown(0)) 
		{	
			if (Physics.Raycast(ray, out hitInfo, perspCamera.farClipPlane) && (hitInfo.collider.name == "Tile 1")
			    || (hitInfo.collider.name == "Tile 2"))
			{
				Vector3 tp = hitInfo.point;
				tp = new Vector3 (Mathf.Floor(tp.x)+0.5f, 0.5f, Mathf.Floor(tp.z) +0.5f);
				HPList.Add((GameObject)Instantiate(hidingspot, tp, Quaternion.identity));
			}                                                                        
		}
		//set occupied cell
		if (Input.GetKey(KeyCode.LeftAlt) && Input.GetMouseButton(0))
		{
			if (Physics.Raycast(ray, out hitInfo, perspCamera.farClipPlane) )//&& (hitInfo.collider.name == "Tile 1")
			   // || (hitInfo.collider.name == "Tile 2"))
			{
				Vector3 p = hitInfo.point;
				p = new Vector3 (Mathf.Floor(p.x)+0.5f, 1.2f, Mathf.Floor(p.z) +0.5f);
				
				if (Mathf.Abs(p.x) < 39 && Mathf.Abs(p.z) < 39 && !IsOccupied(p.x, p.z))
				{
					GameObject temp = (GameObject)Instantiate(mushroom, p, Quaternion.identity);
					temp.name = "Mushroom"+obstacleCount;
					SetOccupied(p.x, p.z);
					obstacleCount++;
				}
			}
		}
		//move target
		if (Input.GetKey(KeyCode.LeftControl) && Input.GetMouseButton(0)) 
		{		
			if (Physics.Raycast (ray, out hitInfo, perspCamera.farClipPlane) && (hitInfo.collider.name == "Tile 1" || hitInfo.collider.name == "Tile 2")) {
					
				Vector3 p = hitInfo.point;
				if (Mathf.Abs(p.x) < 39 && Mathf.Abs(p.z) < 39)
					target.transform.position = new Vector3 (p.x, 0.1f, p.z);
			}
		}
	}
	  
	void cellToPos(int i, int j, ref float x, ref float z)
	{
		int m_cellsize = 1;
		x = (i - 39.5f) * m_cellsize;
		z = (j - 39.5f) * m_cellsize;
	}
	
	public void loadMap()
	{
		clearMap();
		reader = new StreamReader("Assets/Maps/map.ini");
		string line;
		while ((line = reader.ReadLine()) != null)
		{
			string[] parts = line.Split(' ');	
			int i = Convert.ToInt32(parts[0]); 
			int j = Convert.ToInt32(parts[1]);
			
			float x = 0;
			float z = 0;
			cellToPos(i, j, ref x, ref z);
			Vector3 pos = new Vector3(x,1.2f,z);
			GameObject temp = (GameObject)Instantiate(mushroom, pos ,Quaternion.identity);
			temp.name = "Mushroom"+obstacleCount;
			obstacleCount++;
			SetOccupied(x, z);
		}
		reader.Close();
		
		reader = new StreamReader("Assets/Maps/hidingspots.ini");
		while ((line = reader.ReadLine()) != null)
		{
			string[] parts = line.Split(' ');
			float x = Convert.ToSingle(parts[0]);
			float z = Convert.ToSingle(parts[1]);
			
			Vector3 pos = new Vector3(x,0.5f,z);
			HPList.Add((GameObject)Instantiate(hidingspot, pos ,Quaternion.identity));
		}
		reader.Close();
	}
	
	public void saveMap()
	{
		File.Delete("Assets/Maps/map.ini");
		SaveMap("Assets/Maps/map.ini");
		
		writer = new StreamWriter("Assets/Maps/hidingspots.ini");
		for (int i=0; i<HPList.Count; i++)
		{
			Vector3 pos = HPList[i].transform.position;
			writer.WriteLine(pos.x + " " + pos.z); 
		}
		writer.Close();
	}
	
	public void clearMap()
	{
		for (int i=0; i<obstacleCount; i++)
			Destroy(GameObject.Find("Mushroom"+i));
		
		ClearObstacles();
		obstacleCount = 0;
		
		for (int i=0; i<HPList.Count; i++)
			Destroy(HPList[i]);

		BehaviorScript bs0 = GameObject.Find("Agent0").GetComponent<BehaviorScript>();
		BehaviorScript bs1 = GameObject.Find("Agent1").GetComponent<BehaviorScript>();
		bs0.target = GameObject.Find("Target");
		bs1.target = GameObject.Find("Target");
		HPList.Clear();
	}
	void instantiateBoundary()
	{
		Vector3 pos;
		float h = 1.2f;
		for (int i = -Width/2; i < Width/2; i++)
		{
			pos = new Vector3 (i, h, Length/2 );
			Instantiate(bMushroom, pos, Quaternion.identity);
			SetOccupied(pos.x, pos.z);
			
		 	pos= new Vector3 (i, h, -Length/2 );
		 	Instantiate (bMushroom, pos, Quaternion.identity);
		 	SetOccupied(pos.x, pos.z);
		}
		for(int j = -Length/2; j <= Length/2; j++)
		{
		 	pos= new Vector3 (Width/2 , h, j);
		 	Instantiate (bMushroom, pos, Quaternion.identity);
			SetOccupied(pos.x, pos.z);
		 	
		 	pos = new Vector3 (-Width/2 - 1, h, j);
		 	Instantiate (bMushroom, pos, Quaternion.identity);	
			SetOccupied(pos.x, pos.z);
		}
	}
}
