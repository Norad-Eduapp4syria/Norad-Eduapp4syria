using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class NeededLettersAnimation  {

	Text mTarget;
	int mDefaultSize;
	int mPopSize;
	float mTimeStarted;
	float mLength;
	bool mRunning;
	int mLastIndex;
	float mLastTimeSine;

	MonsterCalloutController mController;


	public NeededLettersAnimation(Text target, MonsterCalloutController controller)
	{
		mTarget = target;
		mController = controller;
		mDefaultSize = mTarget.fontSize;
		mPopSize = (int)(mDefaultSize * 1.25f);
	}

	public void Show(float length)
	{
		mTimeStarted = Time.time;
		mLastTimeSine = Time.time;
		mLength = length;
		Timer.Instance.Create (new Timer.TimerCommand (Time.time, 0.01f, Update));
		mLastIndex = 0;
		mRunning = true;
	}

	void Update()
	{
		float lerpRate = Mathf.Abs(Mathf.Sin((Time.time - mLastTimeSine) * 3f));

		if (mRunning) {
			SetSize ((int)((float)mDefaultSize * (1f - lerpRate) + (float)mPopSize * lerpRate));
			if (Time.time >= mTimeStarted + mLength) {
				SetSize (mDefaultSize);
				mRunning = false;
			}
		}
	}

	void SetSize(int sizeForNeededLetters)
	{
		string richTextForUI = "";
		string letter;
		int currentIndex;
		switch (GameplayController.Instance.CurrentLevel.monsterInputType) {
		case MonsterInputType.Letter:
//			letter = GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [0];
			letter = GameplayController.Instance.CurrentSegment.GetFixRequiredLetters(0);
//			letter = ArabicSupport.ArabicFixer.Fix(letter, true, true);
//			letter = RTL.Fix(letter);

			richTextForUI += StringWithColorTags (StringWithBoldTags (StringWithSizeTags (letter, sizeForNeededLetters)), mController.FontColorLetter);
			break;
		case MonsterInputType.LetterInWord:
			for (int i= GameplayController.Instance.CurrentSegment.MonsterAllLetters.Length-1; i>=0; i--) {
				//letter = GameplayController.Instance.CurrentSegment.MonsterAllLetters [i];
				letter = GameplayController.Instance.CurrentSegment.GetFixAllLetters(i);

				if (letter == "X") {
					//letter = GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [0];
					letter = GameplayController.Instance.CurrentSegment.GetFixRequiredLetters(0);
				}

//				letter = ArabicSupport.ArabicFixer.Fix(letter, true, true);
//				letter = RTL.Fix(letter);
				if (GameplayController.Instance.CurrentSegment.MonsterAllLetters [i] == "X") {
					richTextForUI += StringWithColorTags (StringWithBoldTags (StringWithSizeTags (letter, sizeForNeededLetters)), 							   mController.FontColorWordBold);
				} else {
					richTextForUI += StringWithColorTags (StringWithBoldTags (StringWithSizeTags (letter, mDefaultSize)), 									   mController.FontColorWordDefault);
				}
			}
			break;

		case MonsterInputType.Word:
			currentIndex = (int)(((Time.time - mTimeStarted) / mLength) * (float)GameplayController.Instance.CurrentSegment.MonsterRequiredLetters.Length);

			if (currentIndex > mLastIndex) {
				mLastTimeSine = Time.time;
			}

			for (int i = GameplayController.Instance.CurrentSegment.MonsterRequiredLetters.Length - 1; i >= 0; i--) {
//				letter = ArabicSupport.ArabicFixer.Fix(GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [i], true, true);
				letter = GameplayController.Instance.CurrentSegment.GetFixRequiredLetters(i);
				//letter = RTL.Fix(GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [i]);

				if (i == currentIndex) {
					richTextForUI += StringWithColorTags (StringWithBoldTags (StringWithSizeTags (letter, sizeForNeededLetters)), mController.FontColorWordBold);
				} else if (i <= mLastIndex) {
					richTextForUI += StringWithColorTags (StringWithBoldTags (StringWithSizeTags (letter, mDefaultSize)), mController.FontColorWordBold);
				} else if (i > mLastIndex) {
					richTextForUI += StringWithColorTags (StringWithSizeTags (letter, mDefaultSize), mController.FontColorWordDefault);
				}
			}
			mLastIndex = currentIndex;
			break;
		}

		if (mTarget != null)
			mTarget.text = richTextForUI;
	}

	string StringWithSizeTags(string str, int size)
	{
		return "<size="+size+">" + str + "</size>";
	}

	string StringWithBoldTags(string str)
	{
		return str;
		return "<b>" + str + "</b>";
	}

	string StringWithColorTags(string str, Color color)
	{
		return "<color="+ColorToHexStr(color)+">" + str + "</color>";
	}

	string ColorToHexStr(Color color)
	{
		var _R = (byte)(color.r * 255f);
		var _G = (byte)(color.g * 255f);
		var _B = (byte)(color.b * 255f);

		return string.Format("#{0:X2}{1:X2}{2:X2}", _R, _G, _B);
	}


	int lastIndex = 0;
	public void UnMarkFirstLetter()
	{
		string richTextForUI = "";
		string letter;

		if(GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.Word) {
			for (int i = GameplayController.Instance.CurrentSegment.MonsterRequiredLetters.Length - 1; i >= 0; i--) {
				//letter = ArabicSupport.ArabicFixer.Fix (GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [i], true, true);
				letter = RTL.Fix (GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [i]);
				if (i <= lastIndex) {
					richTextForUI += StringWithColorTags (StringWithBoldTags (StringWithSizeTags (letter, mDefaultSize)), mController.FontColorWordDefault);
				} else {
					richTextForUI += StringWithColorTags (StringWithBoldTags (StringWithSizeTags (letter, mDefaultSize)), mController.FontColorWordBold);
				}
			}
			if (mTarget != null) {
				mTarget.text = richTextForUI;
			}
			lastIndex++;
		}
	}
}
