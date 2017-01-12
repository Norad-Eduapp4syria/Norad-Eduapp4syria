using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class TigerCaveController : MonoBehaviour {

	private KatkootiController Player;
	private TigerController Tiger;

	public MonkeyController[] Monkeys;



	public enum TigerCaveState{
		NONE,
		SCENE_INTRO,
		PARTY_FURNITURE,
		FINISH
	}
	private TigerCaveState currentTigerState = TigerCaveState.NONE;
	public TigerCaveState getCurrentState(){
		return currentTigerState;
	}


	public TigerCaveController(){
		GameManager.GameInitialize += OnGameInitialized;

	}

	~TigerCaveController(){
		GameManager.GameInitialize -= OnGameInitialized;
	}
	public void Reset(){
		currentTigerState = TigerCaveState.NONE;
		GameManager.Instance.StopAllCoroutines ();

		MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
		MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
		MainUIManager.Instance.decisionUiController.UnPopGenericTapIcon ();
		MainUIManager.Instance.decisionUiController.UnPopTap ();
	}
	void OnGameInitialized(){
		
		if (GameManager.Instance.getCurrentGameState () + 1 >= GameManager.GameSate.TIGER_CAVE && Application.loadedLevelName == "TigerCave") {
			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			Player = GameObject.FindObjectOfType<KatkootiController> ();
			Tiger = GameObject.FindObjectOfType<TigerController> ();
			PlayCurrentState ();
		} else if(Application.loadedLevelName == "TigerCave"){
			MainUIManager.Instance.hudController.inventoryIcon.SetActive (true);
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			Tiger = GameObject.FindObjectOfType<TigerController> ();
			GameManager.Instance.StartCoroutine(GameManager.Instance.tigerCaveController.NotAvailable());
		}

		if (GameManager.Instance.getCurrentGameState () + 1 != GameManager.GameSate.TIGER_CAVE && Application.loadedLevelName == "TigerCave") {
			MainUIManager.Instance.hudController.gameObject.SetActive (true);
			MainUIManager.Instance.hudController.EnableUIMapGlow ();


		} else {
			MainUIManager.Instance.hudController.DisableUIMapGlow ();
		}

	}

	IEnumerator NotAvailable(){
		MainUIManager.Instance.hudController.gameObject.SetActive (true);
		MainUIManager.Instance.hudController.EnableUIMapGlow ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);
		Tiger.StartTalking (MainUIManager.Instance.decisionUiController.SelectedItem);
//		Tiger.dialogController.PopDialogue("Hi, I don't feel like playing right now.");
		Tiger.dialogController.PopDialogue("مرحبًا، لا أشعر بالرغبة \n في اللعب الآن");
		yield return new WaitForSeconds (3f);
//		Tiger.dialogController.ChangeText ("Maybe next time");
		Tiger.dialogController.ChangeText ("ربما في المرة القادمة");
		yield return new WaitForSeconds (1f);
		Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);
		Tiger.TigerSad (MainUIManager.Instance.decisionUiController.SelectedItem);
		yield return new WaitForSeconds (1f);
	}
	public void PopulateTigerBaloonQuest(){
		Quest quest= new Quest ();
		quest.LearningItemsInQuest = new LearningItem[3];
		quest.LearningItemsInQuest [0] = new LearningItem ();


		quest.LearningItemsInQuest [0].letter = "قمر";
		quest.LearningItemsInQuest [0].Maxfrequency = 1;
		quest.LearningItemsInQuest [0].soundName = "Kamar";


		quest.LearningItemsInQuest [1] = new LearningItem ();
		quest.LearningItemsInQuest [1].letter = "أم";
		quest.LearningItemsInQuest [1].Maxfrequency = 1;
		quest.LearningItemsInQuest [1].soundName = "Um";

		quest.LearningItemsInQuest [2] = new LearningItem ();
		quest.LearningItemsInQuest [2].letter = "نمر";
		quest.LearningItemsInQuest [2].Maxfrequency = 1;
		quest.LearningItemsInQuest [2].soundName = "Namar";



		GameManager.Instance.TogglePopulateQuest (quest);
	}

	void ProceedState(){
		currentTigerState++;
		if (currentTigerState == TigerCaveState.FINISH) {
			MainUIManager.Instance.hudController.EnableUIMapGlow ();
			MainUIManager.Instance.hudController.mapIcon.SetActive (true);
			if (GameManager.Instance.getCurrentGameState () + 1 == GameManager.GameSate.TIGER_CAVE) {
				GameManager.Instance.ProceedGameState ();
			}
		}
	}


	void PlayCurrentState(){
		ProceedState ();
		switch (currentTigerState) {
		case TigerCaveState.SCENE_INTRO:
			GameManager.Instance.StartCoroutine(GameManager.Instance.tigerCaveController.SCENE_INTRO());
			break;
		case TigerCaveState.PARTY_FURNITURE:
			GameManager.Instance.StartCoroutine(GameManager.Instance.tigerCaveController.PARTY_FURNITURE());
			break;

		default:
			break;
		}

	}


	IEnumerator SCENE_INTRO()
	{
		
			MainUIManager.Instance.hudController.gameObject.SetActive (true);
			yield return new WaitForSeconds (0.4f);
			//Tiger.TigerSad ();

			MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<TigerSceneController>().KKBubblePosition);
			yield return new WaitForSeconds (0.35f);
			GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
			yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
			GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
			MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

			Player.StartTalking ();
			Player.dialogController.PopDialogue ("مرحبًا يا ملك، ماالمناسبة؟");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Player.dialogController.UnPopDialogue ();
			Player.MakeIdle ();

			yield return new WaitForSeconds (1f);

			MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<TigerSceneController>().TigerBubblePosition);
			yield return new WaitForSeconds (0.35f);
			GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
			yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
			GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
			MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);
		Tiger.StartTalking (MainUIManager.Instance.decisionUiController.SelectedItem);
			Tiger.dialogController.PopDialogue ("أرررغغغ!");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
		Tiger.dialogController.UnPopDialogue ();
		yield return new WaitForSeconds (0.5f);
		Tiger.dialogController.PopDialogue ("لا أعتقد أنني أستطيع تحمل \n المزيد من هذا!");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);

			yield return new WaitForSeconds (1f);

			Player.StartTalking ();
			Player.dialogController.PopDialogue ("يا للعجب!");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Player.dialogController.ChangeText ("ما الذي أزعج ملك \nالغابة إلى هذا الحد؟");
			
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());

			Player.dialogController.UnPopDialogue ();
			Player.MakeIdle ();
	
			yield return new WaitForSeconds (1f);
	
		Tiger.StartTalking (MainUIManager.Instance.decisionUiController.SelectedItem);
			yield return new WaitForSeconds (0.5f);
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);
		Tiger.PlayTigerMe (MainUIManager.Instance.decisionUiController.SelectedItem);
			Tiger.dialogController.PopDialogue ("الجميع ينادونني بلقب ملك الغابة \n ولكن ماذا فعلت لأستحق هذا اللقب؟");
			
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);

			yield return new WaitForSeconds (0.5f);
		Tiger.PlayTigerMe (MainUIManager.Instance.decisionUiController.SelectedItem);
		Tiger.dialogController.PopDialogue ("لقد شعرت بشيء داخلي عندما نظرت إلى \n العاصفة الجميلة ليلة أمس");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);

			yield return new WaitForSeconds (0.5f);
			Tiger.dialogController.PopDialogue ("ومن الآن فصاعدًا، أريد أن\n أكونا محبوبًا، وليس مخيفًا!");
		Tiger.PlayTigerPointingUp (MainUIManager.Instance.decisionUiController.SelectedItem);
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);


			Tiger.dialogController.PopDialogue ("لذلك قررت أن أقيم حفلة\n للغابة كلها!");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);
	
			yield return new WaitForSeconds (1f);
	
			Player.StartTalking2 ();
			Player.dialogController.PopDialogue ("تلك فكرة رائعة يا ملك!");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Player.dialogController.ChangeText ("إذًا ما المشكلة؟");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Player.dialogController.UnPopDialogue ();
			Player.MakeIdle ();
	
			yield return new WaitForSeconds (1f);
			
		Tiger.StartTalking (MainUIManager.Instance.decisionUiController.SelectedItem);
			//Tiger.PlayTigerPanic ();
			Tiger.dialogController.PopDialogue ("لم أكن أحتاج إلى ملابس\n قبل العاصفة السحرية! ");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Tiger.dialogController.ChangeText ("الآن لا أعرف ماذا\n أرتدي لهذه الحفلة.");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			//Tiger.PlayTigerPanic ();
			Tiger.dialogController.ChangeText ("أحتاج ان ارتدي  شيء مبهر");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);
	
			yield return new WaitForSeconds (1f);
	
			Player.StartTalking ();
			Player.dialogController.PopDialogue ("أعدك بأنك ستكون \nأروع قط في الحفلة\n كلها يا ملك");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
		Player.dialogController.ChangeText ("لدي فكرة  ما رأيك في\n بعض الأحذية البراقة \nأو القبعة اللامعة؟");
		yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
		//	yield return new WaitForSeconds (2f);
		//	Player.dialogController.ChangeText ("الأحذية البراقة أو القبعة اللامعة؟");
		//	yield return new WaitForSeconds (3f);


			Player.dialogController.UnPopDialogue ();
		Player.MakeIdle ();
	
			yield return new WaitForSeconds (1f);
			
		Tiger.PlayAgree (MainUIManager.Instance.decisionUiController.SelectedItem);
			yield return new WaitForSeconds (Tiger.animationController.GetCurrentPlayingClipLength());
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);

		Tiger.StartTalking (MainUIManager.Instance.decisionUiController.SelectedItem);

			Tiger.dialogController.PopDialogue ("واو!");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);

