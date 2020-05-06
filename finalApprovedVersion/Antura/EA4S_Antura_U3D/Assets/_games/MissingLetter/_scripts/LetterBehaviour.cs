﻿using UnityEngine;
using UnityEngine.Assertions;
using DG.Tweening;
using TMPro;
using System;
using System.Collections.Generic;
using ArabicSupport;
using DG.Tweening.Core;
using DG.Tweening.Plugins.Options;
using DG.Tweening.Plugins.Core.PathCore;

namespace EA4S.MissingLetter
{

    public class LetterBehaviour : MonoBehaviour
    {

        #region API

        /// <summary>
        /// reset position, rotation - disable callback, click action and light of LL
        /// </summary>
        public void Reset() {
            gameObject.transform.position = mv3StartPosition;
            gameObject.transform.rotation = Quaternion.identity;
            endTransformToCallback = null;
            onLetterClick = null;
            mbIsSpeaking = false;
            m_sInPhrase = "";
        }

        /// <summary>
        /// play animation passed by param
        /// </summary>
        /// <param name="_animation"> animation to play </param>
        public void PlayAnimation(LLAnimationStates _animation)
        {
            mLetter.SetState(_animation);
        }

        /// <summary>
        /// sets the positions of the LL, for its life action: start, center of scene, end
        /// </summary>
        /// <param name="_start"> start position, enter scene from </param>
        /// <param name="_center"> center of sceen, calculate offset from </param>
        /// <param name="_end"> end position, exit scene target </param>
        public void SetPositions(Vector3 _start, Vector3 _center, Vector3 _end)
        {
            mv3StartPosition = _start;
            mv3CenterPosition = _center;
            mv3EndPosition = _end;
        }

        /// <summary>
        /// refresh graphics text
        /// </summary>
        public void Refresh()
        {
            mLetter.Init(mLetterData);
        }

        /// <summary>
        /// start eneter scene action (calculate the offset by my pos and max pos), enable collider at arrive
        /// </summary>
        /// <param name="_idxPos"> my position </param>
        /// <param name="_length"> number of LL </param>
        public void EnterScene(int _idxPos = 0, int _length = 1)
        {
            Vector3 dir = (mv3CenterPosition - mv3StartPosition).normalized;
            Vector3 _GoalPos = CalculatePos(_idxPos, _length);
            endTransformToCallback += delegate { mCollider.enabled = true; };

            //move and rotate letter
            gameObject.transform.forward = dir;
            endTransformToCallback += delegate { RotateTo(Vector3.up * 180, 0.5f); };

            MoveTo(_GoalPos, 1);
        }

        /// <summary>
        /// start exit scene action, disable collider
        /// </summary>
        public void ExitScene()
        {
            endTransformToCallback += OnEndLifeCycle;
            mCollider.enabled = false;
            LightOff();

            Vector3 dir = (mv3EndPosition - mv3CenterPosition).normalized;

            Vector3 rot = new Vector3(0, Vector3.Angle(Vector3.forward, dir), 0);
            rot = (Vector3.Cross(Vector3.forward, dir).y < 0) ? -rot : rot;
            RotateTo(rot, 1f);

            MoveTo(mv3EndPosition, 1);
        }

        /// <summary>
        /// change the position in the current scene 
        /// </summary>
        /// <param name="_idxPos"> my new position </param>
        /// <param name="_length"> number of LL </param>
        /// <param name="_duration"> duration of action </param>
        public void ChangePos(int _idxPos, int _length, float _duration)
        {
            mCollider.enabled = false;
            Vector3 newPos = CalculatePos(_idxPos, _length);

            Vector3 dist = (gameObject.transform.position - newPos) / 2;

            Vector3 pivot = gameObject.transform.position - dist;

            //dist is only on x
            float radius = dist.x + 0.1f;

            float accuracy = 4f;
            for (int i = 1; i <= accuracy; ++i)
            {
                Vector3 p = Vector3.zero;
                p += pivot;
                p.x += Mathf.Cos(3.14f * (i / accuracy)) * radius;
                p.z += Mathf.Sin(3.14f * (i / accuracy)) * radius;

                positions.Add(p);
            }


            PlayAnimation(LLAnimationStates.LL_walking);
            mLetter.SetWalkingSpeed(1);
            mLetter.HasFear = true;

            transform.DOLookAt(positions[0], 1f);

            TweenerCore<Vector3, Path, PathOptions> value = transform.DOPath(positions.ToArray(), _duration, PathType.CatmullRom);
            value.OnWaypointChange(delegate (int wayPoint) {
                if (wayPoint < positions.Count)
                    transform.DOLookAt(positions[wayPoint], 1f);
            });
            value.OnComplete(delegate {
                transform.DOLookAt(transform.position + Vector3.back, 1f);
                positions.Clear();
                PlayAnimation(m_oDefaultIdleAnimation);
                mCollider.enabled = true;
            });
        }

        /// <summary>
        /// speak the LL data
        /// </summary>
        public void Speak()
        {
            if (mLetterData != null && !mbIsSpeaking)
            {
                mbIsSpeaking = true;
                if(m_sInPhrase != "")
                {
                    AudioManager.I.PlayPhrase(m_sInPhrase);
                }
                else if (mLetterData.DataType == LivingLetterDataType.Letter)
                {
                    AudioManager.I.PlayLetter(mLetterData.Id);
                }
                else
                {
                    AudioManager.I.PlayWord(mLetterData.Id);
                }
                StartCoroutine(Utils.LaunchDelay(0.8f, SetIsSpeaking, false));
            }
        }
        
