using UnityEngine;
//using UnityEditor;
using System.Collections;

public class TutorialController   {


	private CameraController cameraController;
	private KatkootiController Player;
	public enum TutorialStates{
		NONE,
		KATKOOTI_INTRO,
		PLAYER_INTRO,
		BUILD_HOME_DIALOG,
		PLAYER_TAP_TO_BUILD_HOME,
		MORE_GOODS_REQUIRED,
		//        QUESTION_FOR_QUEST,
		//        INTRO_ABOUT_LETTER,
		//        REMIND_ABOUT_TUTORIAL_QUEST_ITEM,
		RETURN_TO_HABITAT,
		DEMAND_MORE_ITEMS_FOR_HABITAT,
		GLOWING_NOTE,
		TAP_ON_MAP,
		FININSH
	}
	private TutorialStates currentTutorialState = TutorialStates.NONE;
	public TutorialStates getCurrentState(){
		return currentTutorialState;
	}
	public void PopulateTutorialQuest(){
		GameManager.Instance.CurrentQuest = new Quest ();
		// get Letters from list from gamemanager;
		GameManager.Instance.CurrentQuest.quest_location = Quest.QUEST_LOCATION.JUNGLE_RUN;
		GameManager.Instance.CurrentQuest.allowedPath_JungleRun = Quest.JUNGLE_RUN.LAND_AND_AIR; 
		GameManager.Instance.CurrentQuest.questItems=new QuestItem[1];
		GameManager.Instance.CurrentQuest.questItems[0]=GameManager.Instance.getQuestItem("Wood",3);
		GameManager.Instance.CurrentQuest.questItems [0].canSpawnState = Quest.JUNGLE_RUN.LAND;
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
		// load Quest GameObject From resources by gamemanager
		GameManager.Instance.TogglePopulateQuest (GameManager.Instance.CurrentQuest);
	}

	public TutorialController(){
		GameManager.GameInitialize += OnGameInitialized;

	}

	~TutorialController(){
		GameManager.GameInitialize -= OnGameInitialized;
	}

	public void Reset(){
		currentTutorialState = TutorialStates.NONE;
		GameManager.Instance.StopAllCoroutines ();

		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		MainUIManager.Instance.decisionUiController.UnPopGenericTapIcon ();
		MainUIManager.Instance.decisionUiController.UnPopTap ();
	}

	void OnGameInitialized(){
		

		if (GameManager.Instance.getCurrentGameState () + 1 >= GameManager.GameSate.TUTORIAL && Application.loadedLevelName == "MainScene") {
			MainUIManager.Instance.hudController.mapIcon.SetActive (false);
			Player = GameObject.FindObjectOfType<KatkootiController> ();
			cameraController = Camera.main.gameObject.GetComponent<CameraController> ();
			PlayCurrentState ();
		} else if(Application.loadedLevelName == "MainScene"){
			// other sequence;
//			SoundManager.Instance.PlaySoundOneShot("Dummy");
//			SoundManager.Instance.getSoundLengthByName("Dummy");
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			Player = GameObject.FindObjectOfType<KatkootiController> ();
			cameraController = Camera.main.gameObject.GetComponent<CameraController> ();
			GameManager.Instance.StartCoroutine(GameManager.Instance.tutorialController.NotAvailable());
		}



	}

