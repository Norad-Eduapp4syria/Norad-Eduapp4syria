using UnityEngine;
using System.Collections;

public class HurdleMainController : MonoBehaviour {

	public GameObject []LandHurdlesGenerator;
	public GameObject []AirHurdleGenerator;
	public GameObject []WaterHurdlesGenerator;


	private bool Makechange = true;
	private bool LockSpawners=false;
	void Start () {
		InvokeRepeating ("MakeChangeEnable", 0, 3);
		if (IRPlayerController.currentWorld == 0) {
			ToggleLandGenerator(true);
			ToggleAirGenerator(false);
			ToggleWaterGenerator(false);
		}
	}
	public void DisableSpawner(){
		ToggleLandGenerator (false);
		ToggleAirGenerator (false);
		ToggleWaterGenerator (false);
		LockSpawners = true;
		
	}
	public void EnableSpawner(){
		LockSpawners = false;
	}
	// Update is called once per frame
	void Update () {
		if (!LockSpawners) {
			if (IRPlayerController.currentWorld == 0) {
				ToggleLandGenerator (true);
				ToggleAirGenerator (false);
				ToggleWaterGenerator (false);
			} else if (IRPlayerController.currentWorld == 1) {
				ToggleLandGenerator (false);
				ToggleAirGenerator (true);
				ToggleWaterGenerator (false);	
			} else if (IRPlayerController.currentWorld == -1) {
				ToggleLandGenerator (false);
				ToggleAirGenerator (false);
				ToggleWaterGenerator (true);	
			}
		}
	}

	void ToggleLandGenerator(bool value){
		foreach (GameObject g in LandHurdlesGenerator) {
			g.SetActive(value);
		}
	}
	void ToggleWaterGenerator(bool value){
		if (value == false) {
			foreach (GameObject g in WaterHurdlesGenerator) {
				g.SetActive (value);
			}
		} else {
			if (Makechange) {
				int hurdle1 = Random.Range (0, 3);
				int hurdle2 = Random.Range (0, 3);
				for (int i = 0; i < 6; i++) {
					WaterHurdlesGenerator [i].gameObject.SetActive (false);
				}
				for (int i = 0; i < 3; i++) {
					if (i == hurdle1 || i == hurdle2) {
						WaterHurdlesGenerator [i].gameObject.SetActive (true);
					} else {
						WaterHurdlesGenerator [i+3].gameObject.SetActive (true);
					}
				}
				Makechange = false;
			}
		}

	}
	public void LockMainHurdleController(){
		ToggleLandGenerator (false);
		ToggleAirGenerator (false);
		ToggleWaterGenerator (false);
		LockSpawners = true;
	}
	void MakeChangeEnable(){
		Makechange = true;
	}
	void ToggleAirGenerator(bool value){
		if (value == false) {
			foreach (GameObject g in AirHurdleGenerator) {
				g.SetActive (value);
			}
		} else {
			if (Makechange) {
				int hurdle1 = Random.Range (0, 3);
				int hurdle2 = Random.Range (0, 3);
				for (int i = 0; i < 6; i++) {
					AirHurdleGenerator [i].gameObject.SetActive (false);
				}
				for (int i = 0; i < 3; i++) {
					if (i == hurdle1 || i == hurdle2) {
						AirHurdleGenerator [i].gameObject.SetActive (true);
					} else {
						AirHurdleGenerator [i+3].gameObject.SetActive (true);
					}
				}
				Makechange = false;
			}
		}
	}
}
