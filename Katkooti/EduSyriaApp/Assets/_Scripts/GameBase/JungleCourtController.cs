using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class JungleCourtController : MonoBehaviour {

	private KatkootiController Player;

	private GiraafeController Giraafe;

	private HareController Hare;

	private TortoiseController Tortoise;

	private CameraController cameraController;

	public enum JungleCourtStates{
		NONE,
		INTRO,
		HAIR_TORTOISE_DIALOGUES,
		RUUNER_GAME_HAIR,
		ENDING_DIALOGUES,
		FINISH
	}

	private JungleCourtStates currentControllerState = JungleCourtStates.NONE;


	void PopulateJungleCourtQuest()
	{
		GameManager.Instance.CurrentQuest= new Quest ();
		GameManager.Instance.CurrentQuest.quest_location = Quest.QUEST_LOCATION.HARE_RACE;
		GameManager.Instance.CurrentQuest.allowedPath_JungleRun = Quest.JUNGLE_RUN.LAND_WATER_AIR; 
		GameManager.Instance.CurrentQuest.questItems=new QuestItem[1];
		GameManager.Instance.CurrentQuest.questItems[0]=GameManager.Instance.getQuestItem("Empty",1);
		GameManager.Instance.CurrentQuest.questItems [0].canSpawnState = Quest.JUNGLE_RUN.LAND_WATER_AIR;
		GameManager.Instance.CurrentQuest.QuestItemCollected = true;
		GameManager.Instance.CurrentQuest.isImune = false;

		int rand = Random.Range (0, 5);

		GameManager.Instance.CurrentQuest.LearningItemsInQuest = new LearningItem[4];
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [0] = new LearningItem ();
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [0].letter =DataLoader.readonlyLetters[rand];
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [0].Maxfrequency = 3;
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [0].soundName=DataLoader.readonlyLettersSound[rand];
		rand = Random.Range (0, 5);
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [1] = new LearningItem ();
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [1].letter = DataLoader.readonlyLetters[rand];
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [1].Maxfrequency = 3;
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [1].soundName=DataLoader.readonlyLettersSound[rand];
		rand = Random.Range (0, 5);
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [2] = new LearningItem ();
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [2].letter = DataLoader.readonlyLetters[rand];
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [2].Maxfrequency = 3;
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [2].soundName=DataLoader.readonlyLettersSound[rand];
		rand = Random.Range (0, 5);
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [3] = new LearningItem ();
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [3].letter = DataLoader.readonlyLetters[rand];
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [3].Maxfrequency = 3;
		GameManager.Instance.CurrentQuest.LearningItemsInQuest [3].soundName=DataLoader.readonlyLettersSound[rand];

		GameManager.Instance.TogglePopulateQuest (GameManager.Instance.CurrentQuest);
	}

	public JungleCourtController(){

		GameManager.GameInitialize += OnGameInitialized;

	}

	~JungleCourtController(){
		GameManager.GameInitialize -= OnGameInitialized;
	}
	public void Reset(){
		currentControllerState = JungleCourtStates.NONE;
		GameManager.Instance.StopAllCoroutines ();

		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		MainUIManager.Instance.decisionUiController.UnPopGenericTapIcon ();
		MainUIManager.Instance.decisionUiController.UnPopTap ();
	}
	void OnGameInitialized(){


		if (GameManager.Instance.getCurrentGameState () + 1 >= GameManager.GameSate.JUNGLE_COURT_UNLOCK && Application.loadedLevelName == "JungleCourt") {

			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			Player = GameObject.FindObjectOfType<KatkootiController> ();
			Tortoise = GameObject.FindObjectOfType<TortoiseController> ();
			Hare = GameObject.FindObjectOfType<HareController> ();
			Giraafe = GameObject.FindObjectOfType<GiraafeController> ();
			cameraController = Camera.main.gameObject.GetComponent<CameraController> ();
			PlayCurrentState ();
		} else if(Application.loadedLevelName == "JungleCourt") {
			
		
			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			Player = GameObject.FindObjectOfType<KatkootiController> ();
			Giraafe = GameObject.FindObjectOfType<GiraafeController> ();
			Tortoise = GameObject.FindObjectOfType<TortoiseController> ();
			Hare = GameObject.FindObjectOfType<HareController> ();
			cameraController = Camera.main.gameObject.GetComponent<CameraController> ();
			GameManager.Instance.StartCoroutine(GameManager.Instance.jungleCourtController.NotAvailable());
		}


		if (GameManager.Instance.getCurrentGameState () + 1 != GameManager.GameSate.JUNGLE_COURT_UNLOCK && Application.loadedLevelName == "JungleCourt") {
			MainUIManager.Instance.hudController.gameObject.SetActive (true);
			MainUIManager.Instance.hudController.EnableUIMapGlow ();
		} else {
			MainUIManager.Instance.hudController.DisableUIMapGlow ();
		}
	}
	IEnumerator NotAvailable(){
		Player.WalkWithTransform ();
		yield return new WaitForSeconds (2f);
		Giraafe.MakeIdle ();
		Giraafe.TalkRight ();
//		Giraafe.dialogController.PopDialogue("Hi, I don't feel like playing right now.");
		Giraafe.dialogController.PopDialogue("مرحبًا، لا أشعر\n بالرغبة في اللعب الآن");
		yield return new WaitForSeconds (3f);
//		Giraafe.dialogController.ChangeText ("Maybe next time");
		Giraafe.dialogController.ChangeText ("ربما في المرة القادمة");
		yield return new WaitForSeconds (1f);
		Giraafe.dialogController.UnPopDialogue ();
		Giraafe.MakeIdle ();

	

		yield return new WaitForSeconds (1f);
	}
	void ProceedState(){
		currentControllerState++;
		if (currentControllerState == JungleCourtStates.FINISH) {
			if (GameManager.Instance.getCurrentGameState () + 1 == GameManager.GameSate.JUNGLE_COURT_UNLOCK) {
				GameManager.Instance.ProceedGameState ();
			}
		
		}
	}



	void PlayCurrentState(){
		ProceedState ();
		switch (currentControllerState) {
		case JungleCourtStates.INTRO:
			GameManager.Instance.StartCoroutine(GameManager.Instance.jungleCourtController.INTRO());
			break;
		case JungleCourtStates.HAIR_TORTOISE_DIALOGUES:
			GameManager.Instance.StartCoroutine(GameManager.Instance.jungleCourtController.HAIR_TORTOISE_DIALOGUES());
			break;

		case JungleCourtStates.RUUNER_GAME_HAIR:
			GameManager.Instance.StartCoroutine(GameManager.Instance.jungleCourtController.RUUNER_GAME_HAIR());
			break;
		case JungleCourtStates.ENDING_DIALOGUES:
			GameManager.Instance.StartCoroutine(GameManager.Instance.jungleCourtController.ENDING_DIALOGUES());
			break;
		
		default:
			break;
		}

	}


	IEnumerator INTRO(){

		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		//Player.MakeIdle ();
		yield return new WaitForSeconds (0.5f);
		Player.WalkWithTransform ();


		//Player.MakeIdle ();
		//Tortoise.WalkWithTransform ();
		//Hare.WalkWithTransform ();
		yield return new WaitForSeconds(Player.animationController.GetCurrentPlayingClipLength());
	
		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<JungleHubController>().KKBuublePOsition);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();


//		Player.dialogController.PopDialogue ("Wow !");
		Player.dialogController.PopDialogue ("رائع");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//207
		Player.StartTalking2 ();
		yield return new WaitForSeconds (1f);
//		Player.dialogController.ChangeText ("What is this place?");

		Player.dialogController.ChangeText ("ما هذا المكان؟");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//198
		Player.dialogController.UnPopDialogue ();

		Player.MakeIdle ();

		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<JungleHubController>().GiraafePosition);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();


		Giraafe.Talk ();
		yield return new WaitForSeconds (1f);
