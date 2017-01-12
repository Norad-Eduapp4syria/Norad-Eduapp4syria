using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Analytics;

public class CameraTouchInteraction : ITouchInteraction
{
    Camera _camera;
    public static float TouchSensitivity = 0.3f;

    public float CameraRightBounds;
    public float CameraLeftBounds;

    public void Start(Camera camera)
    {
        _camera = camera;
        CalculateTouchSensitivity();
    }

    private void CalculateTouchSensitivity()
    {
        if (Screen.dpi < 1)
        {
            Debug.Log("Unknown Screen DPI. Defaulting to touch sensitivity = 1");
            Analytics.CustomEvent(CustomEventNames.SetTouchSensitivity, new Dictionary<string, object> { { CustomEventData.Dpi, Screen.dpi }, { CustomEventData.ScreenWidth, Screen.width }, { CustomEventData.TouchSensitivity, TouchSensitivity } });
            return;
        }

        TouchSensitivity = Screen.dpi * 5 / Screen.width;
        Debug.LogFormat("Screen DPI={0}, width={1}, resulting touch sensitivity = {2}", Screen.dpi, Screen.width, TouchSensitivity);

        Analytics.CustomEvent(CustomEventNames.SetTouchSensitivity, new Dictionary<string, object> { {CustomEventData.Dpi, Screen.dpi}, {CustomEventData.ScreenWidth, Screen.width}, { CustomEventData.TouchSensitivity, TouchSensitivity} });
    }

    public InteractionContinuation Update(Touch2[] touches)
    {
        if (touches.Any())
        {
            var touch = touches.First();
            PanCamera(touch);
        }
        else
        {
            MaybeApplyInertia();
        }

        return InteractionContinuation.Next();
    }

    private void PanCamera(Touch2 touch)
    {
        switch (touch.Phase)
        {
            case TouchPhase.Began:
                StopInertia();
                break;

            case TouchPhase.Moved:
                MoveCamera(touch);
                break;

            case TouchPhase.Ended:
                StartInertia();
                break;
        }
    }

    private void StartInertia()
    {
        _isUnderInertia = true;
        _inertiaTimer = 0.0f;
    }

    private void StopInertia()
    {
        _isUnderInertia = false;
        _inertiaTimer = 0.0f;
        _inertia = Vector3.zero;
    }

    private void MoveCamera(Touch2 touch)
    {
        _inertia = CalculateInertia(touch);
        _camera.transform.position += ClampDeltaMovement(_inertia);
    }

    private Vector3 CalculateInertia(Touch2 touch)
    {
        Vector2 delta = touch.DeltaPosition;

        float positionX = -delta.x*TouchSensitivity*Time.deltaTime;
        float positionY = 0; // -delta.y * TouchSensitivity * Time.deltaTime;

        return new Vector3(positionX, positionY, 0);
    }

    private bool _isUnderInertia;
    private float _inertiaTimer;
    private float InertiaDuration = 1;

    private Vector3 _inertia;

    private void MaybeApplyInertia()
    {
        if (!_isUnderInertia) return;
        
        if(_inertiaTimer > InertiaDuration)
        {
            StopInertia();
            return;
        }
        
        ApplyInertia();
    }

    private void ApplyInertia()
    {
        _camera.transform.position += ClampDeltaMovement(_inertia);
        _inertia = Vector3.Lerp(_inertia, Vector3.zero, _inertiaTimer);
        _inertiaTimer += Time.smoothDeltaTime;
    }
    
    Vector3 ClampDeltaMovement(Vector3 deltaMovement)
    {
        var newPosition = _camera.transform.position + deltaMovement;
        var cameraHalfWidth = GetCameraWidth() / 2;
        if (newPosition.x + cameraHalfWidth > CameraRightBounds)
            return Vector3.zero;

        if (newPosition.x - cameraHalfWidth < CameraLeftBounds)
            return Vector3.zero;

        return deltaMovement;
    }

    float GetCameraWidth()
    {
        var height = 2 * _camera.orthographicSize;
        return height * _camera.aspect;
    }
}