//			Tiger.dialogController.ChangeText ("أنا رائع مع أي منهما!");
//			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
		SoundManager.Instance.IncrementTigerCaveDialogueSound();
			Tiger.dialogController.UnPopDialogue ();
		Tiger.MakeIdle (MainUIManager.Instance.decisionUiController.SelectedItem);
	
			yield return new WaitForSeconds (1f);
	
			Player.StartTalking ();
			Player.dialogController.PopDialogue ("أعتقد أن القردة \nقد تستطيع المساعدة");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
			Player.dialogController.ChangeText ("هلا ذهبنا إلى القردة لنعثر \nعلى بعض من ");
			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
	
			Player.dialogController.UnPopDialogue ();
			Player.MakeIdle ();
	
			yield return new WaitForSeconds (1f);

			PlayCurrentState ();
	}

	IEnumerator PARTY_FURNITURE(){

				
//				yield return new WaitForSeconds(2f);
//
//				Player.animationController.PlayAnimation ("ChickSong");
//				GameManager.Instance.ChickSongPowerValue = 0;
//				MainUIManager.Instance.StartCoroutine (MainUIManager.Instance.hudController.StarEffect ());
//				yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());
//
//				yield return new WaitForSeconds (1f);


				MainUIManager.Instance.decisionUiController.PopDicisionBox ("ItemSelection");

				//				MainUIManager.Instance.decisionUiController.PopDicisionBox ("نعم/ لا");
				yield return new WaitUntil (() => MainUIManager.Instance.decisionUiController.proceedStatus == true);
				MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();
				
				


//				Player.StartTalking3 ();
//				//		Player.dialogController.PopDialogue ("Shall we go to the monkeys?");
//				Player.dialogController.PopDialogue ("نذهب إلى القرود؟");
//		yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
//				Player.MakeIdle ();
//				Player.dialogController.UnPopDialogue ();
//
//
//				yield return new WaitForSeconds (1.5f);


				MainUIManager.Instance.decisionUiController.PopDicisionBox ("YesNoSelection");

				yield return new WaitUntil (()=>(MainUIManager.Instance.decisionUiController.proceedStatus == true));

				MainUIManager.Instance.decisionUiController.UnPopDecisionBox();


				MainUIManager.Instance.loadingUiController.Activate ();
				AsyncOperation operation = Application.LoadLevelAsync ("MonkeysHub");
				yield return new WaitUntil (() => (operation.isDone == true));

				Monkeys = GameObject.FindObjectsOfType<MonkeyController>();
				Player = GameObject.FindObjectOfType<KatkootiController>();

				Player.transform.position = GameObject.FindObjectOfType<MonkeyHubController> ().Katkooti_postion.transform.position;
				MainUIManager.Instance.loadingUiController.DeActivate ();
				yield return new WaitForSeconds (1f);
		   		
				MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().Katkooti_postion);
				yield return new WaitForSeconds (0.35f);
				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
				yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
				MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();


				Player.StartTalking ();
			//	Player.dialogController.PopDialogue ("Hey Monkeys!");
				Player.dialogController.PopDialogue ("مرحبًا أيتها القرود! ");
				yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
				//Player.dialogController.ChangeText ("Do you think you can help us find some ");//161
			Player.dialogController.ChangeText ("هل تعتقدون أن \nبإمكانكم مساعدتنا ");
		//yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
		SoundManager.Instance.IncrementTigerCaveDialogueSound ();	
