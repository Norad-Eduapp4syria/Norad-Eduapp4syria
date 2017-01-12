using UnityEngine;
using System;
using Assets.Common.Assets.Ressi;
using Assets.Common.Data;
using System.Linq;
using Object = UnityEngine.Object;
using Assets.Common.Assets.Ressi.SpineRessi;
using Assets.Common.Missions;

[RequireComponent(typeof(SpineRessiAnimator), typeof(RessiAutoMovement))]
[DisallowMultipleComponent]
public class RessiController : MonoBehaviour {

    [NonSerialized]
    public SpineRessiAnimator Animator;
    [NonSerialized]
    public RessiCommunication Communication;
    [NonSerialized]
    public TouchInteractions TouchInteractions;
    [NonSerialized]
    public RessiAutoMovement Movement;


    [Header("Proficiency")]
    public LetterProficiency[] LetterProficiencies;

	void Start () {
        Animator = GetComponent<SpineRessiAnimator>();
        Movement = GetComponent<RessiAutoMovement>();
        Communication = new RessiCommunication(this);
        TouchInteractions = Object.FindObjectOfType<TouchInteractions>();
        LetterProficiencies = GameStateManager.Instance.State.LetterProficiency.ToArray();
	}

    public void EatOther(ConsumableObject obj, Action onAnimationComplete)
    {
        PauseTouchInput();
        var letter = obj as ConsumableLetter;
        if (letter != null)
            ModifyProficiency(letter.Letter, -1);

        Destroy(obj.gameObject);
        Animator.ReactNegatively(onComplete: ResumeTouchAfterAnimation(onAnimationComplete));
    }

    public void EatLetter(ConsumableLetter obj, Action onAnimationComplete)
    {
        PauseTouchInput();

        Destroy(obj.gameObject);
        ModifyProficiency(obj.Letter, 1);

        Animator.ReactPositively();
        PronounceLetter(obj, ResumeTouchAfterAnimation(onAnimationComplete));
    }

    void PronounceLetter(ConsumableLetter obj, Action onAnimationComplete)
    {
        Animator.PronounceLetter(obj, onAnimationComplete);
    }

    public void FailActivity(Action onAnimationComplete = null)
    {
        PauseTouchInput();
        Animator.FailActivity(new AnimationEventSubscriptions { OnComplete = ResumeTouchAfterAnimation(onAnimationComplete) });
    }

    public void CompleteActivity(Action onAnimationComplete = null)
    {
        PauseTouchInput();
        Animator.CompleteActivity(new AnimationEventSubscriptions { OnComplete = ResumeTouchAfterAnimation(onAnimationComplete) });
    }

    public void FinishActivity(ActivityScore score, Action onAnimationComplete = null)
    {
        PauseTouchInput();
        Animator.FinishActivity(score, ResumeTouchAfterAnimation(onAnimationComplete));
    }

    public void RequestLetter(ConsumableLetter obj, bool withText, Action onComplete = null)
    {
        var subscriptions = new AnimationEventSubscriptions
        {
            OnComplete = onComplete
        };

        Animator.RequestLetter(obj, subscriptions);
        if (withText)
            Communication.ShowDialog(obj.Letter.ToString());
    }

    public void PauseTouchInput()
    {
        Movement.enabled = false;
        TouchInteractions.Paused = true; 
    }

    public void ResumeTouch()
    {
        Movement.enabled = true;
        TouchInteractions.Paused = false;
    }

    public Action ResumeTouchAfterAnimation(Action onAnimationComplete)
    {
        return () =>
        {
            ResumeTouch();
            onAnimationComplete.Raise();
        };
    }

    void ModifyProficiency(Letter letter, int modifier)
    {
        var letterProficiency = LetterProficiencies.FirstOrDefault(i => i.Letter == letter);
        if (letterProficiency == null)
        {
            letterProficiency = new LetterProficiency(letter, 0);
            GameStateManager.Instance.State.LetterProficiency.Add(letterProficiency);
            LetterProficiencies = GameStateManager.Instance.State.LetterProficiency.ToArray();
        }

        letterProficiency.AddProficiency(modifier);

        GameStateManager.Instance.State.LetterProficiency = LetterProficiencies.ToList();
    }
}
