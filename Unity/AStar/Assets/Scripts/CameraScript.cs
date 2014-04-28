using UnityEngine;
using System.Collections;

public class CameraScript : MonoBehaviour {

	// Use this for initialization
	float w;
	float h;
	float v;
	public float tiltSpeed = 1.0f;
	public float panSpeed = 1.0f;
	public float dollySpeed = 8.0f;
	public Camera topCamera;
	Vector3 initPos;
	Quaternion initRot;
	
	void Start () {
	
	initPos = transform.position;
	initRot = transform.rotation;
	}
	
	// camera controller
	void LateUpdate () {


		 w = dollySpeed * Input.GetAxis("Mouse ScrollWheel");
		 transform.Translate(Vector3.forward * w );
		 if( topCamera.camera.enabled)
		 topCamera.transform.Translate(Vector3.forward * w );

		 
	 if(!Input.GetKey(KeyCode.LeftControl) && !Input.GetKey(KeyCode.LeftAlt))
	 {
		if(Input.GetMouseButton(0) && Input.GetKey(KeyCode.LeftAlt)){ 

		 	v = tiltSpeed * Input.GetAxis("Mouse Y");
		 
	
			transform.Rotate(Vector3.right * v );		
			}
			
				 
		if(Input.GetMouseButton(2)){ 

		 	v = panSpeed * Input.GetAxis("Mouse Y");
		 	h = panSpeed * Input.GetAxis("Mouse X");
			transform.Translate(Vector3.up * -v ); 
			transform.Translate(Vector3.right * -h ); 


			}
	 }

		if (Input.GetKeyDown("t")) // resets camera
		{
		 	transform.position = initPos ;
			 transform.rotation = initRot;
			 
			 camera.enabled = true;
	 		 topCamera.camera.enabled = false;
		}
	}
}