//		yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
//
//		yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
		SoundManager.Instance.IncrementTigerCaveDialogueSound ();
		SoundManager.Instance.IncrementTigerCaveDialogueSound ();
				Player.dialogController.UnPopDialogue ();
				Player.MakeIdle ();

//				yield return new WaitForSeconds (1f);
//				
//				MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_1_postion);
//				yield return new WaitForSeconds (0.35f);
//				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
//				yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
//				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
//				MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
//
//
//				Monkeys [0].MonkeyTalk ();
//				//Monkeys [0].dialogController.PopDialogue ("Ahh, so you need our help? ");
//						Monkeys [0].dialogController.PopDialogue ("إذًا تحتاجون إلى مساعدتنا؟");
//		yield return new WaitForSeconds (2f);
//				//Monkeys [0].dialogController.ChangeText ("I propose a trade: ");
//				Monkeys [0].dialogController.ChangeText ("أقترح عليكم المقايضة\n او المبادلة ");
//		yield return new WaitForSeconds (2f);
//				//Monkeys [0].dialogController.ChangeText ("You do something for us, and we can do something for you?");
//				Monkeys [0].dialogController.ChangeText ("تفعلون شيئًا لأجلنا مقابل\n أن نفعل شيئًا لأجلكم؟");
//		yield return new WaitForSeconds (2f);
//				Monkeys [0].dialogController.UnPopDialogue ();
//				Monkeys [0].MonkeyIdle ();
//
//				yield return new WaitForSeconds (1f);
//
//				Monkeys [1].MonkeyTalk ();
//				//Monkeys [1].dialogController.PopDialogue ("Now that's some real Monkey Business");
//						Monkeys [1].dialogController.PopDialogue ("هذا بحق هو عمل القردة الحقيقي");
//		yield return new WaitForSeconds (2f);
//				Monkeys [1].dialogController.UnPopDialogue ();
//				Monkeys [1].MonkeyIdle ();
//
//				yield return new WaitForSeconds (1f);
//
//				Monkeys [2].MonkeyTalk ();
//				//Monkeys [2].dialogController.PopDialogue ("No it's NOT");
//						Monkeys [2].dialogController.PopDialogue ("كلا، ليس كذلك");
//		yield return new WaitForSeconds (2f);
//				Monkeys [2].dialogController.UnPopDialogue ();
//				Monkeys [2].MonkeyIdle ();
//
//				yield return new WaitForSeconds (1f);
//
//				Monkeys [3].MonkeyTalk ();
//				//Monkeys [3].dialogController.PopDialogue ("It's called…something");
//						Monkeys [3].dialogController.PopDialogue ("إنه يُدعى...شيء ما");
//		yield return new WaitForSeconds (2f);
//				Monkeys [3].dialogController.UnPopDialogue ();
//				Monkeys [3].MonkeyIdle ();
//
//				yield return new WaitForSeconds (1f);
//
//				Monkeys [0].MonkeyTalk ();
//				//Monkeys [0].dialogController.PopDialogue ("Quiet!,");
//						Monkeys [0].dialogController.PopDialogue ("صمتًا");
//		yield return new WaitForSeconds (2f);
//				//Monkeys [0].dialogController.ChangeText ("Quiet! As you can see Katkoooti, my monkeys get irritable when their words get boring");
//				Monkeys [0].dialogController.ChangeText ("كما ترى يا كتكوتي، تضطرب\n القردة عندما تصبح كلماتها مملة");
//		yield return new WaitForSeconds (2f);
//				//Monkeys [0].dialogController.ChangeText ("Help us learn new words so my monkeys can speak better!");
//				Monkeys [0].dialogController.ChangeText ("!ساعدنا على تعلم كلمات جديدة\n حتى تستطيع القردة التحدث بطريقة أفضل");
//		yield return new WaitForSeconds (2f);
//				Monkeys [0].dialogController.UnPopDialogue ();
//				Monkeys [0].MonkeyIdle ();
//
//
//				yield return new WaitForSeconds (1f);
//
//				Player.StartTalking ();
//				//Player.dialogController.PopDialogue ("Shall we help the monkeys?");
//				Player.dialogController.PopDialogue ("هلا ساعدنا القردة؟");
//		yield return new WaitForSeconds (2f);
//				Player.dialogController.UnPopDialogue ();
//				Player.MakeIdle ();
//
//				yield return new WaitForSeconds (1f);
//
//				


				
				MainUIManager.Instance.decisionUiController.PopDicisionBox ("YesNoSelection");
				yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
				MainUIManager.Instance.decisionUiController.UnPopDecisionBox ();

				PopulateTigerBaloonQuest ();


				MainUIManager.Instance.hudController.gameObject.SetActive (false);
				MainUIManager.Instance.loadingUiController.ActivateSwingingWineQuest ();
				operation = Application.LoadLevelAsync ("WF2");
				yield return new WaitUntil (()=>(operation.isDone == true));
				MainUIManager.Instance.loadingUiController.DeActivate ();

				yield return new WaitUntil(()=>(GameManager.Instance.QuestInitialized == false));

				yield return new WaitForSeconds (1f);
				MainUIManager.Instance.loadingUiController.Activate ();
				operation = Application.LoadLevelAsync ("MonkeysHub");
				yield return new WaitUntil (()=>(operation.isDone == true));
				MainUIManager.Instance.loadingUiController.DeActivate ();
				
				Player = GameObject.FindObjectOfType<KatkootiController>() ;
				Player.transform.position = GameObject.FindGameObjectWithTag ("SceneByDefaultPosition").transform.position;
				Monkeys = GameObject.FindObjectsOfType<MonkeyController> ();

			
				
				GameObject MonkeysMainObject = GameObject.FindObjectOfType<MonkeyHubController> ().gameObject;
			
				//	MainUIManager.Instance.
				MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<MonkeyHubController>().monkey_1_postion);
				yield return new WaitForSeconds (0.35f);
				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
				yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
				MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();
