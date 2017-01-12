#include "ArabicHelperForGames.h"
#include "../StringUtility.h"
#include "../../AppMacros.h"

ArabicHelperForGames::ArabicHelperForGames() {
    
    CCLOG("ArabicHelperForGames()");
    
    
}


std::string ArabicHelperForGames::getInArabic(std::string word) {
    
    if (word == "") return "";
    
    if (word == "give the") return "اعطي ال";
    if (word == "to the") return "الى ال";
    if (word == "put the") return "ضع ال";
    
    // colors
    if (word == "yellow") return "باللون الاصفر";
    if (word == "red") return "باللون الاحمر";
    if (word == "blue") return "باللون الازرق";
    if (word == "green") return "باللون الاخضر";
    if (word == "black") return "باللون الاسود";
    if (word == "white") return "باللون الابيض";
    
    if (word == "on top of the") return "في اعلى ال";
    if (word == "to the left of the") return "على شمال ال";
    if (word == "to the right of the") return "على يمين ال";
    if (word == "under the") return "تحت ال";
    if (word == "next to the") return "بعد ال";
    if (word == "on the") return "فوق ال";
    
    if (word == "old woman") return "سيدة عجوزة";
    if (word == "old man") return "رجل عجوز";
    if (word == "woman") return "سيدة";
    if (word == "man") return "رجل";
    if (word == "young girl") return "بنت";
    if (word == "young boy") return "ولد";
    
    
    if (word == "tree") return "شجرة";
    if (word == "desk") return "مكتب";
    if (word == "window") return "نافذة";
    if (word == "truck") return "شاحنة";
    if (word == "horse") return "حصان";
    if (word == "blackboard") return "سبورة";
    if (word == "bridge") return "جسر";
    if (word == "rock") return "صخرة";
    if (word == "house") return "بيت";
    if (word == "table") return "جدول";
    
    if (word == "hat") return "قبعة";
    if (word == "boots") return "خذاء";
    if (word == "umbrella") return "مظلة";
    if (word == "dress") return "ثوب";
    if (word == "mouse") return "فأر";
    if (word == "boat") return "قارب";
    if (word == "shorts") return "سروال";
    if (word == "banana") return "موز";
    if (word == "pen") return "قلم";
    if (word == "book") return "كتاب";
    if (word == "cup") return "كأس";
    if (word == "coat") return "معطف";
    if (word == "nest") return "عش";
    if (word == "bag") return "حقيبة";
    if (word == "cat") return "قطة";
    
    if (word == "broom") return "مكنسة";
    if (word == "glass") return "زجاج";
    if (word == "glasses") return "نظارات";
    if (word == "sock") return "جورب";
    if (word == "trumpet") return "بوق";
    if (word == "star") return "نجم";
    if (word == "duck") return "بطة";
    if (word == "clock") return "ساعة";
    if (word == "bucket") return "دلو";
    if (word == "watch") return "راقب";
    if (word == "rug") return "سجادة";
    if (word == "dish") return "صحن";
    if (word == "plant") return "مصنع";
    if (word == "sun") return "شمس";
    if (word == "fish") return "سمك";
    if (word == "ring") return "حلق";
    if (word == "bee") return "نحلة";
    if (word == "basket") return "سلة";
    if (word == "box") return "صندوق";
    if (word == "bottle") return "زجاجة";
    if (word == "fan") return "مروحة";
    if (word == "doll") return "دمية";
    if (word == "lamp") return "مصباح";
    if (word == "spoon") return "ملعقة";
    if (word == "fork") return "شوكة";
    if (word == "shell") return "قذيفة";
    if (word == "car") return "سيارة";
    if (word == "pan") return "مقلاة";
    if (word == "pig") return "خنزير";
    if (word == "jug") return "ابريق";
    if (word == "dog") return "كلب";
    if (word == "frog") return "ضفدع";
    if (word == "train") return "قطار";
    if (word == "crab") return "سلطعون";
    if (word == "hen") return "دجاجة";
    
    // body parts
    if (word == "nose") return "انف";
    if (word == "head") return "راس";
    if (word == "arm") return "ذراع";
    if (word == "chin") return "ذقن";
    if (word == "mouth") return "فم";
    if (word == "back") return "ظهر";
    if (word == "hand") return "يد";
    if (word == "finger") return "اصبع";
    if (word == "tongue") return "لسان";
    if (word == "foot") return "قدم";
    if (word == "leg") return "ساق";
    if (word == "ear") return "اذن";
    if (word == "hair") return "شعر";
    if (word == "neck") return "عنق";
    if (word == "knee") return "ركبة";
    if (word == "shoulder") return "كتف";
    if (word == "eye") return "عين";
    
    return word;
}

