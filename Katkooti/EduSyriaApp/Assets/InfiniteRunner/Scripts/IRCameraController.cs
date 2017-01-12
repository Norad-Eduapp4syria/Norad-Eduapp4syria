using UnityEngine;
using System.Collections;

public class IRCameraController : MonoBehaviour {

	public IRPlayerController player;
	private bool goneUp = false;

	void OnEnable(){
		player.PlayerHit += OnPlayerHit;
	}
	void OnDisable(){
		player.PlayerHit -= OnPlayerHit;
	}

	void Update () {
		
			if (!goneUp && IRPlayerController.currentWorld == 1) {
				goneUp = true;
			}
			if (IRPlayerController.currentWorld == 0) {
				if (goneUp) {
					this.transform.position = Vector3.Lerp (this.transform.position, new Vector3 (this.transform.position.x, player.transform.position.y, this.transform.position.z), 2.8f * Time.deltaTime);
					Invoke ("SetGoneUpFalse", 2.5f);
				} else {
					this.transform.position = Vector3.Lerp (this.transform.position, new Vector3 (this.transform.position.x, -2.72f, this.transform.position.z), 1.75f * Time.deltaTime);
				}
			}
			if (IRPlayerController.currentWorld == 1) {
				
				this.transform.position = Vector3.Lerp (this.transform.position, new Vector3 (this.transform.position.x, 9.5f, this.transform.position.z), 1.5f * Time.deltaTime);
			}
			if (IRPlayerController.currentWorld == -1) {

				this.transform.position = Vector3.Lerp (this.transform.position, new Vector3 (this.transform.position.x, -11f, this.transform.position.z), 1.5f * Time.deltaTime);
			}

	}

	void OnPlayerHit(){
		if(!player.isChangingWorld)
			this.GetComponent<CameraShake> ().Shake ();
	}

	void SetGoneUpFalse(){
		goneUp=false;
	}
}
