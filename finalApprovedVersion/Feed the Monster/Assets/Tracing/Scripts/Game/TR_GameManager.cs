using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

///Developed by Indie Studio
///https://www.assetstore.unity3d.com/en/#!/publisher/9268
///www.indiestd.com
///info@indiestd.com
///copyright © 2016 IGS. All rights reserved.

public class TR_GameManager : MonoBehaviour
{
	public delegate void onCompleteDelegate();
	public onCompleteDelegate onComplete;





	/// <summary>
	/// Whether the script is running or not.
	/// </summary>
	public bool isRunning = true;

	/// <summary>
	/// The shapes list.
	/// </summary>
	public GameObject[] shapes;
	private Queue<GameObject> shapesQueue;


	/// <summary>
	/// The current pencil Color.
	/// </summary>
	public Color currentPencilColor;

		/// <summary>
		/// The path.
		/// </summary>
		private TR_Path path;

		/// <summary>
		/// The shape parent.
		/// </summary>
		public Transform shapeParent;

		/// <summary>
		/// The shape reference.
		/// </summary>
		[HideInInspector]
		public TR_Shape shape;

		/// <summary>
		/// The path fill image.
		/// </summary>
		private Image pathFillImage;

		/// <summary>
		/// The click postion.
		/// </summary>
		private Vector3 clickPostion;

		/// <summary>
		/// The direction between click and shape.
		/// </summary>
		private Vector2 direction;

		/// <summary>
		/// The current angle , angleOffset and fill amount.
		/// </summary>
		private float angle, angleOffset, fillAmount;

		/// <summary>
		/// The clock wise sign.
		/// </summary>
		private float clockWiseSign;

		/// <summary>
		/// The hand reference.
		/// </summary>
		public Transform hand;
		
		/// <summary>
		/// The default size of the cursor.
		/// </summary>
		private Vector3 cursorDefaultSize;

		/// <summary>
		/// The click size of the cursor.
		/// </summary>
		private Vector3 cursorClickSize;

		/// <summary>
		/// The target quarter of the radial fill.
		/// </summary>
		private float targetQuarter;

		/// <summary>
		/// The bright effect.
		/// </summary>
		public Transform brightEffect;

		/// <summary>
		/// The window dialog reference.
		/// </summary>
		public TR_WinDialog winDialog;

		/// <summary>
		/// The completed sound effect.
		/// </summary>
//		public AudioClip completedSFX;

		/// <summary>
		/// The correct sound effect.
		/// </summary>
//		public AudioClip correctSFX;
		public AudioClip[] correctSFX;


		int lastCorrectSFXIndex = 0;



		/// <summary>
		/// The wrong sound effect.
		/// </summary>
		public AudioClip wrongSFX;

		/// <summary>
		/// The hit2d reference.
		/// </summary>
		private RaycastHit2D hit2d;
	
		// Use this for initialization
	void Start ()
	{
		//Initiate values and setup the references
		cursorDefaultSize = hand.transform.localScale;
		cursorClickSize = cursorDefaultSize / 1.2f;

		ResetTargetQuarter ();
//		SetShapeOrderColor ();
//		CreateShape ();
	}

	void OnEnable()
	{

	}

	void OnDisable() {
		if (shape != null && shape.transform.parent == shapeParent) {
			Destroy(shape.gameObject);
		}
	}



