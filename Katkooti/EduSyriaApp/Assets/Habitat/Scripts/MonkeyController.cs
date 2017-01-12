using UnityEngine;
using System.Collections;

public class MonkeyController : MonoBehaviour {
	
	//public Animator AnimationController;
	public DialogController dialogController;
	private AnimationController _animationController;

	public AnimationController animationController{
		get{ return _animationController; }
	}

	// Use this for initialization
	void Start () {
		_animationController = this.GetComponent<AnimationController> ();
	}
	


	public void MonkeyTalk()
	{
		_animationController.PlayAnimation ("talk");
	}

	public void MonkeyIdle()
	{
		_animationController.PlayAnimation ("mainidle");
	}

}
