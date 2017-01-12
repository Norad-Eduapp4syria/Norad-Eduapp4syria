using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class BoosterController : LetterController {

	public static string letterName = "Booster";

	public Booster Model{ get; private set; }


	

	//public void Init(Booster model, Vector3 position)
	public void Init(Stone stone, Booster model, Vector3 position, int spawnId)
	{
		//base.Init (BoosterController.letterName, position);
		//base.Init (BoosterController.letterName, position, spawnId);
		base.Init (Stone.CreateBooster(stone), position, spawnId);


		Model = model;
		text.text = "";

		OutlineImage.sprite = Model.SelectedIcon;

		MainImage.sprite = Model.Icon;
	}

	/*
	override public void OnPointerDown (PointerEventData eventData) {
	}

	override public void OnPointerEnter (PointerEventData eventData) {
	}

	override public void OnBeginDrag(PointerEventData eventData) {
	}

	override public void OnDrag(PointerEventData eventData) {
	}

	override public void OnEndDrag(PointerEventData eventData) {
	}
*/


	public void PlaySound()
	{
		if (Model != null && Model.Sound != null) {
			AudioController.Instance.PlaySound (Model.Sound);
		}
	}

}
