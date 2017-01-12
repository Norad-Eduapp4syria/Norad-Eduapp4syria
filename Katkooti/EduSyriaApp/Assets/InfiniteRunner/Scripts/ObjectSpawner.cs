using UnityEngine;
using System.Collections;
using ArabicSupport;
public class ObjectSpawner : MonoBehaviour {

	// Use this for initialization
	public MovingObject [] movingObject;
	public float minRefreshTime;
	public float maxReFreshTime;
	public float StatingTime;
	protected bool SpawnAgain=false;

	public bool ObjectSpawned=false;
	protected MovingObject temp=null;
	protected void OnEnable(){
		StartCoroutine("StartSpawning");
	}
	public void OnDisable(){
		SpawnAgain = false;
	}

	// Update is called once per frame
	public void Update () {
		if (SpawnAgain) {
			SpawnAgain=false;
			StartCoroutine("SpawnObject");
		}
	}

	protected virtual IEnumerator SpawnObject(){
		int rand = Random.Range (0, movingObject.Length);
		temp = Instantiate (movingObject[rand],this.transform.position,Quaternion.identity) as MovingObject;
		temp.OnDestroyObject += ObjectDestoyed ;
		ObjectSpawned = true;
		PowerUp p = temp.gameObject.GetComponent<PowerUp> ();
		if (temp.gameObject.name.Contains ("Rabit")) {
			Destroy (temp.gameObject);
		}
		if (p != null) {
			p.Text.text = ArabicFixer.Fix(GameManager.Instance.CurrentQuest.getNextLearningItem ().letter,true,true);
			p.SoundName = GameManager.Instance.CurrentQuest.getNextLearningItem ().soundName;
		}
		yield return new WaitForSeconds (Random.Range(minRefreshTime,maxReFreshTime+1)); 
		SpawnAgain=true;
	}

	public IEnumerator StartSpawning(){
		yield return new WaitForSeconds(StatingTime);
		SpawnAgain = true;
	}

	public void ObjectDestoyed(){
		ObjectSpawned = false;
	}
}
