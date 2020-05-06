﻿using DG.Tweening;
using System;
using UnityEngine;

namespace EA4S.Egg
{
    public class EggRunLetter
    {
        LetterObjectView letterObject;
        Transform shadowTransform;

        Tween moveTweener;
        Tween rotationTweener;

        Vector3[] outPositions = new Vector3[2];

        int currentOutPosition;

        Vector3 lookCamera = new Vector3(0f, 180f, 0f);
        Vector3 lookLeft = new Vector3(0f, 270f, 0f);
        Vector3 lookRight = new Vector3(0f, 90f, 0f);

        Vector3 nextRotation;
        Vector3 nextPosition;
        float moveTime;

        Action moveCallback;
        Action rotationCallback;

        float lerpPositionValue;

        public EggRunLetter(GameObject letterObjectPrefab, GameObject shadowPrefab, ILivingLetterData letterData, Transform parent, Vector3 leftOutPosition, Vector3 rightOutPosition)
        {
            outPositions[0] = leftOutPosition;
            outPositions[1] = rightOutPosition;

            letterObject = UnityEngine.Object.Instantiate(letterObjectPrefab).GetComponent<LetterObjectView>();
            letterObject.transform.SetParent(parent);
            letterObject.Init(letterData);

            currentOutPosition = UnityEngine.Random.Range(0, 2);

            lerpPositionValue = currentOutPosition;

            letterObject.transform.position = outPositions[currentOutPosition];

            shadowTransform = UnityEngine.Object.Instantiate(shadowPrefab).transform;
            shadowTransform.SetParent(letterObject.transform);
            shadowTransform.localPosition = Vector3.zero;
            shadowTransform.localScale *= 0.7f;

            letterObject.Poof();
        }

        public void Run()
        {
            CalcNextRotationAndPosition();

            float delay = UnityEngine.Random.Range(4f, 8f);

            Rotate(nextRotation, 0.2f, delay, delegate ()
            {
                PlayRunAnimation();
                Move(nextPosition, moveTime, 0.2f, delegate () 
                {
                    PlayIdleAnimation();

                    Rotate(lookCamera, 0.2f, 0f, Run);
                });
            });
        }

        public void Stop()
        {
            if (moveTweener != null)
            {
                moveTweener.Kill();
            }
        }

        void Move(Vector3 position, float duration, float delay, Action callback)
        {
            moveCallback = callback;

            if (moveTweener != null) { moveTweener.Kill(); }

            moveTweener = letterObject.transform.DOMove(position, duration).OnComplete(delegate () { if (moveCallback != null) { moveCallback(); }  }).SetDelay(delay);
        }

        void Rotate(Vector3 eulerAngle, float duration, float delay, Action callback)
        {
            rotationCallback = callback;

            if (rotationTweener != null) { rotationTweener.Kill(); }

            rotationTweener = letterObject.transform.DORotate(eulerAngle, duration).OnComplete(delegate () { if (rotationCallback != null) { rotationCallback(); } }).SetDelay(delay);
        }

        void PlayIdleAnimation()
        {
            letterObject.SetState(LLAnimationStates.LL_idle);
        }

        void PlayRunAnimation()
        {
            letterObject.SetState(LLAnimationStates.LL_walking);
            letterObject.SetWalkingSpeed(LetterObjectView.RUN_SPEED);
        }

        public void DestroyRunLetter()
        {
            UnityEngine.Object.Destroy(letterObject.gameObject);
        }

        void CalcNextRotationAndPosition()
        {
            float newLerpPositionValue = UnityEngine.Random.Range(0f, 1f);

            moveTime = Mathf.Abs(newLerpPositionValue - lerpPositionValue) * 8f;

            nextRotation = (newLerpPositionValue > lerpPositionValue) ? lookRight : lookLeft;

            lerpPositionValue = newLerpPositionValue;

            nextPosition = Vector3.Lerp(outPositions[0], outPositions[1], lerpPositionValue);
        }
    }
}