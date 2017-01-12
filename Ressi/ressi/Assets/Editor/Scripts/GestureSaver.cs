using UnityEngine;
using UnityEditor;
using Assets.Common.Mechanics.Gesture;
using System.Linq;

[CustomEditor(typeof(GestureDebugger))]
public class GestureSaver : Editor {

    GestureDebugger Debugger;
    SerializedObject GestureTracer;
    SerializedProperty Idx;


    void OnEnable()
    {
        if (target != null)
        {
            GestureTracer = new SerializedObject(target);
            Idx = GestureTracer.FindProperty("GesturePreviewIndex");
            Debugger = (GestureDebugger)target;
        }
    }


    public override void OnInspectorGUI()
    {
        if (GUILayout.Button("Save last gesture"))
        {
            var template = Debugger.CreateStringTemplateFromLastGesture();
            EditorGUIUtility.systemCopyBuffer = template;
            EditorUtility.DisplayDialog("Gesture", "Copied gesture to clipboard", "Ok");
        }

        DrawDefaultInspector();

        

        GestureTracer.Update();

        var list = GestureTemplates.Templates.Select(i => i.Name).ToList();
        list.Insert(0, "None");

        EditorGUILayout.BeginHorizontal();
        EditorGUILayout.PrefixLabel("Gesture preview");
        var index = EditorGUILayout.Popup(Idx.intValue, list.ToArray());
        EditorGUILayout.EndHorizontal();
        if (index < 0)
            return;

        Idx.intValue = index;

        if (GUI.changed)
            GestureTracer.ApplyModifiedProperties();

    }
}

