using System;
using System.Collections.Generic;
using UnityEngine;
using Object = UnityEngine.Object;
using Assets.Common.Missions;
using UnityEngine.Analytics;

public abstract class Activity
{
    readonly ActivityCallbacks _callbacks = new ActivityCallbacks();
    private bool _started;

    private float _lapTimeStart;
    private float _elapsedTime;
    private bool _completed;

    GameObject _root;
    public ILevelSection Section;

    protected RessiController Ressi;
    protected ActivityDifficulty Difficulty;

    public Activity(ActivityDifficulty difficulty)
    {
        Difficulty = difficulty;
    }

    public ActivityCallbacks Start(ILevelSection section)
    {
        if(_started) throw new InvalidOperationException("Already started");

        Analytics.CustomEvent(CustomEventNames.StartActivity, new Dictionary<string, object> { {CustomEventData.ActivityType, GetType().Name}, {CustomEventData.ActivityDifficulty, Difficulty} });

        _started = true;
        _root = new GameObject(GetType().Name);

        Section = section;
        Section.EndSection.OnPlayerLeftActivity = PlayerLeftActivity;
        Section.EndSection.OnPlayerResumedActivity = ReturnedToActivity;
        Section.EndSection.OnPlayerEnteredEvaluation = ActivityEvaluationTriggered;

        Ressi = LocateRessiController();

        BuildActivity(section, _root);

        _lapTimeStart = Time.time;

        Debug.Log("ACTIVITY ::: Player started activity");

        return _callbacks;
    }

    public virtual void ModifyDefaultCameraBounds(CameraTouchInteraction camera) {}

    protected void ReleaseCamera()
    {
        TouchInteractions.CameraTouchInteraction.CameraLeftBounds = Section.LeftEdge.x;
    }

    private void PlayerLeftActivity()
    {
        PauseTime();

        Debug.Log("ACTIVITY ::: Player left activity, Time= " + _elapsedTime);

        _callbacks.Ended(EvaluateActivity());
        BeforeDestroy();
        Destroy();
    }

    public ActivityResult EvaluateActivity()
    {
        var completionKind = EvaluateActivity(_elapsedTime);
        return new ActivityResult(GetType(), Difficulty, completionKind, _elapsedTime);
    }

    protected void PlayerFailedActivity()
    {
        PauseTime();
        _completed = true;
        Ressi.FailActivity(() => Object.Destroy(_root));
    }
    protected void PlayerCompletedActivity()
    {
        PauseTime();
        _completed = true;
        Ressi.CompleteActivity(() => Object.Destroy(_root));
    }

    /// <summary>
    /// Called before the activity is destroyed and removed from the scene
    /// </summary>
    protected abstract void BeforeDestroy();

    private void Destroy()
    {
        Object.Destroy(_root);
        Section.EndSection.OnPlayerLeftActivity = null;
        Section.EndSection.OnPlayerResumedActivity = null;
        Section.EndSection.OnPlayerEnteredEvaluation = null;
    }

    private ActivityScore ActivityEvaluationTriggered()
    {
        PauseTime();

        var evaluation = EvaluateActivity();
        return _callbacks.PreliminaryEvaluation(evaluation);
    }

    /// <summary>
    /// Called when the activity should evaluate the score for the current player state
    /// </summary>
    /// <param name="elapsedTime">The currently elapsed time to calculate score for</param>
    /// <returns></returns>
    protected abstract ActivityResultKind EvaluateActivity(float elapsedTime);

    private void ReturnedToActivity()
    {
        Debug.Log("ACTIVITY ::: Player returned to activity. Time= " + _elapsedTime);

        if (_completed) return; // don't resume time if activity completed
        ResumeTime();
    }

    private bool _timeIsPaused;

    private void PauseTime()
    {
        if (_timeIsPaused) return;
        _elapsedTime += Time.time - _lapTimeStart;
        _timeIsPaused = true;
    }

    private void ResumeTime()
    {
        _lapTimeStart = Time.time;
        _timeIsPaused = false;
    }

    RessiController LocateRessiController()
    {
        var player = GameObject.FindGameObjectWithTag(Constants.Tags.Player);

        var controller = player.GetComponent<RessiController>();
        if (controller == null)
        {
            Debug.LogError("RessiController script not attached to player");
            return null;
        }

        return controller;
    }

    /// <summary>
    /// Called when the activity should populate the scene with its game objects
    /// </summary>
    /// <param name="section">The section that holds the activity</param>
    /// <param name="root">The root that should hold all the game objects for this activity</param>
    protected abstract void BuildActivity(ILevelSection section, GameObject root);
    
}