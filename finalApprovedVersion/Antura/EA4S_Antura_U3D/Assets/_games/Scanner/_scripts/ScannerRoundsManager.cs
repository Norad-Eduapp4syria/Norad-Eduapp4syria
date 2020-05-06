using UnityEngine;
using System.Collections.Generic;
using System;
using System.Linq;
using System.Collections;

namespace EA4S.Scanner
{
	public class ScannerRoundsManager {
		
		public event Action <int> onRoundsFinished;

		IAudioSource wordAudioSource;
        

		private int numberOfRoundsWon = 0;
		public int numberOfRoundsPlayed = -1;
		private int numberOfFailedMoves = 0;

		ScannerGame game;
		bool initialized = false;

		List <ILivingLetterData> wrongAnswers;
		List <ILivingLetterData> correctAnswers;

		enum Level { Level1, Level2, Level3, Level4, Level5, Level6 };

		private Level currentLevel = Level.Level4;

		public ScannerRoundsManager(ScannerGame game)
		{
			this.game = game;
		}

		public void Initialize()
		{
			if (!initialized)
			{
				/*if (ScannerConfiguration.Instance.Variation == ScannerVariation.MultipleWords)
				{
					numberOfRoundsPlayed = 0;
				}*/

				initialized = true;

				foreach (ScannerSuitcase ss in game.suitcases)
				{
					ss.onCorrectDrop += CorrectMove;
					ss.onWrongDrop += WrongMove;
				}

				Debug.Log("[Scanner] Diffculty: " + ScannerConfiguration.Instance.Difficulty);

				int LLs = 0;

				if (ScannerConfiguration.Instance.Variation == ScannerVariation.OneWord)
				{
					LLs = 1;
				}
				else if (ScannerConfiguration.Instance.Variation == ScannerVariation.MultipleWords)
				{
					LLs = game.LLCount;
				}

				Debug.Log("[Scanner] LLs: " + LLs);


				for (int i = 0; i < LLs; i++)
				{
					ScannerLivingLetter LL = GameObject.Instantiate(game.LLPrefab).GetComponent<ScannerLivingLetter>();
					LL.facingCamera = ScannerConfiguration.Instance.facingCamera;
					LL.gameObject.SetActive(true);
					LL.onStartFallOff += OnLetterStartFallOff;
					LL.onFallOff += OnLetterFallOff;
					LL.onPassedMidPoint += OnLetterPassedMidPoint;
					game.scannerLL.Add(LL);
				}

				StartRound();

			}
		}

		IEnumerator ResetLetters()
		{
			// Reset letters first so that they are set for this round
			// If not set first fall off will make unset letters fall with next round
			for (int i = 0; i < game.scannerLL.Count; i++)
			{
				game.scannerLL[i].Reset();
				game.scannerLL[i].letterObjectView.Init(correctAnswers[i]);

                if (game.scannerLL.Count == 3)
                    game.scannerLL[i].slidingTime = Time.time + 8 * i;
                else
                    game.scannerLL[i].slidingTime = Time.time + 5 * i;
            }

            // Then start sliding gardually
            for (int i = 0; i < game.scannerLL.Count; i++)
			{

                game.scannerLL[i].StartSliding();

                if (game.scannerLL.Count == 3)
				{   
                    yield return new WaitForSeconds(8f);
				}
				else
				{
                    yield return new WaitForSeconds(5f);
				}

			}

		}

		private void OnLetterPassedMidPoint(ScannerLivingLetter sender)
		{
			if (!game.trapDoor.GetBool("TrapDown") && !ScannerAntura.IS_IN_SCENE)
			{
				game.trapDoor.SetBool("TrapUp",false);
				game.trapDoor.SetBool("TrapDown", true);
			}
			// Decide if Antura will bark
			// Antura leaves
			// Trapdoor drops
		}

		private void AddDataToSuitcase (ScannerSuitcase ss, List <ILivingLetterData> fromList, bool isCorrect)
		{
			var ans = fromList.RandomSelectOne();
			ss.drawing.text = ans.DrawingCharForLivingLetter;
			ss.wordId = ans.Id;
			ss.isCorrectAnswer = isCorrect;
			fromList.Remove(ans);
		}

		private void SetupSuitCases()
		{

			Debug.Log("Number of suitcases: " + game.suitcases.Count);

			List <ILivingLetterData> tempCorrect = correctAnswers.ToList();

			for (int i = 0; i < game.suitcases.Count; i++)
			{
				ScannerSuitcase ss = game.suitcases[i];
				ss.Reset();

				if (tempCorrect.Count > 0 && wrongAnswers.Count > 0)
				{
					int coinFlip = UnityEngine.Random.Range(1,5);
					if (coinFlip == 1)
					{
						AddDataToSuitcase(ss,tempCorrect,true);
					}
					else
					{
						AddDataToSuitcase(ss,wrongAnswers,false);
					}

				} 
				else if (tempCorrect.Count > 0)
				{
					AddDataToSuitcase(ss,tempCorrect,true);
					ss.isCorrectAnswer = true;
				}
				else if (wrongAnswers.Count > 0)
				{
					AddDataToSuitcase(ss,wrongAnswers,false);
				}
					
			}
		}

