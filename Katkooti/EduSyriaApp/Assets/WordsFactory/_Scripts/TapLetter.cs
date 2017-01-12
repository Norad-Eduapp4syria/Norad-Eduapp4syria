using UnityEngine;
using System.Collections;

public class TapLetter : MonoBehaviour {

	public GameObject[] Monkey;
	public Animator Tank,KK,Wheel;
	public bool movetobucket,movetomonkeyhand;
	public GameObject bucket,monkeyhand;
	private WFManager WM;
	private UIManager UM;

	// Use this for initialization
	void Start () {
		
		movetomonkeyhand = false;
		movetobucket = false;
		Monkey = GameObject.FindGameObjectsWithTag ("Monkey");
		Tank  = GameObject.FindGameObjectWithTag("Tank").GetComponent<Animator>();
		Wheel  = GameObject.FindGameObjectWithTag("wheel").GetComponent<Animator>();
		KK  = GameObject.FindGameObjectWithTag("kk").GetComponent<Animator>();
		bucket = GameObject.FindGameObjectWithTag ("MergeLetter");
		monkeyhand = GameObject.FindGameObjectWithTag ("Monkey");
		WM = GameObject.FindObjectOfType<WFManager> ().GetComponent<WFManager> ();
		UM = GameObject.FindObjectOfType<UIManager> ().GetComponent<UIManager> ();
	}

	void Update()
	{
		if(movetobucket)
		{
			this.gameObject.GetComponent<Rigidbody2D> ().constraints = RigidbodyConstraints2D.None;
			this.transform.position = Vector3.Lerp (this.transform.position,bucket.transform.position,4*Time.deltaTime);

		}
		if (movetomonkeyhand) {

			this.gameObject.GetComponent<Rigidbody2D> ().constraints = RigidbodyConstraints2D.None;
			this.transform.position = Vector3.Lerp (this.transform.position,monkeyhand.transform.position,6*Time.deltaTime);

		}
	}


	void OnMouseDown(){
			this.gameObject.transform.GetChild (1).gameObject.SetActive (true);
			SelectLetter (this.gameObject);
	}

	public void SelectLetter(GameObject letter)
	{
		if (!letter.gameObject.CompareTag ("Selected")) {
			letter.gameObject.tag = "Selected";
		
		}
	}

	public void RejectLetter(GameObject letter)
	{
		letter.tag = "Rejected";
	}

	void OnTriggerEnter2D(Collider2D other)
	{
		if (other.gameObject.CompareTag ("DestroyLetter")) {

			Destroy (this.transform.parent.transform.parent.gameObject);

		} else if(other.gameObject.CompareTag ("MergeLetter"))
		{
			SoundManager.Instance.PlaySoundOneShot ("Monkey");
			WM.CompletionEffectSpawn ();
			this.gameObject.transform.GetChild (1).gameObject.SetActive (false);
			Wheel.SetTrigger ("rotate");
			Tank.SetTrigger ("tank");
			foreach (GameObject monk in Monkey) {
				monk.GetComponent<Animator>().SetTrigger ("happy");
			}
			KK.SetTrigger ("happy");
			WM.EnableHandpointer ();
			SoundManager.Instance.PlaySoundOneShot ("MonkeyMedal");
			UM.Word = this.gameObject.transform.GetChild(0).gameObject.GetComponent<TextMesh> ().text;
			WM.counter++;

			Destroy (this.gameObject);

		}else if(other.gameObject.CompareTag ("Decision Bucket") && this.gameObject.CompareTag ("Selected")){
			if (WM.MatchLetter(this.gameObject)) 
			{
				// Right Letter Selected
				this.GetComponent<SpriteRenderer> ().color = Color.green;
				GameObject monk = other.transform.parent.gameObject;
				monk.GetComponent<Animator>().SetTrigger ("letter");
				this.gameObject.GetComponent<CircleCollider2D> ().isTrigger = true;
				this.gameObject.GetComponent<Rigidbody2D> ().constraints = RigidbodyConstraints2D.FreezePositionX;
				this.gameObject.GetComponent<Rigidbody2D> ().isKinematic = false;
				monkeyhand = other.gameObject.transform.parent.gameObject.transform.GetChild(1).gameObject;
				this.transform.parent = null;
				SoundManager.Instance.PlaySoundOneShot ("LetterCollect");

			}
			else {
				// Wrong Letter Selected
				foreach (GameObject monk in Monkey) {
					monk.GetComponent<Animator>().SetTrigger ("sad");
				}
				WM.EnableHandpointer ();
				this.GetComponent<SpriteRenderer> ().color = Color.red;
				this.gameObject.tag = "Letter";
				this.gameObject.transform.GetChild (1).gameObject.SetActive (false);
				SoundManager.Instance.PlaySoundOneShot ("WrongLetter");

			}
		}else if(other.gameObject.CompareTag ("Hint")){
			if(this.transform.GetChild(0).GetComponent<TextMesh> ().text.Equals (WM.CurrentWord[WM.counter].ToString()))
			{
				this.gameObject.transform.GetChild (1).gameObject.SetActive (true);
			}
		}

	}



}