//
//				//		Player.dialogController.PopDialogue ("Hi Monkeys!");
//				Monkeys[0].dialogController.PopDialogue ("لديك كل العناصر يا كتكوتي");
//
//				Monkeys[0].MonkeyTalk ();
//				yield return new WaitForSeconds (2f);
//				Monkeys [0].dialogController.UnPopDialogue ();
//				Monkeys[0].MonkeyIdle ();
				

		if (MainUIManager.Instance.decisionUiController.SelectedItem == 1) {
					MonkeysMainObject.GetComponent<MonkeyHubController> ().FlashingShoes.SetActive (true);
					yield return new WaitForSeconds (3f);
					MonkeysMainObject.GetComponent<MonkeyHubController> ().FlashingShoes.SetActive (false);

					yield return new WaitForSeconds (2f);
			
			MainUIManager.Instance.inventoryController.ResetInventory (2, 3);
					MainUIManager.Instance.inventoryController.Activate ();
					yield return new WaitForSeconds (1f);

					MainUIManager.Instance.inventoryController.PopulateAt (GameObject.FindObjectOfType<MonkeyHubController> ().FlashingShoesImage, 2);
		} else if (MainUIManager.Instance.decisionUiController.SelectedItem == 2) {
					MonkeysMainObject.GetComponent<MonkeyHubController> ().ShiningHat.SetActive (true);
					yield return new WaitForSeconds (3f);
					MonkeysMainObject.GetComponent<MonkeyHubController> ().ShiningHat.SetActive (false);

			yield return new WaitForSeconds (2f);
						
			//MainUIManager.Instance.inventoryController.ResetInventory (2, 3);
					MainUIManager.Instance.inventoryController.Activate ();
					yield return new WaitForSeconds (1f);
					MainUIManager.Instance.inventoryController.PopulateAt (GameObject.FindObjectOfType<MonkeyHubController> ().ShinyHatImage, 2);
				}

				yield return new WaitForSeconds (2f);
				Player.dialogController.PopDialogue ("شكرًا!");

			yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
	

				Player.dialogController.UnPopDialogue ();
	

				MainUIManager.Instance.loadingUiController.Activate ();
				operation = Application.LoadLevelAsync ("TigerCave");
				yield return new WaitUntil (()=>(operation.isDone == true));
				MainUIManager.Instance.loadingUiController.DeActivate ();
				MainUIManager.Instance.hudController.gameObject.SetActive (true);
				yield return new WaitForSeconds (1f);

				Player = GameObject.FindObjectOfType<KatkootiController> ();
				Tiger = GameObject.FindObjectOfType<TigerController> ();

				GameManager.Instance.ChickSongPowerValue = 1;

				yield return new WaitForSeconds (0.5f);

				GameObject.FindObjectOfType<TigerSceneController> ().TigerGlow.SetActive (true);
				MainUIManager.Instance.decisionUiController.PopDialogueIcon (GameObject.FindObjectOfType<TigerSceneController>().TigerBubblePosition);
				yield return new WaitForSeconds (0.35f);
				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 255);
				yield return new WaitUntil (() => (MainUIManager.Instance.decisionUiController.proceedStatus == true));
				GameObject.FindGameObjectWithTag ("Bubble").GetComponent<Image> ().color = new Color32 (255, 255, 255, 0);
				MainUIManager.Instance.decisionUiController.UnPopDialogueIcon ();

		GameObject.FindObjectOfType<TigerSceneController> ().TigerGlow.SetActive (false);
				Player.animationController.PlayAnimation ("ChickSong");
				//        Player.dialogController.UnPopDialogue ();
				MainUIManager.Instance.StartCoroutine (MainUIManager.Instance.hudController.StarEffect ());
				GameManager.Instance.ChickSongPowerValue = 0;
				GameManager.Instance.InstantiateObject ("ConstructionParticles",GameObject.FindObjectOfType<TigerSceneController>().SongPowerStarEffectPosition.transform.position);
				SoundManager.Instance.PlaySoundOneShot ("SongBarPowerDown");
				yield return new WaitForSeconds (Player.animationController.GetCurrentPlayingClipLength ());
		      
				Tiger.MakeIdle(PlayerPrefs.GetInt("ItemSelected"));
				Player.MakeIdle ();

				yield return new WaitForSeconds (1f);
				Player.dialogController.PopDialogue ("تفضل يا ملك!");

				Player.StartTalking2 ();
				yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
				Player.dialogController.UnPopDialogue ();
			
				
				Tiger.StartTalking (PlayerPrefs.GetInt("ItemSelected"));
				Tiger.dialogController.PopDialogue ("هذه الأشياء هي ما أريده تمامًا");
				yield return new WaitForSeconds (SoundManager.Instance.PlayTigerCaveDialogue());
				Tiger.dialogController.UnPopDialogue ();
				Tiger.MakeIdle (PlayerPrefs.GetInt("ItemSelected"));
			

//				Player.MakeIdle ();
//
//				yield return new WaitForSeconds (1f);
//				Player.dialogController.PopDialogue ("تبدو هذه الأشياء لطيفة!");
//
//				Player.StartTalking2 ();
//				yield return new WaitForSeconds (1f);
				MainUIManager.Instance.hudController.gameObject.SetActive (true);
				MainUIManager.Instance.hudController.EnableUIMapGlow ();

			
				PlayCurrentState ();
	}

}
