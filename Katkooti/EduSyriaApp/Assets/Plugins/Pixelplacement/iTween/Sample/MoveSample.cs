using UnityEngine;
using System.Collections;

public class MoveSample : MonoBehaviour
{	
	void Start(){
		iTween.MoveBy(gameObject, iTween.Hash("y", 0.5f, "easeType", "easeInOutExpo", "loopType", "pingPong", "delay", .1));
	}
}

