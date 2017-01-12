using UnityEngine;
using System.Collections;

public class GiraafeController : MonoBehaviour {

	public DialogController dialogController;
	private AnimationController _animationController;
	private Vector3 ChickyPostion;
	public AnimationController animationController{
		get{ return _animationController; }
	}

	// Use this for initialization
	void Start () {

		_animationController = this.GetComponent<AnimationController> ();
	}

	// Update is called once per frame
	void Update () {

	}



	public void MakeIdle()
	{
		_animationController.PlayAnimation ("Idle");
	}

	public void TalkLeft()
	{
		_animationController.PlayAnimation ("Left");
		_animationController.PlayAnimation ("Talk");
	}

	public void TalkRight()
	{
		_animationController.PlayAnimation ("Right");
		_animationController.PlayAnimation ("Talk");
	}

	public void MoveLeft(){
		_animationController.PlayAnimation ("Left");
	}
	public void MoveRight(){
		_animationController.PlayAnimation ("Right");
	}
	public void Talk()
	{
		_animationController.PlayAnimation ("Talk");
	}

	public void Order()
	{
		_animationController.PlayAnimation ("Order");
	}
}
