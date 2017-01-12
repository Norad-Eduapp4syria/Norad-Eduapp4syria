using UnityEngine;
using System.Collections;

public class SelfDestroy : MonoBehaviour {

	public float lifeSpan;
	public bool AutoDestroy;
	void Start () {
		if (AutoDestroy)
			StartCoroutine (DistroyCoroutine ());
	}
	IEnumerator DistroyCoroutine(){
		yield return new WaitForSeconds (lifeSpan);
		Destroy (this.gameObject);
	}
	public void DestroyImidiately(){
		Destroy (this.gameObject);
	}

	public void DestroyAfter(float time){
		Destroy (this.gameObject, time);
	}
}
