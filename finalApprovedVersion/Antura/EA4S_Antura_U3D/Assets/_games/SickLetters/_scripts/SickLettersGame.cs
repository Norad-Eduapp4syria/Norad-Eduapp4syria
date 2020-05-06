﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using TMPro;

namespace EA4S.SickLetters
{
    public enum Diacritic { Sokoun, Fatha, Dameh, Kasrah, None };

    public class SickLettersGame : MiniGame
    {
        public SickLettersLLPrefab LLPrefab;
        public SickLettersAntura antura;
        public SickLettersVase scale;
        public GameObject DropZonesGO;
        public Transform[] safeDropZones;
        public UnityEngine.Animation hole;
        public SickLettersTutorial tut;
        public bool lastMoveIsCorrect;

        public SickLettersCamera slCamera;
        public SickLettersGameManager manager;

        [HideInInspector]
        public MinigamesUIStarbar uiSideBar;
        [HideInInspector]
        public MinigamesUITimer uiTimer;
        //[HideInInspector]
        public int maxRoundsCount = 6, roundsCount = 1, wrongDraggCount = 0, correctMoveSequence = 0, currentStars = 0;
        [HideInInspector]
        public bool disableInput;

        public bool enableTutorial = true;
        public int gameDuration = 120 ,  targetScale = 10, maxWieght;
        public float vaseWidth = 5.20906f;
        public bool LLCanDance = false, with7arakat;
        public int numerOfWringDDs = 3;
        public string dotlessLetters = " إ إ أ ا ى ر س ل ص ع ه ح د م ك ط ئ ء ؤ و إ";
        public string LettersWithDots = "ض ث ق ف غ خ ج ش ي ب ت ن ة ظ ز ذ";

        public SickLettersDraggableDD[] Draggables;

        [HideInInspector]
        public SickLettersDropZone[] DropZones;


        [HideInInspector]
        public List<SickLettersDraggableDD> allWrongDDs = new List<SickLettersDraggableDD>();
        [HideInInspector]
        public QuestionsManager questionsManager;


        public IntroductionGameState IntroductionState { get; private set; }
        public QuestionGameState QuestionState { get; private set; }
        public PlayGameState PlayState { get; private set; }
        public ResultGameState ResultState { get; private set; }

        public QuestionsManager questionManager;

        protected override void OnInitialize(IGameContext context)
        {
            IntroductionState = new IntroductionGameState(this);
            QuestionState = new QuestionGameState(this);
            PlayState = new PlayGameState(this);
            ResultState = new ResultGameState(this);
            questionManager = new QuestionsManager();

            hole.gameObject.SetActive(false);

            manager = GetComponent<SickLettersGameManager>();            
            DropZones = DropZonesGO.GetComponentsInChildren<SickLettersDropZone>();
            tut = GetComponent<SickLettersTutorial>();

            scale.game = this;
            scale.transform.localScale = new Vector3(vaseWidth, scale.transform.localScale.y, scale.transform.localScale.z);
        }

        protected override IGameState GetInitialState()
        {
            return IntroductionState;
        }

        protected override IGameConfiguration GetConfiguration()
        {
            return SickLettersConfiguration.Instance;
        }

        public SickLettersDraggableDD createNewDragable(GameObject go)
        {
            return Instantiate(go).GetComponent<SickLettersDraggableDD>();
        }

        public Transform Poof(Transform t)
        {
            SickLettersConfiguration.Instance.Context.GetAudioManager().PlaySound(Sfx.Poof);
            var puffGo = GameObject.Instantiate(LLPrefab.GetComponent<LetterObjectView>().poofPrefab);
            puffGo.AddComponent<AutoDestroy>().duration = 2;
            puffGo.SetActive(true);
            puffGo.transform.position = t.position - Vector3.forward * 2;

            ParticleSystem[] PSs = puffGo.GetComponentsInChildren<ParticleSystem>();
            foreach(ParticleSystem ps in PSs)
                ps.scalingMode = ParticleSystemScalingMode.Hierarchy;

            puffGo.transform.localScale *= t.lossyScale.y * 1.2f/3f;//0.75f;

            return puffGo.transform;
        }

