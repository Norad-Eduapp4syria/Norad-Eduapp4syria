using UnityEngine;
using System.Collections;

public class templetter : MonoBehaviour {

	public float force;
	public float SpeedLmit;
	private Rigidbody2D rb;


	// Use this for initialization
	void Start () {
		rb = GetComponent<Rigidbody2D> ();
	}
	
	// Update is called once per frame
	void FixedUpdate () {
	     
//		Debug.Log (rb.velocity.magnitude);
//		if (rb.velocity.magnitude >= SpeedLmit) {
//			//rb.velocity = new Vector2 (rb.velocity.x - 0.5f, rb.velocity.y - 0.5f);
//			rb.AddRelativeForce (new Vector2 (-1f,0f) * force * Time.deltaTime,ForceMode2D.Impulse);
//		}




//		rb.AddRelativeForce (new Vector2 (1f,0f) * force * Time.deltaTime,ForceMode2D.Impulse);
//
//		rb.velocity = Vector2.ClampMagnitude (rb.velocity, SpeedLmit);
	}
}
