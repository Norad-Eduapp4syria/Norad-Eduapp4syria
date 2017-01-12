using Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers;
using Spine.Unity;
using System;
using System.Collections.Generic;

namespace Assets.Common.Assets.Ressi.SpineRessi
{
    public class AnimationStateMachine
    {
        public AnimationControllerBase ActiveController { get; private set; }
        public StableAnimationState ActiveState { get; private set; }

        Dictionary<StableAnimationState, AnimationControllerBase> _stateLookup = new Dictionary<StableAnimationState, AnimationControllerBase>();
        Dictionary<Type, AnimationControllerBase> _typeLookup = new Dictionary<Type, AnimationControllerBase>();
        SkeletonAnimation _skeletonAnimation;
        bool _isLocked;

        public AnimationStateMachine(SkeletonAnimation skeletonAnimation)
        {
            _skeletonAnimation = skeletonAnimation;
        }

        public void AddState<T>(StableAnimationState state, T controller) where T : AnimationControllerBase
        {
            if (_stateLookup.ContainsKey(state))
                throw new ArgumentException("Controller for state " + state + " already added.");

            _stateLookup.Add(state, controller);
            _typeLookup.Add(typeof(T), controller);
        }

        public T Get<T>() where T : AnimationControllerBase
        {
            return (T)_typeLookup[typeof(T)];
        }

        public void Unlock()
        {
            _isLocked = false;
        }

        public bool ChangeState(StableAnimationState state)
        {
            if (_isLocked)
                return false;

            if (state == ActiveState && ActiveController != null)
                return false;

            var newController = _stateLookup[state];

            if (ActiveController != null)
                ActiveController.Disable();

            if (SwitchingFromSidewaysToFrontFacingAnimation(ActiveController, newController))
                ResetSkeleton();

            ActiveController = newController;
            ActiveController.Enable();

            if (ActiveController.LocksStateMachine)
                _isLocked = true;

            ActiveState = state;

            return true;
        }

        bool SwitchingFromSidewaysToFrontFacingAnimation(AnimationControllerBase oldController, AnimationControllerBase newController)
        {
            if (oldController == null)
                return false;

            return oldController.IsSidewaysAnimation && !newController.IsSidewaysAnimation;
        }

        void ResetSkeleton()
        {
            _skeletonAnimation.Skeleton.SetToSetupPose();
        }
    }
}
