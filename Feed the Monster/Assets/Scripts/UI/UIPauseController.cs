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

	public void ChangeMusicButtonColor()
	{
		MusicButtonImage.color = UserInfo.Instance.IsMusicEnable() ? MusicOnColor : MusicOffColor;
	}

	public void ChangeSoundButtonColor()
	{
		SoundButtonImage.color = UserInfo.Instance.IsSoundEnable() ? SoundOnColor : SoundOffColor;
	}
}
