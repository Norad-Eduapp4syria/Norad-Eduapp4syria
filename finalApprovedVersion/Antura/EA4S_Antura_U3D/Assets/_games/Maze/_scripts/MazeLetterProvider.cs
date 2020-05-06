﻿using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace EA4S.Maze
{
    /// <summary>
    /// Letter provider sample
    /// </summary>
    public class MazeLetterProvider : ILivingLetterDataProvider
    {
        public List<LL_LetterData> letters;
       
        public MazeLetterProvider()
        {
            letters = new List<LL_LetterData>();

            
            for (int i = 0; i < 7; ++i)
            {
                letters.Add(AppManager.I.Teacher.GetRandomTestLetterLL());
            }
        }

        

        public ILivingLetterData GetNextData()
        {
            LL_LetterData ld = letters[0];
            letters.RemoveAt(0);
          
            return ld;
        }
    }
}
