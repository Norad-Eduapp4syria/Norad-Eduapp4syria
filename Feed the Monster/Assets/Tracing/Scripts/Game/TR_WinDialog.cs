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
		/// Number of stars for the WinDialog.
		/// </summary>
		private StarsNumber starsNumber;

		/// <summary>
		/// Star sound effect.
		/// </summary>
		public AudioClip starSoundEffect;

		/// <summary>
		/// Win dialog animator.
		/// </summary>
		public Animator WinDialogAnimator;

		/// <summary>
		/// First star fading animator.
		/// </summary>
		public Animator firstStarFading;

		/// <summary>
		/// Second star fading animator.
		/// </summary>
		public Animator secondStarFading;

		/// <summary>
		/// Third star fading animator.
		/// </summary>
		public Animator thirdStarFading;

		/// <summary>
		/// The level title text.
		/// </summary>
		public Text levelTitle;


	public GameObject feadback;

		/// <summary>
		/// The timer reference.
		/// </summary>
//		public Timer timer;

		/// <summary>
		/// The effects audio source.
		/// </summary>
		//private AudioSource effectsAudioSource;




		// Use this for initialization
		void Start ()
		{
			///Setting up the references
			if (WinDialogAnimator == null) {
				WinDialogAnimator = GetComponent<Animator> ();
			}

			if (firstStarFading == null) {
				firstStarFading = transform.Find ("Stars").Find ("FirstStarFading").GetComponent<Animator> ();
			}

			if (secondStarFading == null) {
				secondStarFading = transform.Find ("Stars").Find ("SecondStarFading").GetComponent<Animator> ();
			}

			if (thirdStarFading == null) {
				thirdStarFading = transform.Find ("Stars").Find ("ThirdStarFading").GetComponent<Animator> ();
			}

//			if (effectsAudioSource == null) {
//				effectsAudioSource = GameObject.Find ("AudioSources").GetComponents<AudioSource> () [1];
//			}
				
			if (levelTitle == null) {
				levelTitle = transform.Find ("Level").GetComponent<Text> ();
			}

//			if (timer == null) {
//				timer = GameObject.Find ("Time").GetComponent<Timer> ();
//			}
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

		if (feadback) {
			feadback.SetActive (true);
		}
	}

	/// <summary>
	/// Hide the Win Dialog.
	/// </summary>
	public void Hide ()
	{
		StopAllCoroutines ();
		WinDialogAnimator.SetBool ("Running", false);
		firstStarFading.SetBool ("Running", false);
		firstStarFading.transform.Find ("Effect").GetComponent<ParticleEmitter> ().emit = false;
		secondStarFading.SetBool ("Running", false);
		secondStarFading.transform.Find ("Effect").GetComponent<ParticleEmitter> ().emit = false;
		thirdStarFading.SetBool ("Running", false);
		thirdStarFading.transform.Find ("Effect").GetComponent<ParticleEmitter> ().emit = false;

		if (feadback) {
			feadback.SetActive (false);
		}

	}

		/// <summary>
		/// Fade stars Coroutine.
		/// </summary>
		/// <returns>The stars.</returns>
		public IEnumerator FadeStars ()
		{
//				starsNumber = timer.progress.starsNumber;
				float delayBetweenStars = 0.5f;
				if (starsNumber == StarsNumber.ONE) {//Fade with One Star
			if (AudioController.Instance != null) {
//				CommonUtil.PlayOneShotClipAt (starSoundEffect, Vector3.zero, effectsAudioSource.volume);
				AudioController.Instance.PlaySound (starSoundEffect);
			}
						firstStarFading.SetTrigger ("Running");
						ShowEffect (firstStarFading.transform);
				} else if (starsNumber == StarsNumber.TWO) {//Fade with Two Stars
			if (AudioController.Instance != null) {
				//CommonUtil.PlayOneShotClipAt (starSoundEffect, Vector3.zero, effectsAudioSource.volume);
				AudioController.Instance.PlaySound (starSoundEffect);
			}
						firstStarFading.SetTrigger ("Running");
						ShowEffect (firstStarFading.transform);
						yield return new WaitForSeconds (delayBetweenStars);
			if (AudioController.Instance != null) {
				//CommonUtil.PlayOneShotClipAt (starSoundEffect, Vector3.zero, effectsAudioSource.volume);
				AudioController.Instance.PlaySound (starSoundEffect);
			}
						secondStarFading.SetTrigger ("Running");
						ShowEffect (secondStarFading.transform);
				} else if (starsNumber == StarsNumber.THREE) {//Fade with Three Stars
			if (AudioController.Instance != null) {
//				CommonUtil.PlayOneShotClipAt (starSoundEffect, Vector3.zero, effectsAudioSource.volume);
				AudioController.Instance.PlaySound (starSoundEffect);
			}
						firstStarFading.SetTrigger ("Running");
						ShowEffect (firstStarFading.transform);
						yield return new WaitForSeconds (delayBetweenStars);
			if (AudioController.Instance != null) {
//				CommonUtil.PlayOneShotClipAt (starSoundEffect, Vector3.zero, effectsAudioSource.volume);
				AudioController.Instance.PlaySound (starSoundEffect);
			}
						secondStarFading.SetTrigger ("Running");
						ShowEffect (secondStarFading.transform);
						yield return new WaitForSeconds (delayBetweenStars);
			if (AudioController.Instance != null) {
//				CommonUtil.PlayOneShotClipAt (starSoundEffect, Vector3.zero, effectsAudioSource.volume);
				AudioController.Instance.PlaySound (starSoundEffect);
			}
						thirdStarFading.SetTrigger ("Running");
						ShowEffect (thirdStarFading.transform);

				}
				yield return 0;
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

		/// <summary>
		/// Set the level title.
		/// </summary>
		/// <param name="value">Value.</param>
		public void SetLevelTitle (string value)
		{
				if (string.IsNullOrEmpty (value) || levelTitle == null) {
						return;
				}
				levelTitle.text = value;
		}

		public enum StarsNumber
		{
				ONE,
				TWO,
				THREE
		}
}