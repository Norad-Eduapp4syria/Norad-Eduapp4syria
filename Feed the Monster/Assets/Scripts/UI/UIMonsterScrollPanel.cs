using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using UnityEngine.Events;
using UnityEngine.EventSystems;

public class UIMonsterScrollPanel : MonoBehaviour, IEndDragHandler, IDragHandler {

	public GridLayoutGroup Content;
	public RectTransform MonsterIcon;
	private GameObject monster;

	private int count = 5;
	public int currentIndex = 0;
	private ScrollRect scroll;
	private bool _lerp = true;
	// Use this for initialization
	void Awake () {
		scroll = GetComponent<ScrollRect> ();
		Content.GetComponent<RectTransform>().sizeDelta = new Vector2 (Content.cellSize.x * (count + 2), Content.cellSize.y);
		//scroll.horizontalNormalizedPosition = 0;
		scroll.scrollSensitivity = 5;
		monster = GameObject.Find ("monster");
		if (monster != null) {
			monster.SetActive (false);
		}
		//SetChosenIndex (0);
	}
	int lastForegroundIndex = 0;
	// Update is called once per frame
	void Update () {
		int foregroundIndex = (int)Mathf.Round( scroll.horizontalNormalizedPosition * count - .5f);
		if (foregroundIndex < count && foregroundIndex != lastForegroundIndex) {
			var grayMat = Content.transform.GetChild (foregroundIndex + 1).gameObject.GetComponent<Image> ().material;
			Content.transform.GetChild (foregroundIndex + 1).gameObject.GetComponent<Image> ().material = null;
			Content.transform.GetChild (lastForegroundIndex + 1).gameObject.GetComponent<Image> ().material = grayMat;
			lastForegroundIndex = foregroundIndex;
		}

		if (_lerp) {
			if (currentIndex >= count)
				currentIndex = count - 1;
			if (Mathf.Abs(scroll.velocity.x) < 50f) {
				//Debug.Log ((float)currentIndex / count);
				scroll.horizontalNormalizedPosition = Mathf.Lerp (scroll.horizontalNormalizedPosition, ((float)currentIndex + .5f) / count, 5* Time.deltaTime);
				//if (Mathf.Abs (scroll.horizontalNormalizedPosition -  (currentIndex) / count) < 0.01f)
				//	_lerp = false;
			} else {
				OnEndDrag (null);
				///currentIndex = (int)Mathf.Round(scroll.horizontalNormalizedPosition * count);
				//Debug.Log (scroll.horizontalNormalizedPosition + "    =   =   " + currentIndex);
			}
		}
	}

	void OnEnable(){
	}

	void OnDisable(){
		Content.transform.GetChild (currentIndex + 1).localScale = new Vector3(1,1,1);
	}

	public void Select(){
		StartCoroutine (GrowToSelect ());
	}


	IEnumerator GrowToSelect(){
		var trans = Content.transform.GetChild (currentIndex + 1);
		Vector3 start = trans.localScale;
		Vector3 end = new Vector3(1.8f, 1.8f, 1.8f);
		for (float t = 0; t <= 1; t += Time.deltaTime) {
			trans.localScale = Vector3.Lerp(start , end , t*t*t);
			yield return null;
		}
		monster.SetActive (true);
		gameObject.SetActive (false);
	}

	public void OnDrag (PointerEventData eventData)
	{
		if(eventData.dragging)
			_lerp = true;
		Debug.Log ("dragging man " + eventData.dragging);
	}

	private void SetChosenIndex(int index){
		currentIndex = index;
		scroll.horizontalNormalizedPosition = (float)(currentIndex) / (count - 1);
	}


	public void OnEndDrag (PointerEventData eventData)
	{
		Debug.Log ("ended dragging man");
		currentIndex = (int)Mathf.Round( scroll.horizontalNormalizedPosition * count - .5f);
		Debug.Log (scroll.horizontalNormalizedPosition + "    =   =   " + currentIndex);
		_lerp = true;
	}

}
