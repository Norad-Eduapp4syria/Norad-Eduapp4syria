using UnityEngine;
using System.Collections;

public class TreasureChest : MonoBehaviour {


	public delegate void onDoneDelegate();
	public onDoneDelegate onDone;


	private int clicksHad = 0;
	private CanvasGroup cg;

	public GameObject BoxClose;
	public GameObject BoxOpen;

	public GameObject ParticlesOpen;


	public AudioClip SoundOpen;
	public AudioClip SoundOpenSFX;

	public AudioClip SoundSucsess;
	public AudioClip SoundSucsessSFX;

	public AudioClip SoundClick;

	float shakeSpeedX = 300f;
	float shakeSpeedY = 70f;
	float shakeSpeedZ = 70f;


	Vector3 initPosition;
	Quaternion initRotation;

	bool toShake;
	bool isDone;


	// Use this for initialization
	void Start () {
		clicksHad = 0;
		toShake = false;
		isDone = false;

		BoxClose.SetActive (true);
		BoxOpen.SetActive (false);

		initPosition	= BoxClose.transform.position;
		initRotation	= BoxClose.transform.rotation;

		cg = this.gameObject.GetComponent<CanvasGroup> ();

		AudioController.Instance.PlaySound (SoundOpenSFX);

		if (ParticlesOpen != null) {
			ParticlesOpen.SetActive (false);
		}
		Invoke ("playOpenVoice", 1f);
	}

	void playOpenVoice()
	{
		AudioController.Instance.PlaySound (SoundOpen);
	}

	
	// Update is called once per frame
	void Update () {

		if (clicksHad >= GameplaySettings.TreasureChest_ClicksToOpen) {
			StartCoroutine (startHide ());
		} else if (toShake) {
			Vector3 v = new Vector3 ();
			v.x = Mathf.Sin (Time.time * shakeSpeedX);
			v.x = Mathf.Sin (Time.time * shakeSpeedY);
			BoxClose.transform.position = v + initPosition;

			v = Vector3.zero;
			v.z = Mathf.Sin (Time.time * shakeSpeedZ);

			BoxClose.transform.rotation = Quaternion.Euler(v);
		}
	}

	bool isTutorial = false;

	public void addTutorial()
	{
		TutorialController.Instance.PointAt (this.transform.position - new Vector3(50, 220, 0), this.transform);

		isTutorial = true;
	}

	IEnumerator startHide()
	{
		yield return new WaitForSeconds (3.0f);

		cg.alpha -= Time.deltaTime;
		if (cg.alpha <= 0) {
			if(onDone != null && !isDone) {
				isDone = true;
				onDone ();
			}
			if (isTutorial) {
				TutorialController.Instance.EndTutorial ();
			}
			Destroy (this.gameObject);
		}
	}

	public void onClick() {
		if (!isDone) {
			clicksHad++;
			if (clicksHad == GameplaySettings.TreasureChest_ClicksToOpen) {
				OpenChest ();
				if (AudioController.Instance != null) {
					AudioController.Instance.PlaySound (SoundSucsess);
					AudioController.Instance.PlaySound (SoundSucsessSFX);
				}
				if (ParticlesOpen != null) {
					ParticlesOpen.SetActive (true);
				}
			} else {
				startShake ();
//			Handheld.Vibrate();
				if (AudioController.Instance != null) {
					AudioController.Instance.PlaySound (SoundClick);
				}
			}
		}
	}

	void startShake ()
	{
		toShake = true;
		Invoke ("stoptShake", 0.3f);
	}
	void stoptShake()
	{
		toShake = false;
		BoxClose.transform.position = initPosition;
		BoxClose.transform.rotation = initRotation;
	}

	void OpenChest() {

		BoxClose.SetActive (false);
//		BoxOpen.SetActive (true);

		addScore(getRandomScore());
		cg.interactable = false;
		cg.blocksRaycasts = false;
	}


	int getRandomScore()
	{
		int sum;

		sum = Random.Range(GameplaySettings.TreasureChest_ScoreMin, GameplaySettings.TreasureChest_ScoreMax + 1);
		sum = sum / 10;
		sum = sum * 10;
		return sum;
	}

	void addScore(int score) {
		addScorebubble (transform, score);
		if (GameplayController.Instance) {
			GameplayController.Instance.IncreaseLevelScore (score);
		}
	}

	void addScorebubble (Transform parent, int score)
	{
		GameObject GOScore = Instantiate(Resources.Load ("Gameplay/ScoreAnimation") as GameObject);
		GOScore.transform.SetParent (parent, false);
		if (transform != parent) {
			GOScore.transform.position = transform.position;
		}
		UIScoreAnimationController c = GOScore.GetComponent<UIScoreAnimationController>();
		c.gameObject.AddComponent<DestroyAfter> ().After = 1.4f;
		c.Play (score);
	}
}
