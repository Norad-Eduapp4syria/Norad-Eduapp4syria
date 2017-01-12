using System.Collections.Generic;
using Assets.Common.Mechanics.Gesture;
using Assets.Common.Mechanics.Gesture.Models;
using Assets.Common.Assets.Ressi;

public class GestureRecognizer
{
    // Normalizer settings
    const int BoundingBoxSize = 100; //The bounding box to scale gestures to
    const float Tolerance = 0.5f; //Tolerance for perpendicular distance when reducing
    //IMPORTANT: All templates must be regenerated when changing the following value:
    const int TargetNormalizationPointCount = 32; //Number of points when normalizing list,

    // Matcher settings
    const float DotDistancePenalty = 1f; //1 = no extra distance penalty

    GestureNormalizer normalizer;
    TemplateMatcher templateMatcher;

    public GestureRecognizer(GestureDebugger debugger)
    {
        normalizer = new GestureNormalizer(BoundingBoxSize, Tolerance, TargetNormalizationPointCount);
        templateMatcher = new TemplateMatcher(DotDistancePenalty, debugger);
    }

    /// <summary>
    /// If match  the recognizer will only concern itself with the given letters
    /// </summary>
    public GestureRecognizerResponse StartRecognizer(IList<Stroke> strokes, float sensitivity, params Letter[] lettersToMatch)
    {
        var normalizedStrokes = normalizer.NormalizeGesture(strokes);

        if (normalizer.IsNormalizationInvalid(normalizedStrokes))
            return GestureRecognizerResponse.Fail(normalizedStrokes);

        var matchedTemplate = templateMatcher.MatchGesture(normalizedStrokes, sensitivity, lettersToMatch);
        if (matchedTemplate == null)
            return GestureRecognizerResponse.Fail(normalizedStrokes);

        return new GestureRecognizerResponse(matchedTemplate.Template, normalizedStrokes, matchedTemplate.Score);
    }

    public static bool IsDot(Stroke stroke)
    {
        //TODO less naïve implementation
        return IsDot(stroke, TargetNormalizationPointCount);
    }

    public static bool IsDot(Stroke stroke, int lengthCutoff)
    {
        return stroke.Points.Count < lengthCutoff;
    }

}
