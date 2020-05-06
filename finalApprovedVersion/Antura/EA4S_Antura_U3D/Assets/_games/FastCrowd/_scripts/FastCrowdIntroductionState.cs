﻿namespace EA4S.FastCrowd
{
    public class FastCrowdIntroductionState : IGameState
    {
        FastCrowdGame game;

        bool nextState;
        bool playIntro;

        public FastCrowdIntroductionState(FastCrowdGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            nextState = false;
            playIntro = false;

            if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Alphabet) {
                game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_alphabet_Title, () => { playIntro = true; });
            } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Counting) {
                game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_counting_Title, () => { playIntro = true; });
            } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Letter) {
                game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_letter_Title, () => { playIntro = true; });
            } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Spelling) {
                game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_spelling_Title, () => { playIntro = true; });
            } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Words) {
                game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_words_Title, () => { playIntro = true; });
            } else {
                nextState = true;
            }

            game.Context.GetAudioManager().PlayMusic(Music.Theme10);
        }

        public void ExitState() { }

        public void Update(float delta)
        {
            if (nextState) {
                nextState = false;
                game.SetCurrentState(game.QuestionState);
            }

            if (playIntro) {
                playIntro = false;

                if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Alphabet) {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_alphabet_Intro, () => { nextState = true; });
                } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Counting) {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_counting_Intro, () => { nextState = true; });
                } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Letter) {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_letter_Intro, () => { nextState = true; });
                } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Spelling) {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_spelling_Intro, () => { nextState = true; });
                } else if (FastCrowdConfiguration.Instance.Variation == FastCrowdVariation.Words) {
                    game.Context.GetAudioManager().PlayDialogue(Db.LocalizationDataId.FastCrowd_words_Intro, () => { nextState = true; });
                }
            }
        }

        public void UpdatePhysics(float delta) { }

    }
}