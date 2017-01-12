using UnityEngine;
using System.Collections;


	public class Parallax : ObjectBounds
	{

		public bool EnableRandomParallexing;
		public float ParallaxSpeed=0;
		public GameObject _clone;
		protected Vector3 _movement;
		public Vector3 _initialPosition;
		private float _width;
		private bool isChanging = false;
		public int currentPatching=0;

		bool ChangePatch=false;
		public Sprite []loopingSprite;
		public Sprite []transitionSprite;
		public int temp;



	   void Start()
		{
			InvokeRepeating ("ChangePatchFunction", 10, 20);
			_width = GetBounds().size.x;
			_initialPosition=transform.position	;	

			_clone = (GameObject)Instantiate(gameObject, new Vector3(transform.position.x+_width, transform.position.y, transform.position.z), transform.rotation);

			Parallax parallaxComponent = _clone.GetComponent<Parallax>();
			Destroy(parallaxComponent);		
		}


		public void ResetAllPosition(){
			transform.position = _initialPosition;
		_clone.transform.position = new Vector3 (_initialPosition.x + _width, transform.position.y, transform.position.z);
		}
		/// <summary>
		/// On Update, we move the object and its clone
		/// </summary>
		float delay=0;

		public void OnSetEnable(){
		_clone.GetComponent<SpriteRenderer> ().sprite =loopingSprite [0];
		this.GetComponent<SpriteRenderer> ().sprite = loopingSprite [0];
		currentPatching = 0;
		temp = 0;
		delay = 2;
		}


	    void Update()
		{		
			if (transform.position.x +_width < _initialPosition.x)
			{
			
			if (EnableRandomParallexing ) {
				if (isChanging) {
					this.GetComponent<SpriteRenderer> ().sprite = transitionSprite [currentPatching];
					_clone.GetComponent<SpriteRenderer> ().sprite = loopingSprite [temp];
					isChanging = false;
					currentPatching = temp;
				} else {
					this.GetComponent<SpriteRenderer> ().sprite = loopingSprite [currentPatching];
					_clone.GetComponent<SpriteRenderer> ().sprite = loopingSprite [currentPatching];
				}
				
				if(ChangePatch){
					temp = Random.Range (0, loopingSprite.Length);
					if(temp!=currentPatching){
					this.GetComponent<SpriteRenderer> ().sprite = loopingSprite [currentPatching];
					_clone.GetComponent<SpriteRenderer> ().sprite = transitionSprite [currentPatching];
					ChangePatch = false;
					isChanging = true;
					}
				}

			}

			transform.Translate (Vector3.right * _width);
			_clone.transform.Translate (Vector3.right * _width);

		
				
			}

		_movement = Vector3.left * (ParallaxSpeed / 10) *Time.deltaTime;
		_clone.transform.Translate(_movement);
		transform.Translate(_movement);

		if (_clone.transform.position.x == transform.position.x + _width) {
			
		} else {
			_clone.transform.position = new Vector3 (transform.position.x + _width, transform.position.y, transform.position.z);
		}


	}



	void ChangePatchFunction(){
		ChangePatch = true;
	}

	public void DisableClone(){
		_clone.SetActive (false);
	}

	public void EnableClone(){
		
		_clone.SetActive (true);
		_clone.GetComponent<SpriteRenderer> ().sprite = loopingSprite [0];
		isChanging = false;
		currentPatching = 0;

	}

		
	}
