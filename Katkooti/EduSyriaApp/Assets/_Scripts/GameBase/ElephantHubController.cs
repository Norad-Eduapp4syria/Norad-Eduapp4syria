using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class ElephantHubConroller : MonoBehaviour {

	private KatkootiController Player;
	private ElephantController Elephant;

	//public MonkeyController[] Monkeys;

	public enum ElephantState{
		NONE,
		SCENE_INTRO,
		//		PARTY_FURNITURE,
		FINISH
	}
	private ElephantState currentElephantstate = ElephantState.NONE;
	public ElephantState getCurrentState(){
		return currentElephantstate;
	}


	public ElephantHubConroller(){
		GameManager.GameInitialize += OnGameInitialized;

	}

	~ElephantHubConroller(){
		GameManager.GameInitialize -= OnGameInitialized;
	}

	void OnGameInitialized(){


		if (GameManager.Instance.getCurrentGameState () + 1 >= GameManager.GameSate.ELEPHANT_HUB && Application.loadedLevelName == "ElephantHub") {
			
			//MainUIManager.Instance.hudController.gameObject.SetActive
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			MainUIManager.Instance.hudController.EnableUIMapGlow ();
			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			Player = GameObject.FindObjectOfType<KatkootiController> ();
			Elephant = GameObject.FindObjectOfType<ElephantController> ();
			PlayCurrentState ();
		} else if(Application.loadedLevelName == "ElephantHub") {
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			MainUIManager.Instance.hudController.EnableUIMapGlow ();
			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			Player = GameObject.FindObjectOfType<KatkootiController> ();
			Elephant = GameObject.FindObjectOfType<ElephantController> ();
			GameManager.Instance.StartCoroutine(GameManager.Instance.elephantcontroller.NotAvailable());
		}



	}


//	public void PopulateTigerBaloonQuest(){
//		//GameManager.Instance.CurrentQuest = new Quest ();
//
//		//GameManager.Instance.TogglePopulateQuest (GameManager.Instance.CurrentQuest);
//	}
	IEnumerator NotAvailable(){
		Player.WalkWithTransform ();
		yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());
		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<ElephantHub>().elephantTalkPoint);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

		Elephant.dialogController.PopDialogue("مرحبًا، لا أشعر بالرغبة\n في اللعب الآن");
		yield return new WaitForSeconds (3f);

		Elephant.dialogController.ChangeText ("ربما في المرة القادمة");
		yield return new WaitForSeconds (1f);
		Elephant.dialogController.UnPopDialogue ();

		yield return new WaitForSeconds (1f);



	}

	public void Reset(){
		currentElephantstate = ElephantState.NONE;
		GameManager.Instance.StopAllCoroutines ();

		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		MainUIManager.Instance.decisionUiController.UnPopGenericTapIcon ();
		MainUIManager.Instance.decisionUiController.UnPopTap ();
	}
	void ProceedState(){
		currentElephantstate++;
		if (currentElephantstate == ElephantState.FINISH) {
			if (GameManager.Instance.getCurrentGameState () + 1 == GameManager.GameSate.FINISH) {
				GameManager.Instance.ProceedGameState ();
			}

		}
	}


	void PlayCurrentState(){
		ProceedState ();
		switch (currentElephantstate) {
		case ElephantState.SCENE_INTRO:
			GameManager.Instance.StartCoroutine(GameManager.Instance.elephantcontroller.SCENE_INTRO());
			break;
//			//		case TigerCaveState.PARTY_FURNITURE:
//			//GameManager.Instance.StartCoroutine(GameManager.Instance.tigerCaveController.PARTY_FURNITURE());
//			//			break;

		default:
			break;
		}

	}


	IEnumerator SCENE_INTRO(){
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		yield return new WaitForSeconds (0.4f);
		Player.WalkWithTransform ();
		yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());

		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<ElephantHub>().elephantTalkPoint);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

		Elephant.dialogController.PopDialogue("مرحبًا، لا أشعر بالرغبة\n في اللعب الآن");
		yield return new WaitForSeconds (3f);

		Elephant.dialogController.ChangeText ("ربما في المرة القادمة");
		yield return new WaitForSeconds (1f);
		Elephant.dialogController.UnPopDialogue ();

		yield return new WaitForSeconds (1f);


		PlayCurrentState ();
	

	}

}