	IEnumerator NotAvailable(){
		yield return new WaitForSeconds(0);
	}
	void ProceedState(){
		currentTutorialState++;
		if (currentTutorialState == TutorialStates.FININSH) {
			if (GameManager.Instance.getCurrentGameState () + 1 == GameManager.GameSate.TUTORIAL) {
				GameManager.Instance.ProceedGameState ();
			}
			MainUIManager.Instance.mapUIController.Activate ();
		}
	}
	void PlayCurrentState(){
		ProceedState ();
		switch (currentTutorialState) {
		case TutorialStates.KATKOOTI_INTRO:
			GameManager.Instance.StartCoroutine(GameManager.Instance.tutorialController.KatkootiIntro());
			break;
		case TutorialStates.PLAYER_INTRO:
			GameManager.Instance.StartCoroutine(GameManager.Instance.tutorialController.PlayerIntro());
			break;
		case TutorialStates.BUILD_HOME_DIALOG:
			GameManager.Instance.StartCoroutine(GameManager.Instance.tutorialController.BUILD_HOME_DIALOG());
			break;
		case TutorialStates.PLAYER_TAP_TO_BUILD_HOME:
			GameManager.Instance.StartCoroutine(GameManager.Instance.tutorialController.PLAYER_TAP_TO_BUILD_HOME());
			break;
		case TutorialStates.MORE_GOODS_REQUIRED:
			GameManager.Instance.StartCoroutine(GameManager.Instance.tutorialController.MORE_GOODS_REQUIRED());
			break;
		case TutorialStates.RETURN_TO_HABITAT:
			GameManager.Instance.StartCoroutine (GameManager.Instance.tutorialController.RETURN_TO_HABITAT ());
			break;
		case TutorialStates.DEMAND_MORE_ITEMS_FOR_HABITAT:
			GameManager.Instance.StartCoroutine (GameManager.Instance.tutorialController.DEMAND_MORE_ITEMS_FOR_HABITAT ());
			break;
		case TutorialStates.GLOWING_NOTE:
			GameManager.Instance.StartCoroutine (GameManager.Instance.tutorialController.GLOWING_NOTE ());
			break;
		case TutorialStates.TAP_ON_MAP:
			GameManager.Instance.StartCoroutine (GameManager.Instance.tutorialController.TAP_ON_MAP ());
			break;
		default:
			break;
		}

	}

	IEnumerator KatkootiIntro(){
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		yield return new WaitForSeconds (0.4f);
		Player.WalkWithTransform ();
		yield return new WaitForSeconds(Player.animationController.GetCurrentPlayingClipLength());
		//        Player.MakeIdle ();
		yield return new WaitForSeconds (0.4f);
		Player.WaveHand ();
		//        yield return new WaitForSeconds(Player.animationController.GetCurrentPlayingClipLength()-2);
	//	SoundManager.Instance.PlaySoundOneShot ("Dummy");
		Player.StartTalking ();
//		Player.dialogController.PopDialogue ("Good morning!");
		Player.dialogController.PopDialogue ("صباح الخير!");
//		Player.dialogController.PopDialogue ("ربما توجد طريقة ما لإعادة\n شحنها لكي يمكنني إتمام بناء منزل");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//13
//		Player.dialogController.ChangeText("Are you new to Jungle Town?");
		//Player.dialogController.ChangeText("هل أنت جديد هنا \n في مدينة الأدغال؟");
		//yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//14
//		Player.dialogController.ChangeText("I just moved here too!");
	//	Player.dialogController.ChangeText("أنا ايضا إنتقلت هنا للتوا!");
		//yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//15

		SoundManager.Instance.InrementTutorialSound ();
		SoundManager.Instance.InrementTutorialSound ();
		Player.MakeIdle ();
		//yield return new WaitForSeconds(1f);
		cameraController.ZoomIn ();
		Player.StartTalking3 ();
//		Player.dialogController.ChangeText("My name is Katkooti");
		Player.dialogController.ChangeText("اسمي كتكوتي");

		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//16

//		Player.dialogController.ChangeText("I haven’t seen a lot of people like you before, so you must be really special.");
		//Player.dialogController.ChangeText("لم أرى أناسًا كثيرين مثلك من\n قبل، لابد أنك مميز بحق");
		//yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//17
		SoundManager.Instance.InrementTutorialSound ();
		Player.MakeIdle ();
		cameraController.Normal ();
		//yield return new WaitForSeconds(1f);
		//        Player.dialogController.ChangeText("");
		//        yield return new WaitForSeconds(Player.animationController.GetCurrentPlayingClipLength());

		PlayCurrentState ();
	}

	IEnumerator PlayerIntro()
	{
		//        camera
		Player.WaveHand ();
//		Player.dialogController.ChangeText("What should I call you?");
//				Player.dialogController.ChangeText("بم يمكنني أن أناديك");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//18
		SoundManager.Instance.InrementTutorialSound ();
		Player.dialogController.UnPopDialogue();
	


//		MainUIManager.Instance.decisionUiController.PopDicisionBox ("GenderSelection");
//	//	yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//19
//	//	yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//20
		SoundManager.Instance.InrementTutorialSound();
		SoundManager.Instance.InrementTutorialSound();
//		//		MainUIManager.Instance.decisionUiController.PopDicisionBox ("");
//		//    Debug.Log (MainUIManager.Instance.decisionUiController.proceedStatus);
//		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//		MainUIManager.Instance.decisionUiController.UnPopDecisionBox();
		yield return new WaitForSeconds(.5f);
		PlayCurrentState ();

	}


