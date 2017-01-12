using UnityEngine;
using System.Collections;

public class ShadowFolow : MonoBehaviour {

	// Use this for initialization
	public IRPlayerController player;
	private SpriteRenderer renderer;
	void Start(){
		renderer = this.GetComponent<SpriteRenderer> ();
	}
	void Update () {
		
		if (IRPlayerController.currentWorld == 0) {
			renderer.enabled = true;
		} else {
			renderer.enabled = false;
		}

		if (this.gameObject.activeInHierarchy) {
			this.transform.position = new Vector3 (player.transform.position.x, this.transform.position.y, this.transform.position.z);
		}
	}
}
