
public static class ArabicBaseForm {

	const int ArabicBaseStart = 1569;
	const int ArabicBaseEnd = 1640; //1610 + some extra
	public static int[][] ARABIC_GLPHIES = {
		new int[]{ 1569,65152,65163,65164,65152,3 } ,
		new int[]{ 1570,65153,65153,65154,65154,2 } ,
		new int[]{ 1571,65155,65155,65156,65156,2 } ,
		new int[]{ 1572,65157,65157,65158,65158,2 } ,
		new int[]{ 1573,65159,65159,65160,65160,2 } ,
		new int[]{ 1574,65161,65163,65163,65162,2 } ,
		new int[]{ 1575,65165,65165,65166,65166,2 } ,
		new int[]{ 1576,65167,65169,65170,65168,4 } ,
		new int[]{ 1577,65171,65171,65172,65172,2 } ,
		new int[]{ 1578,65173,65175,65176,65174,4 } ,
		new int[]{ 1579,65177,65179,65180,65178,4 } ,
		new int[]{ 1580,65181,65183,65184,65182,4 } ,
		new int[]{ 1581,65185,65187,65188,65186,4 } ,
		new int[]{ 1582,65189,65191,65192,65190,4 } ,
		new int[]{ 1583,65193,65193,65194,65194,2 } ,
		new int[]{ 1584,65195,65195,65196,65196,2 } ,
		new int[]{ 1585,65197,65197,65198,65198,2 } ,
		new int[]{ 1586,65199,65199,65200,65200,2 } ,
		new int[]{ 1587,65201,65203,65204,65202,4 } ,
		new int[]{ 1588,65205,65207,65208,65206,4 } ,
		new int[]{ 1589,65209,65211,65212,65210,4 } ,
		new int[]{ 1590,65213,65215,65216,65214,4 } ,
		new int[]{ 1591,65217,65219,65218,65220,4 } ,
		new int[]{ 1592,65221,65223,65222,65222,4 } ,
		new int[]{ 1593,65225,65227,65228,65226,4 } ,
		new int[]{ 1594,65229,65231,65232,65230,4 } ,
		new int[]{ 1601,65233,65235,65236,65234,4 } ,
		new int[]{ 1602,65237,65239,65240,65238,4 } ,
		new int[]{ 1603,65241,65243,65244,65242,4 } ,
		new int[]{ 1604,65245,65247,65248,65246,4 } ,
		new int[]{ 1605,65249,65251,65252,65250,4 } ,
		new int[]{ 1606,65253,65255,65256,65254,4 } ,
		new int[]{ 1607,65257,65259,65260,65258,4 } ,
		new int[]{ 1608,65261,65261,65262,65262,2 } ,
		new int[]{ 1610,65265,65267,65268,65266,4 } 
	};

	public enum LetterForm{
		Initial = 2,
		Medial = 3,
		Final = 4
	}


	private static char GetBaseShape(char chr){
		if (ArabicBaseStart <= chr && chr <= ArabicBaseEnd)
			return chr;
		for (int n = 0; n < ARABIC_GLPHIES.Length; n++) {
			for (int glyphIndex = 0; glyphIndex < ARABIC_GLPHIES [n].Length; glyphIndex++) {
				if (chr == (char)ARABIC_GLPHIES [n] [glyphIndex])
					return (char)ARABIC_GLPHIES [n] [0];
			}
		}
		return chr;
	}

	public static string Extract(string s){
		string result = "";
		foreach (char chr in s) {
			result += GetBaseShape (chr);
		}
		return result;
	}

	public static char GetLetterForm(char chr, LetterForm form){
		
		for (int n = 0; n < ARABIC_GLPHIES.Length; n++) {
			for (int glyphIndex = 0; glyphIndex < ARABIC_GLPHIES [n].Length; glyphIndex++) {
				if (chr == (char)ARABIC_GLPHIES [n] [glyphIndex])
					return (char)ARABIC_GLPHIES [n] [(int)form];
			}
		}
		return chr;
	}

	public static string GetConnectedForm(string word){
		string result = "";
		LetterForm form;
		for (int i = word.Length - 1; i >= 0; i--) {
			if (i == word.Length - 1)
				result += GetLetterForm (word [i], LetterForm.Final);
			else if (i == 0)
				result += GetLetterForm (word [i], LetterForm.Initial);
			else
				result += GetLetterForm (word [i], LetterForm.Medial);
		}
		return result;
	}
}
