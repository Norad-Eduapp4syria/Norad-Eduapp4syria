using UnityEngine;
using System.Collections;

public class BaloonWoggle : MonoBehaviour {

	// Use this for initialization
	public float time;
	public float MaxYPos =	0;

	private bool MoveUp = true;


	private float tempTime=0;
	void Start () {
//		Hashtable ht = new Hashtable();
//		//ht.Add("x",YPos);
//		ht.Add("y",YPos);
//		ht.Add("time",time);
//		ht.Add("delay",0.1f);
//		ht.Add("looptype",iTween.LoopType.pingPong);
//		iTween.PunchPosition(gameObject,ht);
	}
	
	// Update is called once per frame
	void Update () {
		if(MoveUp)
			this.transform.localPosition = Vector3.Lerp (this.transform.localPosition, new Vector3(this.transform.localPosition.x,MaxYPos,this.transform.localPosition.z), 0.1f* Time.deltaTime);
		else
			this.transform.localPosition = Vector3.Lerp (this.transform.localPosition, new Vector3(this.transform.localPosition.x,MaxYPos*-1f,this.transform.localPosition.z),0.1f * Time.deltaTime);


		tempTime += Time.deltaTime;


		if (tempTime >= time) {
			tempTime = 0;
			MoveUp = !MoveUp;
		}
		
			
	
	}
}
