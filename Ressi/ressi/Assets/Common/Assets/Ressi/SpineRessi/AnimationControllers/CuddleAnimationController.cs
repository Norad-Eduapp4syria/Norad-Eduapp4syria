using System;
using Spine.Unity;
using UnityEngine;

namespace Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers
{
    public class CuddleAnimationController : AnimationControllerBase
    {
        bool _enabled;
        AudioSource _audioSource;
        bool _animationInProgress;

        public CuddleAnimationController(int animationTrack, SkeletonAnimation animator, SpineParameters parameters, AudioSource audioSource) 
            : base(animationTrack, animator, parameters)
        {
            LocksStateMachine = true;
            _audioSource = audioSource;
        }

        public void HighFive(Action onHighFiveFinish)
        {
            if (!CanStartNewAnimation())
                return;

            _animationInProgress = true;

            Parameters.HighFive.Play(_audioSource, Animator.state, AnimationTrack, false, FinishAnimation(onHighFiveFinish));
        }

        public void Poke(Action onPokeFinish)
        {
            if (!CanStartNewAnimation())
                return;

            _animationInProgress = true;

            Parameters.PokeAnimation.Play(_audioSource, Animator.state, AnimationTrack, false, FinishAnimation(onPokeFinish));
        }

        AnimationEventSubscriptions FinishAnimation(Action callback)
        {
            return new AnimationEventSubscriptions
            {
                OnComplete = () =>
                {
                    _animationInProgress = false;
                    callback();
                }
            };
        }

        public void StartStroking()
        {
            if (!CanStartNewAnimation())
                return;

            _animationInProgress = true;
            Parameters.StrokeAnimation.Play(_audioSource, Animator.state, AnimationTrack, true);
        }

        public void EndStroking()
        {
            _animationInProgress = false;
            Animator.state.SetAnimation(AnimationTrack, Parameters.StandardIdle, true);
        }

        protected override void OnDisable()
        {
            _enabled = false;
            _animationInProgress = false;
        }

        bool CanStartNewAnimation()
        {
            return _enabled && !_animationInProgress;
        }

        protected override void OnEnable()
        {
            _enabled = true;
            Animator.Skeleton.FlipX = false;
        }

        protected override void HandleEvents(Spine.AnimationState state, int trackIndex, Spine.Event e) { }
        protected override void OnUpdate() { }
                
    }
}
