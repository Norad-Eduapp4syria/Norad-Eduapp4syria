using UnityEngine;
using System.Collections;

public class LetterChunkMover : MonoBehaviour {

	private Rigidbody2D rb;
	public float force;
	public float SpeedLmit;
	// Use this for initialization
	void Start () {
		rb = GetComponent<Rigidbody2D> ();
	}
	
	void FixedUpdate () {

		//Debug.Log (rb.velocity.magnitude);

		rb.AddRelativeForce (new Vector2 (1f,0f) * force * Time.deltaTime,ForceMode2D.Impulse);

		rb.velocity = Vector2.ClampMagnitude (rb.velocity, SpeedLmit);
	}
}
