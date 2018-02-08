using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SaveStatConnector : MonoBehaviour {

	public static SaveStatConnector Instance = null;

	void Awake()
	{
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
	void OnEnable() {

	}
	void Update () {
		
	}
*/


	public void init() {
		bool m = MusicState;
		bool s = SoundState;
		isInited = true;
	}

	void createUserData(string userId, WWW www)
	{
		try {

			if(www.error != null)
			{
				Debug.Log ("SaveStatConnector.createUserData - Fail\n" + www.error );
			}
			else 
			{
				string json = www.text;

				UserDataTO userData = UserDataTO.create(json, userId);
				if(UsersController.Instance.userData() == null || UsersController.Instance.userData().UserId.Equals(userData.UserId)) {
					UsersController.Instance.setUserData(userData);
					LogConntroller.Instance.Log("SaveStatConnector.createUserData - Done");
				}
			}
		} catch (System.Exception e) {
			LogConntroller.Instance.Log("SaveStatConnector.createUserData - Fail\n" + e.Message + "\n" + e.StackTrace + "\n" + www.text);
		}
		if (UsersController.Instance.OnLoadData != null) {
			UsersController.Instance.OnLoadData ();
		}
	}

	#region Local State


	string LocalStateKey(string userId)
	{
		return Keys.LocalState.ToString() + "_" + userId;
	}

	public void StartSaveLocal(UserDataTO userData)
	{
		string json = userData.toJson ();
		Debug.Log ("Save Data: \n" + json);
		PlayerPrefs.SetString (LocalStateKey(userData.UserId), json);
	}

	public UserDataTO StartLoadLocal(string userId)
	{
		return UserDataTO.create(PlayerPrefs.GetString (LocalStateKey(userId) , "{}"), userId);
	}
	#endregion

	#region basic state
	bool isInited = false;
	bool musicState;
	bool soundState;

	public bool MusicState
	{
		get {
			if (!isInited) {
				musicState = (PlayerPrefs.GetInt (Keys.MusicEnable.ToString (), 1) == 1);
			}
			return musicState;
		}
		set {
			musicState = value;
			PlayerPrefs.SetInt (Keys.MusicEnable.ToString(), value ? 1 : 0);
		}
	}

	public bool SoundState
	{
		get {
			if (!isInited) {
				soundState = (PlayerPrefs.GetInt (Keys.SoundEnable.ToString (), 1) == 1);
			}
			return soundState;
		}
		set {
			soundState = value;
			PlayerPrefs.SetInt (Keys.SoundEnable.ToString(), value ? 1 : 0);
		}
	}

	public string UserName
	{
		get {
			return PlayerPrefs.GetString (Keys.UserName.ToString (), "");
		}
		set {
			PlayerPrefs.SetString(Keys.UserName.ToString(), value);
		}
	}

	public string UserPassword
	{
		get {
			return PlayerPrefs.GetString (Keys.UserPassword.ToString (), "");
		}
		set { 
			PlayerPrefs.SetString(Keys.UserPassword.ToString(), value);
		}
	}



	public int ProfileId
	{
		get {
			return PlayerPrefs.GetInt (Keys.LastProfileId.ToString (), -1);
		}
		set { 
			PlayerPrefs.SetInt(Keys.LastProfileId.ToString(), value);
		}
	}

	#endregion




	public int DataVersion
	{
		get {
			return  PlayerPrefs.GetInt (Keys.DataVersion.ToString (), 0);
		}
		set {
			PlayerPrefs.SetInt (Keys.DataVersion.ToString (), value);
		}
	}



}

public enum Keys
{
	DataVersion,
	LocalState,
	UserName,
	UserPassword,
	MusicEnable,
	SoundEnable,
	LastProfileId,
}

