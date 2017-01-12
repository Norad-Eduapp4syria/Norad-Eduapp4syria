using UnityEngine;
using Assets.Common.Data;
using System;
using Object = UnityEngine.Object;
using Assets.Common.Missions;

public class EndSectionTransition : ITransition {

    public Vector2 LeftEdge { get; private set; }
    public Vector2 RightEdge { get; private set; }

    private float _placementOffsetx = 13.7f;
    public float Length { get; private set; }
    GameObject _content { get; set; }

    public Func<ActivityScore> OnPlayerEnteredEvaluation { get; set; }
    public Action OnPlayerResumedActivity { get; set; }
    public Action OnPlayerLeftActivity { get; set; }

    EvaluationManager _manager;
    ShowProgress _progressbar;
    EndActivityTransition _activityTransition;

    public EndSectionTransition(Vector2 startCoordinates)
    {
        _content = ResourceLoader.InstantiatePrefabAtPosition(Constants.Resources.SectionTransition, new Vector2(startCoordinates.x - _placementOffsetx, startCoordinates.y), null);
        _manager = _content.GetComponent<EvaluationManager>();
        _progressbar = _content.GetComponentInChildren<ShowProgress>();
        _activityTransition = new EndActivityTransition(_content, _manager);

        SetEdges();
        InitializeTriggers();
    }

    public void Destroy()
    {
        Object.Destroy(_content);
    }

    private void SetEdges()
    {
        LeftEdge = _manager.LeftEdgeMarker.position;
        RightEdge = _manager.RightEdgeMarker.position;
        Length = RightEdge.x - LeftEdge.x;
    }

    void InitializeTriggers()
    {
        _manager.OnEnterArea = OnEnterArea;
        _manager.OnLeavingActivity = PlayerLeftActivity;
        _manager.OnReturnToActivity = PlayerReturnedToActivity;
    }

    void OnEnterArea()
    {
        if (OnPlayerEnteredEvaluation != null)
        {
            var score = OnPlayerEnteredEvaluation();
            UpdateProgressbar(score);

            if (ShouldShowActivityTransition(score))
                _activityTransition.Enable(score);
        }
    }

    bool ShouldShowActivityTransition(ActivityScore score)
    {
        return score.NextActivity != score.ActivityResult.ActivityType;
    }

    void UpdateProgressbar(ActivityScore score)
    {
        _progressbar.ChangeProgress(score);
    }

    void PlayerLeftActivity()
    {
        _activityTransition.PlayerLeftActivity();
        OnPlayerLeftActivity.Raise();
    }

    void PlayerReturnedToActivity()
    {
        _activityTransition.PlayerReturnedToActivity();
        OnPlayerResumedActivity.Raise();
    }
}
