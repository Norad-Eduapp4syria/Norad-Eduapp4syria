using Assets.Common.Mechanics.Gesture.LineReducers;
using Assets.Common.Mechanics.Gesture.Models;
using Assets.Common.Mechanics.Gesture.ReductionAlgorithms;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Assets.Common.Mechanics.Gesture
{
    public class GestureNormalizer
    {
        int boundingBoxSize;
        float tolerance;
        int targetNormalizationPointCount;

        ILineReducer lineReducer;

        public GestureNormalizer(int boundingBoxSize, float tolerance, int targetNormalizationPointCount)
        {
            this.boundingBoxSize = boundingBoxSize;
            this.tolerance = tolerance;
            this.targetNormalizationPointCount = targetNormalizationPointCount;
            lineReducer = new DouglasPeuckerAlgorithm();
        }

        public IList<GestureStroke> NormalizeGesture(IList<Stroke> strokes)
        {
            var settings = GetSettings(strokes);

            var normalizedStrokes = new List<GestureStroke>();

            foreach (var stroke in strokes)
            {
                normalizedStrokes.Add(
                    NormalizeStroke(stroke, settings)
                );
            }

            return normalizedStrokes;
        }

        public bool IsNormalizationInvalid(IList<GestureStroke> strokes)
        {
            return strokes.Any(i => !i.IsDot && i.Points.Count != targetNormalizationPointCount);
        }

        GestureNormalizeSettings GetSettings(IList<Stroke> strokes)
        {
            var mainLinePoints = strokes.OrderByDescending(i => i.Points.Count).First().Points;
            var center = CalculateCenterOfGesture(mainLinePoints);

            var minX = mainLinePoints.Min(i => i.x);
            var maxX = mainLinePoints.Max(i => i.x);

            var minY = mainLinePoints.Min(i => i.y);
            var maxY = mainLinePoints.Max(i => i.y);

            var xDiff = maxX - minX;
            var yDiff = maxY - minY;
            var ratioX = xDiff / yDiff;
            var ratioY = yDiff / xDiff;

            float widthBoundingBox = boundingBoxSize;
            float heightBoundingBox = boundingBoxSize;
            if (ratioX < ratioY)
            {
                widthBoundingBox = boundingBoxSize * ratioX;
            }
            else
            {
                heightBoundingBox = boundingBoxSize * ratioY;
            }

            var widthNormalizeFactor = widthBoundingBox / xDiff;
            var heightNormalizeFactor = heightBoundingBox / yDiff;

            return new GestureNormalizeSettings(widthNormalizeFactor, heightNormalizeFactor, center);
        }


        GestureStroke NormalizeStroke(Stroke stroke, GestureNormalizeSettings settings)
        {
            return GestureRecognizer.IsDot(stroke, targetNormalizationPointCount)
                ? HandleDotStroke(stroke, settings)
                : HandleRegularStroke(stroke, settings);
        }

        GestureStroke HandleDotStroke(Stroke stroke, GestureNormalizeSettings settings)
        {
            var point = stroke.Points.First();
            var points = TranslateGestureToOrigin(new List<Vector2> { point }, settings.GestureCenter);
            points = ScaleGesture(points, settings.WidthNormalizeFactor, settings.HeightNormalizeFactor);
            return GestureStroke.AsDot(points[0]);
        }

        GestureStroke HandleRegularStroke(Stroke stroke, GestureNormalizeSettings settings)
        {
            var points = lineReducer.ReduceLine(stroke.Points, tolerance, targetNormalizationPointCount);
            points = TranslateGestureToOrigin(points, settings.GestureCenter);
            points = ScaleGesture(points, settings.WidthNormalizeFactor, settings.HeightNormalizeFactor);
            return new GestureStroke(points.ToArray());
        }

        static Vector2 CalculateCenterOfGesture(IList<Vector2> points)
        {
            var sum = points.Aggregate(new { X = 0.0f, Y = 0.0f },
                (agg, item) => new { X = agg.X + item.x, Y = agg.Y + item.y });

            return new Vector2(sum.X / points.Count, sum.Y / points.Count);
        }

        static IList<Vector2> ScaleGesture(IList<Vector2> points, float widthNormalizeFactor, float heightNormalizeFactor)
        {
            return points
                .Select(i => new Vector2(i.x * widthNormalizeFactor, i.y * heightNormalizeFactor))
                .ToList();
        }

        static IList<Vector2> TranslateGestureToOrigin(IList<Vector2> points, Vector2 center)
        {
            return points
                .Select(i => new Vector2(i.x - center.x, i.y - center.y))
                .ToList();
        }

        static float CalculateTotalGestureLength(IList<Vector2> points)
        {
            var length = 0.0f;
            for (var i = 1; i < points.Count; i++)
                length += Vector2.Distance(points[i - 1], points[i]);

            return length;
        }
    }
}
