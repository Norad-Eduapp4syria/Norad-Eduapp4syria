﻿// Author: Daniele Giardini - http://www.demigiant.com

using UnityEngine;
using System.Collections;
using DG.Tweening;

namespace EA4S
{
    /// <summary>
    /// Animates the appearance of the reward scene
    /// </summary>
    public class RewardsAnimator : MonoBehaviour
    {
        [Header("Settings")]
        public float Pedestal360Duration = 15f;
        public float Godrays360Duration = 15f;
        [Header("References")]
        public Transform Pedestal;
        public RectTransform Bottom;
        public RectTransform Godray0, Godray1;
        public RectTransform LockClosed, LockOpen;

        public bool IsComplete { get; private set; }

        Transform pedestalObject;
        Sequence showTween, godraysTween;
        Tween pedestalTween;

        IEnumerator Start()
        {
            LockClosed.gameObject.SetActive(false);
            LockOpen.gameObject.SetActive(false);
            Pedestal.gameObject.SetActive(true);

            showTween = DOTween.Sequence().Pause()
                .Append(LockClosed.DOScale(0.0001f, 0.45f).From().SetEase(Ease.OutBack))
                .AppendInterval(0.3f)
                .AppendCallback(() => {
                    AudioManager.I.PlaySfx(Sfx.AlarmClock);
                })
                .Append(LockClosed.DOShakePosition(0.8f, 40f, 16, 90, false, false))
                .Join(LockClosed.DOShakeRotation(0.8f, new Vector3(0, 0, 70f), 16, 90, false))
                .Join(LockClosed.DOPunchScale(Vector3.one * 0.8f, 0.4f, 20))
                .AppendCallback(() => {
                    LockClosed.gameObject.SetActive(false);
                    LockOpen.gameObject.SetActive(true);
                    AudioManager.I.StopSfx(Sfx.AlarmClock);
                    AudioManager.I.PlaySfx(Sfx.UIPopup);
                })
                .Join(LockClosed.DOScale(0.00001f, 0.4f))
                .Join(LockOpen.DOScale(0.00001f, 0.4f).From().SetEase(Ease.OutBack))
                .Join(Godray1.DOScale(0.00001f, 0.3f).From())
                .AppendInterval(0.7f)
                .Append(LockOpen.DOScale(0.00001f, 0.6f).SetEase(Ease.InBack))
                .AppendCallback(() => {
                    AudioManager.I.PlaySfx(Sfx.Win);
                })
                .Join(LockOpen.DORotate(new Vector3(0, 0, 360), 0.6f, RotateMode.FastBeyond360).SetRelative().SetEase(Ease.InCubic))
                .Join(Godray1.DOScale(0.00001f, 0.6f).SetEase(Ease.InCubic))
                .Join(Pedestal.DOScale(0.00001f, 1f).From().SetDelay(0.5f).SetEase(Ease.OutBack))
                .OnComplete(() => {
                    IsComplete = true;
                    pedestalTween.Play();
                });

            godraysTween = DOTween.Sequence().SetLoops(-1, LoopType.Restart)
                .Append(Godray0.DORotate(new Vector3(0, 0, 360), Godrays360Duration, RotateMode.FastBeyond360).SetRelative().SetEase(Ease.Linear))
                .Join(Godray1.DORotate(new Vector3(0, 0, -360), Godrays360Duration, RotateMode.FastBeyond360).SetRelative().SetEase(Ease.Linear));

            pedestalTween = Pedestal.DORotate(new Vector3(0, 360, 0), Pedestal360Duration, RotateMode.LocalAxisAdd)
                .SetEase(Ease.Linear).SetLoops(-1).Pause();

            // Wait a couple frames to allow Unity to load correctly
            yield return new WaitForSeconds(0.5f);

            LockClosed.gameObject.SetActive(true);
            showTween.Play();
        }

        void OnDestroy()
        {
            showTween.Kill();
            godraysTween.Kill();
            pedestalTween.Kill();
        }
    }
}