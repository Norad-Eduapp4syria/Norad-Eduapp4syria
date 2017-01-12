using UnityEngine;
using Assets.Common.Data;
using System;
using Object = UnityEngine.Object;
using Assets.Common.Missions;

public class EndActivityTransition  {

    EvaluationManager _manager;
    EvaluationLight[] _evaluationLights;
    RessiController _ressi;

    GameObject _transition;
    ActivityTransitionFinished _eventTrigger;
    GameObject _root;

    bool _enabled;

    public EndActivityTransition(GameObject root, EvaluationManager manager)
    {
        _manager = manager;
        _root = root;
        _transition = manager.ActivityTransition;
        _eventTrigger = root.GetComponent<ActivityTransitionFinished>();
        _evaluationLights = _transition.GetComponentsInChildren<EvaluationLight>();
        _ressi = GameObject.FindObjectOfType<RessiController>();
    }

    public void Enable(ActivityScore score)
    {
        if (_enabled)
        {
            TurnOnLights(score);
            return;
        }

        _enabled = true;

        var camera = GameObject.FindObjectOfType<CameraMovement>();
        var evaluationPosition = _manager.EvaluationMark.position;

        _ressi.Movement.MoveToPosition(evaluationPosition, OnRessiAtEvaluationPosition);
        camera.SetTargetX(evaluationPosition.x, targetReached: () => AnimateTerrain(score));
    }
   
    void AnimateTerrain(ActivityScore score)
    {
        _transition.SetActive(true);
        _eventTrigger.OnTransitionAreaShown = () => OnActivityTransitionVisible(score);
        var animator = _root.GetComponent<Animator>();
        animator.SetTrigger(Constants.AnimatorEvents.ActivityTransitionAnimation);
    }

    void TurnOnLights(ActivityScore score)
    {
        if (_evaluationLights == null)
            return;

        foreach (var light in _evaluationLights)
            light.TurnOnLight(score);
    }

    void TurnOffLights()
    {
        if (_evaluationLights == null)
            return;

        foreach (var light in _evaluationLights)
            light.TurnOffLight();
    }

    void OnRessiAtEvaluationPosition()
    {
        _ressi.PauseTouchInput();
    }

    void OnActivityTransitionVisible(ActivityScore score)
    {
        TurnOnLights(score);
        _ressi.FinishActivity(score);
    }

    public void PlayerLeftActivity()
    {
        _manager.PlatformGlow.SetActive(false);
    }

    public void PlayerReturnedToActivity()
    {
        TurnOffLights();
    }
}
