﻿using UnityEngine;
using System.Collections;

namespace EA4S.MakeFriends
{
    public enum MakeFriendsVariation
    {
        EASY,
        MEDIUM,
        HARD
    }

    public class MakeFriendsConfiguration : IGameConfiguration
    {
        // Game configuration
        public IGameContext Context { get; set; }
        public IQuestionProvider Questions { get; set; }

        public float Difficulty { get; set; }

        public MakeFriendsVariation Variation
        {
            get
            {
                // GameManager Override
                if (MakeFriendsGame.Instance.overrideDifficulty)
                {
                    switch (MakeFriendsGame.Instance.difficultySetting)
                    {
                        case MakeFriendsVariation.EASY:
                            Difficulty = EASY_THRESHOLD;
                            break;

                        case MakeFriendsVariation.MEDIUM:
                            Difficulty = MEDIUM_THRESHOLD;
                            break;

                        case MakeFriendsVariation.HARD:
                            Difficulty = HARD_THRESHOLD;
                            break;
                    }
                }

                // SRDebugger Override
                if (SROptions.Current.MakeFriendsUseDifficulty)
                {
                    switch (SROptions.Current.MakeFriendsDifficulty)
                    {
                        case MakeFriendsVariation.EASY:
                            Difficulty = EASY_THRESHOLD;
                            break;

                        case MakeFriendsVariation.MEDIUM:
                            Difficulty = MEDIUM_THRESHOLD;
                            break;

                        case MakeFriendsVariation.HARD:
                            Difficulty = HARD_THRESHOLD;
                            break;
                    }
                }

                // Get Variation based on Difficulty
                var variation = default(MakeFriendsVariation);

                if (Difficulty < MEDIUM_THRESHOLD)
                {
                    variation = MakeFriendsVariation.EASY;
                }
                else if (Difficulty < HARD_THRESHOLD)
                {
                    variation = MakeFriendsVariation.MEDIUM;
                }
                else
                {
                    variation = MakeFriendsVariation.HARD;
                }

                return variation;
            }
        }

        public readonly static float EASY_THRESHOLD = 0f;
        public readonly static float MEDIUM_THRESHOLD = 0.3f;
        public readonly static float HARD_THRESHOLD = 0.7f;

           
        /////////////////
        // Singleton Pattern
        static MakeFriendsConfiguration instance;

        public static MakeFriendsConfiguration Instance
        {
            get
            {
                if (instance == null)
                    instance = new MakeFriendsConfiguration();
                return instance;
            }
        }

        /////////////////

        private MakeFriendsConfiguration()
        {
            // Default values
            // THESE SETTINGS ARE FOR SAMPLE PURPOSES, THESE VALUES MUST BE SET BY GAME CORE
            Questions = new MakeFriendsQuestionProvider();
            Context = new SampleGameContext();
            Difficulty = 0f;
        }

        public IQuestionBuilder SetupBuilder() {
            IQuestionBuilder builder = null;

            int nPacks = 10;
            int nMinCommonLetters = 1;
            int nMaxCommonLetters = 1;
            int nWrong = 5;
            int nWords = 2;

            var builderParams = new Teacher.QuestionBuilderParameters();
            builder = new CommonLettersInWordQuestionBuilder(nPacks, nMinCommonLetters, nMaxCommonLetters, nWrong, nWords, parameters: builderParams);

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