std::string ArabicHelperForGames::getInArabic_wordDictation(std::string word) {
    
    if (word == "bubble1_ep5_wordDictation_p1") return "ا#ن#ف";
    if (word == "bubble1_ep5_wordDictation_p2") return "ا#ذ#ن";
    if (word == "bubble1_ep5_wordDictation_p3") return "ا#س#د";

    if (word == "bubble2_ep5_wordDictation_p1") return "ب#ا#ب";
    if (word == "bubble2_ep5_wordDictation_p2") return "ب#ي#ت";
    if (word == "bubble2_ep5_wordDictation_p3") return "ب#ح#ر";

    if (word == "bubble3_ep5_wordDictation_p1") return "ت#و#ت";
    if (word == "bubble3_ep5_wordDictation_p2") return "ت#ي#ن";
    if (word == "bubble3_ep5_wordDictation_p3") return "ت#م#س#ا#ح";
	
	if (word == "bubble4_ep5_wordDictation_p1") return "ث#و#ر";
    if (word == "bubble4_ep5_wordDictation_p2") return "ث#و#ب";
    if (word == "bubble4_ep5_wordDictation_p3") return "ث#ق#ب";
	
	if (word == "bubble5_ep5_wordDictation_p1") return "ج#م#ل";
    if (word == "bubble5_ep5_wordDictation_p2") return "ج#ب#ل";
    if (word == "bubble5_ep5_wordDictation_p3") return "ج#س#م";
	
	if (word == "bubble6_ep5_wordDictation_p1") return "ح#و#ت";
    if (word == "bubble6_ep5_wordDictation_p2") return "ح#م#ل";
    if (word == "bubble6_ep5_wordDictation_p3") return "ح#ص#ا#ن";
	
	if (word == "bubble7_ep5_wordDictation_p1") return "خ#ر#ي#ف";
    if (word == "bubble7_ep5_wordDictation_p2") return "خ#و#خ";
    if (word == "bubble7_ep5_wordDictation_p3") return "خ#س";
	
	if (word == "bubble8_ep5_wordDictation_p1") return "د#ا#ر";
    if (word == "bubble8_ep5_wordDictation_p2") return "د#و#ل#ا#ب";
    if (word == "bubble8_ep5_wordDictation_p3") return "د#ب";
	
	if (word == "bubble9_ep5_wordDictation_p1") return "ذ#ي#ل";
    if (word == "bubble9_ep5_wordDictation_p2") return "ذ#ر#ا#ع";
    if (word == "bubble9_ep5_wordDictation_p3") return "ذ#ب#ا#ب";
	
	if (word == "bubble10_ep5_wordDictation_p1") return "ر#م#ل";
    if (word == "bubble10_ep5_wordDictation_p2") return "ر#م#ح";
    if (word == "bubble10_ep5_wordDictation_p3") return "ر#ف";
	
	if (word == "bubble11_ep5_wordDictation_p1") return "ف#ي#ل";
    if (word == "bubble11_ep5_wordDictation_p2") return "ز#و#ر#ق";
    if (word == "bubble11_ep5_wordDictation_p3") return "ز#ر#ع";
	
	if (word == "bubble12_ep5_wordDictation_p1") return "س#ط#ح";
    if (word == "bubble12_ep5_wordDictation_p2") return "س#د";
    if (word == "bubble12_ep5_wordDictation_p3") return "س#ر#ي#ر";
	
	if (word == "bubble13_ep5_wordDictation_p1") return "ش#م#س";
    if (word == "bubble13_ep5_wordDictation_p2") return "ش#و#ك";
    if (word == "bubble13_ep5_wordDictation_p3") return "ش#ر#ي#ط";
	
	if (word == "bubble14_ep5_wordDictation_p1") return "ص#ا#ب#و#ن";
    if (word == "bubble14_ep5_wordDictation_p2") return "ص#ب#ا#ر";
    if (word == "bubble14_ep5_wordDictation_p3") return "ص#م#غ";
	
	if (word == "bubble15_ep5_wordDictation_p1") return "ض#ر#س";
    if (word == "bubble15_ep5_wordDictation_p2") return "ض#ب#ا#ب";
    if (word == "bubble15_ep5_wordDictation_p3") return "ا#ص#ف#ر";
	
	if (word == "bubble16_ep5_wordDictation_p1") return "ط#ا#و#و#س";
    if (word == "bubble16_ep5_wordDictation_p2") return "ط#ي#ر";
    if (word == "bubble16_ep5_wordDictation_p3") return "ط#ر#ي#ق";
	
	if (word == "bubble17_ep5_wordDictation_p1") return "ظ#ر#ف";
    if (word == "bubble17_ep5_wordDictation_p2") return "ا#س#و#د";
    if (word == "bubble17_ep5_wordDictation_p3") return "ظ#ب#ي";
	
	if (word == "bubble18_ep5_wordDictation_p1") return "ع#ي#ن";
    if (word == "bubble18_ep5_wordDictation_p2") return "ع#و#د";
    if (word == "bubble18_ep5_wordDictation_p3") return "ع#ن#ب";
	
	if (word == "bubble19_ep5_wordDictation_p1") return "غ#ي#م";
    if (word == "bubble19_ep5_wordDictation_p2") return "غ#ص#ن";
    if (word == "bubble19_ep5_wordDictation_p3") return "غ#ز#ا#ل";
	
	if (word == "bubble20_ep5_wordDictation_p1") return "ف#ي#ل";
    if (word == "bubble20_ep5_wordDictation_p2") return "ف#و#ل";
    if (word == "bubble20_ep5_wordDictation_p3") return "ف#ح#م";
	
	if (word == "bubble21_ep5_wordDictation_p1") return "ق#ط#ا#ر";
    if (word == "bubble21_ep5_wordDictation_p2") return "ق#مة";
    if (word == "bubble21_ep5_wordDictation_p3") return "ق#م#ر";
	
	if (word == "bubble22_ep5_wordDictation_p1") return "ك#ت#ا#ب";
    if (word == "bubble22_ep5_wordDictation_p2") return "ك#رة";
    if (word == "bubble22_ep5_wordDictation_p3") return "ك#ر#س#ي";
	
	if (word == "bubble23_ep5_wordDictation_p1") return "ل#ي#م#و#ن";
    if (word == "bubble23_ep5_wordDictation_p2") return "ل#ع#بة";
    if (word == "bubble23_ep5_wordDictation_p3") return "ل#ي#ل";
	
	if (word == "bubble24_ep5_wordDictation_p1") return "م#ر#ج";
    if (word == "bubble24_ep5_wordDictation_p2") return "م#ش#ط";
    if (word == "bubble24_ep5_wordDictation_p3") return "م#ف#ت#ا#ح";
	
	if (word == "bubble25_ep5_wordDictation_p1") return "ن#ج#م";
    if (word == "bubble25_ep5_wordDictation_p2") return "ن#س#ي#م";
    if (word == "bubble25_ep5_wordDictation_p3") return "ن#ف#ق";
	
	if (word == "bubble26_ep5_wordDictation_p1") return "ه#ا#ت#ف";
    if (word == "bubble26_ep5_wordDictation_p2") return "ه#د#ه#د";
    if (word == "bubble26_ep5_wordDictation_p3") return "س#ي#دة";

	
	if (word == "bubble1_ep7_wordDictation_p1") return "ب#ا#ص";
    if (word == "bubble1_ep7_wordDictation_p2") return "ح#ط#ب";
    if (word == "bubble1_ep7_wordDictation_p3") return "ك#ت#ا#ب";

    if (word == "bubble2_ep7_wordDictation_p1") return "و#ق#ت";
    if (word == "bubble2_ep7_wordDictation_p2") return "ب#ر#ج";
    if (word == "bubble2_ep7_wordDictation_p3") return "ح#ص#ا#ن";

    if (word == "bubble3_ep7_wordDictation_p1") return "خ#و#خ";
    if (word == "bubble3_ep7_wordDictation_p2") return "ب#د#ر";
    if (word == "bubble3_ep7_wordDictation_p3") return "ج#ب#ل";
	
	if (word == "bubble4_ep7_wordDictation_p1") return "خ#ي#ط";
    if (word == "bubble4_ep7_wordDictation_p2") return "ب#ح#ر";
    if (word == "bubble4_ep7_wordDictation_p3") return "م#ل#ح";
	
	if (word == "bubble5_ep7_wordDictation_p1") return "ج#ذ#ر";
    if (word == "bubble5_ep7_wordDictation_p2") return "س#م#ك";
    if (word == "bubble5_ep7_wordDictation_p3") return "س#ل#ك";
	
	if (word == "bubble6_ep7_wordDictation_p1") return "ش#ب#ل";
    if (word == "bubble6_ep7_wordDictation_p2") return "ص#ق#ر";
    if (word == "bubble6_ep7_wordDictation_p3") return "ي#ي#ض";
	
	if (word == "bubble7_ep7_wordDictation_p1") return "ز#ر#ع";
    if (word == "bubble7_ep7_wordDictation_p2") return "ص#م#غ";
    if (word == "bubble7_ep7_wordDictation_p3") return "ق#ف#ل";
	
	if (word == "bubble8_ep7_wordDictation_p1") return "ل#و#ح";
    if (word == "bubble8_ep7_wordDictation_p2") return "ق#ر#د";
    if (word == "bubble8_ep7_wordDictation_p3") return "ن#ه#ر";
	
	if (word == "bubble9_ep7_wordDictation_p1") return "و#ج#ه";
    if (word == "bubble9_ep7_wordDictation_p2") return "و#ل#د";
    if (word == "bubble9_ep7_wordDictation_p3") return "ن#م#ل";
	
	if (word == "bubble10_ep7_wordDictation_p1") return "ه#د#ه#د";
    if (word == "bubble10_ep7_wordDictation_p2") return "ع#و#د";
    if (word == "bubble10_ep7_wordDictation_p3") return "ع#س#ل";
	
	if (word == "bubble11_ep7_wordDictation_p1") return "ظ#ب#ي";
    if (word == "bubble11_ep7_wordDictation_p2") return "خ#ش#ب";
    if (word == "bubble11_ep7_wordDictation_p3") return "د#ي#ك";
	
	if (word == "bubble12_ep7_wordDictation_p1") return "ذ#ه#ب";
    if (word == "bubble12_ep7_wordDictation_p2") return "و#ر#د";
    if (word == "bubble12_ep7_wordDictation_p3") return "ا#س#د";
	
	if (word == "bubble13_ep7_wordDictation_p1") return "ن#س#ر";
    if (word == "bubble13_ep7_wordDictation_p2") return "د#ر#س";
    if (word == "bubble13_ep7_wordDictation_p3") return "ش#م#س";
	
	if (word == "bubble14_ep7_wordDictation_p1") return "ذ#ر#ا#ع";
    if (word == "bubble14_ep7_wordDictation_p2") return "ش#م#ع";
    if (word == "bubble14_ep7_wordDictation_p3") return "ق#م#ر";
	
	if (word == "bubble15_ep7_wordDictation_p1") return "غ#و#ل";
    if (word == "bubble15_ep7_wordDictation_p2") return "ر#ف";
    if (word == "bubble15_ep7_wordDictation_p3") return "ر#ع#د";
	
	if (word == "bubble16_ep7_wordDictation_p1") return "ع#ي#ن";
    if (word == "bubble16_ep7_wordDictation_p2") return "ع#ق#د";
    if (word == "bubble16_ep7_wordDictation_p3") return "ف#ج#ل";
	
	if (word == "bubble17_ep7_wordDictation_p1") return "س#ي#ف";
    if (word == "bubble17_ep7_wordDictation_p2") return "ل#ي#ل";
    if (word == "bubble17_ep7_wordDictation_p3") return "ه#ر#م";
	
	if (word == "bubble18_ep7_wordDictation_p1") return "د#ل#و";
    if (word == "bubble18_ep7_wordDictation_p2") return "ج#ر#ن";
    if (word == "bubble18_ep7_wordDictation_p3") return "ق#ل#م";
	
	if (word == "bubble19_ep7_wordDictation_p1") return "ض#ر#س";
    if (word == "bubble19_ep7_wordDictation_p2") return "ح#ظ";
    if (word == "bubble19_ep7_wordDictation_p3") return "ل#ح#م";
	
	if (word == "bubble20_ep7_wordDictation_p1") return "غ#ز#ا#ل";
    if (word == "bubble20_ep7_wordDictation_p2") return "ه#ا#ت#ف";
    if (word == "bubble20_ep7_wordDictation_p3") return "م#ف#ت#ا#ح";
	
    return word;
}

