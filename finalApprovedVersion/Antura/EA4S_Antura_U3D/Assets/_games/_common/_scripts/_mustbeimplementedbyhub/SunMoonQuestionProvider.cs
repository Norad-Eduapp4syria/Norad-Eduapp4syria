﻿using System;
using System.Collections.Generic;
using System.Linq;

namespace EA4S
{
    public class SunMoonQuestionProvider : IQuestionProvider
    {
        List<SampleQuestionPack> questions = new List<SampleQuestionPack>();

        int currentQuestion;

        public SunMoonQuestionProvider()
        {
            currentQuestion = 0;

            // 10 QuestionPacks
            for (int i = 0; i < 32; i++)
            {
                List<ILivingLetterData> correctAnswers = new List<ILivingLetterData>();
                List<ILivingLetterData> wrongAnswers = new List<ILivingLetterData>();

                var data = AppManager.I.Teacher.GetRandomTestLetterLL();

                if (data == null)
                    return;

                // sun
                var sunData = AppManager.I.DB.GetWordDataById("the_sun");
                var moonData = AppManager.I.DB.GetWordDataById("the_moon");

                ILivingLetterData sunWord = new LL_ImageData(sunData.GetId(), sunData);
                ILivingLetterData moonWord = new LL_ImageData(moonData.GetId(), moonData);

                if (data.Data.SunMoon == Db.LetterDataSunMoon.Sun)
                {
                    correctAnswers.Add(sunWord);
                    wrongAnswers.Add(moonWord);
                }
                else if (data.Data.SunMoon == Db.LetterDataSunMoon.Moon)
                {
                    correctAnswers.Add(moonWord);
                    wrongAnswers.Add(sunWord);
                }
                else
                    continue;

                var currentPack = new SampleQuestionPack(data, wrongAnswers, correctAnswers);
                questions.Add(currentPack);
            }
        }

        IQuestionPack IQuestionProvider.GetNextQuestion()
        {
            currentQuestion++;

            if (currentQuestion >= questions.Count)
                currentQuestion = 0;

            return questions[currentQuestion];
        }
    }
}
