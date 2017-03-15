using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class UISettingsController : UIPauseController
{
	public Image ProfileIcon;


	void OnEnable()
	{
		transform.SetAsLastSibling ();

		if(ProfileIcon != null) {
			Sprite sp = UsersController.Instance.CurrentProfileSprite;
			if (sp != null) {
				ProfileIcon.sprite = sp;
			}
		}

		ChangeMusicButtonColor ();
		ChangeSoundButtonColor ();
	}	





}
