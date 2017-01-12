using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.Text;

public class Common : MonoBehaviour {
	public static Common Instance;

	Queue<Action> mNonPauseActions;

	// Use this for initialization
	void Awake () {
		Instance = this;

		mNonPauseActions = new Queue<Action> ();
	}
	
	// Update is called once per frame
	void Update () {
		if (!GameplayController.Instance.IsPause && !GameplayController.Instance.IsPausePopup) {
			if (mNonPauseActions.Count > 0)
				mNonPauseActions.Dequeue ().Invoke ();
		}
	}

	public void AddNonPauseAction(Action action)
	{
		mNonPauseActions.Enqueue(action);
	}

	public Vector3 CanvasPositionToWorld(RectTransform canvas, Camera camera, Vector3 position) {
		position.x /= canvas.sizeDelta.x;
		position.y /= canvas.sizeDelta.y;

		position.x -= canvas.pivot.x;
//		position.y -= canvas.pivot.y;

		Vector3 temp = camera.ViewportToWorldPoint(position);

		return temp;
	}

	public string GetIsolatedForm(string letter)
	{
		for (int i=0; i<GameplayController.Instance.Recognitions.Length; i++) {

			Debug.Log (letter + " " + GameplayController.Instance.Recognitions[i].Letter);

			if (letter.Trim()== GameplayController.Instance.Recognitions[i].Letter.Trim()) {
				Debug.Log ("letter " + letter + " = recognition.Letter " + GameplayController.Instance.Recognitions[i].Letter);
				return GameplayController.Instance.Recognitions[i].Letter;
			}

			string[] variants = GameplayController.Instance.Recognitions[i].Variants.Split (",".ToCharArray ());
			foreach (string variant in variants) {
				Debug.Log (letter  + " " + variant);
				if (letter.Trim ().Equals(variant.Trim ())) {
					Debug.Log ("letter " + letter + " = recognition.Letter " + GameplayController.Instance.Recognitions[i].Letter);
					return GameplayController.Instance.Recognitions[i].Letter;
				}
			}
		}
		Debug.Log ("letter " + letter + " = null");
		return null;
	}
}
