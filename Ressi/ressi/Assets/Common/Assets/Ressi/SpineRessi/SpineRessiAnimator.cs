using UnityEngine;
using Spine.Unity;
using Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers;
using System;
using Assets.Common.Assets.Ressi.SpineRessi;
using Spine.Unity.Modules;
using Assets.Common.Missions;

[RequireComponent(typeof(AudioSource))]
public class SpineRessiAnimator : MonoBehaviour {

    public SpineParameters Parameters;
                  
    SkeletonAnimation _skeletonAnimation;
    AnimationStateMachine _stateMachine;
    AudioSource _audioSource;
    
    const int _stableAnimationTrack = 0;
    const int _transientAnimationTrack = 1;

	// Use this for initialization
	void Start () {
        _skeletonAnimation = GetComponent<SkeletonAnimation>();
        _audioSource = GetComponent<AudioSource>();
        _stateMachine = new AnimationStateMachine(_skeletonAnimation);
        InitializeStates();

        _stateMachine.ChangeState(StableAnimationState.Idle);
	}

    void InitializeStates()
    {
        var eyeConstraints = GetComponentsInChildren<SkeletonUtilityEyeConstraint>();

        var idleAnimator = new IdleAnimationController(_stableAnimationTrack, _skeletonAnimation, Parameters, _audioSource);
        var walkAnimator = new SingleAnimationStateController(_stableAnimationTrack, _skeletonAnimation, Parameters, Parameters.StandardWalkAnimation, canFlipSprite: true, isSidewaysAnimation: true);
        var chaseConsumableAnimator = new ChaseConsumableAnimationController(_stableAnimationTrack, _skeletonAnimation, Parameters, eyeConstraints);
        var cuddleAnimator = new CuddleAnimationController(_stableAnimationTrack, _skeletonAnimation, Parameters, _audioSource);
        var drawingAnimator = new DrawLetterAnimationController(_stableAnimationTrack, _skeletonAnimation, Parameters, _audioSource);

        _stateMachine.AddState(StableAnimationState.Idle, idleAnimator);
        _stateMachine.AddState(StableAnimationState.Walk, walkAnimator);
        _stateMachine.AddState(StableAnimationState.ChaseConsumable, chaseConsumableAnimator);
        _stateMachine.AddState(StableAnimationState.Cuddling, cuddleAnimator);
        _stateMachine.AddState(StableAnimationState.Drawing, drawingAnimator);
    }

    public void FinishActivity(ActivityScore score, Action onComplete)
    {
        _skeletonAnimation.Skeleton.FlipX = false;
        AnimationWithSound animation;

        var onCompleteSubscription = new AnimationEventSubscriptions { OnComplete = onComplete };

        switch (score.P)
        {
            case P.Detoriated:
                animation = Parameters.WorseEvaluation;
                break;
            default:
                animation = Parameters.BestEvaluation;
                break;
        }
        PlayTransientAnimation(animation, onCompleteSubscription);
    }

    public void ReactNegatively(Action onComplete)
    {
        PlayTransientAnimation(Parameters.NegativeEatingAnimation, new AnimationEventSubscriptions {OnComplete = onComplete });
    }

    public void ReactPositively(Action onComplete = null)
    {
        PlayTransientAnimation(Parameters.PositiveEatingAnimation, new AnimationEventSubscriptions { OnComplete = onComplete });
    }

    public void PronounceLetter(ConsumableLetter letter, Action onComplete)
    {
        var subscriptions = new AnimationEventSubscriptions {
            OnComplete = onComplete
        };
        subscriptions.CustomEvents.Add(letter.PronounciationEvent, () => _audioSource.PlayOneShot(letter.PronounciationSound));
        QueueTransientAnimation(letter.PronounciationAnimation, subscriptions);
    }

    public void RequestLetter(ConsumableLetter letter, AnimationEventSubscriptions subscriptions = null)
    {
        QueueTransientAnimation(letter.RequestAnimation, subscriptions);
    }

    public void FailActivity(AnimationEventSubscriptions subscriptions = null)
    {
        _skeletonAnimation.Skeleton.FlipX = false;
        QueueTransientAnimation(Parameters.FailActivityAnimation, new AnimationEventSubscriptions {
            OnComplete = () => QueueTransientAnimation(Parameters.PointLeftActivityAnimationModerate, subscriptions)
        });
    }

