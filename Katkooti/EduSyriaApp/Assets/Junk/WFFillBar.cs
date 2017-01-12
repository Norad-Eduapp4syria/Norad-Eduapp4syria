using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class WFFillBar : MonoBehaviour {

	private Image wffillbar;
	private WFManager WM;
	// Use this for initialization
	void Start () {
		wffillbar = this.GetComponent<Image> ();
		WM = GameObject.FindObjectOfType<WFManager> ().GetComponent<WFManager> ();
	}
	
	// Update is called once per frame
	void Update () {


		wffillbar.fillAmount = Mathf.Lerp(wffillbar.fillAmount,(float) WM.wordCompleted/WM.words.Length,1*Time.deltaTime);

	}
}
