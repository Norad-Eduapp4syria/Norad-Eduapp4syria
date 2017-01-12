using System.Linq;
using UnityEngine;

public class SelectableObjectTouchInteraction : ITouchInteraction
{
    private Camera _camera;
    private float _longpressTime = 0.05f;
    private float _touchPhaseBeganTime = float.MaxValue;
    private SelectOnTouch _selectedObject;

    public void Start(Camera camera)
    {
        _camera = camera;
    }

    public InteractionContinuation Update(Touch2[] touches)
    {
        if (!touches.Any()) return InteractionContinuation.Next();

        var touch = touches.First();

        MaybeDeselectObject(touch);
        MaybeSelectObject(touch);

        MaybeMoveSelectedObject(touch);

        if(_selectedObject == null) return InteractionContinuation.Next();
        return InteractionContinuation.End();
    }

    private void MaybeDeselectObject(Touch2 touch)
    {
        if (_selectedObject == null) return;
        
        if (touch.Phase != TouchPhase.Ended) return;

        Debug.Log("Deselecting object");

        _selectedObject.Deselect();
        _selectedObject = null;
        _touchPhaseBeganTime = float.MaxValue;
    }

    private void MaybeSelectObject(Touch2 touch)
    {
        if (_selectedObject != null) return;
        
        if (touch.Phase == TouchPhase.Began) ResetLongPressTimer();
        if (touch.Phase != TouchPhase.Stationary) return;
        
        if (Time.time - _longpressTime < _touchPhaseBeganTime) return;

        ResetLongPressTimer();
        
        var origin = _camera.ScreenToWorldPoint(touch.Position);
        
        var hit = Physics2D.Raycast(origin, Vector2.zero, 10, Constants.Layers.Ground);
        
        if(touch.Phase == TouchPhase.Began)
            Debug.Log("_camera touch at " + origin);

        Debug.DrawRay(origin, Vector3.forward*10, Color.red, 10f);

        if (hit.collider == null)
            return;
        
        var selected = hit.collider.gameObject.GetComponent<SelectOnTouch>();
        if (selected == null) return;

        Debug.Log("Selecting object " + hit.collider.gameObject.name);
        
        selected.Select();
        _selectedObject = selected;
    }

    private void ResetLongPressTimer()
    {
        _touchPhaseBeganTime = Time.time;
    }

    private void MaybeMoveSelectedObject(Touch2 touch)
    {
        if (_selectedObject == null) return;

        _selectedObject.Move(_camera.ScreenToWorldPoint(touch.Position));
    }
}