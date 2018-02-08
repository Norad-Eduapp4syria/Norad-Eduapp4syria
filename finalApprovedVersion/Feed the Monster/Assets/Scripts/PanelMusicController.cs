using UnityEngine;
using System.Collections;

public class PanelMusicController : MonoBehaviour {

	public AudioClip music;

	[Range(0f, 1f)]
	public float volume = 0.7f;

	[Range(0f, 1f)]
	public float startDelay = 0f;


/*
	void Start () {
	}
	
	void Update () {
	
	}
*/
	void OnEnable() {
		if (startDelay == 0) {
			StartMusic ();
		} else {
			Invoke ("StartMusic", startDelay);
		}
	}

	void StartMusic()
	{
		if (AudioController.Instance != null) {
			AudioController.Instance.ChangeMusic (music == null ? null : music, false, volume);
		}
	}
}
