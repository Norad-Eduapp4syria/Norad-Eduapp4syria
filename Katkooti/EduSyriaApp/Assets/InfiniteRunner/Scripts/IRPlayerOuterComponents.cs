using UnityEngine;
using System.Collections;

public class IRPlayerOuterComponents : MonoBehaviour {
	[Header("Reference of Main IR Player")]
	public IRPlayerController playerController;
	[Header("Player Outer Component Animations Triggers")]
	public string PlayerHitTrigger;
	public string PlayerJumpTrigger;
	public string PlayerDoubleJumpTrigger;
	public string PlayerLaneSwitchTrigger;
	public string PlayerCollectPowerUpTrigger;



	private AnimationController _controller;
	void Start () {
		
		_controller = this.GetComponent<AnimationController> ();

		if(!this.gameObject.name.Equals("StarOrHit"))
			playerController.CollectPowerUp += OnPlayerCollectPowerUp;

		playerController.PlayerHit += OnPlayerHit;
	}

	public void OnPlayerCollectPowerUp(){
		if (_controller != null) {
			_controller.PlayAnimation(PlayerCollectPowerUpTrigger);
		}
	}

	public void OnPlayerHit(){
		if (_controller != null) {
			_controller.PlayAnimation(PlayerHitTrigger);
		}
	}

	void Update(){
		
	}




}
