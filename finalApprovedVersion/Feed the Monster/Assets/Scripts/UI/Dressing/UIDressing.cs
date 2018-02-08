using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIDressing : MonoBehaviour {

	public static UIDressing Instance;


	public UIDressingPopup[] popups;
	public Material GrayOutMaterial;

	Image mainImage;


	void Awake() {
		Instance = this;

	}

	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {

	}

	public void DressingPopupClick(int type)
	{
		if (popups != null) {
			foreach (UIDressingPopup popup in popups) {
				if (popup != null) {
					if (popup._categoryId.Equals (type)) {
						if (popup.isOpen) {
							popup.close ();
						} else {
							popup.open ();
						}
					} else {
						if (popup.isOpen) {
							popup.close ();
						} 
					}
				}
			}
		}
	}




	public void onMonsterChange()
	{
		if (popups != null) {
			foreach (UIDressingPopup popup in popups) {
				if(popup != null) {
					popup.onMonsterChange ();
				}
			}
		}
	}


}
