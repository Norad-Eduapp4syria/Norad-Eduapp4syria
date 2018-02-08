using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIPauseController : MonoBehaviour {
	public Image MusicButtonImage;
	public Color MusicOnColor;
	public Color MusicOffColor;

	public Image SoundButtonImage;
	public Color SoundOnColor;
	public Color SoundOffColor;


	public Transform popupsHolder;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown (KeyCode.Escape)) {
			UIController.Instance.ClosePopup (this.gameObject);
		}
	}

	void OnEnable()
	{
		transform.SetAsLastSibling ();

		ChangeMusicButtonColor ();
		ChangeSoundButtonColor ();
	}

	protected void ChangeMusicButtonColor()
	{
		MusicButtonImage.color = SaveStatConnector.Instance.MusicState ? MusicOnColor : MusicOffColor;
	}

	protected void ChangeSoundButtonColor()
	{
		SoundButtonImage.color = SaveStatConnector.Instance.SoundState ? SoundOnColor : SoundOffColor;
	}



	public void SoundButtonClick()
	{
		SaveStatConnector.Instance.SoundState = !SaveStatConnector.Instance.SoundState;
		AudioController.Instance.UpdateVolume ();

		ChangeSoundButtonColor ();
	}

	public void MusicButtonClick()
	{
		SaveStatConnector.Instance.MusicState = !SaveStatConnector.Instance.MusicState;
		AudioController.Instance.UpdateVolume ();

		ChangeMusicButtonColor ();
	}


	public void BackToMapClick() {
		GameObject popup = Instantiate(Resources.Load ("Gameplay/Popups/Popup Panel - Confirmation") as GameObject, popupsHolder);

		UIConfirmationPopup psc = popup.GetComponent<UIConfirmationPopup> ();
		psc.onConfirm = BackToMap;
	}

	public void TryAgainClick() {
		GameObject popup = Instantiate(Resources.Load ("Gameplay/Popups/Popup Panel - Confirmation") as GameObject, popupsHolder);

		UIConfirmationPopup psc = popup.GetComponent<UIConfirmationPopup> ();
		psc.onConfirm = TryAgain;
	}

	public void BackToMap() {
		if (GameplayController.Instance) {
			GameplayController.Instance.IsPause = true;
		}
		SceneController.Instance.LoadScene("MapScreen");
	}

	void TryAgain() {
		SceneController.Instance.LoadScene("GameScreen");
	}


}
