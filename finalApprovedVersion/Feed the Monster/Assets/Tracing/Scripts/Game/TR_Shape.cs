using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

///Developed by Indie Studio
///https://www.assetstore.unity3d.com/en/#!/publisher/9268
///www.indiestd.com
///info@indiestd.com
///copyright © 2016 IGS. All rights reserved.

public class TR_Shape : MonoBehaviour
{
	/// <summary>
	/// The paths of the shape.
	/// </summary>
	public List<TR_Path> paths = new List<TR_Path> ();

	/// <summary>
	/// The audio clip of the shape , used for spelling.
	/// </summary>
	public AudioClip clip;

	/// <summary>
	/// Whether the shape is completed or not.
	/// </summary>
	[HideInInspector]
	public bool completed;

	UIPopInOut popOut;

	// Use this for initialization
	void Start ()
	{

	}



	public void init() {
		if (paths.Count != 0) {
			Invoke ("EnableTracingHand", 0.2f);
			ShowPathNumbers (0);
		}
		popOut = gameObject.AddComponent<UIPopInOut> ();
		popOut.PopIn ();

		Analitics.TreckScreen (AnaliticsCategory.TracingGame + " " + gameObject.name);
	}

	/// <summary>
	/// Spell the shape.
	/// </summary>
	public void Spell ()
	{
		if (clip == null) {
			return;
		}
		if (AudioController.Instance != null) {
			AudioController.Instance.PlaySound (clip);
		}
	}

	/// <summary>
	/// Show the numbers of the path .
	/// </summary>
	/// <param name="index">Index.</param>
	public void ShowPathNumbers (int index)
	{
		for (int i = 0; i < paths.Count; i++) {
			if (paths [i] != null) {
				if (i != index) {
					paths [i].SetNumbersStatus (false);
				} else {
					paths [i].SetNumbersStatus (true);
				}
			}
		}
	}

	/// <summary>
	/// Get the index of the current path.
	/// </summary>
	/// <returns>The current path index.</returns>
	public int GetCurrentPathIndex ()
	{
		int index = -1;
		for (int i = 0; i < paths.Count; i++) {
			if (paths [i].completed) {
				continue;
			}
			bool isCurrentPath = true;
			for (int j = 0; j < i; j++) {
				if (!paths [j].completed) {
					isCurrentPath = false;
					break;
				}
			}
			if (isCurrentPath) {
				index = i;
					break;
			}
		}
		return index;
	}

	/// <summary>
	/// Determine whether this instance is current path or not.
	/// </summary>
	/// <returns><c>true</c> if this instance is current path; otherwise, <c>false</c>.</returns>
	/// <param name="path">Path.</param>
	public bool IsCurrentPath (TR_Path path)
	{
		bool isCurrentPath = false;
		if (path == null) {
			return isCurrentPath;
		}
		isCurrentPath = true;
		for (int i = 0; i < paths.Count; i++) {
			if (paths [i].GetInstanceID () == path.GetInstanceID ()) {
				for (int j = 0; j < i; j++) {
					if (!paths [j].completed) {
						isCurrentPath = false;
						break;
					}
				}
				break;
			}
		}
		return isCurrentPath;
	}

	/// <summary>
	/// Enable the tracing hand.
	/// </summary>
	public void EnableTracingHand ()
	{
		int currentPathIndex = GetCurrentPathIndex ();
		if (currentPathIndex == -1) {
				return;
		}
		Animator animator = GetComponent<Animator> ();
		animator.SetTrigger (name);
		animator.SetTrigger (paths [currentPathIndex].name.Replace ("Path", name.Split ('-') [0]));
	}

	/// <summary>
	/// Disable the tracing hand.
	/// </summary>
	public void DisableTracingHand ()
	{
		int currentPathIndex = GetCurrentPathIndex ();
		if (currentPathIndex == -1) {
			return;
		}
		Animator animator = GetComponent<Animator> ();
		//animator.SetBool (name,false);
		animator.SetBool (paths [currentPathIndex].name.Replace ("Path", name.Split ('-') [0]), false);
	}

	/// <summary>
	/// Get the title of the shape.
	/// </summary>
	/// <returns>The title.</returns>
	public string GetTitle ()
	{
		return name.Split ('-') [0];
	}


	public void hide() {
		if (popOut != null) {
			popOut.PopOut ();
		}
	}


}
