using UnityEngine;
using System.Collections;

public class UIFlashAnimation : MonoBehaviour {
	public delegate void onDelegate();
	public onDelegate onEnd;
	public onDelegate onPeak;

	public AudioClip sndEvolv;


	// Use this for initialization
	void Start () {
		StartCoroutine (ChangeTimer());

		AudioController.Instance.PlaySound ( sndEvolv );

	}
	
	// Update is called once per frame
	void Update () {
	
	}



	IEnumerator ChangeTimer()
	{
		yield return new WaitForSeconds(0.1f);
		ChangeScreen ();

		yield return new WaitForSeconds(2.5f);
		End ();
	}


	public void ChangeScreen(){
		if(onPeak != null) {
			onPeak ();
		}

	}

	public void End(){
		if(onEnd != null) {
			onEnd ();
		}
	}

}
