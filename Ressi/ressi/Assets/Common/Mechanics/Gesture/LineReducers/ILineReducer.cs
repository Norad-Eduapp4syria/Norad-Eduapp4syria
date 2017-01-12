using System.Collections.Generic;
using UnityEngine;

namespace Assets.Common.Mechanics.Gesture.ReductionAlgorithms
{
    public interface ILineReducer
    {
        IList<Vector2> ReduceLine(IList<Vector2> points, float tolerance, int targetNodeCount);
    }
}
