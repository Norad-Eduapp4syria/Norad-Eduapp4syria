using UnityEngine;
using Assets.Common.Data;

[RequireComponent(typeof(Collider2D))]
public class GotoSceneTrigger : MonoBehaviour {
    
    public SceneIndex Scene;
    
    void OnTriggerEnter2D(Collider2D other)
    {
        if (!other.CompareTag(Constants.Tags.Player)) return;

        if (Scene == null)
        {
            print("GotoSceneTrigger triggered, but Scene=null");
            return;
        }

        GameStateManager.Instance.SwitchScene(Scene.value);
    }

    void OnDrawGizmos()
    {
        Gizmos.DrawIcon(transform.position, "door.png");
    }
}
