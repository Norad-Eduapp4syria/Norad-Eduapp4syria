using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Serialization;



[System.Serializable]
public class DressingCategoriesTO {

	[XmlAttribute("id")]
	public int id;


	[XmlAttribute("zOrder")]
	public int zOrder;


	[XmlArray("items")]
	[XmlArrayItem("item")]
	public DressingItemTO[] items;



}
