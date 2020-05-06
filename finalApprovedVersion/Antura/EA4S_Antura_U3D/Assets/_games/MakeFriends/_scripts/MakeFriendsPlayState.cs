﻿namespace EA4S.MakeFriends
{
    public class MakeFriendsPlayState : IGameState
    {
        MakeFriendsGame game;

        public MakeFriendsPlayState(MakeFriendsGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            MakeFriendsConfiguration.Instance.Context.GetOverlayWidget().Initialize(showStarsBar: true, showClock: false, showLives: false);

            game.PlayIntroVoiceOver();
            game.PlayActiveMusic();
            game.Play();
        }

        public void ExitState()
        {
        }

        public void OnResult()
        {
            game.SetCurrentState(game.ResultState);
        }

        public void Update(float delta)
        {
        }

        public void UpdatePhysics(float delta)
        {
        }
    }
}
