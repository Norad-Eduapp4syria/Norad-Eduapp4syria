using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIDressingItem : MonoBehaviour {
	public Image _icon;
	public Image _outlineIcon;

	Action<DressingItemTO> _onClickCallback;

	DressingItemTO _item;
	string _defaultOutlineFile;

/*
	void Awake() { }
	void Start () { }
	void Update () { }
*/
	void clear() {
	
	}

	public void init(Action<DressingItemTO> onClickCallback, DressingItemTO item, MonsterAccessoryTO activeItem, string defaultOutlineFile) {

		_item = item;
		_onClickCallback = onClickCallback;
		_defaultOutlineFile = defaultOutlineFile;


		clear ();
		loadIcon (_icon, false);
		loadIcon (_outlineIcon, true);

		gameObject.SetActive (true);

		updateActiveIcon (activeItem);
		updateLock (); 
	}

	void loadIcon(Image img, bool isOutline) {
		if (img != null) {
			string url = "Gameplay/Dressing/Icons/";
			if (isOutline == true) {
				if (string.IsNullOrEmpty (_defaultOutlineFile)) {
					url += "Item_" + _item.id.ToString () + ((isOutline == true) ? "_outline" : "");
				} else {
					url += _defaultOutlineFile;
				}
			} else {
				url += "Item_" + _item.id.ToString ();
			}

//			string url = "Gameplay/Dressing/Icons/Item_" + _item.id.ToString () + ((isOutline == true) ? "_outline" : "");

			var src = Resources.Load<Sprite> (url);
			if (src != null) {
				Sprite sp = GameObject.Instantiate (src);
				if (sp != null) {
					img.sprite = sp;
				}
			}
			img.preserveAspect = true;
		}
	}

	public void updateActiveIcon (MonsterAccessoryTO activeItem) {
		if (_item == null) {
			return;
		}

		if (activeItem == null) {

			if (_outlineIcon != null) {
				_outlineIcon.enabled = false;
			}
		} else {
			if (_outlineIcon != null) {
				_outlineIcon.enabled = activeItem.id.Equals (_item.id);
			}
		}
	}




	public void onclick() {

		if (_onClickCallback != null) {
			_onClickCallback (_item);
		}
	}


	void updateLock() {
		if(_item == null) {
			return;
		}
		int highestLevel = UsersController.Instance.userData ().HighestOpenLevel;

		if (_item.openInLevel > 0 && highestLevel < _item.openInLevel) {
			gameObject.GetComponent<Button> ().interactable = false;

			_icon.material = UIDressing.Instance.GrayOutMaterial;
		} else {
			gameObject.GetComponent<Button> ().interactable = true;

			_icon.material = null;
		}
	}


}
	
