using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

///Developed by Indie Studio
///https://www.assetstore.unity3d.com/en/#!/publisher/9268
///www.indiestd.com
///info@indiestd.com
///copyright © 2016 IGS. All rights reserved.

public class TR_CommonUtil
{
	/// <summary>
	/// Converts bool value true/false to int value 0/1.
	/// </summary>
	/// <returns>The int value.</returns>
	/// <param name="value">The bool value.</param>
	public static int TrueFalseBoolToZeroOne (bool value)
	{
		if (value) {
			return 1;
		}
		return 0;
	}
	
	/// <summary>
	/// Converts int value 0/1 to bool value true/false.
	/// </summary>
	/// <returns>The bool value.</returns>
	/// <param name="value">The int value.</param>
	public static bool ZeroOneToTrueFalseBool (int value)
	{
		if (value == 1) {
			return true;
		} else {
			return false;
		}
	}
	
	/// <summary>
	/// Converts from enum StarsNumber to int number value.
	/// </summary>
	/// <returns>The stars number as int.</returns>
	/// <param name="starsNumber">Stars number enum.</param>
	/*
	public static int ShapeStarsNumberEnumToIntNumber (TableShape.StarsNumber starsNumber)
	{
		if (starsNumber == TableShape.StarsNumber.ZERO) {
			return 0;
		} else if (starsNumber == TableShape.StarsNumber.ONE) {
			return 1;
		} else if (starsNumber == TableShape.StarsNumber.TWO) {
			return 2;
		} else if (starsNumber == TableShape.StarsNumber.THREE) {
			return 3;
		}
		
		return -1;//undefined
	}
	*/
	
	/// <summary>
	/// Converts from int number value to enum StarsNumber.
	/// </summary>
	/// <returns>The stars number as enum.</returns>
	/// <param name="starsNumber">Stars number as int.</param>
	/*
	public static TableShape.StarsNumber IntNumberToShapeStarsNumberEnum (int starsNumber)
	{
		if (starsNumber == 1) {
			return TableShape.StarsNumber.ONE;
		} else if (starsNumber == 2) {
			return TableShape.StarsNumber.TWO;
		} else if (starsNumber == 3) {
			return TableShape.StarsNumber.THREE;
		} else {
			return TableShape.StarsNumber.ZERO;
		}
	}
	*/

	/// <summary>
	/// Get the table shape stars.
	/// </summary>
	/// <returns>The table shape stars.</returns>
	/// <param name="starsNumber">WinDialog Stars number.</param>
	/*
	public static TableShape.StarsNumber GetTableShapeStars(WinDialog.StarsNumber starsNumber){
		if (starsNumber == WinDialog.StarsNumber.ONE) {
			return TableShape.StarsNumber.ONE;
		} else if (starsNumber == WinDialog.StarsNumber.TWO) {
			return TableShape.StarsNumber.TWO;
		}else if(starsNumber == WinDialog.StarsNumber.THREE){
			return TableShape.StarsNumber.THREE;
		}
		return 	TableShape.StarsNumber.ZERO;
	}
*/
	/// <summary>
	/// Set the size for the UI element.
	/// </summary>
	/// <param name="trans">The Rect transform referenced.</param>
	/// <param name="newSize">The New size.</param>
	public static void SetSize (RectTransform trans, Vector2 newSize)
	{
		Vector2 oldSize = trans.rect.size;
		Vector2 deltaSize = newSize - oldSize;
		trans.offsetMin = trans.offsetMin - new Vector2 (deltaSize.x * trans.pivot.x, deltaSize.y * trans.pivot.y);
		trans.offsetMax = trans.offsetMax + new Vector2 (deltaSize.x * (1f - trans.pivot.x), deltaSize.y * (1f - trans.pivot.y));
	}

	/// <summary>
	/// Covert RectTransform to screen space.
	/// </summary>
	/// <returns>The transform to screen space.</returns>
	/// <param name="transform">Transform.</param>
	public static Rect RectTransformToScreenSpace (RectTransform transform)
	{
		Vector2 size = Vector2.Scale (transform.rect.size, transform.lossyScale);
		return new Rect (transform.position.x, Screen.height - transform.position.y, size.x, size.y);
	}

	/// <summary>
	/// Find the game objects of tag.
	/// </summary>
	/// <returns>The game objects of tag(Sorted by name).</returns>
	/// <param name="tag">Tag.</param>
	public static GameObject[] FindGameObjectsOfTag (string tag)
	{
		GameObject[] gameObjects = GameObject.FindGameObjectsWithTag (tag);
		Array.Sort (gameObjects, CompareGameObjects);
		return gameObjects;
	}