	// Update is called once per frame
	void Update ()
	{
		//Game Logic is here
		if (GameplayController.Instance != null) {
			DrawHand (GetCurrentPlatformClickPosition (MiniGameController.Instance.canvasCamera));
			DrawBrightEffect (GetCurrentPlatformClickPosition (MiniGameController.Instance.canvasCamera));
		}
		if (shape == null) {
			return;
		}	

		if (shape.completed) {
			return;
		}

		if (Input.GetMouseButtonDown (0)) {
			if (!shape.completed) {
				brightEffect.GetComponent<ParticleEmitter> ().emit = true;
			}
			
			hit2d = Physics2D.Raycast (GetCurrentPlatformClickPosition (MiniGameController.Instance.canvasCamera), Vector2.zero);
			if (hit2d.collider != null) {
				if (hit2d.transform.tag == "Start") {
					OnStartHitCollider (hit2d);
					shape.CancelInvoke ();
					shape.DisableTracingHand ();
					EnableHand ();
				} else if (hit2d.transform.tag == "Collider") {
					shape.DisableTracingHand ();
					EnableHand ();
				}
			}
		} else if (Input.GetMouseButtonUp (0)) {
			brightEffect.GetComponent<ParticleEmitter> ().emit = false;
			DisableHand ();
			shape.Invoke ("EnableTracingHand", 1);
			ResetPath ();
		}
		if (!isRunning || path == null || pathFillImage == null) {
				return;
		}

		if (path.completed) {
				return;
		}
		
		hit2d = Physics2D.Raycast (GetCurrentPlatformClickPosition (MiniGameController.Instance.canvasCamera), Vector2.zero);
		if (hit2d.collider == null) {
			if (wrongSFX != null && AudioController.Instance) {
				AudioController.Instance.PlaySound (wrongSFX);
				//CommonUtil.PlayOneShotClipAt (wrongSFX, Vector3.zero, effectsAudioSource.volume);
			}
			ResetPath ();
			return;
		}
		
		if (path.fillMethod == TR_Path.FillMethod.Radial) {
			RadialFill ();
		} else if (path.fillMethod == TR_Path.FillMethod.Linear) {
			LinearFill ();
		} else if (path.fillMethod == TR_Path.FillMethod.Point) {
			PointFill ();
		}
	}

	/// <summary>
	/// On the start hit collider event.
	/// </summary>
	/// <param name="hit2d">Hit2d.</param>
	private void OnStartHitCollider (RaycastHit2D hit2d)
	{
		path = hit2d.transform.GetComponentInParent<TR_Path> ();
		pathFillImage = TR_CommonUtil.FindChildByTag (path.transform, "Fill").GetComponent<Image> ();
		if (path.completed || !shape.IsCurrentPath (path)) {
			ReleasePath ();
		} else {
			path.StopAllCoroutines ();
			TR_CommonUtil.FindChildByTag (path.transform, "Fill").GetComponent<Image> ().color = currentPencilColor;
		}
	}

		/// <summary>
		/// Go to the Next shape.
		/// </summary>
		/*
		public void NextShape ()
		{
				if (TableShape.selectedShape.ID >= 1 && TableShape.selectedShape.ID < ShapesTable.shapes.Count) {
						//Get the next shape and check if it's locked , then do not load the next shape
						if (TableShape.selectedShape.ID + 1 <= ShapesManager.instance.shapes.Count) {
					
								if (DataManager.IsShapeLocked (TableShape.selectedShape.ID + 1)) {
										//Play lock sound effectd
										if (lockedSFX != null && effectsAudioSource != null) {
												CommonUtil.PlayOneShotClipAt (lockedSFX, Vector3.zero, effectsAudioSource.volume);
										}
										//Skip the next
										return;
								}
						}
						TableShape.selectedShape = ShapesTable.shapes [TableShape.selectedShape.ID];//Set the selected shape
						CreateShape ();//Create new shape
				
				} else {
						if (TableShape.selectedShape.ID == ShapesTable.shapes.Count) {
							StartCoroutine(SceneLoader.LoadSceneAsync("Album"));
						} else {
								//Play lock sound effectd
								if (lockedSFX != null && effectsAudioSource != null) {
										CommonUtil.PlayOneShotClipAt (lockedSFX, Vector3.zero, effectsAudioSource.volume);
								}
						}
					
				}
		}
		*/
		/// <summary>
		/// Go to the previous shape.
		/// </summary>
		/*
		public void PreviousShape ()
		{
				if (TableShape.selectedShape.ID > 1 && TableShape.selectedShape.ID <= ShapesTable.shapes.Count) {
						TableShape.selectedShape = ShapesTable.shapes [TableShape.selectedShape.ID - 2];
						CreateShape ();
				} else {
						//Play lock sound effectd
						if (lockedSFX != null && effectsAudioSource != null) {
								CommonUtil.PlayOneShotClipAt (lockedSFX, Vector3.zero, effectsAudioSource.volume);
						}
				}
		}
		*/