//		Giraafe.dialogController.PopDialogue ("This is a court of law, young one.");
		Giraafe.dialogController.PopDialogue ("هذه قاعة محكمة صغيرة");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//199
		Giraafe.dialogController.UnPopDialogue ();
		Giraafe.MakeIdle ();

		yield return new WaitForSeconds (1f);
		cameraController.PanLeft (0.5f);
//		Player.dialogController.PopDialogue ("Pleased to meet you mam, I’m Katkooti.");
		Player.dialogController.PopDialogue ("أنا كتكوتي، سعدت \n بلقائك يا سيدتي");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//200
	
		Player.StartTalking ();
//		Player.dialogController.ChangeText ("What shall I call you?");
		Player.dialogController.ChangeText ("بم أناديك؟");

		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//201
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();


		yield return new WaitForSeconds (1f);
		cameraController.ZoomIn ();
//		Giraafe.dialogController.PopDialogue ("Well met Katkooti.");
		Giraafe.dialogController.PopDialogue ("أهلً بك يا كتكوتي");
		Giraafe.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//202
//		Giraafe.dialogController.ChangeText ("I’m Judge Hakeema");
		Giraafe.dialogController.ChangeText ("أنا القاضية حكيمة");

		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//203

		Giraafe.dialogController.UnPopDialogue ();
		Giraafe.MakeIdle ();

		cameraController.Normal();
		yield return new WaitForSeconds (1f);

