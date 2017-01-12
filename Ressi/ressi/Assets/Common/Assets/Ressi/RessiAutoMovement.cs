using System;
using System.Linq;
using Assets.Common.Data;
using UnityEngine;

[RequireComponent(typeof(Rigidbody2D))]
[RequireComponent(typeof(SpineRessiAnimator))]
public class RessiAutoMovement : MonoBehaviour
{
    public float MaxSpeed = 50f;

    Camera _camera;
    private Rigidbody2D _rigidBody;
    Vector3 _velocity = Vector3.zero;
    float _smoothTime = 0.5f;
    
    public bool IsObjectSelected = false;
    public float EatingRange = 2f;
    private Vector3? _target;

    Action _onReachedTarget;

    SpineRessiAnimator _animator;

    void Start()
    {
        _camera = Camera.main;
        _prevCameraBounds = _camera.OrthographicBounds();
        _rigidBody = GetComponent<Rigidbody2D>();
        _animator = GetComponent<SpineRessiAnimator>();
    }

    private Bounds _prevCameraBounds;

    void Update()   
    {
        var cameraBounds = _camera.OrthographicBounds();
        EnableMovementOnCameraMoved(cameraBounds);
        _prevCameraBounds = cameraBounds;

        var target = ChooseTarget();
        if (!target.HasValue) return;

        FaceTowardsTarget(target.Value);
        MoveTowardsTarget(target.Value);
    }

    Vector2? ChooseTarget()
    {
        if (_target.HasValue)
            return _target.Value;
        
        var camerabounds = _camera.OrthographicBounds();
        if (!_stopped)
            return camerabounds.center;
        
        return null;
    }

    void FixedUpdate()
    {
        ApplyQueuedForces();
    }

    private void EnableMovementOnCameraMoved(Bounds cameraBounds)
    {
        if (!_stopped || !CameraMoved(cameraBounds)) return;
        _stopped = false;
    }

    private void FaceTowardsTarget(Vector3 target)
    {
        if (target.x > transform.position.x)
        {
            _animator.FaceRight();
        }
        else
        {
            _animator.FaceLeft();
        }
    }

    private bool IsContainedBy(Bounds cameraBounds)
    {
        return cameraBounds.Contains(transform.position);
    }

    private float _cameraMoveTolerance = 0.0001f;

    private bool CameraMoved(Bounds cameraBounds)
    {
        var deltaX = _prevCameraBounds.center.x - cameraBounds.center.x;
        return Math.Abs(deltaX) > _cameraMoveTolerance;
    }

    private bool _hasQueuedForces;
    private float _jumpForce = 1f;
    private bool _stopped;

    public void Stop()
    {
        print("Stopping");
        _stopped = true;
    }

    public void Jump()
    {
        _hasQueuedForces = true;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns>True if forces were applied; otherwise, false</returns>
    private bool ApplyQueuedForces()
    {
        if (!_hasQueuedForces) return false;
        _hasQueuedForces = false;

        ApplyJumpForce();

        return true;
    }

    private void ApplyJumpForce()
    {
        var forwardVector = _animator.GetForwardFacingVector();
        _rigidBody.AddForce(
            Vector2.up + (forwardVector * _jumpForce),
            ForceMode2D.Impulse);

        print("Jumped");
    }

    private void MoveTowardsTarget(Vector3 target)
    {    
        var distance = transform.position.x - target.x;
        if(Mathf.Abs(distance) < 0.5f)
        {
            ReachTarget();
            return;
        }

        transform.position = Vector3.SmoothDamp(transform.position, new Vector3(target.x, transform.position.y, 0), ref _velocity, _smoothTime, MaxSpeed);
        _animator.StartWalking();
    }

    void ReachTarget()
    {
        _animator.StopWalking();
        _onReachedTarget.Raise();
        _target = null;
        _onReachedTarget = null;
    }

    public void MoveToPosition(Vector2 position, Action onReachedTarget = null)
    {
        _target = position;
        _onReachedTarget = onReachedTarget;
    }

    public void SetTarget(Transform target)
    {
        _animator.StartChaseConsumable(target);
        _target = target.position;
    }

    public void ClearTarget()
    {
        Stop();
        _animator.StopChasingConsumable();
        _target = null;
    }
}
