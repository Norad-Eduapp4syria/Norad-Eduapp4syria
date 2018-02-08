using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Serialization;

[System.Serializable]
public class DressingItemTO {

	[XmlAttribute("id")]
	public int id;

	[XmlAttribute("openInLevel")]
	public int openInLevel;

}
