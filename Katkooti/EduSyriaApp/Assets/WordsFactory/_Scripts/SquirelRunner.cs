using UnityEngine;
using System.Collections;

public class SquirelRunner : MonoBehaviour {

	public float force;
	public float SpeedLmit;
	Rigidbody2D rb;
	// Use this for initialization
	void Start () {
		rb = this.transform.GetComponent<Rigidbody2D> ();
	}
	
	void FixedUpdate () {



		rb.AddRelativeForce (new Vector2 (-1f,0f) * force * Time.deltaTime,ForceMode2D.Impulse);

		rb.velocity = Vector2.ClampMagnitude (rb.velocity, SpeedLmit);
	}

}
