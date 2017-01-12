using UnityEngine;
using System.Collections;

public class MonsterAnimation : MonoBehaviour {

	public void EndEat()
	{
		if (GameplayController.Instance != null) {
			GameplayController.Instance.OnEatAnimationEnd ();
		}
	}

	public void MealStart()
	{
		if (GameplayController.Instance != null) {
			GameplayController.Instance.OnMealStartAnimationEnd ();
		}
	}


	public void SpitsMeal()
	{
		if (GameplayController.Instance != null) {
			GameplayController.Instance.SpitsMeal();
		}
	}



}
