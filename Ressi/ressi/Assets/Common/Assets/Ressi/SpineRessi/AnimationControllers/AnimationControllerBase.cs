using Spine.Unity;
using System;

namespace Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers
{
    public abstract class AnimationControllerBase
    {
        public bool CanFlipSprite { get; protected set; }
        public bool IsSidewaysAnimation { get; protected set; }
        /// <summary>
        /// Some animations are locked and must explicitly be unlocked to be able to change state
        /// </summary>
        public bool LocksStateMachine { get; protected set; }

        public Action OnExternalAnimationEnd { get; protected set; }

        protected SkeletonAnimation Animator { get; private set; }
        protected int AnimationTrack { get; private set; }
        protected SpineParameters Parameters { get; private set; }

        bool _enabled;

        public AnimationControllerBase(int animationTrack, SkeletonAnimation animator, SpineParameters parameters)
        {
            AnimationTrack = animationTrack;
            Animator = animator;
            Parameters = parameters;
        }

        public void Enable()
        {
            _enabled = true;
            Animator.state.Event += HandleEvents;
            OnEnable();
        }

        public void Update()
        {
            if (!_enabled)
                return;

            OnUpdate();
        }

        public void Disable()
        {
            _enabled = false;
            Animator.state.Event -= HandleEvents;
            OnDisable();
        }

        protected abstract void OnUpdate();
        protected abstract void OnEnable();
        protected abstract void OnDisable();
        protected abstract void HandleEvents(Spine.AnimationState state, int trackIndex, Spine.Event e);
    }
}
