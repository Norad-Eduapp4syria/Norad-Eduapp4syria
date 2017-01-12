using UnityEngine;
using System.Collections;

public class MonsterSpritesController : MonoBehaviour {

	public Monster monster;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	void LateUpdate(){
/*
 * this used for the old monsters
		if (monster == null)
			return;
		var subSprites = Resources.LoadAll<Sprite> ("Gameplay/Monsters/Spritesheets/"+ monster.SpritesheetName);
		foreach (var renderer in GetComponentsInChildren<SpriteRenderer>()) {
			if (renderer.sprite == null) {
				continue;
			}
			string spriteName = renderer.sprite.name;
			if (spriteName == "Shadow" || spriteName == "crown_glow") {
				continue;
			}
			if (spriteName == "stick" || spriteName == "leaf") {
				renderer.enabled = monster.SpritesheetName == "Green";
				continue;
			}
			if (spriteName.Contains ("mouth")) {
				continue; //ignore the mouth
			}
			var newSprite = System.Array.Find (subSprites, item => item.name == spriteName);

			if (newSprite)
				renderer.sprite = newSprite;
		}
*/
	}
}
