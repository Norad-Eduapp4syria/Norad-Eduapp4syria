using UnityEngine;
using System.Collections;

public class MouseFollower : MonoBehaviour {
	// Use this for initialization

	[Range(0.1f,5f)]
	public float HideAfter = 1f;

	float Counter;

	Vector3 LastPosition;

	void Start () {
		Counter = 0;
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 newPosition;

		Rect rect = GameObject.Find ("Canvas").GetComponent<RectTransform> ().rect;

		if (GameplayController.Instance && (GameplayController.Instance.IsPause || GameplayController.Instance.IsPausePopup)) {
			newPosition = transform.position;
			newPosition.z = -11;
		} else {
			var mousePosition = Input.mousePosition; 
			mousePosition = Camera.main.ScreenToViewportPoint (mousePosition);
			mousePosition.x = mousePosition.x * rect.width - rect.width / 2;
			mousePosition.y = mousePosition.y * rect.height - rect.height / 2;

			newPosition = new Vector3 (mousePosition.x, mousePosition.y, -9);

			if (!newPosition.Equals (LastPosition)) {
				LastPosition = newPosition;
				Counter = 0f;
			} else {
				Counter += Time.deltaTime;
			}

			if (Counter >= HideAfter) {
				newPosition.z = -11;
			}
		}
		transform.position = newPosition;
    }
}
