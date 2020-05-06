﻿using System;
using System.Collections.Generic;
using UnityEngine;

namespace EA4S.FastCrowd
{
    public class StrollingLetterHangingState : StrollingLetterState
    {
        List<StrollingLivingLetter> near = new List<StrollingLivingLetter>();

        LetterCharacterController movement;

        public StrollingLetterHangingState(StrollingLivingLetter letter) : base(letter)
        {
            movement = letter.GetComponent<LetterCharacterController>();
        }

        public override void EnterState()
        {
            letter.gameObject.GetComponent<LetterObjectView>().SetState(LLAnimationStates.LL_dragging);
            
        }

        public override void ExitState()
        {
            letter.gameObject.GetComponent<LetterObjectView>().SetState(LLAnimationStates.LL_idle);
        }

        public override void Update(float delta)
        {
            // Scare neighbourhood
            near.Clear();
            letter.crowd.GetNearLetters(near, letter.transform.position, 5.0f);
            for (int i = 0, count = near.Count; i < count; ++i)
                near[i].Scare(letter.transform.position, 2);

            // Face Camera!
            movement.LerpLookAt(Camera.main.transform.position, 8*delta);
        }

        public override void UpdatePhysics(float delta)
        {
        }
    }
}
