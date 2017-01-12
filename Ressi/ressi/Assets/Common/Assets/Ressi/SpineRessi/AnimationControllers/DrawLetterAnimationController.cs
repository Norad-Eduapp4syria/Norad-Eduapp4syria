using Spine.Unity;
using System;
using UnityEngine;

namespace Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers
{
    public class DrawLetterAnimationController : AnimationControllerBase
    {
        AudioSource _audioSource;

        public DrawLetterAnimationController(int animationTrack, SkeletonAnimation animator, SpineParameters parameters, AudioSource audioSource) 
            : base(animationTrack, animator, parameters)
        {
            LocksStateMachine = true;
            _audioSource = audioSource;
            
        }

        public void PointAtCanvas()
        {
            PointAtCanvas(null);
        }

        public void PointAtCanvas(Action onComplete)
        {
            Parameters.DrawingHint.Play(_audioSource, Animator.state, AnimationTrack, false, RevertToStandardAnimationSubscription(onComplete));
        }

        public void CompletedDrawing(Action onComplete)
        {
            Parameters.DrawingHappy.Play(_audioSource, Animator.state, AnimationTrack, false, RevertToStandardAnimationSubscription(onComplete));
        }

        public void FailedDrawing(Action onComplete)
        {
            Parameters.DrawingSad.Play(_audioSource, Animator.state, AnimationTrack, false, RevertToStandardAnimationSubscription(onComplete));
        }

        public void InitialAnimation()
        {
            PointAtCanvas(onComplete: () => Parameters.DrawingWait.Play(_audioSource, Animator.state, AnimationTrack, false, RevertToStandardAnimationSubscription(null)));
        }

        AnimationEventSubscriptions RevertToStandardAnimationSubscription(Action callback)
        {
            return new AnimationEventSubscriptions
            {
                OnComplete = () =>
                {
                    Animator.state.SetAnimation(AnimationTrack, Parameters.StandardIdle, true);
                    callback.Raise();
                }
            };
        }

        protected override void OnDisable()
        {
        }

        protected override void OnEnable()
        {
            Animator.Skeleton.FlipX = false;
            Animator.state.SetAnimation(AnimationTrack, Parameters.StandardIdle, true);
        }

        protected override void HandleEvents(Spine.AnimationState state, int trackIndex, Spine.Event e) { }
        protected override void OnUpdate() { }
                
    }
}
