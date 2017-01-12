using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class UIManager : MonoBehaviour {

	public Text TimeText,LivesText,WordText,MainWord,CurrentletterText,StartMessage;
	public Button Discard,Accept;
	public GameObject Succcess;
	public GameObject StartMessageObject;
	public GameObject Board,MonkeyHolder;

	private string mainword="";
	private WFManager WM;

	public string Word {
		get{
			return mainword;
		}
		set {
			mainword += value;
		}
	}

	void Start()
	{
		WM = GameObject.FindObjectOfType<WFManager> ().GetComponent<WFManager> ();
		PauseGame();
	}
	// Update is called once per frame
	void Update () {


		string temp = ArabicSupport.ArabicFixer.Fix (WM.Word.ToString (),true,true);
			if (temp != null) {
				WordText.text = temp;
				MainWord.text = ArabicSupport.ArabicFixer.Fix (mainword);
			}
			if (WM.CurrentWord [WM.counter] != null && WM.counter < WM.CurrentWord.Length)
				CurrentletterText.text = WM.CurrentWord [WM.counter].ToString ();
			if (StartMessageObject.activeInHierarchy) {
			
			StartMessage.text = ArabicSupport.ArabicFixer.Fix("قم بتكوين هذه الكلمات : " + WM.Word.ToString (),true,true);
			}


	}

	public void ClearMainWord()
	{
		mainword = "";
	}

	public void EnableControls()
	{
		Discard.interactable = true;
		Accept.interactable = true;
	}

	public void DisableControls()
	{
		Discard.interactable = false;
		Accept.interactable = false;
	}

	public void AcceptLetterButton()
	{
		Letter LetterClass = GameObject.FindGameObjectWithTag ("Letter").GetComponent<Letter>();
	//	LetterClass.AcceptLetter ();
	//	DisableControls ();
	}

	public void DiscardLetterButton()
	{
		Letter LetterClass = GameObject.FindGameObjectWithTag ("Letter").GetComponent<Letter>();
	//	LetterClass.DiscardLetter ();
		//DisableControls ();
	}

	public void ResetGame()
	{

		Time.timeScale = 1;
		WM.GameRestart ();
	}

	public void PauseGame()
	{
		
		StartCoroutine ("StartSound");
		StartMessageObject.SetActive (true);
		//Time.timeScale = 0;
	}

	IEnumerator StartSound()
	{
		SoundManager.Instance.PlaySoundOneShot ("AssembleWord");
		yield return new WaitForSeconds (SoundManager.Instance.getSoundLengthByName("AssembleWord"));
		SoundManager.Instance.PlaySoundOneShot (WM.Sound [WM.wordCompleted]);
		yield return new WaitForSeconds (SoundManager.Instance.getSoundLengthByName(WM.Sound [WM.wordCompleted]));


		MonkeyHolder.SetActive (true);

	}

	public void ShowSuccess(){
		Succcess.SetActive (true);
	}

	public void DisableStartMessagePanel()
	{
		StartMessageObject.SetActive (false);
	}

	public void EnableStartMessagePanel()
	{
		StartMessageObject.SetActive (true);
	}
	public void Resume()
	{
		WM.StartLetterSpawner ();
		Time.timeScale = 1;
		Board.SetActive(true);

	}

	public void RestartToMain()
	{
		//Gabject Temp = GameObject.FindObjectOfType<WFManager> ();
		//Destroy (WM.gameObject);
		//Destroy (UIManager.Instance.gameObject);
		Time.timeScale = 1;
		Application.LoadLevel (0);
	}


}
