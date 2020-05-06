﻿using System;
using UnityEngine;

namespace EA4S.Egg
{
    public class EggControllerCollider : MonoBehaviour
    {
        public Collider eggCollider;

        public Action pressedCallback;

        public void EnableCollider()
        {
            eggCollider.enabled = true;
        }

        public void DisableCollider()
        {
            eggCollider.enabled = false;
        }

        void OnMouseDown()
        {
            if (pressedCallback != null)
            {
                pressedCallback();
            }
        }
    }
}
