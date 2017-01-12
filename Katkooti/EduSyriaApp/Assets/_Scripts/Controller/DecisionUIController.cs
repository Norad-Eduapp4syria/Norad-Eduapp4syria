using UnityEngine;
using System.Collections;

public class DecisionUIController : MonoBehaviour {
	[SerializeField]
	private DecisionUIObjects[] SelectionObjects;
	[SerializeField]
	private GameObject DecisionBox;

	[SerializeField]
	private GameObject DialoguePopIcon;

	[SerializeField]
	private GameObject GenericTapButton;

	[SerializeField]
	private GameObject MonkeyTapButton;


	public void Awake()
	{
		if(!PlayerPrefs.HasKey("ItemSelected"))
		{
			PlayerPrefs.SetInt ("ItemSelected",0);
			
		}
	
	}

	[SerializeField]
	private GameObject TapHandPointer;


	private bool proceed = false; 

	// Decision Box Blue Effects
	public GameObject leftBlue;
	public GameObject rightBlue;
	private int ItemSelected=0;

		public int SelectedItem
		{
			get{ return ItemSelected; }
	
		}




	public void LeftItemSelected()
	{
		ItemSelected = 1;
		PlayerPrefs.SetInt ("ItemSelected",ItemSelected);
	}


	public void RightItemSelected()
	{
		ItemSelected = 2;
		PlayerPrefs.SetInt ("ItemSelected",ItemSelected);
	}




	public bool proceedStatus{
		get {return proceed;}
	}


	public void LeftItemPressed()
	{
		LeftItemSelected ();
		proceed = true;
	}

	public void LeftItemReleased()
	{
		proceed = false;
	}

	public void RightItemPressed()
	{
		RightItemSelected ();
		proceed = true;
	}

	public void RightItemReleased()
	{
		proceed = false;
	}

	public void OnNoClicked()
	{
		MainUIManager.Instance.decisionUiController.DecisionBox.SetActive (false);
		Invoke ("ActiveDecisionBoxAfter", 2.5f);
	}
	void ActiveDecisionBoxAfter(){
		MainUIManager.Instance.decisionUiController.DecisionBox.SetActive (true);
	}
	public void MalePressed()
	{
		SoundManager.Instance.PlaySoundOneShot ("Habib");
		proceed = true;
	}

	public void MaleReleased()
	{
		proceed = false;
	}

	public void FemalePressed()
	{
		SoundManager.Instance.PlaySoundOneShot ("Habibi");
		proceed = true;
	}

	public void FemaleReleased()
	{
		proceed = false;
	}

	public void MonkeyButtonPressed()
	{
		proceed = true;
	}

	public void MonkeyButtonReleased()
	{
		proceed = false;
	}


	public void PopTap(GameObject target)
	{
		TapHandPointer.SetActive (true);
		TapHandPointer.GetComponent<MoveTapToTarget> ().target = target.transform;
	}

	public void UnPopTap()
	{
		proceed = false;
		TapHandPointer.SetActive (false);
	}


	public void GenericTapPressed()
	{
		proceed = true;
	}

	public void GenericTapReleased()
	{
		proceed = false;
	}

	public void TapPressed()
	{
		proceed = true;
	}

	public void TapReleased()
	{
		proceed = false;
	}


	public void PopMonkeyButtonIcon(GameObject target)
	{
		MonkeyTapButton.SetActive (true);
		MonkeyTapButton.GetComponent<MoveTapToTarget> ().target = target.transform;
	}

	public void UnPopMonkeyButtonIcon()
	{
		proceed = false;
		MonkeyTapButton.SetActive (false);
	}


	public void PopGenericTapIcon(GameObject target)
	{
		GenericTapButton.SetActive (true);
		GenericTapButton.GetComponent<MoveTapToTarget> ().target = target.transform;
	}

	public void UnPopGenericTapIcon()
	{
		proceed = false;
		GenericTapButton.SetActive (false);
	}


	public void PopDialogueIcon(GameObject target)
	{
		DialoguePopIcon.SetActive (true);
		DialoguePopIcon.GetComponent<MoveTapToTarget> ().target = target.transform;
	}

	public void UnPopDialogueIcon()
	{
		proceed = false;
		DialoguePopIcon.SetActive (false);
	}

	public void DialogPressed()
	{
		proceed = true;
	}

	public void DialogueReleased()
	{
		proceed = false;
	}

	public void YesPressed()
	{
		proceed = true;
	}

	public void YesReleased()
	{
		proceed = false;
	}

	public void PlayPressed(){
		proceed = true;
	}
	public void PlayReleased(){
		proceed = false;
	}
	public void PopDicisionBox(string selectionName){
		DecisionBox.SetActive (true);
		foreach (DecisionUIObjects o in SelectionObjects) {
			if (o.SelectionName.Equals (selectionName)) {
				o.SelectionObject.SetActive (true);
			}
		}
	}
	public void UnPopDecisionBox(){
		leftBlue.SetActive (false);
		rightBlue.SetActive (false);
		DisableAllSelection ();
		DecisionBox.SetActive (false);
		proceed = false;
	}

	void DisableAllSelection(){
		foreach (DecisionUIObjects o in SelectionObjects) {
			o.SelectionObject.SetActive (false);
		}
	}


}
