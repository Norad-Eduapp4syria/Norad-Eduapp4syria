using UnityEngine;
using System.Collections;

public class MonsterPosition : MonoBehaviour {

	public Vector2 EndScreen = new Vector2 (0f, 0f);
	public Vector2 NewMonsterScreen = new Vector2 (0f, 0f);
	public Vector2 GameScreen = new Vector2 (0f, 0f);
	public Vector2 MiniGameScreen = new Vector2 (0f, 0f);


	bool needUpdate = false;
	Vector2 toPos;

	// Update is called once per frame
	void Update () {

		if (needUpdate == true) {
			MoveTo();
		}
	}





	public void setNewMonsterPosition()
	{
		transform.position = NewMonsterScreen;
	}

	public void setEndPosition(bool inAnimated = true)
	{
		if (inAnimated) {
			toPos = EndScreen;
			needUpdate = true;
		} else {
			transform.position = EndScreen;
		}
	}

	public void setGamePosition()
	{
		transform.position = GameScreen;
	}

	public void setMiniGamePosition()
	{
		transform.position = MiniGameScreen;
	}

	void MoveTo()
	{
		transform.position = Vector2.MoveTowards (transform.position, toPos, Time.deltaTime / 2);

		float dis = Vector2.Distance (transform.position, toPos);

		if (dis < 0.001f) {
			needUpdate = false;
		}
	}


}
