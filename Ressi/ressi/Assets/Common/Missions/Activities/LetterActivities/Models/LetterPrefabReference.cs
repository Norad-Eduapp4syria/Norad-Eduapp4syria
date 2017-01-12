using Assets.Common.Assets.Ressi;
using Assets.Common.Data;
using System;
using UnityEngine;

namespace Assets.Common.Missions.Activities.LetterActivities.Models
{
    public class LetterPrefabReference : PrefabReference
    {
        const string LetterPrefix = "Prefabs/LetterActivities/Letters/";
        const string OutlinePrefix = "Prefabs/LetterActivities/Letters/Outlines/";

        public Letter Letter { get; private set; }
        public bool HasOutline { get; private set; }

        string _prefabPath;

        ConsumableLetter _letterPrefab;
        public ConsumableLetter LetterScript
        {
            get
            {
                if (_letterPrefab == null)
                    _letterPrefab = ResourceLoader.LoadResource<GameObject>(LetterPrefix + _prefabPath).GetComponent<ConsumableLetter>();

                return _letterPrefab;
            }
        }

        public LetterPrefabReference(Letter letter, string prefabPath, bool hasOutline)
            : base(LetterPrefix + prefabPath)
        {
            Letter = letter;
            HasOutline = hasOutline;

            _prefabPath = prefabPath;
        }

        public GameObject InstantiateOutline()
        {
            if (!HasOutline)
                throw new NotSupportedException("The letter does not support outlines");

            return Instantiate(OutlinePrefix + _prefabPath);
        }
    }
}
