using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class CloudParalexing : MonoBehaviour {
	public float ParallaxSpeed=0;
	public float speed;
//	protected GameObject _clone;
	protected Vector3 _movement;
	protected Vector3 _initialPosition;
	public float finalXPos;
	void Awake()
	{

	}
	void Start()
	{
		CallOnStart();

	}
	public void CallOnStart()
	{

		_initialPosition=transform.position	;
	}

	/// <summary>
	/// On FixedUpdate, we move the object and its clone
	/// </summary>
	protected virtual void Update()
	{

		_movement = Vector3.left * (ParallaxSpeed / 10) * speed * Time.deltaTime;

		//}
		// we move both objects
		gameObject.transform.Translate (_movement);


		if (gameObject.transform.position.x <= finalXPos) {
			gameObject.transform.position = _initialPosition;
			//Change third patch
		}
		//		}
	}

}
