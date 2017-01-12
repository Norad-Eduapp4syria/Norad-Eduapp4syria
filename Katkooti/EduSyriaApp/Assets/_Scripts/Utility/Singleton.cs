using UnityEngine;
using System.Collections;

public class  Singleton<T> : MonoBehaviour where T : MonoBehaviour
{

    private static T _instance=null;
    public static T Instance {
        get { return _instance; } 
    }

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this as T;
			DontDestroyOnLoad(this.gameObject);
        }
        else
        {
			Destroy(this.gameObject);
        }
    }


}
