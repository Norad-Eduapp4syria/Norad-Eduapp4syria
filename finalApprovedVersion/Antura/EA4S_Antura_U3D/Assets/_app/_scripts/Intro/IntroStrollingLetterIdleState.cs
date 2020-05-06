﻿using UnityEngine;

namespace EA4S.FastCrowd
{
    public class IntroStrollingLetterIdleState : IntroStrollingLetterState
    {
        public IntroStrollingLetterIdleState(IntroStrollingLetter letter) : base(letter)
        {

        }

        float timer = 0.0f;
        public override void EnterState()
        {
            // Set letter animation
            letter.gameObject.GetComponent<LetterObjectView>().SetState(LLAnimationStates.LL_idle);

            // Wait a random time in idle
            timer = 1.0f + 3.0f * UnityEngine.Random.value;
        }

        public override void ExitState()
        {
        }

        public override void Update(float delta)
        {
            timer -= delta;

            if (timer < 0)
            {
                letter.SetCurrentState(letter.WalkingState);
            }
        }

        public override void UpdatePhysics(float delta)
        {
        }
    }
}
