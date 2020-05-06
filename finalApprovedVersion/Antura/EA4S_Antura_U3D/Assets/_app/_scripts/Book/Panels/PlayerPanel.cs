﻿using UnityEngine;
using UnityEngine.UI;
using EA4S.Db;
using System.Collections.Generic;

namespace EA4S
{

    public class PlayerPanel : MonoBehaviour
    {
        public InfoTable InfoTable;
        public GraphJourney journeyGraph;
        public Image playerAvatar;

        void OnEnable()
        {

            InfoTable.Reset();
            InfoTable.AddRow("لاعب", AppManager.I.Player.Id.ToString(), "player id");
            InfoTable.AddRow("لاعب", AppManager.I.Player.CurrentJourneyPosition.ToString(), "current LB");

            //var str = "";

            //str = "hello player (ID: " + AppManager.I.Player.Id + ")\n";
            //str += "you're now in LB " + AppManager.I.Player.CurrentJourneyPosition + "\n";
            //str += "your max LB is " + AppManager.I.Player.MaxJourneyPosition + "\n";
            //str += "Mood " + AppManager.I.Player.MainMood + "\n";

            //if (AppManager.I.Player.Precision != 0f) { str += "Precision " + AppManager.I.Player.Precision + "\n"; }
            //if (AppManager.I.Player.Reaction != 0f) { str += "Reaction " + AppManager.I.Player.Reaction + "\n"; }
            //if (AppManager.I.Player.Memory != 0f) { str += "Memory " + AppManager.I.Player.Memory + "\n"; }
            //if (AppManager.I.Player.Logic != 0f) { str += "Logic " + AppManager.I.Player.Logic + "\n"; }
            //if (AppManager.I.Player.Rhythm != 0f) { str += "Rhythm " + AppManager.I.Player.Rhythm + "\n"; }
            //if (AppManager.I.Player.Musicality != 0f) { str += "Musicality " + AppManager.I.Player.Musicality + "\n"; }
            //if (AppManager.I.Player.Sight != 0f) { str += "Sight " + AppManager.I.Player.Sight + "\n"; }

            // Number of play sessions
            var allPlaySessionInfos = AppManager.I.Teacher.scoreHelper.GetAllPlaySessionInfo();
            var unlockedPlaySessionInfos = allPlaySessionInfos.FindAll(x => x.unlocked);
            //str += "Play sessions unlocked: " + unlockedPlaySessionInfos.Count + "\n";
            InfoTable.AddRow("لاعب", unlockedPlaySessionInfos.Count.ToString(), "Play sessions unlocked");

            // Total elapsed time
            var db = AppManager.I.DB;
            var tableName = db.GetTableName<LogInfoData>();
            string query = "select * from \"" + tableName + "\"";
            List<LogInfoData> list = db.FindLogInfoDataByQuery(query);

            System.TimeSpan totalTimespan = new System.TimeSpan(0);
            bool foundStart = false;
            int startTimestamp = 0;
            int endTimestamp = 0;
            foreach (var infoData in list) {
                if (!foundStart && infoData.Event == InfoEvent.AppStarted) {
                    startTimestamp = infoData.Timestamp;
                    foundStart = true;
                } else if (foundStart && infoData.Event == InfoEvent.AppClosed) {
                    endTimestamp = infoData.Timestamp;
                    foundStart = false;

                    var deltaTimespan = GenericUtilities.FromTimestamp(endTimestamp) - GenericUtilities.FromTimestamp(startTimestamp);
                    totalTimespan += deltaTimespan;
                    //Debug.Log("TIME FOUND:"  + deltaTimespan.Days + " days " + deltaTimespan.Hours + " hours " + deltaTimespan.Minutes + " minutes " + deltaTimespan.Seconds + " seconds");
                }
            }
            var timeElapsed = totalTimespan.Days + "d " + totalTimespan.Hours + "h " + totalTimespan.Minutes + "m " + totalTimespan.Seconds + "s";

            InfoTable.AddRow("لاعب", timeElapsed, "Total time elapsed");


            //AppManager.I.DB.GetLocalizationDataById("Game_Title").Arabic;
            //output.text += "\n" + AppManager.I.DB.GetLocalizationDataById("Game_Title2").Arabic;

            journeyGraph.Show(allPlaySessionInfos, unlockedPlaySessionInfos);

            playerAvatar.sprite = AppManager.I.Player.GetAvatar();
        }

    }
}