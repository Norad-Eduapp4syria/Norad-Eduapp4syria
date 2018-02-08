using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class CreateMemoryGameCouple : MonoBehaviour {

	[MenuItem("GameObject/FTM/MemoryGame/Create Memory card Couple")]
	static void CreateMemorycardCouple()
	{
		MemoryGameCouple c = new MemoryGameCouple ();
		AssetDatabase.CreateAsset (c, "Assets/Prefabs/MiniGames/MemoryGame/CardCouple.asset");
	}



}
