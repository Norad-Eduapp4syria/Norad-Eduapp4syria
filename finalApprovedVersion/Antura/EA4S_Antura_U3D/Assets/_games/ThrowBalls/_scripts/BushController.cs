﻿using UnityEngine;
using System.Collections;

namespace EA4S.ThrowBalls
{
    public class BushController : MonoBehaviour
    {
        public LetterController letterController;

        // Use this for initialization
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {

        }

        public void Enable()
        {
            gameObject.SetActive(true);
        }

        public void Disable()
        {
            gameObject.SetActive(false);
        }

        public void Reset()
        {
            GameObject letter = letterController.gameObject;
            transform.position = new Vector3(letter.transform.position.x, letter.transform.position.y + 3.4f, letter.transform.position.z - 2.5f);
        }
    }
}

