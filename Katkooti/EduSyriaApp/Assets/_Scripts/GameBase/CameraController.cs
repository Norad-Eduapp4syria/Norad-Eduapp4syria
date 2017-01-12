using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour {



	public float ZoomInValue,ExtraZoomValue,Intensity;
	private Vector3 CamStartingPosition;
	private Camera cam;
	private Vector3 CurrentPannedCamera;
	private float startingOrtho;
	public enum CameraState
	{
		Normal,
		ZoomIn,
		ExtraZoomIn,
		LeftPan,
		RightPan
	}


	public CameraState CurrentCameraState = CameraState.Normal; 


	// Use this for initialization

	void Start () {
		CamStartingPosition = this.transform.position;
	//	PanLeft(2);

		cam = this.GetComponent<Camera> ();
		startingOrtho = cam.orthographicSize;
	}


	public void ZoomIn()
	{
		
		cam.orthographicSize = Mathf.Lerp (cam.orthographicSize, ZoomInValue, Intensity  * Time.deltaTime );
		SetCameraState (CameraState.ZoomIn);
	}

	public void ExtraZoomIn()
	{
		cam.orthographicSize = Mathf.Lerp (cam.orthographicSize, ExtraZoomValue, Intensity * Time.deltaTime);
		SetCameraState (CameraState.ExtraZoomIn);
	}

	public void PanLeft(float panningfactor)
	{
		CurrentPannedCamera = this.transform.position;
		CurrentPannedCamera = new Vector3 (CurrentPannedCamera.x-panningfactor, CurrentPannedCamera.y, CurrentPannedCamera.z);
		SetCameraState (CameraState.LeftPan);

	}

	public void PanRight(float panningfactor)
	{
		CurrentPannedCamera = this.transform.transform.position;
		CurrentPannedCamera = new Vector3 (CurrentPannedCamera.x+panningfactor, CurrentPannedCamera.y, CurrentPannedCamera.z);
		SetCameraState (CameraState.RightPan);
	}

	public void Normal()
	{
		cam.orthographicSize = Mathf.Lerp (cam.orthographicSize, startingOrtho, Intensity  * Time.deltaTime );
		Camera.main.transform.position = Vector3.Lerp (this.transform.transform.position,CamStartingPosition, Intensity * Time.deltaTime);
		SetCameraState(CameraState.Normal);
	}


	public void SetCameraState(CameraState state)
	{
		CurrentCameraState = state;
	}

	// Update is called once per frame
	void Update () {

		switch(CurrentCameraState)
		{
		case CameraState.Normal:
			Normal ();
			break;
		case CameraState.ZoomIn:
			ZoomIn ();
			break;
		case CameraState.ExtraZoomIn:
			ExtraZoomIn ();
			break;
		case CameraState.LeftPan:
			Camera.main.transform.position = Vector3.Lerp (this.transform.position,CurrentPannedCamera, (Intensity - 0.5f) * Time.deltaTime);
			break;
		case CameraState.RightPan:
			Camera.main.transform.position = Vector3.Lerp (this.transform.position,CurrentPannedCamera, (Intensity - 0.5f) * Time.deltaTime);
			break;

		}
	}
}
