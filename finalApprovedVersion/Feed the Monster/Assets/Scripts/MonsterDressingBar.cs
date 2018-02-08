using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterDressingBar : MonoBehaviour {

	public Transform monsterHolder;

	public GameObject[] Categories;

	public Dictionary<MonsterType, Vector3> monsterPos = new Dictionary<MonsterType, Vector3> ();


	public Dictionary<MonsterType, List<MonsterDressingItem>> monstersItems = new Dictionary<MonsterType, List<MonsterDressingItem>>();


	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
		transform.position = monsterHolder.position;
	}

	public void clean ()
	{
		monsterPos.Clear ();
		monstersItems.Clear ();

		foreach (GameObject cat in Categories) {
			foreach (Transform child in cat.transform) {
				Destroy (child.gameObject);
			}
		}
	}

	void addPos(MonsterType type, Vector3 pos) {
		if (monsterPos == null) {
			monsterPos = new Dictionary<MonsterType, Vector3> ();
		}
		if (monsterPos.ContainsKey (type)) {
			monsterPos [type] = pos;
		} else {
			monsterPos.Add(type, pos);
		}
	}

	public IEnumerator addMonster(Monster monster, Vector3 pos) {
//		bool isReady = (DressingController.Instance != null && DressingController.Instance.Dressing != null);

		addPos (monster.MonsterType, pos);

		yield return new WaitUntil(() => (DressingController.Instance != null && DressingController.Instance.Dressing != null) == true);

		add_Monster(monster);
	}

	void add_Monster(Monster monster) {
		if (monstersItems == null) {
			monstersItems = new Dictionary<MonsterType, List<MonsterDressingItem>> ();
		}
		if (!monstersItems.ContainsKey (monster.MonsterType)) {
			monstersItems.Add (monster.MonsterType, new List<MonsterDressingItem> ());
		}

		foreach (DressingCategoriesTO cat in DressingController.Instance.Dressing.Values ) {

			MonsterAccessoryTO monsterItem = UsersController.Instance.userData ().getMonsterAccessory (monster, cat.id);
			if (monsterItem != null) {

				Transform parent = Categories [cat.id - 1].transform;

				Vector3 v = parent.localPosition;
				v.z = cat.zOrder;
				parent.localPosition = v;

				addItem (parent, monster.MonsterType, monsterItem, cat);
			}
		}
	}

	public void updateMonsterItem (Monster monster) {

		MonsterDressingItem[] items = monstersItems [monster.MonsterType].ToArray();

		monstersItems [monster.MonsterType].Clear ();

		foreach (DressingCategoriesTO cat in DressingController.Instance.Dressing.Values) {
			bool isTreated = false;
			MonsterAccessoryTO monsterItem = UsersController.Instance.userData ().getMonsterAccessory (monster, cat.id);

			foreach (MonsterDressingItem item in items) {
				if (item.cat.id == cat.id) {
					isTreated = true;
					if (monsterItem == null) {
						item.gameObject.GetComponent<GOInOut> ().PopOut ();	
					} else if (monsterItem.id == item.item.id) {
						monstersItems [monster.MonsterType].Add (item);
					} else {
						item.gameObject.GetComponent<GOInOut> ().PopOut ();	

						Transform parent = Categories [cat.id - 1].transform;
						addItem (parent, monster.MonsterType, monsterItem, cat);
					}
				}
			}
			if (isTreated == false) {
				Transform parent = Categories [cat.id - 1].transform;
				addItem (parent, monster.MonsterType, monsterItem, cat);
			}

		}
/*
		return;

		foreach(MonsterDressingItem item in monstersItems [monster.MonsterType]) {
			item.gameObject.GetComponent<GOInOut> ().PopOut ();
		}
		monstersItems [monster.MonsterType].Clear();
		add_Monster(monster);
*/
	}

	void addItem (Transform parent, MonsterType monsterType, MonsterAccessoryTO monsterItem, DressingCategoriesTO cat) {
		var copy = Resources.Load<GameObject> ("Gameplay/Dressing/Items/" + monsterItem.id.ToString ());
		if (copy != null) {
			GameObject go = GameObject.Instantiate (copy);

			if (go != null) {
				go.transform.SetParent (parent, false);

				Vector3 v = go.transform.localPosition + monsterPos[monsterType];
				v.z = cat.zOrder;
				go.transform.localPosition = v;

				MonsterDressingItem mdi = go.AddComponent<MonsterDressingItem> ();
				mdi.item = monsterItem;
				mdi.cat = cat;

				monstersItems [monsterType].Add (mdi);
			}
		}
	}

	public void hideAllItems()
	{
		foreach (List<MonsterDressingItem> lgo in monstersItems.Values) {
			foreach (MonsterDressingItem go in lgo) {
				go.gameObject.SetActive (false);
			}
		}
	}

	public void showCurrentMonsterItems(MonsterType currentType)
	{
		foreach (MonsterType type in monstersItems.Keys) {
			bool isActive = type.Equals (currentType);
			foreach (MonsterDressingItem go in monstersItems[type]) {
				go.gameObject.SetActive (isActive);
			}
		}
	}


}
