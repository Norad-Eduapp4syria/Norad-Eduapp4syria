using UnityEngine;
using UnityEditor;
using System;
using System.Reflection;
using UnityEditorInternal;

[CustomPropertyDrawer(typeof(SortingLayerName))]
public class SortingLayerIndexPropertyDrawer : PropertyDrawer
{
    public override void OnGUI(Rect position, SerializedProperty property, GUIContent label)
    {
        string[] layerNames = GetSortingLayerNames();

        EditorGUI.BeginProperty(position, label, property);

        Rect rect = new Rect(position.x, position.y + position.height / 2, position.width, position.height / 2);
        EditorGUI.PrefixLabel(position, GUIUtility.GetControlID(FocusType.Passive), label);

        SerializedProperty layerProp = property.FindPropertyRelative("name");
        var selectedSortingLayer = layerProp.stringValue;
        if (selectedSortingLayer == string.Empty)
            selectedSortingLayer = layerNames[0];

        var index = Array.IndexOf(layerNames, selectedSortingLayer);
        index = EditorGUI.Popup(rect, "Sorting Layer", index, layerNames);
        layerProp.stringValue = layerNames[index];

        EditorGUI.EndProperty();
    }

    public string[] GetSortingLayerNames()
    {
        Type internalEditorUtilityType = typeof(InternalEditorUtility);
        PropertyInfo sortingLayersProperty = internalEditorUtilityType.GetProperty("sortingLayerNames", BindingFlags.Static | BindingFlags.NonPublic);
        return (string[])sortingLayersProperty.GetValue(null, new object[0]);
    }

    public override float GetPropertyHeight(SerializedProperty property, GUIContent label)
    {
        return base.GetPropertyHeight(property, label) * 2;
    }
}