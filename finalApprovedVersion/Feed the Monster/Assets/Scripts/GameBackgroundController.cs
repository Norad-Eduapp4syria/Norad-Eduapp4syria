using UnityEngine;
using System.Collections;

public class GameBackgroundController : MonoBehaviour {

	public static GameBackgroundController Instance;


	public SpriteRenderer BackgroundCloud1;
	public SpriteRenderer BackgroundCloud2;
	public SpriteRenderer ForegroundCloud1;
	public SpriteRenderer ForegroundCloud2;
	public SpriteRenderer ForegroundCloud3;
	public SpriteRenderer Hill;


	void Awake()
	{
		Instance = this;
	}

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	//public void Load(Level level){
	public void Load(GameBackground background){
		gameObject.SetActive (true);
		if (background != null) {
			GetComponent<SpriteRenderer> ().sprite = background.PlaygroundSprite;

			setSprite (BackgroundCloud1,	background.BackgroundCloud1);
			setSprite (BackgroundCloud2,	background.BackgroundCloud2);
			setSprite (ForegroundCloud1,	background.ForegroundCloud1);
			setSprite (ForegroundCloud2,	background.ForegroundCloud2);
			setSprite (ForegroundCloud3,	background.ForegroundCloud3);
			setSprite (Hill, background.Hill);
		}
/*
		GetComponent<SpriteRenderer>().sprite = level.PlaygroundSprite;
		BackgroundCloud1.sprite = level.BackgroundCloud1;
		BackgroundCloud2.sprite = level.BackgroundCloud2;
		ForegroundCloud1.sprite = level.ForegroundCloud1;
		ForegroundCloud2.sprite = level.ForegroundCloud2;
		ForegroundCloud3.sprite = level.ForegroundCloud3;
		Hill.sprite = level.Hill;
*/
	}


	void setSprite(SpriteRenderer sp, Sprite newSprite) 
	{
		if (newSprite != null) {
			sp.gameObject.SetActive (true);
			sp.sprite = newSprite;
		} else {
			sp.gameObject.SetActive (false);
		}

	}

}
