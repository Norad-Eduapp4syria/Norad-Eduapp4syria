using UnityEngine;
using System.Collections;

public class Util : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}

public class MessageBox
{
    #region Console Log Fuctions
    // ====================================== Console Log Functions Start =============================================
    public static void ShowLog(string msg)
    {
        if (GameManager.Instance.gameSettings.isDevelopmentBuild)
        {
            Debug.Log(msg);
        }
    }
    public static void ShowError(string msg)
    {
        if (GameManager.Instance.gameSettings.isDevelopmentBuild)
        {
            Debug.LogError(msg);
        }
    }
    public static void ShowWarning(string msg)
    {
        if (GameManager.Instance.gameSettings.isDevelopmentBuild)
        {
            Debug.LogWarning(msg);
        }
    }
    // ======================================== Console Log Functions End ==================================================

    #endregion
}
