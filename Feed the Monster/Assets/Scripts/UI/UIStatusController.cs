using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class UIStatusController : MonoBehaviour {


	public Image TitleImg;
	public Image IconImg;
	public GameObject MonsterHolder;

	public Sprite Icon_Angry;
	public Sprite Icon_Bored;
	public Sprite Icon_Sad;
	public Sprite Icon_Hungry;
	public Sprite Icon_Afraid;


	public Sprite Title_Angry;
	public Sprite Title_Bored;
	public Sprite Title_Sad;
	public Sprite Title_Hungry;
	public Sprite Title_Afraid;

	public AudioClip Sound_Angry;
	public AudioClip Sound_Bored;
	public AudioClip Sound_Sad;
	public AudioClip Sound_Hungry;
	public AudioClip Sound_Afraid;


	public GameObject SadMonster_m1e2;
	public GameObject SadMonster_m1e3;
	public GameObject SadMonster_m1e4;


	public GameObject SadMonster_m2e2;
	public GameObject SadMonster_m2e3;
	public GameObject SadMonster_m2e4;

	public GameObject SadMonster_m3e2;
	public GameObject SadMonster_m3e3;
	public GameObject SadMonster_m3e4;


	public GameObject ButtonOK;


	Monster CurrentMonster;





	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
		if (TutorialController.Instance.GetIsInMinigameTutorial ()) { //Jonathan
			TutorialController.Instance.PointAt(ButtonOK.transform.position, this.transform);
		}
		if (SadMonster != null) {
			Destroy (SadMonster);
		}
	}

	public void init(Monster monster)
	{
		CurrentMonster = monster;
		if (SadMonster != null) {
			Destroy (SadMonster);
		}

		switch (CurrentMonster.EmotionType) {

		case MonsterEmotionTypes.Happy:
			break;
		case MonsterEmotionTypes.Angry:
			UpdateTitle (Title_Angry);
			UpdateIcon (Icon_Angry);
			AudioController.Instance.PlaySound (Sound_Angry);
			break;
		case MonsterEmotionTypes.Bored:
			UpdateTitle (Title_Bored);
			UpdateIcon (Icon_Bored);
			AudioController.Instance.PlaySound (Sound_Bored);
			break;
		case MonsterEmotionTypes.Sad:
			UpdateTitle (Title_Sad);
			UpdateIcon (Icon_Sad);
			AudioController.Instance.PlaySound (Sound_Sad);
			break;
		case MonsterEmotionTypes.Hungry:
			UpdateTitle (Title_Hungry);
			UpdateIcon (Icon_Hungry);
			AudioController.Instance.PlaySound (Sound_Hungry);
			break;
		case MonsterEmotionTypes.Afraid:
			UpdateTitle (Title_Afraid);
			UpdateIcon (Icon_Afraid);
			AudioController.Instance.PlaySound (Sound_Afraid);
			break;
		}
		UpdateMonster ();
	}

	void UpdateIcon(Sprite Icon)
	{
		if (IconImg != null) {
			if (Icon != null) {
				IconImg.sprite = Icon;
			}
		}
	}

	void UpdateTitle(Sprite Title)
	{
		if (TitleImg != null) {
			if (Title != null) {
				TitleImg.sprite = Title;
			}
		}
	}
	GameObject SadMonster;
	void UpdateMonster()
	{
		GameObject go = null;
		if (CurrentMonster.MonsterType == MonsterType.Magnet) {
			if (CurrentMonster.Gage == 1) {
				go = SadMonster_m1e2;
			} else if (CurrentMonster.Gage == 2) {
				go = SadMonster_m1e3;
			} else if (CurrentMonster.Gage == 3) {
				go = SadMonster_m1e4;
			} else  {
				go = SadMonster_m1e4;
			}
		} else if (CurrentMonster.MonsterType == MonsterType.Ice) {
			if (CurrentMonster.Gage == 1) {
				go = SadMonster_m2e2;
			} else if (CurrentMonster.Gage == 2) {
				go = SadMonster_m2e3;
			} else if (CurrentMonster.Gage == 3) {
				go = SadMonster_m2e4;
			} else  {
				go = SadMonster_m2e4;
			}
		} else if (CurrentMonster.MonsterType == MonsterType.Hypnosis) {
			if (CurrentMonster.Gage == 1) {
				go = SadMonster_m3e2;
			} else if (CurrentMonster.Gage == 2) {
				go = SadMonster_m3e3;
			} else if (CurrentMonster.Gage == 3) {
				go = SadMonster_m3e4;
			} else  {
				go = SadMonster_m3e4;
			}
		}

		if (go != null) {
			SadMonster = (GameObject)Instantiate (go, MonsterHolder.transform, false);
//			SadMonster.transform.SetParent (MonsterHolder.transform, true);
//			SadMonster.transform.localPosition = Vector3.zero;
		}

	}


	public void OnOKClick()
	{
		UIController.Instance.ShowPanel (UIController.Instance.MiniGamePopup);
		UIController.Instance.ClosePopup (UIController.Instance.MonsterStatusPopup);
	}
}
