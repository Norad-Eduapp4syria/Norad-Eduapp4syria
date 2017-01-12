using UnityEngine;
using System.Collections;

public class BaseMiniGame : MonoBehaviour {

	public bool GameOver = false;



//	public GameObject TitleImage;
	public AudioClip TitleSound;
	public GameObject VictoryImage;
	//public AudioClip VictorySound;


	public AudioClip VictoryFromAngry;
	public AudioClip VictoryFromBored;
	public AudioClip VictoryFromSad;
	public AudioClip VictoryFromHungry;
	public AudioClip VictoryFromAfraid;


	protected Animator animController;
	protected Monster CurrentMonster;


	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		//TitleImage.GetComponent<CanvasGroup> ().alpha -= Time.deltaTime/10;
	}
		
	public void StartMiniGame() {
		if (VictoryImage) {
			VictoryImage.SetActive (false);
		}
//		TitleImage.transform.localScale = new Vector3 (0, 0, 0);
//		TitleImage.SetActive (true);
		AudioController.Instance.PlaySound (TitleSound);
//		this.gameObject.GetComponent<UIPopupPanel> ().PopOutAny (TitleImage.transform, 6f, 2f);
		gameObject.SetActive (true);
		var obj = GameObject.Find ("monster");
		if (obj != null) {
			animController = obj.GetComponentInChildren<Animator> ();
		}
		GameOver = false;
	}

	public void EndMiniGame() {
		VictoryImage.transform.localScale = new Vector3 (0, 0, 0);
		VictoryImage.SetActive (true);

		playHappySound ();

		this.gameObject.GetComponent<UIPopupPanel> ().PopInAny (VictoryImage.transform, 0, 5f);
		this.gameObject.GetComponent<UIPopupPanel> ().PopOutAny (VictoryImage.transform, 6f, 2f);

		onMiniGameDone ();
//		Invoke ("onMiniGameDone", 4f);
		GameOver = true;
	}
	void onMiniGameDone() {
		MiniGameController.Instance.onMiniGameDone ();
	}

	public virtual void init (Monster monster)
	{
		CurrentMonster = monster;

		animController.SetBool ("IsSad", true);
	}


	void playHappySound ()
	{
		AudioClip snd = null;

		switch (CurrentMonster.EmotionType) {
			case MonsterEmotionTypes.Angry:
				snd = VictoryFromAngry;
				break;
			case MonsterEmotionTypes.Bored:
				snd = VictoryFromBored;
				break;
			case MonsterEmotionTypes.Sad:
				snd = VictoryFromSad;
				break;
			case MonsterEmotionTypes.Hungry:
				snd = VictoryFromHungry;
				break;
			case MonsterEmotionTypes.Afraid:
				snd = VictoryFromAfraid;
				break;
			default:
				snd = VictoryFromSad;
				break;
		}
		if (snd != null) {
			AudioController.Instance.PlaySound (snd);
		}
	}

}
