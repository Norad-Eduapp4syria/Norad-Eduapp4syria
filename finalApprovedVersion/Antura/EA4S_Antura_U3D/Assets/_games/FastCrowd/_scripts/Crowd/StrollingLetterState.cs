﻿namespace EA4S
{
    public abstract class StrollingLetterState : IGameState
    {
        protected StrollingLivingLetter letter;

        public StrollingLetterState(StrollingLivingLetter letter)
        {
            this.letter = letter;
        }

        public abstract void EnterState();
        public abstract void ExitState();
        public abstract void Update(float delta);
        public abstract void UpdatePhysics(float delta);
    }
}
