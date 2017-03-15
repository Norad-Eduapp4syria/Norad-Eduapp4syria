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

	List <GameObject> mAddedButtons = new List<GameObject>();

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
/*
		if (_gameBackground != null && GameBackgroundController.Instance) {
			GameBackgroundController.Instance.Load (_gameBackground);
		}
*/
		Destroy (GameObject.Find ("monster"));

		if (GameplayController.Instance.CurrentLevel.CollectableMonster != null) {
			
			Monster friend = GameplayController.Instance.CurrentLevel.CollectableMonster;

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
			UserInfo.Instance.AddFriendToCollection (friend);
			AudioController.Instance.PlaySound (MonsterDiscoveredSound);

			Analitics.Instance.treckScreen ("New Monster " + friend.MonsterType.ToString()   + " Profile: " + UsersController.Instance.CurrentProfileId );
		}
	}

	void OnDisable()
	{
		
	}

	public void OkClick()
	{
		GameplayController.Instance.ReaplaceBackground_SelectMonster = false;
		if (mNextPanelToShow.gameObject != null) {
			if (mNextPanelToShow.gameObject == UIController.Instance.GamePanel) {
				UIController.Instance.GoToLevel (mNextPanelToShow.levelIndex);
			} else {
				UIController.Instance.ShowPanel (mNextPanelToShow.gameObject);
			}
		} else {
			UIController.Instance.ShowPanel (UIController.Instance.MapPanel);
		}

		mNextPanelToShow.gameObject = null;
	}

	public void SetNextPanelToShow(GameObject panel, int levelIndex)
	{
		mNextPanelToShow.gameObject = panel;
		mNextPanelToShow.levelIndex = levelIndex;
	}
}
