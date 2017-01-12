using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class HudController : MonoBehaviour {

	public Image ChickSongBar;
	public GameObject screeenTapEffect;
	public GameObject star;
	public GameObject inventoryIcon;
	public GameObject mapIcon;
	public GameObject mapIconGlow;
	// Use this for initialization

	void Start () {
	
	}
	// Update is called once per frame



	void Update () {
		if(ChickSongBar.IsActive())
			ChickSongBar.fillAmount = Mathf.Lerp( ChickSongBar.fillAmount,GameManager.Instance.ChickSongPowerValue,1*Time.deltaTime);

		if (Input.GetMouseButtonDown (0)) {
			if (Camera.main != null) {
				Vector3 temp = Camera.main.ScreenToWorldPoint (Input.mousePosition); 

				temp = new Vector3 (temp.x, temp.y, 0);
				Instantiate (screeenTapEffect, temp, Quaternion.identity);
				SoundManager.Instance.PlaySoundOneShot ("Tap");
			}

		}


	}
	public void EnableUIMapGlow(){
		mapIconGlow.SetActive (true);
	//	mapIconGlow.GetComponent<AnimateAlpha> ().StartAnimating ();
	}

	public void DisableUIMapGlow(){
		mapIconGlow.SetActive (false);
	//	mapIconGlow.GetComponent<AnimateAlpha> ().StartAnimating ();
	}
	public void OpenMap(){
		MainUIManager.Instance.mapUIController.Activate ();
	}

	public void BackButton(){
	
	}

	public void Inventory(){

	}
	public IEnumerator StarEffect(){
		KatkootiController controller=GameObject.FindObjectOfType<KatkootiController> ();
		if (controller != null) {
			Vector3 temp = Camera.main.ScreenToWorldPoint (ChickSongBar.transform.position); 
			temp = new Vector3 (temp.x, temp.y, 0);
			GameObject obj = Instantiate (star, temp, Quaternion.identity) as GameObject;
			MoveLerp m = obj.GetComponent<MoveLerp> ();
			m.target = controller.chickSongEffectPosition;
			yield return new WaitForSeconds (0.2f);



			temp = Camera.main.ScreenToWorldPoint (ChickSongBar.transform.position); 
			temp = new Vector3 (temp.x, temp.y, 0);
			obj = Instantiate (star, temp, Quaternion.identity) as GameObject;
			 m = obj.GetComponent<MoveLerp> ();
			m.target = controller.chickSongEffectPosition;
			yield return new WaitForSeconds (0.2f);

			if(GameManager.Instance.getCurrentGameState() == GameManager.GameSate.TUTORIAL)
				GameManager.Instance.EnableExterior ();
			
			 temp = Camera.main.ScreenToWorldPoint (ChickSongBar.transform.position); 
			temp = new Vector3 (temp.x, temp.y, 0);
			obj = Instantiate (star, temp, Quaternion.identity) as GameObject;
			m = obj.GetComponent<MoveLerp> ();
			m.target = controller.chickSongEffectPosition;
			yield return new WaitForSeconds (0.2f);
		

			temp = Camera.main.ScreenToWorldPoint (ChickSongBar.transform.position); 
			temp = new Vector3 (temp.x, temp.y, 0);
			obj = Instantiate (star, temp, Quaternion.identity) as GameObject;
			m = obj.GetComponent<MoveLerp> ();
			m.target = controller.chickSongEffectPosition;
			yield return new WaitForSeconds (0.2f);
		}
		yield return new WaitForSeconds (0);
	}



}
