using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class SwingingVinesController {

	private KatkootiController Player;

	public MonkeyController[] Monkeys;

	private CameraController cameraController;

	public enum SwingingVinesStates{
		NONE,
		KK_INTRO,
		MONKEYS_DIALOGUES,
		HELP_MONKEYS,
		SWINGING_VINES_MINIGAME,
		KK_DIALOGUES,
		//		USE_WORDSONG_POWER,  
		//		MONKEY_GLOW_INTERACTION_AND_REWARDS,
		//		MONKEY_DIALOGUES,
		//		RETURN_TO_HABITAT,
		FINISH
	}

	private SwingingVinesStates currentControllerState = SwingingVinesStates.NONE;


	void PopulateSwingingvinesQuest()
	{
		Quest quest= new Quest ();
		quest.LearningItemsInQuest = new LearningItem[3];
		quest.LearningItemsInQuest [0] = new LearningItem ();



						quest.LearningItemsInQuest [0].letter = "موز";
						quest.LearningItemsInQuest [0].Maxfrequency = 1;
						quest.LearningItemsInQuest [0].soundName = "Mooz";
				
						quest.LearningItemsInQuest [1] = new LearningItem ();
						quest.LearningItemsInQuest [1].letter = "بيت";
						quest.LearningItemsInQuest [1].Maxfrequency = 1;
						quest.LearningItemsInQuest [1].soundName = "Bat";
				
						quest.LearningItemsInQuest [2] = new LearningItem ();
						quest.LearningItemsInQuest [2].letter = "باب";
						quest.LearningItemsInQuest [2].Maxfrequency = 1;
						quest.LearningItemsInQuest [2].soundName = "Bab";
		


		GameManager.Instance.TogglePopulateQuest (quest);
	}

	public SwingingVinesController(){

		GameManager.GameInitialize += OnGameInitialized;

	}

	~SwingingVinesController(){
		GameManager.GameInitialize -= OnGameInitialized;
	}
	public void Reset(){
		currentControllerState = SwingingVinesStates.NONE;
		GameManager.Instance.StopAllCoroutines ();

		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		MainUIManager.Instance.decisionUiController.UnPopGenericTapIcon ();
		MainUIManager.Instance.decisionUiController.UnPopTap ();
	}
	void OnGameInitialized(){
		Debug.Log (GameManager.Instance.getCurrentGameState ());

		if (GameManager.Instance.getCurrentGameState () + 1 >= GameManager.GameSate.VINES_QUEST_UNLOCK && Application.loadedLevelName == "MonkeysHub") {
			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			Player = GameObject.FindObjectOfType<KatkootiController>() ;
			Monkeys = GameObject.FindObjectsOfType<MonkeyController> ();
			cameraController = Camera.main.gameObject.GetComponent<CameraController> ();
			PlayCurrentState ();
		}else if(Application.loadedLevelName == "MonkeysHub"){

			Player = GameObject.FindObjectOfType<KatkootiController>() ;
			Monkeys = GameObject.FindObjectsOfType<MonkeyController> ();
			// other sequence;
			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			Monkeys = GameObject.FindObjectsOfType<MonkeyController> ();
			GameManager.Instance.StartCoroutine(GameManager.Instance.swingingVines.NotAvailable());
		}


		if (GameManager.Instance.getCurrentGameState () + 1 != GameManager.GameSate.VINES_QUEST_UNLOCK && Application.loadedLevelName == "MonkeysHub") {

			MainUIManager.Instance.hudController.gameObject.SetActive (true);
			MainUIManager.Instance.hudController.EnableUIMapGlow ();
		} else {
			MainUIManager.Instance.hudController.DisableUIMapGlow ();
		}
	}
	IEnumerator NotAvailable(){
		Player.WalkWithTransform2 ();
		yield return new WaitForSeconds(Player.animationController.GetCurrentPlayingClipLength());
		yield return new WaitForSeconds (0.5f);

		Monkeys[0].MonkeyTalk ();
//		Monkeys[0].dialogController.PopDialogue("Hi, I don't feel like playing right now."); //63
		Monkeys[0].dialogController.PopDialogue("مرحبًا، \nلا أشعر بالرغبة في اللعب الآن");             
		yield return new WaitForSeconds (3f);
		//		Monkeys[0].dialogController.ChangeText ("Maybe next time");  //64
		Monkeys[0].dialogController.ChangeText ("ربما في المرة القادمة");   
		yield return new WaitForSeconds (1f);
		Monkeys[0].dialogController.UnPopDialogue ();
		Monkeys[0].MonkeyIdle ();

		yield return new WaitForSeconds(0.2f);
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		MainUIManager.Instance.hudController.EnableUIMapGlow ();

		//yield return new WaitForSeconds (1f);

	}
	void ProceedState(){
		currentControllerState++;
		if (currentControllerState == SwingingVinesStates.FINISH) {
			if (GameManager.Instance.getCurrentGameState () + 1 == GameManager.GameSate.VINES_QUEST_UNLOCK) {
				GameManager.Instance.ProceedGameState ();
			}

		}
	}


	void PlayCurrentState(){
		ProceedState ();
		switch (currentControllerState) {
		case SwingingVinesStates.KK_INTRO:
			GameManager.Instance.StartCoroutine(GameManager.Instance.swingingVines.KK_INTRO());
			break;
		case SwingingVinesStates.MONKEYS_DIALOGUES:
			GameManager.Instance.StartCoroutine(GameManager.Instance.swingingVines.MONKEYS_DIALOGUES());
			break;

		case SwingingVinesStates.HELP_MONKEYS:
			GameManager.Instance.StartCoroutine(GameManager.Instance.swingingVines.HELP_MONKEYS());
			break;
		case SwingingVinesStates.SWINGING_VINES_MINIGAME:
			GameManager.Instance.StartCoroutine(GameManager.Instance.swingingVines.SWINGING_VINES_MINIGAME());
			break;
		case SwingingVinesStates.KK_DIALOGUES:
			GameManager.Instance.StartCoroutine(GameManager.Instance.swingingVines.KK_DIALOGUES());
			break;
		default:
			break;
		}

	}


	IEnumerator KK_INTRO(){
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		Player.WalkWithTransform2 ();
		yield return new WaitForSeconds(Player.animationController.GetCurrentPlayingClipLength());


		yield return new WaitForSeconds (0.5f);

		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().Katkooti_postion);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		//		Player.dialogController.PopDialogue ("Hi Monkeys!");  //63
		Player.dialogController.PopDialogue ("مرحبًا أيتها القرود! ");
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");
		cameraController.ZoomIn ();

		Player.StartTalking2 ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		//		Player.dialogController.ChangeText ("I got your note");  //64
		Player.dialogController.ChangeText ("تسلمت ملاحظاتكم");
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");
		cameraController.Normal ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Player.dialogController.UnPopDialogue ();
		//		yield return new WaitForSeconds (2f);
		Player.MakeIdle ();
		PlayCurrentState ();
	}

	IEnumerator MONKEYS_DIALOGUES(){
		
		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_1_postion);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		cameraController.Normal ();
		//		Monkeys [0].dialogController.PopDialogue ("OO OO..");  //65
		//Monkeys [0].dialogController.PopDialogue ("أوه أوه...");
		SoundManager.Instance.InrementMonkeyHubSound();
		Monkeys [0].MonkeyTalk ();
		//yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		//		Monkeys [0].dialogController.ChangeText ("EE EE..");  //66
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");
		//Monkeys [0].dialogController.ChangeText ("إي إي..."); 
		//yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		SoundManager.Instance.InrementMonkeyHubSound();
		//		Monkeys [0].dialogController.ChangeText ("My monkeys are confused");   //67
		Monkeys [0].dialogController.PopDialogue ("القرود مرتبكة بعض \nالشيئ");
		cameraController.ZoomIn ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [0].dialogController.UnPopDialogue ();

		Monkeys [0].MonkeyIdle ();
		yield return new WaitForSeconds (2f);

