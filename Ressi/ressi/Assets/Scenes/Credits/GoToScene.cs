using UnityEngine;
using Assets.Common.Data;

public class GoToScene : MonoBehaviour 
{
    public SceneIndex Scene;
	
    public void ChangeScene()
    {
        StartCoroutine(GameStateManager.Instance.SwitchSceneAsync(Scene.value));
    }
}
