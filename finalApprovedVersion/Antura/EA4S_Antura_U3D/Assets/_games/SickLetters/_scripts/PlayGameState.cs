﻿using System;
using TMPro;
using UnityEngine;
using System.Collections;

namespace EA4S.SickLetters
{
    public class PlayGameState : IGameState
    {
        SickLettersGame game;
        Vector3 correctDotPos;

        float timer = 2, t = 0;
        int alarmIsTriggered;

        public PlayGameState(SickLettersGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            
            game.processDifiiculties(SickLettersConfiguration.Instance.Difficulty);

            timer = game.gameDuration;

            SickLettersConfiguration.Instance.Context.GetAudioManager().MusicEnabled = true;
            if (game.roundsCount == 0)
                SickLettersConfiguration.Instance.Context.GetAudioManager().PlayMusic(Music.Relax);
            else
            {
                SickLettersConfiguration.Instance.Context.GetAudioManager().PlayMusic(Music.Theme10);
                game.Context.GetOverlayWidget().Initialize(true, true, false);
                game.Context.GetOverlayWidget().SetClockDuration(game.gameDuration);
            }

            game.LLPrefab.jumpIn();

        }

        public void ExitState()
        {
            game.disableInput = true;
        }

        public void Update(float delta)
        {
            game.processDifiiculties(SickLettersConfiguration.Instance.Difficulty);


            if (game.roundsCount > 0)
            {
                timer -= delta;
                game.Context.GetOverlayWidget().SetClockTime(timer);
            }
            if (timer < 0)
            {
                AudioManager.I.StopSfx(Sfx.DangerClockLong);
                game.SetCurrentState(game.ResultState);
                AudioManager.I.PlayDialog("Keeper_TimeUp");
            }

            if (alarmIsTriggered == 0 && timer < 2)
            {
                alarmIsTriggered = 1;
                AudioManager.I.PlayDialog("Keeper_Time_"+UnityEngine.Random.Range(1,4));
            }
            if (alarmIsTriggered == 1 && timer < 4)
            {
                alarmIsTriggered = 2;
                AudioManager.I.PlaySfx(Sfx.DangerClockLong);
            }

            if (Input.GetKeyDown(KeyCode.A))
             {
                 t = 1;
                 game.LLPrefab.jumpOut();
            }

            correctDotPos = game.LLPrefab.correctDot.transform.TransformPoint(Vector3.Lerp(game.LLPrefab.correctDot.mesh.vertices[0], game.LLPrefab.correctDot.mesh.vertices[2], 0.5f));


            if(game.LLPrefab.correctDotCollider.transform.childCount == 0)
                game.LLPrefab.correctDotCollider.transform.position = correctDotPos;

            if(game.LLPrefab.letterView.Label.color.a > 0)
                game.LLPrefab.letterView.Label.color = new Color32(0, 0, 0, 0);

            Debug.DrawRay(correctDotPos, -Vector3.forward * 10, Color.red);
            Debug.DrawRay(correctDotPos, -Vector3.right * 10, Color.yellow);

        }

        

        public void UpdatePhysics(float delta)
        {
            
        }

            
        
    }
}