	IEnumerator BUILD_HOME_DIALOG(){
		yield return new WaitForSeconds (1.6f);
		//SoundManager.Instance.PlaySoundOneShot ("Dummy");
		Player.StartTalking2 ();
		SoundManager.Instance.PlaySoundOneShot ("Birds");
//		Player.dialogController.PopDialogue ("A cool breeze was blowing and it made me so happy!");
		Player.dialogController.PopDialogue ("لقد هبت نسمة \nمنعشة أسعدتني كثيرًا!");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//23
//		Player.dialogController.ChangeText("It was magical!");
		Player.dialogController.ChangeText("لقد كانت ساحرة!");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//24
//		Player.dialogController.ChangeText("I feel different, like something amazing has happened...");
		Player.dialogController.ChangeText("أشعر بشيء غريب، كأن شيئًا\n مذهلاً قد حدث!");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//25
//		Player.dialogController.ChangeText("Stand back!");
//		Player.dialogController.ChangeText("تراجع للخلف!");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//26
		SoundManager.Instance.InrementTutorialSound();
		cameraController.ZoomIn ();
//		Player.dialogController.ChangeText("Something is happening!");
//		Player.dialogController.ChangeText("ثمة شيء يحدث!");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());  //27
		SoundManager.Instance.InrementTutorialSound();
		Player.dialogController.UnPopDialogue ();

		Player.MakeIdle ();
		SoundManager.Instance.PlaySoundOneShot ("SongBarPowerUp");

		Player.KKGlowAnimation ();
		cameraController.ExtraZoomIn ();
		GameManager.Instance.ChickSongPowerValue = 1;
		Player.dialogController.UnPopDialogue ();
		yield return new WaitForSeconds (2);
		//yield return new WaitForSeconds(4f);
		Player.StartTalking ();

//		Player.dialogController.PopDialogue ("I am glowing!");
				Player.dialogController.PopDialogue ("أنا متوهج!");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//28
//		Player.dialogController.ChangeText ("It feels amazing!");
				Player.dialogController.ChangeText ("إنه شعور مدهش!");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//29
//		Player.dialogController.ChangeText ("I think we can do anything with this power!");
		Player.dialogController.ChangeText ("أعتقد أنه يمكننا عمل أي شيء \nباستخدام هذه القوة!");
		cameraController.Normal ();
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//30
//		Player.dialogController.ChangeText ("Let’s give it a test");
				Player.dialogController.ChangeText ("لنختبر ذلك");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//31
//		Player.dialogController.ChangeText ("Shall we use this power to build a home?");
				Player.dialogController.ChangeText ("هل سنستخدم هذه القوة لبناء\n بيت؟");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//32
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();
		GameManager.Instance.ChickSongPowerValue = 1;
		//yield return new WaitForSeconds (1.6f);

		PlayCurrentState ();
	}
	IEnumerator PLAYER_TAP_TO_BUILD_HOME(){
		
	
		//        Player.dialogController.PopDialogue ("Double Tap here to use the power to build my home");
		//        yield return new WaitForSeconds(2f);
		//        /*
		//yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//33
		SoundManager.Instance.InrementTutorialSound();
		GameManager.Instance.getHabitat ().exterior.ActivateLevel0Glow ();
		MainUIManager.Instance.decisionUiController.PopTap (GameManager.Instance.getHabitat().exterior.chickHome);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));

		Player.Celebrations ();
		MainUIManager.Instance.decisionUiController.UnPopTap ();
		SoundManager.Instance.PlaySoundOneShot ("SongBarPowerDown");
		yield return new WaitForSeconds(0.3f);
		//        */
		Player.MakeIdle();

		Player.animationController.PlayAnimation ("ChickSong");
		//        Player.dialogController.UnPopDialogue ();
		MainUIManager.Instance.StartCoroutine (MainUIManager.Instance.hudController.StarEffect ());
		GameManager.Instance.ChickSongPowerValue = 0;
		yield return new WaitForSeconds (0.2f);


		///MainUIManager.Instance.hudController.StartCoroutine (MainUIManager.Instance.hudController.FillChickSongBar);
		GameManager.Instance.InstantiateObject ("ConstructionParticles", GameManager.Instance.getHabitat ().HouseBuildEffect.transform.position);
		GameManager.Instance.EnableExterior ();

		//GameManager.Instance.InstantiateObject ("ConstructionParticles", GameManager.Instance.getHabitat ().HouseBuildEffect.transform.position);
		yield return new WaitForSeconds (0.3f);
		SoundManager.Instance.PlaySoundOneShot ("KKClap");
	
		//yield return new WaitForSeconds (3f);
