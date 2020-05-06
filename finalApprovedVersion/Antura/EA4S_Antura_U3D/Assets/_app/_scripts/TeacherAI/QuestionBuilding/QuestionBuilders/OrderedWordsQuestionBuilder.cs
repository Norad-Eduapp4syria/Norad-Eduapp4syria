﻿using EA4S.Teacher;
using System.Collections.Generic;

namespace EA4S
{
    public class OrderedWordsQuestionBuilder : IQuestionBuilder
    {
        // focus: Words
        // pack history filter: only 1 pack
        // journey: enabled

        private Db.WordDataCategory category;
        private QuestionBuilderParameters parameters;

        public OrderedWordsQuestionBuilder(Db.WordDataCategory category, QuestionBuilderParameters parameters = null)
        {
            if (parameters == null) parameters = new QuestionBuilderParameters();

            this.category = category;
            this.parameters = parameters;
        }

        public List<QuestionPackData> CreateAllQuestionPacks()
        {
            List<QuestionPackData> packs = new List<QuestionPackData>();
            packs.Add(CreateSingleQuestionPackData());
            return packs;
        }

        private QuestionPackData CreateSingleQuestionPackData()
        {
            var teacher = AppManager.I.Teacher;

            // Ordered words
            var words = teacher.wordAI.SelectData(
                 () => teacher.wordHelper.GetWordsByCategory(category, parameters.wordFilters),
                 new SelectionParameters(parameters.correctSeverity, getMaxData:true, useJourney:parameters.useJourneyForCorrect) 
               );

            // sort by id
            words.Sort((x, y) =>
                {
                    return x.Id.CompareTo(y.Id);
                }
            );

            if (ConfigAI.verboseTeacher)
            {
                string debugString = "Words: " + words.Count;
                foreach (var w in words) debugString += " " + w;
                UnityEngine.Debug.Log(debugString);
            }

            return QuestionPackData.CreateFromCorrect(null, words);
        }

    }
}