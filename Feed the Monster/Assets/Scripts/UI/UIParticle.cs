using UnityEngine;
using System.Collections;

public class UIParticle : MonoBehaviour {

	private Vector3 direction;
	float speed = 0;
	private float timer;
	// Use this for initialization
	void Start () {
		//direction = new Vector2 ( RandomRangeFloat(2), RandomRangeFloat(2));
		speed = RandomRangeFloat(4, 8);
		transform.rotation = Quaternion.AngleAxis (RandomRangeFloat (-180, 180), Vector3.forward);
		float scale = RandomRangeFloat (.5f, .9f);
		transform.localScale = new Vector3(scale, scale,scale);
	}
	
	// Update is called once per frame
	void Update () {
		timer += Time.deltaTime * speed;
		this.transform.position += this.transform.right  * speed;
		if (timer > 20)
			Destroy (gameObject);
	}

	float RandomRangeFloat(float range){
		return (Random.value * range) - range;
	}

	float RandomRangeFloat(float min, float max){
		return (Random.value * (max-min)) + min;
	}

}
