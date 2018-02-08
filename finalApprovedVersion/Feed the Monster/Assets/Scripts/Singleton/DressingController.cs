using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DressingController : MonoBehaviour {

	public static DressingController Instance = null;

	Dictionary<int, DressingCategoriesTO> _dressing = new Dictionary<int, DressingCategoriesTO>();
	Action _onInitCallBack;
	bool _isReady = false;

	public Dictionary<int, DressingCategoriesTO> Dressing
	{
		get { 
			return _dressing;
		}
		set { 
			_isReady = true;
			_dressing = value;
			if (_onInitCallBack != null) {
				_onInitCallBack();
			}
		}
	}



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

	public void init() {
		
	}

	public void onInit(Action callBack) {

		if (_isReady && callBack != null) {
			callBack ();
		} else {
			_onInitCallBack += callBack;
		}
	}


	public int isNewItemAvailable(int inLevelId)
	{
		foreach (DressingCategoriesTO cat in Dressing.Values) {
			foreach (DressingItemTO item in cat.items) {
				if (item.openInLevel.Equals (inLevelId)) {
					return item.id;
				}
			}
		}
		return -1;
	}



}
