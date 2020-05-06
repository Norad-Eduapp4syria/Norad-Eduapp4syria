﻿using System;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

namespace EA4S.FastCrowd
{
    public class FastCrowdGame : MiniGame
    {
        public QuestionManager QuestionManager;

        public AnturaRunnerController antura;

        public List<ILivingLetterData> CurrentChallenge = new List<ILivingLetterData>();
        public List<ILivingLetterData> NoiseData = new List<ILivingLetterData>();

        public IQuestionPack CurrentQuestion = null; // optional

        private int currentScore;
        public int CurrentScore
        {
            get
            {
                return currentScore;
            }
            private set
            {
                currentScore = value;
                Context.GetOverlayWidget().SetStarsScore(currentScore);
            }
        }

        public int QuestionNumber = 0;

        [HideInInspector]
        public bool isTimesUp;

        int stars1Threshold
        {
            get
            {
                switch (FastCrowdConfiguration.Instance.Variation)
                {
                    case FastCrowdVariation.Words:
                        return 8;
                    default:
                        return 5;
                }
            }
        }

        int stars2Threshold
        {
            get
            {
                return 10;
            }
        }

        int stars3Threshold
        {
            get
            {
                return 15;
            }
        }


        public int CurrentStars
        {
            get
            {
                if (CurrentScore < stars1Threshold)
                    return 0;
                if (CurrentScore < stars2Threshold)
                    return 1;
                if (CurrentScore < stars3Threshold)
                    return 2;
                return 3;
            }
        }

        public bool showTutorial { get; set; }

        public FastCrowdIntroductionState IntroductionState { get; private set; }
        public FastCrowdQuestionState QuestionState { get; private set; }
        public FastCrowdPlayState PlayState { get; private set; }
        public FastCrowdResultState ResultState { get; private set; }
        public FastCrowdEndState EndState { get; private set; }
        public FastCrowdTutorialState TutorialState { get; private set; }

        public void ResetScore()
        {
            CurrentScore = 0;
        }

        public void IncrementScore()
        {
            ++CurrentScore;
        }

        protected override IGameConfiguration GetConfiguration()
        {
            return FastCrowdConfiguration.Instance;
        }

        protected override IGameState GetInitialState()
        {
            return IntroductionState;
        }

        protected override void OnInitialize(IGameContext context)
        {
            //float difficulty = FastCrowdConfiguration.Instance.Difficulty;

            showTutorial = true;

            IntroductionState = new FastCrowdIntroductionState(this);
            QuestionState = new FastCrowdQuestionState(this);
            PlayState = new FastCrowdPlayState(this);
            ResultState = new FastCrowdResultState(this);
            EndState = new FastCrowdEndState(this);
            TutorialState = new FastCrowdTutorialState(this);

            QuestionManager.wordComposer.gameObject.SetActive(
                FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Spelling
                );
        }


        public bool ShowChallengePopupWidget(bool showAsGoodAnswer, Action callback)
        {
            if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Spelling)
            {
                var popupWidget = Context.GetPopupWidget();
                popupWidget.Show();
                popupWidget.SetButtonCallback(callback);

                if (showAsGoodAnswer)
                {
                    popupWidget.SetTitle(Db.LocalizationDataId.Keeper_Good_5);
                    popupWidget.SetMark(true, true);
                }
                else
                    popupWidget.SetTitle("" + QuestionNumber);

                var question = CurrentQuestion.GetQuestion();
                popupWidget.SetLetterData(question);
                Context.GetAudioManager().PlayLetterData(question);
                return true;
            }
            return false;
        }

        public void InitializeOverlayWidget()
        {
            Context.GetOverlayWidget().Initialize(true, true, false);
            Context.GetOverlayWidget().SetStarsThresholds(stars1Threshold, stars2Threshold, stars3Threshold);
        }

        public override Vector3 GetGravity()
        {
            return Vector3.up * (-40);
        }
    }
}