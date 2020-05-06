﻿// Author: Daniele Giardini - http://www.demigiant.com
// Created: 2016/11/29

using System.Collections;
using DG.Tweening;
using UnityEngine;
using UnityEngine.UI;

namespace EA4S
{
    [RequireComponent(typeof(CanvasGroup))]
    public class CreditsUI : MonoBehaviour
    {
        [Tooltip("Units x second for the scroll animation")]
        public float ScrollAnimationSpeed = 100;
        public float ScrollAnimationDelay = 1.5f;
        public Color Level0Color = Color.blue;
        public int Level0FontPerc = 140;
        public Color Level1Color = Color.yellow;
        public int Level1FontPerc = 110;
        [Header("References")]
        public TextAsset CreditsTxt;
        public RectTransform CreditsContainer;
        public UIButton BtBack;
        public TMPro.TextMeshProUGUI TfCredits;

        public bool HasAwoken { get; private set; }
        RectTransform rectT;
        Vector2 defCreditsContainerPos;
        Tween showTween, scrollTween;

        #region Unity

        void Awake()
        {
            HasAwoken = true;
            defCreditsContainerPos = CreditsContainer.anchoredPosition;
            rectT = this.GetComponent<RectTransform>();

            showTween = this.GetComponent<CanvasGroup>().DOFade(0, 0.4f).From().SetEase(Ease.Linear).SetUpdate(true).SetAutoKill(false).Pause()
                .OnRewind(() => this.gameObject.SetActive(false));

            this.gameObject.SetActive(false);

            // Listeners
            BtBack.Bt.onClick.AddListener(OnClick);

            TfCredits.text = FormatCredits(CreditsTxt.text);
        }

        void Update()
        {
            if (Input.GetMouseButtonDown(0)) StopScrollLoop();
            else if (Input.GetMouseButtonUp(0) && showTween.IsComplete()) StartScrollLoop();
        }

        void OnDestroy()
        {
            this.StopAllCoroutines();
            showTween.Kill();
            scrollTween.Kill();
            BtBack.Bt.onClick.RemoveAllListeners();
        }

        #endregion

        #region Public Methods

        public void Show(bool _doShow)
        {
            scrollTween.Kill();
            this.StopAllCoroutines();
            if (_doShow) {
                this.gameObject.SetActive(true);
                CreditsContainer.anchoredPosition = defCreditsContainerPos;
                showTween.PlayForward();
                StartScrollLoop();
            } else {
                showTween.PlayBackwards();
            }
        }

        #endregion

        #region Methods

        string FormatCredits(string _txt)
        {
            // Format
            string lv0 = "<size=" + Level0FontPerc + "%><color=#" + GenericUtilities.ColorToHex(Level0Color) + ">";
            string lv1 = "<size=" + Level1FontPerc + "%><color=#" + GenericUtilities.ColorToHex(Level1Color) + ">";
            _txt = _txt.Replace("[0]", lv0);
            _txt = _txt.Replace("[0E]", "</color></size>");
            _txt = _txt.Replace("[1]", lv1);
            _txt = _txt.Replace("[1E]", "</color></size>");
            // Fix missing characters
            _txt = _txt.Replace("ö", "o");

            return _txt;
        }

        void StartScrollLoop()
        {
            this.StartCoroutine(CO_StartScrollLoop());
        }

        IEnumerator CO_StartScrollLoop()
        {
            yield return null;

            float toY = CreditsContainer.rect.height - rectT.rect.height;
            scrollTween = CreditsContainer.DOAnchorPosY(toY, ScrollAnimationSpeed).SetSpeedBased()
                .SetEase(Ease.Linear).SetDelay(ScrollAnimationDelay).SetUpdate(true);
        }

        void StopScrollLoop()
        {
            this.StopAllCoroutines();
            scrollTween.Kill();
        }

        #endregion

        #region Callbacks

        void OnClick()
        {
            Show(false);
        }

        #endregion
    }
}