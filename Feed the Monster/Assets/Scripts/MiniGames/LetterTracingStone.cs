using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LetterTracingStone : MonoBehaviour {

	public delegate void onCompleteDelegate();
	public onCompleteDelegate onCompleteIdle;
	public onCompleteDelegate onCompleteGame;



	public Vector2 IdlePosition;
	public Vector2 IdleScale = new Vector2(1f,1f);


	public Vector2 GamePosition;
	public Vector2 GameScale = new Vector2(1f,1f);



	bool isInGame = false;

	TR_Shape _shape;
	Vector3 mShapeInitPosition;
	Vector3 mShapeInitScale;



	public TR_Shape shape
	{
		get { 
			if (_shape == null) {
				_shape = gameObject.GetComponentInChildren<TR_Shape> ();
				mShapeInitPosition = _shape.transform.localPosition;
				mShapeInitScale = _shape.transform.localScale;
			}
			return _shape;
		}
	}



	// Use this for initialization
	void Start ()
	{

	}

	void OnEnable()
	{
	}

	void OnDisable() {
		CancelInvoke ();
		iTween.Stop (gameObject);
		Reset (0);
	}

	// Update is called once per frame
	void Update ()
	{

	}


	public void Reset(float stoneCount)
	{
		isInGame = false;
		transform.localScale = IdleScale;
		//		transform.position = IdlePosition;

		iTween.MoveTo (gameObject, 
			iTween.Hash (
				"x", IdlePosition.x,
				"y", IdlePosition.y,
				"islocal", false,
				"time", 0.0f
			)
		);
	}


	public void OpenGame()
	{
		if (!isInGame) {
			iTween.MoveTo (gameObject, 
				iTween.Hash (
					"x", GamePosition.x,
					"y", GamePosition.y,
					"z", 0f,
					"islocal", false,
					"oncomplete", "onGame", 
					"easetype", iTween.EaseType.easeInOutBack,
					"time", 1.0f
				)
			);
			//iTween.ScaleTo (gameObject, GameScale, 1f);

			iTween.ScaleTo (gameObject, 
				iTween.Hash (
					"x", GameScale.x,
					"y", GameScale.y,
					"easetype", iTween.EaseType.easeInOutBack,
					"time", 1.0f
				)
			);
			isInGame = true;
		}
	}

	public void CloseGame()
	{
		shape.transform.SetParent (transform, true);
		shape.transform.localPosition = mShapeInitPosition;
		shape.transform.localScale = mShapeInitScale;

		if (isInGame) {
			iTween.MoveTo (gameObject, 
				iTween.Hash (
					"x", IdlePosition.x,
					"y", IdlePosition.y,

					"islocal", false,
					"oncomplete", "onIdle", 
					"easetype", iTween.EaseType.easeInOutBack,
//					"delay", 0.3f,
					"time", 0.6f
				)
			);
			//iTween.ScaleTo (gameObject, IdleScale, 1f);

			iTween.ScaleTo (gameObject, 
				iTween.Hash (
					"x", IdleScale.x,
					"y", IdleScale.y,
					"easetype", iTween.EaseType.easeInOutBack,
					"time", 0.6f
				)
			);

			isInGame = false;
		}
	}

	void onIdle()
	{
		shape.DisableTracingHand ();
		if (onCompleteIdle != null) {
			onCompleteIdle ();
		}
	}

	void onGame() {
		if (onCompleteGame != null) {
			onCompleteGame ();
		}
//		shape.init ();
	}


}
