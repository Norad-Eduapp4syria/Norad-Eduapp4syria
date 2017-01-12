using UnityEngine;
using System.Collections;

public class MonsterCollectionController : MonoBehaviour {


	Animator animController;
	float idleStateTimer = 0;
	public Monster monster;


	// Use this for initialization
	void Start () {
		//animController = GameObject.Find ("monster").GetComponentInChildren<Animator> ();
		animController = gameObject.GetComponentInChildren<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
	
	}


	void FixedUpdate(){
		idleStateTimer += Time.deltaTime; // count back to idle mode

		if (idleStateTimer >= 1.0f && monster != null) {
			idleStateTimer = 0;

			animController.SetInteger ("EatState", 0);
			animController.SetInteger ("EmotionState", 0);

			if (UnityEngine.Random.value < 0.4f) {
				animController.SetInteger ("IdleState", monster.IdleStates[UnityEngine.Random.Range (0, monster.IdleStates.Count)]);
			} else {
				animController.SetInteger ("IdleState", 0);
			}
		}
	}



}
