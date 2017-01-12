using Assets.Common.Missions.Activities.LetterActivities;
using System;
using System.Linq;

namespace Assets.Common.Missions
{
    [Serializable]
    //I Initially made this using a Dictionary so we didn't need these awful type-conditionals. Dictionaries cannot be serialized correctly, so this is the result. Rewrite
    public class MissionScore
    {
        Percentage GatherLettersScore;
        Percentage RequestLettersScore;
        Percentage DrawLettersScore;

        public MissionScore()
        {
            GatherLettersScore = new Percentage(0);
            RequestLettersScore = new Percentage(0);
            DrawLettersScore = new Percentage(0);
        }

        public bool IsComplete()
        {
            return IsComplete(GatherLettersScore, RequestLettersScore, DrawLettersScore);
        }

        bool IsComplete(params Percentage[] scores)
        {
            return scores.All(i => i == Percentage.OneHundred);
        }

        public Type GetCurrentActivity()
        {
            if (!IsComplete(GatherLettersScore))
                return typeof(GatherLettersActivity);
            if (!IsComplete(RequestLettersScore))
                return typeof(RequestLettersActivity);

            return typeof(DrawLetterActivity);
        }

        public Percentage GetScore(Type activityType)
        {
            if (activityType == typeof(GatherLettersActivity))
                return GatherLettersScore;
            if (activityType == typeof(RequestLettersActivity))
                return RequestLettersScore;
            if (activityType == typeof(DrawLetterActivity))
                return DrawLettersScore;

            return Percentage.Zero;
        }

        public void AddScore(ActivityScore activityResult)
        {
            var activityType = activityResult.ActivityResult.ActivityType;

            if (activityType == typeof(GatherLettersActivity))
                GatherLettersScore = activityResult.NewMissionScore;
            if (activityType == typeof(RequestLettersActivity))
                RequestLettersScore = activityResult.NewMissionScore;
            if (activityType == typeof(DrawLetterActivity))
                DrawLettersScore = activityResult.NewMissionScore;
        }

        public override string ToString()
        {
            return string.Format("GatherLettersScore: {0}, RequestLettersScore: {1}, DrawLettersScore: {2}", GatherLettersScore, RequestLettersScore, DrawLettersScore);
        }
    }
}
