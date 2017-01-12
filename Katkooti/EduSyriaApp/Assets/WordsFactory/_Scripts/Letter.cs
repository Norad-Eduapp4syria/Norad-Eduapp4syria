using UnityEngine;
using System.Collections;
using ArabicSupport;

public class Letter : MonoBehaviour {

	public GameObject[] MainPath;
	public GameObject path;
	int count,count1,count2;
	public GameObject[] AcceptPath;
	public GameObject[] RejectedPath;
	float time = 0.2f;
	public string [] letterspool;
	public string thisletter;

	//private Rigidbody2D rb;
	public float force;
	public float SpeedLmit;
	//public GameObject Monkey;
	private WFManager WM;

	// Use this for initialization
	void Start () {
		WM = GameObject.FindObjectOfType<WFManager> ().GetComponent<WFManager> ();
		//Monkey = GameObject.FindGameObjectWithTag("Monkey");
		count = 0;
		count1 = 0;
		count2 = 0;
		//rb = this.transform.GetComponent<Rigidbody2D> ();
	//	GameObject waypoint=GameObject.FindGameObjectWithTag("WayPoint");

		int temprand = Random.Range(0,letterspool.Length-1);
		thisletter = letterspool [temprand];

		if (thisletter == WM.Word [WM.counter].ToString()) {
			thisletter = letterspool[temprand+1];
		}
		this.GetComponent<TextMesh> ().text = thisletter;

		path = MainPath[0];


	}

//	void OnMouseDown()
//	{
//		Debug.Log ("hahahahahahahahahaha");
//		if (!this.gameObject.CompareTag ("Rejected")) {
//			SelectLetter (this.gameObject);
//			GameObject[] OtherLetters = GameObject.FindGameObjectsWithTag ("Letter");
//			foreach (GameObject leter in OtherLetters) 
//			{
//				RejectLetter (leter.gameObject);
//			}
//		} 
//	
//	}


//	public void SelectLetter(GameObject letter)
//	{
//		if (!this.gameObject.CompareTag ("Selected")) {
//			letter.gameObject.tag = "Selected";
//			this.GetComponent<TextMesh> ().color = Color.red;
//			this.transform.localScale = Vector3.Lerp (this.transform.localScale, new Vector3 (this.transform.localScale.x + .5f, this.transform.localScale.y + .5f, this.transform.localScale.z + .5f), 0.3f);
//		}
//	}
//
//	public void RejectLetter(GameObject letter)
//	{
//		letter.gameObject.tag = "Rejected";
//	}