		private void StartRound()
		{
			game.StopAllCoroutines();
			var provider = ScannerConfiguration.Instance.Questions;
			var question = provider.GetNextQuestion();
		    wrongAnswers = question.GetWrongAnswers().ToList();
			correctAnswers = question.GetCorrectAnswers().ToList();

			Debug.Log("Correct Answers: " + correctAnswers.Count);
			Debug.Log("Wrong   Answers: " + wrongAnswers.Count);


			game.wordData = correctAnswers;

			numberOfRoundsPlayed++;
			numberOfFailedMoves = 0;

//			if (ScannerConfiguration.Instance.Difficulty == 0f) // TODO for testing only each round increment Level. Remove later!
//			{
//				switch (numberOfRoundsPlayed)
//				{
//				case 1: 
//				case 2: currentLevel = Level.Level1;
//					break;
//				case 3: currentLevel = Level.Level4;
//					break;
//				case 4: currentLevel = Level.Level2;
//					break;
//				case 5: 
//				case 6: currentLevel = Level.Level3;
//					break;
//				default: currentLevel = Level.Level3;
//					break;
//				}
//			}
//			else
//			{
//				// TODO Move later to Start method
//				var numberOfLevels = Enum.GetNames(typeof(Level)).Length;
//				currentLevel = (Level) Mathf.Clamp((int) Mathf.Floor(game.pedagogicalLevel * numberOfLevels),0, numberOfLevels - 1);
//			}
//				
//			SetLevel(currentLevel);

			if (!game.trapDoor.GetBool("TrapUp"))
			{
				game.trapDoor.SetBool("TrapDown", false);
				game.trapDoor.SetBool("TrapUp",true);
			}

			game.StartCoroutine(ResetLetters());
			game.scannerDevice.Reset();
			SetupSuitCases();

            game.tut.setupTutorial();
		}

		public void CorrectMove(GameObject GO, ScannerLivingLetter livingLetter)
		{
			AudioManager.I.PlayDialog("Keeper_Good_" + UnityEngine.Random.Range(1, 12));
			livingLetter.RoundWon();
			if (game.scannerLL.All(ll => ll.gotSuitcase))
			{
				if (ScannerConfiguration.Instance.Variation == ScannerVariation.OneWord)
				{
					game.StartCoroutine(PoofOthers(game.suitcases));
				}

				foreach (ScannerLivingLetter LL in game.scannerLL)
				{
                    LL.gotSuitcase = false;
				}
				game.StartCoroutine(RoundWon());
			}

		}

		public void WrongMove(GameObject GO)
		{
			numberOfFailedMoves++;
			AudioManager.I.PlayDialog("Keeper_Bad_" + UnityEngine.Random.Range(1, 6));
			game.CreatePoof(GO.transform.position,2f,true);

            if (game.tut.isTutRound)
            {
                GO.GetComponent<ScannerSuitcase>().Reset();
                return;
            }

            GO.SetActive(false);

			if (numberOfFailedMoves >= game.allowedFailedMoves || 
				ScannerConfiguration.Instance.Variation == ScannerVariation.MultipleWords)
			{
				game.StopAllCoroutines();

				game.StartCoroutine(RoundLost());
			}

		}

		IEnumerator co_CheckNewRound()
		{
			yield return new WaitForSeconds(2f);

			if (numberOfRoundsPlayed >= game.numberOfRounds)
			{
				onRoundsFinished(numberOfRoundsWon);
			}
			else
			{
				yield return new WaitForSeconds(2f);
				StartRound();
			}
		}

		private void OnLetterStartFallOff(ScannerLivingLetter sender)
		{
//			AudioManager.I.PlaySfx(Sfx.Lose);
//			game.StartCoroutine(PoofOthers(game.suitcases));
//			game.StartCoroutine(RoundLost());

		}


		private void OnLetterFallOff(ScannerLivingLetter sender)
		{
//			game.StartCoroutine(co_CheckNewRound());
			game.StartCoroutine(RoundLost());
		}

		IEnumerator RoundLost()
		{
			yield return new WaitForSeconds(0.5f);
			AudioManager.I.PlaySfx(Sfx.Lose);
			foreach (ScannerLivingLetter LL in game.scannerLL)
			{
				LL.RoundLost();
			}
			game.StartCoroutine(PoofOthers(game.suitcases));

			game.StartCoroutine(co_CheckNewRound());

		}

		IEnumerator RoundWon()
		{
            if(!game.tut.isTutRound)
			    numberOfRoundsWon++;

			game.Context.GetOverlayWidget().SetStarsScore(numberOfRoundsWon);

			yield return new WaitForSeconds(0.25f);
			AudioManager.I.PlaySfx(Sfx.Win);
//			foreach (ScannerLivingLetter LL in game.scannerLL)
//			{
//				LL.RoundWon();
//			}

			game.StartCoroutine(co_CheckNewRound());

		}

		IEnumerator PoofOthers(List <ScannerSuitcase> draggables)
		{
			foreach (ScannerSuitcase ss in draggables)
			{
				if (ss.gameObject.activeSelf && 
					(!ss.isCorrectAnswer || ScannerConfiguration.Instance.Variation == ScannerVariation.MultipleWords))
				{
					yield return new WaitForSeconds(0.25f);
					ss.gameObject.SetActive(false);
                    ss.shadow.SetActive(false);
					game.CreatePoof(ss.transform.position, 2f, true);
				}
			}
		}


		public Color32 SetAlpha(Color32 color, byte alpha)
		{
			if (alpha >= 0 && alpha <= 255)
			{
				return new Color32(color.r, color.g, color.b, alpha);
			}
			else
			{
				return color;
			}
		}




		private void SetLevel(Level level)
		{
			//TODO Different levels
			switch (level)
			{
			case Level.Level1 :
				break;

			case Level.Level2 : 
				break;

			case Level.Level3 :
				break;

			case Level.Level4 : 
				break;

			case Level.Level5 : 
				break;

			case Level.Level6 :
				break;

			default:
				SetLevel(Level.Level1);
				break;

			}
		}
	}

}
