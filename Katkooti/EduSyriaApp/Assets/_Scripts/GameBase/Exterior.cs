using UnityEngine;
using System.Collections;

[System.Serializable]
public class Exterior{


	public int Level;
	public GameObject exteriorMain;
	public GameObject Level0,Level1,Level2;

	public GameObject chickHome;
	public GameObject BuildchickHome;
	public void ActivateLevel0Glow(){
		Level0.GetComponentInChildren<AnimateAlpha> ().StartAnimating ();
	}

	public void ActivateLevel1Glow(){
		Level1.GetComponentInChildren<AnimateAlpha> ().StartAnimating ();
	}
	public void ActivateLevel()
	{
		if (Level == 1) {
			Level0.SetActive (false);
			Level1.SetActive (true);
			Level2.SetActive (false);
		} else if (Level == 2) {
			Level2.SetActive (true);
			Level1.SetActive (false);

		} else {
			Level1.SetActive (false);
			Level2.SetActive (false);
		}
	}

}
