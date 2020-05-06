﻿using UnityEngine;
using System.Collections.Generic;
using System;

namespace EA4S.FastCrowd
{
    /// <summary>
    /// This class manages the letters crowd
    /// </summary>
    public class FastCrowdLetterCrowd : LetterCrowd
    {
        FastCrowdDraggableLetter dragging;

        void Start()
        {
            var inputManager = FastCrowdConfiguration.Instance.Context.GetInputManager();

            inputManager.onPointerDown += OnPointerDown;
            inputManager.onPointerUp += OnPointerUp;
        }

        void OnPointerDown()
        {
            if (dragging != null)
                return;

            var inputManager = FastCrowdConfiguration.Instance.Context.GetInputManager();

            Vector3 draggingPosition = Vector3.zero;
            float draggingDistance = 100;

            for (int i = 0, count = letters.Count; i < count; ++i)
            {
                Vector3 position;
                float distance;
                if (letters[i].Raycast(out distance, out position, Camera.main.ScreenPointToRay(inputManager.LastPointerPosition), draggingDistance) &&
                    distance < draggingDistance)
                {
                    draggingPosition = position;
                    draggingDistance = distance;
                    dragging = letters[i].GetComponent<FastCrowdDraggableLetter>();
                }
            }

            if (dragging != null)
            {
                dragging.StartDragging(draggingPosition - dragging.transform.position);

                var data = dragging.GetComponent<LetterObjectView>().Data;

                FastCrowdConfiguration.Instance.Context.GetAudioManager().PlayLetterData(data, true);
            }
        }

        void OnPointerUp()
        {
            if (dragging != null)
                dragging.EndDragging();
            dragging = null;
        }
        
        protected override LetterObjectView SpawnLetter()
        {
            LetterObjectView l = base.SpawnLetter();

            l.gameObject.AddComponent<FastCrowdDraggableLetter>();

            return l;
        }
    }
}
