using UnityEngine;
using UnityEditor;

[CustomPropertyDrawer(typeof(SceneIndex))]
public class SceneIndexPropertyDrawer : PropertyDrawer
{
    public override void OnGUI(Rect position, SerializedProperty property, GUIContent label)
    {
        string[] levelNames = new string[EditorBuildSettings.scenes.Length];
        for (int i = 0; i < EditorBuildSettings.scenes.Length; i++)
        {
            if (!EditorBuildSettings.scenes[i].enabled) continue;

            string scenePath = EditorBuildSettings.scenes[i].path;
            string[] seperators = new string[2] { "/", "." };
            string[] splitPath = scenePath.Split(seperators, System.StringSplitOptions.None);
            levelNames[i] = splitPath[splitPath.Length - 2];
        }

        EditorGUI.BeginProperty(position, label, property);

        Rect rect = new Rect(position.x, position.y + position.height / 2, position.width, position.height / 2);
        EditorGUI.PrefixLabel(position, GUIUtility.GetControlID(FocusType.Passive), label);

        SerializedProperty levelIndexProp = property.FindPropertyRelative("value");
        int selectedLevelIndex = levelIndexProp.intValue;
        selectedLevelIndex = EditorGUI.Popup(rect, "Select Scene", selectedLevelIndex, levelNames);
        levelIndexProp.intValue = selectedLevelIndex;

        EditorGUI.EndProperty();
    }

    public override float GetPropertyHeight(SerializedProperty property, GUIContent label)
    {
        return base.GetPropertyHeight(property, label) * 2;
    }
}