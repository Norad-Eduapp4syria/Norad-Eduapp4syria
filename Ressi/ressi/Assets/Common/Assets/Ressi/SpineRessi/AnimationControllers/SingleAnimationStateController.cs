using Spine;
using Spine.Unity;

namespace Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers
{
    public class SingleAnimationStateController : AnimationControllerBase
    {
        string _state;

        public SingleAnimationStateController(int animationTrack, SkeletonAnimation animator, SpineParameters parameters, string state, bool canFlipSprite, bool isSidewaysAnimation)
            : base(animationTrack, animator, parameters)
        {
            _state = state;
            CanFlipSprite = canFlipSprite;
            IsSidewaysAnimation = isSidewaysAnimation;
        }

        protected override void HandleEvents(AnimationState state, int trackIndex, Event e)
        { }

        protected override void OnDisable()
        {
            Animator.state.ClearTrack(AnimationTrack);
        }

        protected override void OnEnable()
        {
            Animator.state.SetAnimation(AnimationTrack, _state, true);
        }

        protected override void OnUpdate()
        {
        }
    }
}
