using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIDressingPopup : MonoBehaviour {

	public UIDressingItem[] items;

	public int _categoryId;

	public string defaultOutlineFile = string.Empty;



	[HideInInspector]
	public bool isOpen = false;

	Vector3 inPosition;
	Vector3 outPosition;

	Vector3 targetPosition;

	RectTransform rt;


	void Awake()
	{
		RectTransform rt = gameObject.GetComponent<RectTransform> ();

		inPosition = transform.localPosition;
		outPosition = targetPosition = inPosition + new Vector3 (rt.rect.width, 0f);
		transform.localPosition = outPosition;
	}

	void OnEnable()
	{
		transform.localPosition = outPosition;
	}

	void OnDisable()
	{
		transform.localPosition = outPosition;
	}

	// Use this for initialization
	void Start () {
		Invoke ("requestInit", 0.1f);

	}


	void requestInit() {
		DressingController.Instance.onInit (init);
	}


	// Update is called once per frame
	void Update () {
		transform.localPosition = Vector3.Lerp (transform.localPosition, targetPosition, Time.deltaTime * 10f);

		if (!isOpen && Vector3.Distance(transform.localPosition, outPosition) < 1f) {
			gameObject.SetActive (false);
		}
	}

	void init() {
		int itemId = 0;

		MonsterAccessoryTO activeItem = UsersController.Instance.userData ().getMonsterAccessory (UIMiniGame.Instance.CurrentMonster.MonsterType, _categoryId);

		if (DressingController.Instance != null && DressingController.Instance.Dressing.ContainsKey (_categoryId)) {
			foreach (DressingItemTO item in DressingController.Instance.Dressing[_categoryId].items) {
				if (items [itemId] != null) {
					items [itemId].init (onSelectItem, item, activeItem, defaultOutlineFile);
				}
				itemId++;
			}
		}

		while (items.Length > itemId && items [itemId] != null) {
			items [itemId].gameObject.SetActive (false);

			itemId++;
		}
//		if (targetPosition != inPosition) {
//			transform.localPosition = outPosition;
//			Invoke("open", 0.1f);
//		}
	}

	public void onSelectItem(DressingItemTO item)
	{
		MonsterAccessoryTO activeItem = null;
		MonsterAccessoryTO newActiveItem = null; 

		activeItem = UsersController.Instance.userData ().getMonsterAccessory (UIMiniGame.Instance.CurrentMonster.MonsterType, _categoryId);

		newActiveItem = (activeItem != null && activeItem.id.Equals (item.id)) ? null : MonsterAccessoryTO.create (item); 

		if (UIMiniGame.Instance.CurrentMonster != null) {
			UsersController.Instance.userData ().updateMonsterAccessory (
				UIMiniGame.Instance.CurrentMonster,
				_categoryId,
				newActiveItem
			);
		}
		MonsterBar.Instance.DressingBar.updateMonsterItem (UIMiniGame.Instance.CurrentMonster);
		updateActiveItem (newActiveItem); 
	}

	void updateActiveItem (MonsterAccessoryTO activeItem) {
		foreach (UIDressingItem item in items) {
			item.updateActiveIcon (activeItem);
		}
	}

	public void open() {
		isOpen = true;
		gameObject.SetActive (true);
		targetPosition = inPosition;
	}

	public void close() {
		isOpen = false;
		targetPosition = outPosition;



	}


	public void onMonsterChange(){
		MonsterAccessoryTO activeItem = UsersController.Instance.userData ().getMonsterAccessory (UIMiniGame.Instance.CurrentMonster.MonsterType, _categoryId);
		updateActiveItem (activeItem); 
	}
}
