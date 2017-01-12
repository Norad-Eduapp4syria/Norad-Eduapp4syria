using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace Assets.Common.Mechanics.Gesture.Models
{
    public class GestureRecognizerResponse
    {
        public float Score { get; private set; }
        public bool IsMatch { get; private set; }
        public GestureTemplate MatchedTemplate { get; private set; }
        public ReadOnlyCollection<GestureStroke> OptimizedPoints { get; private set; }

        private GestureRecognizerResponse(IEnumerable<GestureStroke> optimizedPoints)
        {
            OptimizedPoints = new ReadOnlyCollection<GestureStroke>(optimizedPoints.ToArray());
        }

        public static GestureRecognizerResponse Fail(IEnumerable<GestureStroke> optimizedPoints)
        {
            return new GestureRecognizerResponse(optimizedPoints);
        }

        public GestureRecognizerResponse(GestureTemplate matchedTemplate, IEnumerable<GestureStroke> optimizedPoints, float score)
            : this(optimizedPoints)
        {
            Score = score;
            IsMatch = true;
            MatchedTemplate = matchedTemplate;
        }
    }
}
