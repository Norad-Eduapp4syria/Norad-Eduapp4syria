using UnityEngine;
using System.Collections;

public class UICircularParticleSystem : MonoBehaviour {

	public UIParticle particle;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		if (Random.value < 0.15f)
			(Instantiate (particle.gameObject, new Vector3 (0, 0, 0), Quaternion.identity) as GameObject).transform.SetParent(transform);
	}
		
}
