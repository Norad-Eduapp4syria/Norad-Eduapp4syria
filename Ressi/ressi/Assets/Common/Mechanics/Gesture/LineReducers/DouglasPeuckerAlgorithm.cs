using Assets.Common.Mechanics.Gesture.ReductionAlgorithms;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Assertions;

namespace Assets.Common.Mechanics.Gesture.LineReducers
{
    //Heavily modified. Not vanilla reduction algo
    public class DouglasPeuckerAlgorithm : ILineReducer
    {
        public IList<Vector2> ReduceLine(IList<Vector2> points, float tolerance, int targetNodeCount)
        {
            if (points.Count <= 2)
                return points.ToList();

            var firstPoint = points.First();
            var lastPoint = points.Last();

            switch (targetNodeCount)
            {
                case 2:
                    return new List<Vector2> { firstPoint, lastPoint };
                case 1:
                    return new List<Vector2> { firstPoint };
                case 0:
                    return new List<Vector2>();
            }

            if (targetNodeCount > points.Count)
            {
                Debug.LogError("Cannot produce the requested number of nodes");
                return new List<Vector2>();
            }

            var maxDistance = 0.0f;
            var index = 0;

            var distances = new float[points.Count];
            for (var i = 1; i < points.Count - 1; i++)
            {
                var distance = PerpendicularDistance(firstPoint, lastPoint, points[i]);
                distances[i] = distance;
                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    index = i;
                }
            }

            if (maxDistance > tolerance)
            {
                var leftDistanceSum = distances.Take(index).Sum();
                var rightDistanceSum = distances.Skip(index).Sum();
                var leftWeight = leftDistanceSum / (leftDistanceSum + rightDistanceSum);
                var rightWeight = rightDistanceSum / (leftDistanceSum + rightDistanceSum);
                var leftNodes = Mathf.RoundToInt(leftWeight * targetNodeCount);
                var rightNodes = Mathf.RoundToInt(rightWeight * targetNodeCount);

                //Debug sanity check
                Assert.AreEqual(targetNodeCount, leftNodes + rightNodes);

                var leftPoints = ReduceLine(points.Take(index).ToList(), tolerance, leftNodes);
                var rightPoints = ReduceLine(points.Skip(index).ToList(), tolerance, rightNodes);

                var savedPoints = new List<Vector2>(leftPoints);
                savedPoints.AddRange(rightPoints);
                return savedPoints;
            }
            else
            {
                distances[0] = Mathf.Infinity;
                distances[distances.Length - 1] = Mathf.Infinity;
                var largestDistances = distances
                    .Select((el, idx) => new { distance = el, index = idx })
                    .OrderByDescending(i => i.distance)
                    .Take(targetNodeCount);
                return largestDistances.OrderBy(i => i.index).Select(i => points[i.index]).ToList();
            }
        }

        static float PerpendicularDistance(Vector2 Point1, Vector2 Point2, Vector2 Point)
        {
            //Area = |(1/2)(x1y2 + x2y3 + x3y1 - x2y1 - x3y2 - x1y3)|   *Area of triangle
            //Base = v((x1-x2)²+(x1-x2)²)                               *Base of Triangle*
            //Area = .5*Base*H                                          *Solve for height
            //Height = Area/.5/Base

            var area = Mathf.Abs(.5f * (Point1.x * Point2.y + Point2.x *
                Point.y + Point.x * Point1.y - Point2.x * Point1.y - Point.x *
                Point2.y - Point1.x * Point.y));
            var bottom = Mathf.Sqrt(Mathf.Pow(Point1.x - Point2.x, 2) +
                Mathf.Pow(Point1.y - Point2.y, 2));
            var height = area / bottom * 2;

            return height;
        }
    }
}