std::string ArabicHelperForGames::getInArabic_sentenceDictation(std::string word) {
       
    if (word == "bubble1_ep8_sentenceDictation_p1") return "ه#و# #ر#ج#ل";
    if (word == "bubble1_ep8_sentenceDictation_p2") return "ا#ل#ر#ج#ل# #ي#س#ي#ر";
    
    if (word == "bubble2_ep8_sentenceDictation_p1") return "ق#ط#ة# #ج#م#ي#ل#ة";
    if (word == "bubble2_ep8_sentenceDictation_p2") return "ا#ل#ق#ط#ة# #ت#ل#ع#ب";
	
	if (word == "bubble3_ep8_sentenceDictation_p1") return "ا#ل#ط#ف#ل# #ي#ر#س#م";
    if (word == "bubble3_ep8_sentenceDictation_p2") return "م#ا#م#ا# #ت#غ#س#ل";
	
	if (word == "bubble4_ep8_sentenceDictation_p1") return "با#ب#ا# #ي#ع#م#ل";
    if (word == "bubble4_ep8_sentenceDictation_p2") return "ع#ا#م#ر# #ي#ل#ب#س";
	
	if (word == "bubble5_ep8_sentenceDictation_p1") return "ي#س#ي#ر# #ا#ل#ق#ط#ا#ر";
    if (word == "bubble5_ep8_sentenceDictation_p2") return "ي#ن#ز#ل# #ا#ل#م#ط#ر";
	
	if (word == "bubble6_ep8_sentenceDictation_p1") return "ح#ز#ن# #ش#ا#د#ي";
    if (word == "bubble6_ep8_sentenceDictation_p2") return "ن#ا#م# #و#ل#ي#د";
	
	if (word == "bubble7_ep8_sentenceDictation_p1") return "ق#ل#م# #س#ا#م#ي# #ا#ح#م#ر";
    if (word == "bubble7_ep8_sentenceDictation_p2") return "س#م#ر# #ب#ن#ت# #ذ#ك#ي#ة";
	
	if (word == "bubble8_ep8_sentenceDictation_p1") return "خ#ر#ج# #ع#ا#د#ل# #م#ن# #ا#ل#م#ن#ز#ل";
    if (word == "bubble8_ep8_sentenceDictation_p2") return "ذ#ه#ب# #ب#ا#س#م# #ا#ل#ى# #ا#ل#م#د#ر#س#ة";
	
	if (word == "bubble9_ep8_sentenceDictation_p1") return "د#ا#ر# #ج#د#ي";
    if (word == "bubble9_ep8_sentenceDictation_p2") return "ا#ل#ا#ر#ن#ب# #ي#ش#ر#ب";
	
	if (word == "bubble10_ep8_sentenceDictation_p1") return "ن#ا#م# #خ#ا#ل#د";
    if (word == "bubble10_ep8_sentenceDictation_p2") return "ا#ل#ب#ا#ب# #م#ف#ت#و#ح";
	
	if (word == "bubble11_ep8_sentenceDictation_p1") return "ت#د#ر#س# #ر#ب#ا#ب";
    if (word == "bubble11_ep8_sentenceDictation_p2") return "غ#ا#ب# #ر#ا#م#ي";
	
	if (word == "bubble12_ep8_sentenceDictation_p1") return "ض#ا#ع# #ش#ا#د#ي";
    if (word == "bubble12_ep8_sentenceDictation_p2") return "ع#ا#د#ت# #ا#م#ل";
	
	if (word == "bubble13_ep8_sentenceDictation_p1") return "مر#ض#ت# #ل#و#ل#و";
    if (word == "bubble13_ep8_sentenceDictation_p2") return "ك#ت#ب# #ا#ل#ط#ا#ل#ب";
	
	if (word == "bubble14_ep8_sentenceDictation_p1") return "ق#ص#ة# #ح#ل#و#ة";
    if (word == "bubble14_ep8_sentenceDictation_p2") return "ن#ز#ر#ع# #ت#ف#ا#ح";
	
	if (word == "bubble15_ep8_sentenceDictation_p1") return "ق#ف#ز# #ا#ل#ا#ر#ن#ب";
    if (word == "bubble15_ep8_sentenceDictation_p2") return "ط#ا#ر# #ا#ل#ع#ص#ف#و#ر";
	
	if (word == "bubble16_ep8_sentenceDictation_p1") return "ج#ا#ع# #د#و#د#و";
    if (word == "bubble16_ep8_sentenceDictation_p2") return "ا#ح#س#ن#ت# #ي#ا# #ع#م#ر";
	
	if (word == "bubble17_ep8_sentenceDictation_p1") return "ا#ل#ع#س#ل# #م#ف#ي#د";
    if (word == "bubble17_ep8_sentenceDictation_p2") return "ا#ل#ط#ع#ا#م# #ل#ذ#ي#ذ";
	
	if (word == "bubble18_ep8_sentenceDictation_p1") return "ه#و# #م#ر#ي#ض";
    if (word == "bubble18_ep8_sentenceDictation_p2") return "س#ا#ف#ر# #ب#ا#ب#ا";
	
	if (word == "bubble19_ep8_sentenceDictation_p1") return "ا#ك#ل# #س#ا#م#ي";
    if (word == "bubble19_ep8_sentenceDictation_p2") return "ا#ل#ك#ت#ا#ب# #ا#ل#ج#د#ي#د";
	
	if (word == "bubble20_ep8_sentenceDictation_p1") return "خ#ر#و#ف# #ص#غ#ي#ر";
    if (word == "bubble20_ep8_sentenceDictation_p2") return "و#ق#ف# #ا#ل#ب#ا#ص";
    
	
	if (word == "bubble1_ep9_sentenceDictation_p1") return "ب#ي#ت# #ا#ح#ل#ا#م# #ك#ب#ي#ر";
    if (word == "bubble1_ep9_sentenceDictation_p2") return "ا#ل#م#ل#ا#ب#س# #م#غ#س#و#ل#ة";
    
    if (word == "bubble2_ep9_sentenceDictation_p1") return "ا#ل#ك#ت#ب# #ع#ل#ى# #ا#ل#ر#ف";
    if (word == "bubble2_ep9_sentenceDictation_p2") return "ز#ج#ا#ج# #ا#ل#ن#ا#ف#ذ#ة# #ن#ظ#ي#ف";
	
	if (word == "bubble3_ep9_sentenceDictation_p1") return "ا#ن#ا# #ل#ا# #ا#ل#ع#ب# #ب#ا#ل#ن#ا#ر";
    if (word == "bubble3_ep9_sentenceDictation_p2") return "ف#ي# #م#د#ر#س#ت#ي# #س#ا#ح#ة# #ك#ب#ي#ر#ة";
	
	if (word == "bubble4_ep9_sentenceDictation_p1") return "ع#ل#ى# #ا#ل#س#و#ر# #ر#س#و#م# #ج#م#ي#ل#ة";
    if (word == "bubble4_ep9_sentenceDictation_p2") return "ا#ن#ا# #ا#ح#ب# #م#د#ر#س#ت#ي";
	
	if (word == "bubble5_ep9_sentenceDictation_p1") return "ا#د#ر#س# #ا#ل#د#ر#س# #ج#ي#د#ا";
    if (word == "bubble5_ep9_sentenceDictation_p2") return "ا#ل#ط#ف#ل# #ي#ل#ع#ب# #ف#ي# #ا#ل#م#ن#ز#ل";
	
	if (word == "bubble6_ep9_sentenceDictation_p1") return "ا#ن#ا# #و#ص#د#ي#ق#ي# #ن#ح#ب# #ا#ل#ك#ت#ا#ب#ة";
    if (word == "bubble6_ep9_sentenceDictation_p2") return "ا#ش#ا#ه#د# #ا#ل#ت#ل#ف#ا#ز# #ي#و#م# #ا#ل#س#ب#ت";
	
	if (word == "bubble7_ep9_sentenceDictation_p1") return "س#ع#ي#د# #د#خ#ل# #ا#ل#م#ل#ع#ب";
    if (word == "bubble7_ep9_sentenceDictation_p2") return "ع#م#ر# #ل#ا#ع#ب# #ش#ا#ط#ر";
	
	if (word == "bubble8_ep9_sentenceDictation_p1") return "ف#ا#ز# #ا#ل#ف#ر#ي#ق# #ا#ل#ا#و#ل";
    if (word == "bubble8_ep9_sentenceDictation_p2") return "ه#ش#ا#م# #ت#ل#م#ي#ذ# #ز#ك#ي";
	
	if (word == "bubble9_ep9_sentenceDictation_p1") return "ز#ر#ن#ا# #ح#د#ي#ق#ة# #ا#ل#ا#ز#ه#ا#ر";
    if (word == "bubble9_ep9_sentenceDictation_p2") return "ا#ل#ف#ل#ا#ح# #ي#ز#ر#ع# #ا#ل#ح#ق#ل";
	
	if (word == "bubble10_ep9_sentenceDictation_p1") return "و#ض#ع# #ا#ل#ك#ت#ا#ب# #ع#ل#ى# #ا#ل#ط#ا#و#ل#ة";
    if (word == "bubble10_ep9_sentenceDictation_p2") return "ه#و# #ف#ت#ح# #ا#ل#ب#ا#ب";
	
	if (word == "bubble11_ep9_sentenceDictation_p1") return "ا#ل#أ#س#د# #م#ل#ك# #ا#ل#غ#ا#ب#ة";
    if (word == "bubble11_ep9_sentenceDictation_p2") return "ا#ل#ن#م#ر# #ح#ي#و#ا#ن# #م#ف#ت#ر#س";
	
	if (word == "bubble12_ep9_sentenceDictation_p1") return "ع#ا#د# #ا#ل#ط#ا#ل#ب# #م#ن# #ا#ل#م#د#ر#س#ة";
    if (word == "bubble12_ep9_sentenceDictation_p2") return "ذ#ه#ب# #ا#ل#ف#ل#ا#ح# #ا#ل#ى# #ا#ل#ح#ق#ل";
	
	if (word == "bubble13_ep9_sentenceDictation_p1") return "ه#ذ#ا# #م#ن#ز#ل# #ج#د#ي#د";
    if (word == "bubble13_ep9_sentenceDictation_p2") return "ه#ذ#ه# #ق#ط#ة# #ص#غ#ي#ر#ة";
	
	if (word == "bubble14_ep9_sentenceDictation_p1") return "ف#ي# #ا#ل#ك#ت#ا#ب# #ص#و#ر# #ج#م#ي#ل#ة";
    if (word == "bubble14_ep9_sentenceDictation_p2") return "ب#ا#س#م# #ع#ن#د#ه# #ك#ت#ا#ب# #ج#د#ي#د";
	
	if (word == "bubble15_ep9_sentenceDictation_p1") return "ا#غ#س#ل# #و#ج#ه#ي# #ك#ل# #ي#و#م";
    if (word == "bubble15_ep9_sentenceDictation_p2") return "م#ع#ي# #ا#ر#ب#ع# #ت#ف#ا#ح#ا#ت";
	
	if (word == "bubble16_ep9_sentenceDictation_p1") return "ا#ل#ع#ب# #ب#ا#ل#ك#ر#ة# #م#ع# #ا#ص#ح#ا#ب#ي";
    if (word == "bubble16_ep9_sentenceDictation_p2") return "ا#ش#ر#ب# #ا#ل#ح#ل#ي#ب# #ف#ي# #ا#ل#ص#ب#ا#ح";
	
	if (word == "bubble17_ep9_sentenceDictation_p1") return "م#ا#ز#ن# #ط#ا#ل#ب# #ج#ي#د";
    if (word == "bubble17_ep9_sentenceDictation_p2") return "ر#ب#ا#ب# #ف#ت#ا#ة# #ج#م#ي#ل#ة";
	
	if (word == "bubble18_ep9_sentenceDictation_p1") return "ه#و# #ي#ف#ت#ح# #ا#ل#ب#ا#ب";
    if (word == "bubble18_ep9_sentenceDictation_p2") return "ه#ي# #ت#ق#ط#ع# #ا#ل#ش#ا#ر#ع";
	
	if (word == "bubble19_ep9_sentenceDictation_p1") return "ا#ن#ت# #ت#ج#ل#س# #عل#ى# #ا#ل#ك#ر#س#ي";
    if (word == "bubble19_ep9_sentenceDictation_p2") return "ا#ن#ا# #ا#ح#ب# #ا#ل#ح#ي#و#ا#ن#ا#ت";
	
	if (word == "bubble20_ep9_sentenceDictation_p1") return "ا#ل#ن#ح#ل#ة# #ت#ص#ن#ع# #ا#ل#ع#س#ل";
    if (word == "bubble20_ep9_sentenceDictation_p2") return "س#م#ي#ر# #ي#ب#ي#ع# #ا#ل#خ#ب#ز";
    	
    return word;
}

