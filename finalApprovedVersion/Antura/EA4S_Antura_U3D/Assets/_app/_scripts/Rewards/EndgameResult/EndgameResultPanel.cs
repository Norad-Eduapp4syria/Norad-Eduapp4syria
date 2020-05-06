﻿// Author: Daniele Giardini - http://www.demigiant.com
// Created: 2016/11/18

using System.Collections;
using DG.DeExtensions;
using DG.Tweening;
using ModularFramework.Core;
using UnityEngine;
using UnityEngine.UI;

namespace EA4S
{
    public class EndgameResultPanel : MonoBehaviour
    {
        public RectTransform ContentRT;
        public Image Rays;
        public EndgameStar[] Stars;
        [Header("Audio")]
        public Sfx SfxGainStar = Sfx.UIPopup;
        public Sfx SfxCompleteWithStars = Sfx.Win;
        public Sfx SfxCompleteNoStars = Sfx.Lose;

        public static EndgameResultPanel I { get; private set; }
        bool setupDone;
        int numStars;
        RectTransform raysRT;
        Sequence showTween;
        Tween bgTween;

        #region Unity + Setup

        void Setup()
        {
            if (setupDone) return;

            setupDone = true;
            I = this;
            raysRT = Rays.GetComponent<RectTransform>();

            showTween = DOTween.Sequence().SetAutoKill(false).Pause()
                .Append(this.GetComponent<Image>().DOFade(0, 0.35f).From().SetEase(Ease.Linear))
                .Join(ContentRT.DOAnchorPosY(-960, 0.35f).From().SetEase(Ease.OutBack))
                .OnRewind(() => {
                    this.gameObject.SetActive(false);
                    bgTween.Rewind();
                })
                .OnComplete(()=> this.StartCoroutine(CO_ShowComplete()));
            for (int i = 0; i < Stars.Length; ++i) {
                EndgameStar star = Stars[i];
                star.Setup();
                showTween.Insert(0.2f + i * 0.1f, star.StarImg.DOFade(0, 0.3f).From().SetEase(Ease.Linear));
                showTween.Insert(0.2f + i * 0.1f, star.transform.DORotate(new Vector3(0, 0, -200), 0.3f, RotateMode.FastBeyond360).From());
            }
            bgTween = DOTween.Sequence().SetAutoKill(false).Pause()
                .Append(Rays.DOFade(0, 0.35f).From().SetEase(Ease.Linear))
                .Join(Rays.transform.DORotate(new Vector3(0, 0, 360), 9f, RotateMode.FastBeyond360).SetEase(Ease.Linear).SetLoops(9999));

            this.gameObject.SetActive(false);
        }

        void Awake()
        {
            Setup();
        }

        void OnDestroy()
        {
            if (I == this) I = null;
            showTween.Kill();
            bgTween.Kill();
        }

        #endregion

        #region Public Methods

        public void Show(int _numStars = 0)
        {
            Setup();

            this.StopAllCoroutines();
            ContinueScreen.Close(true);
            numStars = _numStars;
            this.gameObject.SetActive(true);
            foreach (EndgameStar star in Stars) star.Reset();
            showTween.Restart();
            this.gameObject.SetActive(true);
            GameResultUI.I.BonesCounter.Show();
            GameResultUI.I.BonesCounter.DecreaseBy(_numStars);
        }

        public void Hide(bool _immediate)
        {
            if (!setupDone) return;

            this.StopAllCoroutines();
            ContinueScreen.Close(true);
            if (_immediate) showTween.Rewind();
            else showTween.PlayBackwards();
        }

        #endregion

        #region Methods

        IEnumerator CO_ShowComplete()
        {
            int id = 0;
            while (id < numStars) {
                Stars[id].Gain();
                GameResultUI.I.BonesCounter.IncreaseByOne();
                yield return new WaitForSeconds(0.2f);
                id++;
            }

            if (numStars > 0) bgTween.Restart();

            AudioManager.I.PlaySfx(numStars > 0 ? SfxCompleteWithStars : SfxCompleteNoStars);
            ContinueScreen.Show(Continue, ContinueScreenMode.Button);
        }

        void Continue()
        {
            //          GameManager.Instance.Modules.SceneModule.LoadSceneWithTransition(AppManager.I.MiniGameDone());
            NavigationManager.I.GoToNextScene();
        }

        #endregion
    }
}