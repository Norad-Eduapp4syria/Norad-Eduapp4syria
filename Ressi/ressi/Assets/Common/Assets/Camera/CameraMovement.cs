using UnityEngine;
using System;
using System.Runtime.Remoting.Messaging;

public class CameraMovement : MonoBehaviour {
    
    float? _targetX;
    float? _targetY;

    private Action _targetXReached;
    private Action _targetYReached;

    [Header("Auto Movement Settings")]
    public float Damping = 1f;
    public float DistanceFromTargetThreshold = 0.2f;
    public float MaxSpeed = 0.5f;

    Camera _camera;
    private Vector2 _currentVelocity;

    void Start()
    {
        _camera = Camera.main;
    }

    // Update is called once per frame
    void Update()
    {
        if (_targetX == null && _targetY == null) return;

        if (HasReachedTargetX())
        {
            ReachedTargetX();
        }

        if (HasReachedTargetY())
        {
            ReachedTargetY();
        }
        
        MoveTowardsTarget();
    }

    void MoveTowardsTarget()
    {
        var x = _targetX.HasValue ? _targetX.Value : transform.position.x;
        var y = _targetY.HasValue ? _targetY.Value : transform.position.y;

        var newPos = Vector2.SmoothDamp(transform.position, new Vector2(x, y), ref _currentVelocity, Damping);
        
        _camera.transform.position = ToNewCameraPosition(newPos);
    }

    Vector3 ToNewCameraPosition(Vector2 newPosition)
    {
        return new Vector3(newPosition.x, newPosition.y, _camera.transform.position.z);
    }

    bool HasReachedTargetX()
    {
        if (_targetX == null) return true;

        var distanceFromTargetX = _camera.transform.position.x - _targetX.Value;
        var xDelta = Mathf.Abs(distanceFromTargetX);

        return xDelta <= DistanceFromTargetThreshold;
    }

    bool HasReachedTargetY()
    {
        if (_targetY == null) return true;

        var distanceFromTargetY = _camera.transform.position.y - _targetY.Value;
        var yDelta = Mathf.Abs(distanceFromTargetY);
        return yDelta <= DistanceFromTargetThreshold;
    }

    void ReachedTargetX()
    {
        if (_targetX == null) return;
        
        _targetXReached.Raise();
        _targetX = null;
        _targetXReached = null;
    }

    void ReachedTargetY()
    {
        if (_targetY == null) return;
        
        _targetYReached.Raise();
        _targetY = null;
        _targetYReached = null;
    }

    public void SetTargetX(float value, float velocity =0, Action targetReached = null)
    {
        _targetX = value;
        _currentVelocity = new Vector2(velocity, _currentVelocity.y);
        _targetXReached = targetReached;
    }
    
    public void SetTargetY(float value, float velocity = 0, Action targetReached = null)
    {
        _targetY = value;
        _currentVelocity = new Vector2(_currentVelocity.x, velocity);
        _targetYReached = targetReached;
    }

    public void ClearTargetX()
    {
        _targetX = null;
        _targetXReached = null;
    }

    public void ClearTargetY()
    {
        _targetY = null;
        _targetYReached = null;
    }
}
