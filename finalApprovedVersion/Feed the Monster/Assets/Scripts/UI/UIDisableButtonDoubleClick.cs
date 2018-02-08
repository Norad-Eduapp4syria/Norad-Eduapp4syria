using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIDisableButtonDoubleClick : MonoBehaviour {

	[Range(0.1f, 10f)]
	public float DisableSeconds = 1f;

	Button btn;
	bool isDisable;
	float time;

	void Start () {
		btn = gameObject.GetComponent<Button> ();
		if (btn != null) {
			btn.onClick.AddListener(onClick);
		}
	}

	void OnEnable()
	{
		isDisable = false;
		time = 0;
	}

	void Update () {
		if (isDisable) {
			time += Time.deltaTime;

			if (time >= DisableSeconds) {
				isDisable = false;
				btn.interactable = true;
				time = 0;
			}
		}
	}

	void onClick() {
		isDisable = true;
		time = 0;
		btn.interactable = false;
		Debug.Log ("Button Clicked");
	}

}
