﻿using UnityEngine;
using UnityEngine.UI;
using ModularFramework.Helpers;

namespace EA4S.ColorTickle
{
    public class PlayGameState : IGameState
    {
        #region PRIVATE MEMBERS

        ColorTickleGame game;
        GameObject m_CurrentLetter;

		int m_MaxLives;
        int m_Lives;
        int m_Rounds;
        int m_iRoundsSuccessfull;

        Button m_PercentageLetterColoredButton;
        float m_PercentageLetterColored;
        

        ColorsUIManager m_ColorsUIManager;

        // LL components
        LetterObjectView m_LetterObjectView;
        TMPTextColoring m_TMPTextColoringLetter;
        SurfaceColoring m_SurfaceColoringLetter;
        ColorTickle_LLController m_LLController;
        HitStateLLController m_HitStateLLController;

        // LL vanishing vars
        bool m_bLLVanishing = false;
        float m_fTimeToDisappear = 3f;
        float m_fDisappearTimeProgress = 0;

        #endregion

        public PlayGameState(ColorTickleGame game)
        {
            this.game = game;
        }

        public void EnterState()
        {
            m_Rounds = game.rounds;
			m_MaxLives = game.lives; //max number of lives is already setted in the game according to difficulty
            m_iRoundsSuccessfull = 0;

			//Init ColorCanvas and PercentageLetterColoredButton
			InitGameUI();

			ResetState ();

            game.anturaController.OnStateChanged += AnturaInteractions;
            
            //Init the first letter
            m_CurrentLetter = game.myLetters[m_Rounds - 1];
			m_CurrentLetter.gameObject.SetActive (true);         
            InitLetter();
        }

        public void ExitState()
        {
        }

        public void Update(float delta)
        {
            if (m_Rounds <= 0)
            {               
                game.SetCurrentState(game.ResultState);
            }
            else
            {
                CalcPercentageLetterColored();

                if (m_PercentageLetterColoredButton != null)
                {
                    m_PercentageLetterColoredButton.GetComponentInChildren<Text>().text = Mathf.FloorToInt(m_PercentageLetterColored) + "%";
                }

                if(m_bLLVanishing) //if the LL is about to vanish
                {
                    m_fDisappearTimeProgress += Time.deltaTime;

                    //if(m_LetterObjectView.GetState()!=LLAnimationStates.LL_dancing)//when the dance is finished ---> DoDancingWin/Lose do not exit from this state
                    if (m_fDisappearTimeProgress >= m_fTimeToDisappear)//after the given time is reached
                    {
                        m_LetterObjectView.Poof(); //LL vanishes

                        //stop win particle
                        foreach (var particles in game.winParticle.GetComponentsInChildren<ParticleSystem>(true))
                        {
                            particles.Stop();
                        }
                        game.winParticle.SetActive(false);

                        m_bLLVanishing = false;
                        m_fDisappearTimeProgress = 0;

                        //just for possible reusing of the LL renable components
                        EnableLetterComponents();

                        m_CurrentLetter.SetActive(false);

                        --m_Rounds;
                        if (m_Rounds > 0) //activate next LL
                        {
                            ResetState();
                            m_ColorsUIManager.ChangeButtonsColor();
                            m_CurrentLetter = game.myLetters[m_Rounds - 1];
                            m_CurrentLetter.gameObject.SetActive(true);
                            // Initialize the next letter
                            InitLetter();
                        }
                    }
                }
                else if (m_PercentageLetterColored >= 100 || m_Lives <=0) //else check for letter completed
                {
                    game.anturaController.ForceAnturaToGoBack();//we completed the letter, antura turn back
                    m_bLLVanishing = true; //LL is about to disappear

                    //disable color components to avoid input in this phase (or ignore input using touch manager?)
                    DisableLetterComponents();

                    AudioManager.I.PlayLetter(m_LetterObjectView.Data.Id);//play letter pronounce again

                    m_SurfaceColoringLetter.Reset();//reset to clean surface of LL (maybe make a function to clean it rather than reinitialize it)

                    //LL does win or lose animation 
                    if(m_PercentageLetterColored >= 100)
                    {
                        m_iRoundsSuccessfull += 1;
                        game.starsAwarded = Mathf.CeilToInt(m_iRoundsSuccessfull / 2f);
                        game.gameUI.SetStarsScore(game.starsAwarded);

                        m_LetterObjectView.DoHorray();
                        AudioManager.I.PlaySfx(Sfx.Win);

                        //play win particle
                        game.winParticle.SetActive(true);
                        foreach (var particles in game.winParticle.GetComponentsInChildren<ParticleSystem>(true))
                        {
                            particles.Play();
                        }

                    }
                    else if (m_Lives <= 0)
                    {
                        /*m_LetterObjectView.DoDancingLose(); //this just set trigger for lose on dancing animation
                        m_LetterObjectView.SetState(LLAnimationStates.LL_dancing);*/
                        m_LetterObjectView.DoAngry();
                        AudioManager.I.PlaySfx(Sfx.Lose);
                    }                   
                }
            }
        }


