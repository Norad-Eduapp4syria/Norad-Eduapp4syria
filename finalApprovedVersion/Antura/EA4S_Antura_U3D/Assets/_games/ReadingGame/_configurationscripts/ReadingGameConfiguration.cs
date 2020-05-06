﻿namespace EA4S.ReadingGame
{
    public enum ReadingGameVariation : int
    {
        ReadAndAnswer = 1,
        AlphabetSong = 2,
    }

    public class ReadingGameConfiguration : IGameConfiguration
    {
        // Game configuration
        public IGameContext Context { get; set; }
        public IQuestionProvider Questions { get; set; }
        public ReadingGameVariation Variation { get; set; }

        public float Difficulty { get; set; }

        public int GetDiscreteDifficulty(int maximum)
        {
            int d = (int) Difficulty * (maximum + 1);

            if (d > maximum)
                return maximum;
            return d;
        }

        /////////////////
        // Singleton Pattern
        static ReadingGameConfiguration instance;
        public static ReadingGameConfiguration Instance
        {
            get
            {
                if (instance == null)
                    instance = new ReadingGameConfiguration();
                return instance;
            }
        }
        /////////////////

        private ReadingGameConfiguration()
        {
            // Default values
            // THESE SETTINGS ARE FOR SAMPLE PURPOSES, THESE VALUES MUST BE SET BY GAME CORE
            Questions = new SampleReadingGameQuestionProvider();
            Variation = ReadingGameVariation.ReadAndAnswer;
            //Variation = ReadingGameVariation.AlphabetSong;

            Context = new SampleGameContext();
            Difficulty = 0.0f;
        }

        public IQuestionBuilder SetupBuilder() {
            IQuestionBuilder builder = null;

            var builderParams = new Teacher.QuestionBuilderParameters();
            switch (Variation)
            {
                case ReadingGameVariation.AlphabetSong:
                    builder = new EmptyQuestionBuilder();
                    break;
                case ReadingGameVariation.ReadAndAnswer:
                    builderParams.wordFilters.excludeColorWords = true;
                    builderParams.wordFilters.requireDrawings = true;
                    builderParams.phraseFilters.requireAnswersOrWords = true;
                    builder = new WordsInPhraseQuestionBuilder(nPacks: 10, nCorrect: 1, nWrong: 6, usePhraseAnswersIfFound: true, parameters: builderParams);
                    break;
            } 
            return builder;
        }

        public MiniGameLearnRules SetupLearnRules()
        {
            var rules = new MiniGameLearnRules();
            // example: a.minigameVoteSkewOffset = 1f;
            return rules;
        }

    }
}
