using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class IRFillBar : MonoBehaviour {

	// Use this for initialization

	//this is Jumk
	public GameObject b1,b2,b3;
	public LocalSoundHandler handler;
	//this is junk


	public IRPlayerController player;
	Image image;

	void Start () {
		image = this.GetComponent<Image> ();
		image.fillAmount = 0;

//		player.PlayerHit += OnPlayerHit;
//		player.CollectPowerUp += OnCollectPowerUp;
	}


	void Update () {
		
		image.fillAmount =Mathf.Lerp(image.fillAmount,GameManager.Instance.ChickSongPowerValue,1*Time.deltaTime);


	}




}
