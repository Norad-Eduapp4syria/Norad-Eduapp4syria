using UnityEngine;
using System.Collections;
using System.Security.Cryptography;
using System.Text;
using System.Collections.Generic;
using System.IO;
using System;

public static class Helpers
{
	
	//FileLoadedIntoPersistant _fileLoaded;
	public static string AddQuotes(string aString)
	{
		return "\"" + aString + "\"";
	}
	
	//For Writing to IOS, it takes url without "file://"
	public static string formatLocalPersistentUrlToWrite(string filename)
	{
		string url;
		if( Application.platform == RuntimePlatform.Android )
		{
			url= Application.persistentDataPath+"/"+filename;
		}
		else if( Application.platform == RuntimePlatform.IPhonePlayer )
		{
			url= Application.persistentDataPath+"/"+filename;
		}
		else
		{
			url= "file://" +Application.persistentDataPath+"/"+filename;
		}
		return url;
	}
	
	//For Reading from IOS,it takes url with "file://"
	public static string formatLocalPersistentUrlToRead(string filename)
	{
		string url;
		if(Application.platform==RuntimePlatform.Android)
		{
			url = "file://" + Application.persistentDataPath + "/"+filename;
		}
		else if(Application.platform==RuntimePlatform.IPhonePlayer)
		{
			url= "file://" +Application.persistentDataPath+"/"+filename;
		}
		else
		{
			url= "file://" +Application.streamingAssetsPath+"/"+filename;
		}
		Debug.Log("formatLocalPersistentUrlToRead=="+url);
		return url;
	}
	
	//For Testing in editor, For reading it takes url with "file://"
	public static string formatLocalUrlToRead(string filename)
	{
		string url;
		
		if(Application.platform==RuntimePlatform.Android)
		{
			url = "jar:file://" + Application.dataPath + "!/assets/"+filename;
		}
		else if(Application.platform==RuntimePlatform.IPhonePlayer)
		{
			url= "file://" +Application.streamingAssetsPath+"/"+filename;
		}
		else
		{
			url = "file://" +Application.streamingAssetsPath+"/"+filename;
		}
				Debug.Log("formatLocalUrlToRead=="+url);
		return url;
	}
	//For Testing in Editor, It takes url without the "file://"
	public static string formatLocalUrlToWrite(string filename)
	{
		string url;
		
		if(Application.platform==RuntimePlatform.Android)
		{
			url = "jar:file://" + Application.dataPath + "!/assets/"+filename;
		}
		else
		{
			url = Application.streamingAssetsPath+"/"+filename;
		}
		//		Debug.Log("formatLocalUrlToWrite=="+url);
		return url;
	}
	
	
	public static void Shuffle<T>(this IList<T> list)  
	{  
		System.Random rng = new System.Random();  
		int n = list.Count;  
		while (n > 1) {  
			n--;  
			int k = rng.Next(n + 1);  
			T value = list[k];  
			list[k] = list[n];  
			list[n] = value;  
		}  
	}

	public static List<int> GenerateRandomNumber(int totalNumbers)
	{
		List<int> randomNumbers = new List<int> ();
		int randNo;
		//for (int i=0; i<totalNumbers; i++) {
		while(randomNumbers.Count!=totalNumbers){
			randNo =UnityEngine.Random.Range (1, totalNumbers + 1);
			if (!randomNumbers.Exists (n=>n == randNo)) {
				randomNumbers.Add (randNo);
//								Debug.Log(randNo);
			}
		}
		return randomNumbers;
	}

	public static float ClampAngle (float angle, float min, float max)
	{
		if (angle < -360F)
			angle += 360F;
		if (angle > 360F)
			angle -= 360F;
		return Mathf.Clamp (angle, min, max);
	}
	
	
	public static string Encrypt (string toEncrypt)
	{
		byte[] keyArray = UTF8Encoding.UTF8.GetBytes ("12345678901234567890123456789012");
		// 256-AES key
		byte[] toEncryptArray = UTF8Encoding.UTF8.GetBytes (toEncrypt);
		RijndaelManaged rDel = new RijndaelManaged ();
		rDel.Key = keyArray;
		rDel.Mode = CipherMode.ECB;
		// http://msdn.microsoft.com/en-us/library/system.security.cryptography.ciphermode.aspx
		rDel.Padding = PaddingMode.PKCS7;
		// better lang support
		ICryptoTransform cTransform = rDel.CreateEncryptor ();
		byte[] resultArray = cTransform.TransformFinalBlock (toEncryptArray, 0, toEncryptArray.Length);
		return Convert.ToBase64String (resultArray, 0, resultArray.Length);
	}
	
	public static string Decrypt (string toDecrypt)
	{
		byte[] keyArray = UTF8Encoding.UTF8.GetBytes ("12345678901234567890123456789012");
		// AES-256 key
		byte[] toEncryptArray = Convert.FromBase64String (toDecrypt);
		RijndaelManaged rDel = new RijndaelManaged ();
		rDel.Key = keyArray;
		rDel.Mode = CipherMode.ECB;
		// http://msdn.microsoft.com/en-us/library/system.security.cryptography.ciphermode.aspx
		rDel.Padding = PaddingMode.PKCS7;
		// better lang support
		ICryptoTransform cTransform = rDel.CreateDecryptor ();
		byte[] resultArray = cTransform.TransformFinalBlock (toEncryptArray, 0, toEncryptArray.Length);
		return UTF8Encoding.UTF8.GetString (resultArray);
	}
	
	public static DateTime UnixTimeStampToDateTime( double unixTimeStamp )
	{
		// Unix timestamp is seconds past epoch
		System.DateTime dtDateTime = new DateTime(1970,1,1,0,0,0,0);
		dtDateTime = dtDateTime.AddSeconds( unixTimeStamp ).ToLocalTime();
		return dtDateTime;
	}
	
	public static int Compute2DAngle(Vector3 toObj, Vector3 fromObj)
	{
		float rise = (toObj.y - fromObj.y);
		float run = (toObj.x - fromObj.x);
		
		float radians = Mathf.Atan(Mathf.Abs(rise / run));
		
		int angle = (int) (Mathf.Rad2Deg * radians);
		
		switch(toObj.y > fromObj.y)
		{
		case true:
			if(toObj.x > fromObj.x) 					//first Quadrant
				angle = 90 - angle;
			else 										//fourth quadrant
				angle = 270 + angle;
			break;
		case false:
			if(toObj.x > fromObj.x) 					//second Quadrant
				angle = 90 + angle;
			else 										//third Quadrant
				angle = 180 + (90 - angle);
			break;
		}
		
		return angle;
	}



	public static T[] CombineArrayExcludingCommon<T> (T[] arrayOne, T[] arrayTwo)
	{
		List<T> uniqueList = new List<T> ();
		T anItem;
		int length = arrayOne.Length;
		for (int i = 0; i < length; i++) {
			anItem = arrayOne [i];
			T match = uniqueList.Find (str => str.Equals (anItem));
			if (match == null || match.Equals (""))
				uniqueList.Add (match);
		}
		length = arrayTwo.Length;
		for (int i = 0; i < length; i++) {
			anItem = arrayTwo [i];
			T match = uniqueList.Find (str => str.Equals (anItem));
			if (match == null || match.Equals (""))
				uniqueList.Add (match);
		}
		return uniqueList.ToArray ();
	}
}
