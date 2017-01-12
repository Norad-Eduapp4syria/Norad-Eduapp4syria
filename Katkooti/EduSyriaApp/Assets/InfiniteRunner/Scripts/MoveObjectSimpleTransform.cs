using UnityEngine;
using System.Collections;

public class MoveObjectSimpleTransform : MovingObject {


	public override void Move ()
	{
		_movement = Direction * (Speed / 10) * Time.deltaTime;
		transform.Translate(_movement);
		if (this.transform.position.x < HorizontalLimit && Direction.x < 0) {
			Destroy (this.gameObject);
		} else if (this.transform.position.x > HorizontalLimit && Direction.x > 0) {
			Destroy (this.gameObject);
		}
	}
	public override void Update ()
	{
		Move();

	}
}
