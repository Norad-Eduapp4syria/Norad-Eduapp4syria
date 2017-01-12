using UnityEngine;
using System.Collections;

public class PondAnimationController : MonoBehaviour {

	// Use this for initialization
	public GameObject []Variations;
	public float delay;
	void Start () {
		StartCoroutine ("StartAnimation");
	}
	IEnumerator StartAnimation(){
		foreach (GameObject g in Variations) {
			g.SetActive (true);
			yield return new WaitForSeconds (delay);
		}
	}
	// Update is called once per frame
	void Update () {
	
	}
}
