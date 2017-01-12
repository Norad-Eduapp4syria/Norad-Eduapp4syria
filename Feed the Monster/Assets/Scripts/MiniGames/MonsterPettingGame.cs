using UnityEngine;
using System.Collections;

public class MonsterPettingGame : BaseMiniGame 
{
	public AudioClip Cheering;
	public GameObject PettingZones;


	int times;

	// Use this for initialization
	void Start () {
	}

	void OnDisable(){
		Camera.main.orthographicSize = 5;
		Camera.main.transform.position = new Vector3 (0, 0, -10);
	}

	void OnEnable()
	{
		ZoomIn ();
		StartMiniGame ();
		times = 0;

		ActiveteZones (true);

		animController.SetBool ("IsSad", true);
		animController.SetInteger ("IdleState", 0);

		TutorialController.Instance.StartTutorial(MiniGameController.GameType.MonsterPetting); //Jonathan!!!!

	}

	// Update is called once per frame
	void Update ()
	{

	}

	void ZoomIn()
	{
		UIZoomIn uIZoomIn = gameObject.AddComponent<UIZoomIn> ();
		//		uIZoomIn.onDone = onGageZoomInDone;
		uIZoomIn.init (2.6f);
	}

	public void StartPetting()
	{
		times++;
		ActiveteZones (false);

		if (times == 1) {
			animController.SetInteger ("IdleState", Random.Range (1, 4));
			Invoke("ActiveteZones", 1.0f);

		} else if (times == 2) {
			animController.SetBool ("IsSad", false);
			animController.SetInteger ("IdleState", 0);
			Invoke("ActiveteZones", 1.0f);
		} else if (times >= 3) {
			animController.SetInteger ("IdleState", 0);
			animController.SetInteger ("EmotionState", 2);

			Invoke ("Complete", 1.1f);
		}
		if (Cheering != null) {
			AudioController.Instance.PlaySound (Cheering);
		}
	}

	void ResetAnimation()
	{
		animController.SetInteger ("IdleState", 0);
	}

	public override void init (Monster monster)
	{
		base.init (monster);
		Debug.Log ("MonsterPetting init");
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