//		Player.dialogController.PopDialogue ("That was so much fun!....");

		Player.dialogController.PopDialogue ("لقد كان ذلك ممتعًا لل غاية!...");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//34
		Player.StartTalking ();
		Player.dialogController.UnPopDialogue ();
//		Player.dialogController.ChangeText ("But my home doesn’t look quite finished yet");
	//	Player.dialogController.ChangeText ("ولكن يبدو أن بيتي لم ينته\n بناؤه بعد");
		yield return new WaitForSeconds (1f);
		//Player.dialogController.ChangeText ("ولكن يبدو أن بيتي لم \n ينته بناؤه بعد.");
		Player.dialogController.PopDialogue ("");
		yield return new WaitForSeconds (0.15f);
		Player.dialogController.EnableTempDialogueImage();
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//35
		Player.dialogController.DisableTempDialogueImage();
//		Player.dialogController.ChangeText ("I think we need more wood");
		Player.dialogController.ChangeText ("أعتقد أننا نحتاج مزيدًا من\n الأخشاب");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//36
		//        Maybe there is some way to recharge it so I can finish building my house
//		Player.dialogController.ChangeText ("My power seems to be finished also…");
		Player.dialogController.ChangeText ("يبدو أن قوتي قد\n انتهت كذلك ...");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//37-1
//		Player.dialogController.ChangeText ("Maybe there is some way to recharge it so I can finish building my house");
		Player.dialogController.ChangeText ("ربما توجد طريقة ما\n لإعادة شحنها\n لكي يمكنني إتمام بناء منزلي");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//37-2

		//        Player.dialogController.ChangeText ("Maybe there is some way to recharge it so I can finish building my house.");
		//        yield return new WaitForSeconds(3f);
		//
		//        Player.dialogController.ChangeText ("so I can finish building my house");
		//        yield return new WaitForSeconds(3f);
//		SoundManager.Instance.PlaySoundOneShot ("MagicalSwoosh");
//		Player.dialogController.ChangeText ("That storm sure brought a lot of magical things to this place");
		Player.dialogController.ChangeText ("لابد أن هذه العاصفة أحضرت \nالكثير من الأشياء\n السحرية إلى هنا");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//38

		SoundManager.Instance.PlaySoundOneShot ("Birds");
//		Player.dialogController.ChangeText ("I wonder what I can find deeper in the jungle!");
		Player.dialogController.ChangeText ("أتساءل مالذي يمكنني أن أجده\nفي أعماق الغابة");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//39

//		Player.dialogController.ChangeText ("Shall we go deeper into the jungle!");
	//	Player.dialogController.ChangeText ("هل ندخل إلى أعماق الغابة؟");


		Player.dialogController.UnPopDialogue ();
		SoundManager.Instance.InrementTutorialSound ();
		//	yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//40
		MainUIManager.Instance.decisionUiController.PopDicisionBox ("YesNoSelection");

