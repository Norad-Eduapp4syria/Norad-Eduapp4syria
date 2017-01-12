using UnityEngine;
using System.Collections;
using ArabicSupport;
using UnityEngine.UI;
public class test : MonoBehaviour {

	// Use this for initialization
	MeshRenderer renderer;
	void Start () {
		
		renderer = GetComponent<MeshRenderer> ();
		if (renderer != null) {
			renderer.sortingOrder = 14;
		}
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
