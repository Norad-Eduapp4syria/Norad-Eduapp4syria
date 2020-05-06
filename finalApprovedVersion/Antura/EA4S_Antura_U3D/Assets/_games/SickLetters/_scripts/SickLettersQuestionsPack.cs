﻿using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

namespace EA4S.SickLetters
{
    public class SickLettersQuestionsPack : MonoBehaviour, IQuestionPack
    {
        LL_LetterData correctAnswers, question;

        public SickLettersQuestionsPack(LL_LetterData LLData)
        {
            question = correctAnswers = LLData;
        }

        public LL_LetterData getAnswer()
        {
            return correctAnswers;
        }


        public IEnumerable<ILivingLetterData> GetCorrectAnswers()
        {
            throw new NotImplementedException();
        }

        public ILivingLetterData GetQuestion()
        {
            return question;
        }

        public IEnumerable<ILivingLetterData> GetQuestions()
        {
            throw new NotImplementedException();
        }

        public IEnumerable<ILivingLetterData> GetWrongAnswers()
        {
            throw new NotImplementedException();
        }

    }
}