	public void cleanShapesQueue()
	{

		if (shapesQueue == null) {
			shapesQueue = new Queue<GameObject> ();
		} else {
			shapesQueue.Clear ();
		}
	}

	private GameObject getRandomShape()
	{
		if (shapesQueue == null) {
			cleanShapesQueue ();
		}

		if (shapesQueue.Count == 0) {

			System.Random rng = new System.Random ();
			int n = shapes.Length;
			while (n > 1) 
			{
				int k = rng.Next(n--);
				GameObject temp = shapes[n];
				shapes[n] = shapes[k];
				shapes[k] = temp;
			}
			foreach(GameObject go in shapes )
			{
				if (go != null) {
					shapesQueue.Enqueue (go);
				}
			}
		}

		return shapesQueue.Dequeue ();
//		return shapes[Random.Range(0, shapes.Length - 1)].gameObject;
	}


	public void DestroyOldShape()
	{
		if (shape != null && shape.transform.parent == shapeParent) {
			shape.transform.parent = null;
		}

		if(shape != null) {
//			Destroy (shape.gameObject);
		}
		shape = null;
	}

	public void loadShape (TR_Shape newShape)
	{
		lastCorrectSFXIndex = 0;

		winDialog.Hide ();

		DestroyOldShape ();

		if (newShape == null) {
			return;
		}

		newShape.transform.SetParent (shapeParent, true);
//		shapeGameObject.transform.localPosition = shapePrefab.transform.localPosition;
//		shapeGameObject.name = shapePrefab.name;
//		shapeGameObject.transform.localScale = shapePrefab.transform.localScale;
		shape = newShape;//GameObject.FindObjectOfType<TR_Shape> ();

		shape.Spell ();
		EnableGameManager ();
	}


	/// <summary>
	/// Create new shape.
	/// </summary>
	public void CreateShape ()
	{
		lastCorrectSFXIndex = 0;
		winDialog.Hide ();
		DestroyOldShape ();
		try {
			GameObject shapePrefab = getRandomShape();
			GameObject shapeGameObject = Instantiate (shapePrefab, Vector3.zero, Quaternion.identity) as GameObject;
			shapeGameObject.transform.SetParent (shapeParent);
			shapeGameObject.transform.localPosition = shapePrefab.transform.localPosition;
			shapeGameObject.name = shapePrefab.name;
			shapeGameObject.transform.localScale = shapePrefab.transform.localScale;
			shape = GameObject.FindObjectOfType<TR_Shape> ();
		} catch (System.Exception ex) {
			Debug.LogError ("Create Shape Error: " + ex.Message);
		}

		if (shape == null) {
			return;
		}
		shape.Spell ();
		EnableGameManager ();
	}

	/// <summary>
	/// Draw the hand.
	/// </summary>
	/// <param name="clickPosition">Click position.</param>
	private void DrawHand (Vector3 clickPosition)
	{
		if (hand == null) {
			return;
		}
		hand.transform.position = clickPosition;
	}

	/// <summary>
	/// Set the size of the hand to default size.
	/// </summary>
	private void SetHandDefaultSize ()
	{
		hand.transform.localScale = cursorDefaultSize;
	}
	
	/// <summary>
	/// Set the size of the hand to click size.
	/// </summary>
	private void SetHandClickSize ()
	{
		hand.transform.localScale = cursorClickSize;
	}
	
