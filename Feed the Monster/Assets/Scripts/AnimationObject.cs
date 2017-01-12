using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System;
using System.Collections.Generic;

[System.Serializable]
public class AnimationObject {
	public enum AnimationType
	{
		Dissolve,
		Sequence
	}

	public AnimationType Type;
	public string SpritesPathInResourcesFolder; 
	public string SpritePrefixFileName;

	const float FPS = 30;

	int mCurrentIndex;
	Action mCallback;
	Image mTarget;

	public void Play (Image target, Action callback)
	{
		mTarget = target;
		mCallback = callback;
		mCurrentIndex = 0;
		Timer.Instance.Create (new Timer.TimerCommand (Time.time, 1f / FPS, Frame));
	}

	void Frame()
	{
		Sprite currentSprite = Resources.Load (SpritesPathInResourcesFolder + "/" + SpritePrefixFileName + mCurrentIndex) as Sprite;
		if (currentSprite != null) {
			mTarget.sprite = currentSprite;
			mCurrentIndex++;
		} else {
			Stop ();
		}
	}

	void Stop()
	{
		Timer.Instance.Remove (Frame);
		mCallback.Invoke ();
	}

	void OnDisable()
	{
		Stop ();
	}
}
