using UnityEngine;
using System.Collections;

[System.Serializable]
public class GameSettings  {

    public bool isDevelopmentBuild = true;
    [Range(15,60)]
    public int TargerFPS=30;
}
