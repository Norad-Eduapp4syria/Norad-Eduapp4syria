using UnityEngine;

namespace Assets.Common.Mechanics.Gesture.Models
{
    public class GestureNormalizeSettings
    {
        public float WidthNormalizeFactor { get; private set; }
        public float HeightNormalizeFactor { get; private set; }
        public Vector2 GestureCenter { get; private set; }

        public GestureNormalizeSettings(float widthNormalizeFactor, float heightNormalizeFactor, Vector2 gestureCenter)
        {
            WidthNormalizeFactor = widthNormalizeFactor;
            HeightNormalizeFactor = heightNormalizeFactor;
            GestureCenter = gestureCenter;
        }
    }
}
