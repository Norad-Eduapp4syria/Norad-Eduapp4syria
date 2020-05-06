﻿// Author: Daniele Giardini - http://www.demigiant.com
// Created: 2016/12/01

using DG.Tweening;
using TMPro;
using UnityEngine;

namespace EA4S
{
    public class BonesCounter : MonoBehaviour
    {
        public TextMeshProUGUI TfCount;
        public RectTransform BoneImg;

        int totBones {
            get { return fooTotBones; }
            set { fooTotBones = value; TfCount.text = value.ToString(); }
        }
        int fooTotBones;
        bool setupDone;
        Tween showTween, increaseTween;

        #region Unity

        void Start()
        {
            Setup();
        }

        void Setup()
        {
            if (setupDone) return;

            setupDone = true;

            SetValue(0);
            showTween = this.transform.DOScale(0.001f, 0.35f).From().SetEase(Ease.OutBack).SetAutoKill(false).Pause()
                .OnRewind(()=> this.gameObject.SetActive(false));
            showTween.Complete();
            increaseTween = BoneImg.transform.DOPunchScale(Vector3.one * 0.15f, 0.35f).SetAutoKill(false).Pause();
        }

        void OnDestroy()
        {
            showTween.Kill();
            increaseTween.Kill();
        }

        #endregion

        #region Public Methods

        public void Show(bool _setValueAuto = true)
        {
            Setup();
            if (_setValueAuto) SetValueAuto();
            this.gameObject.SetActive(true);
            showTween.PlayForward();
        }

        public void Hide()
        {
            Setup();
            if (increaseTween != null) increaseTween.Complete();
            showTween.Rewind();
        }

        public void SetValueAuto()
        {
            totBones = AppManager.I.Player.GetTotalNumberOfBones();
        }

        public void SetValue(int _bones)
        {
            totBones = _bones;
        }

        public void DecreaseBy(int _by)
        {
            totBones -= _by;
        }

        public void IncreaseByOne(bool _animate = true)
        {
            increaseTween.Restart();
            totBones++;
        }

//        public void AnimateIncreaseToCurrent(int _by)
//        {
//            increaseTween = DOVirtual.Float(totBones, totBones + _by, 0.35f, x => {
//                totBones = Mathf.RoundToInt(x);
//            }).SetEase(Ease.Linear).OnKill(()=> increaseTween = null);
//        }

        #endregion
    }
}