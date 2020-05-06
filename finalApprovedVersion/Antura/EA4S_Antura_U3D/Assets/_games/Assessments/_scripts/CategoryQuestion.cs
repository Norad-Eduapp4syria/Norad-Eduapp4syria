using System;
using System.Collections.Generic;
using UnityEngine;

namespace EA4S.Assessment
{
    public class CategoryQuestion : IQuestion
    {
        private int correctCount;
        private GameObject gameObj;

        public CategoryQuestion( GameObject q, int correctAnswers)
        {
            gameObj = q;
            placeholdersSet = new List<GameObject>();
            this.correctCount = correctAnswers;
            var question = gameObj.AddComponent< QuestionBehaviour>();
            question.SetQuestion(this);
        }

        public GameObject gameObject
        {
            get
            {
                return gameObj;
            }
        }

        public ILivingLetterData Image()
        {
            throw new NotImplementedException( "Not implemented (on purpose)");
        }

        public ILivingLetterData LetterData()
        {
            return null;
        }

        public int PlaceholdersCount()
        {
            return placeholdersSet.Count;
        }

        private List< GameObject> placeholdersSet;

        public void TrackPlaceholder( GameObject gameObject)
        {
            placeholdersSet.Add( gameObject);
        }

        public IEnumerable< GameObject> GetPlaceholders()
        {
            return placeholdersSet;
        }

        private AnswerSet answerSet;
        public void SetAnswerSet( AnswerSet answerSet)
        {
            this.answerSet = answerSet;
        }

        public AnswerSet GetAnswerSet()
        {
            return answerSet;
        }
    }
}
