using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IAnalitics
{
	void init ();
	void StopSession();
	void StartSession();
	void TreckScreen(string screenName);
	void TreckEvent(string category, string action, string label, long value);
}
