using UnityEngine;
using System;
using System.Collections;
using System.Xml;
using System.Xml.Serialization;

[System.Serializable]
public class Stone {

	[XmlAttribute("spawnId")]
	public string spawnId;

	[XmlAttribute("bonusScore")]
	public string bonusScore;

	[XmlAttribute("size")]
	public int size;

	[XmlAttribute("delayIn")]
	public float delayIn;

	[XmlAttribute("delayRepet")]
	public float delayRepet;

	[XmlAttribute("speed")]
	public float speed;

	[XmlAttribute("loop")]
	public bool loop;

	[XmlText()]
	public string value;



	int[] _spawnIds;
	string _fixValue = null;

	public string FixValue
	{
		get
		{
			if (string.IsNullOrEmpty (_fixValue)) {
				_fixValue = RTL.Fix (value);
			}
			return _fixValue;
		}
	}


	public int[] spawnIds
	{
		get {
			if(_spawnIds == null)
			{
				if (spawnId != null) {
					string[] stringSplited = spawnId.Split (',');
					_spawnIds = new int[stringSplited.Length];

					for (int i = 0; i < stringSplited.Length; i++) {
						int num;
						if (int.TryParse (stringSplited [i], out num)) {
							_spawnIds [i] = num;
						}
					}
				} else {
					_spawnIds = new int[0];
				}
			}
			return _spawnIds;
		}
	}


	public bool isBooster() {
		if(Array.IndexOf(Booster.BoosterNames, value) != -1) {
			return true;
		} else if(value.ToLower().Equals("monsterBooster")){
			return true;
		}

		return	false;
	}



	public static Stone CreateBooster(Stone origStone)
	{
		Stone stone = new Stone();
		stone.spawnId = "";
		stone.value = BoosterController.letterName;
		stone.bonusScore = origStone.bonusScore;
		return stone;
	}




}
