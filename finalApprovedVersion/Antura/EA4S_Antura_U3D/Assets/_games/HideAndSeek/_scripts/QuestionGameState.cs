﻿namespace EA4S.HideAndSeek
{
    public class QuestionGameState : IGameState
    {
		HideAndSeekGame game;
        
		public QuestionGameState(HideAndSeekGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            game.Context.GetAudioManager().PlayMusic(Music.Relax);
            // Show questions description
            var popupWidget = game.Context.GetPopupWidget();
            popupWidget.Show();
            popupWidget.SetButtonCallback(OnQuestionCompleted);
            popupWidget.SetMessage("");
        }

        public void ExitState()
        {
            game.Context.GetPopupWidget().Hide();
            game.Context.GetAudioManager().StopMusic();
        }

        void OnQuestionCompleted()
        {
            game.SetCurrentState(game.TutorialState);
        }

        public void Update(float delta) { }

        public void UpdatePhysics(float delta) { }
    }
}
