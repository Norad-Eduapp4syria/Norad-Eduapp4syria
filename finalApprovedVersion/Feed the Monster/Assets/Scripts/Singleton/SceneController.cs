using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneController : MonoBehaviour {
	public static SceneController Instance;

	public GameObject MainObject;

	public string SceneToLoad = "GameScreen";


	Animator anim;

	void Awake () {
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (MainObject);
			anim = GetComponent<Animator> ();
			SingletonLoader.CheckSingleton();


		} else if (Instance != this) {
			Destroy (gameObject);
		}
	}



	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void init()
	{
		anim.SetBool ("IsActive", false);
	}


	public void LoadScene(string sceneName)
	{
		if (!string.IsNullOrEmpty (sceneName)) {
			this.SceneToLoad = sceneName;
			anim.SetBool ("IsActive", true);
		}
	}

	public void onReadyToLoad ()
	{
		DestroyNotNececeryObjects ();
		CreateSceneLoader ();
	}

	public void onReadyToHide ()
	{
		anim.SetBool ("IsActive", false);
	}

	void DestroyNotNececeryObjects()
	{
		Destroy(GameObject.Find ("Canvas"));
		Destroy(GameObject.Find ("Mini Game Canvas"));
		Destroy(GameObject.Find ("Background"));
		Destroy(GameObject.Find ("MonsterBar"));
	}

	void CreateSceneLoader()
	{
		GameObject go = new GameObject ("SceneLoader");
		SceneLoader sceneLoader = go.AddComponent<SceneLoader>();

		//		sceneLoader.minimumTime = 0;
		sceneLoader.scene = SceneToLoad;
		sceneLoader.isActive = true;
	}




}