	/// <summary>
	/// Get the current platform click position.
	/// </summary>
	/// <returns>The current platform click position.</returns>
	private Vector3 GetCurrentPlatformClickPosition (Camera camera)
	{
		Vector3 clickPosition = Vector3.zero;
		if (Application.isMobilePlatform) {//current platform is mobile
			if (Input.touchCount != 0) {
				Touch touch = Input.GetTouch (0);
				clickPosition = touch.position;
			}
		} else {//others
			clickPosition = Input.mousePosition;
		}
	
		clickPosition = camera.ScreenToWorldPoint (clickPosition);//get click position in the world space
		clickPosition.z = 0;
		return clickPosition;
	}

	/// <summary>
	/// Radial the fill method.
	/// </summary>
	private void RadialFill ()
	{
		clickPostion = MiniGameController.Instance.canvasCamera.ScreenToWorldPoint (Input.mousePosition);
		direction = clickPostion - path.transform.position;

		angleOffset = 0;
		clockWiseSign = (pathFillImage.fillClockwise ? 1 : -1);
		
		if (pathFillImage.fillOrigin == 0) {//Bottom
			angleOffset = 0;
		} else if (pathFillImage.fillOrigin == 1) {//Right
			angleOffset = clockWiseSign * 90;
		} else if (pathFillImage.fillOrigin == 2) {//Top
			angleOffset = -180;
		} else if (pathFillImage.fillOrigin == 3) {//left
			angleOffset = -clockWiseSign * 90;
		}
		
		angle = Mathf.Atan2 (-clockWiseSign * direction.x, -direction.y) * Mathf.Rad2Deg + angleOffset;

		if (angle < 0) {
			angle += 360;
		}
		
		angle = Mathf.Clamp (angle, 0, 360);
		angle -= path.radialAngleOffset;

		if (path.quarterRestriction) {
			if (!(angle >= 0 && angle <= targetQuarter)) {
				pathFillImage.fillAmount = 0;
				return;
			}
			if (angle >= targetQuarter / 2) {
				targetQuarter += 90;
			} else if (angle < 45) {
				targetQuarter = 90;
			}
			targetQuarter = Mathf.Clamp (targetQuarter, 90, 360);
		}
		fillAmount = Mathf.Abs (angle / 360.0f);
		pathFillImage.fillAmount = fillAmount;
		CheckPathComplete ();
	}

	/// <summary>
	/// Linear fill method.
	/// </summary>
	private void LinearFill ()
	{
		clickPostion = MiniGameController.Instance.canvasCamera.ScreenToWorldPoint (Input.mousePosition);
	
		Vector3 rotation = path.transform.eulerAngles;
		rotation.z -= path.offset;
	
		Rect rect = TR_CommonUtil.RectTransformToScreenSpace (path.GetComponent<RectTransform> ());
	
		Vector3 pos1 = Vector3.zero, pos2 = Vector3.zero;

		if (path.type == TR_Path.ShapeType.Horizontal) {
			pos1.x = path.transform.position.x - Mathf.Sin (rotation.z * Mathf.Deg2Rad) * rect.width / 2.0f;
			pos1.y = path.transform.position.y - Mathf.Cos (rotation.z * Mathf.Deg2Rad) * rect.width / 2.0f;
		
			pos2.x = path.transform.position.x + Mathf.Sin (rotation.z * Mathf.Deg2Rad) * rect.width / 2.0f;
			pos2.y = path.transform.position.y + Mathf.Cos (rotation.z * Mathf.Deg2Rad) * rect.width / 2.0f;
		} else {
			pos1.x = path.transform.position.x - Mathf.Cos (rotation.z * Mathf.Deg2Rad) * rect.height / 2.0f;
			pos1.y = path.transform.position.y - Mathf.Sin (rotation.z * Mathf.Deg2Rad) * rect.height / 2.0f;
		
			pos2.x = path.transform.position.x + Mathf.Cos (rotation.z * Mathf.Deg2Rad) * rect.height / 2.0f;
			pos2.y = path.transform.position.y + Mathf.Sin (rotation.z * Mathf.Deg2Rad) * rect.height / 2.0f;
		}
		pos1.z = path.transform.position.z;
		pos2.z = path.transform.position.z;

		GameObject obj1 = GameObject.Find ("obj1");
		if (obj1 == null) {
				obj1 = new GameObject ("obj1");
		}

		GameObject obj2 = GameObject.Find ("obj2");
		if (obj2 == null) {
				obj2 = new GameObject ("obj2");
		}
		if (path.flip) {
				Vector3 temp = pos2;
				pos2 = pos1;
				pos1 = temp;
		}

		obj1.transform.position = pos1;
		obj2.transform.position = pos2;

		clickPostion.x = Mathf.Clamp (clickPostion.x, Mathf.Min (pos1.x, pos2.x), Mathf.Max (pos1.x, pos2.x));
		clickPostion.y = Mathf.Clamp (clickPostion.y, Mathf.Min (pos1.y, pos2.y), Mathf.Max (pos1.y, pos2.y));
		fillAmount = Vector2.Distance (clickPostion, pos1) / Vector2.Distance (pos1, pos2);
		pathFillImage.fillAmount = fillAmount;
		CheckPathComplete ();
	}

