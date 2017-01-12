using UnityEngine;
using System;
using System.Collections;

public class IRPlayerController : MonoBehaviour {
	#region Variables
	//Private Members
	Rigidbody2D _rigidbody;
	AnimationController _animController;
	int tap = 0;
	bool readyForDoubleTap = false;
	public bool isChangingWorld =false;
	private InputDirectionListener _directionListener;
	private bool disableJump = false;

	public GameObject middleCollider;

	#endregion

	public Parallax groundParallex;
	public Parallax foregroundParallex;

	public float jumpForce=10;
	public int totalCollectedLetters = 0;
	public static int currentWorld=0;
	public float camSpeed =0.8f;
	public float interval =0.1f;
	public float doubleJumpForce = 2f;
	public float laneChangeSpeed = 0.7f;
	Vector3 screenBounds;
	Vector3 screen;
	Vector3 playerScreenPos;
	
	private Action _moveAction;
	
	public Transform AirLane1;
	public Transform AirLane2;
	public Transform AirLane3;


	public Transform WaterLane1;
	public Transform WaterLane2;
	public Transform WaterLane3;
	public static string currentLane = "AirLane2";

	public delegate void PlayerEventsFloat (float a);
	public delegate void PlayerEvents ();
	public PlayerEvents PlayerHit,CollectPowerUp,PlayerLaneChange,CollectQuestItem;
	public PlayerEventsFloat CollectSceneTrigger;
	public bool Isgrounded;
	public LayerMask GroundLayer;

	public bool QuestCompleted=false;
	private int PlayerCollectetQuestItem=0;
	#region Monodevelop Functions
	public void Awake()
	{
		currentLane="AirLane2";
		currentWorld = 0;
		AssignDirectionListener();
	}
	
	
	void Start () {
		_rigidbody = this.GetComponent<Rigidbody2D> ();
		_animController = this.GetComponent<AnimationController> ();
		
		//		player = this.gameObject;
		screenBounds = new Vector3 (Screen.width, Screen.height,0 );
		screen.x = screenBounds.x;
		screen.y = screenBounds.y*0.15f;//4% of screenBounds.x
	}
	
	Vector3 newWorldPosition  = Vector3.zero;
	// Update is called once per frame

	public void WorldChanged(){
		isChangingWorld = false;
	}
	void EnableForJumping(){
		middleCollider.SetActive (true);
		//_animController.PlayAnimation("Swim2Run");
		isChangingWorld = false;
		_rigidbody.gravityScale = 1.8f;
	}
	void Update () {

		Isgrounded = Physics2D.IsTouchingLayers (this.GetComponent<BoxCollider2D> (), GroundLayer);
	
		if (isSlide) {
			this.GetComponent<PolygonCollider2D> ().enabled = false;
		}

		if (currentWorld == 0) {
			this.GetComponent<BoxCollider2D> ().enabled = true;
		}else if (currentWorld == 1) {
			this.GetComponent<BoxCollider2D> ().enabled = false;
		}if (currentWorld == -1) {
			this.GetComponent<BoxCollider2D> ().enabled = false;
		}


		if (isChangingWorld && !QuestCompleted) {
			if (currentWorld == 0) {
				_rigidbody.isKinematic = false;
				if (currentLane.Equals ("WaterLane1") || currentLane.Equals ("WaterLane2") || currentLane.Equals ("WaterLane3")) {
					newWorldPosition = new Vector3 (this.transform.position.x, -2f, this.transform.position.z);
					this.transform.position = Vector3.Lerp (this.transform.position, newWorldPosition, (camSpeed+1f) * Time.deltaTime);
					if (this.transform.position.y > -3f) {
						
					}
				} else {
					isChangingWorld = false;
					_rigidbody.gravityScale = 1.8f;
				}

			} else if (currentWorld == -1) {
				newWorldPosition = WaterLane2.position;
				currentLane="WaterLane2";
				this.transform.position = Vector3.Lerp (this.transform.position, newWorldPosition, camSpeed * Time.deltaTime);
			} else if (currentWorld == 1) {
				_rigidbody.gravityScale = 0;
				newWorldPosition = AirLane2.position;
				this.transform.position = Vector3.Lerp (this.transform.position, newWorldPosition, camSpeed * Time.deltaTime);
			}

			if (Vector3.Distance (this.transform.position, newWorldPosition) < 0.02f) {
				isChangingWorld = false;
			}		
		} else {
//			if(currentWorld==0)
//				this.transform.position = new Vector3 (-2.2f, this.transform.position.y, this.transform.position.z);
		}


//		if (Isgrounded && isChangingWorld) {
//			isChangingWorld = false;
//		}

		if(_moveAction != null && Time.timeScale==1 && !QuestCompleted){
			if (currentWorld == 1 || currentWorld==-1) {
				_moveAction ();
			}
		}
	}
	


	




