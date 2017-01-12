using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class UIEvolveMonsterController : MonoBehaviour {
	public GameObject FriendButtonPrefab;
	public int NumOfMonstersToShow;

	List <GameObject> mAddedButtons = new List<GameObject>();

	string mSelectedFriendName;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
		List<Monster> playerMonsters = new List<Monster>( UserInfo.Instance.CollectedFriends);
		List<Monster> monstersToShow = new List<Monster> ();

		for (int i = 0; i < NumOfMonstersToShow; i++) {
			int rnd = Random.Range (0, playerMonsters.Count);
			monstersToShow.Add (playerMonsters [rnd]);
			playerMonsters.RemoveAt (rnd);
		}

		foreach (Monster friend in monstersToShow) {
			CreateButton (friend);
		}
	}

	void CreateButton(Monster friend)
	{
		GameObject newButton = GameObject.Instantiate (FriendButtonPrefab) as GameObject;
		newButton.name = friend.name;
		newButton.transform.SetParent (FriendButtonPrefab.transform.parent);
		newButton.transform.localScale = FriendButtonPrefab.transform.localScale;
//		newButton.GetComponent<Button> ().image.sprite = friend.Icon;
		newButton.SetActive (true);
		mAddedButtons.Add (newButton);
	}

	void OnDisable()
	{
		DeleteAllButtons ();
	}

	void DeleteAllButtons()
	{
		foreach (GameObject button in mAddedButtons) {
			Destroy (button);
		}
		mAddedButtons = new List<GameObject>();
	}

	public void SelectFriend(GameObject buttonSender)
	{
		mSelectedFriendName = buttonSender.name;
		ShowEvolveAnimation (buttonSender);
	}

	void ShowEvolveAnimation(GameObject buttonSender)
	{

	}

	public void OkClick()
	{
		//UserInfo.Instance.AddFriendToCollection (mSelectedFriendName);
	}
}
