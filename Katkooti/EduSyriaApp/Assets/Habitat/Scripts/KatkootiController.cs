using UnityEngine;
using System.Collections;

public class KatkootiController : MonoBehaviour {
	[Range(0,5)]
	public float chickySpeed;
	public DialogController dialogController;


	public Transform chickSongEffectPosition;
	public Transform chickGlowEffectPosition;
	[SerializeField]
	private GameObject ChickSongEffect;
	public GameObject kkGlowEffect,kkGlowEffect2;


	private AnimationController _animationController;
	private Vector3 ChickyPostion;
	public AnimationController animationController{
		get{ return _animationController; }
	}
	void OnEnable(){
		GameManager.GameInitialize += OnGameInitialized;
	}

	void OnDisable(){
		GameManager.GameInitialize -= OnGameInitialized;
	}
	void Start () {
		_animationController = this.GetComponent<AnimationController> ();
	}

	void Update () {

	}

	void OnGameInitialized(){

	}


	public void MoveToPostion(Vector3 newPostion,bool moveToRight){
		if (moveToRight) {
			
		} else {
			
		}
	}
	public void MakeIdle(){
		_animationController.PlayAnimation("MakeIdle");
	}
	public void StartTalking(){
		_animationController.PlayAnimation("Talk");
	}
	public void StartTalking2(){
		_animationController.PlayAnimation("Talk2");
	}
	public void StartTalking3(){
		_animationController.PlayAnimation("Talk3");
	}
	public void WaveHand(){
		_animationController.PlayAnimation("Wave");
	}
	public void WalkWithTransform(){
		_animationController.PlayAnimation("WalkWithTransform");
	}

	public void WalkWithTransform2(){
		_animationController.PlayAnimation("WalkWithTransform2");
	}
	public void ChickSong(){
		_animationController.PlayAnimation("ChickSong");

	}

	public void Celebrations(){
		_animationController.PlayAnimation("Celebrations");

	}



	public void ChickSongMagickEffect()
	{
		Instantiate (ChickSongEffect, chickSongEffectPosition.position, Quaternion.identity);
	}

	public void KKGlowAnimation()
	{
		Instantiate (kkGlowEffect, chickGlowEffectPosition.position, Quaternion.identity);
	}

	public void KKGlowAnimationForMonkeyHub()
	{
		Instantiate (kkGlowEffect2, chickGlowEffectPosition.position, Quaternion.identity);
	}


}
