﻿using System.Collections;
using System.Collections.Generic;

namespace EA4S.Teacher
{
    /// <summary>
    /// Handles the selection of what minigames to play during a playsession
    /// </summary>
    public class MiniGameSelectionAI
    {
        // References
        private DatabaseManager dbManager;
        //private PlayerProfile playerProfile;

        public MiniGameSelectionAI(DatabaseManager _dbManager, PlayerProfile _playerProfile)
        {
            this.dbManager = _dbManager;
            // this.playerProfile = _playerProfile;
        }

        public void InitialiseNewPlaySession()
        {
            // Nothing to be done here
        }

        public List<Db.MiniGameData> PerformSelection(string playSessionId, int numberToSelect)
        {
            Db.PlaySessionData playSessionData = dbManager.GetPlaySessionDataById(playSessionId);

            List<Db.MiniGameData> selectedMiniGameData = null;
            switch (playSessionData.Order)
            {
                case Db.PlaySessionDataOrder.Sequence:
                    selectedMiniGameData = PerformSelection_Sequence(playSessionData, numberToSelect);
                    break;
                case Db.PlaySessionDataOrder.Random:
                    selectedMiniGameData = PerformSelection_Random(playSessionData, numberToSelect);
                    break;
            }

            return selectedMiniGameData;
        }

        private List<Db.MiniGameData> PerformSelection_Sequence(Db.PlaySessionData playSessionData, int numberToSelect)
        {
            // Get all minigame codes for the given playsession
            // ... also, use the weights to determine insertion order (used to determine the sequential order)
            SortedDictionary<float, MiniGameCode> ordered_minigamecodes = new SortedDictionary<float, MiniGameCode>();
            int fakeNumber = 1000;
            foreach (var minigameInPlaySession in playSessionData.Minigames)
            {
                if (ordered_minigamecodes.ContainsKey(minigameInPlaySession.Weight)){
                    ordered_minigamecodes[fakeNumber] = minigameInPlaySession.MiniGameCode;
                    fakeNumber++;
                }
                else
                {
                    ordered_minigamecodes[minigameInPlaySession.Weight] = minigameInPlaySession.MiniGameCode;
                }
            }

            // Get, in order, each minigame data, filter by availability (from the static DB)
            List<Db.MiniGameData> minigame_data_list = new List<Db.MiniGameData>();
            foreach(var orderedPair in ordered_minigamecodes)
            {
                var data = dbManager.GetMiniGameDataByCode(orderedPair.Value);
                if (data.Available)
                {
                    minigame_data_list.Add(data);
                }
            }

            // Number checks
            int actualNumberToSelect = UnityEngine.Mathf.Min(numberToSelect, minigame_data_list.Count);
            if (minigame_data_list.Count == 0)
            {
                throw new System.Exception("Cannot find even a single minigame for play session " + playSessionData.Id);
            }
            if (numberToSelect > minigame_data_list.Count)
            {
                UnityEngine.Debug.LogWarning("Could not select the requested number of " + numberToSelect + " minigames for play session " + playSessionData.Id + " (only " + minigame_data_list.Count + " are available)");
            }

            // Choose the first N minigames in the ordered list
            var selectedMiniGameData = minigame_data_list.GetRange(0, actualNumberToSelect);
            return selectedMiniGameData;
        }

        private List<Db.MiniGameData> PerformSelection_Random(Db.PlaySessionData playSessionData, int numberToSelect)
        { 
            // Get all minigames ids for the given playsession (from PlaySessionData)
            // ... also, keep the weights around
            Dictionary<MiniGameCode, float> playsession_weights_dict = new Dictionary<MiniGameCode, float>();
            List<string> minigame_id_list = new List<string>();
            foreach(var minigameInPlaySession in playSessionData.Minigames)
            {
                minigame_id_list.Add(minigameInPlaySession.MiniGameCode.ToString());
                playsession_weights_dict[minigameInPlaySession.MiniGameCode] = minigameInPlaySession.Weight;
            }

            // Get all minigame data, filter by availability (from the static DB)
            List<Db.MiniGameData> minigame_data_list = dbManager.FindMiniGameData(x => x.Available && minigame_id_list.Contains(x.GetId()));

            // Create the weights list too
            List<float> weights_list = new List<float>(minigame_data_list.Count);

            // Retrieve the current score data (state) for each minigame (from the dynamic DB)
            List<Db.ScoreData> minigame_score_list = dbManager.FindScoreDataByQuery("SELECT * FROM ScoreData WHERE TableName = 'MiniGames'");

            //UnityEngine.Debug.Log("M GAME SCORE LIST: " + minigame_score_list.Count);
            //foreach(var l in minigame_score_list) UnityEngine.Debug.Log(l.ElementId);

            // Determine the final weight for each minigame
            string debugString = "----- TEACHER: MiniGameSelection ----- \n";
            foreach (var minigame_data in minigame_data_list)
            {
                float cumulativeWeight = 0;
                var minigame_scoredata = minigame_score_list.Find(x => x.ElementId == minigame_data.GetId());
                int daysSinceLastScore = 0;
                if (minigame_scoredata != null)
                {
                    var timespanFromLastScoreToNow = GenericUtilities.GetTimeSpanBetween(minigame_scoredata.LastAccessTimestamp, GenericUtilities.GetTimestampForNow());
                    daysSinceLastScore = timespanFromLastScoreToNow.Days;
                }
                debugString += minigame_data.Code + " --- \t";

                // PlaySession Weight [0,1]
                float playSessionWeight = playsession_weights_dict[minigame_data.Code] / 100f; //  [0-100]
                cumulativeWeight += playSessionWeight * ConfigAI.minigame_playSessionWeight;
                debugString += " PSw: " + playSessionWeight * ConfigAI.minigame_playSessionWeight + "("+playSessionWeight+")";

                // RecentPlay Weight  [1,0]
                const float dayLinerWeightDecrease = 1f/ConfigAI.daysForMaximumRecentPlayMalus;
                float weightMalus = daysSinceLastScore * dayLinerWeightDecrease;
                float recentPlayWeight = 1f - UnityEngine.Mathf.Min(1, weightMalus);
                cumulativeWeight += recentPlayWeight * ConfigAI.minigame_recentPlayWeight;
                debugString += " RPw: " + recentPlayWeight * ConfigAI.minigame_recentPlayWeight + "(" + recentPlayWeight + ")";

                // Save cumulative weight
                weights_list.Add(cumulativeWeight);
                debugString += " TOTw: " + cumulativeWeight;
                debugString += "\n";
            }
            if (ConfigAI.verboseTeacher)
            {
                UnityEngine.Debug.Log(debugString);
            }


            // Number checks
            int actualNumberToSelect = UnityEngine.Mathf.Min(numberToSelect, minigame_data_list.Count);
            if (minigame_data_list.Count == 0)
            {
                throw new System.Exception("Cannot find even a single minigame for play session " + playSessionData.Id);
            }
            if (numberToSelect > minigame_data_list.Count)
            {
                UnityEngine.Debug.LogWarning("Could not select the requested number of " + numberToSelect + " minigames for play session " + playSessionData.Id + " (only " + minigame_data_list.Count + " are available)");
            }

            // Choose N minigames based on these weights
            var selectedMiniGameData = RandomHelper.RouletteSelectNonRepeating(minigame_data_list, weights_list, actualNumberToSelect);

            return selectedMiniGameData;
        }

    }
}