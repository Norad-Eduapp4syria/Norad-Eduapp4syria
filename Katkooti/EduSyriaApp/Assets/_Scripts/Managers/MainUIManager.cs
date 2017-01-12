using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class MainUIManager : Singleton<MainUIManager> {

	// Use this for initialization



	[Header("\t\tHud Controller")]
	public HudController hudController;
	[Header("\t\tDecision Controller")]
	public DecisionUIController decisionUiController;

	[Header("\t\tMap Controller")]
	public MapUIController mapUIController;

	[Header("\t\tDecision Controller")]
	public LoadingUIController loadingUiController;

	[Header("\t\tInventory Controller")]
	public InventoryUIController inventoryController;





}
