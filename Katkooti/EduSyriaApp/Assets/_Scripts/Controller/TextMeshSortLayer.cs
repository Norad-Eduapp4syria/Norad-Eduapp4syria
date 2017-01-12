using UnityEngine;
using System.Collections;

public class TextMeshSortLayer : MonoBehaviour {

	private MeshRenderer renderer;
	// Use this for initialization
	void Start () {

		renderer = this.GetComponent<MeshRenderer> ();

		renderer.sortingOrder = 16;
		 
	}

}
