using UnityEngine;
using System.Collections;

public class MoveObjectAxis : MovingObject {

	public GameObject axis;
	public float maxX;
	public float minX;
	private float tempAxisX;
	void Start(){
		tempAxisX = axis.transform.position.x;
	}
	public override void Move ()
	{
		_movement = Direction * (Speed / 10) * Time.deltaTime;

		if (this.transform.localPosition.x < maxX && this.transform.localPosition.x > minX)
			transform.Translate(_movement);

	}
	public override void Update ()
	{
		if (tempAxisX < axis.transform.position.x) {
			Direction = Vector3.left;
		} else if (tempAxisX > axis.transform.position.x) {
			Direction = Vector3.right;
		} else {
			Direction = Vector3.zero;
		}
		tempAxisX = axis.transform.position.x;
		Move();


	}

}
