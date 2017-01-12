
using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class birdController : MonoBehaviour {

	// Use this for initialization
	public GameObject jumpButton, slideButton;
	public Text JumpText,SlideText;
	private Animator _animator;
	public enum IRWorld{
		SKY,LAND,WATER
	}
	public InputDirectionListener inputController;
	public IRWorld currentWorld=IRWorld.WATER;
	public Text LaneNumber;
//	public Collider2D landCollider,WaterCollider;

	public float inputCoolDownTime;
	public bool IsDoingTransition=false;
	public float centerPoint=0;
	private Rigidbody2D rb;
	void Start () {
		_animator = this.GetComponent<Animator> ();
		rb = GetComponent<Rigidbody2D> ();
		ChangeTransition ();
	}
	private int skyLane=0;
	// Update is called once per frame
	public float lastTimeOfTouch;
	void Update () {
		ChangeTransition ();
		if (!IsDoingTransition) {
//			#if UNITY_EDITOR
//			if (Input.GetKeyDown (KeyCode.UpArrow)) {
//				Jump ();
//			}
//			if (Input.GetKeyDown (KeyCode.DownArrow)) {
//				Slide (true);
//			}
//			#endif
			#if UNITY_ANDROID || UNITY_EDITOR
			if(!buttonActive){
				if(inputController.direction==InputDirectionListener.Direction.Up && (Time.time-lastTimeOfTouch)>inputCoolDownTime){
					Jump ();
					inputController.setNone();
					lastTimeOfTouch=Time.time;
				}else if(inputController.direction==InputDirectionListener.Direction.Down && (Time.time-lastTimeOfTouch)>inputCoolDownTime){
					Slide(true);
					inputController.setNone();
					lastTimeOfTouch=Time.time;
				}
			}else{
				if(jumpClicked && (Time.time-lastTimeOfTouch)>inputCoolDownTime){
					jumpClicked=false;
					Jump();
					lastTimeOfTouch=Time.time;
				}else if(slideClicked && (Time.time-lastTimeOfTouch)>inputCoolDownTime){
					slideClicked=false;
					Slide(true);
					lastTimeOfTouch=Time.time;
				}
			}

			#endif
		}
		if (IsDoingTransition && (Mathf.Abs((Vector3.Distance(this.transform.position,new Vector3(this.transform.position.x,centerPoint,this.transform.position.z)))) > 0.2f)) {
			this.GetComponent<BoxCollider2D> ().enabled = false;
			IsDoingTransition = true;
			rb.gravityScale = 0;
			rb.isKinematic = true;
			if (this.currentWorld == IRWorld.LAND) {
				_animator.SetBool ("Run",true);
				_animator.SetBool ("Swim",false);
				_animator.SetBool ("Fly",false);
			} else if (this.currentWorld == IRWorld.SKY) {
				_animator.SetBool ("Run",false);
				_animator.SetBool ("Swim",false);
				_animator.SetBool ("Fly",true);
			} else {
				_animator.SetBool ("Run",false);
				_animator.SetBool ("Swim",true);
				_animator.SetBool ("Fly",false);
			}
			if(currentWorld!=IRWorld.SKY)
				this.transform.position = Vector3.MoveTowards (this.transform.position, new Vector3 (transform.position.x, centerPoint, transform.position.z), 1 * Time.deltaTime);
		} else {
			this.GetComponent<BoxCollider2D> ().enabled = true;

			IsDoingTransition = false;
			if (currentWorld != IRWorld.SKY) {
				rb.isKinematic = false;
				rb.gravityScale = 0.2f;
			}
		}

	
	


	}

	void LateUpdate(){
		if (buttonActive) {
			JumpText.text = "Up";
			SlideText.text="Down";
		} else {
			JumpText.text = "Jump";
			SlideText.text="Slide";
		}
		if (currentWorld == IRWorld.SKY) {
			LaneNumber.text = "Lane Number = " + (skyLane + 1).ToString ();

		} else if (currentWorld == IRWorld.WATER) {
			LaneNumber.text = "Swipe Up to Jump";
		}
		else if (currentWorld == IRWorld.LAND) {
			LaneNumber.text = "Swipe Up and Down to Jump and slide respectivily";
		}
			
		if(currentWorld==IRWorld.SKY)
			this.transform.position = Vector3.Lerp (this.transform.position,new Vector3( this.transform.position.x,centerPoint+(skyLane*0.5f),this.transform.position.z), 1f*Time.deltaTime);
	}
	public void OnTriggerEnter2D(Collider2D col){
		
		if (col.gameObject.CompareTag ("Hurdle")) {
			// Death Animation 
			
		} else if (col.gameObject.CompareTag ("SceneChangeTrigger")) {
			//Shifting From One Scene to Another
		}
	}

	 
	public void ChangeTransition(){

		if (currentWorld == IRWorld.WATER) {
			centerPoint= -0.33f;
		} else if (currentWorld == IRWorld.SKY) {
			centerPoint = 6.0f;
		} else {

			centerPoint = 2.55f;
		}
	}



	public void Jump(){
	// play jump animation and apply force on rigidbody
		if (currentWorld == IRWorld.LAND || currentWorld == IRWorld.WATER)
			rb.AddForce (Vector2.up * 80f);
		else {
			skyLane++;
			if (skyLane > 2) {
				skyLane = 2;
			}


		}

	}
	public void Slide(bool isSlide){
	// play slide animation
		if (currentWorld == IRWorld.LAND) {
//			if (isSlide)
//				this.transform.localScale = new Vector3 (this.transform.localScale.x, 0.2f, this.transform.localScale.z);
//			else
//				this.transform.localScale = new Vector3 (this.transform.localScale.x, 0.75f, this.transform.localScale.z);
		} else if (currentWorld == IRWorld.SKY) {
			skyLane--;
			if (skyLane < 0) {
				skyLane = 0;
			}
			//this.transform.position = new Vector3 (this.transform.position.x, centerPoint+(skyLane*0.5f), this.transform.position.z);
		}
	}
	bool jumpClicked,slideClicked;
	bool buttonActive=false;
	public void ChangeControl(){
		buttonActive = !buttonActive;

		jumpButton.SetActive (buttonActive);
		slideButton.SetActive (buttonActive);
	}

	public void JumpClicked(){
		jumpClicked = true;
	}
	public void SlideClicked(){
		slideClicked = true;
	}

}
