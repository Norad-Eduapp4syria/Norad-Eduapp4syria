using UnityEngine;
using UnityEngine.Events;
using System.Collections;

public class VideoEndController : MonoBehaviour {

	public UnityEvent VideoEnded;
	public string mNextScene;

	float elapsedTime;
	bool videoPlaying;



	// Use this for initialization
	void Start () {

	}

	void OnEnable() {
		Screen.sleepTimeout = SleepTimeout.NeverSleep;

		elapsedTime = 0;
		videoPlaying = true;
	}

	void OnDisable() {
		Screen.sleepTimeout = SleepTimeout.SystemSetting;
	}

	// Update is called once per frame
	void Update () {
		if (videoPlaying) {
			elapsedTime += Time.deltaTime;
		}
		#if !UNITY_WEBPLAYER && !UNITY_WEBGL && !UNITY_WP8 && !UNITY_WP8_1

		if(elapsedTime > 10 && GetComponent<MediaPlayerCtrl>().GetCurrentState() != MediaPlayerCtrl.MEDIAPLAYER_STATE.PLAYING && videoPlaying)
		{
			if (VideoEnded != null) {
				VideoEnded.Invoke ();
			}
			videoPlaying = false;
		}
		#endif
	}

	public void loadNextScene () {
		SceneController.Instance.LoadScene(mNextScene);
	}





}
