using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class SoundManager : Singleton<SoundManager> {
	public AudioSource _SFXSource;
	public AudioSource _dialgueSource;
	public SoundAudioBase [] GameSounds;

	private AudioSource _source;


	[Header("Tutorial Dialogues")]
	public AudioClip[] TutorialDialogue;
	int TD=0;

	[Header("Tiger Dialogues")]
	public AudioClip[] TigerCaveDialogue;
	int TCD=0;

	[Header("Monkey Hub Dialogues")]
	public AudioClip[] MonkeysHubDialogue;
	int MHD=0;

	[Header("Jungle Court Dialogues")]
	public AudioClip[] JungleCourtDialogue;
	int JCD=0;

	void Start(){
		_source = this.GetComponent<AudioSource> ();
	}
	public bool Contain(string name){
		foreach (SoundAudioBase sound in GameSounds) {
			if (sound.name == name) {
				return true;
			}
		}
		return false;
	}
	public void Stop(){
		
	}
	public void PlaySoundOneShot(string name){
		if (Contain (name)) {
			_SFXSource.PlayOneShot (getAudioByName (name));
		}
	}
	public float getSoundLengthByName(string name){
		foreach (SoundAudioBase sound in GameSounds) {
			if (sound.name == name) {
				return sound.clip.length;
			}
		}
		return 0;
	}
	public AudioClip getAudioByName(string name){
		foreach (SoundAudioBase sound in GameSounds) {
			if (sound.name == name) {
				return sound.clip;
			}
		}
		return null;
	}

	public float PlayTutorialDialogue(){
		float time = TutorialDialogue [TD].length;
		_dialgueSource.PlayOneShot (TutorialDialogue [TD]);
		TD++;
		TD = TD % TutorialDialogue.Length;
		return time;
	}
	public void InrementTutorialSound(){
		TD++;
	}
	public void InrementJungleCourtSound(){
		JCD++;
	}
	public void InrementMonkeyHubSound(){
		MHD++;
	}

	public void IncrementTigerCaveDialogueSound(){
		TCD++;
	}

	public float PlayMonkeysHubDialogue(){
		float time = MonkeysHubDialogue [MHD].length;
		_dialgueSource.PlayOneShot (MonkeysHubDialogue [MHD]);
		MHD++;
		MHD = MHD % MonkeysHubDialogue.Length;
		return time;
	}
	public float PlayTigerCaveDialogue(){
		float time = TigerCaveDialogue [TCD].length;
		_dialgueSource.PlayOneShot (TigerCaveDialogue [TCD]);
		TCD++;
		TCD = TCD % TigerCaveDialogue.Length;
		return time;
	}
	public float PlayJungleCourtDialogue(){
		float time = JungleCourtDialogue [JCD].length;
		_dialgueSource.PlayOneShot (JungleCourtDialogue [JCD]);
		JCD++;
		JCD = JCD % JungleCourtDialogue.Length;
		return time;
	}


}
