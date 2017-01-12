using UnityEngine;
using System.Collections;

public class RotateSample : MonoBehaviour
{	
	void Start(){
		iTween.ScaleBy(gameObject, iTween.Hash("x", .8f,"y",.8f,"speed",1.2f, "easeType", "easeInOutBack", "loopType", "pingPong", "delay", .2));
		iTween.MoveBy (gameObject, iTween.Hash ("y",1.5f,"easeType","linear","loopType","pingPong"));
	}
}

