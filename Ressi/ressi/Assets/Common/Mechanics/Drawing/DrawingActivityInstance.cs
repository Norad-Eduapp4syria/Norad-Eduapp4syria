using Assets.Common.Assets.Ressi;
using Assets.Common.Assets.Ressi.SpineRessi.AnimationControllers;
using Assets.Common.Data;
using Assets.Common.Mechanics.Gesture.Models;
using Assets.Common.Missions.Activities.LetterActivities.Models;
using System;
using System.Collections;
using UnityEngine;
using Object = UnityEngine.Object;


public class DrawingActivityInstance
{
    public Action<DrawingActivityInstance> OnTriggerActivity;
    public Action<DrawingActivityInstance> OnComplete;
    public Action<DrawingActivityInstance> OnFail;

    public bool Solved { get; private set; }
    public bool Completed { get; private set; }
    public Vector2 Position { get; private set; }

    int _currentAttempt = 1;
    GameObject _root;
    CustomEventTrigger _canvasTrigger;
    RessiController _ressi;

    //During attempt
    Gesture _gestureScript;
    int _maxAttempts;
    LetterPrefabReference _requestedLetter;
    AttemptCounter _attemptCounter;
    DrawLetterAnimationController _drawletterAnimations;
    Animator _canvasAnimator;
    Animator _letterAnimator;

    public DrawingActivityInstance(RessiController ressi, GameObject parent, int activityIndex, float position)
    {
        Position = new Vector2(position, 0);
        _ressi = ressi;

        _root = new GameObject("Drawing Activity " + activityIndex);
        _root.transform.parent = parent.transform;

        _canvasTrigger = CreateTrigger(position, _root);
        _canvasTrigger.OnEnter = RessiReachedTrigger;
    }

    public void StartActivity(DrawLetterAnimationController drawingAnimations, LetterPrefabReference requestedLetter, int maxAttempts, int sensitivity)
    {
        var canvas = InstantiateCanvas(Position.x, _root);
        var sprite = canvas.transform.GetChild(0);

        _requestedLetter = requestedLetter;
        _maxAttempts = maxAttempts;
        _attemptCounter = canvas.GetComponentInChildren<AttemptCounter>();
        _gestureScript = new Gesture(_root, sensitivity);
        _drawletterAnimations = drawingAnimations;

        _gestureScript.LettersToMatch = new Letter[] { requestedLetter.Letter };
        _ressi.TouchInteractions.OverrideInputChain(_gestureScript);
        _gestureScript.OnGestureComplete += ValidateDrawing;

        _canvasTrigger.StartCoroutine(WaitForCanvasAppearance(sprite));
    }

    IEnumerator WaitForCanvasAppearance(Transform sprite)
    {
        _canvasAnimator = sprite.GetComponent<Animator>();
        while (_canvasAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime < 0.95f)
            yield return null;

        _attemptCounter.SetMaxAttempts(_maxAttempts);
        _gestureScript.Enabled = true;

        _letterAnimator = SpawnLetterCanvas(_requestedLetter, sprite.position.x, _root.transform);

        ShowDrawingHint(onComplete: _drawletterAnimations.InitialAnimation);
    }

    void ShowDrawingHint(Action onComplete)
    {
        var consumableLetterScript = _requestedLetter.LetterScript;
        _ressi.RequestLetter(consumableLetterScript, withText: false, onComplete: () =>
        {
            onComplete.Raise();
            if (_letterAnimator != null)
                _letterAnimator.SetTrigger(Constants.AnimatorEvents.LetterhintTrigger);
        });
    }

    void ValidateDrawing(GestureRecognizerResponse response)
    {
        _gestureScript.Enabled = false;
        if (response.IsMatch && response.MatchedTemplate.Letter == _requestedLetter.Letter)
            HandleCorrectLetter();
        else
            HandleWrongLetter();
    }

    void HandleCorrectLetter()
    {
        Solved = true;
        Completed = true;
        RemoveCanvas();
        _drawletterAnimations.CompletedDrawing(() => OnComplete.Raise(this));
    }

    void HandleWrongLetter()
    {
        _drawletterAnimations.FailedDrawing(RetryAttempt);
    }

    void RetryAttempt()
    {
        if (TooManyAttempts())
        {
            Completed = true;
            RemoveCanvas();
            OnFail.Raise(this);
            return;
        }
        _currentAttempt++;
        _attemptCounter.IncrementAttempts();
        _gestureScript.Enabled = true;
        ShowDrawingHint(_drawletterAnimations.PointAtCanvas);
    }

    bool TooManyAttempts()
    {
        return _currentAttempt >= _maxAttempts;
    }

    void RessiReachedTrigger(GameObject ressi)
    {
        _canvasTrigger.OnEnter = null;
        OnTriggerActivity.Raise(this);
    }

    static GameObject InstantiateCanvas(float xPosition, GameObject root)
    {
        return ResourceLoader.InstantiatePrefabAtPosition(Constants.Resources.DrawingCanvas, xPosition, root.transform);
    }

    static Animator SpawnLetterCanvas(LetterPrefabReference letter, float xPosition, Transform parent)
    {
        var letterInWorld = letter.InstantiateOutline();
        letterInWorld.transform.parent = parent;

        var animator = letterInWorld.GetComponent<Animator>();
        letterInWorld.transform.position = new Vector2(xPosition, letterInWorld.transform.position.y);
        return animator;
    }

    public void Destroy()
    {
        _gestureScript.ResetRecognizer();
        Object.Destroy(_root);
    }

    void RemoveCanvas()
    {
        Object.Destroy(_letterAnimator.gameObject);
        Object.Destroy(_attemptCounter.gameObject);
        _canvasAnimator.SetTrigger(Constants.AnimatorEvents.HideCanvas);
    }

    static CustomEventTrigger CreateTrigger(float position, GameObject root)
    {
        var triggerContainer = ResourceLoader.InstantiatePrefabAtPosition(Constants.Resources.DrawLettersMarker, position, root.transform);

        var trigger = triggerContainer.GetComponent<CustomEventTrigger>();
        return trigger;
    }
}
