﻿using System;
using UnityEngine;

namespace EA4S.ReadingGame
{
    public class ReadingGameQuestionState : IGameState
    {
        ReadingGameGame game;
        bool firstRun = true;
        bool completed = false;

        public ReadingGameQuestionState(ReadingGameGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            game.antura.AllowSitting = true;
            game.isTimesUp = false;

            if (game.CurrentQuestionNumber >= ReadingGameGame.MAX_QUESTIONS)
            {
                game.EndGame(game.CurrentStars, game.CurrentScore);
                return;
            }

            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
            {
                game.Context.GetOverlayWidget().SetClockDuration(game.TimeToAnswer);
                game.Context.GetOverlayWidget().SetClockTime(game.TimeToAnswer);
            }

            game.blurredText.SetActive(true);
            //game.circleBox.SetActive(false);

            if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
            {
                // Pick a question
                var pack = ReadingGameConfiguration.Instance.Questions.GetNextQuestion();
                game.CurrentQuestion = pack;
                if (pack != null)
                    game.barSet.SetData(pack.GetQuestion());
                else
                    game.EndGame(game.CurrentStars, game.CurrentScore);
            }
            else
            {
                game.barSet.SetShowTargets(ReadingGameConfiguration.Instance.Difficulty < 0.3f);
                game.barSet.SetShowArrows(ReadingGameConfiguration.Instance.Difficulty < 0.6f);

                game.barSet.SetData(game.alphabetSong);
            }

            game.barSet.active = false;

            if (firstRun)
            {
                if (ReadingGameConfiguration.Instance.Variation == ReadingGameVariation.ReadAndAnswer)
                {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.ReadingGame_Intro, () => { completed = true; });
                    game.ReadState.TutorialMode = true;
                }
                else
                {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.AlphabetSong_Intro, () =>
                    {
                        var firstBar = game.barSet.GetNextBar();
                        TutorialUI.DrawLine(firstBar.start.transform.position, firstBar.endCompleted.transform.position, TutorialUI.DrawLineMode.FingerAndArrow, false, true);

                        game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.AlphabetSong_Tuto, () =>
                        {
                            completed = true;
                        });
                    });
                }
            }
            else
            {
                ++game.CurrentQuestionNumber;
                completed = true;
                game.ReadState.TutorialMode = false;
            }

            firstRun = false;
        }

        public void ExitState()
        {

        }

        public void Update(float delta)
        {
            if (completed)
                game.SetCurrentState(game.ReadState);
        }

        public void UpdatePhysics(float delta)
        {

        }
    }
}

