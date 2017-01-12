using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UILoadingScreenController : MonoBehaviour {
	public Slider slider;

	bool mIsRunning;
	GameObject mPanelToShowOnEnd;
	public AudioClip LoadingSound;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (mIsRunning) {
			slider.value += (Time.deltaTime / 3);
		}
	}

	public void SetNextPanel(GameObject panel){
		mPanelToShowOnEnd = panel;
	}

	void OnEnable()
	{
		mIsRunning = true;
		Invoke ("End", 3);
		AudioController.Instance.PlaySound (LoadingSound);
	}

	void OnDisable()
	{
		mIsRunning = false;
		slider.value = 0;
	}

	void End()
	{
		UIController.Instance.ClosePopup (gameObject);
		//UIController.Instance.ShowPanel (mPanelToShowOnEnd);
	}
}
