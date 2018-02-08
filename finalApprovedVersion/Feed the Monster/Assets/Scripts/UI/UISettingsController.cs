using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class UISettingsController : UIPauseController
{
	public Image ProfileIcon;
	[Header("Debug")] 
	public GameObject debugPanel;


	bool isRealoadMapNedded = false;

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

		UpdateDebugPanel ();

	}

	public void ShowParentReport()
	{
		SceneController.Instance.LoadScene("ParentScreen");
	}

	public void OpenProfileSelection()
	{
		GameObject popup = Instantiate(Resources.Load ("Gameplay/Popups/Popup Panel - Profile Selection") as GameObject, popupsHolder);


		UIProfileSelectionController psc = popup.GetComponent<UIProfileSelectionController> ();
		psc.NextScene = "MapScreen";
		psc.popupsHolder = popupsHolder;

		gameObject.SetActive (false);
	}


	public void Close()
	{
		if (isRealoadMapNedded) {
			BackToMap ();
		} else {
			UIPopupPanel pop = gameObject.GetComponent<UIPopupPanel> ();
			if (pop != null) {
				pop.PopOut ();
			} else {
				gameObject.SetActive (false);
			}
		}
	}


	void UpdateDebugPanel()
	{
		debugPanel.SetActive (GameAssets.Instance.DEBUG_ACTIVE);

		if (!GameAssets.Instance.DEBUG_ACTIVE) {
			return;
		}
	}

	public void OnDeleteUserData()
	{
		if (GameAssets.Instance.DEBUG_ACTIVE) {
			UsersController.Instance.clearUserData ();

			isRealoadMapNedded = true;
			Close ();
		}
	}

	public void OnDeleteAllUsersData()
	{
		if (GameAssets.Instance.DEBUG_ACTIVE) {
			UsersController.Instance.clearAllUsersData ();

			isRealoadMapNedded = true;
			Close ();
		}
	}

}
