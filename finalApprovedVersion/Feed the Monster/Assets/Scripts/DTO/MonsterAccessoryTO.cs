using System;
using UnityEngine;
	
[Serializable]
public class MonsterAccessoryTO
{
	
	public int id;
//	public Vector2 pos; 
//	public Vector2 rot; 



	public static MonsterAccessoryTO create(DressingItemTO item){
		MonsterAccessoryTO i = new MonsterAccessoryTO();
		i.id = item.id;
//		i.pos = Vector2.zero;
//		i.rot = Vector2.zero;
		return i;
	}

}