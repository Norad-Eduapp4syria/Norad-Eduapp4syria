using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

public class Timer : MonoBehaviour {
	public static Timer Instance;

	public class TimerCommand
	{
		public float LastTimeInterval;
		public float Interval;
		public Action action;
		public bool IsPause;
		public GameplayController.GameState MaskState;

		public TimerCommand(float lastTimeInterval, float interval, Action act)
		{
			LastTimeInterval = lastTimeInterval;
			Interval = interval;
			action = act;
			MaskState = GameplayController.GameState.None;
		}

		public TimerCommand(float lastTimeInterval, float interval, Action act, GameplayController.GameState maskState)
		{
			LastTimeInterval = lastTimeInterval;
			Interval = interval;
			action = act;
			MaskState = maskState;
		}
	}

	List<TimerCommand> mCommands = new List<TimerCommand>();
	float mLastTimeNotPaused;

	void Awake()
	{
		Instance = this;
	}

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		mLastTimeNotPaused += Time.deltaTime;

		if (GameplayController.Instance.IsPause || GameplayController.Instance.IsPausePopup)
			return;

		for (int i=0; i<mCommands.Count; i++) {
			if (!mCommands[i].IsPause && mLastTimeNotPaused - mCommands[i].LastTimeInterval >= mCommands[i].Interval && (mCommands[i].MaskState == GameplayController.Instance.State || mCommands[i].MaskState == GameplayController.GameState.None)) {
				mCommands[i].LastTimeInterval = mLastTimeNotPaused;
				mCommands[i].action.Invoke ();
			}
		}
	}

	public void Create(TimerCommand command)
	{
		mCommands.Add (command);
//		Debug.Log ("Create timer action: " + command.action.Method.Name);
	}

	public void Remove(Action action)
	{
		for (int i = 0; i < mCommands.Count; i++) {
			if (mCommands [i].action == action) {
				//Debug.Log ("Remove timer action: " + mCommands [i].action.Method.Name);
				mCommands.RemoveAt (i);
			}
		}
	}

	public void Pause(Action action)
	{
		for (int i = 0; i < mCommands.Count; i++) {
			if (mCommands [i].action == action) {
				mCommands [i].IsPause = true;
			}
		}
	}

	public void Resume(Action action)
	{
		for (int i = 0; i < mCommands.Count; i++) {
			if (mCommands [i].action == action) {
				mCommands [i].IsPause = false;
			}
		}
	}
}
