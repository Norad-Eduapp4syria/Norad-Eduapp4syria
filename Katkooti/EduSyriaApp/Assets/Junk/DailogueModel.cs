using UnityEngine;
using System.Collections;
using UnityEngine.UI;

[System.Serializable]
public class DailogueModel : MonoBehaviour {
	public string Sentence;
	private string [] Dailogue;



	public float ClipLegth;
	public Text DailogueText;


	void Start(){
		Dailogue=Sentence.Split (' ');



		StartCoroutine ("PlayDailogue");

	}

	public void ShowDialog(){
	
	}
	IEnumerator PlayDailogue()
	{

		for(int i=0;i<Dailogue.Length;i++)
		{
			DailogueText.text += " " +Dailogue [i].ToString();
			yield return new WaitForSeconds(ClipLegth);
		}
	}

}