std::string ArabicHelperForGames::getFilenameInEnglish_wordDictation(std::string phoneme) {
   
    if (phoneme == "") return "";
	if (phoneme == "انف") return "nose";
	if (phoneme == "باب") return "Door";
	if (phoneme == "توت") return "blueberry";
    if (phoneme == "ثور") return "ox";
    if (phoneme == "جمل") return "Camel";
    if (phoneme == "حوت") return "whale";
    if (phoneme == "خريف") return "Autumn";
    if (phoneme == "دار") return "house";
    if (phoneme == "ذيل") return "Tail";
    if (phoneme == "رمل") return "sand";
    if (phoneme == "فيل") return "Elephant";
    if (phoneme == "سطح") return "Surface";
    if (phoneme == "شمس") return "sun";
    if (phoneme == "صابون") return "soap";
    if (phoneme == "ضرس") return "sprocket";
    if (phoneme == "طاووس") return "peacock";
    if (phoneme == "ظرف") return "Circumstance";
    if (phoneme == "عين") return "Eye";
    if (phoneme == "غيم") return "Cloud";
    if (phoneme == "فيل") return "Elephant";
    if (phoneme == "قطار") return "Train";
    if (phoneme == "كتاب") return "Book";
    if (phoneme == "ليمون") return "Lemon";
    if (phoneme == "مرج") return "meadow";
    if (phoneme == "نجم") return "a star";
    if (phoneme == "هاتف") return "Phone";
    if (phoneme == "باص") return "Bus";
    if (phoneme == "وقت") return "time";
    if (phoneme == "خوخ") return "Peache";
    if (phoneme == "خيط") return "string";
    if (phoneme == "جذر") return "root";
    if (phoneme == "شبل") return "Cub";
    if (phoneme == "زرع") return "planting";
    if (phoneme == "لوح") return "Slab";
    if (phoneme == "وجه") return "Face";
    if (phoneme == "هدهد") return "Rock";
    if (phoneme == "ظبي") return "Dhabi";
    if (phoneme == "ذهب") return "Go";
    if (phoneme == "نسر") return "Eagle";
    if (phoneme == "ذراع") return "an arm";
    if (phoneme == "غول") return "Ghoul";
    if (phoneme == "عين") return "Eye";
    if (phoneme == "سيف") return "Sword";
    if (phoneme == "دلو") return "Bucket";
    if (phoneme == "ضرس") return "sprocket";
    if (phoneme == "غزال") return "Deer";
    if (phoneme == "اذن") return "So";
    if (phoneme == "بيت") return "a house";
    if (phoneme == "تين") return "Figs";
    if (phoneme == "ثوب") return "dress";
    if (phoneme == "جبل") return "Mount";
    if (phoneme == "حمل") return "Pregnancy";
    if (phoneme == "خوخ") return "Peache";
    if (phoneme == "دولاب") return "cupbord";
    if (phoneme == "ذراع") return "an arm";
    if (phoneme == "رمح") return "spear";
    if (phoneme == "زورق") return "boat";
    if (phoneme == "سد") return "dam";
    if (phoneme == "شوك") return "Thistle";
    if (phoneme == "صبار") return "cactus";
    if (phoneme == "ضباب") return "fog";
    if (phoneme == "طير") return "bird";
    if (phoneme == "اسود") return "black";
    if (phoneme == "عود") return "Lute";
    if (phoneme == "غصن") return "branch";
    if (phoneme == "فول") return "Bean";
    if (phoneme == "قمة") return "summit";
    if (phoneme == "كرة") return "a ball";
    if (phoneme == "لعبة") return "Game";
    if (phoneme == "مشط") return "comb";
    if (phoneme == "نسيم") return "breeze";
    if (phoneme == "هدهد") return "Rock";
    if (phoneme == "حطب") return "wood";
    if (phoneme == "برج") return "horoscope";
    if (phoneme == "بدر") return "Badr";
    if (phoneme == "بحر") return "Sea";
    if (phoneme == "سمك") return "fish";
    if (phoneme == "صقر") return "Falcon";
    if (phoneme == "صمغ") return "Glue";
    if (phoneme == "قرد") return "Monkey";
    if (phoneme == "ولد") return "Boy";
    if (phoneme == "عود") return "Lute";
    if (phoneme == "خشب") return "wood";
    if (phoneme == "ورد") return "flower";
    if (phoneme == "درس") return "Lesson";
    if (phoneme == "شمع") return "wax";
    if (phoneme == "رف") return "Rack";
    if (phoneme == "عقد") return "Contract";
    if (phoneme == "ليل") return "night";
    if (phoneme == "جرن") return "Jarn";
    if (phoneme == "حظ") return "luck";
    if (phoneme == "هاتف") return "Phone";
    if (phoneme == "اسد") return "Lion";
    if (phoneme == "بحر") return "Sea";
    if (phoneme == "تمساح") return "crocodile";
    if (phoneme == "ثقب") return "hole";
    if (phoneme == "جسم") return "Body";
    if (phoneme == "حصان") return "a horse";
    if (phoneme == "خس") return "lettuce";
    if (phoneme == "دب") return "Bear";
    if (phoneme == "ذباب") return "Flies";
    if (phoneme == "رف") return "Rack";
    if (phoneme == "زرع") return "planting";
    if (phoneme == "سرير") return "Bed";
    if (phoneme == "شريط") return "ribbon";
    if (phoneme == "صمغ") return "Glue";
    if (phoneme == "اصفر") return "yellow";
    if (phoneme == "طريق") return "Road";
    if (phoneme == "ظبي") return "deer";
    if (phoneme == "عنب") return "Grape";
    if (phoneme == "غزال") return "Gazelle";
    if (phoneme == "فحم") return "coal";
    if (phoneme == "قمر") return "Moon";
    if (phoneme == "كرسي") return "a chair";
    if (phoneme == "ليل") return "night";
    if (phoneme == "مفتاح") return "a key";
    if (phoneme == "نفق") return "Subway";
    if (phoneme == "سيدة") return "Lady";
    if (phoneme == "كتاب") return "Book";
    if (phoneme == "حصان") return "a horse";
    if (phoneme == "جبل") return "Mount";
    if (phoneme == "ملح") return "salt";
    if (phoneme == "سلك") return "Cable";
    if (phoneme == "بيض") return "eggs";
    if (phoneme == "قفل") return "a lock";
    if (phoneme == "نهر") return "River";
    if (phoneme == "نمل") return "ant";
    if (phoneme == "عسل") return "honey";
    if (phoneme == "ديك") return "rooster";
    if (phoneme == "اسد") return "Lion";
    if (phoneme == "شمس") return "sun";
    if (phoneme == "قمر") return "Moon";
    if (phoneme == "رعد") return "thunder";
    if (phoneme == "فجل") return "radish";
    if (phoneme == "هرم") return "pyramid";
    if (phoneme == "قلم") return "pencil";
    if (phoneme == "لحم") return "meat";
    if (phoneme == "مفتاح") return "a key";

    CCLOG("getFilenameInEnglish_wordDictation %s", phoneme.c_str());
    if (TEST_ENABLED) return "getFilenameInEnglish_wordDictation_ERROR";
    
    return "";
}

