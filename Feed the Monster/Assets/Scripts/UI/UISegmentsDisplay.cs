using UnityEngine;
using UnityEngine.UI;
using System.Collections;

[System.Serializable]
public class SegmentDisplay {
	public Sprite SegmentEmpty;
	public Sprite SegmentFull;
}

public class UISegmentsDisplay : MonoBehaviour {

	public SegmentDisplay[] segmentsDisplays;
	// Use this for initialization
	void Start () {
		//Init (GameplayController);
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void Init(int numSegments){
		for (int i = 0; i < transform.childCount; i++) {
			Destroy (transform.GetChild (i).gameObject);
		}

		var width = GetComponent<RectTransform> ().rect.width - 25;
		var padding = width / numSegments;
		for (int i = 0; i < numSegments; i++) {
			GameObject segmentDisplayObj = new GameObject ();
			segmentDisplayObj.transform.parent = transform;
			segmentDisplayObj.transform.localScale = new Vector3 (0.9f, 0.9f, 0.9f);

			var rectTransform = segmentDisplayObj.AddComponent<RectTransform> ();
			rectTransform.localPosition = new Vector2 (10 + padding * i - width/2.0f, 2.5f);
			rectTransform.sizeDelta = new Vector2 (27.7f, 27.7f);
			if (i < segmentsDisplays.Length) {
				var img = segmentDisplayObj.AddComponent<Image> ();
				img.sprite = segmentsDisplays [i].SegmentEmpty;
				img.preserveAspect = true;
			}
		}

	}

	public void Fill(int index)
	{
		if (index < segmentsDisplays.Length) {
			transform.GetChild (index).gameObject.GetComponent<Image> ().sprite = segmentsDisplays [index].SegmentFull;
		}
	}

}
