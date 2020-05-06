﻿#if UNITY_EDITOR
using UnityEngine;
using UnityEditor;

namespace EA4S.Db.Management
{
    public class DatabaseLoader : MonoBehaviour
    {
        public DatabaseInputData inputData;
        private Database database;
        public bool verbose;

        public void RecreateDatabase()
        {
            CreateDatabaseAsset.CreateAssets("Assets/Resources/" + DatabaseManager.STATIC_DATABASE_NAME+"/", DatabaseManager.STATIC_DATABASE_NAME);
            this.database = Database.LoadDB(DatabaseManager.STATIC_DATABASE_NAME);
        }

        public void CopyCurrentDatabaseForTesting()
        {
            this.database = Database.LoadDB(DatabaseManager.STATIC_DATABASE_NAME);

            var test_db = Database.LoadDB(DatabaseManager.STATIC_DATABASE_NAME_TEST);
            if (!test_db.HasTables())
            {
                CreateDatabaseAsset.CreateAssets("Assets/Resources/" + DatabaseManager.STATIC_DATABASE_NAME_TEST+"/", DatabaseManager.STATIC_DATABASE_NAME_TEST);
                test_db = Database.LoadDB(DatabaseManager.STATIC_DATABASE_NAME_TEST);
            }

            {
                var table = test_db.GetLetterTable();
                table.Clear();
                table.AddRange(this.database.GetLetterTable().GetValuesTyped());
            }

            {
                var table = test_db.GetWordTable();
                table.Clear();
                table.AddRange(this.database.GetWordTable().GetValuesTyped());
            }

            {
                var table = test_db.GetPhraseTable();
                table.Clear();
                table.AddRange(this.database.GetPhraseTable().GetValuesTyped());
            }

            {
                var table = test_db.GetLocalizationTable();
                table.Clear();
                table.AddRange(this.database.GetLocalizationTable().GetValuesTyped());
            }

            {
                var table = test_db.GetMiniGameTable();
                table.Clear();
                table.AddRange(this.database.GetMiniGameTable().GetValuesTyped());
            }

            {
                var table = test_db.GetPlaySessionTable();
                table.Clear();
                table.AddRange(this.database.GetPlaySessionTable().GetValuesTyped());
            }

            {
                var table = test_db.GetLearningBlockTable();
                table.Clear();
                table.AddRange(this.database.GetLearningBlockTable().GetValuesTyped()); 
            }

            {
                var table = test_db.GetStageTable();
                table.Clear();
                table.AddRange(this.database.GetStageTable().GetValuesTyped());
            }

            {
                var table = test_db.GetRewardTable();
                table.Clear();
                table.AddRange(this.database.GetRewardTable().GetValuesTyped());
            }

            Debug.Log("Database copied");
            AssetDatabase.SaveAssets();
        }

        public void RegenerateEnums()
        {
            if (verbose) Debug.Log("Regenerating enums from JSON files...");

            RegenerateEnumsFrom(inputData);

            if (verbose) Debug.Log("Finished regenerating enums!");
        }

        private void RegenerateEnumsFrom(DatabaseInputData DBInputData)
        {
            {
                Debug.Log("Generating Letters enums...");
                var parser = new LetterParser();
                parser.RegenerateEnums(DBInputData.letterDataAsset.text);
            }

            {
                Debug.Log("Generating Words enums...");
                var parser = new WordParser();
                parser.RegenerateEnums(DBInputData.wordDataAsset.text);
            }

            {
                Debug.Log("Generating Phrases enums...");
                var parser = new PhraseParser();
                parser.RegenerateEnums(DBInputData.phraseDataAsset.text);
            }

            {
                Debug.Log("Generating MiniGames enums...");
                var parser = new MiniGameParser();
                parser.RegenerateEnums(DBInputData.minigameDataAsset.text);
            }

            {
                Debug.Log("Generating PlaySessions enums...");
                var parser = new PlaySessionParser();
                parser.RegenerateEnums(DBInputData.playSessionDataAsset.text);
            }

            {
                Debug.Log("Generating LearningBlocks enums...");
                var parser = new LearningBlockParser();
                parser.RegenerateEnums(DBInputData.playSessionDataAsset.text);  // @note: LearningBlockParser works on the same table of playSessionData
            }

            {
                Debug.Log("Generating Localization enums...");
                var parser = new LocalizationParser();
                parser.RegenerateEnums(DBInputData.localizationDataAsset.text);
            }

            {
                Debug.Log("Generating Stages enums...");
                var parser = new StageParser();
                parser.RegenerateEnums(DBInputData.stageDataAsset.text);
            }

            {
                Debug.Log("Generating Rewards enums...");
                var parser = new RewardParser();
                parser.RegenerateEnums(DBInputData.rewardDataAsset.text);
            }
        }