	/// <summary>
	/// Point fill.
	/// </summary>
	private void PointFill ()
	{
		pathFillImage.fillAmount = 1;
		CheckPathComplete ();
	}



	AudioClip getCorrectSFX ()
	{
		AudioClip clip = null;

		if (correctSFX != null) {
			if (lastCorrectSFXIndex < correctSFX.Length && correctSFX [lastCorrectSFXIndex] != null) {
				clip = correctSFX [lastCorrectSFXIndex];
				lastCorrectSFXIndex++;
			} else {
				lastCorrectSFXIndex = 0;
				clip = correctSFX [lastCorrectSFXIndex];
			}
		}
		return clip;
	}


	/// <summary>
	/// Checks wehther path completed or not.
	/// </summary>
	private void CheckPathComplete ()
	{
		if (fillAmount >= path.completeOffset) {
			path.completed = true;
			path.AutoFill ();
			path.SetNumbersVisibility (false);
			ReleasePath ();

			if (AudioController.Instance != null) {
				AudioClip clip = getCorrectSFX ();
				if (clip) {
					AudioController.Instance.PlaySound (clip);
				}
			}

			if (CheckShapeComplete ()) {
				shape.completed = true;
				OnShapeComplete ();
			} else {
				
			}
			shape.ShowPathNumbers (shape.GetCurrentPathIndex ());

			hit2d = Physics2D.Raycast (GetCurrentPlatformClickPosition (MiniGameController.Instance.canvasCamera), Vector2.zero);
			if (hit2d.collider != null) {
				if (hit2d.transform.tag == "Start") {
					if (shape.IsCurrentPath (hit2d.transform.GetComponentInParent<TR_Path> ())) {
						OnStartHitCollider (hit2d);
					}
				}
			}
		}
	}

	/// <summary>
	/// Check whether the shape completed or not.
	/// </summary>
	/// <returns><c>true</c>, if shape completed, <c>false</c> otherwise.</returns>
	private bool CheckShapeComplete ()
	{
		bool shapeCompleted = true;
//		TR_Path [] paths = GameObject.FindObjectsOfType<TR_Path> ();
		TR_Path [] paths = shape.gameObject.GetComponentsInChildren<TR_Path> ();
		foreach (TR_Path path in paths) {
			if (!path.completed) {
				shapeCompleted = false;
				break;
			}
		}
		return shapeCompleted;
	}

