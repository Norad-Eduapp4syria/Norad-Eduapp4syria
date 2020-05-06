﻿using System;
using System.IO;
using System.Text;
using TMPro;
using UnityEngine;

namespace EA4S.ReadingGame
{
    public class ReadingGameGame : MiniGame // ReadingGameGameGameGameGame!
    {
        public ReadingBarSet barSet;
        public GameObject blurredText;
        public GameObject circleBox;
        public ReadingGameAntura antura;
        public ReadingRadialWidget radialWidget;
        public Camera uiCamera;

        public int CurrentScore { get; private set; }
        public int CurrentQuestionNumber { get; set; }

        [HideInInspector]
        public bool isTimesUp;

        int lives = 3;
        public int Lives { get { return lives; } }

        [HideInInspector]
        public KaraokeSong alphabetSong;
        public AudioClip alphabetSongAudio;
        public TextAsset alphabetSongSrt;

        public int TimeToAnswer
        {
            get
            {
                return Mathf.RoundToInt(30 - 20 * ReadingGameConfiguration.Instance.Difficulty);
            }
        }

        public const int MAX_QUESTIONS = 5;
        static readonly float[] READING_STARS_THRESHOLDS_RATIOS = new float[] { 0.4f, 0.55f, 0.7f };

        public int GetStarsThreshold(int stars)
        {
            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
            {
                return Mathf.FloorToInt(MAX_QUESTIONS * TimeToAnswer * READING_STARS_THRESHOLDS_RATIOS[stars - 1]);
            }

            if (alphabetSong == null)
                return int.MaxValue;

            var t = (int)(alphabetSong.GetSegmentsLength() / (4 - stars));
            return t;
        }

        public int CurrentStars
        {
            get
            {
                if (CurrentScore < GetStarsThreshold(1))
                    return 0;
                if (CurrentScore < GetStarsThreshold(2))
                    return 1;
                if (CurrentScore < GetStarsThreshold(3))
                    return 2;
                return 3;
            }
        }

        public ReadingGameInitialState InitialState { get; private set; }
        public ReadingGameQuestionState QuestionState { get; private set; }
        public ReadingGameReadState ReadState { get; private set; }
        public ReadingGameAnswerState AnswerState { get; private set; }
        public IQuestionPack CurrentQuestion { get; set; }

        protected override IGameConfiguration GetConfiguration()
        {
            return ReadingGameConfiguration.Instance;
        }

        protected override IGameState GetInitialState()
        {
            return InitialState;
        }

        protected override void OnInitialize(IGameContext context)
        {
            InitialState = new ReadingGameInitialState(this);
            QuestionState = new ReadingGameQuestionState(this);
            ReadState = new ReadingGameReadState(this);
            AnswerState = new ReadingGameAnswerState(this);

            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.AlphabetSong)
            {
                ISongParser parser = new AkrSongParser();

                using (MemoryStream stream = new MemoryStream(Encoding.UTF8.GetBytes(alphabetSongSrt.text)))
                {
                    alphabetSong = new KaraokeSong(parser.Parse(stream));
                }
            }

            radialWidget.Hide();
        }

        public void AddScore(int score)
        {
            CurrentScore += score;

            Context.GetOverlayWidget().SetStarsScore(CurrentScore);
        }

        public bool RemoveLife()
        {
            --lives;
            Context.GetOverlayWidget().SetLives(lives);

            if (lives == 0)
            {
                EndGame(CurrentStars, CurrentScore);
                return true;
            }
            return false;
        }
    }
}