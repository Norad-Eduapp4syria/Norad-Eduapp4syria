using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DefaultAnalitics : MonoBehaviour, IAnalitics {

	GoogleAnalyticsV4 mGoogleAnalytics;
	GoogleAnalyticsV4 GoogleAnalytics {
		get {
			if (mGoogleAnalytics == null) {
				mGoogleAnalytics = GameObject.FindObjectOfType<GoogleAnalyticsV4> ();
			}
			return mGoogleAnalytics;
		}
	}

	public void init() {
//		GameObject goLoader = Instantiate (Resources.Load ("Gameplay/GAv4") as GameObject);
		Instantiate (Resources.Load ("Gameplay/GAv4") as GameObject);
	}

	public void StopSession() {
		if (GoogleAnalytics != null) {
			GoogleAnalytics.StopSession ();
		}
	}

	public void StartSession() {
		if (GoogleAnalytics != null) {
			GoogleAnalytics.StartSession ();
		}
	}

	public void TreckScreen(string screenName) {
		if (GoogleAnalytics != null) {
			GoogleAnalytics.LogScreen (screenName);
		}
	}

	public void TreckEvent(string category, string action, string label, long value) {
		if (GoogleAnalytics != null) {
			GoogleAnalytics.LogEvent (category.ToString(), action, label, value);
		}
	}

}
