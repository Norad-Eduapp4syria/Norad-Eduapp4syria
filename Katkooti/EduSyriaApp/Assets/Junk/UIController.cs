using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class UIController : MonoBehaviour {

	// Use this for initialization
	public Text tex;
	bool TurnOnButton=false;
	public GameObject jump,slide,fly,dive,water2land,air2land,waterjump;
	void Start () {
	
	}
		
	public void ToggleButton(){
		TurnOnButton = !TurnOnButton;
		if (TurnOnButton == false) {
			
			jump.SetActive (false);
			slide.SetActive (false);
			waterjump.SetActive (false);
		}
	}
	public void Restart(){
		
		Application.LoadLevel (0);

	}
	public void Exit(){
		Application.Quit ();

	}
	// Update is called once per frame
	void Update () {
		if (TurnOnButton) {
			if (IRPlayerController.currentWorld == 0) {
//		
			jump.SetActive (true);
 	 		slide.SetActive (true);
////			djump.SetActive (true);
//			fly.SetActive (true);
//			dive.SetActive (true);
//
//			water2land.SetActive (false);
//			air2land.SetActive (false);
			waterjump.SetActive (false);
//			tex.text = "";
				//changelane.SetActive (false);
			}
			if (IRPlayerController.currentWorld == 1) {
		
			jump.SetActive (false);
			slide.SetActive (false);
////			djump.SetActive (false);
//			fly.SetActive (false);
//			dive.SetActive (false);
//
//			water2land.SetActive (false);
//			air2land.SetActive (true);
			waterjump.SetActive (false);
//			tex.text = "Swipe up or down to change lane respectively";
				//	changelane.SetActive (true);
			}
			if (IRPlayerController.currentWorld == -1) {

			jump.SetActive (false);
			slide.SetActive (false);
////			djump.SetActive (false);
//			fly.SetActive (false);
//			dive.SetActive (false);
//
//			water2land.SetActive (true);
//			air2land.SetActive (false);
			waterjump.SetActive (true);
//			tex.text = "";
				//		changelane.SetActive (false);
			}
		}
	}
}
