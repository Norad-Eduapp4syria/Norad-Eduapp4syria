using UnityEngine;

namespace Assets.Common.ProceduralGeneration
{
    public class EndSectionGenerator
    {
        public ITransition GenerateEndSection(ActivityFactory activityFactory, Vector2 startPosition)
        {
            return new EndSectionTransition(startPosition);
        }
    }
}
