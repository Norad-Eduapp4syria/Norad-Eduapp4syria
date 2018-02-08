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
//	public Sprite Icon_Hungry;
//	public Sprite Icon_Afraid;


	public Sprite Title_Angry;
	public Sprite Title_Bored;
	public Sprite Title_Sad;
//	public Sprite Title_Hungry;
//	public Sprite Title_Afraid;

	public AudioClip Sound_Angry;
	public AudioClip Sound_Bored;
	public AudioClip Sound_Sad;
//	public AudioClip Sound_Hungry;
//	public AudioClip Sound_Afraid;


	public GameObject SadMonster_m1e4;
	public GameObject SadMonster_m2e4;
	public GameObject SadMonster_m3e4;
	public GameObject SadMonster_m4e4;
	public GameObject SadMonster_m5e4;
	public GameObject SadMonster_m6e4;


	public GameObject ButtonOK;


	Monster CurrentMonster;





	// Use this for initialization
	void Start () {
		Destroy (gameObject);
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
		Destroy (gameObject);

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
		case MonsterEmotionTypes.NONE:
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
//		case MonsterEmotionTypes.Hungry:
//			UpdateTitle (Title_Hungry);
//			UpdateIcon (Icon_Hungry);
//			AudioController.Instance.PlaySound (Sound_Hungry);
//			break;
//		case MonsterEmotionTypes.Afraid:
//			UpdateTitle (Title_Afraid);
//			UpdateIcon (Icon_Afraid);
//			AudioController.Instance.PlaySound (Sound_Afraid);
//			break;
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
		if (MonsterHolder == null) {
			return;
		}

		GameObject go = null;

		switch (CurrentMonster.MonsterType) {
		case MonsterType.Magnet:
			go = SadMonster_m1e4;
			break;
		case MonsterType.Ice:
			go = SadMonster_m2e4;
			break;
		case MonsterType.Hypnosis:
			go = SadMonster_m3e4;
			break;
		case MonsterType.Fire:
			go = SadMonster_m4e4;
			break;
		case MonsterType.Larva:
			go = SadMonster_m5e4;
			break;
		case MonsterType.Knight:
			go = SadMonster_m6e4;
			break;
		}

		if (go != null) {
			SadMonster = (GameObject)Instantiate (go, MonsterHolder.transform, false);
//			SadMonster.transform.SetParent (MonsterHolder.transform, true);
//			SadMonster.transform.localPosition = Vector3.zero;
		}

	}


	public void OnOKClick()
	{
		Analitics.Instance.treckEvent (AnaliticsCategory.Sel, AnaliticsAction.Open, "Status Popup");

		SceneController.Instance.LoadScene("MiniGamesScreen");

		GameAssets.Instance.DefaultMonster = CurrentMonster.MonsterType;
		Destroy (gameObject);
	}


	public void OnCloseClick()
	{
		Destroy (gameObject);
	}

}
