using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MapAvatarController : MonoBehaviour {

	[HideInInspector]
	public Vector2[] ColliderPoints;

	Image mProfileIcon;


	int mCurrentPointId = -1;
	int mNextPointId = -1;
	int mTargetPointId = -1;
	LevelButtonController mTargetLevelController = null;
	float mDelay = 0;


	void Awake () {
		mProfileIcon = GetComponent<Image> ();
	}

	// Use this for initialization
	void Start () {
		
	}

	void OnEnable() {

		if(mProfileIcon != null && UsersController.Instance != null) {
			Sprite sp = UsersController.Instance.CurrentProfileSprite;
			if (sp != null) {
				mProfileIcon.sprite = sp;
			}
		}
	}

	// Update is called once per frame
	void Update () {
		if (mTargetPointId != -1) {

			if (mDelay > 0f) {
				mDelay -= Time.deltaTime;
			} else { 
				Vector2 nextPoint = ColliderPoints[mNextPointId];
				if (Vector2.Distance (transform.localPosition, nextPoint) == 0f) {
					mNextPointId++;
					if (mNextPointId > mTargetPointId) {
						onDone ();
					} else {
						nextPoint = ColliderPoints [mNextPointId];
					}
				}
				transform.localPosition = Vector2.MoveTowards (transform.localPosition, nextPoint, Time.deltaTime * 50f);
			} 
		}
	}

	void onDone()
	{
		GameAssets.CurrentLevelIndex = mTargetLevelController.levelIndex;
		GoToGame ();

		mTargetLevelController = null;
		mTargetPointId = -1;
		mNextPointId = -1;

//		UIController.Instance.GoToLevel (mTargetLevel);
	}

	public void jumpToPointId(int PointId)
	{
		Vector2 v = ColliderPoints[PointId];
		transform.localPosition = v;
		mCurrentPointId = PointId;
	}

	public void goToPointId(int targetPointId, LevelButtonController targetLevelController, float delay = 0)
	{
		mTargetPointId = targetPointId;
		mTargetLevelController = targetLevelController;
		mNextPointId = mCurrentPointId + 1;
		mDelay = delay;
	}

	public void GoToGame() {
		mTargetLevelController.onClick ();
//		SceneController.Instance.LoadScene("GameScreen");
	}


}
