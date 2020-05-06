﻿using System;
using System.Collections.Generic;

namespace EA4S
{
    public class MakeFriendsQuestionPack : IQuestionPack
    {
        IEnumerable<ILivingLetterData> questions;
        ILivingLetterData questionWord1;
        ILivingLetterData questionWord2;
        IEnumerable<ILivingLetterData> wrongAnswers;
        IEnumerable<ILivingLetterData> correctAnswers;

        public MakeFriendsQuestionPack(ILivingLetterData questionWord1, ILivingLetterData questionWord2, IEnumerable<ILivingLetterData> wrongAnswers, IEnumerable<ILivingLetterData> correctAnswers)
        {
            this.questionWord1 = questionWord1;
            this.questionWord2 = questionWord2;
            this.questions = new List<ILivingLetterData>{ questionWord1, questionWord2 };
            this.wrongAnswers = wrongAnswers;
            this.correctAnswers = correctAnswers;
        }

        ILivingLetterData IQuestionPack.GetQuestion()
        {
            throw new Exception("This provider can not use this method");
        }

        IEnumerable<ILivingLetterData> IQuestionPack.GetWrongAnswers()
        {
            return wrongAnswers;
        }

        public IEnumerable<ILivingLetterData> GetCorrectAnswers()
        {
            return correctAnswers;
        }

        public IEnumerable<ILivingLetterData> GetQuestions()
        {
            return questions;
        }
    }
}