	void MoveToMainPath()
	{


			if(Mathf.Abs(Vector3.Distance(this.transform.position,path.transform.position)) <= 0.1f)
			{
				count++;
			count = Mathf.Clamp (count,0,MainPath.Length-1);
			path = MainPath [count];
			}

	}

//	void FixedUpdate () {
//
//	
//
//		rb.AddRelativeForce (new Vector2 (1f,0f) * force * Time.deltaTime,ForceMode2D.Impulse);
//
//		rb.velocity = Vector2.ClampMagnitude (rb.velocity, SpeedLmit);
//	}
//
//	void MoveToAcceptedPath()
//	{
//
//		if(Mathf.Abs(Vector3.Distance(this.transform.position,path.transform.position)) <= 0.1f)
//		{
//			count1++;
//			count1 = Mathf.Clamp (count1,0,AcceptPath.Length-1);
//			path = AcceptPath [count1];
//		}
//
//	}
//
//	void MoveToRejectedPath()
//	{
//		
//		if(Mathf.Abs(Vector3.Distance(this.transform.position,path.transform.position)) <= 0.1f)
//		{
//			count2++;
//			count2 = Mathf.Clamp (count2,0,RejectedPath.Length-1);
//			path = RejectedPath [count2];
//		}
//
//	}

//	public void DiscardLetter()
//	{
//		if (WM.MatchLetter(this.gameObject)) {
//			Debug.Log ("Matched and LostLife");
//			WM.LifeLost ();
//			WM.CheckLives ();
//
//		} else {
//			Debug.Log ("Not Matched and Discarded");
//			//WFManager.Instance.DestroyLetter ();
//			path= RejectedPath[0];
//			this.gameObject.tag = "Rejected";
//			//WFManager.Instance.Reset ();
//		}
//	}
//
//	public void AcceptLetter()
//	{
//		if (WM.MatchLetter(this.gameObject)) {
//			Debug.Log ("Matched and Accepted");
//			WM.counter++;
////			if (WFManager.Instance.counter >= WFManager.Instance.StringLength) {
////				
////	//			WFManager.Instance.LevelCleared ();
////				WFManager.Instance.ResetLevel ();
////			} else {
//				//WFManager.Instance.MoveLettertoBucket ();
//				path = AcceptPath[0];
//				this.gameObject.tag = "Accepted";
//			WM.Reset ();
////			}
//		} else {
//			Debug.Log ("Not Matched and Not Accepted");
//			WM.LifeLost ();
//			WM.CheckLives ();
//		}
//
//	}


//	void Update()
//	{
//		
////		if (this.gameObject.tag == "Letter") {
////			MoveToMainPath ();
////			this.gameObject.transform.position = Vector3.MoveTowards (this.transform.position, path.transform.position, 5f * Time.deltaTime);
////		}
////		else if(this.gameObject.tag == "Accepted")
////		{
////			MoveToAcceptedPath ();
////			this.gameObject.transform.position = Vector3.MoveTowards (this.transform.position, path.transform.position, 5f * Time.deltaTime);
////		}
////		else if(this.gameObject.tag == "Rejected")
////		{
////			MoveToRejectedPath ();
////			this.gameObject.transform.position = Vector3.MoveTowards (this.transform.position, path.transform.position, 5f * Time.deltaTime);
////		}
//	}


//	void OnTriggerEnter2D(Collider2D other)
//	{
//		if (other.gameObject.CompareTag ("DestroyLetter")) {
//			Debug.Log ("one");
//				Destroy (this.gameObject);
//	
//		} else if(other.gameObject.CompareTag ("MergeLetter"))
//		{
//				UIManager.Instance.Word = this.gameObject.GetComponent<TextMesh> ().text;
//				WFManager.Instance.counter++;
//				Destroy (this.gameObject);
//
//		}else if(other.gameObject.CompareTag ("Decision Bucket") && this.gameObject.CompareTag ("Selected")){
//			if ( WFManager.Instance.MatchLetter(this.gameObject)) 
//			{
//				Monkey.GetComponent<Animator> ().SetTrigger ("grabletter");
//				//this.gameObject.transform.parent.gameObject.GetComponent<Rigidbody2D> ().constraints = RigidbodyConstraints2D.FreezePositionX;
//				this.gameObject.GetComponent<Rigidbody2D> ().constraints = RigidbodyConstraints2D.FreezePositionX;
//				this.gameObject.GetComponent<CircleCollider2D> ().isTrigger = true;
//				//this.gameObject.transform.parent.gameObject.GetComponent<CircleCollider2D> ().isTrigger = true;
//			}
//			else {
//				this.GetComponent<TextMesh> ().color = Color.blue;
//				this.transform.localScale = Vector3.Lerp(this.transform.localScale,new Vector3 (this.transform.localScale.x - .5f, this.transform.localScale.y - .5f, this.transform.localScale.z - .5f),0.3f );
//				WFManager.Instance.LifeLost ();
//				WFManager.Instance.CheckLives ();
//
//			}
//		}else if(other.gameObject.CompareTag ("Hint")){
//			this.gameObject.tag = "Rejected";
//			if(this.GetComponent<TextMesh> ().text.Equals (WFManager.Instance.CurrentWord[WFManager.Instance.counter].ToString()))
//			{
//				//StartCoroutine ("ColorChanger");
//			}
//		}
//
//
//	}

//	IEnumerator ColorChanger()
//	{
//		while (true) {
//			this.GetComponent<TextMesh> ().color = Color.green;
//			yield return new WaitForSeconds (0.25f);
//			this.GetComponent<TextMesh> ().color = Color.blue;
//		}
//	}
}
