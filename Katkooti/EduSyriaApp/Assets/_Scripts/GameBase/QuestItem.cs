using UnityEngine;
using System.Collections;
[System.Serializable]
public class QuestItem  {


	public Quest.JUNGLE_RUN canSpawnState =  Quest.JUNGLE_RUN.NONE;
	public GameObject questItem;
	public int Maxfrequency;
	public int counter=0;


}