std::string ArabicHelperForGames::getFilenameInEnglish_sentenceDictation(std::string phoneme) {
    
    
    if (phoneme == "") return "";
    
    if (phoneme == "هو رجل") return "he is a man";
    if (phoneme == "الرجل يسير") return "The man is walking";
    if (phoneme == "قطة جميلة") return "Lovely cat";
    if (phoneme == "القطة تلعب") return "The cat is playing";
    if (phoneme == "الطفل يرسم") return "The child is painting";
    if (phoneme == "ماما تغسل") return "Mama is washing";
    if (phoneme == "بابا يعمل") return "My father works";
    if (phoneme == "عامر يلبس") return "Amer wears";
    if (phoneme == "يسير القطار") return "The train runs";
    if (phoneme == "ينزل المطر") return "The rain is coming";
    if (phoneme == "حزن شادي") return "Chadi is sad";
    if (phoneme == "نام وليد") return "Walid is sleeping";
    if (phoneme == "قلم سامي احمر") return "Samis pen is red";
    if (phoneme == "سمر بنت ذكية") return "Samar is a smart girl";
    if (phoneme == "خرج عادل من المنزل") return "Adel came out of the house";
    if (phoneme == "ذهب باسم الى المدرسة") return "Bassem went to the school";
    if (phoneme == "دار جدي") return "My grandfather home";
    if (phoneme == "الارنب يشرب") return "Bunny is drinking";
    if (phoneme == "نام خالد") return "Khaled slept";
    if (phoneme == "الباب مفتوح") return "The door is opend";
    if (phoneme == "تدرس رباب") return "Rabab is studying";
    if (phoneme == "غاب رامي") return "Rami missed";
    if (phoneme == "ضاع شادي") return "Shadi is lost";
    if (phoneme == "عادت امل") return "Amal returned";
    if (phoneme == "مرضت لولو") return "Lulu get sick";
    if (phoneme == "كتب الطالب") return "The student wrote";
    if (phoneme == "قصة حلوة") return "Lovley story";
    if (phoneme == "نزرع تفاح") return "We are planting apple";
    if (phoneme == "قفز الارنب") return "The bunny jump";
    if (phoneme == "طار العصفور") return "The bird files";
    if (phoneme == "جاع دودو") return "Dudu is get hungry";
    if (phoneme == "احسنت يا عمر") return "Well done Omar";
    if (phoneme == "العسل مفيد") return "The honey is useful";
    if (phoneme == "الطعام لذيذ") return "The food is delicous";
    if (phoneme == "هو مريض") return "He is sick";
    if (phoneme == "سافر بابا") return "My father traveled";
    if (phoneme == "اكل سامي") return "Sami eats";
    if (phoneme == "الكتاب الجديد") return "The book is new";
    if (phoneme == "خروف صغير") return "Small sheep";
    if (phoneme == "وقف الباص") return "The bust as stopped";
    if (phoneme == "بيت احلام كبير") return "Ahlams home is big";
    if (phoneme == "الملابس مغسولة") return "The clothes are washed";
    if (phoneme == " الكتب على الرف") return "The books are on the shelf";
    if (phoneme == "زجاج النافذة نظيف") return "The window glass is clean ";
    if (phoneme == "انا لا العب بالنار") return "I dont play with fire";
    if (phoneme == "في مدرستي ساحة كبيرة") return "In my school a big square";
    if (phoneme == "على السور رسوم جميلة") return "On the well nice fees";
    if (phoneme == "انا احب مدرستي") return "I like my school";
    if (phoneme == "ادرس الدرس جيدا") return "I study the lesson well";
    if (phoneme == "الطفل يلعب في المنزل") return "The child is playing at home";
    if (phoneme == "انا وصديقي نحب الكتابة") return "Me and my friend like writing";
    if (phoneme == "اشاهد التلفاز يوم السبت") return "I watch the tv every saturday";
    if (phoneme == "سعيد دخل الملعب") return "Said entred to the stadium";
    if (phoneme == "عمر لاعب شاطر") return "Omar is a good player";
    if (phoneme == "فاز الفريق الاول") return "The first team won";
    if (phoneme == "هشام تلميذ زكي") return "Hisham is a cleaver student";
    if (phoneme == "زرنا حديقة الازهار") return "We visited the follower gardens";
    if (phoneme == "الفلاح يزرع الحقل") return "The farmer cultivate the garden";
    if (phoneme == "وضع الكتاب على  الطاولة") return "He put the book on the table";
    if (phoneme == "هو فتح الباب") return "He opened the door";
    if (phoneme == "الأسد ملك الغابة") return "The lion is the king of the jungle";
    if (phoneme == "النمر حيوان مفترس") return "The tiger is a wild animal";
    if (phoneme == "عاد الطالب من المدرسة") return "The student returned from the school";
    if (phoneme == "ذهب الفلاح الى الحقل") return "The farmer goes to the garden";
    if (phoneme == "هذا منزل جديد") return "This is a new house";
    if (phoneme == "هذه قطة صغيرة") return "This is a small cat";
    if (phoneme == "في الكتاب صور جميلة") return "The pictures in the book are nice";
    if (phoneme == "باسم عنده كتاب جديد") return "Bassem has a news book";
    if (phoneme == "اغسل وجهي  كل  يوم") return "I wash my face everyday";
    if (phoneme == "معي اربع تفاحات") return "I have four apples";
    if (phoneme == "العب بالكرة مع اصحابي") return "I play ball with my friends";
    if (phoneme == "اشرب الحليب في الصباح") return "I drink milk every morning";
    if (phoneme == "مازن  طالب جيد") return "Mazen is good student";
    if (phoneme == "رباب فتاة جميلة") return "Rabab is beautiful girl";
    if (phoneme == "هو  يفتح الباب") return "He opens the door";
    if (phoneme == "هي تقطع الشارع") return "She across the street";
    if (phoneme == "انت تجلس على الكرسي") return "You sit on the chair";
    if (phoneme == "انا احب الحيوانات") return "I love the animals";
    if (phoneme == "النحلة تصنع العسل") return "The bee makes the honey";
    if (phoneme == "سمير يبيع الخبز") return "Samir sells bread";
     
    
    CCLOG("getFilenameInEnglish_sentenceDictation %s", phoneme.c_str());
    if (TEST_ENABLED) return "getFilenameInEnglish_sentenceDictation_ERROR";
    
    return "";
}
    
