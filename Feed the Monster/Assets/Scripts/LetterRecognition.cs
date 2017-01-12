using UnityEngine;
using System.Collections;
using System.Xml;
using System.Xml.Serialization;

[System.Serializable]
public class LetterRecognition  {

	[XmlAttribute("Letter")]
	public string Letter;

	[XmlAttribute("Variants")]
	public string Variants;

	public LetterRecognition(string letter, string variants)
	{
		Letter = letter;
		Variants = variants;
	}
}