//		Player.dialogController.PopDialogue ("Why does the jungle need a courthouse Judge Hakeema?");
		Player.dialogController.PopDialogue ("لماذا تحتاج الغابة \nإلى محكمة أيتها \nالقاضية حكيمة؟");

		Player.StartTalking ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//204
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();

		yield return new WaitForSeconds (1f);

//		Giraafe.dialogController.PopDialogue ("Well, that storm that hit last night was quite something wasn’t it?");
		Giraafe.dialogController.PopDialogue ("حسنًا، لقد كانت العاصفة \nالتي هبت ليلة أمس\n شيئًا خطيرًا، أليس كذلك؟");
		Giraafe.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//205


//	
		Giraafe.dialogController.ChangeText ("عندما استيقظت شعرت بشيء \nمختلف تمامًا. أدركت أنه بدون \nالقوانين، سنكون في غابة!");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//206
		Giraafe.dialogController.UnPopDialogue ();
		Giraafe.MakeIdle ();

		yield return new WaitForSeconds (1f);

//		Player.dialogController.PopDialogue ("Fascinating! ");
		Player.dialogController.PopDialogue ("رائع");

		Player.StartTalking ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//207

		Player.dialogController.UnPopDialogue ();


		Player.MakeIdle ();
		SoundManager.Instance.InrementJungleCourtSound ();
		SoundManager.Instance.InrementJungleCourtSound ();
		SoundManager.Instance.InrementJungleCourtSound ();

		yield return new WaitForSeconds (1f);





		PlayCurrentState ();
	}

	IEnumerator HAIR_TORTOISE_DIALOGUES(){
		Hare.WalkWithTransform ();
		Tortoise.WalkWithTransform ();
		yield return new WaitForSeconds (Tortoise.animationController.GetCurrentPlayingClipLength());
		cameraController.ZoomIn ();

		Giraafe.Talk ();
		Giraafe.Order ();
		yield return new WaitForSeconds (Giraafe.animationController.GetCurrentPlayingClipLength ());
//		Giraafe.dialogController.ChangeText ("I thought we settled this one at the last Jungle Olympics");
		Giraafe.MoveLeft();
		Giraafe.Talk ();
		Giraafe.dialogController.PopDialogue ("أعتقد أننا سوينا هذه \nالقضية في دورة الألعاب \nالأولمبية الأخيرة في الغابة.");
//		Giraafe.TalkRight ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//214

//		Giraafe.dialogController.ChangeText ("Didn’t Tortoise win the race between you two?");
		Giraafe.dialogController.ChangeText ("ألم تفز السلحفاة \nبالسباق الذي تم بينكما؟");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//215
		Giraafe.MakeIdle ();
		Giraafe.dialogController.UnPopDialogue ();

		yield return new WaitForSeconds (2f);

		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<JungleHubController>().HarePosition);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

		cameraController.PanRight (0.25f);
