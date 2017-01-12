using UnityEngine;
using System.Collections;
//using UnityEditor;
[System.Serializable]
public class Inventory  {

	public IItem []items;
	void Start(){
		

	}

	void OnGUI(){
		//string s = GUILayout.TextField ("Hamza");
		GUILayout.Button ("hamza");
	}
}
