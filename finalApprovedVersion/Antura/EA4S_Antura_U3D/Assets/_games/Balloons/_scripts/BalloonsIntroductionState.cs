﻿namespace EA4S.Balloons
{
    public class BalloonsIntroductionState : IGameState
    {
        BalloonsGame game;

        float timer = 1.5f;
        bool playTutorial = true;
        bool takenAction = false;

        public BalloonsIntroductionState(BalloonsGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            game.PlayTitleVoiceOver();
        }

        public void ExitState()
        {
        }

        public void OnFinishedTutorial()
        {
            game.SetCurrentState(game.QuestionState);
        }

        public void Update(float delta)
        {
            if (takenAction)
            {
                return;
            }

            timer -= delta;

            if (timer < 0)
            {
                takenAction = true;

                if (playTutorial)
                {
                    this.game.PlayTutorial();
                }
                else
                {
                    game.SetCurrentState(game.QuestionState);
                }
            }
        }

        public void UpdatePhysics(float delta)
        {
        }
    }
}