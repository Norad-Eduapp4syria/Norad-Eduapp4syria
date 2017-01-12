using UnityEngine;
using UnityEditor;
using Assets.Common.Assets.Ressi;

[CustomPropertyDrawer(typeof(LetterProficiency))]
public class LetterProficiencyPropertyDrawer : PropertyDrawer {

    float SliderHorizontalOffset = 30f;

    public override void OnGUI(Rect position, SerializedProperty property, GUIContent label)
    {
        var letter = property.FindPropertyRelative("_letter");
        var proficiency = property.FindPropertyRelative("_proficiency");

        var letterEnum = (Letter)letter.enumValueIndex;

        EditorGUI.BeginProperty(position, new GUIContent(letterEnum.ToString()), property);

        EditorGUI.PrefixLabel(position, new GUIContent(letterEnum.ToString()));

        var sliderPosition = new Rect(position.x + SliderHorizontalOffset, position.y, position.width - SliderHorizontalOffset, position.height);
        var newValue = EditorGUI.IntSlider(sliderPosition, proficiency.intValue, LetterProficiency.MinValue, LetterProficiency.MaxValue);

        proficiency.intValue = newValue;

        if (GUI.changed)
            property.serializedObject.ApplyModifiedProperties();

        EditorGUI.EndProperty();

    }

}