//		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_2_postion);
//		yield return new WaitForSeconds (0.35f);
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
//		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
//		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		//		Monkeys [1].dialogController.PopDialogue ("bewildered");  //68
		Monkeys [1].dialogController.PopDialogue ("متحيرون");   

		Monkeys [1].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [1].dialogController.UnPopDialogue ();
		Monkeys [1].MonkeyIdle ();
		yield return new WaitForSeconds (1f);
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");

//		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_3_postion);
//		yield return new WaitForSeconds (0.35f);
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
//		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
//		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();


//		Monkeys [2].dialogController.PopDialogue ("flabergasted");     //69
		Monkeys [2].dialogController.PopDialogue ("مندهشون");

		Monkeys [2].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [2].dialogController.UnPopDialogue ();
		Monkeys [2].MonkeyIdle ();
		yield return new WaitForSeconds (1f);
		cameraController.Normal ();
//		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_4_postion);
//		yield return new WaitForSeconds (0.35f);
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
//		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
//		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

		//		Monkeys [3].dialogController.PopDialogue ("something…");     //70
		Monkeys [3].dialogController.PopDialogue ("شيء ما...");
		Monkeys [3].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [3].dialogController.UnPopDialogue ();
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");

		Monkeys [3].MonkeyIdle ();
		yield return new WaitForSeconds (1f);
		//		Monkeys [0].dialogController.PopDialogue ("My monkeys are feeling different after last night's magical storm");   //71
		Monkeys [0].dialogController.PopDialogue ("قرودي يشعرون بشيء \nغريب بعد العاصفة\n السحرية ليلة أمس");

		Monkeys [0].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [0].dialogController.UnPopDialogue ();
		Monkeys [0].MonkeyIdle ();

		//		Monkeys [1].dialogController.PopDialogue ("tempest");  //72
		Monkeys [1].dialogController.PopDialogue ("العاصفة");
		Monkeys [1].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [1].dialogController.UnPopDialogue ();
		Monkeys [1].MonkeyIdle ();
		yield return new WaitForSeconds (0.5f);
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");
		//		Monkeys [2].dialogController.PopDialogue ("gale"); //73
		Monkeys [2].dialogController.PopDialogue ("زوبعة");
		Monkeys [2].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [2].dialogController.UnPopDialogue ();
		Monkeys [2].MonkeyIdle ();
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");

		yield return new WaitForSeconds (0.5f);
		//		Monkeys [3].dialogController.PopDialogue ("something…");  //74
		Monkeys [3].dialogController.PopDialogue ("شيء ما");
		Monkeys [3].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [3].dialogController.UnPopDialogue ();
		Monkeys [3].MonkeyIdle ();
		//		Monkeys [0].dialogController.PopDialogue ("Where they once spoke in E E s and OO OOs, now they're obsessed with Synonyms!");     //75
		Monkeys [0].dialogController.PopDialogue ("كانوا يتحدثون قديمًا بكلمات \nإي إي، أوه أوه، والآن\n هم مولعون بالمترادفات!");
		Monkeys [0].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [0].dialogController.UnPopDialogue ();
		Monkeys [0].MonkeyIdle ();

		//		Monkeys [1].dialogController.PopDialogue ("tempest");     //76
		Monkeys [1].dialogController.PopDialogue ("المتشابهات");
		Monkeys [1].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [1].dialogController.UnPopDialogue ();
		Monkeys [1].MonkeyIdle ();
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");
		cameraController.ZoomIn ();
		yield return new WaitForSeconds (0.5f);
		//		Monkeys [2].dialogController.PopDialogue ("gale");  //77
		Monkeys [2].dialogController.PopDialogue ("الكنايات");
		Monkeys [2].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [2].dialogController.UnPopDialogue ();
		Monkeys [2].MonkeyIdle ();
		yield return new WaitForSeconds (0.5f);
		//		Monkeys [3].dialogController.PopDialogue ("something…");    //78
		Monkeys [3].dialogController.PopDialogue ("شيء ما");
		Monkeys [3].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [3].dialogController.UnPopDialogue ();

		yield return new WaitForSeconds (0.5f);
		//		Monkeys [0].dialogController.ChangeText ("Help us learn new words so my monkeys can speak better!");     ////79
		Monkeys [0].dialogController.PopDialogue ("ساعدنا على تعلم كلمات \n جديدة حتى تستطيع \n القردة التحدث بطريقة أفضل!");
		cameraController.Normal ();
		Monkeys [0].MonkeyTalk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Monkeys [0].dialogController.UnPopDialogue ();
		Monkeys [0].MonkeyIdle ();
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");

		yield return new WaitForSeconds (2f);
		PlayCurrentState ();
	}
	IEnumerator HELP_MONKEYS(){
		Player.StartTalking2 ();
		SoundManager.Instance.PlaySoundOneShot ("QuestSelection");
		//		Player.dialogController.PopDialogue ("Shall we help the monkeys?");   //80
		Player.dialogController.PopDialogue ("هلا ساعدنا القردة؟");
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		Player.MakeIdle ();
		Player.dialogController.UnPopDialogue ();
		yield return new WaitForSeconds (1.5f);
		MainUIManager.Instance.decisionUiController.PopDicisionBox ("YesNoSelection");

		yield return new WaitUntil (()=>(MainUIManager.Instance.decisionUiController.proceedStatus == true));

		MainUIManager.Instance.decisionUiController.UnPopDecisionBox();
		PlayCurrentState ();
	}

	IEnumerator SWINGING_VINES_MINIGAME(){
		PopulateSwingingvinesQuest ();


		MainUIManager.Instance.hudController.gameObject.SetActive (false);
		MainUIManager.Instance.loadingUiController.ActivateSwingingWineQuest ();
		AsyncOperation operation = Application.LoadLevelAsync ("WF2");
		yield return new WaitUntil (()=>(operation.isDone == true));
		MainUIManager.Instance.loadingUiController.DeActivate ();

		yield return new WaitUntil(()=>(GameManager.Instance.QuestInitialized == false));

		yield return new WaitForSeconds (1f);
		MainUIManager.Instance.loadingUiController.Activate ();
		operation = Application.LoadLevelAsync ("MonkeysHub");
		yield return new WaitUntil (()=>(operation.isDone == true));
		MainUIManager.Instance.loadingUiController.DeActivate ();

		//Application.LoadLevel ("MonkeysHub");
		//yield return new WaitForSeconds (2f);
		Player = GameObject.FindObjectOfType<KatkootiController>() ;
		Player.transform.position = GameObject.FindGameObjectWithTag ("SceneByDefaultPosition").transform.position;
		Monkeys = GameObject.FindObjectsOfType<MonkeyController> ();
		yield return new WaitForSeconds (2f);
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		PlayCurrentState ();

	}

	IEnumerator KK_DIALOGUES(){
		Player.MakeIdle ();
		yield return new WaitForSeconds (2f);
		Player.StartTalking ();
		Player.KKGlowAnimationForMonkeyHub ();
//		Player.dialogController.PopDialogue ("I am glowing again");  //84
//		Player.dialogController.PopDialogue ("إنني أتوهج من جديد");
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		SoundManager.Instance.InrementMonkeyHubSound();
		//		Player.dialogController.ChangeText ("Lets see if i can use my Wordsong power to help improve your speech");  //85
		Player.dialogController.PopDialogue ("لنرى إذا كنت \nأستطيع استخدام قوة ");
		float temptime = SoundManager.Instance.PlayMonkeysHubDialogue () / 2;
		yield return new WaitForSeconds (temptime);
		Player.dialogController.ChangeText ("لولو الروح لمساعدتك\n في تحسين كلامك ");
		yield return new WaitForSeconds (temptime);
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();
		yield return new WaitForSeconds (2f);

		GameObject GlowAnim = GameObject.FindObjectOfType<MonkeyHubController> ().gameObject;

//		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_1_postion);
//		yield return new WaitForSeconds (0.35f);
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());    //86
//		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
//		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
//
//
//		Monkeys [0].MonkeyTalk ();
//		//		Monkeys [0].dialogController.PopDialogue ("Thank you but i don't need it, try the other monkeys");  //87
//		Monkeys [0].dialogController.PopDialogue ("شكرًالك،لكنني لاأحتاج إليها\nحاول مع القرودالاخرى");
//
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
//
//		Monkeys [0].dialogController.UnPopDialogue ();
//		Monkeys [0].MonkeyIdle ();
		SoundManager.Instance.InrementMonkeyHubSound();

		yield return new WaitForSeconds (1f);

		GlowAnim.GetComponent<MonkeyHubController> ().GlowAnimation [0].SetActive (true);
		GlowAnim.GetComponent<MonkeyHubController> ().GlowAnimation [1].SetActive (true);
		GlowAnim.GetComponent<MonkeyHubController> ().GlowAnimation [2].SetActive (true);
		MainUIManager.Instance.decisionUiController.PopMonkeyButtonIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_2_postion);
		yield return new WaitForSeconds (0.35f);
		SoundManager.Instance.PlaySoundOneShot ("Monkeys");

		//GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		//GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
	
		MainUIManager.Instance.decisionUiController.UnPopMonkeyButtonIcon ();
		GameManager.Instance.InstantiateObject ("ConstructionParticles",GameObject.FindObjectOfType<MonkeyHubController>().SongPowerStarPosition.transform.position);
		SoundManager.Instance.PlaySoundOneShot ("SongBarPowerDown");
		GlowAnim.GetComponent<MonkeyHubController> ().GlowAnimation [2].SetActive (false);
		GlowAnim.GetComponent<MonkeyHubController> ().GlowAnimation [1].SetActive (false);
		GlowAnim.GetComponent<MonkeyHubController> ().GlowAnimation [0].SetActive (false);



		Player.animationController.PlayAnimation ("ChickSong");
		GameManager.Instance.ChickSongPowerValue = 0;
		SoundManager.Instance.PlaySoundOneShot ("KKSongPower");
		SoundManager.Instance.PlaySoundOneShot ("MonkeyMedal");


