using Assets.Common.Missions;
using System;

public class ActivityResult
{
    public ActivityResult(Type activityType, ActivityDifficulty difficulty, ActivityResultKind result, float timeToCompleteInSeconds)
    {
        ActivityType = activityType;
        Difficulty = difficulty;
        Result = result;
        TimeToCompleteInSeconds = timeToCompleteInSeconds;
    }

    public Type ActivityType { get; private set; }
    public ActivityDifficulty Difficulty { get; private set; }
    public ActivityResultKind Result { get; private set; }

    public float TimeToCompleteInSeconds { get; private set; }

    public override string ToString()
    {
        return string.Format("{0} result: {1}, time: {2}", ActivityType.Name, Result, TimeToCompleteInSeconds);
    }
}

public enum ActivityResultKind
{
    Flawless,
    Well,
    WithHelp,
    UnableToComplete,
    GaveUp
}