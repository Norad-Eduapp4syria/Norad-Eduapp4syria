using UnityEngine;
using System.Collections;

public class DestroyAfter : MonoBehaviour {
	public float After = 2.5f;
	// Use this for initialization
	void Start () {
	
	}

	float timer = 0;
	// Update is called once per frame
	void Update () {
		timer += Time.deltaTime;
		if (timer >= After)
			Destroy (gameObject);
	}
}