//		Hare.dialogController.PopDialogue ("I challenge that victory, Judge!");
		Hare.dialogController.PopDialogue ("أنا اعترض على هذا الفوز،\n حضرة القاضية!"); 
		Hare.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//216
		//		Hare.dialogController.ChangeText ("Ever since crossing the finish line this tortoise hasn’t moved an inch");//217
		Hare.dialogController.ChangeText ("فمنذ عبور خط \nالنهاية لم تتحرك \nالسلحفاة شبراً واحداً.");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//217
//		Hare.dialogController.ChangeText ("He couldn’t possibly have beat me in a race!");
		Hare.dialogController.ChangeText ("فلا يمكنه أن يفوز علي \nفي سباق");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//218
		Hare.dialogController.UnPopDialogue ();
		Hare.MakeIdle ();
		yield return new WaitForSeconds (2f);

		MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<JungleHubController>().TurtleBubblePOsition);
		yield return new WaitForSeconds (0.35f);
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

//		Tortoise.dialogController.PopDialogue ("I’ll tie your ears into a knot, Hare!");
		Giraafe.MoveRight();
		cameraController.PanLeft (0.25f);
		Tortoise.dialogController.PopDialogue ("سأعقد أذنيك يا أرنب");
		Tortoise.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//219
//		Tortoise.dialogController.ChangeText ("I won fair and square.");
		Tortoise.dialogController.ChangeText ("لقد فزت بنزاهة وجدارة");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//220
//		Tortoise.dialogController.ChangeText ("And I got the medal right here to prove it");
		Tortoise.dialogController.ChangeText ("ولدي الميدالية هنا\n  لنثبت ذلك");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//221
		Tortoise.dialogController.ChangeText ("سابقيني مجددًا\n وسوف ترين!");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//222

		Tortoise.dialogController.UnPopDialogue ();
		Tortoise.MakeIdle ();
		yield return new WaitForSeconds (2f);

//		Hare.dialogController.PopDialogue ("Race me again and you’ll see!");
		cameraController.Normal();
		Giraafe.MoveLeft ();
		Hare.dialogController.PopDialogue ("حضرة القاضية، أطالب\n بإعادة المباراة\n ضد هذه المخادعة!");
		Hare.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//223
		Hare.dialogController.UnPopDialogue ();
		Hare.MakeIdle ();

		yield return new WaitForSeconds (2f);

//		Giraafe.dialogController.PopDialogue ("This is court of law! ");
		Giraafe.Talk ();
		Giraafe.Order ();
		yield return new WaitForSeconds (Giraafe.animationController.GetCurrentPlayingClipLength ());
		Giraafe.MoveRight ();
		Giraafe.Talk ();
		Giraafe.dialogController.PopDialogue ("هذه قاعة محكمة!");
		//Giraafe.TalkRight ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//224
//		Giraafe.dialogController.ChangeText ("There will be no demands or name-calling here!");
		Giraafe.dialogController.ChangeText ("لا يُسمح \nفيها بإلقاء الشتائم ! ");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//225
//		Giraafe.dialogController.ChangeText ("Mr. Tortoise, do you accept Ms. Hare’s challenge to a rematch?");
		Giraafe.dialogController.ChangeText ("أيتها السلحفاة، هل\n تقبلين تحدي السيد\n أرنب لإعادة السباق؟");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//226
		Giraafe.dialogController.UnPopDialogue ();
		Giraafe.MakeIdle ();

		yield return new WaitForSeconds (2f);


//		Tortoise.dialogController.PopDialogue ("To race??");
		Tortoise.dialogController.PopDialogue ("السباق؟");
		Tortoise.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//227
//		Tortoise.dialogController.ChangeText ("Never happening, Judge.");
		Tortoise.dialogController.ChangeText ("لن يحدث، حضرة القاضية");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//228

