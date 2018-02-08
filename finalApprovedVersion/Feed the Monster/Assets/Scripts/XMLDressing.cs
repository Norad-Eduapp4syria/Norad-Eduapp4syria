using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System;

[XmlRoot("XMLDressing")]
public class XMLDressing {
	[XmlArray("categories")]
	[XmlArrayItem("category")]
	public DressingCategoriesTO[] cat;


	public IEnumerator LoadFromResources(string path){
		TextAsset xmlDataFile = new TextAsset ();
		xmlDataFile = (TextAsset)Resources.Load (path, typeof(TextAsset));
		MemoryStream ms = new MemoryStream (xmlDataFile.bytes);

		XmlTextReader reader;
		yield return reader = new XmlTextReader  (ms);

		SerializeLevelFromXML (path ,reader);
		yield return true;
	}

	private void SerializeLevelFromXML(string path, XmlReader reader)
	{
		var serializer = new XmlSerializer(typeof(XMLDressing));
		XMLDressing xmlDressing = serializer.Deserialize(reader) as XMLDressing;

		Dictionary<int, DressingCategoriesTO> categories = new Dictionary<int, DressingCategoriesTO>();

		foreach (DressingCategoriesTO category in xmlDressing.cat) {
			if(!categories.ContainsKey(category.id)) {
				categories.Add (category.id, category);
			}
		}
		DressingController.Instance.Dressing = categories;

	}
}
