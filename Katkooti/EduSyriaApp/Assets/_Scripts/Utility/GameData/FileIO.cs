using UnityEngine;
using System.Collections;
using System.IO;
using System.Collections.Generic;

public class FileIO : MonoBehaviour {


	public delegate void LoadFileDelegate (bool isError,string fileContent);

	public IEnumerator LoadIntoPersistantDataPathFromLocalPath (string filename, GameManager.FileLoadedIntoPersistant fileLoaded)
	{
		string urlToRead = Helpers.formatLocalUrlToRead (filename);
		Debug.Log ("urlToRead" + urlToRead);
		
		WWW www = new WWW (urlToRead);
		
		yield return www;
		
		if (www.error == null) {
			Debug.Log ("www.text" + www.text);
			WriteIntoPersistantDataPathFromLocalPath (www.text, filename, fileLoaded);
		} else {
			Debug.Log ("PersistantPathERROR: " + www.error);
		}	
	}


	public bool CheckFileExistance (string filename)
	{
		string url;
		if (Application.isEditor) {
			url = Helpers.formatLocalUrlToWrite (filename);
		} else {
			url = Helpers.formatLocalPersistentUrlToWrite (filename);
		}
		
		bool success = false;
		
		if (File.Exists (url)) {
			Debug.Log ("~~~~~~~~File Exists : Check File Existance Function~~~~~~~~~" + filename);
			success = true;
		} else {
			Debug.Log ("~~~~~~~~File Does Not Exists : In Check File Existance Function~~~~~~~~~" + filename);
			success = false;
		}
		
		return success;
		
	}
	
	public void WriteIntoPersistantDataPathFromLocalPath (string dataString, string filename, GameManager.FileLoadedIntoPersistant fileLoaded)
	{
		string urlToWrite = Helpers.formatLocalPersistentUrlToWrite (filename);
		
		Debug.Log ("urlToWrite" + urlToWrite);
		if (File.Exists (urlToWrite)) {
			Debug.Log ("~~~~File Exists~~~~" + filename);
			File.WriteAllText (urlToWrite, dataString);
			
		} else {
			Debug.Log ("~~~~File Does Not Exists~~~~" + filename);
			StreamWriter sw = File.CreateText (urlToWrite);
			sw.WriteLine (dataString);
			//File.WriteAllText(urlToWrite,dataString);
			
			sw.Close ();
		}
		
		fileLoaded (filename);
		
	}
	
	public void WriteIntoPersistantDataPath (string dataString, string filename)
	{
		string urlToWrite;
		if (Application.isEditor) {
			urlToWrite = Helpers.formatLocalUrlToWrite (filename);
		} else {
			urlToWrite = Helpers.formatLocalPersistentUrlToWrite (filename);
		}
		
		//		Debug.Log("urlToWrite"+urlToWrite);
		if (File.Exists (urlToWrite)) {
			//			Debug.Log("~~~~File Exists~~~~"+filename);
			File.WriteAllText (urlToWrite, dataString);
			
		} else {
			Debug.Log ("~~~~File Does Not Exists~~~~" + filename);
			StreamWriter sw = File.CreateText (urlToWrite);
			sw.WriteLine (dataString);
			//File.WriteAllText(urlToWrite,dataString);
			
			sw.Close ();
		}
		
	}
	
	public IEnumerator CopyIntoAnotherFileOnPersistantDataPath (string fromFileName, string toFileName)
	{
		string urlToRead;
		//string urlToWrite;
		
		if (Application.isEditor) {
			urlToRead = Helpers.formatLocalUrlToRead (fromFileName);
			//urlToWrite=Helpers.formatLocalUrlToWrite(toFileName);
		} else {
			urlToRead = Helpers.formatLocalPersistentUrlToRead (fromFileName);
			//urlToWrite=Helpers.formatLocalPersistentUrlToWrite(toFileName);
		}
		
		WWW www = new WWW (urlToRead);
		
		yield return www;
		
		if (www.error == null) {
			//			Debug.Log("Coppying from "+fromFileName+" to "+toFileName+ www.text);
			//File.WriteAllText(urlToWrite,www.text);
			WriteIntoPersistantDataPath (www.text, toFileName);
		} else {
			Debug.Log ("Error While Copying file: " + www.error);
		}
		
		yield return null;
		
		
		
	}


	
	//Function to load file text from streaming assets
	public IEnumerator LoadFromFile (string fileName, bool isLocalPath, LoadFileDelegate fileDelegate)
	{
//		Debug.Log ("LoadFromFile");
		string filePath = "";
		if (isLocalPath) {
			filePath = Helpers.formatLocalUrlToRead (fileName);
		} else {
			filePath = Helpers.formatLocalPersistentUrlToRead (fileName);
		}
		
		WWW www = new WWW (filePath);
		
		yield return www;
		
		if (www.error == null) {
			Debug.Log ("JSON -->>" + www.text);
			fileDelegate (false, www.text);
		} else {
			Debug.Log ("filePathError: " + www.error);
			fileDelegate (true, www.error);
		}
		
		yield return null;
	}

}