        private void SetIsSpeaking(bool _isSpeaking)
        {
            mbIsSpeaking = _isSpeaking;
        }

        public void SetEnabledCollider(bool _enabled) {
            mCollider.enabled = _enabled;
        }

        public void SuggestLetter()
        {
            PlayAnimation(LLAnimationStates.LL_dancing);
        }

        public void SetInPhrase(string _phraseId)
        {
            m_sInPhrase = _phraseId;
        }

        public void LightOn()
        {
            if(m_oLetterLightInstance == null)
            {
                m_oLetterLightInstance = Instantiate(m_oLetterLightRef);
            }
            m_oLetterLightInstance.transform.parent = transform;
            m_oLetterLightInstance.transform.position = transform.position;
            m_oLetterLightInstance.SetActive(true);
        }

        public void LightOff()
        {
            if (m_oLetterLightInstance != null)
            {
                m_oLetterLightInstance.SetActive(false);
            }
        }


        #endregion

        #region PRIVATE_FUNCTION
        void Start()
        {
            mCollider = gameObject.GetComponent<Collider>();
            Assert.IsNotNull<Collider>(mCollider, "Collider Not Set in " + name);
            Assert.IsNotNull<GameObject>(m_oLetterLightRef, "LightObj Not Set in " + name);
            mCollider.enabled = false;
            mbIsSpeaking = false;
            mLetter.SetWalkingSpeed(1);
        }

        /// <summary>
        /// move the LL with walking animation, idle at end
        /// </summary>
        /// <param name="_position"> target position </param>
        /// <param name="_duration"> time for action </param>
        void MoveTo(Vector3 _position, float _duration)
        {
            PlayAnimation(LLAnimationStates.LL_walking);
            mLetter.SetWalkingSpeed(1);

            if (moveTweener != null)
            {
                moveTweener.Kill();
            }

            moveTweener = transform.DOLocalMove(_position, _duration).OnComplete(
                delegate () {
                    PlayAnimation(m_oDefaultIdleAnimation);
                    if (endTransformToCallback != null)
                        endTransformToCallback();
                });
        }

        /// <summary>
        /// rotate the LL
        /// </summary>
        /// <param name="_rotation"> rotation in eulerian angle </param>
        /// <param name="_duration"> duration of rotation </param>
        void RotateTo(Vector3 _rotation, float _duration)
        {
            if (rotationTweener != null)
            {
                rotationTweener.Kill();
            }
            rotationTweener = transform.DORotate(_rotation, _duration);
        }

        void OnEndLifeCycle()
        {
            Reset();

            if (onLetterBecameInvisible != null)
            {
                onLetterBecameInvisible(gameObject);
            }
        }

        void OnMouseDown()
        {
            Speak();

            if (onLetterClick != null)
            {
                StartCoroutine(Utils.LaunchDelay(0.2f, onLetterClick, mLetterData.Id));
                mCollider.enabled = false;
            }
        }

        /// <summary>
        /// calculate the position by center sceen and offset of index in length
        /// </summary>
        /// <param name="_idxPos"> my index position </param>
        /// <param name="_length"> number of LL </param>
        /// <returns></returns>
        private Vector3 CalculatePos(int _idxPos, int _length)
        {
            float _zeroPosX = mv3CenterPosition.x + 1.0f; // +1.0 beacuse we have some UI Widget at the left

            if (_length % 2 == 0)
            {
                _zeroPosX += mfDistanceBetweenLetters / 2;
            }

            Vector3 _GoalPos;

            if (_idxPos == 0)
            {
                _GoalPos = new Vector3(_zeroPosX, mv3CenterPosition.y, mv3CenterPosition.z);
            }
            else
            {
                int _n = ((_idxPos + 1) / 2);
                if (_idxPos % 2 != 0)
                {
                    _GoalPos = new Vector3(_zeroPosX - (_n * mfDistanceBetweenLetters), mv3CenterPosition.y, mv3CenterPosition.z);
                }
                else
                {
                    _GoalPos = new Vector3(_zeroPosX + (_n * mfDistanceBetweenLetters), mv3CenterPosition.y, mv3CenterPosition.z);
                }
            }
            return _GoalPos;
        }
        #endregion

        #region VARS
        private List<Vector3> positions = new List<Vector3>();

        private Tweener moveTweener;
        private Tweener rotationTweener;
        private Collider mCollider;

        private bool mbIsSpeaking;
        private string m_sInPhrase = "";

        public ILivingLetterData LetterData
        {
            get
            {
                return mLetterData;
            }
            set
            {
                mLetterData = value;
                mLetter.Init(value);
            }
        }

        public LetterObjectView mLetter;

        [SerializeField]
        private GameObject m_oLetterLightRef;
        private GameObject m_oLetterLightInstance;

        [HideInInspector]
        public ILivingLetterData mLetterData;
        [HideInInspector]
        public Action endTransformToCallback;
        [HideInInspector]
        public Action<string> onLetterClick;
        [HideInInspector]
        public event Action<GameObject> onLetterBecameInvisible;


        //public for pool
        [HideInInspector]
        public float mfDistanceBetweenLetters;
        [HideInInspector]
        public Vector3 mv3StartPosition;
        [HideInInspector]
        public Vector3 mv3CenterPosition;
        [HideInInspector]
        public Vector3 mv3EndPosition;


        public LLAnimationStates m_oDefaultIdleAnimation { get; set; }
        #endregion

    }
}
