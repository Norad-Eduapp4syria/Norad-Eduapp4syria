using System;
using UnityEngine;

public class ButtonTouchInteraction : ITouchInteraction
{
    Camera _camera;
    Action _onStart;
    bool _started;
    SpriteRenderer _startButton;

    public ButtonTouchInteraction(SpriteRenderer startButton, Action onStart)
    {
        _onStart = onStart;
        _startButton = startButton;
    }

    public void Start(Camera camera)
    {
        _camera = camera;
    }

    public InteractionContinuation Update(Touch2[] touches)
    {
        if (_started)
            return InteractionContinuation.End();

        if (!SingleTouchBegan(touches))
            return InteractionContinuation.Next();

        var touch = touches[0];
        if (!HitStartButton(touch))
            return InteractionContinuation.Next();

        _started = true;
        StartPlaying();
        return InteractionContinuation.End();
    }

    bool SingleTouchBegan(Touch2[] touches)
    {
        if (touches.Length != 1)
            return false;

        if (touches[0].Phase != TouchPhase.Began)
            return false;

        return true;
    }

    bool HitStartButton(Touch2 touch)
    {
        var origin = _camera.ScreenToWorldPoint(touch.Position);
        var hit = Physics2D.Raycast(origin, Vector2.zero, 10, Constants.Layers.UI);

        return hit.collider != null;
    }

    void StartPlaying()
    {
        _startButton.enabled = false;
        _onStart.Raise();
    }
}