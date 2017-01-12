using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class IceBoosterGaugeController : MonoBehaviour {
	public Slider slider;
	IEnumerator disapearing;
	public AudioClip iceAudio;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		slider.value = Mathf.Max(0, slider.value - Time.deltaTime / GameplaySettings.BoosterFreezeDuration);
		if (slider.value <= 0.1f)
			Disappear ();
	}

	void OnEnable(){
		transform.localScale = new Vector3 (1, 1, 1);
		AudioController.Instance.PlaySound (iceAudio);
		slider.value = 1;
	}

	public void Disappear(){
		disapearing = PopOutElement (transform);
		StartCoroutine (disapearing);
	}

	void OnDisable(){
		if(disapearing != null) {
			StopCoroutine (disapearing);
		}
	}

	IEnumerator PopOutElement(Transform transform, float delay = 0, float speed=0.08f){

		transform.localScale = new Vector3 (1, 1, 1);

		yield return new WaitForSeconds (delay);

		float[] scales = new float[] { 1.1f, 0f }; 

		foreach (float destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t+=speed)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}

		this.gameObject.SetActive (false);
		GameplayController.Instance.isFreezeTimer = false;
	}
}