//		MainUIManager.Instance.StartCoroutine (MainUIManager.Instance.hudController.StarEffect ());
//		GameManager.Instance.ChickSongPowerValue = 0;
//		yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());
//
//		Monkeys [1].MonkeyTalk ();
//		//		Monkeys [1].dialogController.PopDialogue ("Wow i can speak OO OO EE EE AA AA");     //88
//		Monkeys [1].dialogController.PopDialogue ("رائع أستطيع التحدث \nأوه أوه إي إي آه آه");
//
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
//		Monkeys [1].dialogController.UnPopDialogue ();
//		Monkeys [1].MonkeyIdle ();
		SoundManager.Instance.InrementMonkeyHubSound();

		SoundManager.Instance.PlaySoundOneShot ("Monkeys");

		yield return new WaitForSeconds (0.25f);


//		MainUIManager.Instance.decisionUiController.PopMonkeyButtonIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_3_postion);
//		yield return new WaitForSeconds (0.35f);
//		//GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
//		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//		//GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
//		MainUIManager.Instance.decisionUiController.UnPopMonkeyButtonIcon ();


//		Player.animationController.PlayAnimation ("ChickSong");
//		MainUIManager.Instance.StartCoroutine (MainUIManager.Instance.hudController.StarEffect ());
//		GameManager.Instance.ChickSongPowerValue = 1f-0.66f;
//		yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());

