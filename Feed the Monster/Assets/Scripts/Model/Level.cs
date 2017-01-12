using UnityEngine;
using System.Collections;


[System.Serializable]
public class Level : ScriptableObject {
	//public Monster[] FriendsAvailableToCollectWhenFinish;

	public int levelId  { get; set;}
	public Monster CollectableMonster;
	public MonsterInputType monsterInputType;

	public int lettersGroup;

	public int hideCallout;
	public bool shuffleSegment;

	public float SegmentTime;

	public Color ActiveTintColor;

	public Color StoneLetterMainColorDefault;
	public Color StoneLetterMainColorSelected;

	public Color StoneLetterMainOutlineColorDefault;
	public Color StoneLetterMainOutlineColorSelected;

	public Segment[] Segments;

	public void LoadTemplete(Level templete)
	{
		ActiveTintColor = templete.ActiveTintColor;
		StoneLetterMainColorDefault = templete.StoneLetterMainColorDefault;
		StoneLetterMainColorSelected = templete.StoneLetterMainColorSelected;
		StoneLetterMainOutlineColorDefault = templete.StoneLetterMainOutlineColorDefault;
		StoneLetterMainOutlineColorSelected = templete.StoneLetterMainOutlineColorSelected;
	}



	public void ShuffleSegments()
	{
		System.Random rng = new System.Random ();

		int n = Segments.Length;
		while (n > 1) 
		{
			int k = rng.Next(n--);
			Segment temp = Segments[n];
			Segments[n] = Segments[k];
			Segments[k] = temp;
		}
	}

}