	/// <summary>
	/// Finds the direct child by tag.
	/// </summary>
	/// <returns>The child by tag.</returns>
	/// <param name="p">parent.</param>
	/// <param name="childTag">Child tag.</param>
	public static Transform FindChildByTag (Transform theParent, string childTag)
	{
		if (string.IsNullOrEmpty (childTag) || theParent == null) {
			return null;
		}
		
		foreach (Transform child in theParent) {
			if (child.tag == childTag) {
				return child;
			}
		}
		
		return null;
	}

	/// <summary>
	/// Finds the direct children by tag.
	/// </summary>
	/// <returns>The children by tag.</returns>
	/// <param name="p">parent.</param>
	/// <param name="childrenTag">Child tag.</param>
	public static List<Transform> FindChildrenByTag (Transform theParent, string childTag)
	{
		List<Transform> children = new List<Transform> ();

		if (string.IsNullOrEmpty (childTag) || theParent == null) {
			return children;
		}

		foreach (Transform child in theParent) {
			if (child.tag == childTag) {
				children.Add(child);
			}
		}
		
		return children;
	}

	/// <summary>
	/// Compares the game objects.
	/// </summary>
	/// <returns>The game objects.</returns>
	/// <param name="gameObject1">Game object1.</param>
	/// <param name="gameObject2">Game object2.</param>
	private static int CompareGameObjects (GameObject gameObject1, GameObject gameObject2)
	{
		return gameObject1.name.CompareTo (gameObject2.name);
	}

	/// <summary>
	/// Enable the childern of the given gameobject.
	/// </summary>
	/// <param name="gameObject">The Gameobject reference.</param>
	public static void EnableChildern (Transform gameObject)
	{
		if (gameObject == null) {
			return;
		}
		
		foreach (Transform child in gameObject) {
			child.gameObject.SetActive (true);
		}
	}

	/// <summary>
	/// Converts RGBA string to RGBA Color , seperator is ',' 
	/// </summary>
	/// <returns>The RGBA Color.</returns>
	/// <param name="rgba">rgba string.</param>
	public static Color StringRGBAToColor (string rgba)
	{
		Color color = Color.clear;
		
		if (!string.IsNullOrEmpty (rgba)) {
			try {
				string[] rgbaValues = rgba.Split (',');
				float red = float.Parse (rgbaValues [0]);
				float green = float.Parse (rgbaValues [1]);
				float blue = float.Parse (rgbaValues [2]);
				float alpha = float.Parse (rgbaValues [3]);
				
				color.r = red;
				color.g = green;
				color.b = blue;
				color.a = alpha;
			} catch (Exception ex) {
				Debug.Log (ex.Message);
			}
		}
		return color;
	}

	/// <summary>
	/// Convert Integer value to custom string format.
	/// </summary>
	/// <returns>The to string.</returns>
	/// <param name="value">Value.</param>
	public static string IntToString (int value)
	{
		if (value < 10) {
			return "0" + value;
		}
		return value.ToString ();
	}

	/// <summary>
	/// Disable the childern of the given gameobject.
	/// </summary>
	/// <param name="gameObject">The Gameobject reference.</param>
	public static void DisableChildern (Transform gameObject)
	{
		if (gameObject == null) {
			return;
		}
		
		foreach (Transform child in gameObject) {
			child.gameObject.SetActive (false);
		}
	}

	/// <summary>
	/// Play the one shot clip.
	/// </summary>
	/// <param name="audioClip">Audio clip.</param>
	/// <param name="postion">Postion.</param>
	/// <param name="volume">Volume.</param>
	public static void PlayOneShotClipAt (AudioClip audioClip, Vector3 postion, float volume)
	{

		if (audioClip == null || volume == 0) {
			return;
		}

		GameObject oneShotAudio = new GameObject ("one shot audio"); 
		oneShotAudio.transform.position = postion; 

		AudioSource tempAudioSource = oneShotAudio.AddComponent<AudioSource> (); //add an audio source
		tempAudioSource.clip = audioClip;//set the audio clip
		tempAudioSource.volume = volume;//set the volume
		tempAudioSource.loop = false;//set loop to false
		tempAudioSource.rolloffMode = AudioRolloffMode.Linear;//linear rolloff mode
		tempAudioSource.Play ();// play audio clip
		GameObject.Destroy (oneShotAudio, audioClip.length); //destroy oneShotAudio gameobject after clip duration
	}

	/// <summary>
	/// Get random color.
	/// </summary>
	/// <returns>The random color.</returns>
	public static Color GetRandomColor ()
	{
		return new Color (UnityEngine.Random.Range (0, 255), UnityEngine.Random.Range (0, 255), UnityEngine.Random.Range (0, 255), 255) / 255.0f;
	}
}