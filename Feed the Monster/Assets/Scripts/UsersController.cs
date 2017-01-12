using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UsersController : MonoBehaviour
{
	public static UsersController Instance;


	public int CurrentUserId;





	// Use this for initialization
	void Awake () {
		Instance = this;
	}


	// Use this for initialization
	void Start () {
		CurrentUserId = 0;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
