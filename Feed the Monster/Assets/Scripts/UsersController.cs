using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UsersController : MonoBehaviour
{
	public static UsersController Instance;


	public Sprite[] ProfileSprites;


	int currentProfileId = -1;


	public int CurrentProfileId
	{
		set {
			currentProfileId = value;
			UserInfo.Instance.SetLastProfileId (currentProfileId);
		}
		get {
			if (currentProfileId == -1) {
				currentProfileId = UserInfo.Instance.GetLastProfileId ();
			}
			return currentProfileId;
		}
	}

	public Sprite CurrentProfileSprite
	{
		get {
			return ProfileSprites[CurrentProfileId];
		}
	}




	// Use this for initialization
	void Awake () {
		Instance = this;
	}


	// Use this for initialization
	void Start () {
		if (CurrentProfileId > 0) {
		}
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
