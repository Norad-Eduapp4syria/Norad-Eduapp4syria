﻿using UnityEngine;
using System.Collections.Generic;
using System;
using ModularFramework.Helpers;

namespace EA4S
{
    public class IntroFactory : MonoBehaviour {

        public event System.Action<ILivingLetterData, bool> onDropped;

        public LettersWalkableArea walkableArea;
        public AnturaRunnerController antura;

        public LetterObjectView livingLetterPrefab;
        public GameObject puffPrefab;

        public int MaxConcurrentLetters = 5;

        protected List<IntroStrollingLetter> letters = new List<IntroStrollingLetter>();
        List<GameObject> letterGOs = new List<GameObject>();

        //Queue<ILivingLetterData> toAdd = new Queue<ILivingLetterData>();

        Queue<IntroStrollingLetter> toDestroy = new Queue<IntroStrollingLetter>();
        float destroyTimer = 0;

        [HideInInspector]
        public bool StartSpawning = false;

        public void GetNearLetters(List<IntroStrollingLetter> output, Vector3 position, float radius)
        {
            for (int i = 0, count = letters.Count; i < count; ++i)
            {
                if (Vector3.Distance(letters[i].transform.position, position) < radius)
                {
                    output.Add(letters[i]);
                }
            }
        }

        //public void AddLivingLetter(ILivingLetterData letter)
        //{
        //    toAdd.Enqueue(letter);
        //}

        public void Clean()
        {
            //toAdd.Clear();

            foreach (var l in letters)
                toDestroy.Enqueue(l);

            letters.Clear();
            letterGOs.Clear();
        }

        protected virtual LetterObjectView SpawnLetter()
        {
            // Spawn!
            LetterObjectView letterObjectView = Instantiate(livingLetterPrefab);
            letterObjectView.gameObject.SetActive(true);
            letterObjectView.transform.SetParent(transform, true);

            Vector3 newPosition = walkableArea.GetFurthestSpawn(letterGOs); // Find isolated spawn point

            letterObjectView.transform.position = newPosition;
            letterObjectView.transform.rotation = Quaternion.Euler(0, UnityEngine.Random.value * 360, 0);
            //letterObjectView.Init(toAdd.Dequeue());
            letterObjectView.Init(AppManager.I.Teacher.GetAllTestLetterDataLL().GetRandomElement());

            letterObjectView.gameObject.AddComponent<Rigidbody>().isKinematic = true;

            foreach (var collider in letterObjectView.gameObject.GetComponentsInChildren<Collider>())
                collider.isTrigger = true;

            var characterController = letterObjectView.gameObject.AddComponent<CharacterController>();
            characterController.height = 6;
            characterController.center = Vector3.up * 3;
            characterController.radius = 1.5f;
            letterObjectView.gameObject.AddComponent<LetterCharacterController>();

            var livingLetter = letterObjectView.gameObject.AddComponent<IntroStrollingLetter>();
            livingLetter.factory = this;

            var pos = letterObjectView.transform.position;
            pos.y = 10;
            letterObjectView.transform.position = pos;

            letters.Add(livingLetter);
            letterGOs.Add(livingLetter.gameObject);

            livingLetter.onDropped += (result) =>
            {
                if (result)
                {
                    letters.Remove(livingLetter);
                    letterGOs.Remove(livingLetter.gameObject);
                    toDestroy.Enqueue(livingLetter);
                }

                if (onDropped != null)
                    onDropped(letterObjectView.Data, result);
            };

            return letterObjectView;
        }

        void Update()
        {
            //if (toAdd.Count > 0)
            if (StartSpawning)
            {
                if (letters.Count < MaxConcurrentLetters)
                {
                    SpawnLetter();
                }
            }

            //if (toDestroy.Count > 0)
            //{
            //    destroyTimer -= Time.deltaTime;

            //    if (destroyTimer <= 0)
            //    {
            //        destroyTimer = 0.1f;

            //        var puffGo = GameObject.Instantiate(puffPrefab);
            //        puffGo.AddComponent<AutoDestroy>().duration = 2;
            //        puffGo.SetActive(true);

            //        var t = toDestroy.Dequeue();
            //        puffGo.transform.position = t.transform.position + Vector3.up * 3;
            //        Destroy(t.gameObject);
            //    }
            //}

        }


    }
}
