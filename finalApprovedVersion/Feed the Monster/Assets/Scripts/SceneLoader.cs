using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class SceneLoader : MonoBehaviour {

	[SerializeField]
	public string scene;

	AsyncOperation async = null;

/*
	[SerializeField] 
	private Text loadingText; 
*/

	[HideInInspector]
	public bool isActive = false;

	bool loadScene = false;

	// Use this for initialization
	void Start () {
		
	}

	void OnEnable()
	{
	}

	void OnDestroy()
	{
		SceneController.Instance.onReadyToHide ();
	}

	// Update is called once per frame
	void Update () {
		if (isActive == false) {
			return;
		}
		if (loadScene == false) {
			loadScene = true; 
			StartCoroutine(LoadNewScene()); 
		} 

	}


	// The coroutine runs on its own at the same time as Update() and takes an integer indicating which scene to load. 
	IEnumerator LoadNewScene() { 
		async = UnityEngine.SceneManagement.SceneManager.LoadSceneAsync(scene);
		async.allowSceneActivation = false;

		while (!async.isDone)
		{
			if (async.progress == 0.9f)
			{
				async.allowSceneActivation = true;
			}
			yield return null;
		}
		Destroy (this);
	} 
}