        public bool checkForNextRound()
        {

            if (checkSucess())
                return false;

            if (StateManager.CurrentState == ResultState)
                return false;

            int i = 0;
            foreach (SickLettersDraggableDD dd in LLPrefab.thisLLWrongDDs)
            {
                if (dd && !dd.deattached)
                    i++;
            }

            if (i == 0)
            {
                if (roundsCount == maxRoundsCount)
                {
                    this.SetCurrentState(ResultState);
                    return false;
                }

                roundsCount++;
                //Context.GetOverlayWidget().SetStarsScore(roundsCount / 2);
                LLPrefab.letterAnimator.SetBool("dancing", false);
                LLPrefab.letterAnimator.Play("LL_idle_1", -1);

                if (lastMoveIsCorrect)
                {
                    LLPrefab.letterView.DoHorray();
                    SickLettersConfiguration.Instance.Context.GetAudioManager().PlaySound(Sfx.LetterHappy);
                    LLPrefab.jumpOut(1.5f);
                }
                else
                    LLPrefab.jumpOut(0.5f);

                if (roundsCount == 1)
                {
                    Context.GetOverlayWidget().Initialize(true, true, false);
                    Context.GetOverlayWidget().SetClockDuration(gameDuration);
                    scale.counter = 0;

                    SickLettersConfiguration.Instance.Context.GetAudioManager().PlayMusic(Music.Theme10);
                }

                return true;
            }
            else
            {
                tut.doTutorial();
                return false;
            }

            
        }

        public bool checkSucess()
        {
            if (scale.counter == targetScale)
            {
                manager.sucess();
                return true;
            }
            else
                return false;
        }

        

        public void setDifficulty(float diff, int gameDuration, int targetScale, float vaseWidth, bool LLCanDance, bool with7arakat)
        {
            this.gameDuration = gameDuration;
            //Context.GetOverlayWidget().SetClockDuration(gameDuration);
            this.targetScale = targetScale;
            //Context.GetOverlayWidget().SetStarsThresholds((targetScale / 3), (targetScale * 2 / 3), targetScale);

            if (diff> 0.666f)
                scale.transform.localScale = new Vector3(vaseWidth, scale.transform.localScale.y, 7.501349f);
            else
                scale.transform.localScale = new Vector3(vaseWidth, scale.transform.localScale.y, scale.transform.localScale.z);

            this.LLCanDance = LLCanDance;
            this.with7arakat = with7arakat;
            numerOfWringDDs = targetScale/6;
        }

        float prevDiff = -1;
        public void processDifiiculties(float diff)
        {
            if (prevDiff == diff)
                return;
            else
                prevDiff = diff;


            if (diff < 0.333f)
                setDifficulty(diff, 120, 18, 5.20906f, false, false);
            else if (diff < 0.666f)
                setDifficulty(diff, 160, 30, 4.0f, false, true);
            else
                setDifficulty(diff, 180, 42, 3.0f, true, true);
        }

        public void onWrongMove()
        {
            Debug.Log("XXXXX "+Time.deltaTime);
            lastMoveIsCorrect = false;
            goodCommentCounter = correctMoveSequence = 0;
            AudioManager.I.PlayDialog("Keeper_Bad_" + UnityEngine.Random.Range(1,6));
            TutorialUI.MarkNo(scale.transform.position - Vector3.forward * 2 + Vector3.up, TutorialUI.MarkSize.Big);
            Context.GetAudioManager().PlaySound(Sfx.Lose);
        }


        int goodCommentCounter;
        public void onCorrectMove(SickLettersDraggableDD dd)
        {
            //AudioManager.I.PlayDialog("Keeper_Good_" + UnityEngine.Random.Range(1, 13));

            if (goodCommentCounter == 3 || !lastMoveIsCorrect)
            {
                AudioManager.I.PlayDialog("Keeper_Good_" + UnityEngine.Random.Range(1, 13));
                goodCommentCounter = 0;
            }

            scale.counter++;
            correctMoveSequence++;
            goodCommentCounter++;
            lastMoveIsCorrect = true;
            dd.deattached = true;

            

            if (!dd.touchedVase)
                dd.boxCollider.isTrigger = false;

            TutorialUI.MarkYes(scale.transform.position - Vector3.forward * 2 + Vector3.up, TutorialUI.MarkSize.Big);
            //game.Context.GetCheckmarkWidget().Show(true);
            Context.GetAudioManager().PlaySound(Sfx.OK);


            //int prevStarNum = game.currentStars;
            if (scale.counter > maxWieght)
            {
                Context.GetOverlayWidget().SetStarsThresholds((targetScale / 3), (targetScale * 2 / 3), targetScale);
                currentStars = (scale.counter / 2) / (targetScale / 6);
                Context.GetOverlayWidget().SetStarsScore(scale.counter/*game.currentStars*/);
            }



            dd.isInVase = true;
            dd.gameObject.tag = "Finish";

            checkForNextRound();
        }
    
    }

    
}
