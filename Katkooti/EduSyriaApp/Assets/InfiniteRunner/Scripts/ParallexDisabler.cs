using UnityEngine;
using System.Collections;

public class ParallexDisabler : MonoBehaviour {

	// Use this for initialization
	public Parallax []parallexGameObjects;
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnCollisionEnter2D(Collision2D collision){
		if (collision.collider.gameObject.CompareTag ("Chicky")) {
			this.GetComponent<BoxCollider2D> ().enabled = false;
			foreach (Parallax p in parallexGameObjects) {
				p.DisableClone ();
				p.gameObject.SetActive (false);
			}
		}
	}
}
