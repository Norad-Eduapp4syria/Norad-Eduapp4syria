using Assets.Common.Missions;
using System;

public class ActivityCallbacks
{
    public Action<ActivityResult> Ended;
    public Func<ActivityResult, ActivityScore> PreliminaryEvaluation;
}