        #region Loading

        /// <summary>
        /// Load all database values from scriptable objects
        /// </summary>
        public void LoadDatabase()
        {
            if (verbose) Debug.Log("Loading data from JSON files...");

            this.database = Database.LoadDB(DatabaseManager.STATIC_DATABASE_NAME);
            LoadDataFrom(inputData);

            if (verbose) Debug.Log("Finished loading!");
        }

        /// <summary>
        /// Load input data and place it inside the database.
        /// </summary>
        /// <param name="DBInputData"></param>
        private void LoadDataFrom(DatabaseInputData DBInputData)
        {
            {
                Debug.Log("Loading Letters...");
                var parser = new LetterParser();
                parser.Parse(DBInputData.letterDataAsset.text, database, database.GetLetterTable());
            }

            {
                // @note: depends on Letter
                Debug.Log("Loading Words...");
                var parser = new WordParser();
                parser.Parse(DBInputData.wordDataAsset.text, database, database.GetWordTable());
            }

            {
                // @note: depends on Word
                Debug.Log("Loading Phrases...");
                var parser = new PhraseParser();
                parser.Parse(DBInputData.phraseDataAsset.text, database, database.GetPhraseTable());
            }

            {
                Debug.Log("Loading MiniGames...");
                var parser = new MiniGameParser();
                parser.Parse(DBInputData.minigameDataAsset.text, database, database.GetMiniGameTable());
            }

            {
                // @note: depends on Minigame
                Debug.Log("Loading PlaySessions...");
                var parser = new PlaySessionParser();
                parser.Parse(DBInputData.playSessionDataAsset.text, database, database.GetPlaySessionTable());
            }

            {
                // @note: depends on Letter, Word, Phrase, PlaySession
                Debug.Log("Loading LearningBlocks...");
                var parser = new LearningBlockParser();
                parser.Parse(DBInputData.playSessionDataAsset.text, database, database.GetLearningBlockTable());
            }

            {
                Debug.Log("Loading Localization...");
                var parser = new LocalizationParser();
                parser.Parse(DBInputData.localizationDataAsset.text, database, database.GetLocalizationTable());
            }

            {
                Debug.Log("Loading Stages...");
                var parser = new StageParser();
                parser.Parse(DBInputData.stageDataAsset.text, database, database.GetStageTable());
            }

            {
                Debug.Log("Loading Rewards...");
                var parser = new RewardParser();
                parser.Parse(DBInputData.rewardDataAsset.text, database, database.GetRewardTable());
            }

            // Save database modifications
            EditorUtility.SetDirty(database.stageDb);
            EditorUtility.SetDirty(database.minigameDb);
            EditorUtility.SetDirty(database.rewardDb);
            EditorUtility.SetDirty(database.letterDb);
            EditorUtility.SetDirty(database.wordDb);
            EditorUtility.SetDirty(database.phraseDb);
            EditorUtility.SetDirty(database.localizationDb);
            EditorUtility.SetDirty(database.learningblockDb);
            EditorUtility.SetDirty(database.playsessionDb);
            AssetDatabase.SaveAssets();
        }
        #endregion

    }
}
#endif