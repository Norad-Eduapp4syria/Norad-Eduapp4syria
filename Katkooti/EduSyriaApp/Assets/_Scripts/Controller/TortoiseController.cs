using UnityEngine;
using System.Collections;

public class TortoiseController : MonoBehaviour {

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
		_animationController.PlayAnimation ("idle");
	}

	public void Talk()
	{
		_animationController.PlayAnimation ("talk");
	}
	public void WalkWithTransform()
	{
		_animationController.PlayAnimation ("walk");
	}
}
