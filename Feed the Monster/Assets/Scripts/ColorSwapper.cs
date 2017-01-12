using UnityEngine;
using System.Collections;
using UnityEngine.UI;

[RequireComponent(typeof(Image))]
public class ColorSwapper : MonoBehaviour {
	public Color DefaultColor;
	public Color HighlightColor;

	Image mImageTarget;
	bool mGoHighlight;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (mGoHighlight) {
			mImageTarget.color = Vector4.MoveTowards (mImageTarget.color, HighlightColor, Time.deltaTime);
		} else {
			mImageTarget.color = Vector4.MoveTowards (mImageTarget.color, DefaultColor, Time.deltaTime);
		}
	}

	public void Highlight()
	{
		mGoHighlight = true;
	}

	public void BackToDefault()
	{
		mGoHighlight = false;
	}

	void OnEnable()
	{
		mImageTarget = GetComponent<Image> ();
	}

	void OnDisable()
	{
		mImageTarget.color = DefaultColor;
	}
}