std::string ArabicHelperForGames::getFilenameInEnglish_sentenceReading(std::string phoneme) {
    
    if (phoneme == "") return "";
    
    if (phoneme == "هذه قطتي") return "this is my cat";
    if (phoneme == "القطة  تلعب") return "Cat is playing";
    if (phoneme == "احب قطتي نونو") return "I love my cat Nuno";
    if (phoneme == "القطة تشرب") return "Cat is drinking";
    if (phoneme == "انا  احب المدرسة") return "I like school";
    if (phoneme == "تامر يحب التوت") return "Tamer likes berries";
    if (phoneme == "العصفور يطير") return "The Bird is flying";
    if (phoneme == "القمر بدر") return "The Moon is a fullmoon";
    if (phoneme == "في دار ادم بلبل") return "In Adams home there is a Bulbul";
    if (phoneme == "بلبل اصفر") return "Yellow Bulbul";
    if (phoneme == "رياض يسبح") return "Riad like to swim";
    if (phoneme == "ماجد صديق عامر") return "Majid is a friend of Amer";
    if (phoneme == "القطة فوق الطاولة") return "The Cat is on the table";
    if (phoneme == "الطيور تاكل") return "Birds eat";
    if (phoneme == "البيت نظيف") return "House is clean";
    if (phoneme == "القطار سريع") return "Fast train";
    if (phoneme == "عامر في المدرسة") return "Amer is at school";
    if (phoneme == "ماما تغسل") return "Mama washed";
    if (phoneme == "في دارنا بطة") return "In our home there is a duck";
    if (phoneme == "في دار وداد ورد") return "There is rosses in Widad hom";
    if (phoneme == "في النهر سمكة") return "There is a Fish in the river";
    if (phoneme == "بيتي في اعلى الجبل") return "My home is at the top of the mountain";
    if (phoneme == "المطر ينزل") return "it is raining";
    if (phoneme == "الورد احمر") return "The Roses are red";
    if (phoneme == "الجو بارد") return "the weather is cold";
    if (phoneme == "شادي عطشان") return "Shadi is thirsty";
    if (phoneme == "ابي يزرع التفاح") return "My father plant apples";
    if (phoneme == "انا اسمي باسم") return "My name is Basem";
    if (phoneme == "الفراشة تطير") return "Butterfly is flying";
    if (phoneme == "سليم شرطي") return "Salim is a policeman";
    if (phoneme == "الباب مفتوح") return "the door is open";
    if (phoneme == "في دار جدي ديك") return "There is a cock in my grand father House";
    if (phoneme == "الكتاب على الطاولة") return "The book on the table";
    if (phoneme == "أرنب ابيض صغير") return "Small and white rabbit";
    if (phoneme == "ناهد تلميذة") return "Nahed is a schoolgirl";
    if (phoneme == "أمل تحب العنب") return "Amal loves grapes";
    if (phoneme == "ناهد تلبس") return "Nahed is wearing";
    if (phoneme == "عندي لعبة") return "I have a doll";
    if (phoneme == "التفاحة في اعلى الشجرة") return "The Apple is on the top of the tree";
    if (phoneme == "العب مع اختي") return "I play with my sister";
    if (phoneme == "الهرة تحت السرير") return "The cat is under the bed";
    if (phoneme == "ذهب سعيد") return "Said went";
    if (phoneme == "القرد فوق الشجرة") return "The Monkey is on the tree";
    if (phoneme == "القطار يسير") return "The train runs";
    if (phoneme == "رباب تلعب بالكرة") return "Rabab is playing with the ball";
    if (phoneme == "لولو جاع") return "Lulu is get hungry";
    if (phoneme == "يرسم بالالوان") return "Painting with colors";
    if (phoneme == "ضاع قلم مازن") return "Mazens pen is lost";
    if (phoneme == "يزرع القمح") return "Sowing the Wheat ";
    if (phoneme == "هذا قلم مازن") return "This  Mazens pen";
    if (phoneme == "وليد داخل الصف") return "Walid is in the classroom";
    if (phoneme == "حزن شادي") return "Shadi is get sad";
    
    
    CCLOG("getFilenameInEnglish_sentenceReading %s", phoneme.c_str());
    if (TEST_ENABLED) return "getFilenameInEnglish_sentenceReading_ERROR";
    
    return "";
}



