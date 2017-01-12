using UnityEngine;
using System.Collections;
 
 public class Move : MonoBehaviour 
{
	public AnimationCurve curveX ;
	public AnimationCurve curveY ;

	void Start()
	{
		curveX = new AnimationCurve(
			new Keyframe(  0f, -154),
			new Keyframe(0.5f, -98, 112, 112),
			new Keyframe(  1f, 0, -26, -26)
		);

		curveY = new AnimationCurve(
			new Keyframe(  0f, 0),
			new Keyframe(0.5f, -209, 34, 34),

			new Keyframe(  1f, 45, 90, 90)
		);



		curveX.preWrapMode = WrapMode.Default;
		curveX.postWrapMode = WrapMode.Default;

		curveY.preWrapMode = WrapMode.Default;
		curveY.postWrapMode = WrapMode.Default;

	}

	void Update()
	{
		transform.position = new Vector3(curveX.Evaluate(Time.time), curveY.Evaluate(Time.time), transform.position.z);
	}








	/*
	public GameObject plotPointObject;
	public int numberOfPoints= 100;
	public float animSpeed =1.0f;
	public float scaleInputRange = 2*Mathf.PI; // scale number from [0 to 99] to [0 to 2Pi]
	public float scaleResult = 1.0f;
	public bool animate = true;

	GameObject[] plotPoints;


	void Start () {
		/*
		if (plotPointObject == null) //if user did not fill in a game object to use for the plot points
			plotPointObject = GameObject.CreatePrimitive(PrimitiveType.Sphere); //create a sphere

		plotPoints = new GameObject[numberOfPoints]; //creat an array of 100 points.

		for (int i = 0; i < numberOfPoints; i++)
		{
			plotPoints[i] = (GameObject)GameObject.Instantiate(plotPointObject, new Vector3(i - (numberOfPoints/2), 0, 0), Quaternion.identity); //this specifies what object to create, where to place it and how to orient it
		}
		//we now have an array of 100 points- your should see them in the hierarchy when you hit play
		plotPointObject.SetActive(false); //hide the original

	}



	void Update()
	{

		for (int i = 0; i < numberOfPoints; i++)
		{
			float functionXvalue = i * scaleInputRange / numberOfPoints; // scale number from [0 to 99] to [0 to 2Pi]
			if (animate)
			{
				functionXvalue += Time.time * animSpeed;
			}
			plotPoints[i].transform.position = new Vector3(i - (numberOfPoints/2), ComputeFunction(functionXvalue) * scaleResult, 0);
		}

	}

	float ComputeFunction(float x)
	{
		return Mathf.Sin(x);
	}

*/




/*
	public float frequency = 1.0f; // in Hz
	public Vector3 PositionA = new Vector3(-160f, 0f, 0f);
	public Vector3 PositionB = new Vector3(160f, 0f, 0f);
	private float elapsedTime = 0.0f;


     // Use this for initialization
     void Start () 
     {
		PositionA = new Vector3(-160f,  200f, 0f);
		PositionB = new Vector3( 160f, -200f, 0f);
     }
     
     // Update is called once per frame
     void Update () 
     {
		elapsedTime += Time.deltaTime;
		float cosineValue = Mathf.Cos(2.0f * Mathf.PI * frequency * elapsedTime);
		transform.position = PositionA + (PositionB - PositionA) * 0.5f * (1 - cosineValue);
     }
*/

 }
