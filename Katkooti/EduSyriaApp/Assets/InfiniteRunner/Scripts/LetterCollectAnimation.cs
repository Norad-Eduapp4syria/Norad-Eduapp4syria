using UnityEngine;
using System.Collections;

public class LetterCollectAnimation : MonoBehaviour {

	// Use this for initialization

	public GameObject letterCollection;
	public string InstatateOnTag;
	public int trailCount;
	public float delayTime;

	void OnTriggerEnter2D(Collider2D col){
		if (col.gameObject.CompareTag (InstatateOnTag)) {
			StartCoroutine ("SpawnStarTrail");
		}
	}

	IEnumerator SpawnStarTrail(){
		for (int i = 1; i <= trailCount; i++) {
			yield return new WaitForSeconds (delayTime);
			Instantiate (letterCollection, this.transform.position, Quaternion.identity);
		}
	}


}
