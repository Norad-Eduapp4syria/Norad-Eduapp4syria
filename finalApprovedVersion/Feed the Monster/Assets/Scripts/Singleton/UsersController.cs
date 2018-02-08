using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UsersController : MonoBehaviour
{
	public static string LocalUserPrefix = "Local_";

	public Action OnLoadData;

	public static UsersController Instance = null;

	public static float saveEverySeconds = 10f;

	int currentProfileId = -1;
	float passedTime = 0;

	Dictionary<string, UserDataTO> usersData = new Dictionary<string, UserDataTO>();
	Dictionary<string, UserDataTO> dataToSave = new Dictionary<string, UserDataTO>();






	public UserDataTO userData() {
		return userData (currentProfileId);
	}

	public UserDataTO userData(int ProfileId) {
		string key = UsersController.LocalUserPrefix + ProfileId.ToString();
		if (!usersData.ContainsKey (key)) {
			loadData (key);
		}
		return usersData [key];
	}


	public void setUserData(UserDataTO userData) {

		if (usersData.ContainsKey (userData.UserId)) {
			usersData [userData.UserId] = userData;
		} else {
			usersData.Add (userData.UserId, userData);
		}
	}

	public void clearUserData() {
		setUserData(UserDataTO.create ("{}", userData().UserId));
		save (userData(), true);
	}

	public void clearAllUsersData() {

		for (int i = 0; i < 4; i++) {
			string key = UsersController.LocalUserPrefix + i.ToString();
			setUserData(UserDataTO.create ("{}", key));
			save (userData(), true);
		}
	}



	public int CurrentProfileId
	{
		set {
			currentProfileId = value;
			SaveStatConnector.Instance.ProfileId = currentProfileId;
		}
		get {
			if (currentProfileId == -1) {
				currentProfileId = SaveStatConnector.Instance.ProfileId;
			}
			return (currentProfileId == -1) ? 0 : currentProfileId;
		}
	}

	public Sprite CurrentProfileSprite
	{
		get {
			if (GameAssets.Instance != null) {
				return GameAssets.Instance.ProfileSprites [CurrentProfileId];
			} 
			return null;
		}
	}


	// Use this for initialization
	void Awake () {
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (gameObject);
			SingletonLoader.CheckSingleton();
		} else if (Instance != this) {
			Destroy (gameObject);
		}
	}

/*
	void Start () {
	}
*/	
	void Update () {
		passedTime += Time.deltaTime;

		if (passedTime >= UsersController.saveEverySeconds) {
			SaveAllData ();
		}
	}

	public void init()
	{
		loadData ("");
	}


	void loadData(string userId)
	{
		setUserData(SaveStatConnector.Instance.StartLoadLocal (userId));
	}

	void saveData (UserDataTO userData) {
		SaveStatConnector.Instance.StartSaveLocal (userData);
	}

	
	public void SaveAllData() {
		passedTime = 0;

		foreach (UserDataTO ud in dataToSave.Values) {
			saveData (ud);
		}
		dataToSave.Clear ();
	}

	
	public void save(UserDataTO userDataToSave, bool replace = false) {

		string userId = (string.IsNullOrEmpty(userDataToSave.UserId)) ? "guest" : userDataToSave.UserId;

		if (userDataToSave != null) {
			if (!dataToSave.ContainsKey (userId)) {
				dataToSave.Add (userId, userDataToSave);
			} else if (replace) {
				dataToSave[userId] = userDataToSave;
			}
		}
	}



}