//
//		Monkeys [2].MonkeyTalk ();
//		//		Monkeys [2].dialogController.PopDialogue ("OO EEE I was getting sick of just the synonyms");  //89
//		Monkeys [2].dialogController.PopDialogue ("وه أوه إي إي إي لقدكنت بدأت \nأشعربالممل من هذه المترادفات");
//
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
//		Monkeys [2].dialogController.UnPopDialogue ();
//		Monkeys [2].MonkeyIdle ();
		SoundManager.Instance.InrementMonkeyHubSound();
		yield return new WaitForSeconds (0.25f);


//		MainUIManager.Instance.decisionUiController.PopMonkeyButtonIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_4_postion);
//		yield return new WaitForSeconds (0.35f);
//		//GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
//		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//		//GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
//		MainUIManager.Instance.decisionUiController.UnPopMonkeyButtonIcon ();



//		Player.animationController.PlayAnimation ("ChickSong");
//		MainUIManager.Instance.StartCoroutine (MainUIManager.Instance.hudController.StarEffect ());
//		GameManager.Instance.ChickSongPowerValue = 0;
//		yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());


//		Monkeys [3].MonkeyTalk ();
//		//		Monkeys [3].dialogController.PopDialogue ("something…..else???");  //90
//		Monkeys [3].dialogController.PopDialogue ("هل من شيئا آخر؟؟؟");
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
//		Monkeys [3].dialogController.UnPopDialogue ();
//		Monkeys [3].MonkeyIdle ();
		SoundManager.Instance.InrementMonkeyHubSound();

		SoundManager.Instance.PlaySoundOneShot ("Monkeys");

		yield return new WaitForSeconds (0.25f);
