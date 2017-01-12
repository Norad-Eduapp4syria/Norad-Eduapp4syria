using UnityEngine;
using Assets.Common.Data;

public class DebuggerGameManagement : MonoBehaviour 
{
    void Start()
    {
        if(!Debug.isDebugBuild)
            gameObject.SetActive(false);
    }

    public void DeleteGameState()
    {
        GameStateManager.Instance.DeleteSave();
        gameObject.SetActive(false);
    }
}
