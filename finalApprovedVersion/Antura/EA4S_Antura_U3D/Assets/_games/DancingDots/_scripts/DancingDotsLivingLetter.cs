﻿using UnityEngine;
using System.Collections;
using TMPro;

namespace EA4S.DancingDots
{

	public enum LivingLetterAnim {
		Nothing = 0,
		idle = 1,
		hold = 2,
		run = 3,
		walk = 4,
		ninja = 5
	}

	public class DancingDotsLivingLetter : MonoBehaviour
	{

		[Header("References")]
		public LetterObjectView letterObjectView;
		public TextMeshPro hintText;
		public TextMeshPro dotlessText;
		public GameObject fullTextGO, contentGO;

		public GameObject rainbow;
		public DancingDotsGame game;

		TextMeshPro fullText;

		ILivingLetterData letterData;

		void Start()
		{

			fullText = fullTextGO.GetComponent<TextMeshPro>();
			HideRainbow();
			PlayAnimation();
		}

		public void Reset()
		{
			SetupLetter();
			SpeakLetter();
		}

		void PlayAnimation()
		{
			letterObjectView.SetState(LLAnimationStates.LL_dancing);
		}

		void OnMouseUp()
		{
			if (letterData != null) 
			{
				AudioManager.I.PlayLetter(letterData.Id);
			}
		}

		void GetDiacritic()
		{
			Debug.Log("DD Get Diacritics");
			char FATHA1 = (char) 1611;
			char FATHA2 = (char) 1614;
			char DAMAH = (char) 1615;
			char KASRAH = (char) 1616;
			char SOUKON = (char) 1618;

			if (game.currentLetter.Contains(FATHA1.ToString()) ||
				game.currentLetter.Contains(FATHA2.ToString()))
			{
				game.letterDiacritic = DiacriticEnum.Fatha;
			}
			else if (game.currentLetter.Contains(DAMAH.ToString()))
			{
				game.letterDiacritic = DiacriticEnum.Dameh;
			}

			else if (game.currentLetter.Contains(KASRAH.ToString()))
			{
				game.letterDiacritic = DiacriticEnum.Kasrah;
			}

			else if (game.currentLetter.Contains(SOUKON.ToString()))
			{
				game.letterDiacritic = DiacriticEnum.Sokoun;
			}
			else
			{
				game.letterDiacritic = DiacriticEnum.None;
			}

			StartCoroutine(game.SetupDiacritic());

			string output = "";
			foreach (char c in game.currentLetter)
			{
				if (c != FATHA1 && c != FATHA2 && c != DAMAH && c != KASRAH && c != SOUKON)
				{
					output += c;
				}
			}
			game.currentLetter = output;
		}

		void SetupLetter()
		{
			letterData = game.questionsManager.getNewLetter();

			game.currentLetter = letterData.TextForLivingLetter;

			GetDiacritic();

			string lettersWithOneDot = "ج خ غ ف ض ب ن ز ذ ظ";
			string lettersWithTwoDots = "ة ق ي ت";
			string lettersWithThreeDots = "ث ش";

			if (lettersWithThreeDots.Contains(game.currentLetter))
			{
                game.dotsCount = 3;
			}
			else if (lettersWithTwoDots.Contains(game.currentLetter))
			{
                game.dotsCount = 2;
			}
			else if (lettersWithOneDot.Contains(game.currentLetter))
			{
                game.dotsCount = 1;
			}
			else
			{
                game.dotsCount = 0;
			}
					
			hintText.text = game.currentLetter;
			ShowText(hintText, game.dotHintAlpha);
			dotlessText.text = game.currentLetter;
			fullText.text = game.currentLetter;
			fullTextGO.SetActive(false);

		}

		public void HideText(TextMeshPro tmp)
		{
			tmp.color = game.SetAlpha(tmp.color,0);
		}

		public void ShowText(TextMeshPro tmp, byte alpha)
		{
			tmp.color = game.SetAlpha(tmp.color, alpha);
		}

		public void ShowRainbow()
		{
			rainbow.SetActive(true);
		}

		public void HideRainbow()
		{
			rainbow.SetActive(false);
		}

		private void SpeakLetter()
		{
			if (letterData != null && !game.isTutRound) {
				AudioManager.I.PlayLetter(letterData.Id);
			}
		}

//		public void HideAllText()
//		{
//			hintText.color = SetAlpha(hintText.color,0);
//			dotlessText.color = SetAlpha(dotlessText.color,0);
//			fullText.color = SetAlpha(fullText.color,0);
//		}
//
//		public void ShowAllText()
//		{
//			hintText.color = SetAlpha(hintText.color,DancingDotsGameManager.instance.dotHintAlpha);
//			dotlessText.color = SetAlpha(dotlessText.color,255);
//			fullText.color = SetAlpha(fullText.color,255);
//		}

	}
}