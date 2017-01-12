using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using Assets.Common.Mechanics.Gesture;
using System.Text;
using System;
using Assets.Common.Mechanics.Gesture.Models;

public class GestureDebugger : MonoBehaviour {

    public Text DebugText;
    public Text ExtendedDebug;
    public float DotSize = 5f;
    public float JointSize = 1f;

    IList<GestureStroke> LastNormalizedGesture;
    GestureTemplate LastMatchedGesture;

    [HideInInspector]
    public int GesturePreviewIndex;


    public void StrokeFinished(IList<GestureStroke> normalizedStrokes, IList<TemplateMatch> matches)
    {
        //Debug
        SetExtendedDebugText(string.Empty);
        foreach (var match in matches)
        {
            AppendExtendedDebug(string.Format("{0}: {1}\n", match.Template.Name, match.Score));
            Debug.LogFormat("Score for {0}: {1}", match.Template.Name, match.Score);
        }
    }

    public void RecognizerFinished(GestureRecognizerResponse response)
    {
        LastNormalizedGesture = response.OptimizedPoints;
        if (response.IsMatch)
        {
            LastMatchedGesture = response.MatchedTemplate;
            SetDebugText(response.MatchedTemplate.Name);
            Debug.Log("Matched with " + response.MatchedTemplate.Name + ". Score: " + response.Score);
        }
        else
        {
            LastMatchedGesture = null;
            SetDebugText("No match");
            Debug.Log("No match");
        }
    }

    void SetDebugText(string text)
    {
        if (DebugText == null)
            return;

        DebugText.text = text;
    }

    void SetExtendedDebugText(string text)
    {
        if (ExtendedDebug == null)
            return;

        ExtendedDebug.text = text;
    }

    void AppendExtendedDebug(string text)
    {
        if (ExtendedDebug == null)
            return;

        ExtendedDebug.text += text;
    }

    //Only useful when creating templates using debug->copy/paste
    public string CreateStringTemplateFromLastGesture()
    {
        if (LastNormalizedGesture == null)
            return string.Empty;

        var sb = new StringBuilder();
        sb.AppendLine("new GestureTemplate(\"TEMP\",");
        for (var i = 0; i < LastNormalizedGesture.Count; i++)
        {
            var stroke = LastNormalizedGesture[i];
            if (stroke.IsDot)
            {
                sb.AppendLine("\tGestureStroke.AsDot(new Vector2(" + stroke.DotPosition.x + "f, " + stroke.DotPosition.y + "f)");
            }
            else
            {
                sb.AppendLine("\tnew GestureStroke(");
                for (var j = 0; j < stroke.Points.Count; j++)
                {
                    var point = stroke.Points[j];
                    var separator = ",";
                    if (j == stroke.Points.Count - 1)
                        separator = "";
                    sb.AppendLine("\t\tnew Vector2(" + point.x + "f, " + point.y + "f)" + separator);
                }

               
            }
            if (i == LastNormalizedGesture.Count - 1)
                sb.AppendLine("\t)");
            else
                sb.AppendLine("\t),");
        }
        sb.AppendLine("),");
        return sb.ToString();
    }

    

    void OnDrawGizmosSelected()
    {
        DrawStrokes(LastNormalizedGesture, Color.red);

        if (GesturePreviewIndex > 0)
        {
            var templateStroke = GestureTemplates.Templates[GesturePreviewIndex - 1];
            if (templateStroke != null)
                DrawStrokes(templateStroke.Strokes, Color.yellow);
        }

        if (LastMatchedGesture == null)
            return;

        Gizmos.color = Color.blue;
        for (var j = 0; j < LastMatchedGesture.Strokes.Count; j++)
        {
            var stroke = LastMatchedGesture.Strokes[j];
            var normalizedStroke = LastNormalizedGesture[j];
            if (stroke.IsDot)
            {
                Gizmos.DrawSphere(stroke.DotPosition, DotSize);
                Gizmos.color = Color.gray;
                Gizmos.DrawLine(normalizedStroke.DotPosition, stroke.DotPosition);
                Gizmos.color = Color.blue;
            }
            else
            {
                if (stroke.Points.Count == 0)
                    return;

                Gizmos.DrawSphere(stroke.Points[0], JointSize);
                for (var i = 1; i < stroke.Points.Count; i++)
                {
                    Gizmos.DrawLine(stroke.Points[i - 1], stroke.Points[i]);
                    Gizmos.DrawSphere(stroke.Points[i], JointSize);

                    Gizmos.color = Color.gray;
                    Gizmos.DrawLine(normalizedStroke.Points[i - 1], stroke.Points[i - 1]);
                    Gizmos.DrawLine(normalizedStroke.Points[i], stroke.Points[i]);
                    Gizmos.color = Color.blue;
                }
            }
        }
    }

    void DrawStrokes(IList<GestureStroke> strokes, Color color)
    {
        if (strokes == null || strokes.Count == 0)
            return;

        Gizmos.color = color;
        foreach (var stroke in strokes)
        {
            if (stroke.IsDot)
            {
                Gizmos.DrawSphere(stroke.DotPosition, DotSize);
            }
            else
            {
                if (stroke.Points.Count == 0)
                    return;

                Gizmos.DrawSphere(stroke.Points[0], JointSize);
                for (var i = 1; i < stroke.Points.Count; i++)
                {
                    Gizmos.DrawLine(stroke.Points[i - 1], stroke.Points[i]);
                    Gizmos.DrawSphere(stroke.Points[i], JointSize);
                }
            }
        }
    }
}
