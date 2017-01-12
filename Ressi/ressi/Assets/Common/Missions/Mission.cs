using Assets.Common.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Analytics;

namespace Assets.Common.Missions
{
    public class Mission
    {
        public ActivityBufferList Activities { get; private set; }

        readonly ActivityFactory _availableActivities;
        private readonly LevelSectionGenerator _sectionGenerator;

        public Mission(ActivityFactory availableActivities, LevelSectionGenerator sectionGenerator, GameObject backtrackBlocker)
        {
            _availableActivities = availableActivities;
            _sectionGenerator = sectionGenerator;

            Activities = new ActivityBufferList(2, backtrackBlocker);
            CompletedActivities = new ActivityScore[0];
        }

        public MissionScore Score { get { return GameStateManager.Instance.State.Score; } }

        public void Start()
        {
            if(Activities.Current != null)
                throw new InvalidOperationException("Already started");

            Analytics.CustomEvent(CustomEventNames.StartMission);

            StartNextActivity(null);

            IncludeHomeAreaInPlayingFieldBounds();
        }

        public readonly Percentage MisionTargetScore = Percentage.OneHundred;

        public ActivityScore[] CompletedActivities { get; private set; }

        public Action<Vector2> Completed;

        void StartNextActivity(ActivityScore activityScore)
        {
            var activity = _availableActivities.CreateActivity(Score, activityScore);
            var sectionForActivity = _sectionGenerator.GenerateNewSection(_availableActivities);

            var activityCallbacks = activity.Start(sectionForActivity);
            activityCallbacks.Ended = OnActivityEnded;
            activityCallbacks.PreliminaryEvaluation = result => EvaluateActivity(result, CompletedActivities, Score);

            Activities.AddNewActivity(activity);

            UpdateCameraBounds(activity);
        }

        void IncludeHomeAreaInPlayingFieldBounds()
        {
            //Assuming Home Area starts in origo
            TouchInteractions.CameraTouchInteraction.CameraRightBounds = 0f;
        }

        void UpdateCameraBounds(Activity newActivity)
        {
            var cameraInteraction = TouchInteractions.CameraTouchInteraction;
            cameraInteraction.CameraLeftBounds = Activities.Min(i => i.Section.LeftEdge.x);
            cameraInteraction.CameraRightBounds = Activities.Max(i => i.Section.RightEdge.x);

            newActivity.ModifyDefaultCameraBounds(cameraInteraction);
        }

        void OnActivityEnded(ActivityResult result)
        {
            var activityScore = EvaluateActivity(result, CompletedActivities, Score);
            
            GameStateManager.Instance.State.Score.AddScore(activityScore);

            Debug.Log("New Mission Score: " + Score);
            AddCompletedActivity(activityScore);

            Analytics.CustomEvent(CustomEventNames.EndActivity, new Dictionary<string, object> { { CustomEventData.ActivityType, result.ActivityType.Name }, { CustomEventData.ActivityScore, activityScore.ToString()}, {CustomEventData.MissionScore, Score.ToString()} });

            if (Score.IsComplete())
                FinishMission(_sectionGenerator.GetEndOfWorldCoordinates());
            else
                StartNextActivity(activityScore);
        }

        private void AddCompletedActivity(ActivityScore score)
        {
            var completedActivities = new List<ActivityScore>(CompletedActivities) { score };
            CompletedActivities = completedActivities.ToArray();
        }
        
        public ActivityScore EvaluateActivity(ActivityResult activityResult, ActivityScore[] completedActivities, MissionScore score)
        {
            var previous = completedActivities.LastOrDefault();

            var currentScore = score.GetScore(activityResult.ActivityType);

            var prevActivityScore = previous != null ? previous.Score : 0;
            var activityScore = CalculateScoreFor(activityResult);

            var p = P.Unchanged;
            var newScore = currentScore.Add(30);
            if (activityScore > prevActivityScore)
            {
                p = P.Improved;
            }
            else if (activityScore < prevActivityScore)
            {
                p = P.Detoriated;
            }
            
            // todo: but it won't be fair to get +10 if you didn't complete the activity...score could be 0,0,0,0 and you rack up +10's 
            // Ultimately, basing mission percentage strictly off P+, P= and =- is flawed, I think. Should factor in activityScore in a different way?
            switch (activityResult.Result)
            {
                case ActivityResultKind.GaveUp:
                case ActivityResultKind.UnableToComplete:
                    newScore = currentScore.Add(-10);
                    p = P.Detoriated;
                    break;
            }

            var nextActivity = _availableActivities.GetNextActivityType(score, newScore, activityResult, p);
            return new ActivityScore(activityResult, activityScore, newScore, p, nextActivity);
        }

        private static int CalculateScoreFor(ActivityResult activityResult)
        {
            float baseScore = 0;

            switch (activityResult.Result)
            {
                case ActivityResultKind.Flawless:
                    baseScore = 100;
                    break;

                case ActivityResultKind.Well:
                    baseScore = 75;
                    break;

                case ActivityResultKind.WithHelp:
                    baseScore = 50;
                    break;

                case ActivityResultKind.UnableToComplete:
                    baseScore = 0;
                    break;

                case ActivityResultKind.GaveUp:
                    baseScore = 0;
                    break;
            }

            return (int)baseScore;

            // This must be looked at more closely.
            // If a user gets flawless twice in a row, but a bit slower than last time (due to letter placement maybe?), he will deteriorate by 10 points, 
            // which serves to keep an otherwise skilled player on an activity longer than necessary

            //var normalTime = NormalTimeFor(activityResult.ActivityType);
            //var factor = normalTime/activityResult.TimeToCompleteInSeconds;
            //var score = baseScore*factor;

            //return (int)score;
        }

        private float NormalTimeFor(Type activityKind)
        {
            // todo: per activity and probably use a historic number not a constant? hard to get this right I think..
            return 60; // seconds
        }

        private void FinishMission(Vector2 leftMostEdge)
        {
            Debug.Log("Finished mission with score " + Score);

            Analytics.CustomEvent(CustomEventNames.FinishMission, new Dictionary<string, object> { {CustomEventData.MissionScore, Score.ToString()} });

            Completed.Raise(leftMostEdge);
        }
    }

    public class ActivityScore
    {
        public ActivityScore(ActivityResult activityResult, int activityScore, Percentage newMissionScore, P p, Type nextActivity)
        {
            NextActivity = nextActivity;
            NewMissionScore = newMissionScore;
            P = p;
            ActivityResult = activityResult;
            Score = activityScore;
        }

        public Type NextActivity { get; private set; } 
        public Percentage NewMissionScore { get; private set; }

        public P P { get; private set; }
        public ActivityResult ActivityResult { get; private set; }
        public int Score { get; private set; }

        public override string ToString()
        {
            return string.Format("Score: {0}, P: {1}", Score, Enum.GetName(typeof (P), P));
        }
    }

    public enum P
    {
        Unchanged,
        Detoriated,
        Improved
    }
}