//		Tortoise.dialogController.ChangeText ("But I’ll appoint a champion to represent me, If there is one in the crowd!");
		Tortoise.dialogController.ChangeText ("ولكني سأختار بطلاً \nليمثلني من بين الجمهور!");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//229
		Tortoise.dialogController.UnPopDialogue ();
		Tortoise.MakeIdle ();


		yield return new WaitForSeconds (1f);

//		Hare.dialogController.PopDialogue ("If that medal is on the line, I’m game for anything!");
		Hare.dialogController.PopDialogue ("إذا كانت هذه الميدالية \nعلى المحك، فأنا \nأوافق على أي شيء!");
		Hare.Talk ();
		Giraafe.MoveLeft ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//230
		Hare.dialogController.UnPopDialogue ();
		Hare.MakeIdle ();


		Giraafe.Talk ();
//		Giraafe.dialogController.PopDialogue ("It seems we have a race on our hands.");
		Giraafe.dialogController.PopDialogue ("يبدو ان لدينا سباق");

		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//231
//		Giraafe.dialogController.ChangeText ("Who is up to be Mr Tortoise's champion?");
		Giraafe.dialogController.ChangeText ("من سيكون بطل السيدة\n سلحفاة؟");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//232
		Giraafe.dialogController.UnPopDialogue ();
		Giraafe.MakeIdle ();

		yield return new WaitForSeconds (2f);

//		Player.dialogController.PopDialogue ("Shall we race with the Hare?");
		Player.dialogController.PopDialogue ("هلا تسابقنا مع الأرنب؟");
		Player.StartTalking ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//233
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();

		yield return new WaitForSeconds (1.5f);


		MainUIManager.Instance.decisionUiController.PopDicisionBox ("YesNoSelection");
		//		MainUIManager.Instance.decisionUiController.PopDicisionBox ("نعم/لا");
		yield return new WaitUntil (()=>(MainUIManager.Instance.decisionUiController.proceedStatus == true));
		yield return new WaitForSeconds (1.5f);
		MainUIManager.Instance.decisionUiController.UnPopDecisionBox();

		PopulateJungleCourtQuest ();
		yield return new WaitForSeconds (1.6f);
		MainUIManager.Instance.hudController.gameObject.SetActive (false);

		MainUIManager.Instance.loadingUiController.ActivateHareRunQuest ();
		AsyncOperation operation=Application.LoadLevelAsync ("2dInfiniteRunner");
		yield return new WaitUntil (() => (operation.isDone == true));
		MainUIManager.Instance.loadingUiController.DeActivate ();
		yield return new WaitUntil (() => (GameManager.Instance.QuestInitialized == false));
		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		MainUIManager.Instance.loadingUiController.Activate();
		operation = Application.LoadLevelAsync ("JungleCourt");
		yield return new WaitUntil (() => (operation.isDone == true));
		MainUIManager.Instance.loadingUiController.DeActivate();

		Player = GameObject.FindObjectOfType<KatkootiController>() ;
		Tortoise = GameObject.FindObjectOfType<TortoiseController>() ;
		Hare = GameObject.FindObjectOfType<HareController>() ;
		Giraafe = GameObject.FindObjectOfType<GiraafeController>() ;
		cameraController = Camera.main.gameObject.GetComponent<CameraController> ();
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		Player.transform.position = GameObject.FindObjectOfType<JungleHubController> ().PlayerDefaultPos.transform.position;
		Tortoise.transform.position = GameObject.FindObjectOfType<JungleHubController> ().TurtleDefaultPos.transform.position;
		Hare.transform.position = GameObject.FindObjectOfType<JungleHubController> ().HareDefaultPosition.transform.position;

	//	yield return new WaitForSeconds (1f);


		SoundManager.Instance.PlaySoundOneShot ("WinningSound");
		yield return new WaitForSeconds (4f);
		Player.Celebrations();
		SoundManager.Instance.PlaySoundOneShot ("KKClap");
		Player.MakeIdle ();


		yield return new WaitForSeconds (2f);
