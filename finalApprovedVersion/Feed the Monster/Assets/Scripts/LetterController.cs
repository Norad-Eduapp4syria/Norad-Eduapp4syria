using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityEngine.UI;


public class LetterController : MonoBehaviour
//,IPointerDownHandler, IPointerEnterHandler
//,IBeginDragHandler, IDragHandler, IEndDragHandler, IDropHandler

{
	public enum LetterState{
		Inited,
		Idle,
		Showup,
		Disapear,
		Selected,
		WaitingForMonster,
		GoingToMonster,
		Eaten,
		Warning,
		Tutorial
	}



	public LetterState State{ get; set; }
	public Text text;
	//	public string value { get; private set;  }
	public Stone stone { get; private set;  }
	public float Speed;



	public Image MainImage;
	public Image OutlineImage;
	public ParticleSystem ParticlesShowup;
//	public ParticleSystem ParticlesTrail;

	public ParticleSystem ParticlesIdle;
	public GameObject ParticlesMergeAccept;
	public GameObject ParticlesMergeReject;


	public Image Star;

	public float IdleShakeSpeed;
	public float IdleShakeRadius;
	public float IdleShakeRate;

	public Vector3 mTargetPosition { get; set; }
	public AudioClip SoundAppear;
	public AudioClip SoundSelected;
	public AudioClip SoundUnselected;

	public Color FontColorDefault;
	public Color FontColorSelected;
	public Color FontOutlineColorDefault;
	public Color FontOutlineColorSelected;

	public MonsterCalloutController EatingMonster;
	public float TimeSelected { get; private set; }


	Vector3 mInitPosition;
	Vector3 mLastPosition;
	Vector3 mInitScale;
	Vector3 mTargetScale;


	Vector3 ParticlesMergeAcceptScale = new Vector3 (1, 1, 1);
	Vector3	ParticlesMergeRejectScale = new Vector3 (1, 1, 1);

	Vector3 shakeDest = new Vector3(0,0,0);
	Vector3 shakeStart;
	int shakeFrame;

	int mCurrentSpawnId;

//	float mDistanceFromHole;


	bool mShownup;
	float mTargetAngle;
	float mCurrentSpeed;
	float mTimeFromLaunch;


//	UIPopInOut popinout;
	bool isMovment = false;

	[HideInInspector]
	public int spawnId;

	[HideInInspector]
	public int numSubLetters = 0;

	[HideInInspector]
	public bool isDragable = false;

	LetterController collectLetters = null;
	LetterController mMagnetLetter;

	[HideInInspector]
	public bool isTutorial = false;

	[HideInInspector]
	public bool isActive = false;


	CanvasGroup cg;
	bool isBlinking = false;



	public Vector2 getMonsterMouth()
	{
		Transform to = GameObject.Find ("monster").transform.Find ("Mouth");
		Vector2 toPos;
		if (to == null) {
			to = EatingMonster.transform;
			toPos = EatingMonster.transform.position;
		} else {
			toPos = new Vector2 (to.position.x * 100f, to.position.y * 100f);

			Canvas c = GameObject.Find ("Canvas").GetComponent<Canvas> ();
			RectTransform CanvasRect = c.GetComponent<RectTransform> ();
			Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint(to.position));

			toPos = new Vector2 (
				((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
				((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
			);

		}
		return toPos;
	}


	// Use this for initialization
	void Start () {
		SetParticlesUnVisible ();
		SetVisible (false);

//		popinout = gameObject.AddComponent<UIPopInOut> ();
//		popinout.doActiveOnDone = false;

		State = LetterState.Inited;
		//		Timer.Instance.Create (new Timer.TimerCommand (Time.time, IdleShakeRate, Shake));

		text.color = FontColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontColorDefault;
		text.GetComponent<Outline>().effectColor = FontOutlineColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontOutlineColorDefault;





		if(ParticlesMergeAccept != null)  {
			ParticlesMergeAcceptScale = ParticlesMergeAccept.transform.localScale;
		}
		if (ParticlesMergeReject != null) {
			ParticlesMergeRejectScale  = ParticlesMergeReject.transform.localScale;
		}

		if(stone.spawnIds.Length > 1) { 

			if (stone.speed > 0) {
				mCurrentSpeed = stone.speed;
			} else {
				mCurrentSpeed = GameplaySettings.LetterMovementSpeed;
			}
		} else {
			mCurrentSpeed = GameplaySettings.LetterStationingSpeed;	
		}
	}

	// Update is called once per frame
	void Update () {

		if (GameplayController.Instance.IsPause || GameplayController.Instance.IsPausePopup ||( State == LetterState.Inited && MainImage.enabled == false)) {
			return;
		}

		updateParticlesIdle ();
		Vector2 toPos;
		switch (State) {
		case LetterState.Showup:
			MainImage.color = Color.Lerp( MainImage.color , GameplayController.Instance.CurrentLevel.StoneLetterMainColorDefault, Time.deltaTime*10);
			OutlineImage.color = Color.Lerp( OutlineImage.color , GameplayController.Instance.CurrentLevel.StoneLetterMainOutlineColorDefault, Time.deltaTime*10);
			text.color  = Color.Lerp( text.color , FontColorDefault/*GameplayController.Instance.CurrentLevel.StoneLetterFontColorDefault*/, Time.deltaTime*10);
			text.GetComponent<Outline>().effectColor = Color.Lerp( text.GetComponent<Outline>().effectColor , FontOutlineColorDefault/*GameplayController.Instance.CurrentLevel.StoneLetterFontOutlineColorDefault*/, Time.deltaTime*10);
			break;

		case LetterState.Disapear:
			//MainImage.color = Color.Lerp( MainImage.color , GameplayController.Instance.CurrentLevel.StoneLetterMainColorDefault * new Color (1, 1, 1, 0), Time.deltaTime*10 - .5f);
			//OutlineImage.color = Color.Lerp( OutlineImage.color , GameplayController.Instance.CurrentLevel.StoneLetterMainOutlineColorDefault* new Color (1, 1, 1, 0), Time.deltaTime*10 - .5f);
			//text.color  = Color.Lerp( text.color , GameplayController.Instance.CurrentLevel.StoneLetterFontColorDefault* new Color (1, 1, 1, 0), Time.deltaTime*10 - .1f);
			//text.GetComponent<Outline>().effectColor = Color.Lerp( text.GetComponent<Outline>().effectColor , GameplayController.Instance.CurrentLevel.StoneLetterFontOutlineColorDefault* new Color (1, 1, 1, 0), Time.deltaTime*10 - .1f);
			Debug.Log("Disapear");

			break;

		case LetterState.GoingToMonster:
			toPos = getMonsterMouth ();

			transform.position = Vector3.MoveTowards (transform.position, toPos,	Time.deltaTime * Speed * (Time.time - mTimeFromLaunch));
//			transform.localPosition =  Vector3.MoveTowards (transform.localPosition,	-Vector3.up * 300, 	Time.deltaTime  * Speed * 0.025f - (Time.time - mTimeFromLaunch));

			if (Vector3.Distance (transform.position, toPos) < 5f) {
				EatingMonster.Eat (this);
				State = LetterState.Eaten;
			}
			break;
		case LetterState.Idle:
			if (mMagnetLetter != null) {
				this.mTargetPosition = mMagnetLetter.transform.position;
				transform.position = Vector3.MoveTowards (transform.position, this.mTargetPosition, 2000 * Time.deltaTime);

				if (Vector2.Distance(transform.position, mTargetPosition) < 20f) {
					if (
						GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.Letter
						||
						GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.LetterName
						||
						GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.LetterInWord
						||
						GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.SoundLetter
						||
						GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.SoundLetterName
					) {
						GameplayController.Instance.margeLetters (this, mMagnetLetter);
						
					} else {
						mMagnetLetter = null;
						Select ();
						SetVisible(false);
					}
				}
			} else {
				if (isMovment) {
					transform.position = Vector3.MoveTowards (transform.position, this.mTargetPosition, GameplayController.Instance.calcSpeed (mCurrentSpeed * Time.deltaTime));
//					transform.localScale	= Vector3.MoveTowards (transform.localScale, this.mTargetScale, mCurrentSpeed * Time.deltaTime);

					if (!isActive && Vector2.Distance (transform.position, mTargetPosition) < 5f) { 
						isActive = true;
					} else if (stone.spawnIds.Length > 1 && Vector2.Distance (transform.position, mTargetPosition) < 5f) {
						mCurrentSpawnId++;
						if (mCurrentSpawnId > stone.spawnIds.Length - 1) {
							mCurrentSpawnId = 0;
							isMovment = false;
							if (stone.loop) {
								if (stone.delayRepet > 0) {
									Invoke ("onMovementPopOut", stone.delayRepet);
								} else {
									onMovementPopOut ();
								}
							}
						} else {
							GameObject location = GameplayController.Instance.getLocationBySpawnId (stone.spawnIds [mCurrentSpawnId]);
							mInitPosition = location.transform.position;
							mTargetPosition = location.transform.position;
						}
					}
				}
			}
			break;
		case LetterState.Tutorial:
			toPos = getMonsterMouth();

			transform.position = 	   Vector3.MoveTowards (transform.position,		 toPos,	Time.deltaTime  * Speed * 		   (Time.time - mTimeFromLaunch));
			transform.localPosition =  Vector3.MoveTowards (transform.localPosition,				-Vector3.up * 300, 	Time.deltaTime  * Speed * 0.025f - (Time.time - mTimeFromLaunch));
			break;
			/*case LetterState.Warning: //shaking
			if (!this.enabled) return;

			if (shaking || shake_frame != 0) {
			}
			transform.position = Vector3.Lerp (transform.position, mTargetPosition, IdleShakeSpeed * Time.deltaTime);
			break;*/
		}
		if ((State == LetterState.Warning || shakeFrame != 0)) {
			if (shakeFrame == 0) {
				shakeStart = transform.position;
				shakeDest = State == LetterState.Warning ? new Vector3 (shakeStart.x + (Random.value * 2 - 1) / 1, shakeStart.y + (Random.value * 2 - 1f) / 1, transform.position.z) : shakeStart;
			}
			shakeFrame++;
			float t = shakeFrame / 2;
			transform.position = Vector3.Lerp (shakeStart, shakeDest, t);
			//this.transform.Rotate(new Vector3(0, 0, shake_frame > 5 ? -1 : 1));
			if (shakeFrame == 2) {
				shakeFrame = 0;
			}
		}
		updateScale ();
	}



	void onMovementPopOut()
	{
		GameObject location = GameplayController.Instance.getLocationBySpawnId (stone.spawnIds[mCurrentSpawnId]);
		mInitPosition = location.transform.position;
		mTargetPosition = location.transform.position;
		transform.position = mTargetPosition;

		isMovment = true;
	}

	void startMovment()
	{
		isMovment = true;

		if (stone.hideAfter > 0f) {
			Invoke ("startBlink", stone.hideAfter);
		}
	}

	void updateParticlesIdle()
	{
		if (ParticlesIdle != null) {
			if (MainImage.enabled == true && State == LetterState.Idle && !GameplayController.Instance.IsPause &&  !GameplayController.Instance.IsPausePopup && !ParticlesIdle.isPlaying) {
				float rnd = Random.value * 1000;
				if (rnd < 1f) {
					ParticlesIdle.Emit (1);
				}
			} else {
//				ParticlesIdle.Stop ();
			}
		}
	}

	public void Select()
	{
		if ((State == LetterState.Idle || State == LetterState.Warning) && GameplayController.Instance.State == GameplayController.GameState.SegmentIdle) {

			State = LetterState.Selected;
//			GetComponent<Animation> ().Play ("LetterBeat");
			MainImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainColorSelected;
			OutlineImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainOutlineColorSelected;
			text.color = FontColorSelected;//GameplayController.Instance.CurrentLevel.StoneLetterFontColorSelected;
			text.GetComponent<Outline>().effectColor = FontOutlineColorSelected;//GameplayController.Instance.CurrentLevel.StoneLetterFontOutlineColorSelected;
			//AudioController.Instance.PlaySound (Resources.Load ("Sounds/PickupLetter") as AudioClip);
			TimeSelected = Time.time;
			//			Debug.Log ("Select " + stone.value);

			GameplayController.Instance.OnPlayerInteraction (this);

			AudioController.Instance.PlaySound ( SoundSelected, 1);
		}
	}

	public void UnSelect()
	{
		LetterState s = State;
		if (State == LetterState.Selected)
		{
			State = LetterState.Idle;
			GetComponent<Animation> ().Stop ();
			MainImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainColorDefault;
			OutlineImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainOutlineColorDefault;
			text.color = FontColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontColorDefault;
			text.GetComponent<Outline>().effectColor = FontOutlineColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontOutlineColorDefault;

			GameplayController.Instance.OnPlayerInteraction (this);

			AudioController.Instance.PlaySound ( SoundUnselected, .7f );

			//added by Tzahi
//			roolBackLetter ();
		}

		//added by Tzahi
		if (mShownup == true) {
			State = s;
			roolBackLetter ();
		}
		State = LetterState.Idle;
	}

	public void GoToMonster(MonsterCalloutController monster)
	{
		EatingMonster = monster;
		State = LetterState.GoingToMonster;
		isActive = false;
		
		mTimeFromLaunch = Time.time;
//		ParticlesTrail.Play ();
	}

	public virtual void Init(Stone stone, Vector3 position, int spawnId)
	{
		//		value = letter;
		this.stone = stone;

		this.spawnId = spawnId;

		//text.text = ArabicSupport.ArabicFixer.Fix(this.stone.value, true, true);
		//text.text = RTL.Fix(this.stone.value);
		text.text = this.stone.FixValue;

		MainImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainColorDefault;
		OutlineImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainOutlineColorDefault;

		MainImage.color *= new Color (1, 1, 1, 0);
		OutlineImage.color*= new Color (1, 1, 1, 0);

		text.color = FontColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontColorDefault;
		text.GetComponent<Outline>().effectColor = FontOutlineColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontOutlineColorDefault;

		mCurrentSpawnId = 0;
		mTargetScale = transform.localScale;
		mInitScale = transform.localScale;
		mTargetPosition = position;
		mInitPosition = position;

//		transform.position = position;
		if(stone.spawnIds.Length > 1) { 
			transform.position = position;
		} else {
			transform.position = GameplayController.Instance.LauncherPoint;
		}
	}

	public void Eaten()
	{
		State = LetterState.Eaten; // added by Tzahi
		RemoveTail ();
		//		Vector3 pos =  EatingMonster.transform.position;// way we need it????
		Destroy (gameObject);
	}

	void OnDestroy()
	{

	}

	public void Spilt()
	{
		RemoveTail ();
		Destroy (gameObject);
	}

	void RemoveTail()
	{
//		ParticlesTrail.transform.SetParent (transform.parent);
//		ParticlesTrail.loop = false;
//		ParticlesTrail.Stop ();
//		Destroy (ParticlesTrail.gameObject, 2);	
	}

	public void Showup()
	{
		isActive = false;

	if (stone.spawnIds.Length > 1) {
			transform.position = mTargetPosition;
		} else {
			transform.position = GameplayController.Instance.LauncherPoint;
		}

		transform.localScale = new Vector3(GameplaySettings.LetterLauncherPointStartScale, GameplaySettings.LetterLauncherPointStartScale, GameplaySettings.LetterLauncherPointStartScale);

		State = LetterState.Showup;
		ParticlesShowup.Play ();
		GetComponent<Animation> ().Play ("ShowupAnimation");
		Invoke ("ShowupInner", ParticlesShowup.main.duration * 0.5f);
		AudioController.Instance.PlaySound ( SoundAppear );
		mShownup = true;

		if (stone.delayIn > 0) {
			isMovment = false;
			Invoke("startMovment", stone.delayIn);
		} else {
			startMovment ();
		}
	}

	public bool IsShownup()
	{
		return mShownup;
	}

	void ShowupInner()
	{
		State = LetterState.Idle;
		MainImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainColorDefault ;
		OutlineImage.color = GameplayController.Instance.CurrentLevel.StoneLetterMainOutlineColorDefault;
		text.color = FontColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontColorDefault;
		text.GetComponent<Outline> ().effectColor = FontOutlineColorDefault;//GameplayController.Instance.CurrentLevel.StoneLetterFontOutlineColorDefault;

		SetVisible (true);
	}

	public void Disapear()
	{
		if (State == LetterState.Disapear) {
			return;
		}
		State = LetterState.Disapear;
		GetComponent<Animation> ().Play ("DisapearAnimation");
		mShownup = false;
	}


	public void DisapearWon(float delay){
		Invoke ("Disapear", delay);
	}

	public void DisapearLost(float delay = 0){
		if (Star != null) {
			Star.gameObject.SetActive (false);
		}
		if (delay == 0) {
			Disapear ();
		} else {
			Invoke ("Disapear", delay);
		}
	}

	void DisapearInner()
	{
		Destroy(gameObject);
	}

	public void SetVisible(bool enable)
	{
		text.enabled = enable;
		MainImage.enabled = enable;
		OutlineImage.enabled = enable;
	}

	void OnDisable()
	{
		CancelInvoke ();
	}

	public void StartIceEffect(){
		StartCoroutine (IceEffect ());
	}

	IEnumerator IceEffect(){
		yield return null;
		var renderer = GetComponentInChildren<Image> ();
		if (renderer != null) {
			StartCoroutine (GotoColor (renderer, new Color(.8f, .8f, 1f)));
			yield return new WaitForSeconds (4);
			StartCoroutine (GotoColor (renderer, Color.white));
		}
	}
	IEnumerator GotoColor(Image renderer, Color endColor){
		Color startColor = renderer.color;
		for (float t = 0; t <= 1; t += Time.deltaTime) {
			renderer.color = Color.Lerp (startColor, endColor, t);
			yield return null;
		}
	}

	public void SetState(LetterState state)
	{
		if (stone == null || (state == LetterState.Warning && stone.spawnIds.Length > 1)) {
			return;
		}
		State = state;
	}



	/*
* Tzahi - start
*/


	public virtual void OnPointerDown (PointerEventData eventData)
	{
		if (!GameplayController.Instance.IsInteractable || !isActive || GameplayController.Instance.State == GameplayController.GameState.CollectLetters) {
			return;
		}
//		Debug.Log ("OnPointerDown State:" + State.ToString());

		Select ();
		transform.parent.SetAsLastSibling ();
	}


	public virtual void OnPointerEnter (PointerEventData eventData)
	{
		if (!GameplayController.Instance.IsInteractable || !isActive) {
			return;
		}
	}


	public virtual void OnBeginDrag(PointerEventData eventData) 
	{
		if (!GameplayController.Instance.IsInteractable || !isActive || GameplayController.Instance.State == GameplayController.GameState.CollectLetters) {// && isTutorial == false)
			return;
		}
		mLastPosition = transform.position;

		isDragable = true;
		moveToMouse ();
		GameplayController.Instance.onBeginDragLetter (this);
//		Debug.Log ("OnBeginDrag State:" + State.ToString());
	}

	public virtual void OnDrag(PointerEventData eventData)
	{
		if (!isActive || GameplayController.Instance.State == GameplayController.GameState.CollectLetters) {
			return;
		}

		if (isDragable == true) {
			moveToMouse ();
			GameplayController.Instance.onDragLetter (this);
		}
//		Debug.Log ("OnDrag State:" + State.ToString());
	}

	public virtual void OnEndDrag(PointerEventData eventData)
	{
		if (!isActive) {
			return;
		}

		if (isDragable == true) {
			isDragable = false;
			GameplayController.Instance.onEndDragLetter (this);
		}

		if (isBlinking) {
			startBlink ();
		}
	}

	public void OnDrop(PointerEventData data)
	{

	}

	void moveToMouse()
	{
		Vector2 WorldObject_ScreenPosition;

		if (isTutorial) {
//			RectTransform rt = TutorialController.Instance.tutorialHandImage.GetComponent<RectTransform> ();

			WorldObject_ScreenPosition = new Vector2 (
				TutorialController.Instance.tutorialHandImage.transform.position.x//  + (rt.rect.width / 4)
				,
				TutorialController.Instance.tutorialHandImage.transform.position.y// - (rt.rect.height / 2)
			);
			WorldObject_ScreenPosition = new Vector2 (TutorialController.Instance.tutorialHandImage.transform.position.x, TutorialController.Instance.tutorialHandImage.transform.position.y);
		} else {
			Canvas c = GetComponentInParent<Canvas> ();
			RectTransform CanvasRect = c.GetComponent<RectTransform> ();
			RectTransformUtility.ScreenPointToLocalPointInRectangle(CanvasRect, Input.mousePosition, GameplayController.Instance.canvasCamera, out WorldObject_ScreenPosition);
		}
		transform.position = WorldObject_ScreenPosition;// + GameplaySettings.DragSpacious;
	}

	public void cancelDrag ()
	{
		isDragable = false;
		UnSelect ();
//		roolBackLetter ();
	}

	void roolBackLetter ()
	{
		collectLetters = null;
		if (this.stone != null) {
//			text.text = ArabicSupport.ArabicFixer.Fix (this.stone.value, true, true);
//			text.text = RTL.Fix (this.stone.value);
			text.text = this.stone.FixValue;
		}
		if (State != LetterState.Idle)
		{
			if (stone.spawnIds.Length > 1) {
				transform.position = mLastPosition;
			} else {
				transform.position = mTargetPosition = mInitPosition;
			}
		}

		isDragable = false;
		SetVisible(true);

		mMagnetLetter = null;

		if (GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.Word || GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.SoundWord) {
			numSubLetters = 0;
			//transform.localScale = mTargetScale = mInitScale;
			mTargetScale = mInitScale;
		}
	}

	public void addSubLetter()
	{
		numSubLetters++;
		Vector3 newScale = transform.localScale * GameplaySettings.LetterComboScale [numSubLetters - 1];
		if (newScale.x <= GameplaySettings.LetterComboMaxScale || newScale.y <= GameplaySettings.LetterComboMaxScale) {
			//transform.localScale = mTargetScale = newScale;
			mTargetScale = newScale;
		}
	}

	public void addCollectLetter(LetterController stone)
	{
		numSubLetters ++;

		Vector3 newScale = transform.localScale * GameplaySettings.LetterComboScale [numSubLetters - 1];
		if (newScale.x <= GameplaySettings.LetterComboMaxScale || newScale.y <= GameplaySettings.LetterComboMaxScale) {
			//transform.localScale = mTargetScale = newScale;
			mTargetScale = newScale;
		}
		collectLetters = stone;

//		text.text = ArabicSupport.ArabicFixer.Fix(collectLetters, true, true);
//		text.text = RTL.Fix(collectLetters);
		text.text = collectLetters.stone.FixValue;
	}

	public void	setNewPosition(Vector3 newPosition, int newSpawnId)
	{
		mTargetPosition = newPosition;
		mInitPosition = newPosition;

		this.spawnId = newSpawnId;
		//		transform.position = newPosition;
	}

	public void	magnetToLetter(LetterController magnetLetter)
	{
		mTargetPosition = magnetLetter.transform.position;
		mMagnetLetter = magnetLetter;	
	}

	public void addScorebubble (int score)
	{
		addScorebubble (transform, score);
	}


	GameObject GOScoreBubble; 

	public void addScorebubble (Transform parent, int score)
	{
		if (GOScoreBubble != null) {
			return;
		}

		GOScoreBubble = Instantiate(Resources.Load ("Gameplay/ScoreAnimation") as GameObject);
		GOScoreBubble.transform.SetParent (parent, false);
		if (transform != parent) {
			GOScoreBubble.transform.position += transform.position;
		}
		UIScoreAnimationController c = GOScoreBubble.GetComponent<UIScoreAnimationController>();
		c.gameObject.AddComponent<DestroyAfter> ().After = 1.4f;
		c.Play (score);

//		Debug.Log (new System.Exception ().StackTrace);
	}

	void SetParticlesUnVisible()
	{
		if (ParticlesMergeAccept != null) {
			ParticlesMergeAccept.SetActive (false);
		}
		if (ParticlesMergeReject != null) {
			ParticlesMergeReject.SetActive (false);
		}
	}

	public void addMergeParticlesAccept ()
	{
		SetParticlesUnVisible ();
		UpdateParticlesScale ();
		if (ParticlesMergeAccept != null) {
			ParticlesMergeAccept.SetActive (true);
		}
	}

	public void addMergeParticlesReject ()
	{
		SetParticlesUnVisible ();
		UpdateParticlesScale ();
		if (ParticlesMergeReject != null) {
			ParticlesMergeReject.SetActive (true);
		}
	}

	CanvasGroup getCanvasGroup
	{
		get
		{ 
			if (cg == null) {
				cg = gameObject.GetComponent<CanvasGroup> ();
			}
			return cg;
		}
	}

	void startBlink() {

		if (stone.hideAfterBlinks > 0) {
			isBlinking = true;

			StartCoroutine (Blink (stone.hideAfterBlinks));
		} else {
			getCanvasGroup.alpha = 0;
			gameObject.SetActive (false);
			getCanvasGroup.alpha = 1;
		}
	}

	IEnumerator Blink(int times)
	{
		int count = 0;

		float minAlpha = 0.2f;
		float i = 0.03f;

		if (isDragable) {
			yield break;
		}
		while(count < times) {
			count++;
			while (getCanvasGroup.alpha > minAlpha) {
				yield return new WaitForSeconds(0.01f);
				getCanvasGroup.alpha = getCanvasGroup.alpha - i;

				if (isDragable) {
					yield break;
				}
			}
			yield return new WaitForSeconds(UnityEngine.Random.Range(0f, 0.2f));
			while (getCanvasGroup.alpha < 1) {
				yield return new WaitForSeconds(0.01f);
				getCanvasGroup.alpha = getCanvasGroup.alpha + i;

				if (isDragable) {
					yield break;
				}
			}
			yield return new WaitForSeconds(UnityEngine.Random.Range(0f, 0.2f));
		}
		while (getCanvasGroup.alpha > 0) {
			yield return new WaitForSeconds(0.01f);
			getCanvasGroup.alpha = getCanvasGroup.alpha - i;

			if (isDragable) {
				yield break;
			}
		}

		if (isDragable) {
			yield break;
		}
		gameObject.SetActive (false);
		getCanvasGroup.alpha = 1;
	}

	void updateScale()
	{
		Vector3 newScale;
		newScale = mTargetScale;
		if (isDragable) {
			newScale *= 1.1f;
		}
		transform.localScale = Vector3.MoveTowards(transform.localScale, newScale, (mCurrentSpeed / 4 ) * Time.deltaTime);

		if (ParticlesMergeAccept != null && ParticlesMergeAccept.activeSelf && ParticlesMergeAccept.GetComponent<ParticleSystem>() != null) {
			ParticlesMergeAccept.transform.localScale = ParticlesMergeAcceptScale * newScale.x;
		}
		if (ParticlesMergeReject != null && ParticlesMergeReject.activeSelf && ParticlesMergeReject.GetComponent<ParticleSystem>() != null) {
			ParticlesMergeReject.transform.localScale = ParticlesMergeRejectScale * newScale.x;
		}
	}


	void UpdateParticlesScale()
	{
		updateScale ();

//		if (ParticlesMergeAccept != null) {
//			ParticlesMergeAccept.transform.localScale = ParticlesMergeAccept.transform.localScale * GameplaySettings.LetterComboScale [numSubLetters - 1];
//			ParticlesMergeAccept.transform.localScale = ParticlesMergeAcceptScale * transform.localScale.x;
//		}
//		if (ParticlesMergeReject != null) {
//			ParticlesMergeReject.transform.localScale = ParticlesMergeReject.transform.localScale * GameplaySettings.LetterComboScale [numSubLetters - 1];
//			ParticlesMergeReject.transform.localScale = ParticlesMergeRejectScale * transform.localScale.x;
//		}

	}

/*
* Tzahi - end
*/


}
