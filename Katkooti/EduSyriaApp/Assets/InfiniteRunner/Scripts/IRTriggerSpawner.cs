using UnityEngine;
using System.Collections;

public class IRTriggerSpawner : MonoBehaviour {

	public GameObject camera;
	public Parallax groundParallex;
	public Parallax foregroundParallex;
	public IRSceneShiftTrigger SkySceneTrigger;
	public IRSceneShiftTrigger WaterSceneTrigger;

	public int triggerMin,triggerMax;
	public GameObject WaterToLandShift;

	public float minTime, maxTime;




	[Range(0.5f,20)]
	public float RefreshTime=0;


	private bool ReadyAgain;

	int Rand=2;
	void Start(){
		ReadyAgain = true;

	}

	void OnEnable(){
		ReadyAgain = true;
		RefreshTime = 4;

	}
	void Update(){


		if (ReadyAgain) {
			Rand = Random.Range (triggerMin, triggerMax);

			if (Rand == 1) {
				IRSceneShiftTrigger temp=Instantiate (SkySceneTrigger, this.transform.position, Quaternion.identity) as IRSceneShiftTrigger;
				GameObject currentPowerUp = GameObject.FindGameObjectWithTag ("PowerUp");
				if (currentPowerUp != null) {
					if (Vector3.Distance (currentPowerUp.transform.position, temp.gameObject.transform.position) < 3) {
						Destroy (currentPowerUp);
					}
				}
				temp.targetScene =IRSceneShiftTrigger.IRScene.SKY;
				temp.lifeSpan = Random.Range (minTime, maxTime);
			} else if (Rand == 2) {
				if((groundParallex.currentPatching==0 &&	groundParallex.temp==0) ){
					IRSceneShiftTrigger temp=Instantiate (WaterSceneTrigger, groundParallex._clone.transform.position, Quaternion.identity) as IRSceneShiftTrigger;
					temp.targetScene =IRSceneShiftTrigger.IRScene.WATER;
					temp.lifeSpan  = Random.Range (minTime, maxTime);
					Invoke ("ShiftToLandFromWater", temp.lifeSpan+3.6f);
					RefreshTime = temp.lifeSpan+18;
				}
			}


			ReadyAgain = false;
			StartCoroutine ("SetReadyAgain");
		}
	}
	public void TriggerSpawner(int value){

	}
	IEnumerator SetReadyAgain(){

		yield return new WaitForSeconds (RefreshTime);
		ReadyAgain = true;

	}

	public void DisbaleGroundParallex(){
		groundParallex.DisableClone ();
		groundParallex.gameObject.SetActive (false);
		foregroundParallex.DisableClone ();
		foregroundParallex.gameObject.SetActive (false);
	}

	public void EnableGroundParallex(){
		groundParallex.currentPatching = 0;
		groundParallex.temp = 0;
		groundParallex.EnableClone ();
		groundParallex.gameObject.SetActive (true);
		groundParallex.OnSetEnable ();
		foregroundParallex.EnableClone ();
		foregroundParallex.gameObject.SetActive (true);
	}

	public void EnableAfterSeconds(float time){
		Invoke ("EnableGroundParallex",time);
	}
	void ShiftToLandFromWater(){
			Instantiate (WaterToLandShift,this.transform.position, Quaternion.identity);

		GameObject[] tempHurdles = GameObject.FindGameObjectsWithTag ("Hurdle");

		foreach (GameObject g in tempHurdles) {
			if (g.gameObject.name.Contains ("WaterHurdle 2")) {
				Destroy (g);
			}
		}

	}

}
