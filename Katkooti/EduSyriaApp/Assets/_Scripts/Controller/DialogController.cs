using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using ArabicSupport;

public class DialogController : MonoBehaviour {



	public Text DialogueText;

	private string [] Dailogue;
	private float unitTime=0;
	private AnimationController _controller;
	public GameObject DialogueImage;


	void Start(){
		_controller = this.GetComponent<AnimationController> ();
	}
	public void PopDialogue(string dialogue){
		
	//	unitTime = 0;
		DialogueText.text = ArabicFixer.Fix(dialogue,true,true);
		_controller.PlayAnimation("PopDialogue");
	//Dailogue=dialogue.Split(' ');
	//	unitTime = ClipTime / Dailogue.Length;
	//	StartCoroutine (ShowDialogue ());
	}

	IEnumerator ShowDialogue()
	{
		for(int i=0;i<Dailogue.Length;i++)
		{
			DialogueText.text += " " +Dailogue [i].ToString();
			yield return new WaitForSeconds(unitTime);
		}
	}

	public void ChangeText(string dialogue){
		DialogueText.text = ArabicFixer.Fix(dialogue,true,true);
	}

	public void EnableTempDialogueImage()
	{
		DialogueImage.SetActive (true);
	}

	public void DisableTempDialogueImage()
	{
		DialogueImage.SetActive (false);
	}

	public void UnPopDialogue(){
//		DialogueText.text = "";
		_controller.PlayAnimation("UnPopDialogue");
	}
}
