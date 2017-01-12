using UnityEngine;

public class Touch2
{
    public Touch2(TouchPhase phase, Vector2 deltaPosition, float deltaTime, Vector2 position)
    {
        Phase = phase;
        DeltaPosition = deltaPosition;
        DeltaTime = deltaTime;
        Position = position;
    }

    public TouchPhase Phase { get; private set; }
    public Vector2 DeltaPosition { get; private set; }
    public Vector2 Position { get; private set; }
    public float DeltaTime { get; set; }
}