	void OnTriggerEnter2D(Collider2D col){
		if (col.gameObject.CompareTag ("Hurdle")) {
			col.enabled=false;
			if (!QuestCompleted) {
				_animController.PlayAnimation ("Hurt");
				TogglePlayerHit ();
			}
			Handheld.Vibrate ();
		}
		if (col.gameObject.CompareTag ("PowerUp")) {
			if(ArabicSupport.ArabicFixer.Fix(GameManager.Instance.CurrentQuest.getNextLearningItem().letter,true,true).Equals(col.gameObject.GetComponent<PowerUp>().Text.text)){
				TogglePlayerCollectPowerUp ();
			}
			SoundManager.Instance.PlaySoundOneShot (col.gameObject.GetComponent<PowerUp>().SoundName);
			Destroy(col.gameObject);

		}
		if (col.gameObject.CompareTag ("QuestItem")) {
			PlayerCollectetQuestItem++;
			if (!GameManager.Instance.CurrentQuest.QuestItemCollected) {
				MainUIManager.Instance.inventoryController.Activate ();
				MainUIManager.Instance.inventoryController.Populate (col.gameObject.GetComponent<SpriteRenderer> ().sprite, PlayerCollectetQuestItem);
			}
			ToggleQuestItemCollect ();
			SoundManager.Instance.PlaySoundOneShot ("QuestItemCollect");
			Destroy(col.gameObject);
		}

		if (col.gameObject.CompareTag ("SceneTrigger")) {
			if (!QuestCompleted) {
				IRSceneShiftTrigger trigger = col.gameObject.GetComponent<IRSceneShiftTrigger> ();
				_rigidbody.isKinematic = true;
				_rigidbody.velocity = Vector2.zero;
				if (trigger.targetScene == IRSceneShiftTrigger.IRScene.SKY) {
					currentWorld = 1;
					isChangingWorld = true;
					RunToFly ();
					_rigidbody.velocity = Vector3.zero;
					currentLane = "AirLane2";
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, AirLane2.position, laneChangeSpeed * Time.deltaTime);
					Destroy (col.gameObject);

				} else if (trigger.targetScene == IRSceneShiftTrigger.IRScene.WATER) {
				
					_animController.CancelAnimationTrigger ("Swim2Run");

					currentWorld = -1;
					isChangingWorld = true;
					LandtoWater ();
					currentLane = "WaterLane2";
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, WaterLane2.position, laneChangeSpeed * Time.deltaTime);
					middleCollider.SetActive (false);
					_rigidbody.velocity = Vector3.zero;
					_rigidbody.gravityScale = 0;
					Destroy (col.gameObject, 2);

				}
				TogglePlayerCollectSceneTrigger (trigger.lifeSpan);
				SoundManager.Instance.PlaySoundOneShot ("TriggerCollect");
			} else {
				Destroy (col.gameObject);
			}

		}
		if (col.gameObject.CompareTag ("ShiftToLand")) {
			WaterToLand ();
			_animController.CancelAnimationTrigger ("RunToSwin");
		}
		if (col.gameObject.CompareTag ("DisableSpawner")) {
			
		}
		if (col.gameObject.CompareTag ("ApplyJumpForceTrigger")) {
			_animController.PlayAnimation ("RunToSwin");
		}
		if (col.gameObject.CompareTag ("ToLand")) {
			disableJump = false;
			groundParallex.ResetAllPosition ();
			Invoke ("EnableGroundParallex", 3f);
		}
		if (col.gameObject.CompareTag ("ToWater")) {

			GameObject.FindObjectOfType<IRTriggerSpawner>().DisbaleGroundParallex();
		}
	}

	public void EnableGroundParallex(){
	//	groundParallex.ResetAllPosition ();
		groundParallex.currentPatching = 0;
		groundParallex.temp = 0;

		groundParallex.gameObject.SetActive (true);
		groundParallex.EnableClone ();
	//	groundParallex.ResetAllPosition ();
	//	groundParallex.OnSetEnable ();

		foregroundParallex.gameObject.SetActive (true);
		foregroundParallex.EnableClone ();
	}
	#endregion

	
	void TogglePlayerCollectSceneTrigger (float time){
		if (CollectSceneTrigger != null) {
			CollectSceneTrigger (time);
		}
	}
	void ToggleQuestItemCollect(){
		if (CollectQuestItem != null) {
			CollectQuestItem ();
		}
	}
	public void AssignDirectionListener(){
		if(gameObject.GetComponent<InputDirectionListener>() == null)
			gameObject.AddComponent<InputDirectionListener>()._directionChangeListener = this.OnLaneChanged;
		else
			gameObject.GetComponent<InputDirectionListener>()._directionChangeListener = this.OnLaneChanged;
	}
	
	void OnLaneChanged(InputDirectionListener.Direction direction){
		
		
		switch(direction)
		{ 
		case InputDirectionListener.Direction.Right:
			//			FlyLaneSwitch ();
			break;
		case InputDirectionListener.Direction.Left:
			//			FlyLaneSwitch ();
			
			break;
		case InputDirectionListener.Direction.Down:
			if (currentWorld == 1) {
				FlyLaneSwitch ();
				TogglePlayerLaneChange ();
				if (currentLane.Equals ("AirLane3")) {
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, AirLane2.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "AirLane2";
				} else if (currentLane.Equals ("AirLane2")) {
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, AirLane1.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "AirLane1";
				}
			} else if (currentWorld == 0) {
				Slide ();
			} else if(currentWorld==-1){
				TogglePlayerLaneChange ();
				if (currentLane.Equals ("WaterLane2")) {
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, WaterLane3.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "WaterLane3";
				} else if (currentLane.Equals ("WaterLane1")) {
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, WaterLane2.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "WaterLane2";
				}
			}
			break;
		case InputDirectionListener.Direction.Up:
			if (currentWorld == 1) {
				FlyLaneSwitch ();
				TogglePlayerLaneChange ();
				if(currentLane.Equals("AirLane1")){
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, AirLane2.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "AirLane2";
				}
				else if(currentLane.Equals("AirLane2")){
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, AirLane3.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "AirLane3";
				}
			} 
			else if (currentWorld == 0) {
				if(!disableJump && !isSlide)
					Jump ();
			}
			else if (currentWorld == -1) {
				
				TogglePlayerLaneChange ();
				if(currentLane.Equals("WaterLane2")){
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, WaterLane1.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "WaterLane1";
				}
				else if(currentLane.Equals("WaterLane3")){
					_moveAction = () => transform.position = Vector3.MoveTowards (transform.position, WaterLane2.position, laneChangeSpeed * Time.deltaTime);
					currentLane = "WaterLane2";
				}
			}
			break;
		}
		
		
	}	
	#region Custom Function
	public void Jump(){
			
		tap ++;

		if (tap == 1 && Isgrounded) {

			_animController.PlayAnimation ("Jump");
			_rigidbody.AddForce (Vector3.up * jumpForce, ForceMode2D.Impulse);
			StartCoroutine (DoubleTapInterval ());
		} else if (tap > 1 && readyForDoubleTap) {
			DoubleJump ();
			tap = 0;
			readyForDoubleTap = false;
		} else {
			tap = 0;
		}
	}
	
	IEnumerator DoubleTapInterval()
	{  
		yield return new WaitForSeconds(interval);
		readyForDoubleTap = true;
		yield return new WaitForSeconds (1.4f);
		tap = 0;
	}
	
	
	
	
	public void DoubleJump(){
		_rigidbody.AddRelativeForce (Vector3.up *10,ForceMode2D.Impulse);
		_animController.PlayAnimation ("DoubleJump");

		//		_rigidbody.AddForce(Vector3.up * doubleJumpForce,ForceMode2D.Impulse);
	}
	private bool isSlide=false;
	public void Slide(){
		_animController.PlayAnimation ("Slide");
		isSlide = true;
		Invoke ("SlideOver", 1.5f);
	}

	void SlideOver(){
		isSlide = false;
	}
	
	public void WaterJump(){
		_animController.PlayAnimation ("SwimJump");
	}
	
	public void FlyLaneSwitch(){
		_animController.PlayAnimation ("FlyLaneChange");
	}
	
	
	// Temporary Functions
	public void RunToFly(){
		_animController.PlayAnimation ("RunToFly");
		currentWorld = 1;
		isChangingWorld = true;
	}
	public void FlyToLand(){
		StartCoroutine(_animController.PlayAnimationWithDelay ("Fly2Run",0.1f));
		currentWorld = 0;
		camSpeed = 0.8f;
		isChangingWorld = true;
	}
	public void LandtoWater(){
		
		currentWorld = -1;
		camSpeed = 0.8f;
		isChangingWorld = true;
	}
	public void WaterToLand(){
		_animController.PlayAnimation ("Swim2Run");
		currentWorld = 0;
		camSpeed = 1f;
		isChangingWorld = true;
		Invoke ("EnableForJumping", 3);
	}
	



	public void TogglePlayerHit(){
		if (PlayerHit != null) {
			PlayerHit ();
		}
	}
	public void TogglePlayerCollectPowerUp(){

		if (CollectPowerUp != null)
			CollectPowerUp ();	
	}
	public void TogglePlayerLaneChange(){
		if (PlayerLaneChange != null)
			PlayerLaneChange ();	
	}
	#endregion
	
	
	
	
}
