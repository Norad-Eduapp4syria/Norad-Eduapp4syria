using System.Collections.ObjectModel;
using UnityEngine;

namespace Assets.Common.Mechanics.Gesture.Models
{
    public class GestureStroke
    {
        public ReadOnlyCollection<Vector2> Points { get; private set; }
        public bool IsDot { get; private set; }
        public Vector2 DotPosition { get; private set; }

        private GestureStroke(Vector2 position)
        {
            IsDot = true;
            DotPosition = position;
            Points = new ReadOnlyCollection<Vector2>(new Vector2[0]);
        }

        public static GestureStroke AsDot(Vector2 position)
        {
            return new GestureStroke(position);
        }

        public GestureStroke(params Vector2[] points)
        {
            Points = new ReadOnlyCollection<Vector2>(points);
        }
    }
}
