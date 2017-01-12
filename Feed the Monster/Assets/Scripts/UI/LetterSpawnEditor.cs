using UnityEngine;
using UnityEngine.UI;
using System.Collections;

[ExecuteInEditMode]
public class LetterSpawnEditor : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		#if (UNITY_EDITOR)
		Text t = gameObject.GetComponentInChildren<Text>();
		LetterSpawn ls = gameObject.GetComponent<LetterSpawn> ();

		if(t != null && ls != null) {
			t.text = ls.id.ToString();
		}
		#endif
	}


}
