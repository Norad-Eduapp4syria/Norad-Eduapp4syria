using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System;

[XmlRoot("XMLLetters")]
public class XMLLetters {

	[XmlArray("letters")]
	[XmlArrayItem("letter")]
	public RTLLetter[] letters;

	[XmlArray("exceptions")]
	[XmlArrayItem("l")]
	public string[] exceptions;


	[XmlArray("superExceptions")]
	[XmlArrayItem("l")]
	public string[] superExceptions;


	[XmlArray("reaplace")]
	[XmlArrayItem("letter")]
	public RTLLetterReaplce[] letterReaplace;





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
		Dictionary<char, RTLLetter> ltrs = new Dictionary<char, RTLLetter>();

		var serializer = new XmlSerializer(typeof(XMLLetters));
		XMLLetters xmlLevel = serializer.Deserialize(reader) as XMLLetters;

		foreach (RTLLetter ltr in xmlLevel.letters) {
			ltrs.Add (ltr.r[0], ltr);
		}
		RTL.letters = ltrs;
		RTL.letterReaplace = xmlLevel.letterReaplace;

		RTL.exceptions = new char[xmlLevel.exceptions.Length];
		for (int i = 0; i < xmlLevel.exceptions.Length; i++) {
			RTL.exceptions [i] = xmlLevel.exceptions [i] [0];
		}

		RTL.superExceptions = new char[xmlLevel.superExceptions.Length];
		for (int i = 0; i < xmlLevel.superExceptions.Length; i++) {
			RTL.superExceptions [i] = xmlLevel.superExceptions [i] [0];
		}


	}
}