    public void CompleteActivity(AnimationEventSubscriptions subscriptions = null)
    {
        _skeletonAnimation.Skeleton.FlipX = false;
        QueueTransientAnimation(Parameters.CompleteActivityAnimation, new AnimationEventSubscriptions {
            OnComplete = () => QueueTransientAnimation(Parameters.PointLeftActivityAnimation, subscriptions)
        });
    }

    public void StartChaseConsumable(Transform consumable)
    {
        var changedState = _stateMachine.ChangeState(StableAnimationState.ChaseConsumable);
        if (changedState)
            _stateMachine.Get<ChaseConsumableAnimationController>().SetTarget(consumable);
    }

    public DrawLetterAnimationController StartDrawing()
    {
        _stateMachine.ChangeState(StableAnimationState.Drawing);
        return _stateMachine.Get<DrawLetterAnimationController>();
    }

    public void StopDrawing()
    {
        _stateMachine.Unlock();
        _stateMachine.ChangeState(StableAnimationState.Idle);
    }

    public void StopChasingConsumable()
    {
        _stateMachine.Unlock();
        _stateMachine.ChangeState(StableAnimationState.Idle);
    }

    public void StartWalking()
    {
        _stateMachine.ChangeState(StableAnimationState.Walk);
    }

    public void StopWalking()
    {
       _stateMachine.ChangeState(StableAnimationState.Idle);
    }

    public CuddleAnimationController StartCuddle()
    {
        _stateMachine.ChangeState(StableAnimationState.Cuddling);
        return _stateMachine.Get<CuddleAnimationController>();
    }

    public void StopCuddling()
    {
        _stateMachine.Unlock();
        _stateMachine.ChangeState(StableAnimationState.Idle);
    }

    public void FaceLeft()
    {
        if (_stateMachine.ActiveController.CanFlipSprite)
            _skeletonAnimation.Skeleton.FlipX = false;
    }

    public void FaceRight()
    {
        if (_stateMachine.ActiveController.CanFlipSprite)
            _skeletonAnimation.Skeleton.FlipX = true;
    }

    public Vector2 GetForwardFacingVector()
    {
        return _skeletonAnimation.Skeleton.FlipX ? Vector2.right : Vector2.left;
    }

    public void PlayTransientAnimation(AnimationWithSound animation, AnimationEventSubscriptions events = null)
    {
        var subscriptions = CreateNotifyControllerOfAnimationEndSubscription(events);
        animation.Play(_audioSource, _skeletonAnimation.state, _transientAnimationTrack, false, subscriptions);
    }

    void QueueTransientAnimation(string animation, AnimationEventSubscriptions events = null)
    {
        var trackEntry = _skeletonAnimation.state.AddAnimation(_transientAnimationTrack, animation, false, delay: -0.0f);

        var subscriptions = CreateNotifyControllerOfAnimationEndSubscription(events);
        subscriptions.Subscribe(trackEntry);
    }

    void QueueTransientAnimation(AnimationWithSound animation, AnimationEventSubscriptions events = null)
    {
        var subscriptions = CreateNotifyControllerOfAnimationEndSubscription(events);
        animation.Queue(_audioSource, _skeletonAnimation.state, _transientAnimationTrack, false, delay: -0.0f, subscriptions: subscriptions);
    }

    AnimationEventSubscriptions CreateNotifyControllerOfAnimationEndSubscription(AnimationEventSubscriptions otherSubscriptions)
    {
        if (otherSubscriptions == null)
            otherSubscriptions = new AnimationEventSubscriptions();

        var currentEndSubscription = otherSubscriptions.OnEnd;
        otherSubscriptions.OnEnd = () =>
        {
            _stateMachine.ActiveController.OnExternalAnimationEnd.Raise();
            currentEndSubscription.Raise();
        };

        return otherSubscriptions;
    }

    // Update is called once per frame
    void Update()
    {
        if (_stateMachine.ActiveController == null)
            return;

        _stateMachine.ActiveController.Update();
    }
}
