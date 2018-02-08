using UnityEngine;
using System.Collections;

public class MonsterPettingGame : BaseMiniGame 
{
	public static MonsterPettingGame Instance;


	public AudioClip Cheering;
	public GameObject PettingZones;

	public int NeededPats = 5;
	public int PatsToClose = 8;

	int count;



	void Awake()
	{
		Instance = this;
	}



	// Use this for initialization
	void Start () {
	}

	void OnDisable(){
		animController.SetInteger ("EmotionState", 0);
		if (Camera.main) {
			Camera.main.orthographicSize = 5;
			Camera.main.transform.position = new Vector3 (0, 0, -10);
		}
		CancelInvoke ();

	}

	void OnEnable()
	{
		ZoomIn ();
		StartMiniGame ();
		count = 0;

		ActiveteZones (true);

//		animController.SetBool ("IsSad", true);
		animController.SetInteger ("EmotionState", 0);

		Analitics.TreckScreen ("Monster Petting - Profile: " + UsersController.Instance.CurrentProfileId);
	}

	// Update is called once per frame
	void Update ()
	{

	}


	void ZoomIn()
	{
		UIZoomIn uIZoomIn = gameObject.AddComponent<UIZoomIn> ();
		uIZoomIn.onDone = onZoomInDone;
		uIZoomIn.init (2.6f);
	}

	void onZoomInDone()
	{
		Invoke ("hideTitle", 1f);
		StartTutorial ();
	}


	void hideTitle()
	{
		if (TitleImage != null) {
			gameObject.GetComponent<UIPopupPanel> ().PopOutAny (TitleImage.transform);
		}
	}


	public void SetEmotion(MonsterPettingZone zone, int i)
	{
		animController.SetInteger ("EmotionState", i);

		if (i > 0) {
			count++;
			if (Cheering != null) {
				AudioController.Instance.PlaySound (Cheering);
			}
			if (count == NeededPats) {
				animController.SetBool ("IsSad", false);
				MiniGameController.Instance.ResetEmotion ();

				Analitics.TreckScreen ("Monster Petting Done - Profile: " + UsersController.Instance.CurrentProfileId);
			} else if (count == PatsToClose) {
				Invoke ("Complete", 2f);
			}
			if (zone.isTutorial) {
				UsersController.Instance.userData().setLastPettingZoneTutorial (UsersController.Instance.userData().getLastPettingZoneTutorial () + 1);
			}
		} else {
			StartTutorial ();
		}
	}

	public override void init (Monster monster)
	{
		base.init (monster);
	}


	void StartTutorial ()
	{
		MonsterPettingZone[] zones = PettingZones.GetComponentsInChildren<MonsterPettingZone> ();
		int lastId = UsersController.Instance.userData().getLastPettingZoneTutorial ();

		if (zones.Length > (lastId + 1)) {
			MonsterPettingZone zone = zones [lastId + 1];
			if (zone != null) {
				zones [lastId + 1].startTutorial ();
			}
		}
	}


	void Complete() {
		if (GameOver) {
			return;
		}

		ActiveteZones (false);
		EndMiniGame();
	}

	void ActiveteZones()
	{
		ActiveteZones (true);
	}

	void ActiveteZones(bool val)
	{
		foreach (Transform zone in PettingZones.transform) {
			zone.gameObject.SetActive (val);
		}
	}


}
