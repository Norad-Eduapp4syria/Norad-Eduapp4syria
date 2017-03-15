using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class SceneLoader : MonoBehaviour {

	[SerializeField] 
	[Range(1f,30f)]
	private float minimumTime = 5;

	[SerializeField] 
	private string scene;

	[SerializeField] 
	private Text loadingText; 


	bool loadScene = false;
	float time;

	// Use this for initialization
	void Start () {
		
	}

	void OnEnable()
	{
		time = 0;
	}


	// Update is called once per frame
	void Update () {
		if (loadScene == false) {
			loadScene = true; 

			loadingText.text = "Loading..."; 

			StartCoroutine(LoadNewScene()); 
		} 

		if (loadScene == true) { 
			loadingText.color = new Color(loadingText.color.r, loadingText.color.g, loadingText.color.b, Mathf.PingPong(Time.time, 1)); 

			time += Time.deltaTime;
		} 
	}



	// The coroutine runs on its own at the same time as Update() and takes an integer indicating which scene to load. 
	IEnumerator LoadNewScene() { 
		//		yield return new WaitForSeconds(waitTime); 

//		AsyncOperation async = Application.LoadLevelAsync(scene); 
		AsyncOperation async = UnityEngine.SceneManagement.SceneManager.LoadSceneAsync(scene);

		async.allowSceneActivation = false;

		while (!async.isDone && time < minimumTime) { 
			yield return null; 
		} 
		async.allowSceneActivation = true;
	} 
	

}
