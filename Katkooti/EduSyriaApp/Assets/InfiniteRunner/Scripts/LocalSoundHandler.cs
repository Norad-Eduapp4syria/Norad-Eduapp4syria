using UnityEngine;
using System.Collections;

public class LocalSoundHandler : MonoBehaviour {

	public AudioClip []clips;
	public AudioSource source;
	public IRPlayerController playerController;
	void Start(){
		playerController.CollectPowerUp += PlayLetterSound;
		playerController.PlayerHit += PlayerHurt;
		playerController.PlayerLaneChange += PlayerLaneChange;
	}
	void PlaySound(){
		
	}

	void Update(){
		PlaySound();
	}

	void PlayLetterSound(){
		//source.PlayOneShot (clips [0],0.8f);
	}
	public void PlaySlideSound(){
		source.PlayOneShot (clips [1],0.8f);
	}
	public void PlayerHurt(){
		source.PlayOneShot (clips [2],1.2f);
	}

	public void PlayerJump(){
		source.PlayOneShot (clips [4],0.8f);
	}
	public void PlayerLaneChange(){
		source.PlayOneShot (clips [3],0.4f);
	}
}
