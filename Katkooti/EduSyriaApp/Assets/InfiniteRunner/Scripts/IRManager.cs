using UnityEngine;
using System.Collections;

public class IRManager : MonoBehaviour {

	public GameObject LocalUI;
	public GameObject startingRabit;
	public GameObject sleepingRabit;

	public Quest quest=null;
	public int totalLearningObjects;
	public LocalSoundHandler soundHandler;
	public IRPlayerController _player;

	public HurdleMainController _mainHurdleController;

	public IRTriggerSpawner triggerSpawner;
	public ObjectSpawner landSpawner_PowerUp;
	public ObjectSpawner[] WaterSpawners_PowerUp;
	public ObjectSpawner[] AirSpawners_PowerUp;



	private int QuestItemCollected=0; 




	private bool sleepingHareSpawned = false;

	private bool firstLetterCollected = false;
	private bool lastWoodCollected = false;
	private bool PlayEndingSequence = false;
	void OnEnable(){
		GameManager.PopulateQuest += PopulateQuest;
		_player.CollectQuestItem += OnPlayerCollectQuestItem;
		_player.PlayerHit += OnPlayerHit;
		_player.CollectPowerUp += OnCollectPowerUp;

	}
	void OnDisable(){
		GameManager.PopulateQuest -= PopulateQuest;
		_player.CollectQuestItem -= OnPlayerCollectQuestItem;
		_player.PlayerHit -= OnPlayerHit;
		_player.CollectPowerUp -= OnCollectPowerUp;
	}
	void PopulateQuest(Quest newQuest){
		quest = newQuest;
	}
	void Start(){


		if (GameManager.Instance.CurrentQuest.quest_location == Quest.QUEST_LOCATION.HARE_RACE) {
			Vector3 pos = new Vector3 (-0.5f, -3.56f, 0);
			Instantiate (startingRabit, pos, Quaternion.identity);
		} else {
			StartCoroutine (PlayTutorialSequence ());
		}


		InvokeRepeating ("QuestItemGenerator", 2, 4);
		if (GameManager.Instance.CurrentQuest.allowedPath_JungleRun == Quest.JUNGLE_RUN.LAND_AND_AIR) {
			triggerSpawner.triggerMin = 1;
			triggerSpawner.triggerMax = 2;
		}else if (GameManager.Instance.CurrentQuest.allowedPath_JungleRun == Quest.JUNGLE_RUN.LAND_WATER_AIR) {
			triggerSpawner.triggerMin = 1;
			triggerSpawner.triggerMax = 3;
		}
		else if (GameManager.Instance.CurrentQuest.allowedPath_JungleRun == Quest.JUNGLE_RUN.LAND_AND_WATER) {
			triggerSpawner.triggerMin = 2;
			triggerSpawner.triggerMax = 3;
		}
	}
	void OnPlayerHit(){
		
		if (!GameManager.Instance.CurrentQuest.isImune) {
			GameManager.Instance.CurrentQuest.PlayerHitHurrdle ();
			_player.totalCollectedLetters = Mathf.Clamp (_player.totalCollectedLetters-1,0,GameManager.Instance.CurrentQuest.getTotalLearningObjects ());
		}
		GameManager.Instance.ChickSongPowerValue =(float) _player.totalCollectedLetters / GameManager.Instance.CurrentQuest.getTotalLearningObjects (); 
	}
	void OnCollectPowerUp(){
		GameManager.Instance.CurrentQuest.PlayerCollectLetter ();
		if (!firstLetterCollected && _player.totalCollectedLetters == 1 && GameManager.Instance.CurrentQuest.quest_location != Quest.QUEST_LOCATION.HARE_RACE) {
			StartCoroutine (PlayStartSoundSequence ());
			firstLetterCollected = true;
		}
	
		_player.totalCollectedLetters = Mathf.Clamp (_player.totalCollectedLetters+1,0,GameManager.Instance.CurrentQuest.getTotalLearningObjects ());
		GameManager.Instance.ChickSongPowerValue = (float) _player.totalCollectedLetters / GameManager.Instance.CurrentQuest.getTotalLearningObjects (); 
		if (_player.totalCollectedLetters == GameManager.Instance.CurrentQuest.getTotalLearningObjects ()) {
			GameManager.Instance.CurrentQuest.isImune = true;
			GameManager.Instance.ChickSongPowerValue = 1;
			GameManager.Instance.CurrentQuest.LetterCollected = true;
		}
			
		PlayLastSequence ();

	}
	IEnumerator PlayStartSoundSequence(){
//		if (GameManager.Instance.CurrentQuest.quest_location != Quest.QUEST_LOCATION.HARE_RACE) {
//			SoundManager.Instance.PlaySoundOneShot ("FirstLetter");
//			yield return new WaitForSeconds (SoundManager.Instance.getSoundLengthByName ("FirstLetter"));
//			SoundManager.Instance.PlaySoundOneShot ("FirstLetter2");
//		} else {
//			SoundManager.Instance.PlaySoundOneShot ("FirstLetter");
//			yield return new WaitForSeconds (SoundManager.Instance.getSoundLengthByName ("FirstLetter"));
//			SoundManager.Instance.PlaySoundOneShot ("FirstLetter2");
//		}
		yield return new WaitForSeconds(0);
	}

