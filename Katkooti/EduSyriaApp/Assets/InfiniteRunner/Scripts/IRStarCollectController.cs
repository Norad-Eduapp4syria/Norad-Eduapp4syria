using UnityEngine;
using System.Collections;

public class IRStarCollectController : MonoBehaviour {

	// Use this for initialization
	public float life;
	public enum ScreenPoint
	{
		TopRight,
		TopLeft,
		BottomRight,
		BottomLeft
	}

	public ScreenPoint MoveToward;
	private Vector3 worldPostion;
	void Start () {
		switch (MoveToward) {
			case ScreenPoint.TopRight:
				worldPostion = new Vector3 (1, 0.95f, 0);
			break;
			case ScreenPoint.TopLeft:
				worldPostion = new Vector3 (0, 1, 0);
			break;
			case ScreenPoint.BottomLeft:
				worldPostion = new Vector3 (0, 0, 0);
			break;
			case ScreenPoint.BottomRight:
				worldPostion = new Vector3 (1, 0, 0);
			break;

		}

		Destroy (this.gameObject, life);
	}

	void Update () {

		this.transform.position = Vector3.Lerp (this.transform.position, Camera.main.ViewportToWorldPoint (worldPostion), 2 * Time.deltaTime);
	}
}
