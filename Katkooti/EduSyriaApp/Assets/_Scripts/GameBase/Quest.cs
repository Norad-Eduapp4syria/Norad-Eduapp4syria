using UnityEngine;
using System.Collections;
[System.Serializable]
public class Quest  {

	public enum QUEST_LOCATION{
		NONE,
		JUNGLE_RUN,
		HARE_RACE
	}
	public enum JUNGLE_RUN
	{
		NONE,
		LAND,
		LAND_AND_WATER,
		LAND_AND_AIR,
		LAND_WATER_AIR
	}

	public QUEST_LOCATION quest_location = QUEST_LOCATION.NONE;
	public JUNGLE_RUN allowedPath_JungleRun = JUNGLE_RUN.NONE;

	public bool isImune = true;

	public LearningItem [] LearningItemsInQuest;
	public QuestItem [] questItems;

	private bool questIsOver=false;
	private int totalLettersToSpawn = 0;
	private int totalCollectableToSpawn = 0;

	private int learningItemCounter = 0;
	private int questItemCounter = 0;



	private bool AllLetterCollected = false;
	private bool AllQuestItemCollected = false;



	public bool LetterCollected{
		get{
			return AllLetterCollected;
		}
		set{
			AllLetterCollected = value;
		}
	}

	public bool QuestItemCollected{
		get{
			return AllQuestItemCollected;
		}
		set{
			AllQuestItemCollected = value;
		}
	}
	public QuestItem getNextQuestItem(){
		
		return questItems[questItemCounter];
	}
	public LearningItem getNextLearningItem(){

		return LearningItemsInQuest[learningItemCounter];
	}
	public bool isNextQuestItemAvailable(){
		if (questItemCounter < questItems.Length) {
			return true;
		} else {
			return false;
		}
	}
	public bool isNextLearningItemAvailable(){
		if (learningItemCounter < LearningItemsInQuest.Length) {
			return true;
		} else {
			return false;
		}
	}

	public void PlayerCollectLetter(){
		LearningItemsInQuest [learningItemCounter].counter++;
		if (LearningItemsInQuest [learningItemCounter].counter == LearningItemsInQuest [learningItemCounter].Maxfrequency) {
			if (learningItemCounter + 1 == LearningItemsInQuest.Length) {
				AllLetterCollected = true;
			}
			learningItemCounter = Mathf.Clamp(learningItemCounter+1,0,LearningItemsInQuest.Length-1);
		}
	}
	public void PlayerHitHurrdle(){
		if (!isImune) {
			AllLetterCollected = false;
			LearningItemsInQuest [learningItemCounter].counter--;
			if (LearningItemsInQuest [learningItemCounter].counter < 0) {
				LearningItemsInQuest [learningItemCounter].counter = 0;
				learningItemCounter--;
				learningItemCounter = Mathf.Clamp (learningItemCounter, 0, LearningItemsInQuest.Length-1);
			}
		}
	}

	public void PlayerCollectQuestItem(){
		questItems [questItemCounter].counter++;
		if (questItems [questItemCounter].counter == questItems [questItemCounter].Maxfrequency) {
			if (questItemCounter + 1 == questItems.Length) {
				AllQuestItemCollected = true;
			}
			questItemCounter = Mathf.Clamp(questItemCounter+1,0,questItems.Length-1);
		}
	}

	public int getTotalLearningObjects(){
		int val = 0;
		foreach (LearningItem l in LearningItemsInQuest) {
			val += l.Maxfrequency;
		}
		return val;
	}
	public int getTotalQuestObjects(){
		int val = 0;
		foreach (QuestItem l in questItems) {
			val += l.Maxfrequency;
		}
		return val;
	}

}
