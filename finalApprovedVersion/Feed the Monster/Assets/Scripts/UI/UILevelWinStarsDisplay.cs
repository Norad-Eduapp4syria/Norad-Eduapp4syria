using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class UILevelWinStarsDisplay : MonoBehaviour {

	public Image StarImage1;
	public Image StarImage2;
	public Image StarImage3;

	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void Update () {

	}

	void OnDisable(){

	}

	void OnEnable(){
		float[] delays = new float[]{ .6f, .75f, 1f };
		for (int i = 0; i < transform.childCount; i++) {
			StartCoroutine (PopInStar (transform.GetChild(i), delays[i]));
		}

		Color fullColor = new Color (1, 1, 1, 1);
		Color emptyColor = new Color (0.0f, 0.0f, 0.0f, 0.7f);

		int stars = GameplayController.Instance.CurrentLevelStars;

		StarImage1.color = stars >= 1 ? fullColor : emptyColor;
		StarImage2.color = stars >= 2 ? fullColor : emptyColor;
		StarImage3.color = stars >= 3 ? fullColor : emptyColor;
	}

	IEnumerator PopInStar(Transform transform, float delay = 0){
		
		transform.localScale = new Vector3 (0, 0, 0);

		yield return new WaitForSeconds (delay);

		float[] scales = new float[] { 0f, 1.5f, 1f };

		foreach (float destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += Time.deltaTime * 8)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}
	}
}
