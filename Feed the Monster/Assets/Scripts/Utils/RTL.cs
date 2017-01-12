using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class RTL {

	public static Dictionary<char, RTLLetter> letters;
	public static RTLLetterReaplce[] letterReaplace;

	public static char[] exceptions;
	public static char[] superExceptions;
	static char connector = 'ـ';

//	static char[] sss= {'َ','ً','ُ','ٌ','ِ','ٍ','ْ'};
	static string punctuation = "ًٌٍَُِّْ";

	public static string Fix(string text)
	{
		string newText = string.Empty;

		text = replaceLamAlef (text);

		for (int i = 0; i < text.Length; i++) {
			newText += replaceChar(text, i);
		}

		char[] charArray = newText.ToCharArray ();
		Array.Reverse (charArray);

		newText = new string (charArray);
		newText = newText.Replace(RTL.connector.ToString(), "");
		return newText;
	}

	static string replaceLamAlef(string text)
	{
		if (RTL.letterReaplace != null) {
			foreach (RTLLetterReaplce re in RTL.letterReaplace) {
				text = text.Replace (re.from, re.to);
			}
		}
		return text;
	}

	static char replaceChar (string str, int charIndex)
	{
		char l = str [charIndex];
		try {
			if (letters.ContainsKey (l)) {
				RTLLetter ltr = letters[l];

				bool connectToPrevious = ConnectToPrevious(str, charIndex);
				bool connectToNext = ConnectToNext(str, charIndex);
				if(connectToPrevious && connectToNext) {
					return ltr.m[0];
				} else if(connectToPrevious) {
					return ltr.l[0];
				} else if(connectToNext){
					return ltr.f[0];
				}
			}
		} catch (Exception e) {
			Debug.Log ("Error: " + e.Message);
		}
		return l;
	}

	static bool ConnectToPrevious(string text, int charIndex)
	{
		if (charIndex == 0) {
			return false;

		} else if (
			Array.IndexOf (RTL.exceptions, text [charIndex - 1]) != -1
			||
			Array.IndexOf (RTL.superExceptions, text [charIndex - 1]) != -1
		) {
			return false;
		} else if (
			(charIndex - 2) >= 0
			&&
			punctuation.IndexOf (text [charIndex - 1]) != -1
			&&
			(
				(Array.IndexOf (RTL.exceptions, text [charIndex - 2]) != -1)
				||	
				(Array.IndexOf (RTL.superExceptions, text [charIndex - 2]) != -1)
			)
		){
			return false;
		} else if(
			(charIndex - 3) >= 0
			&&
			punctuation.IndexOf (text [charIndex - 1]) != -1
			&&
			punctuation.IndexOf (text [charIndex - 2]) != -1
			&&
			(
				(Array.IndexOf (RTL.exceptions, text [charIndex - 3]) != -1)
				||
				(Array.IndexOf (RTL.superExceptions, text [charIndex - 3]) != -1)
			)
		) {
			return false;
		} 
		return true;
	}

	static bool ConnectToNext(string text, int charIndex)
	{
		if (charIndex == text.Length - 1) {
			return false;
		} else if (
			(
			    charIndex + 1 == text.Length - 1
			    &&
			    punctuation.IndexOf (text [charIndex + 1]) != -1
			)
			||
			(
			    charIndex + 2 == text.Length - 1
			    &&
			    punctuation.IndexOf (text [charIndex + 1]) != -1
			    &&
			    punctuation.IndexOf (text [charIndex + 2]) != -1
			)) { 
			return false;
		} else if (Array.IndexOf (RTL.exceptions, text [charIndex]) != -1 || Array.IndexOf (RTL.superExceptions, text [charIndex]) != -1) {
			return false;
		} else if (charIndex > 0 && Array.IndexOf (RTL.superExceptions, text [charIndex - 1]) != -1) {
			return false;
		} else if (
			(charIndex + 2) >= 0
			&&
			punctuation.IndexOf (text [charIndex + 1]) != -1
			&&
			(Array.IndexOf (RTL.superExceptions, text [charIndex + 2]) != -1)
		) {
			return false;
		} else if(
			(charIndex + 3) >= 0
			&&
			punctuation.IndexOf (text [charIndex + 1]) != -1
			&&
			punctuation.IndexOf (text [charIndex + 2]) != -1
			&&
			(Array.IndexOf (RTL.superExceptions, text [charIndex + 3]) != -1)
		) {
			return false;
		} 
		return true;
	}
}
