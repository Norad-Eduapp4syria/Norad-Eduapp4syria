﻿namespace EA4S.Tobogan
{
    public class ToboganResultGameState : IGameState
    {
        ToboganGame game;

        bool goToEndGame;

        float timer = 4;
        public ToboganResultGameState(ToboganGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            timer = 4;
            goToEndGame = false;

            game.Context.GetAudioManager().PlayMusic(Music.Relax);

            if (game.isTimesUp)
            {
                game.Context.GetPopupWidget().ShowTimeUp(OnPopupTimeUpCloseRequested);
            }

            // Show some animation
            if (game.CurrentScoreRecord == 0)
            {
                game.feedbackGraphics.ShowPoorPlayerPerformanceFeedback();
            }
        }

        public void ExitState() { }

        void OnPopupTimeUpCloseRequested()
        {
            game.Context.GetPopupWidget().Hide();
            timer = 1;
            goToEndGame = true;
        }

        public void Update(float delta)
        {
            if (!game.isTimesUp || goToEndGame)
                timer -= delta;

            if (timer < 0)
            {
                game.EndGame(game.CurrentStars, game.CurrentScoreRecord);
            }
        }

        public void UpdatePhysics(float delta) { }
    }
}
