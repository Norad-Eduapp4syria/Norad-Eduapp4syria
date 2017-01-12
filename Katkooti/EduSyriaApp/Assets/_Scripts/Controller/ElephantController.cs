using UnityEngine;
using System.Collections;

public class ElephantController : MonoBehaviour {


	public DialogController dialogController;
	private AnimationController _animationController;
//
//	public AnimationController animationController{
//		get{ return _animationController; }
//	}

	void OnEnable(){
		GameManager.GameInitialize += OnGameInitialized;
	}

	void OnDisable(){
		GameManager.GameInitialize -= OnGameInitialized;
	}
	void Start () {
		//_animationController = this.GetComponent<AnimationController> ();
	}

	public void Talk(){
		
	}
	public void Idle(){
	
	}

	void OnGameInitialized(){

	}
}
