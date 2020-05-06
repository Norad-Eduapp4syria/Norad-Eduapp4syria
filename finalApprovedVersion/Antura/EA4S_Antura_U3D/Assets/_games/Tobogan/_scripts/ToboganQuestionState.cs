﻿namespace EA4S.Tobogan
{
    public class ToboganQuestionState : IGameState
    {
        ToboganGame game;

        bool nextState;
        bool playIntro;

        public ToboganQuestionState(ToboganGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            game.questionsManager.Initialize();
            nextState = false;
            playIntro = false;

            if (ToboganConfiguration.Instance.Variation == ToboganVariation.LetterInAWord)
            {
                game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.Tobogan_letters_Title, delegate ()
                {
                    playIntro = true;
                });
            }
            else
            {
                game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.Tobogan_words_Title, delegate ()
                {
                    playIntro = true;
                });
            }

            game.Context.GetAudioManager().PlayMusic(Music.Theme6);
        }

        public void ExitState() { }

        public void Update(float delta)
        {
            if (nextState)
            {
                if (game.showTutorial)
                {
                    game.SetCurrentState(game.TutorialState);
                }
                else
                {
                    game.SetCurrentState(game.PlayState);
                }
                return;
            }

            if(playIntro)
            {
                playIntro = false;

                if (ToboganConfiguration.Instance.Variation == ToboganVariation.LetterInAWord)
                {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.Tobogan_letters_Intro, delegate ()
                    {
                        nextState = true;
                    });
                }
                else
                {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.Tobogan_letters_Intro, delegate ()
                    {
                        nextState = true;
                    });
                }
            }
        }

        public void UpdatePhysics(float delta) { }
    }
}