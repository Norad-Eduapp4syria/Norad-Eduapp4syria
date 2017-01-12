using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class RandomOpacityChanger : MonoBehaviour {


	private SpriteRenderer spriteRenderer;

	private Color32 newColor;
	private bool reset = true;
	public float ResetTime;

	public byte[] transprancyList;
	int counter=0;


	//public int MinOpacity;
	//public int MaxOpacity;

	void Start () {
		spriteRenderer = this.GetComponent<SpriteRenderer> ();
	
		newColor = spriteRenderer.color;

	

	}
	

	void Update () {
		if (reset) {
			StartCoroutine (HazeEffect ());
		}
	
			spriteRenderer.color = Color32.Lerp ( spriteRenderer.color, newColor, 2f*Time.deltaTime);

	
	}

	IEnumerator HazeEffect(){
		reset = false;
		newColor = new Color32 (newColor.r, newColor.g, newColor.b,transprancyList[counter]);
		counter++;
		counter = counter % transprancyList.Length;
		yield return new WaitForSeconds (ResetTime);
		reset = true;
	}

	void OnApplicationFocus(bool focus){
		if (focus) {
			
		}
	}



}
