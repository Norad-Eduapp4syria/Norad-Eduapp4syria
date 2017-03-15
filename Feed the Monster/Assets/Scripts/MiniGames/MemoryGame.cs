using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MemoryGame : BaseMiniGame {

	public static MemoryGame Instance;

	[Range(0.2f,5f)]
	public float firstShowing = 2f;

	[Range(2f,20f)]
	public  float rotateSpeed = 1f;

	[Range(0.3f,5f)]
	public  float shakeTime = 1f;

	public Sprite[] CardTopSprites;

	public AudioClip CardFlipSFX;
	public AudioClip CardMatchSFX;
	public AudioClip CardNotMatchSFX;


	public Image Title;

	public MemoryGameCard[] cards;

	public List<MemoryGameCouple> CouplesGroup_1;
	public List<MemoryGameCouple> CouplesGroup_2;
	public List<MemoryGameCouple> CouplesGroup_3;
	public List<MemoryGameCouple> CouplesGroup_4;
	public List<MemoryGameCouple> CouplesGroup_5;
	public List<MemoryGameCouple> CouplesGroup_6;


	public GameObject FlipParticle;
	public GameObject MatchParticle;



	[HideInInspector]
	public bool isPause;

	MemoryGameCouple[] Couples;

	MemoryGameCard selectedCard;
	int readyCards = 0;
	int completedCards = 0; 
	bool updateCamera = false;
	int numOpen = 0;


	void Awake()
	{
		Instance = this;
	}


	// Use this for initialization
	void Start () {

	}

	void OnEnable()
	{
		StartMiniGame ();
//		initGame ();
		updateCamera = true;

		hideAllCards ();
		StartCoroutine(showAllCards());

		Analitics.Instance.treckScreen ("Memory Game - Profile: " + UsersController.Instance.CurrentProfileId);
	}


	void OnDisable(){
		CancelInvoke ();
		updateCamera = false;
		if (Camera.main != null) {
			Vector3 to = Camera.main.transform.position;
			to.y = 0;
			Camera.main.transform.position = to;
		}
	}


	// Update is called once per frame
	void Update () {
		if (updateCamera) {
			Vector3 to = Camera.main.transform.position;
			to.y = 1;
			Camera.main.transform.position = Vector3.Lerp (Camera.main.transform.position, to, Time.deltaTime * 3);
		}

		if (Camera.main.transform.position.y == 1) {
			updateCamera = false;
		}
	}


	void hideAllCards()
	{
		foreach (MemoryGameCard card in cards) {
			card.gameObject.SetActive (false);
		}

	}


	IEnumerator showAllCards()
	{
		yield return new WaitForSeconds (1.5f);

		UIPopupPanel ui = gameObject.GetComponent<UIPopupPanel>(); 

		if (Title != null) {
			ui.PopOutAny(Title.transform);
		}

		initGame ();

		foreach (MemoryGameCard card in cards) {
			yield return new WaitForSeconds (0.1f);
			card.gameObject.SetActive (true);
			ui.PopInAny(card.transform);
		}
//		initGame ();
	}


	void initGame()
	{
		int i;
		int[] Places = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

		Sprite topSprite = null;


		int rnd = Random.Range (0, CardTopSprites.Length);
		topSprite = CardTopSprites[rnd];

		UpdateLettersFroGroup ();

		ShuffleIntList (Places);
		ShuffleCoupleList (Couples);
		Queue placesQueue = new Queue();

		foreach (int place in Places) {
			placesQueue.Enqueue (place);
		}
		i = 0;

		while (placesQueue.Count > 0 && i < 30 ) {
			int place;
			if (Couples.Length > i) {
				MemoryGameCouple couple = Couples [i];

				place = (int)placesQueue.Dequeue ();
				MemoryGameCard card1 = cards [place];
//			card1.gameObject.SetActive (true);
				card1.init (couple, 1, firstShowing + (place * 0.2f), topSprite);

				place = (int)placesQueue.Dequeue ();
				MemoryGameCard card2 = cards [place];
//			card2.gameObject.SetActive (true);
				card2.init (couple, 2, firstShowing + (place * 0.2f), topSprite);
			}
			i++;
		}
		selectedCard = null;
		isPause = true;
		readyCards = 0;
		completedCards = 0;
		numOpen = 0;
	}

	public void onCardReady()
	{
		readyCards++;
		if (readyCards == cards.Length) {
			isPause = false;
			numOpen = 0;
		}
	}

	public void onCardOpen(MemoryGameCard card)
	{
		if (selectedCard == null) {
			selectedCard = card;
		} else {
			if (selectedCard.Couple.Equals (card.Couple)) {
				completedCards += 2;

				selectedCard.OnCorrect();
				card.OnCorrect ();

				if (AudioController.Instance != null) {
					AudioController.Instance.PlaySound (selectedCard.Couple.matchClip);
					AudioController.Instance.PlaySound (CardMatchSFX);
				}
			} else {
				selectedCard.OnWrong ();
				card.OnWrong ();
				if (AudioController.Instance != null) {
					AudioController.Instance.PlaySound (CardNotMatchSFX);
				}
			}
			selectedCard = null;
		}
		if (completedCards == cards.Length) {
			
			StartCoroutine(delayHideAllCards());
//			Invoke ("onCompleted" , 1);


		}
	}

	public void onCardOpening ()
	{
		numOpen++;
		if (numOpen == 2) {
			isPause = true;
		}
	}

	public void onCardClose ()
	{
		numOpen--;
		if (numOpen == 0) {
			isPause = false;
		}
	}

	IEnumerator delayHideAllCards()
	{
		yield return new WaitForSeconds (1.0f);

		UIPopupPanel ui = gameObject.GetComponent<UIPopupPanel>(); 
		foreach (MemoryGameCard card in cards) {
			yield return new WaitForSeconds (0.1f);

			ui.PopOutAny(card.transform);
		}
		yield return new WaitForSeconds (0.3f);
		onCompleted ();
	}

	void onCompleted() {

		animController.SetBool ("IsSad", false);
		MiniGameController.Instance.ResetEmotion ();
		EndMiniGame ();

		Analitics.Instance.treckScreen ("Memory Game Done - Profile: " + UsersController.Instance.CurrentProfileId);
	}

	void UpdateLettersFroGroup()
	{
		int currentGroup = 1;

		if (UserInfo.Instance != null) {
			currentGroup = UserInfo.Instance.GetLastLetterGroup ();
		}
		List<MemoryGameCouple> newList = new List<MemoryGameCouple>();

		if(currentGroup >= 1) {
			newList.AddRange (CouplesGroup_1);
		}
		if(currentGroup >= 2) {
			newList.AddRange (CouplesGroup_2);
		}
		if(currentGroup >= 3) {
			newList.AddRange (CouplesGroup_3);
		}
		if(currentGroup >= 4) {
			newList.AddRange (CouplesGroup_4);
		}
		if(currentGroup >= 5) {
			newList.AddRange (CouplesGroup_5);
		}
		if(currentGroup >= 6) {
			newList.AddRange (CouplesGroup_6);
		}
		Couples = newList.ToArray ();
	}

	public void ShuffleCoupleList(MemoryGameCouple[] list)
	{
		System.Random rng = new System.Random ();

		int n = list.Length;
		while (n > 1) 
		{
			int k = rng.Next(n--);
			MemoryGameCouple temp = list[n];
			list[n] = list[k];
			list[k] = temp;
		}
	}

	public void ShuffleIntList(int[] list)
	{
		System.Random rng = new System.Random ();

		int n = list.Length;
		while (n > 1) 
		{
			int k = rng.Next(n--);
			int temp = list[n];
			list[n] = list[k];
			list[k] = temp;
		}
	}

}
