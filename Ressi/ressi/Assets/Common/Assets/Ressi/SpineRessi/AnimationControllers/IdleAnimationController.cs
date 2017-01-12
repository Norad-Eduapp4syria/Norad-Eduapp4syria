using Spine.Unity;
using UnityEngine;
using System;
using Random = UnityEngine.Random;
using Assets.Common.Mechanics;

namespace Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers
{
    public class IdleAnimationController : AnimationControllerBase
    {
        float _idleStartTime;

        const int _animationSegments = 4;
        const int _cumulativeSegmentTransitionSeconds = 90;

        const int _transientAnimationCooldown = 10;
        const int _transientAnimationProbabilityPercent = 10;

        ProbabilityTrigger _animationTrigger;
        AudioSource _audioSource;

        string _standardIdleAnimation;
        AnimationWithSound[] _lowResilienceAnimations;

        //TODO inject ressi's stats to switch animation sets with higher resilience
        public IdleAnimationController(int animationTrack, SkeletonAnimation animator, SpineParameters parameters, AudioSource audioSource)
            : base(animationTrack, animator, parameters)
        {
            _audioSource = audioSource;
            _standardIdleAnimation = parameters.StandardIdle;
            _lowResilienceAnimations = parameters.LowResilienceIdle;
            _animationTrigger = new ProbabilityTrigger(_transientAnimationProbabilityPercent, _transientAnimationCooldown);
            OnExternalAnimationEnd = ExternalAnimationEnded;
        }

        void ExternalAnimationEnded()
        {
            _animationTrigger.Reset();
        }

        protected override void OnDisable() { }

        protected override void OnEnable()
        {
            ResetCounters();
            Animator.state.SetAnimation(AnimationTrack, _standardIdleAnimation, true);
        }

        protected override void OnUpdate()
        {
            _animationTrigger.TryTriggerEvent(WhenAnimationTriggered);
        }

        void WhenAnimationTriggered(Action onComplete)
        {
            Debug.Log("Triggered idle-animation at " + (Time.time - _idleStartTime));
            var animation = PickAnimationFromSlidingRange(_lowResilienceAnimations);
            PlayTransientAnimation(animation, onComplete);
        }

        protected override void HandleEvents(Spine.AnimationState state, int trackIndex, Spine.Event e) { } 

        void PlayTransientAnimation(AnimationWithSound animation, Action onComplete)
        {
            var state = Animator.state.GetCurrent(AnimationTrack);
            if (state.Animation.Name != Parameters.StandardIdle)
                return;

            animation.Play(_audioSource, Animator.state, AnimationTrack, false, 
                subscriptions: new AnimationEventSubscriptions
                {
                    OnComplete = () =>
                    {
                        Animator.state.SetAnimation(AnimationTrack, _standardIdleAnimation, true);
                        onComplete();
                    }
                }
            );
        }

        AnimationWithSound PickAnimationFromSlidingRange(AnimationWithSound[] animations)
        {
            var clampedTime = Mathf.Min(Time.time - _idleStartTime, _cumulativeSegmentTransitionSeconds);
            var normalizedTime = clampedTime / _cumulativeSegmentTransitionSeconds;
            var scaledTime = normalizedTime * (animations.Length - 1);

            var stepSize = (animations.Length / _animationSegments) / 2;
            
            var startRange = (int)Math.Round(Math.Max(scaledTime - stepSize, 0));
            var endRange = (int)Math.Round(Math.Min(scaledTime + stepSize, animations.Length - 1)) +1;

            var animationIndex = Random.Range(startRange, endRange);

            return animations[animationIndex];
        }

        void ResetCounters()
        {
            _idleStartTime = Time.time;
            _animationTrigger.Reset();
        }
    }
}
