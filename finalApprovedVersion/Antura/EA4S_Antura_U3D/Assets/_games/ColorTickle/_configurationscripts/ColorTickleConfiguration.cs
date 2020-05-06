﻿namespace EA4S.ColorTickle
{
    public class ColorTickleConfiguration : IGameConfiguration
    {
        // Game configuration
        public IGameContext Context { get; set; }
        public IQuestionProvider Questions { get; set; }
        public float Difficulty { get; set; }

        /////////////////
        // Singleton Pattern
        static ColorTickleConfiguration instance;
        public static ColorTickleConfiguration Instance
        {
            get
            {
                if (instance == null)
                    instance = new ColorTickleConfiguration();
                return instance;
            }
        }
        /////////////////

        private ColorTickleConfiguration()
        {
            // Default values
            Questions = new ColorTickleLetterProvider();
            Context = new SampleGameContext();
            Difficulty = 0.5f;
        }

        public IQuestionBuilder SetupBuilder() {
            IQuestionBuilder builder = null;

            int nPacks = 10;
            int nCorrect = 1;

            var builderParams = new Teacher.QuestionBuilderParameters();
            builderParams.letterFilters.excludeDiacritics = true;
            builderParams.wordFilters.excludeDiacritics = true;
            builder = new RandomLettersQuestionBuilder(nPacks, nCorrect, parameters: builderParams);

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
