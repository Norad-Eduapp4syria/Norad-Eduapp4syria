using Assets.Common.Missions;
using System;
using UnityEngine;

public class ScoreDisplayDebugScript : MonoBehaviour {

	// Use this for initialization
	void Start ()
	{
	    SwipeUpDownTouchInteraction.PositionChanging += PositionChanging;
	}

    void PositionChanging(Position pos)
    {
        var tm = GetComponent<TextMesh>();

        var currentMission = MissionManager.CurrentMission;
        var activityScore = currentMission.EvaluateActivity(MissionManager.CurrentMission.Activities.Current.EvaluateActivity(), currentMission.CompletedActivities, currentMission.Score);
        
        tm.text = string.Format("{0}: {1} in {2}s = {3}p", activityScore.ActivityResult.ActivityType.Name,  activityScore.ActivityResult.Result, Mathf.RoundToInt(activityScore.ActivityResult.TimeToCompleteInSeconds), activityScore.Score);

        tm.text += Environment.NewLine;
        tm.text += string.Format("Progress: {0} -> {1} ({2})", MissionManager.CurrentMission.Score, activityScore.NewMissionScore, activityScore.P);

    }

    public static Percentage CurrentMissionPercentage;
    public static ActivityResult CurrentActivityResult;
	
	// Update is called once per frame
	void Update () {

	}
}
