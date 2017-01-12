using Assets.Common.Assets.Ressi;
using Assets.Common.Mechanics.Gesture.Models;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Assets.Common.Mechanics.Gesture
{
    public class TemplateMatcher
    {
        float dotDistancePenalty;
        GestureDebugger debugger;
        
        public TemplateMatcher(float dotDistancePenalty, GestureDebugger debugger = null) 
        {
            this.dotDistancePenalty = dotDistancePenalty;
            this.debugger = debugger;
        }

        public TemplateMatch MatchGesture(IList<GestureStroke> strokes, float matchSensitivity, params Letter[] lettersToMatch)
        {
            Debug.LogFormat("Matching gesture with sensitivity cutoff set to {0}", matchSensitivity);

            var templatesToMatch = GestureTemplates.Templates;
            if (lettersToMatch != null && lettersToMatch.Length > 0)
                templatesToMatch = templatesToMatch.Where(i => lettersToMatch.Contains(i.Letter)).ToList();

            var scores = templatesToMatch
                .Where(i => i.Strokes.Count == strokes.Count)
                  .Select(i => new TemplateMatch { Template = i, Score = CalculateTemplateDistance(strokes, i) })
                  .OrderBy(i => i.Score)
                  .ToList();

            var bestMatch = scores.FirstOrDefault();

            if (bestMatch == null)
                return null;

            if (debugger != null)
                debugger.StrokeFinished(strokes, scores);

            return bestMatch.Score < matchSensitivity
                ? bestMatch
                : null;
        }

        float CalculateTemplateDistance(IList<GestureStroke> strokes, GestureTemplate templateToMatch)
        {
            var distance = 0.0f;
            for (var i = 0; i < strokes.Count; i++)
            {
                var stroke = strokes[i];
                var strokeToMatch = templateToMatch.Strokes[i];

                if (strokeToMatch.IsDot != stroke.IsDot)
                    return Mathf.Infinity;

                if (strokeToMatch.IsDot && stroke.IsDot)
                {
                    distance += Vector2.Distance(strokeToMatch.DotPosition, stroke.DotPosition) * dotDistancePenalty;
                }
                else
                {
                    if (stroke.Points.Count != strokeToMatch.Points.Count)
                    {
                        Debug.LogError("Difference in list length when calculating distance is not supported");
                        return Mathf.Infinity;
                    }
                    var tempdistance = 0.0f;
                    for (var j = 0; j < stroke.Points.Count; j++)
                    {
                        var strokePoint = stroke.Points[j];
                        var pointToMatch = strokeToMatch.Points[j];
                        var penaltyModifier = templateToMatch.PenaltyModifier(strokePoint, pointToMatch);
                        tempdistance += Vector2.Distance(strokePoint, pointToMatch) * penaltyModifier;
                    }

                    distance += (tempdistance / stroke.Points.Count);
                }
            }

            return distance;
        }

    }
}