	IEnumerator PlayTutorialSequence(){
		yield return new WaitForSeconds (1);
		//Instantiate (Resources.Load ("SwpieUp"), new Vector3(_player.transform.position.x+2,_player.transform.position.y,_player.transform.position.z), Quaternion.identity);
		yield return new WaitForSeconds (3);
	//	Instantiate (Resources.Load ("SwpieDown"), new Vector3(_player.transform.position.x+2,_player.transform.position.y,_player.transform.position.z), Quaternion.identity);
	}
	void OnPlayerCollectQuestItem(){
		QuestItemCollected++;
		GameManager.Instance.CurrentQuest.PlayerCollectQuestItem ();
		if (GameManager.Instance.CurrentQuest.QuestItemCollected) {
		//	SoundManager.Instance.PlaySoundOneShot ("WoodCollected");
		}
		PlayLastSequence ();
	}

	void PlayLastSequence(){
		

		if(GameManager.Instance.CurrentQuest.QuestItemCollected && GameManager.Instance.CurrentQuest.LetterCollected){
			
			if (GameManager.Instance.CurrentQuest.quest_location == Quest.QUEST_LOCATION.HARE_RACE && IRPlayerController.currentWorld==0 && _player.Isgrounded) {
				if (!sleepingHareSpawned) {
					_player.QuestCompleted = true;
					GameManager.Instance.ChickSongPowerValue = 1f;
					sleepingHareSpawned = true;
					Instantiate (sleepingRabit, landSpawner_PowerUp.transform.position, Quaternion.identity);
					_mainHurdleController.LockMainHurdleController ();
					StartCoroutine (TriggerQuestCompleted(3.5f));
				}
			}else if(GameManager.Instance.CurrentQuest.quest_location != Quest.QUEST_LOCATION.HARE_RACE){
				_player.QuestCompleted = true;
				GameManager.Instance.ChickSongPowerValue = 1f;
				_mainHurdleController.LockMainHurdleController ();
				StartCoroutine (TriggerQuestCompleted(1));
			}
		}
	}
	void Update(){
		if (PlayEndingSequence) {
			_player.transform.Translate (Vector3.right * 7f*Time.deltaTime);
		}
	}
	IEnumerator TriggerQuestCompleted(float startingWait){
		LocalUI.gameObject.SetActive (false);
		yield return new WaitForSeconds (startingWait);
		PlayEndingSequence = true;
		SoundManager.Instance.PlaySoundOneShot ("WinningSound");
		yield return new WaitForSeconds (1.3f);

		if (GameManager.Instance.CurrentQuest.quest_location == Quest.QUEST_LOCATION.HARE_RACE) {
			MainUIManager.Instance.decisionUiController.PopDicisionBox ("CompletionTrophy");
			yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
			MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		} else {
			MainUIManager.Instance.decisionUiController.PopDicisionBox ("CompletionWood");
			yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
			MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		}
		GameManager.Instance.ChickSongPowerValue = 1;

		GameManager.Instance.QuestInitialized = false;
	}

	void QuestItemGenerator(){

		switch(GameManager.Instance.CurrentQuest.getNextQuestItem ().canSpawnState){
		case  Quest.JUNGLE_RUN.LAND:
			if (_player.totalCollectedLetters > 0) {
				if ( (_player.totalCollectedLetters > (QuestItemCollected * GameManager.Instance.CurrentQuest.getTotalQuestObjects())) && !GameManager.Instance.CurrentQuest.QuestItemCollected) {
					Instantiate (GameManager.Instance.CurrentQuest.getNextQuestItem ().questItem, landSpawner_PowerUp.gameObject.transform.position, Quaternion.identity);
				}
			}
		break;
		case Quest.JUNGLE_RUN.LAND_AND_AIR:
			
		break;
		case Quest.JUNGLE_RUN.LAND_AND_WATER:
			
		break;
		case Quest.JUNGLE_RUN.LAND_WATER_AIR:
			
		break;
		}

	}
}
