using UnityEngine;
using System.Collections;

public class IRSceneShiftController : MonoBehaviour {



	public IRTriggerSpawner SceneTriggerSpawner;
	public HurdleMainController hmc;
	public IRPlayerController player;

	//private bool ActiveTriggerSpawner=false;
	private int ShiftCounter=0;

	// here i will give the list of commands and how trigger behaves;

	void Start(){
		player.CollectPowerUp += OnCollectLetter;
		player.CollectSceneTrigger += OnCollectSceneTrigger;
		SceneTriggerSpawner.gameObject.SetActive (false);
	}

	void Update(){
		
	}

	void OnCollectLetter(){

		if (IRPlayerController.currentWorld == 0 && (!player.QuestCompleted)) {
			ShiftCounter++;
			if (ShiftCounter >= (GameManager.Instance.CurrentQuest.getTotalLearningObjects()/3)) {
				hmc.DisableSpawner ();
				SceneTriggerSpawner.gameObject.SetActive (true);
			}
		}
	}
	void OnCollectSceneTrigger(float time){
		StartCoroutine ("ShiftToLand", time);
		SceneTriggerSpawner.gameObject.SetActive (false);
		hmc.EnableSpawner();

	}

	IEnumerator ShiftToLand(object time){
		yield return new WaitForSeconds (((float)time));
		if (IRPlayerController.currentWorld == 1) {
			ShiftCounter = 0;
			player.FlyToLand ();
		} else if (IRPlayerController.currentWorld == -1) {
			ShiftCounter = 0;
			player.WaterToLand ();
		}

	}

}