//
//		Monkeys [0].MonkeyTalk ();
//		//		Monkeys [0].dialogController.PopDialogue ("Hahahaha");   //91
//		Monkeys [0].dialogController.PopDialogue ("هاهاها");
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
//	
//
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		SoundManager.Instance.InrementMonkeyHubSound();
		SoundManager.Instance.InrementMonkeyHubSound();
		SoundManager.Instance.InrementMonkeyHubSound();
		//		Monkeys [0].dialogController.ChangeText ("Thank You Katkooti!");   //92
		Monkeys [0].dialogController.PopDialogue ("شكرًا لك يا كتكوتي");    
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		//		Monkeys [0].dialogController.ChangeText ("You have done us a great favor.");  //93
		Monkeys [0].dialogController.ChangeText ("لقد أسديت لنا خدمة \nعظيمة"); 
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		//		Monkeys [0].dialogController.ChangeText ("Please take this as a reward");    //94
		Monkeys [0].dialogController.ChangeText ("فضلاً خذ هذا كمكافأة لك"); 
		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());

		GlowAnim.GetComponent<MonkeyHubController> ().MonkeyMedal.SetActive (true);
		SoundManager.Instance.PlaySoundOneShot ("MonkeyMedal");
		Monkeys [0].dialogController.UnPopDialogue ();
		Monkeys [0].MonkeyIdle ();
		yield return new WaitForSeconds (2f);

		GlowAnim.GetComponent<MonkeyHubController> ().MonkeyMedal.SetActive (false);

		MainUIManager.Instance.inventoryController.Activate ();
		yield return new WaitForSeconds (1f);
		MainUIManager.Instance.inventoryController.ResetInventory ();
		MainUIManager.Instance.inventoryController.PopulateAt (GameObject.FindObjectOfType<MonkeyHubController> ().MedalImage, 1);


		yield return new WaitForSeconds (3f);
		Monkeys [1].MonkeyTalk ();
		//		Monkeys [1].dialogController.PopDialogue ("Come back anytime and we can play and learn new words together");    //95
		Monkeys [1].dialogController.PopDialogue ("يمكنك العودة في أي وقت ويمكننا \n اللعب وتعلم كلمات جديدة سويًا");

		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());

		Monkeys [1].dialogController.UnPopDialogue ();
		Monkeys [1].MonkeyIdle ();
		yield return new WaitForSeconds (2f);

