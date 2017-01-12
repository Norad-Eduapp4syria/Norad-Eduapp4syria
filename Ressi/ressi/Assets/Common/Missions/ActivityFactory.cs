using Assets.Common.Missions;
using Assets.Common.Missions.Activities.LetterActivities;
using Assets.Common.Missions.Activities.LetterActivities.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class ActivityFactory
{
    LinkedList<Type> _activityOrder = new LinkedList<Type>();
    readonly LetterGroupFactory _groupFactory = new LetterGroupFactory();
    DifficultyMatrix _difficultyMatrix;

    public ActivityFactory()
    {
        _difficultyMatrix = new DifficultyMatrix();
        InitializeActivityOrder();
    }

    void InitializeActivityOrder()
    {
        _activityOrder.AddLast(typeof(GatherLettersActivity));
        _activityOrder.AddLast(typeof(RequestLettersActivity));
        _activityOrder.AddLast(typeof(DrawLetterActivity));
    }

    public Activity CreateActivity( MissionScore score, ActivityScore activityScore)
    {
        if (activityScore == null)
            return CreateStartActivity(score);

        var difficulty = CalculateActivityDifficulty(activityScore.NextActivity, activityScore.ActivityResult, activityScore.P);
        return Instantiate(activityScore.NextActivity, _groupFactory.GetGroup1(), difficulty);
    }

    //TODO Remove ASAP
    Type HackToShowActivityTransitionAtTheEnd()
    {
        // Reason: Activity Transition is shown if the Type of the next activity is different from the last
        // Return a random type before showing end section to trigger transition.
        // Beware that if we didn't reach end section after returning this, everything would crash
        return typeof(ActivityFactory);
    }

    public Type GetNextActivityType(MissionScore score, Percentage newScore, ActivityResult newActivityResult, P p)
    {
        if (newActivityResult == null)
            return score.GetCurrentActivity();

        var previousActivity = newActivityResult.ActivityType;
        

        var scoreBasedActivity = previousActivity;

        if (newScore >= Percentage.OneHundred)
        {
            var nextNode = _activityOrder.Find(previousActivity).Next;
            if (nextNode == null)
                //nextNode = _activityOrder.Last;
                return HackToShowActivityTransitionAtTheEnd();

            scoreBasedActivity = nextNode.Value;
        }
        else if(newScore <= Percentage.Zero)
        {
            var previousNode = _activityOrder.Find(previousActivity).Previous;
            if (previousNode == null)
                previousNode = _activityOrder.First;

            scoreBasedActivity = previousNode.Value;
        }

        return scoreBasedActivity;
    }

    Activity CreateStartActivity(MissionScore score)
    {
        var type = score.GetCurrentActivity();
        return Instantiate(type, _groupFactory.GetGroup1(), ActivityDifficulty.Normal);
    }

    ActivityDifficulty CalculateActivityDifficulty(Type nextActivityType, ActivityResult newActivityResult, P p)
    {
        if(newActivityResult == null)
            return ActivityDifficulty.Normal;

        if (newActivityResult.ActivityType != nextActivityType)
            return ActivityDifficulty.Normal;

        if (newActivityResult.Result == ActivityResultKind.Flawless && p == P.Unchanged)
            return ActivityDifficulty.Hard;

        if (newActivityResult.Result == ActivityResultKind.UnableToComplete || newActivityResult.Result == ActivityResultKind.GaveUp)
            return ActivityDifficulty.Easy;

        return _difficultyMatrix.Get(newActivityResult.Difficulty, p);
    }

    Activity Instantiate(Type type, LetterGroup letterGroup, ActivityDifficulty difficulty)
    {
        Debug.Log("Creating new Activity " + type.Name + " with difficulty " + difficulty);

        if (type == typeof(GatherLettersActivity))
            return new GatherLettersActivity(letterGroup, difficulty);
        if (type == typeof(RequestLettersActivity))
            return new RequestLettersActivity(letterGroup, difficulty);
        if (type == typeof(DrawLetterActivity))
            return new DrawLetterActivity(letterGroup, difficulty);

        throw new NotSupportedException("Not supported activity type: " + type.Name);
    }

    public class DifficultyMatrix
    {
        int[,] _m;
        public DifficultyMatrix()
        {
            var width = Enum.GetValues(typeof(ActivityDifficulty)).Cast<int>().Max();
            var height = Enum.GetValues(typeof(P)).Cast<int>().Max();
            _m = new int[width + 1 ,height + 1];

            Initialize();
        }

        void Initialize()
        {
            _m[(int)ActivityDifficulty.Easy, (int)P.Detoriated] = (int)ActivityDifficulty.Easy;
            _m[(int)ActivityDifficulty.Easy, (int)P.Unchanged] = (int)ActivityDifficulty.Easy;
            _m[(int)ActivityDifficulty.Easy, (int)P.Improved] = (int)ActivityDifficulty.Normal;

            _m[(int)ActivityDifficulty.Normal, (int)P.Detoriated] = (int)ActivityDifficulty.Easy;
            _m[(int)ActivityDifficulty.Normal, (int)P.Unchanged] = (int)ActivityDifficulty.Normal;
            _m[(int)ActivityDifficulty.Normal, (int)P.Improved] = (int)ActivityDifficulty.Hard;

            _m[(int)ActivityDifficulty.Hard, (int)P.Detoriated] = (int)ActivityDifficulty.Normal;
            _m[(int)ActivityDifficulty.Hard, (int)P.Unchanged] = (int)ActivityDifficulty.Hard;
            _m[(int)ActivityDifficulty.Hard, (int)P.Improved] = (int)ActivityDifficulty.Hard;
        }

        public ActivityDifficulty Get(ActivityDifficulty lastDifficulty, P change)
        {
            var width = (int)lastDifficulty;
            var height = (int)change;
            return (ActivityDifficulty)_m[width, height];
        }
    }
}