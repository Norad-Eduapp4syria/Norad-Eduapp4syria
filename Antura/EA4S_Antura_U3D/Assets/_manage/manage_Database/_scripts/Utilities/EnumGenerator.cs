﻿#if UNITY_EDITOR
using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace EA4S.Db
{
    public static class EnumGenerator
    {

        public static void ExtractEnum(string className, string columnKey, List<Dictionary<string, object>> tuples_list, bool addNoneValue = false, string customEnumName = null)
        {

            List<string> enumValuesSet = new List<string>();
            foreach (var tuple in tuples_list) {
                var value = ((string)tuple[columnKey]).Trim();
                if (value == "") continue;
                if (!enumValuesSet.Contains(value)) {
                    enumValuesSet.Add(value);
                }
            }

            var enumName = className + columnKey;
            if (customEnumName != null) {
                enumName = customEnumName;
            }

            var path = Application.dataPath + "/_app/_scripts/Database/DataEnums/" + enumName + ".cs";
            WriteEnumFile(path, enumName, enumValuesSet, addNoneValue);
        }

        private static void WriteEnumFile(string toPath, string enumName, List<string> values, bool addNoneValue)
        {
            using (StreamWriter sw = File.CreateText(toPath)) {
                sw.WriteLine("//-------START OF AUTOGENERATED FILE - DO NOT EDIT------");
                sw.WriteLine("");
                sw.WriteLine("namespace EA4S.Db");
                sw.WriteLine("{");
                sw.WriteLine("  public enum " + enumName);
                sw.WriteLine("  {");
                if (addNoneValue) {
                    sw.WriteLine("      None" + " = " + (0) + ",");
                }
                for (int i = 0; i < values.Count; i++) {
                    sw.WriteLine("      " + values[i] + " = " + (i + 1) + ",");
                }
                sw.WriteLine("  }");
                sw.WriteLine("}");
                sw.WriteLine("");
                sw.WriteLine("////-------END OF AUTOGENERATED FILE - DO NOT EDIT------");
            }
            Debug.Log("Regenerated Enum " + enumName);
        }
    }

}
#endif