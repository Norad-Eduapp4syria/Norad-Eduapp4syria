using Assets.Common.Data;
using Assets.Common.Interaction.Selection;
using UnityEngine;

namespace Assets.Common
{
    class RestartGame : MonoBehaviour
    {
        public SceneIndex SceneIndex;
       
        void Start()
        {
            var button = GetComponentInChildren<SpriteRenderer>();
            var interactions = GameObject.FindObjectOfType<TouchInteractions>();

            interactions.OverrideInputChain(new ButtonTouchInteraction(button, OnStart), new TouchRessiInteraction());
        }

        void OnStart()
        {
            GameStateManager.Instance.DeleteSave();
            StartCoroutine(GameStateManager.Instance.SwitchSceneAsync(SceneIndex.value));
        }
    }
}