        public void UpdatePhysics(float delta)
        {
        }

        #region PRIVATE FUNCTIONS

		private void ResetState(){		
			m_Lives = m_MaxLives;
            game.gameUI.SetLives(m_MaxLives);
            m_PercentageLetterColored = 0;
            if (m_PercentageLetterColoredButton != null)
            {
                m_PercentageLetterColoredButton.GetComponentInChildren<Text>().text = "0 %";
            }        
        }

		private void InitGameUI()
		{
            game.gameUI = game.Context.GetOverlayWidget();
            game.gameUI.Initialize(true, false, true);
            game.gameUI.SetMaxLives(game.lives);
            game.gameUI.SetStarsThresholds(1,2,3);
            game.gameUI.SetStarsScore(0);

            game.colorsCanvas.gameObject.SetActive(true);
            m_ColorsUIManager = game.colorsCanvas.GetComponentInChildren<ColorsUIManager>();
            m_ColorsUIManager.SetBrushColor += SetBrushColor;

            if (m_ColorsUIManager.percentageColoredButton != null)
            {
                m_PercentageLetterColoredButton = m_ColorsUIManager.percentageColoredButton;
            }
		}

		private void InitLetter()
		{
            m_LetterObjectView = m_CurrentLetter.GetComponent<LetterObjectView>();

            m_TMPTextColoringLetter = m_CurrentLetter.GetComponent<TMPTextColoring>();
            m_SurfaceColoringLetter = m_CurrentLetter.GetComponent<SurfaceColoring>();

            m_LLController = m_CurrentLetter.GetComponent<ColorTickle_LLController>();
            m_LLController.movingToDestination = true;

            m_HitStateLLController = m_CurrentLetter.GetComponent<HitStateLLController>();
            m_HitStateLLController.LoseLife += LoseLife;

            m_LLController.OnDestinationReached += delegate () { AudioManager.I.PlayLetter(m_LetterObjectView.Data.Id); };//play audio on destination


            m_HitStateLLController.EnableAntura += EnableAntura;
            //game.anturaController.targetToLook = m_CurrentLetter.transform; //make antura look at the LL on rotations

            SetBrushColor(m_ColorsUIManager.defaultColor);     
        }

        private void EnableLetterComponents()
        {
            m_TMPTextColoringLetter.enabled = true;
            m_SurfaceColoringLetter.enabled = true;
            m_HitStateLLController.enabled = true;
        }

        private void DisableLetterComponents()
        {
            m_TMPTextColoringLetter.enabled = false;
            m_SurfaceColoringLetter.enabled = false;
            m_HitStateLLController.enabled = false;
        }

        private void SetBrushColor(Color color)
        {
            m_TMPTextColoringLetter.brush.SetBrushColor(color); //give the exact color to the letter 

            Color brushColor = color;
            brushColor.r += (1 - color.r) * 0.5f;
            brushColor.g += (1 - color.g) * 0.5f;
            brushColor.b += (1 - color.b) * 0.5f;
            m_SurfaceColoringLetter.brush.SetBrushColor(brushColor); //give the desaturated color to the body
        }

