using UnityEngine;
using System.Collections;

public class TigerController : MonoBehaviour {

	public DialogController dialogController;
	private AnimationController _animationController;

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

	void OnGameInitialized(){

	}

	public void MakeIdle(int number){
		if (number == 0) {
			_animationController.PlayAnimation ("MakeIdle");
		} else if (number == 2) {
			_animationController.PlayAnimation("HatIdle");
		}
		else if(number ==1)
		{
			_animationController.PlayAnimation("ShoeIdle");
		}
	}


	public void StartTalking(int number){

		if (number == 0) {
			_animationController.PlayAnimation("Talk");
		} else if (number == 2) {
			_animationController.PlayAnimation("HatTalk");
		}
		else if(number ==1)
		{
			_animationController.PlayAnimation("ShoeTalk");
		}



	}
	public void PlayTigerMe(int number){

		if (number == 0) {
			
			_animationController.PlayAnimation("MakeIdle");
			_animationController.PlayAnimation("TigerMe");
			_animationController.PlayAnimation("Talk");

		} else if (number == 2) {
			_animationController.PlayAnimation("HatIdle");
			_animationController.PlayAnimation("HatMe");
			_animationController.PlayAnimation("HatTalk");
		}
		else if(number == 1)
		{
			_animationController.PlayAnimation("ShoeIdle");
			_animationController.PlayAnimation("ShoeMe");
			_animationController.PlayAnimation("ShoeTalk");
		}



	}
	public void PlayTigerPointingUp(int number){

		if (number == 0) {

			_animationController.PlayAnimation("MakeIdle");
			_animationController.PlayAnimation("TigerPointingUP");
			_animationController.PlayAnimation("Talk");

		} else if (number == 2) {
			_animationController.PlayAnimation("HatIdle");
			_animationController.PlayAnimation("HatPointingUP");
			_animationController.PlayAnimation("HatTalk");
		}
		else if(number == 1)
		{
			_animationController.PlayAnimation("ShoeIdle");
			_animationController.PlayAnimation("ShoePointingUP");
			_animationController.PlayAnimation("ShoeTalk");
		}


	}
	public void PlayTigerPanic(int number){
		_animationController.PlayAnimation("MakeIdle");
		_animationController.PlayAnimation("TigerPanic");
		_animationController.PlayAnimation("Talk");
	}
	public void PlayThumbsUp(int number){
		_animationController.PlayAnimation("MakeIdle");
		_animationController.PlayAnimation("TigerThumbsUp");
		_animationController.PlayAnimation("Talk");
	}
	public void TigerSad(int number){
		_animationController.PlayAnimation("MakeIdleSad");
	}
	public void PlayAgree(int number){
		_animationController.PlayAnimation("MakeIdle");
		_animationController.PlayAnimation("Agree");
		_animationController.PlayAnimation("Talk");
	}




}
