﻿using System;
using System.Collections.Generic;
using UnityEngine;

namespace EA4S
{
    public class CircleButtonBox : MonoBehaviour
    {
        bool active = true;
        public bool Active
        {
            get
            {
                return active;
            }
            set
            {
                active = value;
                for (int i = 0; i < buttons.Count; ++i)
                    buttons[i].Active = value;
            }
        }

        public float buttonDistance = 20f;
        public int maxButtonsPerLine = 5;

        public GameObject buttonPrefab;

        List<CircleButton> buttons = new List<CircleButton>();

        Action<ILivingLetterData> buttonsCallback;

        System.Random randomGenerator;
        bool dirty = false;

        bool imageMode;
        public bool ImageMode
        {
            get
            {
                return imageMode;
            }
            set
            {
                imageMode = value;
                for (int i = 0; i < buttons.Count; i++)
                    buttons[i].ImageMode = value;
            }
        }

        public void Clear(System.Action onClearAnimationCompleted = null, float startDelay = 0)
        {
            for (int i = 0; i < buttons.Count; i++)
            {
                CircleButton button = buttons[i];

                button.Destroy(startDelay + i * 0.1f, i == buttons.Count - 1 ? onClearAnimationCompleted : null);
            }

            buttons.Clear();
        }

        public CircleButton AddButton(ILivingLetterData letterData, System.Action<CircleButton> onClicked, float enterAnimationDelay)
        {
            CircleButton button = CreateButton();
            button.Answer = letterData;
            button.onClicked = onClicked;
            button.ImageMode = ImageMode;
            buttons.Add(button);
            button.DoEnterAnimation(enterAnimationDelay);
            button.Active = Active;
            dirty = true;

            return button;
        }

        CircleButton CreateButton()
        {
            CircleButton button = Instantiate(buttonPrefab).GetComponent<CircleButton>();
            button.transform.SetParent(transform, false);

            return button;
        }

        public bool IsReady()
        {
            for (int i = 0; i < buttons.Count; i++)
            {
                if (!buttons[i].IsReady())
                    return false;
            }
            return true;
        }

        public void ShowButtons()
        {
            for (int i = 0; i < buttons.Count; i++)
            {
                buttons[i].gameObject.SetActive(true);
            }
        }

        public void HideButtons()
        {
            for (int i = 0; i < buttons.Count; i++)
            {
                buttons[i].gameObject.SetActive(false);
            }
        }

        public void UpdatePositions()
        {
            int buttonPerLine = maxButtonsPerLine;

            if (buttonPerLine == buttons.Count - 1)
                --buttonPerLine;

            int width = Mathf.Min(buttons.Count, buttonPerLine);
            int height = (buttons.Count + buttonPerLine - 1) / buttonPerLine;

            for (int i = 0; i < buttons.Count; i++)
            {
                int idX = i % width;
                int idY = i / width;

                float rowWidth = width;

                if (idY == height - 1)
                {
                    rowWidth = buttons.Count % buttonPerLine;
                    if (rowWidth == 0)
                        rowWidth = width;
                }

                buttons[i].transform.localPosition = Vector3.right * (-0.5f * (rowWidth - 1) + idX) * buttonDistance + Vector3.down * (-0.5f * (height - 1) + idY) * buttonDistance;
            }
        }

        void Update()
        {
            if (dirty)
                UpdatePositions();
        }
    }
}