using UnityEngine;
using System.Collections;

public class MapUIController : MonoBehaviour {

	[SerializeField]
	private MapController mapController;
	// Use this for initialization


	public bool mapActive = false; 
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void SwitchToNext()
	{
		mapController.NextPosition ();
	}

	public void Activate()
	{
		mapActive = true;
		Time.timeScale = 0;
		mapController.gameObject.SetActive (true);
	}
	public void DeActivate()
	{
		mapActive = false;
		Time.timeScale = 1;
		mapController.gameObject.SetActive (false);
	}
	 
	public void PopMap()
	{
		mapActive = true;
		Time.timeScale = 0;
		mapController.gameObject.SetActive (true);

	}

	public void UnPopMap(){
		mapActive = false;
		Time.timeScale = 1;
		mapController.gameObject.SetActive (false);
	}

	public void OnPressedRedButton(string SceneName)
	{
		if (!SceneName.Equals (Application.loadedLevelName)) {
			Application.LoadLevel ("Intro");
			GameManager.Instance.DestroyAllControllers ();
			GameManager.Instance.StartCoroutine (GameManager.Instance.PlayState (SceneName));
			UnPopMap ();
		} else {
			DeActivate ();
		}
	}
	//public void LoadNext
}
