using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class IceBoosterGaugeController : MonoBehaviour {
	public AudioClip iceAudio;

	float value = 1;
	bool isRun = false;
	Animator anim;


	Animator Anim
	{
		get {
			if (anim == null) {
				anim = gameObject.GetComponent<Animator> ();
			}
			return anim;
		}
	}


	void Start () {

	}

	// Update is called once per frame
	void Update () {
		if (isRun) {
			value = Mathf.Max (0, value - Time.deltaTime / GameplaySettings.BoosterFreezeDuration);
			if (value <= 0.1f) {
				stopFrezz ();
			}
		}
	}

	void OnEnable() {

	}

	void OnDisable() {
		CancelInvoke();
	}

	public void startFrezz()
	{
		GameplayController.Instance.isFreezeTimer = true;
		AudioController.Instance.PlaySound (iceAudio);
		value = 1;
		isRun = true;

		Anim.SetBool ("IsFrost", true);
	}

	public void stopFrezz()
	{
		Anim.SetBool ("IsFrost", false);

		value = 0;
		isRun = false;
		Invoke ("StartAnim", 0.5f);
	}

	void StartAnim()
	{
		GameplayController.Instance.isFreezeTimer = false;
	}


}