//				MainUIManager.Instance.decisionUiController.PopDicisionBox ("نعم/ لا");
		yield return new WaitUntil (() => MainUIManager.Instance.decisionUiController.proceedStatus == true);
		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
	
		//yield return new WaitForSeconds(3f);
		//yield return new WaitForSeconds(SoundManager.Instance.getSoundLengthByName("Dummy")-1f);
		Player.MakeIdle ();
		PlayCurrentState ();
	}
	IEnumerator MORE_GOODS_REQUIRED(){
		PopulateTutorialQuest ();
		MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);

		MainUIManager.Instance.hudController.gameObject.SetActive (false);
		MainUIManager.Instance.loadingUiController.ActivateLogQuest ();
		AsyncOperation operation = Application.LoadLevelAsync ("2dInfiniteRunner");
		yield return new WaitUntil (() => (operation.isDone == true));
		MainUIManager.Instance.loadingUiController.DeActivate ();

		yield return new WaitUntil (() => (GameManager.Instance.QuestInitialized == false));
		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		MainUIManager.Instance.loadingUiController.Activate ();
		operation = Application.LoadLevelAsync ("MainScene");
		yield return new WaitUntil (() => (operation.isDone == true));
		MainUIManager.Instance.loadingUiController.DeActivate ();
		//yield return new WaitForSeconds (3f);
	//	GameManager.Instance.InstantiateObject ("ConstructionParticles", GameManager.Instance.getHabitat ().HouseBuildEffect.transform.position);
		GameManager.Instance.EnableExterior ();

		cameraController = Camera.main.gameObject.GetComponent<CameraController> ();
		Player = GameObject.FindObjectOfType<KatkootiController>() ;
		Player.transform.position = GameObject.FindGameObjectWithTag ("SceneByDefaultPosition").transform.position;

		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		SoundManager.Instance.PlaySoundOneShot ("SongBarPowerUp");
	//	SoundManager.Instance.PlaySoundOneShot ("Dummy");
		//Player.StartTalking ();

	//	yield return new WaitForSeconds(SoundManager.Instance.getSoundLengthByName("Dummy")-1f);
		Player.MakeIdle ();
		PlayCurrentState ();
	}

	IEnumerator RETURN_TO_HABITAT(){
		//        Player.dialogController.PopDialogue ("Tap Here to Use my Wordsong");
		        yield return new WaitForSeconds(1f);
		Player.KKGlowAnimation ();
		yield return new WaitForSeconds(2f);
		SoundManager.Instance.InrementTutorialSound();
		MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
		GameManager.Instance.getHabitat ().exterior.ActivateLevel1Glow ();

		MainUIManager.Instance.decisionUiController.PopTap (GameManager.Instance.getHabitat().exterior.BuildchickHome);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		MainUIManager.Instance.decisionUiController.UnPopTap ();
	
		MainUIManager.Instance.inventoryController.ResetInventory ();
		//        Player.dialogController.UnPopDialogue ();
	

		SoundManager.Instance.PlaySoundOneShot ("SongBarPowerDown");
		Player.animationController.PlayAnimation ("ChickSong");
		GameManager.Instance.ChickSongPowerValue = 0;
		MainUIManager.Instance.StartCoroutine (MainUIManager.Instance.hudController.StarEffect ());
		//yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());
	    GameManager.Instance.EnableExterior ();
	
		GameManager.Instance.InstantiateObject ("ConstructionParticles", GameManager.Instance.getHabitat ().HouseBuildEffect.transform.position);
		//yield return new WaitForSeconds(SoundManager.Instance.getSoundLengthByName("Dummy")-1f);
		Player.MakeIdle ();
		PlayCurrentState ();
	}

	IEnumerator DEMAND_MORE_ITEMS_FOR_HABITAT(){

		yield return new WaitForSeconds (2f);
		Player.StartTalking ();
//		Player.dialogController.PopDialogue ("That’s so amazing!");
		SoundManager.Instance.PlaySoundOneShot ("Birds");
//				Player.dialogController.PopDialogue ("هذا مذهل للغاية!");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//48
		SoundManager.Instance.InrementTutorialSound();
//		Player.dialogController.ChangeText ("Lets take a look inside");
		Player.dialogController.PopDialogue ("هيا لنلقي نظرة من\nالداخل");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//49

		Player.MakeIdle ();
		Player.dialogController.UnPopDialogue ();

		yield return new WaitForSeconds (0.5f);

		MainUIManager.Instance.decisionUiController.PopTap (GameManager.Instance.getHabitat().exterior.BuildchickHome);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		MainUIManager.Instance.decisionUiController.UnPopTap ();
		GameObject.FindObjectOfType<Habitat> ().GetComponent<Habitat> ().FadeIn ();
		yield return new WaitForSeconds(1.5f);
		GameManager.Instance.EnableInterior ();
		yield return new WaitForSeconds(1.5f);
		GameObject.FindObjectOfType<Habitat> ().GetComponent<Habitat> ().FadeOut ();
		//        cameraController.PanLeft (1f);
		//        yield return new WaitForSeconds(3f);
		yield return new WaitForSeconds(0.5f);
//		Player.dialogController.PopDialogue ("What a beautiful home we built!");
		Player.dialogController.PopDialogue ("ما أجمل البيت الذي\nبنيناه!");
		Player.StartTalking2 ();
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//50
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();
		yield return new WaitForSeconds(0.5f);
		//        cameraController.PanRight (2f);
//		Player.dialogController.ChangeText ("It’s a little empty right now but im sure we will find things to fill it up");
//		Player.dialogController.ChangeText ("إنه خالٍ الآن،لكنني واثق\nأنناسنجد ما نملأه به");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//51

		SoundManager.Instance.InrementTutorialSound();

		cameraController.Normal ();
		yield return new WaitForSeconds(0.5f);

////		Player.dialogController.ChangeText ("You know, I think we make a great team.");
//		Player.dialogController.ChangeText ("أ تعلم،أرى أننا\nنشكل فريقًا رائعًا");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//52
		SoundManager.Instance.InrementTutorialSound();

//		Player.dialogController.ChangeText ("And this new talent of mine is just brilliant!");
		cameraController.ExtraZoomIn();
//		Player.dialogController.ChangeText ("وهذه الموهبة الجديدة\nالتي أتمتع بها رائعة!");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//53
		SoundManager.Instance.InrementTutorialSound();
//		Player.dialogController.ChangeText ("I’m going to stick with calling it 'WordSong'");
//		Player.dialogController.ChangeText ("سوف أختار له اسم لولو الروح‘");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//54
		SoundManager.Instance.InrementTutorialSound();
//		Player.dialogController.ChangeText ("Anytime we need it, just tap me and find something to use it with!");
//		Player.dialogController.ChangeText ("وكلما احتجناإليه،ماعليك سوى النقر\nفوقي لتجد شيئًا يمكنك استخدامه معه!");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//55
		SoundManager.Instance.InrementTutorialSound();
		yield return new WaitForSeconds(0.5f);
		cameraController.ZoomIn ();
//		Player.dialogController.ChangeText ("But don’t forget, we need to charge it up by collecting letters each time.");
//				Player.dialogController.ChangeText ("ولكن لا تنس أننا نحتاج إلى شحنه\nعن طريق جمع الحروف في كل مرة");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//56
		SoundManager.Instance.InrementTutorialSound();
//		Player.dialogController.ChangeText ("That should be easy, right?");
//		Player.dialogController.ChangeText ("وهذا أمراً سهل، أليس كذلك؟");
//
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//57
		SoundManager.Instance.InrementTutorialSound();


		PlayCurrentState ();
	}

	IEnumerator GLOWING_NOTE(){

		yield return new WaitForSeconds (2f);
		Player.StartTalking2 ();
		cameraController.ExtraZoomIn ();
		GameManager.Instance.EnableGlowMap ();
	
//		Player.dialogController.PopDialogue ("What is that glowing note?");
		Player.dialogController.PopDialogue ("ما هذه العلامة المتوهجة؟");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//58
		Player.dialogController.UnPopDialogue();

		MainUIManager.Instance.decisionUiController.PopGenericTapIcon(GameManager.Instance.getHabitat().interior.glowNote);

		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));

		MainUIManager.Instance.decisionUiController.UnPopGenericTapIcon ();
		GameManager.Instance.DisableGlowMap ();



