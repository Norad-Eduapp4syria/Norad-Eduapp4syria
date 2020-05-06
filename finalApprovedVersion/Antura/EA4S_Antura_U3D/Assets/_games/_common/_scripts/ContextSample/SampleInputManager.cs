﻿using System;
using UnityEngine;

namespace EA4S
{
    public class SampleInputManager : IInputManager
    {
        public bool Enabled { get; set; }

        public Vector2 LastPointerPosition { get { return lastPointerPosition; } }
        public Vector2 LastPointerDelta { get { return deltaPosition; } }
        public float LastDeltaTime { get; private set; }

        public Vector2 LastPointerPositionNormalized { get { return new Vector2(LastPointerPosition.x / (float)Screen.width, LastPointerPosition.y / (float)Screen.height); } }
        public Vector2 LastPointerPositionPhysical { get { return LastPointerPosition / Screen.dpi; } }

        public Vector2 LastPointerDeltaNormalized { get { return new Vector2(LastPointerDelta.x / (float)Screen.width, LastPointerDelta.y / (float)Screen.height); } }
        public Vector2 LastPointerDeltaPhysical { get { return LastPointerDelta / Screen.dpi; } }

        public event Action onPointerDown;
        public event Action onPointerDrag;
        public event Action onPointerUp;

        bool wasPointerDown = false;
        Vector2 lastPointerPosition = Vector2.zero;
        Vector2 deltaPosition;

        public void Reset()
        {
            onPointerDown = null;
            onPointerDrag = null;
            onPointerUp = null;
        }

        public void Update(float delta)
        {
            LastDeltaTime = delta;

            if (!Enabled)
                return;

            if (Input.GetMouseButton(0))
            {
                if (wasPointerDown)
                {
                    var newPosition = Input.mousePosition;
                    deltaPosition = (Vector2)newPosition - lastPointerPosition;

                    lastPointerPosition = newPosition;

                    if (deltaPosition.x != 0 || deltaPosition.y != 0)
                    {
                        if (onPointerDrag != null)
                            onPointerDrag();
                    }
                }
                else
                {
                    deltaPosition = Vector2.zero;
                    lastPointerPosition = Input.mousePosition;
                    wasPointerDown = true;

                    if (onPointerDown != null)
                        onPointerDown();
                }
            }
            else
            {
                deltaPosition = Vector2.zero;
                if (wasPointerDown)
                {
                    wasPointerDown = false;

                    if (onPointerUp != null)
                        onPointerUp();
                }
            }
        }
    }
}