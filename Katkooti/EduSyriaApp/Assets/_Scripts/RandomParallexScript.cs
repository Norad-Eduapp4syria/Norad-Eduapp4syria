using UnityEngine;
using System.Collections;
using System.Collections.Generic;
/// <summary>
/// Add this class to an object so it'll move in parallax based on the level's speed.
/// Note that this method duplicates the object
/// </summary>
public class RandomParallexScript : MonoBehaviour 
{
	public static RandomParallexScript instance;
	/// the relative speed of the object
	public float ParallaxSpeed=0;
	public float speed;
	protected GameObject _clone;
	protected Vector3 _movement;
	protected Vector3 _initialPosition;
	protected float _width1;
	protected float _width2;
	//public Transform parentObj;
	[SerializeField]
	public List<GameObject> randomParallexObjects;
	GameObject parallexObject1;
	GameObject parallexObject2;

	GameObject startingObject;
	GameObject MidObject;
	GameObject EndObject;
	/// <summary>
	/// On start, we store various variables and clone the object
	/// </summary>
	/// 
	 void Awake()
	{
		instance = this;
	}
	void Start()
	{
			CallOnStart();
		
	}
	public void CallOnStart()
	{


		parallexObject1 = randomParallexObjects[Random.Range(0,randomParallexObjects.Count)];
		parallexObject2 = randomParallexObjects[Random.Range(0,randomParallexObjects.Count)];
//
//
		_initialPosition=transform.position	;
		startingObject = (GameObject)Instantiate (parallexObject1, _initialPosition, Quaternion.identity);
		_width1 = startingObject.GetComponent<Renderer>().bounds.size.x;
		// we clone the object and position the clone at the end of the initial object
		MidObject = (GameObject)Instantiate(parallexObject2, new Vector3(startingObject.transform.position.x+_width1, startingObject.transform.position.y, startingObject.transform.position.z), startingObject.transform.rotation);
		_width2 = MidObject.GetComponent<Renderer>().bounds.size.x;

		EndObject = (GameObject)Instantiate(parallexObject1, new Vector3(MidObject.transform.position.x+_width2, MidObject.transform.position.y, MidObject.transform.position.z), MidObject.transform.rotation);



		// we remove the parallax component from the clone to prevent an infinite loop
//		RandomParallexScript parallaxComponent = _clone.GetComponent<RandomParallexScript>();
//		_clone.transform.SetParent (parentObj);
//		Destroy(parallaxComponent);	
//		if (bgcontroller.instance.GamePlayedOnce) {
//			for (int i = 0; i < bgcontroller.instance.clones.Length; i++) {
//				if (bgcontroller.instance.clones [i] == null) {
//					bgcontroller.instance.clones [i] = _clone;
//					return;
//
//				}
//			}
//		}





	}

	/// <summary>
	/// On FixedUpdate, we move the object and its clone
	/// </summary>
	protected virtual void Update()
	{

			_movement = Vector3.left * (ParallaxSpeed / 10) * speed * Time.deltaTime;

			//}
			// we move both objects
		startingObject.transform.Translate (_movement);
		MidObject.transform.Translate (_movement);
		EndObject.transform.Translate (_movement);
//			transform.Translate (_movement);

			// if the object has reached its left limit, we teleport both objects to the right
		if (MidObject.transform.position.x + _width2 < _initialPosition.x) {
			startingObject.transform.Translate (Vector3.right * (_width1+_width2));
			MidObject.transform.Translate (Vector3.right * (_width1+_width2));
			EndObject.transform.Translate (Vector3.right * (_width1+_width2));
			}

		if (startingObject.transform.position.x >= _initialPosition.x) {
			//Change third patch
		}
//		}
	}


}