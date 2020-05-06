﻿using UnityEngine;
using System.Collections.Generic;
namespace EA4S.MixedLetters
{
    public class IntroductionGameState : IGameState
    {
        MixedLettersGame game;

        private float anturaEnterTimer;
        private bool anturaEntered = false;
        private bool anturaBarked = false;
        private float anturaExitTimer;
        private bool anturaExited = false;

        private bool isAnturaEnterTimerActivated = false;

        private float timePerRound = 30f;

        public IntroductionGameState(MixedLettersGame game)
        {
            this.game = game;

            float difficulty = MixedLettersConfiguration.Instance.Difficulty;

            if (difficulty <= 0.25f)
            {
                timePerRound = 60f;
            }

            else if (difficulty <= 0.5f)
            {
                timePerRound = 45f;
            }

            else if (difficulty <= 0.75f)
            {
                timePerRound = 30f;
            }

            else
            {
                timePerRound = 15f;
            }
        }

        private void OnQuestionOver()
        {
            isAnturaEnterTimerActivated = true;
        }

        public void EnterState()
        {
            anturaEnterTimer = MixedLettersConfiguration.Instance.Variation == MixedLettersConfiguration.MixedLettersVariation.Spelling ? 3.25f : 1.5f;
            anturaEntered = false;
            anturaBarked = false;
            anturaExitTimer = Random.Range(0.75f, 1.5f);
            anturaExited = false;

            isAnturaEnterTimerActivated = false;

            game.GenerateNewWord();
            game.SayQuestion(OnQuestionOver);

            VictimLLController.instance.HideVictoryRays();
            VictimLLController.instance.Reset();
            VictimLLController.instance.Enable();

            Vector3 victimLLPosition = VictimLLController.instance.transform.position;
            victimLLPosition.x = Random.Range(0, 40) % 2 == 0 ? 0.5f : -0.5f;
            VictimLLController.instance.SetPosition(victimLLPosition);

            game.roundNumber++;

            if (game.roundNumber == 1)
            {
                MinigamesUI.Init(MinigamesUIElement.Timer | MinigamesUIElement.Starbar);
                MinigamesUI.Timer.Setup(timePerRound);
            }

            MinigamesUI.Timer.Rewind();
        }

        public void ExitState()
        {
        }

        public void Update(float delta)
        {
            if (isAnturaEnterTimerActivated)
            {
                anturaEnterTimer -= delta;
            }

            if (anturaEnterTimer < 0.25f && !anturaBarked)
            {
                MixedLettersConfiguration.Instance.Context.GetAudioManager().PlaySound(Sfx.DogBarking);
                VictimLLController.instance.LookTowardsAntura();
                anturaBarked = true;
            }

            if (anturaEnterTimer < 0 && !anturaEntered)
            {
                AnturaController.instance.Enable();
                AnturaController.instance.EnterScene(OnFightBegan, OnAnturaExitedScene);
                anturaEntered = true;
            }
        }

        private void OnAnturaExitedScene()
        {
            game.SetCurrentState(game.PlayState);
        }

        public void UpdatePhysics(float delta)
        {
        }

        public void OnFightBegan()
        {
            AnturaController.instance.SetPosition(VictimLLController.instance.transform.position);
            AnturaController.instance.Disable();
            VictimLLController.instance.Disable();
            ParticleSystemController.instance.Enable();
            ParticleSystemController.instance.SetPosition(VictimLLController.instance.transform.position);
            SeparateLettersSpawnerController.instance.SetPosition(VictimLLController.instance.transform.position);
            SeparateLettersSpawnerController.instance.SpawnLetters(game.lettersInOrder, OnFightEnded);
        }

        public void OnFightEnded()
        {
            AnturaController.instance.Enable();
            AnturaController.instance.SetPositionWithOffset(VictimLLController.instance.transform.position, new Vector3(0, 0, 1f));
            ParticleSystemController.instance.Disable();
            anturaExited = true;
        }
    }
}