using UnityEngine;
using System.Collections;

public class IRSceneShiftTrigger : MonoBehaviour {
	public enum IRScene{
		SKY,
		WATER
	}
	public IRScene targetScene;
	public float lifeSpan;

}
