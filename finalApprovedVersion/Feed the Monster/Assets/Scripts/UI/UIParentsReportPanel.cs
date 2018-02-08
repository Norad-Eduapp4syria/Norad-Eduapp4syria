using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIParentsReportPanel : MonoBehaviour {
	public static UIParentsReportPanel Instance;

	public Color ColorLow;
	public Color ColorMid;
	public Color ColorHigh;

	public UIParentsReportSlider sliderLetter;
	public UIParentsReportSlider sliderSyllable;
	public UIParentsReportSlider sliderWord;

	public Text TextLevel;
	public GameObject ImageLevel;



	[Range(0f,100f)]
	public float SoundLevelWeight = 70f;


	public Image ProfileIcon;

	public Button PreviousButton;
	public Button NextButton;

	List<int> scoreLetter = new List<int> ();
	List<int> scoreLetterSound = new List<int>();
	List<int> scoreSyllable = new List<int>();
	List<int> scoreWord = new List<int> ();
	List<int> scoreWordSound = new List<int>();


	int initProfileId;


	// Use this for initialization
	void Awake () {
		Instance = this;
	}


	// Use this for initialization
	void Start () {
	}

	void OnEnable() {
//		GameplayController.Instance.LoadBackground (background);
		Analitics.TreckScreen ("Parents Report");

		initProfileId = UsersController.Instance.CurrentProfileId;

		sliderLetter.Value = 0;
		sliderSyllable.Value = 0;
		sliderWord.Value = 0;

		updateProfile ();

		recivedScores ();
		calculateScores ();
	}

	void OnDisable()
	{
		UsersController.Instance.CurrentProfileId = initProfileId;
//		GameplayController.Instance.DestroyBackground();
	}

	// Update is called once per frame
	void Update () {
		
	}

	void updateProfile()
	{
		if(ProfileIcon != null) {
			Sprite sp = UsersController.Instance.CurrentProfileSprite;
			if (sp != null) {
				ProfileIcon.sprite = sp;
			}
		}
	}

	void recivedScores()
	{
		scoreLetter.Clear();
		scoreLetterSound.Clear();
		scoreSyllable.Clear();
		scoreWord.Clear();
		scoreWordSound.Clear();
		if (XMLController.Instance != null) {
			foreach (Level lvl in XMLController.Instance.getLevelList()) {
				if (lvl != null) {
					int stars = UsersController.Instance.userData().getLevelStars (lvl.levelId - 1);

					switch (lvl.monsterInputType) {
					case MonsterInputType.Letter:
					case MonsterInputType.LetterName:
						scoreLetter.Add (stars);
						break;
					case MonsterInputType.SoundLetter:
					case MonsterInputType.SoundLetterName:
						scoreLetterSound.Add (stars);
						break;
					case MonsterInputType.LetterInWord:
						scoreSyllable.Add (stars);
						break;
					case MonsterInputType.Word:
						scoreWord.Add (stars);
						break;
					case MonsterInputType.SoundWord:
						scoreWordSound.Add (stars);
						break;
					}
				}
			}
		}
	}

	void calculateScores()
	{
		float i1, i2, avarage;

		i1 = getAvarage (scoreLetter);
		i2 = getAvarage (scoreLetterSound);

		avarage = ((i1 / 100) * (100 - SoundLevelWeight)) + ((i2 / 100) * SoundLevelWeight);
		StartCoroutine (updateSlider (sliderLetter, (int)((avarage * 100) / 3)));

		i1 = getAvarage (scoreSyllable);
		StartCoroutine (updateSlider (sliderSyllable, (int)((i1 * 100) / 3)));

		i1 = getAvarage (scoreWord);
		i2 = getAvarage (scoreWordSound);
		avarage = ((i1 / 100) * (100 - SoundLevelWeight)) + ((i2 / 100) * SoundLevelWeight);
		StartCoroutine (updateSlider (sliderWord, (int)((avarage * 100) / 3)));


		int highestLevelOpenIndex = UsersController.Instance.userData().getHighestOpenLevel ();

		if (highestLevelOpenIndex > 0) {
			ImageLevel.gameObject.SetActive (true);
			TextLevel.text = highestLevelOpenIndex.ToString ();
		} else {
			ImageLevel.gameObject.SetActive (false);
		}
	}

	float getAvarage (List<int> list)
	{
		float sum = 0;
		float count = 0;
		list.ToArray ();

		foreach (int s in list) {

			if (s > 0) {
				sum += s;
				count++;
			}
		}

		if (count == 0) {
			return 0;
		} else {
			return sum / count;
		}
	}

	IEnumerator updateSlider(UIParentsReportSlider s,  int stars, float speed=0.1f)
	{
		float v;
//		for(float t=0; t<=1; t += speed * Time.deltaTime)
		while (s.Value != stars)
		{
//			float v = Mathf.Lerp ((float) s.Value, (float)stars, t*t*4);
//			float v = Mathf.MoveTowards((float)s.Value, (float)stars, t*t * 50);
			yield return new WaitForSeconds (0.008f);
			if (s.Value > stars) {
				v = s.Value - 1;
				if (v <= stars) {
					v = stars; 
				}
			} else {
				v = s.Value + 1;
				if (v >= stars) {
					v = stars; 
				}
			}
			s.Value = (int)v;
		}
		yield return true;
	}

	public void OnPreviousClick()
	{
		int current = UsersController.Instance.CurrentProfileId;
		current--;

		if (current < 0) {
			current = 3;
		}
		UsersController.Instance.CurrentProfileId = current;
		OnChangeProfile ();
	}

	public void OnNextClick()
	{
		int current = UsersController.Instance.CurrentProfileId;
		current++;

		if (current > 3) {
			current = 0;
		}
		UsersController.Instance.CurrentProfileId = current;
		OnChangeProfile ();
	}

	public void OnChangeProfile()
	{
		StopAllCoroutines ();

		updateProfile ();
		recivedScores ();
		calculateScores ();
	}


	public void backToMap() {
		SceneController.Instance.LoadScene("MapScreen");
	}


}
