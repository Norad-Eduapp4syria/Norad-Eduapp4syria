﻿using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;
using TMPro;

namespace EA4S.MakeFriends
{
    public class DropZoneController : MonoBehaviour, IDropHandler, IPointerEnterHandler
    {
        public TMP_Text LetterText;
        public Animator animator;

        [HideInInspector]
        public ILivingLetterData letterData;


        public void OnDrop(PointerEventData eventData)
        {
            var draggedLetter = MakeFriendsGame.Instance.letterPicker.letterChoiceBeingDragged;

            if (draggedLetter != null)
            {
                draggedLetter.wasChosen = true;
                DisplayText(draggedLetter.letterData);
            }
        }

        public void OnPointerEnter(PointerEventData eventData)
        {
            var draggedLetter = MakeFriendsGame.Instance.letterPicker.letterChoiceBeingDragged;

            if (draggedLetter != null)
            {
                animator.SetTrigger("Highlight");
            }
        }

        public void DisplayText(ILivingLetterData _letterData)
        {
            letterData = _letterData;
            LetterText.text = letterData.TextForLivingLetter;//ArabicAlphabetHelper.GetLetterFromUnicode(letterData.Data.Isolated_Unicode);
        }


        public void Appear(float delay = 0f)
        {
            if (delay > 0f)
            {
                StartCoroutine(Appear_Coroutine(delay));
            }
            else
            {
                animator.SetTrigger("Appear");
            }
        }

        private IEnumerator Appear_Coroutine(float delay)
        {
            yield return new WaitForSeconds(delay);
            Appear();
        }

        public void Disappear(float delay = 0f)
        {
            if (delay > 0f)
            {
                StartCoroutine(Disappear_Coroutine(delay));
            }
            else
            {
                animator.SetTrigger("Disappear");
            }
        }

        private IEnumerator Disappear_Coroutine(float delay)
        {
            yield return new WaitForSeconds(delay);
            Disappear();
        }

        public void AnimateCorrect()
        {
            animator.SetTrigger("Correct");
        }

        public void AnimateWrong()
        {
            animator.SetTrigger("Wrong");
        }

        public void ResetLetter(float delay = 0f)
        {
            if (delay > 0f)
            {
                StartCoroutine(ResetLetter_Coroutine(delay));
            }
            else
            {
                letterData = null;
                LetterText.text = string.Empty;
            }
        }

        private IEnumerator ResetLetter_Coroutine(float delay)
        {
            yield return new WaitForSeconds(delay);
            ResetLetter();
        }

        public void Reset()
        {
            ResetLetter();
            animator.SetTrigger("Hidden");
            transform.localScale = Vector3.forward;
        }

    }
}