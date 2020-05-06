﻿using UnityEngine;
using System.Collections;
using System;

namespace EA4S.Scanner
{

    public class ScannerLivingLetter : MonoBehaviour
    {

        public enum LLStatus { None, Sliding, StandingOnBelt, RunningFromAntura, Lost, Won, Happy, Sad, Flying, Poofing, Falling };
        public GameObject livingLetter;
        public float slideSpeed = 2f;
        public float flightSpeed = 10f;
        public bool facingCamera;
        public LLStatus status = LLStatus.None;
        private float turnAngle;
        private Vector3 startingPosition;
        private Quaternion startingRotation;

        public Transform fallOffPoint;
        public Transform midPoint;

        public LetterObjectView letterObjectView;
        public GameObject rainbowJet;
        public float slidingTime;

//		public event Action <ScannerLivingLetter> onReset;
		public event Action <ScannerLivingLetter> onStartFallOff;
		public event Action <ScannerLivingLetter> onFallOff;
		public event Action <ScannerLivingLetter> onPassedMidPoint;
		public event Action <ScannerLivingLetter> onFlying;

		public BoxCollider bodyCollider;

		[HideInInspector]
		public bool gotSuitcase;
//        private Transform originalParent;
        private float fallOffX;
        private float midPointX;
        private bool passedMidPoint = false;

        void Awake()
        {
            status = LLStatus.None;
            letterObjectView = livingLetter.GetComponent<LetterObjectView>();
            startingPosition = transform.position;
            startingRotation = letterObjectView.transform.rotation;
        }

        public void Reset(bool stopCO = true)
        {
            if(stopCO)
                StopAllCoroutines();
            rainbowJet.SetActive(false);

			if (ScannerConfiguration.Instance.gameActive)
			{
				status = LLStatus.None;
				letterObjectView.Falling = false;
				letterObjectView.SetState(LLAnimationStates.LL_still);
				gotSuitcase = false;
	            letterObjectView.transform.rotation = startingRotation;
	            transform.position = startingPosition;

	            fallOffX = fallOffPoint.position.x;
	            midPointX = midPoint.position.x;
	            passedMidPoint = false;

	            turnAngle = facingCamera ? 180 : 0;
				gameObject.SetActive(true);

				gameObject.GetComponent<SphereCollider>().enabled = true; // enable feet collider
				bodyCollider.enabled = false; // disable body collider
			}
        }

		public void StartSliding()
		{
			letterObjectView.Falling = true;
			status = LLStatus.Sliding;
		}

        // Update is called once per frame
        void Update()
        {
            if (status == LLStatus.Sliding) 
			{
                transform.Translate(slideSpeed * Time.deltaTime, -slideSpeed * Time.deltaTime / 2, 0);
			}
			else if (status == LLStatus.StandingOnBelt)
			{
				transform.Translate(ScannerConfiguration.Instance.beltSpeed * Time.deltaTime,0,0);
            }
			else if (status == LLStatus.Flying) 
			{
                transform.Translate(Vector2.up * flightSpeed * Time.deltaTime);
            } 
			else if (status == LLStatus.Falling) 
			{
                transform.Translate(Vector2.down * flightSpeed * Time.deltaTime);
            }
				
			if (livingLetter.transform.position.x > fallOffX && status == LLStatus.StandingOnBelt) 
			{
                StartCoroutine(co_FallOff());
            }
			else if (livingLetter.transform.position.x > midPointX && !passedMidPoint) 
			{
                passedMidPoint = true;
                onPassedMidPoint(this);
            }
        }


        IEnumerator co_FlyAway()
        {
//            letterObjectView.DoSmallJump();
			onFlying(this);
			status = LLStatus.Happy;

			letterObjectView.DoSmallJump();            
			// Rotate in case not facing the camera
			StartCoroutine(RotateGO(livingLetter, new Vector3(0, 180, 0), 1f));
			yield return new WaitForSeconds(1f);

//			// building anticipation
//			letterObjectView.Crouching = true;
//			yield return new WaitForSeconds(1f);
//			letterObjectView.Crouching = false;

			// Starting flight
			letterObjectView.DoHorray();            
            yield return new WaitForSeconds(0.75f);
			status = LLStatus.Flying;
            rainbowJet.SetActive(true);
			letterObjectView.SetState(LLAnimationStates.LL_still);
            yield return new WaitForSeconds(2f);
//            Reset();
        }