//		Monkeys [2].MonkeyTalk ();
//		//		Monkeys [2].dialogController.PopDialogue ("We can also help you find things other have lost high up in the trees");    //96
//		Monkeys [2].dialogController.PopDialogue ("كمايمكننامساعدتك لتجدالأشياءالتي \nأضاعهاالآخرون في أعالي الأشجار");
//	
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
		SoundManager.Instance.InrementMonkeyHubSound();

		Monkeys [2].dialogController.UnPopDialogue ();
		Monkeys [2].MonkeyIdle ();
	//	yield return new WaitForSeconds (2f);

//		Monkeys [3].MonkeyTalk ();
//		//		Monkeys [3].dialogController.PopDialogue ("and… something…else ");     //97
//		Monkeys [3].dialogController.PopDialogue ("و...شيء...آخر");
//		yield return new WaitForSeconds (SoundManager.Instance.PlayMonkeysHubDialogue());
//		Monkeys [3].dialogController.UnPopDialogue ();
//		Monkeys [3].MonkeyIdle ();
//		yield return new WaitForSeconds (1f);

		SoundManager.Instance.InrementMonkeyHubSound();


		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		MainUIManager.Instance.hudController.EnableUIMapGlow ();

		PlayCurrentState ();
	}

	IEnumerator FINISH(){
		yield return new WaitForSeconds (0.5f);
		PlayCurrentState ();
	}

}
