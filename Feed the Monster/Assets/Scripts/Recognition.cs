using UnityEngine;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System;
using System.Collections;

[System.Serializable]
public class Recognition  {

	[XmlAttribute("Letter")]
	public string Letter;
	[XmlAttribute("Variants")]
	public string Variants;
}
