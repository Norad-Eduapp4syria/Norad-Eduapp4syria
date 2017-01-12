using UnityEngine;
using System.Collections.Generic;
using Assets.Common.Interaction;
using Assets.Common.Mechanics.Gesture.Models;
using System;
using Assets.Common.Assets.Ressi;

public class Gesture : ITouchInteraction
{
    public bool Enabled;

    float _graceTimeInSeconds = 2.0f;
    int _sensitivity = 60;

    float _strokeStartWidth = 0.5f;
    float _strokeEndWidth = 0.5f;
    Color _strokeStartColor = Color.white;
    Color _strokeEndColor = Color.white;
    float _strokeDotRadius = 0.1f;

    Stroke _currentStroke;
    List<Stroke> _strokes;

    public event Action<GestureRecognizerResponse> OnGestureComplete;

    GestureRecognizer _recognizer;
    GestureDebugger _debugger;

    float _lastTouch = Mathf.Infinity;
    GameObject _rootObject;
    Camera _camera;

    bool _isDrawing;

    public Letter[] LettersToMatch;

    public Gesture(GameObject rootObject, int sensitivity)
    {
        _rootObject = rootObject;
        Enabled = false;
        _sensitivity = sensitivity;
    }

    public void Start(Camera camera)
    {
        _camera = camera;
        _debugger = GameObject.FindObjectOfType<GestureDebugger>();
        _recognizer = new GestureRecognizer(_debugger);
        _strokes = new List<Stroke>();
    }

    public void ResetRecognizer()
    {
        _isDrawing = false;
        _lastTouch = Mathf.Infinity;
        
        foreach (var stroke in _strokes)
        {
            GameObject.Destroy(stroke.Renderer.gameObject);
        }
        _strokes = new List<Stroke>();
       
    }
    
    public InteractionContinuation Update(Touch2[] touches)
    {
        if (!Enabled)
            return InteractionContinuation.End();

        if (touches.Length == 1)
        {
            var touch = touches[0];
            switch (touch.Phase)
            {
                case TouchPhase.Began:
                    TryStartGesture(touch);                    
                    break;
                case TouchPhase.Moved:
                    TryAddStroke(touch);
                    break;
                case TouchPhase.Ended:
                    TryAddStroke(touch);
                    TryFinishStroke();
                    break;
                case TouchPhase.Canceled:
                    TryFinishStroke();
                    break;
            }
        }
        else if (_isDrawing && Time.time > (_lastTouch + _graceTimeInSeconds))
        {
            FinalizeGesture();
        }

        return InteractionContinuation.End();
    }

    void TryAddStroke(Touch2 touch)
    {
        if (!_isDrawing)
            return;

        if (!IsOnCanvas(touch))
            return;

        _currentStroke.Add(Utilities.GetNormalizedWorldCoordinates(_camera, touch));
    }

    void TryFinishStroke()
    {
        if (!_isDrawing)
            return;

        if (GestureRecognizer.IsDot(_currentStroke))
            _currentStroke.ConvertToPoint(_strokeDotRadius);

        _lastTouch = Time.time;
        _strokes.Add(_currentStroke);
        _currentStroke = null;
    }

    void TryStartGesture(Touch2 touch)
    {
        if (!IsOnCanvas(touch))
            return;

        _isDrawing = true;
        _currentStroke = CreateStroke();
        _currentStroke.Add(Utilities.GetNormalizedWorldCoordinates(_camera, touch));
    }

    bool IsOnCanvas(Touch2 touch)
    {
        var origin = _camera.ScreenToWorldPoint(touch.Position);
        var hit = Physics2D.Raycast(origin, Vector2.zero, 10, Constants.Layers.Canvas);
        return hit.collider != null;
    }

    void FinalizeGesture()
    {
        var response = _recognizer.StartRecognizer(_strokes, _sensitivity, LettersToMatch);
        OnGestureComplete.Raise(response);

        if (_debugger != null)
            _debugger.RecognizerFinished(response);

        ResetRecognizer();
    }

    Stroke CreateStroke()
    {
        var line = new GameObject("Stroke");
        line.transform.parent = _rootObject.transform;
        var lRenderer = line.AddComponent<LineRenderer>();
        lRenderer.material = new Material(Shader.Find(Constants.Resources.LineRenderShader));
        lRenderer.useWorldSpace = true;
        lRenderer.sortingLayerID = Constants.SortingLayers.Foreground;
        lRenderer.sortingOrder = 99;

        //Switched end and start because we append new points to list instead of prepending
        lRenderer.SetWidth(_strokeEndWidth, _strokeStartWidth);
        lRenderer.SetColors(_strokeEndColor, _strokeStartColor);
        return new Stroke(lRenderer);
    }
}



