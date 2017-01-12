using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class IRUILetterBox : MonoBehaviour {

	public Text letter;


	public void Update(){
		letter.text = ArabicSupport.ArabicFixer.Fix (GameManager.Instance.CurrentQuest.getNextLearningItem ().letter,true,true);
	}
}
