using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class AnimateAlpha : MonoBehaviour {
	public bool auto=false;
	SpriteRenderer currentRenderer;
	Image currentImage;
	  float fadeSpeed = 0.01f;
	  float fadeTime = 1f;
	bool fadeIn = true;
	float fadeValue;
	// Use this for initialization
	void Start () {
		if(this.gameObject.layer == 5)
			currentImage = GetComponent<Image> ();
		else
			currentRenderer = GetComponent<SpriteRenderer> ();


		if (auto) {
			StartAnimating ();
		}
//		InvokeRepeating ("FlipDirection",0f,0.5f);
	}

	public float  minValue =0.7f;
	public float maxValue =1.0f;
		

	public void StartAnimating(){
		InvokeRepeating ("FlipDirection",0f,0.5f);
	}

	void FlipDirection(){
		fadeIn = !fadeIn;
		if(currentRenderer!=null){
		if (fadeIn)
			currentRenderer.color = new Color(1f,1f,1f,minValue);
		else
			currentRenderer.color = new Color(1f,1f,1f,maxValue);
		}

		if(currentImage!=null){
			if (fadeIn)
				currentImage.color = new Color(1f,1f,1f,minValue);
			else
				currentImage.color = new Color(1f,1f,1f,maxValue);
		}
//		currentRenderer.color.a
	}

//	IEnumerator FadeInRoutine(){
//		while(fadeValue<0.8){
//		fadeValue = Mathf.Lerp (0f, 0.8f, Time.deltaTime);
//		Debug.Log ("In"+fadeValue);
//		currentRenderer.color = new Color(1f,1f,1f,fadeValue);
//		yield return new WaitForSeconds (0.1f);
//		}
//		//		currentRenderer.color.a
//	}
//
//	IEnumerator FadeOutRoutine(){
//		while(fadeValue>0.25){
//		fadeValue = Mathf.Lerp(1f,0.2f,Time.deltaTime);
//		Debug.Log ("Out"+fadeValue);
//		currentRenderer.color = new Color(1f,1f,1f, fadeValue);
//		yield return new WaitForSeconds (0.1f);
//		}
//	}

	// Update is called once per frame
//	void Update () {
//		if (fadeIn) {
//			fadeValue = Mathf.Lerp (0f, 1f,fadeTime * Time.deltaTime);
//			currentRenderer.color = new Color(1f,1f,1f,fadeValue);
//		}
//
//		if (!fadeIn) {
//			fadeValue = Mathf.Lerp(1f,0f,Time.deltaTime);
//			currentRenderer.color = new Color(1f,1f,1f,fadeTime *fadeValue);
//		}
//	}
}
