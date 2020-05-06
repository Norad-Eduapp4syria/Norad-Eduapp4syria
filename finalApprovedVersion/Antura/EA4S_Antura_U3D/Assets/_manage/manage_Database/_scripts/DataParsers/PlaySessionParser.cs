﻿using System.Collections.Generic;
using MiniJSON;
using UnityEngine;

namespace EA4S.Db.Management
{
    public class PlaySessionParser : DataParser<PlaySessionData, PlaySessionTable>
    {
        override protected PlaySessionData CreateData(Dictionary<string, object> dict, Database db)
        {
            var data = new PlaySessionData();

            data.Type = ToString(dict["Type"]);

            data.Stage = ToInt(dict["Stage"]);
            data.LearningBlock = ToInt(dict["LearningBlock"]);
            data.PlaySession = ToInt(dict["PlaySession"]);
            data.Id = data.Stage + "." + data.LearningBlock + "." + data.PlaySession;

            data.Letters = ParseIDArray<LetterData, LetterTable>(data, (string)dict["Letters"], db.GetLetterTable());
            CustomAddDiacritics(data, db);

            data.Words = ParseIDArray<WordData, WordTable>(data, (string)dict["Words"], db.GetWordTable());
            data.Words_previous = ParseIDArray<WordData, WordTable>(data, (string)dict["Words_previous"], db.GetWordTable());
            data.Phrases = ParseIDArray<PhraseData, PhraseTable>(data, (string)dict["Phrases"], db.GetPhraseTable());
            data.Phrases_previous = ParseIDArray<PhraseData, PhraseTable>(data, (string)dict["Phrases_previous"], db.GetPhraseTable());

            data.Order = ParseEnum<PlaySessionDataOrder>(data, dict["Order"]);
            data.Minigames = CustomParseMinigames(data, dict, db.GetMiniGameTable());

            return data;
        }

        private void CustomAddDiacritics(PlaySessionData psData, Database db)
        {
            // Make sure to also add all combos, if a symbol is found
            HashSet<string> newLetters = new HashSet<string>();
            newLetters.UnionWith(psData.Letters);
            foreach (var letterId in psData.Letters)
            {
                var letterData = db.GetById(db.GetLetterTable(), letterId);
                if (letterData.Kind == LetterDataKind.Symbol)
                {
                    // this is a symbol
                    var symbolId = letterId;
                    var allDiacriticCombos = db.FindAll(db.GetLetterTable(), x => x.Symbol == symbolId);
                    newLetters.UnionWith(allDiacriticCombos.ConvertAll(x => x.Id));
                }
            }
            psData.Letters = new string[newLetters.Count];
            newLetters.CopyTo(psData.Letters);
        }

        public List<MiniGameInPlaySession> CustomParseMinigames(PlaySessionData data, Dictionary<string, object> dict, MiniGameTable table)
        {
            var list = new List<MiniGameInPlaySession>();

            if (data.Type == "Assessment")
            {
                // Assessments have AssessmentType as their minigame
                var minigameStruct = new MiniGameInPlaySession();
                var assessmentType = ToString(dict["AssessmentType"]);
                if (assessmentType == "")
                {
                    Debug.LogWarning(data.GetType().ToString() + " could not find AssessmentType for assessment " + data.Id);
                    return list; // this means that no assessment type has been selected
                }
                minigameStruct.MiniGameCode = (MiniGameCode)System.Enum.Parse(typeof(MiniGameCode), assessmentType);
                minigameStruct.Weight = 1;  // weight is forced to be 1

                list.Add(minigameStruct);
            }
            else
            {
                // Non-Assessments (i.e. Minigames) must be checked through columns
                for (int enum_i = 0; enum_i < System.Enum.GetValues(typeof(MiniGameCode)).Length; enum_i++)
                {
                    var enum_string = ((MiniGameCode)enum_i).ToString();
                    if (enum_string == "") continue; // this means that the enum does not exist
                    if (enum_string == "0") continue; // 0 does not exist in the table

                    if (!dict.ContainsKey(enum_string)) {
                        // TODO: what to do if the enum is not found in the dict? tell once?
                        //Debug.LogWarning(data.GetType().ToString() + " could not find minigame column for " + enum_string);
                        continue;
                    }

                    var minigameStruct = new MiniGameInPlaySession();
                    minigameStruct.MiniGameCode = (MiniGameCode)enum_i;
                    minigameStruct.Weight = ToInt(dict[enum_string]);
                    if (minigameStruct.Weight == 0)
                    {
                        // Skip adding if the weight is zero
                        continue;
                    }

                    list.Add(minigameStruct);
                }

            }


            return list;
        }

        protected override void RegenerateEnums(List<Dictionary<string, object>> rowdicts_list)
        {
            ExtractEnum(rowdicts_list, "Order");
        }

    }
}
