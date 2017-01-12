using Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers;
using System.Linq;
using UnityEngine;

namespace Assets.Common.Interaction.Selection
{
    public class TouchRessiInteraction : ITouchInteraction
    {
        Camera _camera;
        bool _interactionInProgress;
        bool _isStroking;
        float _totalMovement;

        SpineRessiAnimator _ressi;
        CuddleAnimationController _animationController;

        const float PokeThreshold = 100f;

        public void Start(Camera camera)
        {
            _camera = camera;
        }

        public InteractionContinuation Update(Touch2[] touches)
        {
            if (!touches.Any()) return InteractionContinuation.Next();

            var touch = touches.First();

            var ev = TryHitRessi(touch);

            return ev != null
                ? HandleRessiTouch(ev)
                : HandleOutOfBoundsTouch();
        }

        InteractionContinuation HandleRessiTouch(CuddleEvent ev)
        {
            if(ev.Touch.Phase == TouchPhase.Began)
            {
                StartCuddling(ev.Ressi);
                TryHighfive(ev);
                return InteractionContinuation.End();
            }

            if (!_interactionInProgress)
                return InteractionContinuation.Next();
            
            AppendMovementDelta(ev.Touch);
            TryInteract(ev);

            return InteractionContinuation.End();
        }

        void StartCuddling(SpineRessiAnimator ressi)
        {
            _ressi = ressi;
            _interactionInProgress = true;
            _animationController = ressi.StartCuddle();
        }

        InteractionContinuation HandleOutOfBoundsTouch()
        {
            if (!_interactionInProgress) // if no interaction in progress, we don't care
                return InteractionContinuation.Next();

            FinishGesture();
            return InteractionContinuation.End();
        }

        void AppendMovementDelta(Touch2 touch)
        {
            if (touch.Phase == TouchPhase.Began)
                return;
            _totalMovement += Mathf.Abs(touch.DeltaPosition.magnitude);
        }

        void TryInteract(CuddleEvent ev)
        {
            if (_totalMovement <= PokeThreshold && ev.Touch.Phase == TouchPhase.Ended)
            {
                    Poke();
            }
            else if(_totalMovement > PokeThreshold)
            {
                if (ev.Touch.Phase == TouchPhase.Ended)
                {
                    EndStroking();
                    FinishGesture();
                }
                else
                {
                    Stroke();
                }
            }
        }

        bool TryHighfive(CuddleEvent ev)
        {
            if(ev.ColliderName != Constants.ObjectNames.HighFiveCollider)
                return false;

            HighFive();
            return true;
        }

        void Stroke()
        {
            if (_isStroking)
                return;

            _isStroking = true;
            _animationController.StartStroking();
        }

        void EndStroking()
        {
            _isStroking = false;
            _animationController.EndStroking();
        }

        void FinishGesture()
        {
            _interactionInProgress = false;
            _ressi.StopCuddling();
            _ressi = null;
            _animationController = null;
            _isStroking = false;
            _totalMovement = 0;
        }

        CuddleEvent TryHitRessi(Touch2 touch)
        {
            var origin = _camera.ScreenToWorldPoint(touch.Position);

            var hit = Physics2D.Raycast(origin, Vector2.zero, 10, Constants.Layers.TouchRessi);

            if (hit.collider == null)
                return null;

            var animator = hit.collider.gameObject.GetComponentInParent<SpineRessiAnimator>();
            return new CuddleEvent(animator, hit.collider.name, touch);
        }

        void HighFive()
        {
            _animationController.HighFive(FinishGesture);
        }

        void Poke()
        {
            _animationController.Poke(FinishGesture);
        }

        public class CuddleEvent
        {
            public SpineRessiAnimator Ressi { get; private set; }
            public string ColliderName { get; private set; }
            public Touch2 Touch { get; private set; }

            public CuddleEvent(SpineRessiAnimator ressi, string colliderName, Touch2 touch)
            {
                Ressi = ressi;
                ColliderName = colliderName;
                Touch = touch;
            }
        }
    }
}
