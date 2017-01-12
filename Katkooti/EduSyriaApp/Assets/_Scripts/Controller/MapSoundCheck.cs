using UnityEngine;
using System.Collections;

public class MapSoundCheck : MonoBehaviour {

	private AudioSource _source;

	void Start(){
		_source = this.GetComponent<AudioSource> ();
	}

	void Update(){
		if (!MainUIManager.Instance.mapUIController.mapActive) {
			if(!_source.isPlaying)
				_source.Play();
		} else {
			if(_source.isPlaying)
			_source.Pause ();
		}
	}
}