//		Player.dialogController.ChangeText ("Someone must have left it here while we were out");
//		Player.dialogController.PopDialogue ("لا بد أن أحدهم تركها هنا\nفيما كنا بالخارج المنضدة");
//		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//59

		SoundManager.Instance.InrementTutorialSound();

	
		cameraController.Normal();
		Player.MakeIdle ();
		PlayCurrentState ();
	}

	IEnumerator TAP_ON_MAP(){
		

		        yield return new WaitForSeconds (2.5f);


		Player.StartTalking3 ();
		//		Player.dialogController.ChangeText ("Hmm looks like the Monkeys need our help! Lets go help them out");
		Player.dialogController.PopDialogue ("يبدو أن القرود يحتاجون إلى\nمساعدتنا");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//60
		Player.dialogController.ChangeText ("لنذهب لمساعدتهم");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//61

	



	

		//		Player.dialogController.ChangeText ("Tap on the Map to see which locations you can visit");
		Player.dialogController.ChangeText ("انقر فوق الخريطة لمعرفة \nالأماكن التي يمكنك زيارتها");
		yield return new WaitForSeconds(SoundManager.Instance.PlayTutorialDialogue());//62
		Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();


		MainUIManager.Instance.hudController.mapIcon.SetActive (true);
		MainUIManager.Instance.hudController.EnableUIMapGlow ();


		MainUIManager.Instance.decisionUiController.PopTap (GameManager.Instance.getHabitat().mapPostion);
		yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
		MainUIManager.Instance.decisionUiController.UnPopTap ();
		MainUIManager.Instance.hudController.DisableUIMapGlow ();
		MainUIManager.Instance.mapUIController.Activate ();


		//yield return new WaitForSeconds (2f);

		ProceedState ();
	}



}