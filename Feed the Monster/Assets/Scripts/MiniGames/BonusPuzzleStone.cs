using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class BonusPuzzleStone : MonoBehaviour
, IPointerDownHandler 
{

	public delegate void OnClickDelegate(BonusPuzzleStone stone);
	public OnClickDelegate OnClick;
	public OnClickDelegate OnDestroy;


	[Range(100f,1000f)]
	public float Speed = 500f;

	public int ScoreToAdd = 50;


	public Image image;

	public GameObject HideParticles;


	Vector2 target;
	bool isClicked;



	int ScoreForBubble;


	void Start () {
		isClicked = false;
		target = new Vector2(Random.Range (-350f, 350f), 315f);
//		if (HideParticles != null) {
//			HideParticles.SetActive (false);
//		}

	}

	void OnDisable() {
		DestroyStone ();
	}


	// Update is called once per frame
	void Update () {

		Vector2 v;

		if (isClicked) {
			return;
		}

		v = Vector3.MoveTowards(transform.localPosition, target, Time.deltaTime * Speed);
		transform.localPosition = v;

		if (v.y >= (target.y - 2)) {
			DestroyStone ();
		}
	}

	public void OnPointerDown ()
	{
		OnPointerDown (null);
	}

	public void OnPointerDown (PointerEventData eventData)
	{
		if (isClicked) {
			return;
		}

		if (OnClick != null) {
			transform.SetAsLastSibling ();
			OnClick (this);

			addScore ();
			addScorebubble ();

			if (image != null) {
				image.raycastTarget = false;
			}
//			gameObject.GetComponent<Button> ().enabled = false;

			CanvasGroup cg = gameObject.GetComponent<CanvasGroup> ();
			cg.interactable = false;
			cg.blocksRaycasts = false;


			isClicked = true;
		}
		Invoke ("DestroyStone", 0.3f);
	}


	public void addParticles()
	{
		if (HideParticles != null) {
			GameObject go = Instantiate (HideParticles);
			go.transform.SetParent (transform);
			go.transform.localPosition = Vector3.zero;
			go.transform.localScale = new Vector3(31f, 31f, 31f);

//			HideParticles.SetActive (true);
		}
	}

	void addScore() {
		if (GameplayController.Instance) {
			ScoreForBubble = GameplayController.Instance.IncreaseLevelScore (ScoreToAdd, true);
		}
	}

	void addScorebubble ()
	{
		GameObject GOScore = Instantiate(Resources.Load ("Gameplay/ScoreAnimation") as GameObject);
		GOScore.transform.SetParent (gameObject.transform, false);
		if (transform != gameObject.transform) {
			GOScore.transform.position += transform.position;
		}
		UIScoreAnimationController c = GOScore.GetComponent<UIScoreAnimationController>();
		c.gameObject.AddComponent<DestroyAfter> ().After = 1.4f;
		c.Play (ScoreForBubble);
	}


	void DestroyStone()
	{
		if (OnDestroy != null) {
			OnDestroy (this);
		}
		Destroy (gameObject);
	}

}