std::string ArabicHelperForGames::getFilenameInEnglish_shuffledSentence(std::string phoneme) {
    
    if (phoneme == "") return "";
    
    if (phoneme == "نهض عمر من سريره") return "Omar got up from his bed";
    if (phoneme == "أقف عند خط المشاة") return "I stand at the pedestrian strips";
    if (phoneme == "ابتعد الخروف عن القطيع") return "The sheep turned away from the flock";
    if (phoneme == "الخوخ حلو ولذيذ") return "The peach is sweet and delicious";
    if (phoneme == "انا احب الرياضة") return "I love sport";
    if (phoneme == "احلام ذكية ومهذبة") return "Ahlam is smart and polite";
    if (phoneme == "العب بالكرة الصغيرة") return "I play with the small ball";
    if (phoneme == "الغروب منظر جميل") return "The sunset view is nice";
    if (phoneme == "لعبة امل جديدة") return "The doll of Amal is new";
    if (phoneme == "احب امي وابي") return "I love my mom and dad";
    if (phoneme == "هض عمر من سرذهبت امي الى السوق") return "My mom went to the market"; // controllare?
    if (phoneme == "المعلم يشرح الدرس") return "The teacher explains the lesson";
    if (phoneme == "الولد يسمع نصيحة ابيه") return "The boy listen to his father advice";
    if (phoneme == "هذه الأشجار عالية") return "These trees are tall";
    if (phoneme == "مهند اهمل دروسه") return "Muhannad neglected his lessons";
    if (phoneme == "انا نجحت في الامتحان") return "I succeeded in the exam";
    if (phoneme == "ليث صديقي المفضل") return "Laith is my best friend";
    if (phoneme == "الاسماك تعيش في البحر") return "Fishs lives in the sea";
    if (phoneme == "الجزر ينمو تحت التراب") return "Carrotes grows under the soil";
    if (phoneme == "دخلت المعلمة الى الصف") return "The teacher entered to the class room";
    
    CCLOG("getFilenameInEnglish_shuffledSentence %s", phoneme.c_str());
    if (TEST_ENABLED) return "getFilenameInEnglish_shuffledSentence_ERROR";
    
    return "";
}

