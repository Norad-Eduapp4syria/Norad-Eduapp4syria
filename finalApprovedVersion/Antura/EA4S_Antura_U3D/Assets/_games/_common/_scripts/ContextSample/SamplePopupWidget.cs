﻿using ArabicSupport;
using System;
using UnityEngine;
using EA4S.Db;

namespace EA4S
{
    public class SamplePopupWidget : IPopupWidget
    {
        public void Show(System.Action callback, Db.LocalizationDataId text, bool markResult, LL_WordData word = null)
        {
            if (word != null)
                WidgetPopupWindow.I.ShowSentenceAndWordWithMark(callback, text, word, markResult);
            else
                WidgetPopupWindow.I.ShowSentenceWithMark(callback, text, markResult, null);
        }

        public void Show(System.Action callback, Db.LocalizationDataId text, LL_WordData word = null)
        {
            if (word != null)
                WidgetPopupWindow.I.ShowSentenceAndWord(callback, text, word);
            else
                WidgetPopupWindow.I.ShowSentence(callback, text);
        }

        public void Show(Action callback, Sprite image)
        {
            WidgetPopupWindow.I.ShowTutorial(callback, image);
        }

        public void ShowTimeUp(Action callback)
        {
            WidgetPopupWindow.I.ShowTimeUp(callback);
        }

        public void Hide()
        {
            WidgetPopupWindow.I.Close();
        }

        public void Show(bool reset = true)
        {
            if (reset)
                WidgetPopupWindow.I.ResetContents();

            WidgetPopupWindow.I.Show(true);
        }

        public void SetButtonCallback(System.Action callback)
        {
            WidgetPopupWindow.I.SetButtonCallback(callback);
        }

        public void SetMessage(Db.LocalizationDataId text)
        {
            WidgetPopupWindow.I.SetMessage(text);
        }

        public void SetTitle(Db.LocalizationDataId text)
        {
            WidgetPopupWindow.I.SetTitleSentence(text);
        }

        public void SetMark(bool visible, bool correct)
        {
            WidgetPopupWindow.I.SetMark(visible, correct);
        }

        public void SetImage(Sprite image)
        {
            WidgetPopupWindow.I.SetImage(image);
        }

        public void SetTitle(string text)
        {
            WidgetPopupWindow.I.SetTitle(text, false);
        }

        public void SetMessage(string text)
        {
            WidgetPopupWindow.I.SetMessage(text);
        }

        public void SetLetterData(ILivingLetterData data)
        {
            if (!(data is LL_WordData))
                return;

            WidgetPopupWindow.I.SetWord(data.DrawingCharForLivingLetter, ((LL_WordData)data));
        }
    }
}
