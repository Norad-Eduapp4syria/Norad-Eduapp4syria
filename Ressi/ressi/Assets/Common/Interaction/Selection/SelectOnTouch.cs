using Assets.Common.Mechanics;
using System;
using System.Collections;
using UnityEngine;

[RequireComponent(typeof(Collider2D), typeof(Rigidbody2D))]
public class SelectOnTouch : MonoBehaviour
{

    private GameObject _springJointObject;
    private SpringJoint2D _springJoint;
    readonly float _springJointDistance = 0f;
    readonly float _springJointDampingRatio = 0f;
    readonly float _springJointFrequency = 0.75f;

    private float RangeOfInterest = 3f;

    private Rigidbody2D _selectableRigidBody;
    readonly float _selectableRigidBodyDrag = 5f;
    readonly float _selectableRigidBodyAngularDrag = 5.0f;
    float _selectableRigidBodyInitialDrag;
    float _selectableRigidBodyInitialAngularDrag;
    
    private RessiAutoMovement _autoMovement;
    private Collider2D _collider;

    private SpriteRenderer _spriteRenderer;
    VerticalBobbing _bobbing;

    [Header("Sound")]
    public AudioClip TouchSound;
    AudioSource _soundSource;

    [Header("Sprites")]
    public Sprite DefaultSprite;    
    public Sprite OnSelectedSprite;
    public Sprite HintSprite;  
    public void Start()
    {
        var sourceObject = GameObject.FindGameObjectWithTag(Constants.Tags.SoundSource);
        _soundSource = sourceObject.GetComponent<AudioSource>();
        _spriteRenderer = GetComponent<SpriteRenderer>();
        _selectableRigidBody = GetComponent<Rigidbody2D>();
        _selectableRigidBodyInitialDrag = _selectableRigidBody.drag;
        _selectableRigidBodyInitialAngularDrag = _selectableRigidBody.angularDrag;

        _autoMovement = FindObjectOfType<RessiAutoMovement>();
        _collider = GetComponent<Collider2D>();
        _bobbing = GetComponent<VerticalBobbing>();
    }

    private bool _isInteresting;
    
    void Update()
    {
        if (_wasDeselected)
            ResetDrag();

        if (_isInteresting)
        {
            _autoMovement.SetTarget(transform);
            TryMakeUninteresting();
        }
    }
   
    
    void FixedUpdate()
    {
        TryRemovePhysics();
    }

    void TryMakeUninteresting()
    {
        if (!_wasDeselected) return;
        if (IsInRangeOfInterest()) return;

        MakeUninteresting();
        _wasDeselected = false;
    }

    bool IsInRangeOfInterest()
    {
        var distance = Mathf.Abs(transform.position.x - _autoMovement.transform.position.x);
        return distance <= RangeOfInterest;
    }

    void TryRemovePhysics()
    {
        if (_isInteresting) return;
        if (_selectableRigidBody.IsAwake()) return;
        if (_selectableRigidBody.isKinematic) return;

        RemovePhysics();
    }

    private bool _wasDeselected;
    
    public void Select()
    {
        MakeInteresting();
        CreateSpringJoint();
        PlaySelectSound();
        

        if(_bobbing != null)
            _bobbing.enabled = false;
    }

    void PlaySelectSound()
    {
        if (_soundSource == null)
            return;

        _soundSource.PlayOneShot(TouchSound);
    }

    public void Deselect()
    {
        _wasDeselected = true;
        Destroy(_springJointObject);
    }

    void MakeInteresting()
    {
        _isInteresting = true;

        _collider.isTrigger = false;

        _spriteRenderer.sprite = OnSelectedSprite;
    }

    void MakeUninteresting()
    {
        _isInteresting = false;
        _autoMovement.ClearTarget();

        _spriteRenderer.sprite = DefaultSprite;
    }

    void RemovePhysics()
    {
        _selectableRigidBody.isKinematic = true;
        _collider.isTrigger = true;
    }

    void CreateSpringJoint()
    {
        _springJointObject = new GameObject("SpringJointObject");
        _springJointObject.transform.parent = transform;

        var springJointRigidBody = _springJointObject.AddComponent<Rigidbody2D>();
        springJointRigidBody.isKinematic = true;

        _springJoint = _springJointObject.AddComponent<SpringJoint2D>();
        _springJoint.connectedBody = _selectableRigidBody;
        _springJoint.autoConfigureDistance = false;
        
        _selectableRigidBody.isKinematic = false;
        _selectableRigidBody.drag = _selectableRigidBodyDrag;
        _selectableRigidBody.angularDrag = _selectableRigidBodyAngularDrag;
        
        _springJoint.distance = _springJointDistance;
        _springJoint.dampingRatio = _springJointDampingRatio;
        _springJoint.frequency = _springJointFrequency;
    }

    void ResetDrag()
    {
        _selectableRigidBody.drag = _selectableRigidBodyInitialDrag;
        _selectableRigidBody.angularDrag = _selectableRigidBodyInitialAngularDrag;
    }

    public void Move(Vector3 position)
    {
        _springJointObject.transform.position = new Vector3(position.x, position.y + 1.5f, position.z);
    }
}