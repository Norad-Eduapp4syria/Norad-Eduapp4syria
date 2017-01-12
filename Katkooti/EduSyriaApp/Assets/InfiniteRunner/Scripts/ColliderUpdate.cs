using UnityEngine;
using System.Collections;

public class ColliderUpdate : MonoBehaviour {
	[Range(0,5f)]
	public float RefreshTime;


	private float time;
	void Start(){
		time = Time.time;

	}
	void UpdateCollider(){
		Destroy(gameObject.GetComponent<PolygonCollider2D>());
		PolygonCollider2D collider = new PolygonCollider2D ();
		this.gameObject.AddComponent<PolygonCollider2D>();
		time = Time.time;
	}
	
	// Update is called once per frame
	void Update () {
		if (Time.time - time > RefreshTime) {
			UpdateCollider ();

		}
		else {
		//	this.GetComponent<PolygonCollider2D>().isTrigger=true;

		}
	}
}
