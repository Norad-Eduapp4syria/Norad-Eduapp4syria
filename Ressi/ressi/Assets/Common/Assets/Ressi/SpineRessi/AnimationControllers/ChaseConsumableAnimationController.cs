using Spine.Unity;
using Spine.Unity.Modules;
using System.Collections;
using System.Linq;
using UnityEngine;

namespace Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers
{
    public class ChaseConsumableAnimationController : AnimationControllerBase
    {
        SkeletonUtilityEyeConstraint[] _eyes;
        Vector3[][] _initialEyePositions;

        AttachmentSwitcher _mouth;

        public ChaseConsumableAnimationController(int animationTrack, SkeletonAnimation animator, SpineParameters spineParameters, SkeletonUtilityEyeConstraint[] eyeConstraints)
            : base(animationTrack, animator, spineParameters)
        {
            LocksStateMachine = true;
            _eyes = eyeConstraints;
            _mouth = new AttachmentSwitcher(animator, Parameters.MouthSlot, Parameters.ChaseMouthAttachment);
        }

        public void SetTarget(Transform target)
        {
            _mouth.Switch();
            LookAtTarget(target);
        }

        protected override void OnEnable()
        {
            Animator.state.SetAnimation(AnimationTrack, Parameters.ChaseConsumableAnimation, true);
        }

        protected override void OnUpdate() {}

        protected override void OnDisable()
        {
            _mouth.Reset();
            StopLookingAtTarget();
        }

        protected override void HandleEvents(Spine.AnimationState state, int trackIndex, Spine.Event e) { }

        void LookAtTarget(Transform target)
        {
            if (_eyes == null)
                return;

            _initialEyePositions = _eyes
                .Select(i => i.eyes
                    .Select(j => j.localPosition)
                    .ToArray())
                .ToArray();

            foreach (var eye in _eyes)
            {
                SetBoneMode(eye, SkeletonUtilityBone.Mode.Override);
                eye.target = target;
            }
        }

        void StopLookingAtTarget()
        {
            if (_eyes == null)
                return;

            for (var i = 0; i < _eyes.Length; i++)
            {
                var eye = _eyes[i];
                eye.target = null;

                for (var j = 0; j < eye.eyes.Length; j++)
                    eye.eyes[j].localPosition = _initialEyePositions[i][j];

                //NOTE: There is a bug here which prevents the eyes to reset to initial position if bone mode is set to follow straight afterwards.
                // Workaround is to wait a little bit
                eye.StartCoroutine(ResetBones(eye));
            }
        }

        IEnumerator ResetBones(SkeletonUtilityEyeConstraint eye)
        {
            yield return new WaitForSeconds(.5f);
            SetBoneMode(eye, SkeletonUtilityBone.Mode.Follow);
        }

        void SetBoneMode(SkeletonUtilityEyeConstraint eye, SkeletonUtilityBone.Mode mode)
        {
            foreach (var eyeTransform in eye.eyes)
            {
                var bone = eyeTransform.GetComponent<SkeletonUtilityBone>();
                bone.mode = mode;
            }
        }

        
    }
}
