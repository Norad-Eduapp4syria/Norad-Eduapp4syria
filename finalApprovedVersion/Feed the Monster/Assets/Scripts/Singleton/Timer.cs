using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

public class Timer : MonoBehaviour {
	public static Timer Instance = null;

	List<TimerCommand> mCommands = new List<TimerCommand>();

	void Awake()
	{
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (gameObject);
			SingletonLoader.CheckSingleton();
		} else if (Instance != this) {
			Destroy (gameObject);
		}
	}

	// Update is called once per frame
	void Update () {

		if (GameplayController.Instance == null || GameplayController.Instance.IsPause || GameplayController.Instance.IsPausePopup)
			return;

		for (int i = 0; i < mCommands.Count; i++) {
			TimerCommand cmd = mCommands [i];

			if (cmd.MaskState == GameplayController.Instance.State || cmd.MaskState == GameplayController.GameState.None) {
				cmd.passedTime += Time.deltaTime;
				if (cmd.passedTime >= cmd.Interval) {
					cmd.action.Invoke (cmd.passedTime);
					cmd.passedTime = 0f;
				}
			}
		}
	}

	public void init() {
	}

	public void Create(TimerCommand command)
	{
		mCommands.Add (command);
	}

	public void Remove(Action<float> action)
	{
		for (int i = 0; i < mCommands.Count; i++) {
			if (mCommands [i].action == action) {
				//Debug.Log ("Remove timer action: " + mCommands [i].action.Method.Name);
				mCommands.RemoveAt (i);
			}
		}
	}

	public void Pause(Action<float> action)
	{
		for (int i = 0; i < mCommands.Count; i++) {
			if (mCommands [i].action == action) {
				mCommands [i].IsPause = true;
			}
		}
	}

	public void Resume(Action<float> action)
	{
		for (int i = 0; i < mCommands.Count; i++) {
			if (mCommands [i].action == action) {
				mCommands [i].IsPause = false;
			}
		}
	}

	public class TimerCommand
	{
		public float Interval;
		public Action<float> action;
		public bool IsPause;
		public GameplayController.GameState MaskState;
		public float passedTime = 0;

		public TimerCommand(float interval, Action<float> act)
		{
			Interval = interval;
			action = act;
			MaskState = GameplayController.GameState.None;
		}

		public TimerCommand(float interval, Action<float> act, GameplayController.GameState maskState)
		{
			Interval = interval;
			action = act;
			MaskState = maskState;
		}
	}
}
