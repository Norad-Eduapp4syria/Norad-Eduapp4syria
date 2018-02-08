using UnityEngine;
using System.Collections;

public class UIGamePanelController : MonoBehaviour {


	void Awake() {

	}



	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable(){
		Screen.sleepTimeout = SleepTimeout.NeverSleep;

		if (GameAssets.Instance.ForceMonster != MonsterType.NONE) {
			addMonster ();
			GameAssets.Instance.ForceMonster = MonsterType.NONE;
		}

		if (GameplayController.Instance != null) {
//			GameplayController.Instance.CurrentLevelIndex = GameAssets.CurrentLevelIndex;
			GameplayController.Instance.LoadLevel ();

			UsersController.Instance.userData().setLastPlayingLevel (GameAssets.CurrentLevelIndex);
		}
	}

	void OnDisable()
	{
		Screen.sleepTimeout = SleepTimeout.SystemSetting;
		GameplayController.Instance.ClearGameplay ();
	}

	void addMonster()
	{
		Monster monster = null;
		Monster[] monsters = UsersController.Instance.userData().getCollectedMonsters;

		foreach (Monster m in monsters)
		{ 
			if (GameAssets.Instance.ForceMonster == m.MonsterType) {
				monster = m;
			}
		}

		if (monster == null) {
			return;
		}

		GameObject newMonster = Instantiate (monster.currentPlayGO, new Vector3 (), Quaternion.identity) as GameObject;

		newMonster.transform.parent = MonsterBar.Instance.Content;
		newMonster.GetComponent<MonsterPosition> ().setGamePosition ();

		newMonster.transform.localPosition += new Vector3 (0, 0, 0);

		newMonster.transform.localScale = new Vector3 (.8f, .8f, .8f);
		newMonster.AddComponent<MonsterSpritesController> ().monster = monster;


		newMonster.transform.parent = null;
		newMonster.gameObject.name = "monster";

		newMonster.transform.localScale = MonsterBar.Instance.transform.localScale;
		newMonster.transform.position = newMonster.GetComponent<MonsterPosition> ().GameScreen;
	}


}
