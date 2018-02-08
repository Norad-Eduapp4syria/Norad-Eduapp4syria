using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MiniGameButton : MonoBehaviour {

	public MonsterType monsterType;

	Monster _monster;
	Button _button;

	void Awake() {
		_button = GetComponent<Button> ();
	}

	void Start () {
		_button.interactable = false;

		if (
			UsersController.Instance.userData ().HasMonster (monsterType) 
		) {
			Monster[] monsters = UsersController.Instance.userData ().getCollectedMonsters ;
			foreach (Monster monster in monsters) {
				if(monster.MonsterType == monsterType) {
					_monster = monster;
					break;
				}
			}
			if (_monster != null && _monster.IsReady) {
				_button.interactable = true;
			}
		}
	}
/*
	void Update () {

	}
*/
	public void onClick()
	{
		if(_monster != null) {
			GameAssets.Instance.DefaultMonster = _monster.MonsterType;
			GameAssets.Instance.AutoStartMiniGame = true;

			SceneController.Instance.LoadScene("MiniGamesScreen");
		}

	}

}
