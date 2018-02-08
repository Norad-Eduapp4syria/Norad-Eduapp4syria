using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class MemoryGameCard : MonoBehaviour
,IPointerDownHandler
{
	public GameObject Top;
	public GameObject Back;
	public GameObject Shadow;
	public GameObject ParticleHolder;


	GameObject FlipParticle;
	GameObject MatchParticle;


	[HideInInspector]
	public MemoryGameCouple Couple;

	CardStatus status = CardStatus.Close;

	bool isTop;
	bool isBack;
	bool isShadow;
	int _place;
	bool isReady;

	float shikeTime;
	float shakeSpeedZ = 70f;

	enum CardStatus
	{
		Open,
		Opening,
		Close,
		Closeing,
		Wrong,
	}

	// Use this for initialization
	void Start () {
		Vector3 v = Back.transform.rotation.eulerAngles;
		v.y = 0;//180;
		Back.transform.rotation = Quaternion.Euler (v);

		if (ParticleHolder != null) {
			if (MemoryGame.Instance.FlipParticle != null) {
				FlipParticle = Instantiate (MemoryGame.Instance.FlipParticle);
				FlipParticle.transform.SetParent (ParticleHolder.transform);
				FlipParticle.transform.localPosition = Vector3.zero;
				FlipParticle.SetActive (false);
			}
		
			if (MemoryGame.Instance.MatchParticle != null) {
				MatchParticle = Instantiate (MemoryGame.Instance.MatchParticle, ParticleHolder.transform);
				MatchParticle.transform.SetParent (ParticleHolder.transform);
				MatchParticle.transform.localPosition = Vector3.zero;
				MatchParticle.SetActive (false);
			}
		}
	}


	void OnEnable()
	{
		if (FlipParticle != null) {
			FlipParticle.SetActive (false);
		}
		if (MatchParticle != null) {
			MatchParticle.SetActive (false);
		}
	}

	void OnDisable(){
		CancelInvoke ();
	}

	// Update is called once per frame
	void Update () {
		if (status == CardStatus.Close || status == CardStatus.Open) {
			return;
		}
		switch (status) {
			case CardStatus.Closeing:
				rotate ();
				break;
			case CardStatus.Opening:
				rotate ();
				break;
			case CardStatus.Wrong:
				shake ();
				if (shikeTime >= MemoryGame.Instance.shakeTime) {
					
					Vector3 v = new Vector3 ();
					v = transform.rotation.eulerAngles;
					v.z = 0;
					transform.rotation = Quaternion.Euler(v);
					Close ();
				}
				break;
		}
	}

	public void OnPointerDown (PointerEventData eventData)
	{
		if (MemoryGame.Instance.isPause) {
			return;
		}

		if (status == CardStatus.Close) {
			MemoryGame.Instance.onCardOpening ();
			status = CardStatus.Opening;
			setShadowActive (false);
			AudioController.Instance.PlaySound (MemoryGame.Instance.CardFlipSFX);
		}
	}
		
	public void init(MemoryGameCouple couple, int place, float showDelay, Sprite topSprite)
	{
		Couple = couple;
		_place = place;
		isReady = false;


		Image img = Back.GetComponent<Image> ();
		if (_place == 1) {
			img.sprite = Couple.image1;
		} else {
			img.sprite = Couple.image2;
		}

		status = CardStatus.Open;


		setTopActive (false, true);
		setBackActive (true, true);
		setShadowActive (true, true);

		Vector3 v = transform.rotation.eulerAngles;
		v.y = 180;
		transform.rotation = Quaternion.Euler (v);

		if (topSprite != null) {
			img = Top.GetComponent<Image> ();
			img.sprite = topSprite;
		}

		Invoke ("onReady", showDelay);
	}


	public void hide(float hideDelay)
	{
		Invoke ("onReady", hideDelay);
	}

	void shake()
	{
		Vector3 v = new Vector3 ();
		v = transform.rotation.eulerAngles;
		v.z = Mathf.Sin (Time.time * shakeSpeedZ);

		transform.rotation = Quaternion.Euler(v);
		shikeTime += Time.deltaTime;
	}



	void rotate()
	{
		Vector3 v = transform.rotation.eulerAngles;
		v.y += MemoryGame.Instance.rotateSpeed;

		float angle = Mathf.Abs (v.y);

		if (270f - angle <= 2f) {
			setTopActive (true);
			setBackActive (false);
		} else if (90f - angle < 2f) {
			setTopActive (false);
			setBackActive (true);
		} 
		if (status == CardStatus.Opening && (angle >= 176f && angle <= 184f )) {
			status = CardStatus.Open;
			v.y = 180;
			MemoryGame.Instance.onCardOpen (this);

			setShadowActive (true);

			if (FlipParticle) {
				FlipParticle.SetActive (true);
			}

		} else if (status == CardStatus.Closeing && (angle > 356f || angle < 4f)) {
			status = CardStatus.Close;
			v.y = 0;
			setShadowActive (true);

			if (!isReady) {
				isReady = true;
				MemoryGame.Instance.onCardReady ();
			} else {
				MemoryGame.Instance.onCardClose ();
			}
		}
		transform.rotation = Quaternion.Euler (v);
	}

	void setTopActive(bool b, bool isInit = false)
	{
		if (b != isTop || isInit) {
			Top.SetActive (b);
			isTop = b;
		}
	}

	void setBackActive(bool b, bool isInit = false)
	{
		if (b != isBack || isInit) {
			Back.SetActive (b);
			isBack = b;
		}
	}

	void setShadowActive(bool b, bool isInit = false)
	{
		if (Shadow != null) {
			if (b != isShadow || isInit) {
				Shadow.SetActive (b);
				isShadow = b;
			}
			if (b) {
				Vector3 v = Shadow.transform.localPosition;
				v.x = (isBack) ? Mathf.Abs (v.x) * -1 : Mathf.Abs (v.x);
				Shadow.transform.localPosition = v;
			}
		}
	}

	void onReady() {
		Close ();
	}

	public void Close()
	{
		if (FlipParticle) {
			FlipParticle.SetActive (false);
		}

		status = CardStatus.Closeing;
		setShadowActive (false);
	}

	public void OnWrong()
	{
		shikeTime = 0;
		status = CardStatus.Wrong;
	}

	public void OnCorrect()
	{
		MemoryGame.Instance.onCardClose ();
		StartCoroutine (PopOutElement (transform));


		if (MatchParticle != null) {
			MatchParticle.SetActive (true);
		}

	}

	IEnumerator PopOutElement(Transform transform, float speed=5.0f){

		transform.localScale = new Vector3 (1, 1, 1);

		float[] scales = new float[] { 0.9f, 1.2f, 1f }; 

		foreach (float destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}
		yield return true;
	}



}
