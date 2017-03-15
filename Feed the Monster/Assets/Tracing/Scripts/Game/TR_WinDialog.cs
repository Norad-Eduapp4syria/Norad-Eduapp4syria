using UnityEngine;
using System.Collections;
using UnityEngine.UI;

///Developed by Indie Studio
///https://www.assetstore.unity3d.com/en/#!/publisher/9268
///www.indiestd.com
///info@indiestd.com
///copyright © 2016 IGS. All rights reserved.

[DisallowMultipleComponent]
public class TR_WinDialog : MonoBehaviour
{
	/// <summary>
	/// Win dialog animator.
	/// </summary>
	public Animator WinDialogAnimator;


	// Use this for initialization
	void Start ()
	{
		///Setting up the references
		if (WinDialogAnimator == null) {
			WinDialogAnimator = GetComponent<Animator> ();
			WinDialogAnimator.SetBool ("Running", false);
		}
	}

	/// <summary>
	/// When the GameObject becomes visible
	/// </summary>
	void OnEnable ()
	{
		//Hide the Win Dialog
		Hide ();
	}

	/// <summary>
	/// Show the Win Dialog.
	/// </summary>
	public void Show ()
	{
		if (WinDialogAnimator == null) {
			return;
		}
		WinDialogAnimator.SetTrigger ("Running");
	}

	/// <summary>
	/// Hide the Win Dialog.
	/// </summary>
	public void Hide ()
	{
		StopAllCoroutines ();
		WinDialogAnimator.SetBool ("Running", false);
	}


	/// <summary>
	/// Show sub stars effect.
	/// </summary>
	/// <param name="fadingStar">Fading star.</param>
	private void ShowEffect (Transform fadingStar)
	{
		if (fadingStar == null) {
			return;
		}
		StartCoroutine (ShowEffectCouroutine (fadingStar));
	}

	/// <summary>
	/// Shows sub stars effect couroutine.
	/// </summary>
	/// <returns>The effect couroutine.</returns>
	/// <param name="fadingStar">Fading star reference.</param>
	private IEnumerator ShowEffectCouroutine (Transform fadingStar)
	{
		yield return new WaitForSeconds (0.5f);
		fadingStar.Find ("Effect").GetComponent<ParticleEmitter> ().emit = true;
	}

	public enum StarsNumber
	{
		ONE,
		TWO,
		THREE
	}
}