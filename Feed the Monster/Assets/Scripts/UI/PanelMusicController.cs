using UnityEngine;
using System.Collections;

public class PanelMusicController : MonoBehaviour {

	public AudioClip music;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable() {
		AudioController.Instance.ChangeMusic (music == null ? null : music);
	}
}
