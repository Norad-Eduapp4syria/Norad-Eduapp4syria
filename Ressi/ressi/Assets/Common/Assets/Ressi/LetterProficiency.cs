using System;
using UnityEngine;

namespace Assets.Common.Assets.Ressi
{
    [Serializable]
    public class LetterProficiency
    {
        public const int MinValue = 0;
        public const int MaxValue = 100;

        [SerializeField]
        int _proficiency;
        [SerializeField]
        Letter _letter;

        public LetterProficiency(Letter letter, int startingProficiency)
        {
            _proficiency = startingProficiency;
            _letter = letter;
        }

        public int Proficiency { get { return _proficiency; } }
        public Letter Letter { get { return _letter; } }

        public void AddProficiency(int change)
        {
            _proficiency = Mathf.Clamp(_proficiency + change, MinValue, MaxValue);
        }
    }
}
