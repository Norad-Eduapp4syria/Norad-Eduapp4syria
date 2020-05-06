﻿using UnityEngine;
using System.Collections;

namespace EA4S.Db.Management
{
    [System.Serializable]
    public struct DatabaseInputData
    {
        public TextAsset minigameDataAsset;
        public TextAsset letterDataAsset;
        public TextAsset wordDataAsset;
        public TextAsset playSessionDataAsset;
        public TextAsset localizationDataAsset;
        public TextAsset phraseDataAsset;
        public TextAsset stageDataAsset;
        public TextAsset rewardDataAsset;

        public bool AllDataIsSet()
        {
            if (minigameDataAsset == null) return false;
            if (letterDataAsset == null) return false;
            if (wordDataAsset == null) return false;
            if (playSessionDataAsset == null) return false;
            if (localizationDataAsset == null) return false;
            if (phraseDataAsset == null) return false;
            if (stageDataAsset == null) return false;
            if (rewardDataAsset == null) return false;
            return true;
        }
    }
}