std::string ArabicHelperForGames::getFilenameInEnglish_blending(std::string phoneme) {
    
    if (phoneme == "") return "";
        
    if (phoneme == "اي") return "which";
	if (phoneme == "او") return "Or";
	if (phoneme == "يا") return "oh";
	if (phoneme == "بابا") return "Papa";
	if (phoneme == "باب") return "door";
	if (phoneme == "بيت") return "house";
	if (phoneme == "تاب") return "Repented";
	if (phoneme == "توت") return "blueberry";
	if (phoneme == "بات") return "Spend the night";
	if (phoneme == "بث") return "broadcast";
	if (phoneme == "ثوب") return "dress";
	if (phoneme == "ثابت") return "fixed";
	if (phoneme == "وثب") return "bounce";
	if (phoneme == "اثاث") return "forniture";
	if (phoneme == "تاج") return "Crown";
	if (phoneme == "جب") return "well";
	if (phoneme == "جواب") return "answer";
	if (phoneme == "جو") return "atmosphere";
	if (phoneme == "حب") return "love";
	if (phoneme == "حجر") return "stone";
	if (phoneme == "حج") return "pilgrimage";
	if (phoneme == "حوت") return "whale";
	if (phoneme == "خاب") return "disappointed";
	if (phoneme == "خوخ") return "Peach";
	if (phoneme == "تخت") return "bed";
	if (phoneme == "خبث") return "malice";
	if (phoneme == "داخ") return "nausea";
	if (phoneme == "جدي") return "grandfather";
	if (phoneme == "دب") return "bear";
	if (phoneme == "دجاج") return "chuckens";
	if (phoneme == "يد") return "hand";
	if (phoneme == "ذاب") return "thaw";
	if (phoneme == "ذاق") return "testa";
	if (phoneme == "ذم") return "vilify";
	if (phoneme == "اخذ") return "take";
	if (phoneme == "ورد") return "Came";
	if (phoneme == "دار") return "Turn";
	if (phoneme == "حبر") return "Ink";
	if (phoneme == "جار") return "neighbor";
	if (phoneme == "برج") return "tower";
	if (phoneme == "جزر") return "carrots";
	if (phoneme == "خبز") return "bread";
	if (phoneme == "زجاج") return "glass";
	if (phoneme == "زر") return "button";
	if (phoneme == "زيت") return "oil";
	if (phoneme == "ساح") return "dissolve";
	if (phoneme == "دبس") return "molasses";
	if (phoneme == "سرب") return "swarm";
	if (phoneme == "سد") return "dam";
	if (phoneme == "درس") return "lesson";
	if (phoneme == "خشب") return "wood";
	if (phoneme == "شراب") return "drink";
	if (phoneme == "شاب") return "young";
	if (phoneme == "شاي") return "tea";
	if (phoneme == "شيخ") return "Old man";
	if (phoneme == "صوص") return "chick";
	if (phoneme == "باص") return "bus";
	if (phoneme == "صاح") return "shout";
	if (phoneme == "صبي") return "boy";
	if (phoneme == "صيف") return "summer";
	if (phoneme == "ضرس") return "tooth";
	if (phoneme == "ضب") return "lizard";
	if (phoneme == "ضباب") return "fog";
	if (phoneme == "ضجيج") return "Nois";
	if (phoneme == "بيض") return "eggs";
	if (phoneme == "حطب") return "Wood for fire";
	if (phoneme == "طبق") return "dish";
	if (phoneme == "طوق") return "collar";
	if (phoneme == "سطر") return "line";
	if (phoneme == "خيط") return "sting";
	if (phoneme == "ظبي") return "antelope";
	if (phoneme == "حظ") return "Luck";
	if (phoneme == "حظر") return "Ban";
	if (phoneme == "مظلة") return "umbrella";
	if (phoneme == "لفظ") return "pronunciation";
	if (phoneme == "عود") return "lute";
	if (phoneme == "رعد") return "thunder";
	if (phoneme == "عرق") return "sweat";
	if (phoneme == "عش") return "Nest";
	if (phoneme == "زرع") return "sow";
	if (phoneme == "غابة") return "forest";
	if (phoneme == "غسق") return "twilight";
	if (phoneme == "غول") return "ogre";
	if (phoneme == "غضب") return "anger";
	if (phoneme == "تبغ") return "tobacco";
	if (phoneme == "فجل") return "radish";
	if (phoneme == "خفاش") return "bat";
	if (phoneme == "رف") return "Shelf";
	if (phoneme == "ظفر") return "nail";
	if (phoneme == "ضفدع") return "frog";
	if (phoneme == "قصر") return "palace";
	if (phoneme == "قطار") return "train";
	if (phoneme == "قطن") return "cotton";
	if (phoneme == "عقد") return "contract";
	if (phoneme == "قرد") return "monkey";
	if (phoneme == "كرز") return "Cherry";
	if (phoneme == "كتاب") return "book";
	if (phoneme == "كف") return "palm";
	if (phoneme == "كوخ") return "cottage";
	if (phoneme == "كتف") return "shoulder";
	if (phoneme == "ولد") return "boy";
	if (phoneme == "جبل") return "mount";
	if (phoneme == "فجل") return "radish";
	if (phoneme == "لوح") return "blackboard";
	if (phoneme == "كلب") return "Dog";
	if (phoneme == "قلم") return "pencil";
	if (phoneme == "ملح") return "salt";
	if (phoneme == "مطر") return "rain";
	if (phoneme == "قمر") return "moon";
	if (phoneme == "مشط") return "comb";
	if (phoneme == "عنب") return "grape";
	if (phoneme == "نجم") return "star";
	if (phoneme == "نفق") return "tunnel";
	if (phoneme == "نور") return "Light";
	if (phoneme == "نار") return "fire";
	if (phoneme == "وجه") return "face";
	if (phoneme == "هرم") return "pyramid";
	if (phoneme == "هدهد") return "hoopoe";
	if (phoneme == "نهر") return "river";
	if (phoneme == "سهل") return "plains";
	if (phoneme == "وقت") return "time";
	if (phoneme == "كوخ") return "cottage";
	if (phoneme == "دلو") return "bucket";
	if (phoneme == "وزن") return "weight";
	if (phoneme == "ورق") return "paper";
	if (phoneme == "يد") return "hand";
	if (phoneme == "سيف") return "sword";
	if (phoneme == "يخت") return "yacht";
	if (phoneme == "فيل") return "elephant";
	if (phoneme == "ذيل") return "Tail";
	if (phoneme == "انف") return "nose";
	if (phoneme == "ارنب") return "rabbit";
	if (phoneme == "مال") return "money";
	if (phoneme == "حبا") return "crawling";
	if (phoneme == "غفا") return "sleeps";
	if (phoneme == "باب") return "door";
	if (phoneme == "بطة") return "Duck";
	if (phoneme == "نبع") return "spring";
	if (phoneme == "حساب") return "calculation";
	if (phoneme == "حطب") return "Wood for fire";
	if (phoneme == "تمر") return "dates";
	if (phoneme == "تفاح") return "apple";
	if (phoneme == "مفتاح") return "key";
	if (phoneme == "يخت") return "yacht";
	if (phoneme == "وقت") return "time";
	if (phoneme == "ثعبان") return "snake";
	if (phoneme == "ثوب") return "dress";
	if (phoneme == "كثير") return "many";
	if (phoneme == "غيث") return "Rain";
	if (phoneme == "حادث") return "accident";
	if (phoneme == "جرس") return "bell";
	if (phoneme == "جبن") return "cheese";
	if (phoneme == "شجرة") return "tree";
	if (phoneme == "مرج") return "meadow";
	if (phoneme == "مهرج") return "clown";
	if (phoneme == "حبر") return "Ink";
	if (phoneme == "حصان") return "horse";
	if (phoneme == "بحر") return "sea";
	if (phoneme == "ملح") return "salt";
	if (phoneme == "ريح") return "wind";
	if (phoneme == "خشب") return "wood";
	if (phoneme == "خس") return "lettuce";
	if (phoneme == "نخيل") return "palm";
	if (phoneme == "خوخ") return "peach";
	if (phoneme == "سيخ") return "skewer";
	if (phoneme == "ديك") return "rooster";
	if (phoneme == "دولاب") return "tires";
	if (phoneme == "عدد") return "number";
	if (phoneme == "ورد") return "roses";
	if (phoneme == "مقعد") return "seat";
	if (phoneme == "ذهب") return "gold";
	if (phoneme == "ذباب") return "files";
	if (phoneme == "جذر") return "Root";
	if (phoneme == "تلميذ") return "student";
	if (phoneme == "قنفذ") return "hedgehog";
	if (phoneme == "رعد") return "thunder";
	if (phoneme == "رمان") return "pomergrante";
	if (phoneme == "حرف") return "letter";
	if (phoneme == "خضار") return "vegetable";
	if (phoneme == "جسر") return "bridge";
	if (phoneme == "زهرة") return "flower";
	if (phoneme == "زرافة") return "giraffe";
	if (phoneme == "ميزان") return "balance";
	if (phoneme == "كنز") return "treasure";
	if (phoneme == "كرز") return "cherris";
	if (phoneme == "سلم") return "ladder";
	if (phoneme == "سحاب") return "clouds";
	if (phoneme == "اسم") return "name";
	if (phoneme == "جرس") return "bell";
	if (phoneme == "درس") return "lesson";
	if (phoneme == "شمع") return "candle";
	if (phoneme == "شال") return "shawl";
	if (phoneme == "مشط") return "comb";
	if (phoneme == "قماش") return "fabric";
	if (phoneme == "عش") return "nest";
	if (phoneme == "صاروخ") return "missil";
	if (phoneme == "صندوق") return "box";
	if (phoneme == "عصفور") return "bird";
	if (phoneme == "صابون") return "Soap";
	if (phoneme == "مقص") return "sissors";
	if (phoneme == "ضبع") return "heyna";
	if (phoneme == "ضفدع") return "frog";
	if (phoneme == "ابيض") return "white";
	if (phoneme == "بيض") return "Eggs";
	if (phoneme == "طبل") return "drum";
	if (phoneme == "طاووس") return "peacock";
	if (phoneme == "منطاد") return "airship";
	if (phoneme == "وسط") return "center";
	if (phoneme == "سوط") return "whip";
	if (phoneme == "ظفر") return "nail";
	if (phoneme == "ظل") return "shadow";
	if (phoneme == "عظم") return "bone";
	if (phoneme == "حفظ") return "save";
	if (phoneme == "حظ") return "luck";
	if (phoneme == "عود") return "lute";
	if (phoneme == "عصفور") return "bird";
	if (phoneme == "ملعقة") return "spoon";
	if (phoneme == "نبع") return "spring";
	if (phoneme == "شمع") return "candle";
	if (phoneme == "غرفة") return "room";
	if (phoneme == "غصن") return "Branch";
	if (phoneme == "رغيف") return "Piece of bread";
	if (phoneme == "صدغ") return "Temple on face";
	if (phoneme == "تبغ") return "tobacco";
	if (phoneme == "فيل") return "elephant";
	if (phoneme == "فرس") return "horse_female";
	if (phoneme == "رفيق") return "friend";
	if (phoneme == "هاتف.") return "telephon";
	if (phoneme == "رف") return "shelf";
	if (phoneme == "قرد") return "monkey";
	if (phoneme == "قمر") return "Moon";
	if (phoneme == "بقرة") return "cow";
	if (phoneme == "ساق") return "Leg";
	if (phoneme == "بوق") return "trumpet";
	if (phoneme == "كرة") return "ball";
	if (phoneme == "كتاب") return "book";
	if (phoneme == "سكين") return "knife";
	if (phoneme == "شباك") return "window";
	if (phoneme == "شوك") return "Thorns";
	if (phoneme == "لوح") return "blackboard";
	if (phoneme == "لعبة") return "game";
	if (phoneme == "ملعب") return "Stadium";
	if (phoneme == "ليل") return "night";
	if (phoneme == "فجل") return "radish";
	if (phoneme == "موز") return "banana";
	if (phoneme == "ملابس") return "clothes";
	if (phoneme == "نمر") return "tiger";
	if (phoneme == "رقم") return "number";
	if (phoneme == "علم") return "science";
	if (phoneme == "نفق") return "tunnel";
	if (phoneme == "نهر") return "river";
	if (phoneme == "منزل") return "House";
	if (phoneme == "لسان") return "tongue";
	if (phoneme == "جرن") return "sink";
	if (phoneme == "هرة") return "cat";
	if (phoneme == "هدهد") return "hoopoe";
	if (phoneme == "سهم") return "arrow";
	if (phoneme == "وجه") return "face";
      
    CCLOG("getFilenameInEnglish_blending %s", phoneme.c_str());
    if (TEST_ENABLED) return "getFilenameInEnglish_blending_ERROR";
    
    return "";
}
