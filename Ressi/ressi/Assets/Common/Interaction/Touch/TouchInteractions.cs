using Assets.Common.Interaction.Selection;
using System.Linq;
using UnityEngine;

public class TouchInteractions : MonoBehaviour
{
    readonly ITouchInteraction[] _defaultInteractions = {
        new SelectableObjectTouchInteraction(),
        new TouchRessiInteraction(),
        CameraTouchInteraction
    };

    public bool Paused;

    public static readonly SwipeUpDownTouchInteraction SwipeUpDownTouchInteraction = new SwipeUpDownTouchInteraction();
    public static readonly CameraTouchInteraction CameraTouchInteraction = new CameraTouchInteraction();

    ITouchInteraction[] _interactions;
    Camera _mainCamera;

    void Awake()
    {
        _mainCamera = Camera.main;

        StartupGestures(_defaultInteractions);
        UseDefaultInputChain();
    }

    public void UseDefaultInputChain()
    {
        _interactions = _defaultInteractions;
    }

    public void OverrideInputChain(params ITouchInteraction[] interactions)
    {
        if (interactions == null)
            Debug.LogError("Trying to override input with NULL");

        StartupGestures(interactions);
        _interactions = interactions;
    }

    private void StartupGestures(ITouchInteraction[] interaction)
    {
        foreach (var gesture in interaction)
        {
            gesture.Start(_mainCamera);
        }
    }

    void Update()
    {
        if (Paused)
            return;

        var touches = GetTouches();
        
        foreach (var interaction in _interactions)
        {
            var result = interaction.Update(touches);
            
            if (!result.AllowNext) break;
        }
    }

    readonly TouchSimulator _touchSimulator = new TouchSimulator();

    private Touch2[] GetTouches()
    {
        var touches = Input.touches;

        if (touches.Any()) return ParseTouches(touches);
        else return _touchSimulator.SimulateTouchWithMouse();
    }

    private static Touch2[] ParseTouches(Touch[] touches)
    {
        return touches.Select(t => new Touch2(t.phase, t.deltaPosition, t.deltaTime, t.position)).ToArray();
    }
}