	/// <summary>
	/// On shape completed event.
	/// </summary>
	private void OnShapeComplete ()
	{
		DisableHand ();
		brightEffect.GetComponent<ParticleEmitter> ().emit = false;

		Animator shapeAnimator = shape.GetComponent<Animator> ();
		shapeAnimator.SetBool (shape.name, false);
		shapeAnimator.SetTrigger ("Completed");

//		DataManager.SaveShapeStars (TableShape.selectedShape.ID, CommonUtil.GetTableShapeStars (GameObject.FindObjectOfType<Progress> ().starsNumber));
//		if (TableShape.selectedShape .ID + 1 <= ShapesManager.instance.shapes.Count) {
//			DataManager.SaveShapeLockedStatus (TableShape.selectedShape.ID + 1, false);
//		}
		List <Transform> paths = TR_CommonUtil.FindChildrenByTag (shape.transform.Find ("Paths"), "Path");
		/*
		int from, to;
		string [] slices;
		foreach (Transform p in paths) {
				slices = p.name.Split ('-');
				from = int.Parse (slices [1]);
				to = int.Parse (slices [2]);
//				DataManager.SaveShapePathColor (TableShape.selectedShape.ID, from, to, CommonUtil.FindChildByTag (p, "Fill").GetComponent<Image> ().color);
		}
*/
//		timer.Stop ();
//		Area.Show ();
		winDialog.Show ();
//		GameObject.Find ("NextButton").GetComponent<Animator> ().SetTrigger ("Select");
//		completeEffect.emit = true;
//			CommonUtil.PlayOneShotClipAt (completedSFX, Vector3.zero, effectsAudioSource.volume);
//			AudioController.Instance.PlaySound (completedSFX);

		Invoke("HideWinDialog", 1.0f);
		if (onComplete != null) {
//			shape.hide ();
			//onComplete ();
		}
//		Invoke("CreateShape", 1.5f);
	}


	void HideWinDialog()
	{
//		shape.DisableTracingHand ();
//		shape.hide ();
		winDialog.Hide ();

		Animator shapeAnimator = shape.GetComponent<Animator> ();
		shapeAnimator.SetBool("Completed", false);

		if (onComplete != null) {
			onComplete ();
		}
	}





		/// <summary>
		/// Draw the bright effect.
		/// </summary>
		/// <param name="clickPosition">Click position.</param>
		private void DrawBrightEffect (Vector3 clickPosition)
		{
				if (brightEffect == null) {
						return;
				}
		
				clickPosition.z = 0;
				brightEffect.transform.position = clickPosition;
		}

		/// <summary>
		/// Reset the shape.
		/// </summary>
/*
		public void ResetShape ()
		{
				if (shape == null) {
						return;
				}
			
				completeEffect.emit = false;
//				GameObject.Find ("NextButton").GetComponent<Animator> ().SetBool ("Select", false);
				Area.Hide ();
				winDialog.Hide ();
				shape.completed = false;
				shape.GetComponent<Animator> ().SetBool ("Completed", false);
				shape.CancelInvoke ();
				shape.DisableTracingHand ();
				Path [] paths = GameObject.FindObjectsOfType<Path> ();
				foreach (Path path in paths) {
						path.Reset ();
				}
				shape.Invoke ("EnableTracingHand", 2);
				shape.ShowPathNumbers (shape.GetCurrentPathIndex ());
//				timer.Reset ();
				shape.Spell ();
		}
*/
	/// <summary>
	/// Reset the path.
	/// </summary>
	private void ResetPath ()
	{
		if (path != null) 
				path.Reset ();
		ReleasePath ();
		ResetTargetQuarter ();
	}

	/// <summary>
	/// Reset the target quarter.
	/// </summary>
	private void ResetTargetQuarter ()
	{
		targetQuarter = 90;
	}

	/// <summary>
	/// Release the path.
	/// </summary>
	private void ReleasePath ()
	{
		path = null;
		pathFillImage = null;
	}


	/// <summary>
	/// Enable the hand.
	/// </summary>
	public void EnableHand ()
	{
		hand.GetComponent<SpriteRenderer> ().enabled = true;
	}

	/// <summary>
	/// Disable the hand.
	/// </summary>
	public void DisableHand ()
	{
		hand.GetComponent<SpriteRenderer> ().enabled = false;
	}

	/// <summary>
	/// Disable the game manager.
	/// </summary>
	public void DisableGameManager ()
	{
		isRunning = false;
	}
	
	/// <summary>
	/// Enable the game manager.
	/// </summary>
	public void EnableGameManager ()
	{
		isRunning = true;
	}
}