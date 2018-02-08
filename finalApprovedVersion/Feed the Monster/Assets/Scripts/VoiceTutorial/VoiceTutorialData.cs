using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

[System.Serializable]
public class VoiceTutorialData : ScriptableObject
{
	[Range(0.5f, 5f)]
	public float DelayInterval = 0.5f;

	public Sprite MainImage;
	public AudioClip[] Clips;
	public Sprite[] BubbleImages;


}
