using UnityEngine;

public class TouchSimulator
{
    Vector2 _lastPosition;
    float _lastTime;

    public Touch2[] SimulateTouchWithMouse()
    {
        TouchPhase phase;
        Vector2 position;

        if (Input.GetMouseButtonDown(0))
        {
            phase = TouchPhase.Began;
            position = new Vector2(Input.mousePosition.x, Input.mousePosition.y);
        }
        else if (Input.GetMouseButtonUp(0))
        {
            phase = TouchPhase.Ended;
            position = new Vector2(Input.mousePosition.x, Input.mousePosition.y);
        }
        else if (Input.GetMouseButton(0))
        {
            position = new Vector2(Input.mousePosition.x, Input.mousePosition.y);

            var deltaPos = position - _lastPosition;
            phase = deltaPos.magnitude > 0.01f ? TouchPhase.Moved : TouchPhase.Stationary;
        }
        else
        {
            return new Touch2[0];
        }

        var deltaPosition = position - _lastPosition;
        var deltaTime = Time.time - _lastTime;

        _lastPosition = position;
        _lastTime = Time.time;

        return new[] { new Touch2(phase, deltaPosition, deltaTime, position) };
    }
}