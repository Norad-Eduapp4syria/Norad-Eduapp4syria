﻿using System.Collections.Generic;

namespace EA4S.Db.Management
{
    public class LetterParser : DataParser<LetterData, LetterTable>
    {
        override protected LetterData CreateData(Dictionary<string, object> dict, Database db)
        {
            var data = new LetterData();

            data.Id = ToString(dict["Id"]);
            data.Active = (ToInt(dict["Active"]) == 1);
            if (!data.Active) return null;  // Skip this data if inactive

            data.Number = ToInt(dict["Number"]);
            data.Title = ToString(dict["Title"]);
            data.Kind = ParseEnum<LetterDataKind>(data, dict["Kind"]);
            data.BaseLetter = ToString(dict["BaseLetter"]);
            data.Symbol = ToString(dict["Symbol"]);
            data.Type = ParseEnum<LetterDataType>(data, dict["Type"]);
            data.Tag = ToString(dict["Tag"]);
            data.Notes = ToString(dict["Notes"]);
            data.SunMoon = ParseEnum<LetterDataSunMoon>(data, dict["SunMoon"]);
            data.Sound = ToString(dict["Sound"]);
            data.SoundZone = ToString(dict["SoundZone"]);
            data.Isolated = ToString(dict["Isolated"]);
            data.Initial = ToString(dict["Initial"]);
            data.Medial = ToString(dict["Medial"]);
            data.Final = ToString(dict["Final"]);
            data.Isolated_Unicode = ToString(dict["Isolated_Unicode"]);
            data.Initial_Unicode = ToString(dict["Initial_Unicode"]);
            data.Medial_Unicode = ToString(dict["Medial_Unicode"]);
            data.Final_Unicode = ToString(dict["Final_Unicode"]);
            data.Symbol_Unicode = ToString(dict["Symbol_Unicode"]);
            data.MedialFix = ToString(dict["MedialFix"]);
            data.FinalFix = ToString(dict["FinalFix"]);

            data.Old_Isolated = ToString(dict["Old_Isolated"]);
            data.Old_Initial = ToString(dict["Old_Initial"]);
            data.Old_Medial = ToString(dict["Old_Medial"]);
            data.Old_Final = ToString(dict["Old_Final"]);

            return data;
        }

        protected override void RegenerateEnums(List<Dictionary<string, object>> rowdicts_list)
        {
            ExtractEnum(rowdicts_list, "Kind");
            ExtractEnum(rowdicts_list, "Type", addNoneValue: true);
            ExtractEnum(rowdicts_list, "SunMoon", addNoneValue: true);
        }

        protected override void FinalValidation(LetterTable table, Database db)
        {
            // Fields 'BaseLetter' and 'Symbol' are validated with a final validation step, since they are based on this same table
            // Also, Combination letters are validated with their BaseLetter and Symbol.
            foreach (var data in table.GetValuesTyped()) {
                if (data.Kind == LetterDataKind.DiacriticCombo) {
                    if (data.BaseLetter == "") {
                        LogValidation(data, "LetterData with id  " + data.Id + " is a Combination but does not have a BaseLetter.");
                    }

                    if (data.Symbol == "") {
                        LogValidation(data, "LetterData with id  " + data.Id + " is a Combination but does not have a Symbol.");
                    }

                    if ((data.Id != data.BaseLetter + "_" + data.Symbol) && (data.Id != "alef_hamza_hi" && data.Id != "alef_hamza_low")) {
                        // alef_hamza_hi and alef_hamza_low are the only exceptions in the name format on Combinations
                        LogValidation(data, "LetterData with id  " + data.Id + " is a Combination, but the BaseLetter and Symbol do not match the Id.");
                    }
                }

                if (data.BaseLetter != "" && table.GetValue(data.BaseLetter) == null) {
                    LogValidation(data, "Cannot find id of LetterData for BaseLetter value " + data.BaseLetter + " (found in letter " + data.Id + ")");
                }

                if (data.Symbol != "" && table.GetValue(data.Symbol) == null) {
                    LogValidation(data, "Cannot find id of LetterData for Symbol value " + data.Symbol + " (found in letter " + data.Id + ")");
                }
            }
        }

    }
}
