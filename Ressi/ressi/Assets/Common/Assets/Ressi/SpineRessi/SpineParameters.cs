using Spine.Unity;
using System;
using UnityEngine;

namespace Assets.Common.Assets.Ressi.SpineRessi
{
    [Serializable]
    public class SpineParameters
    {
        [Header("Idle Animations")]
        [SpineAnimation]
        public string StandardIdle;
        public AnimationWithSound[] LowResilienceIdle;

        [Header("Movement Animations")]
        [SpineAnimation]
        public string StandardWalkAnimation;

        [Header("Chasing Consumable")]
        [SpineAnimation]
        public string ChaseConsumableAnimation;
        [SpineSlot]
        public string MouthSlot;
        [SpineAttachment]
        public string ChaseMouthAttachment;

        [Header("Eating Animations")]
        public AnimationWithSound NegativeEatingAnimation;
        public AnimationWithSound PositiveEatingAnimation;

        [Header("Activity Animations")]
        public AnimationWithSound CompleteActivityAnimation;
        public AnimationWithSound FailActivityAnimation;
        public AnimationWithSound PointLeftActivityAnimation;
        public AnimationWithSound PointLeftActivityAnimationModerate;
        public AnimationWithSound PointRightActivityAnimation;

        [Header("Drawing Activity Animations")]
        public AnimationWithSound DrawingHint;
        public AnimationWithSound DrawingWait;
        public AnimationWithSound DrawingSad;
        public AnimationWithSound DrawingHappy;

        [Header("Playtime Responses")]
        public AnimationWithSound PokeAnimation;
        public AnimationWithSound StrokeAnimation;
        public AnimationWithSound HighFive;

        [Header("Evaluation")]
        public AnimationWithSound BestEvaluation;
        public AnimationWithSound GoodEvaluation;
        public AnimationWithSound NeutralEvaluation;
        public AnimationWithSound WorseEvaluation;
        public AnimationWithSound NotFinishedEvaluation;
    }
}
