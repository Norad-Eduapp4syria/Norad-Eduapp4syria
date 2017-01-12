using Assets.Common.Assets.Ressi;
using System;
using System.Collections.ObjectModel;
using UnityEngine;

namespace Assets.Common.Mechanics.Gesture.Models
{
    public class GestureTemplate
    {
        public string Name { get; private set; }
        public Letter Letter { get; private set; }
        public ReadOnlyCollection<GestureStroke> Strokes { get; private set; }

        Func<Vector2, Vector2, float> _penaltyModifier;

        public float PenaltyModifier(Vector2 strokePoint, Vector2 pointToMatch)
        {
            if (_penaltyModifier == null)
                return 1;

            return _penaltyModifier(strokePoint, pointToMatch);
        }
        public GestureTemplate(string name, Letter letter, Func<Vector2, Vector2, float> penaltyModifier, params GestureStroke[] strokes)
        {
            _penaltyModifier = penaltyModifier;
            Name = name;
            Letter = letter;
            Strokes = new ReadOnlyCollection<GestureStroke>(strokes);
        }

        public GestureTemplate(string name, Letter letter, params GestureStroke[] strokes) : this(name, letter, null, strokes)
        {
           
        }
    }
}