        private void LoseLife()
        {
            //--TODO maybe this can be better if the LL controller handles all the LL states rather than just the hits
            if(game.anturaController.anturaState!=AnturaContollerState.BARKING) //if the life loss wasn't caused inside Antura disruption
            {
                game.anturaController.ForceAnturaToGoBack();//we tickled the letter, antura turn back
            }
            else //if it was we need also to overwrite the LL tickling animation
            {
                m_LetterObjectView.SetState(LLAnimationStates.LL_walking); //keep running in fear instead of tickling
            }
            //--

            m_Lives--;
            
            game.gameUI.SetLives(m_Lives);
       
        }


        private void CalcPercentageLetterColored()
        {
            float percentageRequiredToWin = m_TMPTextColoringLetter.percentageRequiredToWin;
            m_PercentageLetterColored = ((m_TMPTextColoringLetter.GetRachedCoverage() * 100.0f) / percentageRequiredToWin) * 100.0f;
            if (m_PercentageLetterColored > 100.0f)
            {
                m_PercentageLetterColored = 100.0f;
            }
        }

        private void EnableAntura()
        { 
            game.anturaController.TryLaunchAnturaDisruption();
        }

        private void AnturaReachedLetter()
        {  
            m_LetterObjectView.SetState(LLAnimationStates.LL_walking);
            m_LetterObjectView.HasFear = true;
            m_LetterObjectView.SetWalkingSpeed(1);
            //m_LetterObjectView.Crouching = true;
        }

        private void AnturaGoingAway()
        {
            m_LetterObjectView.SetState(LLAnimationStates.LL_still);
            m_LetterObjectView.HasFear = false;
            m_LetterObjectView.SetWalkingSpeed(0);
            //m_LetterObjectView.Crouching = false;
        }

        /// <summary>
        /// This is called by Antura controller with the change state event to apply any
        /// needed interactions.
        /// </summary>
        /// <param name="eState">Current state for Antura</param>
        private void AnturaInteractions( AnturaContollerState eState)
        {
            if (eState == AnturaContollerState.BARKING) //Antura scared the LL
            {
                AnturaReachedLetter();
            }
            else if (eState == AnturaContollerState.COMINGBACK) //Antura is returning to his place
            {
                if(m_LetterObjectView.GetState()!=LLAnimationStates.LL_tickling) //if the LL is tickling antura didn't reach it (fix)
                {
                    AnturaGoingAway();
                }
                
            }
        }

        #endregion
    }

}

#region DEPRECATED FUNCTIONS 

//private void TrackBrushDistanceCovered()
//{
//    if (m_HitState == eHitState.HIT_LETTERINSIDE_AND_BODY)
//    {
//        // if we already painted the letter the frame before
//        Vector2 newBrushPosition = new Vector2(Input.mousePosition.x, Input.mousePosition.y);
//        Vector2 diffBrushPositions = newBrushPosition - m_LastBrushPosition;
//        m_LastBrushPosition = newBrushPosition;
//        m_BurshDistanceCovered += diffBrushPositions.magnitude;
//        //Debug.Log("Distance Covered:" + m_BurshDistanceCovered);
//    }
//    else
//    {
//        // if we didn't painted the letter the frame before
//        m_LastBrushPosition = new Vector2(Input.mousePosition.x, Input.mousePosition.y);
//    }
//}

//private void CheckBrushVelocity(float delta)
//{
//    m_DelayCheckVelocity += delta;
//    // Every 0.5f seconds we check if the velocity of the brush is more than "m_BrushLimitVelocity" (pixel/seconds)
//    // if it's more we tickles the letter
//    if (m_DelayCheckVelocity >= 0.5f)
//    {
//        //Debug.Log("Distance Covered after 0.5s:" + m_BurshDistanceCovered);
//        //Debug.Log("Velocity in pixel:" + m_BurshDistanceCovered / 0.5f);
//        if (m_BurshDistanceCovered / 0.5f >= game.brushLimitVelocity)
//        {
//            TicklesLetter();
//        }
//        m_BurshDistanceCovered = 0.0f;
//        m_DelayCheckVelocity = 0.0f;
//    }
//}

#endregion