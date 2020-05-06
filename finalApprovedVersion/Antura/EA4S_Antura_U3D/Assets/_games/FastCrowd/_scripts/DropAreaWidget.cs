﻿using UnityEngine;
using System.Collections.Generic;
using System;

namespace EA4S.FastCrowd
{
    /// <summary>
    /// This Widget hides the old implementation of DropSingleArea/DropContainer
    /// </summary>
    [RequireComponent(typeof(DropContainer))]
    public class DropAreaWidget : MonoBehaviour
    {
        public DropSingleArea dropAreaPrefab;

        public event System.Action OnComplete;

        Dictionary<ILivingLetterData, DropSingleArea> letters = new Dictionary<ILivingLetterData, DropSingleArea>();

        DropContainer container;

        public ILivingLetterData GetActiveData()
        {
            var currentArea = container.GetActualDropArea();

            if (currentArea == null)
                return null;

            return container.GetActualDropArea().Data;
        }

        void Awake()
        {
            container = GetComponent<DropContainer>();

            container.OnObjectiveBlockCompleted += OnCompleted;
        }

        public void SetMatchingOutline(bool active, bool matching)
        {
            var currentArea = container.GetActualDropArea();

            if (currentArea == null)
                return;

            if (active)
            {
                if (matching)
                    currentArea.SetMatching();
                else
                    currentArea.SetMatchingWrong();
            }
            else
                currentArea.DeactivateMatching();
        }

        public bool AdvanceArea()
        {
            if (container.GetActualDropArea() != null)
            {
                container.NextArea();
                return false;
            }

            return true;
        } 

        void OnDestroy()
        {
            if (container != null)
                container.OnObjectiveBlockCompleted -= OnCompleted;
        }

        public void AddDropNumber(ILivingLetterData newElement, int number)
        {
            DropSingleArea dropSingleArea = Instantiate(dropAreaPrefab);
            dropSingleArea.transform.SetParent(transform, false);
            dropSingleArea.transform.position = Camera.main.transform.position;
            dropSingleArea.Init(newElement, number, container);

            container.AddArea(dropSingleArea);

            letters[newElement] = dropSingleArea;
        }

        public void AddDropText(ILivingLetterData newElement, string text)
        {
            DropSingleArea dropSingleArea = Instantiate(dropAreaPrefab);
            dropSingleArea.transform.SetParent(transform, false);
            dropSingleArea.transform.position = Camera.main.transform.position;
            dropSingleArea.Init(newElement, text, container);

            container.AddArea(dropSingleArea);

            letters[newElement] = dropSingleArea;
        }

        public void AddDropData(ILivingLetterData newElement, bool asImage)
        {
            DropSingleArea dropSingleArea = Instantiate(dropAreaPrefab);
            dropSingleArea.transform.SetParent(transform, false);
            dropSingleArea.transform.position = Camera.main.transform.position;
            dropSingleArea.Init(newElement, container, asImage);

            container.AddArea(dropSingleArea);

            letters[newElement] = dropSingleArea;
        }

        public void Clean()
        {
            container.Clean();
            letters.Clear();
        }

        void OnCompleted()
        {
            if (OnComplete != null)
                OnComplete();
        }
    }
}
