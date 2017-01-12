using System;
using UnityEngine;
using System.Linq;

public enum Position
{
    Up,
    Center,
    Down
}

public class SwipeUpDownTouchInteraction : ITouchInteraction
{
    public void Start(Camera camera)
    {
        _camera = camera;
        _centerY = _camera.transform.position.y;
    }

    private Camera _camera;

    private bool _isTrackingGesture;
    private bool _processingGesture;
    private bool _didTrackGesture;
    private bool _ignorableGestureDetected;
    private float _totalVelocity;

    public bool AllowSwipeUp = false;
    public bool AllowSwipeDown = false;

    public static event Action<Position> PositionChanging;
    public static event Action<Position> PositionChanged;

    private Position _position = Position.Center; // maybe this should be a property global to all gestures (so f.ex Update(touches, position)

    public InteractionContinuation Update(Touch2[] touches)
    {
        var touch = touches.FirstOrDefault();

        if (_processingGesture)
        {
            ProcessGesture();
            return InteractionContinuation.End();
        }
        
        if (touch != null && touch.Phase == TouchPhase.Began)
        {
            BeginTrackingGesture();
            return DetermineIgnorableGestureContinuation();
        }

        if (_ignorableGestureDetected)
            return DetermineIgnorableGestureContinuation();

        if (touch != null && _isTrackingGesture)
        {
            TrackGesture(touch);
            return _ignorableGestureDetected ? DetermineIgnorableGestureContinuation() : InteractionContinuation.End();
        }

        return InteractionContinuation.Next();
    }

    private InteractionContinuation DetermineIgnorableGestureContinuation()
    {
        if (_position != Position.Center) return InteractionContinuation.End(); // we're outside game area, disallow camera gestures
        return InteractionContinuation.Next(); // allow camera gestures
    }

    private void BeginTrackingGesture()
    {
        _isTrackingGesture = true;
        _processingGesture = false;
        _didTrackGesture = false;
        _ignorableGestureDetected = false;
        _totalVelocity = 0;
    }
    
    private void TrackGesture(Touch2 touch)
    {
        if (touch.Phase == TouchPhase.Ended || touch.Phase == TouchPhase.Canceled)
        {
            if (_didTrackGesture)
            {
                ResetGesture();
                return;
            }

            SetIgnorableGesture();
            return;
        }

        if (touch.Phase != TouchPhase.Moved) return;

        var deltaY = touch.DeltaPosition.y;
        var deltaX = touch.DeltaPosition.x;

        if (Math.Abs(deltaY*_camera.aspect) <= Math.Abs(deltaX))
            // only care if gesture is dominantely in the y direction
        {
            SetIgnorableGesture();
            return;
        }
        
        var velocity = CalculateVelocity(deltaY);
        
        if (_position == Position.Up && velocity > 0)
        {
            SetIgnorableGesture();
            return;
        }

        if (_position == Position.Down && velocity < 0)
        {
            SetIgnorableGesture();
            return;
        }

        if (!AllowSwipeUp && _position == Position.Center && velocity > 0)
        {
            SetIgnorableGesture();
            return;
        }

        if (!AllowSwipeDown && _position == Position.Center && velocity < 0)
        {
            SetIgnorableGesture();
            return;
        }

        _totalVelocity += velocity;
        _didTrackGesture = true;

        _camera.transform.Translate(0, velocity, 0);

        if (Math.Abs(_totalVelocity) > GestureVelocityTreshold)
        {
            StartProcessingGesture();
        }
    }
    
    private void SetIgnorableGesture()
    {
        _ignorableGestureDetected = true;
        if(Math.Abs(_totalVelocity) > 0.0f) ResetGesture();
        
    }

    private void StartProcessingGesture()
    {
        DetermineNextPosition();
        DetermineNextY();

        Debug.Log("Gesture detected! Next position: " + _nextPosition);
        _processingGesture = true;
        PositionChanging.Raise(_nextPosition);
    }

    private void DetermineNextPosition()
    {
        switch (_position)
        {
            case Position.Up:
            case Position.Down:
                _nextPosition = Position.Center;
                break;

            default:
                _nextPosition = _totalVelocity > 0 ? Position.Up : Position.Down;
                break;
        }
    }

    private void DetermineNextY()
    {
        switch (_nextPosition)
        {
            case Position.Center:
                _nextY = _centerY;
                break;

            case Position.Up:
                _nextY = _centerY + _targetYDistance;
                break;

            case Position.Down:
                _nextY = _centerY - _targetYDistance;
                break;
        }
    }

    private void ResetGesture()
    {
        Debug.Log("Gesture cancelled - returning to position " + _position);
        _nextPosition = _position;
        DetermineNextY();
        _processingGesture = true;
    }

    private float _nextY = 0.0f;
    private float movementSpeed = 10f;
    
    private void ProcessGesture()
    {
        var target = new Vector3(_camera.transform.position.x, _nextY, _camera.transform.position.z);
        _camera.transform.position = Vector3.MoveTowards(_camera.transform.position, target, movementSpeed*Time.deltaTime);
        
        if (Math.Abs(Math.Abs(_camera.transform.position.y) - Math.Abs(_nextY)) < TargetReachedThreshold)
        {
            CompleteProcessingGesture();
        }
    }

    Position _nextPosition = Position.Center;

    private void CompleteProcessingGesture()
    {
        _position = _nextPosition;

        Debug.Log("Completed gesture processing. camera at " + _camera.transform.position);
        _processingGesture = false;
        PositionChanged.Raise(_position);
    }

    float _targetYDistance = 4.2f;
    float _centerY;

    public double GestureVelocityTreshold = 1f;
    public double TargetReachedThreshold = 0.1f;

    private static float CalculateVelocity(float deltaY)
    {
        var smoothedDeltaY = -deltaY * CameraTouchInteraction.TouchSensitivity * Time.deltaTime;
        return smoothedDeltaY;
    }
}