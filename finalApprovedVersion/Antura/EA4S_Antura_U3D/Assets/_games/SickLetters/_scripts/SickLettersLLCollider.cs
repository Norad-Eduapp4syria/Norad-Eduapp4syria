﻿using UnityEngine;
using System.Collections;
namespace EA4S.SickLetters
{
    public class SickLettersLLCollider : MonoBehaviour
    {

        LetterObjectView letterView;
        Transform thisTransform, origParent;
        Vector3 origLocalPos;

        void Start()
        {
            letterView = transform.root.GetComponent<LetterObjectView>();
            origLocalPos = transform.localPosition;
            thisTransform = transform;
            origParent = transform.parent;
            transform.parent = null;
        }

        void Update()
        {
            thisTransform.position = origParent.TransformPoint(origLocalPos);
            thisTransform.eulerAngles = new Vector3(0,105,-90);//origParent.TransformPoint(Vector3.zero);
            //thisTransform.localScale = origParent.TransformVector(Vector3.zero);
        }

        void OnMouseDown()
        {
            SickLettersConfiguration.Instance.Context.GetAudioManager().PlayLetterData(letterView.Data, true);
        }
    }
}