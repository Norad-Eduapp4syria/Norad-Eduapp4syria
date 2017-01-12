using UnityEngine;
using UnityEditor;
using System.Collections;

///Developed by Indie Studio
///https://www.assetstore.unity3d.com/en/#!/publisher/9268
///www.indiestd.com
///info@indiestd.com
///copyright © 2016 IGS. All rights reserved.

[CustomEditor(typeof(TR_Path))]
public class TR_PathEditor : Editor {

	public override void OnInspectorGUI ()
	{
		TR_Path path = (TR_Path)target;//get the target
		
		EditorGUILayout.Separator ();
		path.fillMethod = (TR_Path.FillMethod)EditorGUILayout.EnumPopup ("Fill Method",path.fillMethod);
		if (path.fillMethod == TR_Path.FillMethod.Linear) {
			path.type = (TR_Path.ShapeType)EditorGUILayout.EnumPopup ("Type", path.type);
			path.offset = EditorGUILayout.Slider ("Angle Offset", path.offset, -360, 360);
			path.flip = EditorGUILayout.Toggle ("Flip Direction", path.flip);
		} else if (path.fillMethod == TR_Path.FillMethod.Radial) {
			path.quarterRestriction = EditorGUILayout.Toggle ("Quarter Restriction",path.quarterRestriction) ;
			path.radialAngleOffset = EditorGUILayout.Slider ("Radial Offset",path.radialAngleOffset,-360,360) ;
		}

		path.completeOffset = EditorGUILayout.Slider ("Complete Offset", path.completeOffset,0,1);
		path.firstNumber = EditorGUILayout.ObjectField ("First Number",path.firstNumber, typeof(Transform)) as Transform;
		if (path.fillMethod != TR_Path.FillMethod.Point) 
			path.secondNumber = EditorGUILayout.ObjectField ("Second Number",path.secondNumber, typeof(Transform)) as Transform;

	}
}	