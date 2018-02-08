using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class UIVoiceTutorial : MonoBehaviour {
	public Action onDone;

	public Image imageMain;
	public Image imageBubble;
	public Image imageBubbleText;

	public string dataToLoad = "Test1";

	Animator mAnimator;
	VoiceTutorialEvent mTutorialEvent;
	VoiceTutorialData data;
	AudioSource mSource;
	bool mIsPlay = false;
	int currentDataId = 0;


	// Use this for initialization
	void Start () {
		mAnimator = gameObject.GetComponentInChildren<Animator> ();
		mTutorialEvent = gameObject.GetComponentInChildren<VoiceTutorialEvent> ();

		mTutorialEvent.onIn = onIn;
		mTutorialEvent.onOut = onOut;

		init ();
	}


	void OnEnable()
	{
		
	}

	// Update is called once per frame
	void Update () {
		if (mTime > 0) {
			mTime -= Time.deltaTime;
		}
		if (mIsPlay) {
			if (mSource == null && mTime <= 0f) {
				mIsPlay = false;
				goToNextClicp ();
			}
		}
		((RectTransform)transform).SetAsLastSibling();
	}


	void init()
	{
		data = Resources.Load ("Gameplay/Popups/VoiceTutorial/" + dataToLoad) as VoiceTutorialData;
		currentDataId = 0;
		if (data == null || data.Clips.Length == 0) {

			if (onDone != null) {
				onDone ();
			}
			Destroy (gameObject);
			return;
		}

		updateImage ();
		updateBubble ();
		mAnimator.SetBool ("IsIn", true);
		if (imageBubble != null) {
			imageBubble.transform.localScale = Vector3.zero;
		}
	}

	void updateImage ()
	{
		if(imageMain != null && data != null && data.MainImage != null) {
			imageMain.sprite = data.MainImage;
		}
	}

	void updateBubble()
	{
		if (data.BubbleImages.Length > currentDataId) {
			if (imageBubbleText != null && data.BubbleImages [currentDataId] != null) {
				imageBubbleText.sprite = data.BubbleImages [currentDataId];
			}
		}
	}
	float mTime;

	void playClip()
	{
		if (data.Clips.Length > currentDataId) {
			AudioClip clip = data.Clips [currentDataId];
			if (clip != null) {
				mSource = AudioController.Instance.PlaySound (clip, true);
				mIsPlay = true;
			} else {
				mSource = null;
				mTime = data.DelayInterval;
				mIsPlay = true;
			}
		}
	}

	public void OnCloseClick()
	{

		mAnimator.SetBool ("IsIn", false);
		if (mSource) {
			mSource.Stop ();
		}
	}


	void onIn()
	{
		StartCoroutine (PopInBubble ());
	}

	void goToNextClicp()
	{
		currentDataId++;

		if (
			data.BubbleImages.Length <= currentDataId
			&&
			data.Clips.Length <= currentDataId) {
			StartCoroutine (PopOutBubble ());
		} else {
			updateBubble ();
			playClip ();
		}
	}

	IEnumerator PopInBubble(float speed=5f){

		imageBubble.transform.localScale = new Vector3 (0, 0, 0);

		float[] scales = new float[] { 0f, 1.1f, 0.9f, 1f };

		foreach (float destScale in scales)
		{
			Vector3 startScale = imageBubble.transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				imageBubble.transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			imageBubble.transform.localScale = endScale;
		}
		playClip ();
	}

	IEnumerator PopOutBubble(float speed=5f){

		imageBubble.transform.localScale = new Vector3 (1f, 1f, 1f);

		float[] scales = new float[] {0.9f, 1.1f, 0f};

		foreach (float destScale in scales)
		{
			Vector3 startScale = imageBubble.transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				imageBubble.transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			imageBubble.transform.localScale = endScale;
		}

		OnCloseClick ();
	}


	void onOut()
	{
		if (onDone != null) {
			onDone ();
		}
		Destroy (gameObject);
	}

}