//		Tortoise.dialogController.PopDialogue ("Was the Hare caught sleeping once again?");
		Tortoise.dialogController.PopDialogue ("هل عُثر على الأرنب \nنائمًا مجددًا؟");
		Tortoise.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//239

		Tortoise.dialogController.UnPopDialogue ();
		Tortoise.MakeIdle ();

		yield return new WaitForSeconds (1f);

		Player.dialogController.PopDialogue ("هل يفعل ذلك كل مرة؟");
		Player.StartTalking ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//240
		Player.dialogController.ChangeText("ربما عليه أن يراجع طبيبًا");
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//241
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();


		Giraafe.MoveLeft ();
		Giraafe.Talk ();
//		Giraafe.dialogController.PopDialogue ("I declare Tortoise's champion Katkooti the winner ");
		Giraafe.dialogController.PopDialogue ("أعلن أن كتكوتي بطل \nالسلحفاة هو الفائز ");
		float temptime = SoundManager.Instance.PlayJungleCourtDialogue () / 2;

		yield return new WaitForSeconds (temptime);//242
		Giraafe.dialogController.ChangeText("وسأمنح هذه الميدالية \nللمتسابق الذي دار بشكل جيد!");
		yield return new WaitForSeconds (temptime);
		Giraafe.dialogController.UnPopDialogue ();
		Giraafe.MakeIdle ();

		GameObject.FindObjectOfType<JungleHubController> ().JeenaMedal.SetActive (true);
		SoundManager.Instance.PlaySoundOneShot ("MonkeyMedal");
		yield return new WaitForSeconds (2f);
		GameObject.FindObjectOfType<JungleHubController> ().JeenaMedal.SetActive (false);


		MainUIManager.Instance.inventoryController.Activate ();
		//MainUIManager.Instance.inventoryController.ResetInventory (3,3);
		yield return new WaitForSeconds (1f);
		MainUIManager.Instance.inventoryController.PopulateAt (GameObject.FindObjectOfType<JungleHubController> ().JeenaMedalImage, 3);

		yield return new WaitForSeconds (0.5f);


//		Hare.dialogController.PopDialogue ("You ran a good race but I won't go easy on you next time.");
		Hare.dialogController.PopDialogue ("لقد جريت في السباق جيدًا \nولكنني لن أتساهل \nمعك في المرة القادمة");
		Hare.Talk ();
		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//243
		Hare.dialogController.UnPopDialogue ();
		Hare.MakeIdle ();

		// Delete from here ...........................................
		SoundManager.Instance.InrementJungleCourtSound();
////		Hare.dialogController.ChangeText ("Come to me if you want to race again");
//		Hare.dialogController.ChangeText ("تعال الي إذا رغبت \nفي السباق مجددًا");
//		yield return new WaitForSeconds (SoundManager.Instance.PlayJungleCourtDialogue());//244
//		Hare.dialogController.UnPopDialogue ();
//		Hare.MakeIdle ();
//		yield return new WaitForSeconds (2f);
		//
		//		Player.dialogController.PopDialogue ("We have power left over, ");
		//		Player.StartTalking ();
		//		yield return new WaitForSeconds (2f);
		//		Player.dialogController.ChangeText ("why don’t we use it to make our home nicer?");
		//		yield return new WaitForSeconds (2f);
		//		Player.dialogController.ChangeText ("USE MY WORDSONG POWER TO Build new things in my home");
		//		yield return new WaitForSeconds (2f);
		//		Player.dialogController.UnPopDialogue ();
		//		Player.MakeIdle ();
		//		yield return new WaitForSeconds (2f);
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		MainUIManager.Instance.hudController.EnableUIMapGlow ();


		PlayCurrentState ();
		//MainUIManager.Instance.mapUIController.Activate ();
	}

	IEnumerator RUUNER_GAME_HAIR(){


		yield return new WaitForSeconds (0);


		PlayCurrentState ();
	}
	IEnumerator ENDING_DIALOGUES(){
		yield return new WaitForSeconds (0f);
		PlayCurrentState ();

	}
	IEnumerator FINISH(){
		yield return new WaitForSeconds (2f);
		PlayCurrentState ();

	}




}
