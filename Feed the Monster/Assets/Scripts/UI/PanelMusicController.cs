using UnityEngine;
using System.Collections;

public class PanelMusicController : MonoBehaviour {

	public AudioClip music;

	[Range(0f, 1f)]
	public float volume = 0.7f;

	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable() {
		if (AudioController.Instance != null) {
			AudioController.Instance.ChangeMusic (music == null ? null : music, false, volume);
		}
	}
}
