using Assets.Common.Assets.Ressi;
using Assets.Common.Assets.Ressi.SpineRessi;
using Spine.Unity;
using UnityEngine;

public class ConsumableLetter : ConsumableObject {

    [Header("Reactions")]
    [SpineAnimation]
    public string PronounciationAnimation;
    [SpineEvent]
    public string PronounciationEvent;
    public AudioClip PronounciationSound;

    public AnimationWithSound RequestAnimation;

    [Header("Data")]
    public Letter Letter;
    public bool CanBeRequested; //We don't have the request sounds for letters with vocals yet
	
}
