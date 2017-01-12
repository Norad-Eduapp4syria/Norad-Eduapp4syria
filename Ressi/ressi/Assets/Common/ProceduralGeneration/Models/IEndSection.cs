using UnityEngine;
using System;
using Assets.Common.Missions;

public interface ITransition {

    Vector2 LeftEdge { get; }
    Vector2 RightEdge { get; }

    float Length { get; }

    Func<ActivityScore> OnPlayerEnteredEvaluation { get; set; }
    Action OnPlayerResumedActivity { get; set; }
    Action OnPlayerLeftActivity { get; set; }

    void Destroy();
}
