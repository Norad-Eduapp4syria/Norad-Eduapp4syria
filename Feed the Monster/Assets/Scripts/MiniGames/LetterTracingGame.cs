using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LetterTracingGame : BaseMiniGame
{
	public TR_GameManager GameManager;

	public float HeightClose = 16f;
	public float HeightOpen = 484.5f;

	[Range(0.2f,5f)]
	public float Speed = 1;

	public List<GameObject> LettersGroup_1;
	public List<GameObject> LettersGroup_2;
	public List<GameObject> LettersGroup_3;
	public List<GameObject> LettersGroup_4;
	public List<GameObject> LettersGroup_5;
	public List<GameObject> LettersGroup_6;



	RectTransform _rectTransform;

	RectTransform rectTransform {
		get
		{ 
			if (_rectTransform == null) {
				_rectTransform = (RectTransform)transform;
			}
			return _rectTransform;
		}
	}

	// Use this for initialization
	void Start () {
		GameManager.onComplete = complete;
	}

	void OnEnable()
	{
		UpdateLettersFroGroup ();
		UpdateSize (HeightClose);
		StartMiniGame ();

		onScreenClosed ();
	}

	// Update is called once per frame
	void Update () {
		
	}

	public override void init (Monster monster)
	{
		base.init (monster);
	}

	void UpdateLettersFroGroup()
	{
		int currentGroup = UserInfo.Instance.GetLastLetterGroup();
		List<GameObject> newList = new List<GameObject>();

		if(currentGroup >= 1) {
			newList.AddRange (LettersGroup_1);
		}
		if(currentGroup >= 2) {
			newList.AddRange (LettersGroup_2);
		}
		if(currentGroup >= 3) {
			newList.AddRange (LettersGroup_3);
		}
		if(currentGroup >= 4) {
			newList.AddRange (LettersGroup_4);
		}
		if(currentGroup >= 5) {
			newList.AddRange (LettersGroup_5);
		}
		if(currentGroup >= 6) {
			newList.AddRange (LettersGroup_6);
		}
		GameManager.shapes = newList.ToArray ();
		GameManager.cleanShapesQueue ();
	}

	public void complete() 
	{
		animController.SetBool ("IsSad", false);
		MiniGameController.Instance.ResetEmotion ();

		CloseScreen();
	}

	void CloseScreen()
	{
		iTween.ValueTo (gameObject, 
			iTween.Hash (
				"from", rectTransform.sizeDelta.y,
				"to", HeightClose,
				"time", Speed,
				"oncomplete", "onScreenClosed",
				"onupdate", "UpdateSize"
			)
		);
	}

	void onScreenClosed()
	{
		GameManager.CreateShape ();
		OpenScreen ();
	}

	void OpenScreen()
	{
		iTween.ValueTo (gameObject, 
			iTween.Hash (
				"from", rectTransform.sizeDelta.y,
				"to", HeightOpen,
				"time", Speed,
				"oncomplete", "onScreenOpened", 
				"onupdate", "UpdateSize"
			)
		);
	}

	void onScreenOpened()
	{

	}

	void UpdateSize(float Height)
	{
		rectTransform.sizeDelta = new Vector2(rectTransform.sizeDelta.x, Height);
	}


}
