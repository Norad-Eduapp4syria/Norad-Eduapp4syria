using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIParentsReportSlider : MonoBehaviour {
	public Text ScoreText;

	public Image FillImage;
	public Image ScoreImage;

	Slider slider;


	public int Value
	{
		get
		{
			if (slider != null) {
				return (int)slider.value;
			}
			return 0;
		}
		set { 
			if (slider != null) {
				slider.value = value;
			}
			updateColor ();
			updateText ();
		}
	}

	// Use this for initialization
	void Start () {
		slider = gameObject.GetComponent<Slider> ();
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	void updateColor ()
	{
		Color color;

		if(Value > 66) {
			color = UIParentsReportPanel.Instance.ColorHigh;
		} else if(Value > 33) {
			color = UIParentsReportPanel.Instance.ColorMid;
		} else {
			color = UIParentsReportPanel.Instance.ColorLow;
		}
		if (FillImage != null) {
			FillImage.color = color;
		}
		if (ScoreImage != null) {
			ScoreImage.color = color;
		}
	}

	void updateText ()
	{
		if (ScoreText != null) {
//			float calcScore = (Value * 100) / 3;

			if (Value > 0) {
				ScoreText.text = Value.ToString ();
			} else {
				ScoreText.text = "";
			}
		}
	}


}
