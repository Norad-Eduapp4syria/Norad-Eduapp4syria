﻿using System;
using UnityEngine;

namespace EA4S
{
    public class MinigamesOverlayWidget : IOverlayWidget
    {
        int firstStarsScoreThreshold = 1;
        int secondStarsScoreThreshold = 2;
        int thirdStarsScoreThreshold = 3;
        int score = 0;
        float timerDuration = 10;

        bool showStarsBar;
        bool showClock;
        bool showLives;

        public void Initialize(bool showStarsBar, bool showClock, bool showLives)
        {
            this.showStarsBar = showStarsBar;
            this.showClock = showClock;
            this.showLives = showLives;

            MinigamesUI.Init((showLives ? MinigamesUIElement.Lives : 0) |
               (showStarsBar ? MinigamesUIElement.Starbar : 0) |
               (showClock ? MinigamesUIElement.Timer : 0));
        }

        public void Reset()
        {
            this.showStarsBar = false;
            this.showClock = false;
            this.showLives = false;
        }

        public void SetStarsThresholds(int firstStarsScoreThreshold, int secondStarsScoreThreshold, int thirdStarsScoreThreshold)
        {
            if (!showStarsBar)
                return;

            this.firstStarsScoreThreshold = firstStarsScoreThreshold;
            this.secondStarsScoreThreshold = secondStarsScoreThreshold;
            this.thirdStarsScoreThreshold = thirdStarsScoreThreshold;
        }

        public void SetStarsScore(int score)
        {
            if (!showStarsBar)
                return;

            this.score = score;

            // Avoid floating point errors when setting UI
            // thresholds could have different "distances" between them

            if (score < firstStarsScoreThreshold)
                MinigamesUI.Starbar.Goto((score / (float)firstStarsScoreThreshold) * 0.333f);
            else if (score == firstStarsScoreThreshold)
                MinigamesUI.Starbar.GotoStar(0);
            else if (score < secondStarsScoreThreshold)
                MinigamesUI.Starbar.Goto(((score - firstStarsScoreThreshold) / (float)(secondStarsScoreThreshold - firstStarsScoreThreshold)) * 0.333f + 0.333f);
            else if (score == secondStarsScoreThreshold)
                MinigamesUI.Starbar.GotoStar(1);
            else if (score < thirdStarsScoreThreshold)
                MinigamesUI.Starbar.Goto(((score - secondStarsScoreThreshold) / (float)(thirdStarsScoreThreshold - secondStarsScoreThreshold)) * 0.333f + 0.666f);
            else
                MinigamesUI.Starbar.GotoStar(2);
        }

        public void SetClockDuration(float timerDuration)
        {
            if (!showClock)
                return;

            this.timerDuration = timerDuration;
            MinigamesUI.Timer.Setup(timerDuration, false);
        }

        public void SetClockTime(float currentTime)
        {
            if (!showClock)
                return;

            MinigamesUI.Timer.Goto(timerDuration - currentTime);
        }

        public void OnClockCompleted()
        {
            if (!showClock)
                return;

            MinigamesUI.Timer.Complete();
        }

        public void SetMaxLives(int maxLives)
        {
            if (!showLives)
                return;

            MinigamesUI.Lives.Setup(maxLives);
        }
        public void SetLives(int lives)
        {
            if (!showLives)
                return;

            MinigamesUI.Lives.SetCurrLives(lives);
        }
    }
}
