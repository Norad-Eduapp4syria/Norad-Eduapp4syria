using Assets.Common.Assets.Ressi;
using Assets.Common.Missions;
using System;
using System.Collections.Generic;

namespace Assets.Common.Data
{
    [Serializable]
    public class GameState
    {
        public GameState()
        {
            LetterProficiency = new List<LetterProficiency>();
            Score = new MissionScore();
        }

        public MissionScore Score { get; set; }
        public List<LetterProficiency> LetterProficiency { get; set; }
    }
}
