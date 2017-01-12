using UnityEngine;
using Assets.Common.Interaction.Selection;
using Assets.Common.Assets.Ressi.SpineRessi;
using Assets.Common.Data;
using System;
using Assets.Common.Interaction;

[RequireComponent(typeof(TouchInteractions))]
public class StartGame : MonoBehaviour 
{
    public SceneIndex SceneToStart;
    public MonoBehaviour Title;
    public AnimationWithSound AnimationWhenStarting;

    public Vector2 CameraPosition;
    CameraMovement _cameraMovement;
    SpineRessiAnimator _animator;

    void Start () 
	{
        _animator = GameObject.FindObjectOfType<SpineRessiAnimator>();
        _cameraMovement = GameObject.FindObjectOfType<CameraMovement>();
        var button = GetComponentInChildren<SpriteRenderer>();
        var interactions = GetComponent<TouchInteractions>();

        interactions.OverrideInputChain(new ButtonTouchInteraction(button, OnStart), new TouchRessiInteraction());
    }

    void OnStart()
    {
        Utilities.FadeOutObject(Title, 1f);
        _animator.PlayTransientAnimation(AnimationWhenStarting, new AnimationEventSubscriptions
        {
            OnComplete = () =>
            {
                _cameraMovement.SetTargetX(CameraPosition.x, 0, () =>
                   StartCoroutine(GameStateManager.Instance.SwitchSceneAsync(SceneToStart.value))
               );
            }
        });
       
    }

    void OnDrawGizmosSelected()
    {
        Gizmos.DrawSphere(CameraPosition, 1);
    }


}
