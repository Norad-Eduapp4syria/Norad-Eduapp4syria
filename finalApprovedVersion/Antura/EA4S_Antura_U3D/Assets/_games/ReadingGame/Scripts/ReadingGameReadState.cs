﻿using System;
using UnityEngine;

namespace EA4S.ReadingGame
{
    public class ReadingGameReadState : IGameState
    {
        public bool TutorialMode = false;

        CountdownTimer gameTime = new CountdownTimer(90.0f);
        ReadingGameGame game;
        IAudioSource timesUpAudioSource;

        bool hurryUpSfx;

        bool completedDragging = false;
        ReadingBar dragging;
        Vector2 draggingOffset;

        // song related
        float timeFarFromTarget = 0;
        float scoreAccumulator = 0;

        // tutorial
        float drawTutorialLineTimer = 0;
        bool firstRealRun = true;

        public ReadingGameReadState(ReadingGameGame game)
        {
            this.game = game;

            gameTime.onTimesUp += OnTimesUp;
        }

        public void EnterState()
        {
            game.antura.AllowSitting = true;
            game.isTimesUp = false;

            // Reset game timer
            gameTime.Reset(game.TimeToAnswer);

            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
            {
                if (!TutorialMode)
                {
                    gameTime.Start();
                }
                else
                {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.ReadingGame_Tuto);
                    drawTutorialLineTimer = 0;
                }
            }

            hurryUpSfx = false;

            var inputManager = game.Context.GetInputManager();

            inputManager.onPointerDown += OnPointerDown;
            inputManager.onPointerUp += OnPointerUp;

            game.blurredText.SetActive(true);
            //game.circleBox.SetActive(false);

            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.AlphabetSong)
            {
                game.barSet.PlaySong(game.Context.GetAudioManager().PlaySound(game.alphabetSongAudio), OnSongEnded);
            }

            completedDragging = false;

            if (firstRealRun)
            {
                bool isSong = (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.AlphabetSong);

                if (!TutorialMode)
                {
                    // Configure overlay
                    var overlay = game.Context.GetOverlayWidget();
                    overlay.Initialize(true, !isSong, !isSong);
                    overlay.SetMaxLives(game.Lives);
                    overlay.SetLives(game.Lives);
                    overlay.SetClockDuration(gameTime.Duration);
                    overlay.SetClockTime(gameTime.Time);
                    overlay.SetStarsThresholds(game.GetStarsThreshold(1), game.GetStarsThreshold(2), game.GetStarsThreshold(3));

                    firstRealRun = false;
                }
            }

            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
                game.barSet.SwitchToNextBar();

            game.barSet.active = true;
        }


        public void ExitState()
        {
            TutorialMode = false;

            var inputManager = game.Context.GetInputManager();

            inputManager.onPointerDown -= OnPointerDown;
            inputManager.onPointerUp -= OnPointerUp;

            if (timesUpAudioSource != null)
                timesUpAudioSource.Stop();

            gameTime.Stop();

            game.barSet.active = false;
            game.barSet.Clear();
            game.blurredText.SetActive(false);
        }

        public void Update(float delta)
        {
            if (!TutorialMode)
                game.Context.GetOverlayWidget().SetClockTime(gameTime.Time);
            else if (dragging == null)
            {
                drawTutorialLineTimer -= delta;

                if (drawTutorialLineTimer < 0)
                {
                    var activeBar = game.barSet.GetActiveBar();

                    if (activeBar != null)
                    {
                        drawTutorialLineTimer = 5;
                        TutorialUI.DrawLine(activeBar.start.transform.position, activeBar.endCompleted.transform.position, TutorialUI.DrawLineMode.FingerAndArrow, false, true);
                    }
                }
            }

            if (!hurryUpSfx)
            {
                if (gameTime.Time < 4f)
                {
                    hurryUpSfx = true;

                    timesUpAudioSource = game.Context.GetAudioManager().PlaySound(Sfx.DangerClockLong);
                }
            }

            gameTime.Update(delta);

            if (dragging != null)
            {
                var inputManager = game.Context.GetInputManager();
                completedDragging = dragging.SetGlassScreenPosition(inputManager.LastPointerPosition + draggingOffset,
                    ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer);
            }
            else
            {
                if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
                {

                    if (completedDragging)
                    {
                        var completedAllBars = game.barSet.SwitchToNextBar();

                        if (completedAllBars)
                        {
                            // go to Buttons State
                            game.AnswerState.ReadTime = gameTime.Time;
                            game.AnswerState.MaxTime = gameTime.Duration;
                            game.AnswerState.TutorialMode = TutorialMode;
                            game.SetCurrentState(game.AnswerState);
                            return;
                        }
                    }

                    completedDragging = false;
                }
            }


            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
            {
                float perc = gameTime.Time / gameTime.Duration;

                if (perc < 0.05f)
                    game.antura.Mood = ReadingGameAntura.AnturaMood.SAD;
                else if (perc < 0.5f)
                    game.antura.Mood = ReadingGameAntura.AnturaMood.ANGRY;
                else
                    game.antura.Mood = ReadingGameAntura.AnturaMood.HAPPY;
            }
            else // Alphabet Song
            {
                float distance;
                if (game.barSet.GetFollowingDistance(out distance))
                {
                    distance = Math.Abs(distance);

                    if (distance > 100)
                    {
                        timeFarFromTarget += delta;
                    }
                    else
                    {
                        timeFarFromTarget = 0;
                        if (distance < 50)
                            scoreAccumulator += 1.15f * delta;
                        else
                            scoreAccumulator += 1 * delta;

                        if (scoreAccumulator >= 1)
                        {
                            game.AddScore((int)scoreAccumulator);
                            scoreAccumulator = scoreAccumulator - (int)scoreAccumulator;
                        }
                    }

                    if (timeFarFromTarget > 1.0f)
                        game.antura.Mood = ReadingGameAntura.AnturaMood.ANGRY;
                    else
                        game.antura.Mood = ReadingGameAntura.AnturaMood.HAPPY;
                }
            }
        }

        public void UpdatePhysics(float delta)
        {

        }

        void OnTimesUp()
        {
            // Time's up!
            game.barSet.active = false;
            game.isTimesUp = true;
            game.Context.GetOverlayWidget().OnClockCompleted();

            if (game.RemoveLife())
                return;

            // show time's up and back
            game.Context.GetPopupWidget().ShowTimeUp(
                () =>
                {
                    game.SetCurrentState(game.QuestionState);
                    game.Context.GetPopupWidget().Hide();
                });
        }

        void OnPointerDown()
        {
            if (dragging)
                return;

            var inputManager = game.Context.GetInputManager();
            dragging = game.barSet.PickGlass(Camera.main, inputManager.LastPointerPosition);

            if (dragging != null)
                draggingOffset = dragging.GetGlassScreenPosition() - inputManager.LastPointerPosition;
        }

        void OnPointerUp()
        {
            dragging = null;
        }

        void OnSongEnded()
        {
            game.EndGame(game.CurrentStars, game.CurrentScore);
        }
    }
}