        IEnumerator co_Lost()
        {
			if (status == LLStatus.StandingOnBelt)
			{
				status = LLStatus.Sad;
				letterObjectView.DoAngry();
            	yield return new WaitForSeconds(1.5f);
			}
			Debug.Log(status);
			if (status != LLStatus.Flying || status != LLStatus.Falling || status != LLStatus.None)
			{
				letterObjectView.Poof();
				yield return new WaitForSeconds(0.2f);
			}
			else
			{
				yield return new WaitForSeconds(2f);
			}
			transform.position = new Vector3(-100,-100,-100); // Move offscreen


        }

        IEnumerator co_FallOff()
        {
			gotSuitcase = false;
			status = LLStatus.None;
            onStartFallOff(this);
            letterObjectView.SetState(LLAnimationStates.LL_idle);
			letterObjectView.DoSmallJump();
            StartCoroutine(RotateGO(livingLetter, new Vector3(90, 90, 0), 1f));
            yield return new WaitForSeconds(0.5f);
            letterObjectView.Falling = true;
            status = LLStatus.Falling;

            yield return new WaitForSeconds(1f);

			onFallOff(this);

//            Reset();
        }

        void OnMouseUp()
        {
            letterObjectView.SetState(LLAnimationStates.LL_tickling);
        }

        public void RoundLost()
        {
			gotSuitcase = false;
            StopAllCoroutines();
//            letterObjectView.SetState(LLAnimationStates.LL_idle);
			StartCoroutine(co_Lost());
        }

        public void RoundWon()
        {
            StartCoroutine(co_FlyAway());
        }

        public void CorrectMove()
        {
            StopAllCoroutines();
            //			letterObjectView.SetState(LLAnimationStates.LL_idle);
            letterObjectView.DoHorray();
        }

        public void WrongMove()
        {
            StopAllCoroutines();
            letterObjectView.SetState(LLAnimationStates.LL_idle);
            letterObjectView.DoAngry();
        }


        IEnumerator RotateGO(GameObject go, Vector3 toAngle, float inTime)
        {
            var fromAngle = go.transform.rotation;
            var destAngle = Quaternion.Euler(toAngle);
            for (var t = 0f; t < 1; t += Time.deltaTime / inTime) {
                go.transform.rotation = Quaternion.Lerp(fromAngle, destAngle, t);
                yield return null;
            }
        }

        IEnumerator AnimateLL()
        {

            yield return new WaitForSeconds(1f);

//			letterObjectView.SetState(LLAnimationStates.LL_idle);

            int index = -1;
            LLAnimationStates[] animations =
            {
                LLAnimationStates.LL_idle,
                LLAnimationStates.LL_dancing
			};

            do {
                int oldIndex = index;
                do {
                    index = UnityEngine.Random.Range(0, animations.Length);
                } while (index == oldIndex);
                letterObjectView.SetState(animations[index]);
                yield return new WaitForSeconds(UnityEngine.Random.Range(2f, 4f));
            } while (status == LLStatus.StandingOnBelt);
        }

        void OnTriggerEnter(Collider other)
        {
            if (status == LLStatus.Sliding) 
			{
                if (other.tag == ScannerGame.TAG_BELT) 
				{
//                    transform.parent = other.transform;
                    status = LLStatus.StandingOnBelt;
                    gameObject.GetComponent<SphereCollider>().enabled = false; // disable feet collider
					bodyCollider.enabled = true; // enable body collider
                    letterObjectView.Falling = false;
                    StartCoroutine(RotateGO(livingLetter, new Vector3(0, turnAngle, 0), 1f));
                    StartCoroutine(AnimateLL());
                }
            }
        }

    }
}
