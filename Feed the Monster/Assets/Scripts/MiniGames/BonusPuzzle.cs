using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BonusPuzzle : MonoBehaviour {

	public delegate void onDoneDelegate();
	public onDoneDelegate onDone;


	[Range(1,1000)]
	public int MaxStones = 100;

	[Range(0.01f,0.5f)]
	public float Speed = 0.1f; 



	public GameObject StonesHolder;
	public GameObject Stone;

	public GameObject OpenBox;
	public GameObject OpenParticale;

	public GameObject CloseBox;

	public Image title;
	public AudioClip titleSound;

	public AudioClip backSound;


	CanvasGroup cg;
	bool isStart;
	bool isDone = false;
	int count = 0;

	float speed1;
	float speed2;

	// Use this for initialization
	void Start () {
		cg = this.gameObject.GetComponent<CanvasGroup> ();

		speed1 = ((MaxStones / 100f) * 40f);
		speed2 = ((MaxStones / 100f) * 80f);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void OnEnable() {
		Input.multiTouchEnabled = true;
		count = 0;
//		numParticles = 0;
		isStart = false;
		isDone = false;

		OpenBox.SetActive(false);
		CloseBox.SetActive(true);
		if (OpenParticale != null) {
			OpenParticale.SetActive (false);
		}
		if (AudioController.Instance != null) {
			AudioController.Instance.PlaySound (titleSound);
		}
		Invoke ("Init", 2f);
	}

	void OnDisable() {
		Input.multiTouchEnabled = false;
		if (AudioController.Instance != null) {
			AudioController.Instance.ChangeMusic (null);
		}
	}

	void FixedUpdate () {
		if (!isStart) {
			return;
		}

		if (count < MaxStones) {
			float speed;

			if (count > speed2) {
				speed = Speed * 2f;
			} else if (count > speed1) {
				speed = Speed * 1.5f;
			} else {
				speed = Speed;
			}

			if (Random.value < speed) {
				GameObject go = Instantiate (Stone, StonesHolder.transform, false);
				go.GetComponent<BonusPuzzleStone> ().OnClick = onStoneClick;
				go.GetComponent<BonusPuzzleStone> ().OnDestroy = OnStoneDestroy;
				count++;
			}
		} else {
			StartCoroutine (startHide ());
		}
	}

	void Init ()
	{
		isStart = true;
		OpenBox.SetActive(true);
		CloseBox.SetActive(false);
		if (OpenParticale) {
			OpenParticale.SetActive (true);
		}
		title.gameObject.GetComponent<UIPopInOut> ().PopOut ();

		if (AudioController.Instance) {
			AudioController.Instance.ChangeMusic (backSound);
		}
	}

	IEnumerator startHide()
	{
		yield return new WaitForSeconds (2.0f);

		cg.alpha -= Time.deltaTime;
		if (cg.alpha <= 0) {
			if(onDone != null && !isDone) {
				onDone ();
				isDone = true;
			}
			Destroy (this.gameObject);
		}
	}


	//BonusPuzzleStone

//	int numParticles = 0;
//	public int MaxParticles = 2;

	void onStoneClick(BonusPuzzleStone stone)
	{
//		if (numParticles <= MaxParticles)
//		{
			stone.addParticles ();
//			numParticles++;
//		}
	}

	void OnStoneDestroy(BonusPuzzleStone stone)
	{
//		if (numParticles > 0) {
//			numParticles--;
//		}
	}

}
