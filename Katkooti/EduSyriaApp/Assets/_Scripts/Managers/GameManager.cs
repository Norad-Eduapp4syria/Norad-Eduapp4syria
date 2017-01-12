using UnityEngine;
using System.Collections;
using System;

public class GameManager : Singleton<GameManager> {

    /*
     *                      Game Manager Class
     * Main Class of Game holds all setting , game state triggers 
     */

	public enum GameSate
	{
		INTRO,
		TUTORIAL,
		VINES_QUEST_UNLOCK,
		TIGER_CAVE,
		JUNGLE_COURT_UNLOCK,
		ELEPHANT_HUB,
		FINISH



	}

    #region Variables

    //****************************** Public Variables ***************************

    [Header("\t\t \tGame Settings")]
	public GameSettings gameSettings;
	public Quest CurrentQuest;
	public Databank databank;
   // public Habitat habitat;
	public TutorialController tutorialController{
		get {return _tutorialController;} 
	}
	public SwingingVinesController swingingVines{
		get {return _swingingVines;}
	}
	public TigerCaveController tigerCaveController{
		get {return _tigercaveController;}
	}

	public JungleCourtController jungleCourtController{
		get {return _jungleCourtController;}
	}

	public ElephantHubConroller elephantcontroller{
		get {return _elephantController;}
	}




    //***************************** Private Variables ***************************
	private TutorialController _tutorialController;
	private SwingingVinesController _swingingVines;
	private TigerCaveController _tigercaveController;
	private JungleCourtController _jungleCourtController;
	private ElephantHubConroller _elephantController;
	private GameSate currentGameState;

	private float ChickSongPower = 0;

	public bool QuestInitialized ;
	public float ChickSongPowerValue {
		get{ return ChickSongPower; }
		set{ChickSongPower = value; }

	}

    #endregion

    #region GameState Events Declaration
	public delegate void FileLoadedIntoPersistant(string data);
	public delegate void QuestEvents(Quest quest);
    public delegate void GameState();
	public static QuestEvents PopulateQuest;
    public static GameState GameInitialize,GameStart, GameOver, GamePause, GameResume, GameRevive;

    #endregion

    #region MonoFuctions Definition
    //========================== Mono Functions Defintions Start =========================================
	void OnEnable(){
		_tutorialController = new TutorialController ();
		_swingingVines = new SwingingVinesController ();
		_tigercaveController = new TigerCaveController ();
		_jungleCourtController = new JungleCourtController ();
		_elephantController = new ElephantHubConroller ();

	}
    void Start()
    {
		
		Application.targetFrameRate = gameSettings.TargerFPS;
		currentGameState = GameSate.INTRO;
		StartCoroutine (PlayState ("Intro"));
    }
    void Update()
    {
		//MessageBox.ShowLog ("Current State "+ tutorialController.getCurrentState());
    }

    // =========================== Mono Functions Definitions End ====================================
    #endregion

    #region GameState Events Definition
    //========================== GameState Event Funtion Definition Start =========================================

    public void ToggleGameInitialize()
    {
        if (GameInitialize!=null)
        {
            GameInitialize();
        }
    }
    public void ToggleGameStart()
    {
        if (GameStart != null)
        {
            GameStart();
        }
    }
    public void ToggleGamePause()
    {
        if (GamePause != null)
        {
            GamePause();
        }
    }
    public void ToggleGameResume()
    {
        if (GameResume != null)
        {
            GameResume();
        }
    }
    public void ToggleGameOver()
    {
        if (GameOver != null)
        {
            GameOver();
        }
    }
    public void ToggleGameRevive()
    {
        if (GameRevive != null)
        {
            GameRevive();
        }
    }
	public void TogglePopulateQuest(Quest quest){
		CurrentQuest = quest;
		QuestInitialized = true;
		if (PopulateQuest != null) {
			PopulateQuest (quest);
		}
	}


    //========================== GameState Event Funtion Definition End =========================================
    #endregion



	#region Custom Functions Definition
	//========================== Custom Funtions =========================================

	void GoToHabitant(string worldName){

	}
	void OpenWorld(string worldName){
		
	}

	public IEnumerator PlayState(string Value){
		AsyncOperation operation;

		if (Value == "Intro") {
			Value="MainScene";
		}
		MainUIManager.Instance.mapUIController.DeActivate();
		MainUIManager.Instance.loadingUiController.Activate ();
		operation = Application.LoadLevelAsync (Value);
		yield return new WaitUntil (()=>operation.isDone==true); 
		ToggleGameInitialize ();
		MainUIManager.Instance.loadingUiController.DeActivate ();
		//yield return new WaitForSeconds (2);

	}
	//========================== Custom Funtions =========================================
	#endregion


	#region GetterSetter
	public GameSate getCurrentGameState(){
		return currentGameState;
	}
	#endregion


	#region PublicFunctions
	public void ProceedGameState(){
		currentGameState++;
	}
	#endregion

	#region Utility Function
	public QuestItem getQuestItem(string name,int frequency){
		QuestItem item = new QuestItem ();
		item.Maxfrequency = frequency;
		item.counter = 0;
		item.questItem = Resources.Load ("QuestItems/" + name) as GameObject;
		return item;
	}

	public LearningItem getLearningItem(int frequency){
		LearningItem item = new LearningItem ();
		item.Maxfrequency = frequency;
		item.soundName = "Tay";
		item.letter = "f";
		item.counter = 0;
		return item;
	}

	public LearningItem[] getLearningItem(){
		return null;
	}

	public void EnableExterior(){
		Habitat temp = GameObject.FindObjectOfType<Habitat> ();
		temp.exterior.exteriorMain.SetActive (true);
		temp.interior.interiorMain.SetActive (false);
		temp.exterior.ActivateLevel ();
	}
	public void EnableInterior(){
		Habitat temp = GameObject.FindObjectOfType<Habitat> ();
		temp.interior.interiorMain.SetActive (true);
		temp.exterior.exteriorMain.SetActive (false);
	}
	public void EnableGlowMap(){
		Habitat temp = GameObject.FindObjectOfType<Habitat> ();
		temp.interior.glowNote.SetActive (true);
		temp.interior.glowNote.GetComponentInChildren<AnimateAlpha> ().StartAnimating();
}
	public void DisableGlowMap(){
		Habitat temp = GameObject.FindObjectOfType<Habitat> ();
		temp.interior.glowNote.SetActive (false);
//		temp.interior.glowNote.GetComponentInChildren<AnimateAlpha> ().StartAnimating();
	}
	public Habitat getHabitat(){
		return GameObject.FindObjectOfType<Habitat> ();
	}
	public MonkeyHubController getMonkeyHubController(){
		return GameObject.FindObjectOfType<MonkeyHubController> ();
	}
	public void DestroyAllControllers(){
		_tutorialController.Reset ();
		_swingingVines.Reset ();
		_tigercaveController.Reset ();
		_jungleCourtController.Reset();
		_elephantController.Reset ();

	}
	public void InstantiateObject(string path,Vector3 position){
		Instantiate (Resources.Load (path) as GameObject, position, Quaternion.identity);
	}
	#endregion


}
