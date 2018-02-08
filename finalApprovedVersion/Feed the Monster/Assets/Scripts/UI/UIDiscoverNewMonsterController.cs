using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using System.Linq;
using System;

public class UIDiscoverNewMonsterController : MonoBehaviour {
	public struct NextPanelActionStruct
	{
		public GameObject gameObject;
		public int levelIndex;
	}

//	public Image MonsterNameText;
	public AudioClip MonsterDiscoveredSound;


//	public GameBackground _gameBackground;

	public GameObject FirstHolder;

//	List <GameObject> mAddedButtons = new List<GameObject>();

	GameObject mCurrentSelected;
	NextPanelActionStruct mNextPanelToShow;
	string mSelectedFriendName;




	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}


	void OnEnable()
	{
		Destroy (GameObject.Find ("monster"));

		if (GameAssets.Instance.NewMonster != null) {
			
			Monster friend = GameAssets.Instance.NewMonster;

			GameObject orig = friend.firstPlayGO;
			if (orig != null) {
				GameObject newMonsterGO = Instantiate (orig, new Vector3 (), Quaternion.identity) as GameObject;

				if(newMonsterGO != null) {
					newMonsterGO.name = "monster";
					newMonsterGO.transform.SetParent(FirstHolder.transform, false);

					newMonsterGO.GetComponent<MonsterPosition> ().setNewMonsterPosition ();

					Animator animController;
					animController = newMonsterGO.GetComponentInChildren<Animator> ();
					if (animController != null) {
						animController.SetInteger ("IdleState", 0);
						animController.SetInteger ("EmotionState", 0);
						animController.SetInteger ("EatState", 0);
					}

					newMonsterGO.transform.parent = null;

				}
			}

//			MonsterNameText.sprite = friend.Name;
			UsersController.Instance.userData().addFriendToCollection (friend.MonsterType);
			AudioController.Instance.PlaySound (MonsterDiscoveredSound);

			Analitics.TreckScreen ("New Monster " + friend.MonsterType.ToString()   + " Profile: " + UsersController.Instance.CurrentProfileId );

			GameAssets.Instance.NewMonster = null;
			GameAssets.Instance.NextScene = string.Empty;
		}
	}

	void OnDisable()
	{
		
	}

	public void OkClick()
	{
		string nextScene;
		if (string.IsNullOrEmpty (GameAssets.Instance.NextScene)) {
			nextScene = "MapScreen";
		} else {
			nextScene = GameAssets.Instance.NextScene;
		}
		SceneController.Instance.LoadScene(nextScene);
	}

	public void SetNextPanelToShow(GameObject panel, int levelIndex)
	{
		mNextPanelToShow.gameObject = panel;
		mNextPanelToShow.levelIndex = levelIndex;
	}
}
