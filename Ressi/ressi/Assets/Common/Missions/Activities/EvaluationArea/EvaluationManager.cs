using System;
using UnityEngine;

public class EvaluationManager : MonoBehaviour 
{
    public Transform EvaluationMark;
    public GameObject ActivityTransition;

    [SerializeField]
    CustomEventTrigger _rightEdgeTrigger;
    [SerializeField]
    CustomEventTrigger _leftEdgeTrigger;
    [SerializeField]
    CustomEventTrigger _returnToActivityTrigger;

    public Transform LeftEdgeMarker;
    public Transform RightEdgeMarker;

    public GameObject PlatformGlow;

    public Action OnEnterArea;
    public Action OnReturnToActivity;
    public Action OnLeavingActivity;

    


	void Start () 
	{
        _rightEdgeTrigger.OnEnter = EnterArea;
    }

    void EnterArea(GameObject obj)
    {
        _rightEdgeTrigger.OnEnter = null;
        _returnToActivityTrigger.OnEnter = ReturnToActivity;
        _leftEdgeTrigger.OnEnter = LeaveActivity;

        OnEnterArea.Raise();
    }

    void ReturnToActivity(GameObject obj)
    {
        _leftEdgeTrigger.OnEnter = null;
        _returnToActivityTrigger.OnEnter = null;
        _rightEdgeTrigger.OnEnter = EnterArea;

        OnReturnToActivity.Raise();
    }

    void LeaveActivity(GameObject obj)
    {
        _leftEdgeTrigger.OnEnter = null;
        _returnToActivityTrigger.OnEnter = null;
        _rightEdgeTrigger.OnEnter = null;

        OnLeavingActivity.Raise();
    }
}
