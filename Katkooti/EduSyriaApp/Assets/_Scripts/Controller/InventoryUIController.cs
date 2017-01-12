using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class InventoryUIController : MonoBehaviour {

	public Sprite defaultSprite;
	public Image[] Images;
	public GameObject InventoryBackGround;
	public AnimationController controller;

	void Start(){
		
	}
	public void Activate(){
		controller.PlayAnimation ("InventoryIn");
		Invoke ("DeActivate", 2);
	}
	public void DeActivate(){
		controller.PlayAnimation ("InventoryOut");
	}

	public void Populate(Sprite sprite,int collected){
		for (int i = 0; i < collected; i++) {
			Images [i].sprite = sprite;
			if (i == collected - 1) {
				Images [i].gameObject.GetComponent<Animator> ().SetTrigger ("ScaleUp");
			}
		}
	}

	public void PopulateAt(Sprite sprite,int index){
		
		Images [index-1].sprite = sprite;
		Images [index-1].gameObject.GetComponent<Animator> ().SetTrigger ("ScaleUp");
			

	}
	public void ResetInventory(int start, int end){
		for (int i = start-1; i < end; i++) {
			Images [i].sprite = defaultSprite;
		}
	}

	public void ResetInventory(){
		for (int i = 0; i < 3; i++) {
			Images [i].sprite = defaultSprite;
		}
	}
}
