#include "ArabicHelper.h"
#include "../StringUtility.h"
#include "../../AppMacros.h"

ArabicHelper::ArabicHelper() {
    
    CCLOG("ArabicHelper()");
    
    
}


Label* ArabicHelper::createLabel(std::string text, float fontSize, bool setInArabic) {
    
    Label* label;
    
    if (setInArabic) {
        label = Label::createWithSystemFont( getInArabic(text) , "common/fonts/Arabic-Regular.ttf", fontSize);
    } else {
        label = Label::createWithSystemFont(text, "common/fonts/Arabic-Regular.ttf", fontSize);
    }
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        label->setHeight(fontSize*1.5);
    #elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        label->setHeight(fontSize*1.3);
    #else
        CCLOG("No handled platform in ArabicHelper::createLabel");
    #endif
  
    return label;
    
}


std::string ArabicHelper::getFilenameInEnglish(std::string phoneme) {
    
    CCLOG("sono in getFilenameInEnglish con %s", phoneme.c_str());
    
    if (phoneme == "") return "";
    
    
    // blending episode 3
    
    if (phoneme == "اي") return "which";
    if (phoneme == "او") return "or";
    if (phoneme == "يا") return "oh";
    if (phoneme == "بابا") return "papa";
    if (phoneme == "باب") return "door";
    if (phoneme == "بيت") return "house";
    if (phoneme == "تاب") return "repented";
    if (phoneme == "توت") return "blueberry";
    if (phoneme == "بات") return "spend_the_night";
    if (phoneme == "بث") return "broadcast";
    if (phoneme == "ثوب") return "dress";
    if (phoneme == "ثابت") return "fixed";
    if (phoneme == "وثب") return "bounce";
    if (phoneme == "اثاث") return "forniture";
    if (phoneme == "تاج") return "crown";
    if (phoneme == "جب") return "well";
    if (phoneme == "جواب") return "answer";
    if (phoneme == "جو") return "atmosphere";
    if (phoneme == "حب") return "love";
    if (phoneme == "حجر") return "stone";
    if (phoneme == "حج") return "pilgrimage";
    if (phoneme == "حوت") return "whale";
    if (phoneme == "خاب") return "disappointed";
    if (phoneme == "خوخ") return "peach";
    if (phoneme == "تخت") return "bed";
    if (phoneme == "خبث") return "malice";
    if (phoneme == "داخ") return "nausea";
    if (phoneme == "جدي") return "grandfather";
    if (phoneme == "دب") return "bear";
    if (phoneme == "دجاج") return "chickens";
    if (phoneme == "يد") return "hand";
    if (phoneme == "ذاب") return "thaw";
    if (phoneme == "ذاق") return "testa";
    if (phoneme == "ذم") return "vilify";
    if (phoneme == "اخذ") return "take";
    if (phoneme == "ورد") return "came";
    if (phoneme == "دار") return "turn";
    if (phoneme == "حبر") return "ink";
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
    if (phoneme == "شيخ") return "old_man";
    if (phoneme == "صوص") return "chick";
    if (phoneme == "باص") return "bus";
    if (phoneme == "صاح") return "shout";
    if (phoneme == "صبي") return "boy";
    if (phoneme == "صيف") return "summer";
    if (phoneme == "ضرس") return "tooth";
    if (phoneme == "ضب") return "lizard";
    if (phoneme == "ضباب") return "fog";
    if (phoneme == "ضجيج") return "nois";
    if (phoneme == "بيض") return "eggs";
    if (phoneme == "حطب") return "wood_for_fire";
    if (phoneme == "طبق") return "dish";
    if (phoneme == "طوق") return "collar";
    if (phoneme == "سطر") return "line";
    if (phoneme == "خيط") return "sting";
    if (phoneme == "ظبي") return "antelope";
    if (phoneme == "حظ") return "luck";
    if (phoneme == "حظر") return "ban";
    if (phoneme == "مظلة") return "umbrella";
    if (phoneme == "لفظ") return "pronunciation";
    if (phoneme == "عود") return "lute";
    if (phoneme == "رعد") return "thunder";
    if (phoneme == "عرق") return "sweat";
    if (phoneme == "عش") return "nest";
    if (phoneme == "زرع") return "sow";
    if (phoneme == "غابة") return "forest";
    if (phoneme == "غسق") return "twilight";
    if (phoneme == "غول") return "ogre";
    if (phoneme == "غضب") return "anger";
    if (phoneme == "تبغ") return "tobacco";
    if (phoneme == "فجل") return "radish";
    if (phoneme == "خفاش") return "bat";
    if (phoneme == "رف") return "shelf";
    if (phoneme == "ظفر") return "nail";
    if (phoneme == "ضفدع") return "frog";
    if (phoneme == "قصر") return "palace";
    if (phoneme == "قطار") return "train";
    if (phoneme == "قطن") return "cotton";
    if (phoneme == "عقد") return "contract";
    if (phoneme == "قرد") return "monkey";
    if (phoneme == "كرز") return "cherry";
    if (phoneme == "كتاب") return "book";
    if (phoneme == "كف") return "palm";
    if (phoneme == "كوخ") return "cottage";
    if (phoneme == "كتف") return "shoulder";
    if (phoneme == "ولد") return "boy";
    if (phoneme == "جبل") return "mount";
    if (phoneme == "فجل") return "radish";
    if (phoneme == "لوح") return "blackboard";
    if (phoneme == "كلب") return "dog";
    if (phoneme == "قلم") return "pencil";
    if (phoneme == "ملح") return "salt";
    if (phoneme == "مطر") return "rain";
    if (phoneme == "قمر") return "moon";
    if (phoneme == "مشط") return "comb";
    if (phoneme == "عنب") return "grape";
    if (phoneme == "نجم") return "star";
    if (phoneme == "نفق") return "tunnel";
    if (phoneme == "نور") return "light";
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
    if (phoneme == "ذيل") return "tail";
    
    
    // blending episode 4
    
    if (phoneme == "انف") return "nose";
    if (phoneme == "ارنب") return "rabbit";
    if (phoneme == "مال") return "money";
    if (phoneme == "حبا") return "crawling";
    if (phoneme == "غفا") return "sleeps";
    if (phoneme == "باب") return "door";
    if (phoneme == "بطة") return "duck";
    if (phoneme == "نبع") return "spring";
    if (phoneme == "حساب") return "calculation";
    if (phoneme == "حطب") return "wood_for_fire";
    if (phoneme == "تمر") return "dates";
    if (phoneme == "تفاح") return "apple";
    if (phoneme == "مفتاح") return "key";
    if (phoneme == "يخت") return "yacht";
    if (phoneme == "وقت") return "time";
    if (phoneme == "ثعبان") return "snake";
    if (phoneme == "ثوب") return "dress";
    if (phoneme == "كثير") return "many";
    if (phoneme == "غيث") return "rain";
    if (phoneme == "حادث") return "accident";
    if (phoneme == "جرس") return "bell";
    if (phoneme == "جبن") return "cheese";
    if (phoneme == "شجرة") return "tree";
    if (phoneme == "مرج") return "meadow";
    if (phoneme == "مهرج") return "clown";
    if (phoneme == "حبر") return "ink";
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
    if (phoneme == "جذر") return "root";
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
    if (phoneme == "صابون") return "soap";
    if (phoneme == "مقص") return "sissors";
    if (phoneme == "ضبع") return "heyna";
    if (phoneme == "ضفدع") return "frog";
    if (phoneme == "ابيض") return "white";
    if (phoneme == "بيض") return "eggs";
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
    if (phoneme == "غصن") return "branch";
    if (phoneme == "رغيف") return "bread"; // piece of bread
    if (phoneme == "صدغ") return "tpemple"; // temple on face
    if (phoneme == "تبغ") return "tobacco";
    if (phoneme == "فيل") return "elephant";
    if (phoneme == "فرس") return "horse_female";
    if (phoneme == "رفيق") return "friend";
    if (phoneme == "هاتف") return "telephon";
    if (phoneme == "رف") return "shelf";
    if (phoneme == "قرد") return "monkey";
    if (phoneme == "قمر") return "moon";
    if (phoneme == "بقرة") return "cow";
    if (phoneme == "ساق") return "leg";
    if (phoneme == "بوق") return "trumpet";
    if (phoneme == "كرة") return "ball";
    if (phoneme == "كتاب") return "book";
    if (phoneme == "سكين") return "knife";
    if (phoneme == "شباك") return "window";
    if (phoneme == "شوك") return "thorns";
    if (phoneme == "لوح") return "blackboard";
    if (phoneme == "لعبة") return "game";
    if (phoneme == "ملعب") return "stadium";
    if (phoneme == "ليل") return "night";
    if (phoneme == "فجل") return "radish";
    if (phoneme == "موز") return "banana";
    if (phoneme == "ملابس") return "clothes";
    if (phoneme == "نمر") return "tiger";
    if (phoneme == "رقم") return "number";
    if (phoneme == "علم") return "science";
    if (phoneme == "نفق") return "tunnel";
    if (phoneme == "نهر") return "river";
    if (phoneme == "منزل") return "house";
    if (phoneme == "لسان") return "tongue";
    if (phoneme == "جرن") return "sink";
    if (phoneme == "هرة") return "cat";
    if (phoneme == "هدهد") return "hoopoe";
    if (phoneme == "سهم") return "arrow";
    if (phoneme == "وجه") return "face";
    
   
    
    
    // word reading carla

    if (phoneme == "اسد") return "lion";
    if (phoneme == "امير") return "prince";
    if (phoneme == "ساق") return "leg";
    if (phoneme == "باص") return "bus";
    if (phoneme == "عصا") return "stick";
    if (phoneme == "بيت") return "home";
    if (phoneme == "برد") return "cold";
    if (phoneme == "حبل") return "rope";
    if (phoneme == "سبع") return "panther";
    if (phoneme == "ذباب") return "flies";
    if (phoneme == "تين") return "figs";
    if (phoneme == "تاج") return "crown";
    if (phoneme == "كتاب") return "book";
    if (phoneme == "برتقال") return "orange";
    if (phoneme == "توت") return "blueberry";
    if (phoneme == "ثلج") return "snow";
    if (phoneme == "ثور") return "bull";
    if (phoneme == "مثلث") return "triangle";
    if (phoneme == "ممثل") return "actor";
    if (phoneme == "ليث") return "panthera_leo";
    if (phoneme == "جمل") return "camel";
    if (phoneme == "جبل") return "mount";
    if (phoneme == "حجر") return "stone";
    if (phoneme == "فجل") return "radish";
    if (phoneme == "برج") return "tower";
    if (phoneme == "حوت") return "whale";
    if (phoneme == "حقل") return "field";
    if (phoneme == "فحم") return "coal";
    if (phoneme == "لحم") return "meat";
    if (phoneme == "تمساح") return "crocodile";
    if (phoneme == "خيط") return "string";
    if (phoneme == "خبز") return "bread";
    if (phoneme == "صخر") return "rock";
    if (phoneme == "نخيل") return "palm";
    if (phoneme == "فخ") return "trap";
    if (phoneme == "دار") return "house";
    if (phoneme == "دب") return "bear";
    if (phoneme == "جدي") return "grandfather";
    if (phoneme == "بدر") return "full_moon";
    if (phoneme == "سد") return "dam";
    if (phoneme == "ذيل") return "tail";
    if (phoneme == "ذرة") return "corn";
    if (phoneme == "اذن") return "ear";
    if (phoneme == "بذور") return "seeds";
    if (phoneme == "جرذ") return "rat";
    if (phoneme == "رمل") return "sand";
    if (phoneme == "رجل") return "foot";
    if (phoneme == "كرسي") return "chair";
    if (phoneme == "برج") return "tower";
    if (phoneme == "قمر") return "moon";
    if (phoneme == "زيت") return "oil";
    if (phoneme == "زر") return "button";
    if (phoneme == "جزر") return "carrot";
    if (phoneme == "ازرق") return "blue";
    if (phoneme == "لوز") return "almonds";
    if (phoneme == "سمك") return "fish";
    if (phoneme == "سلك") return "cable";
    if (phoneme == "نسر") return "eagle";
    if (phoneme == "رسم") return "draw";
    if (phoneme == "فرس") return "horse";
    if (phoneme == "شمس") return "sun";
    if (phoneme == "شبل") return "lion_cub";
    if (phoneme == "فراشة") return "butterfly";
    if (phoneme == "عطش") return "thirst";
    if (phoneme == "صحن") return "dish";
    if (phoneme == "صقر") return "falcon";
    if (phoneme == "بصل") return "onions";
    if (phoneme == "قصة") return "a_story";
    if (phoneme == "صوص") return "chick";
    if (phoneme == "ضباب") return "fog";
    if (phoneme == "ضرس") return "tooth";
    if (phoneme == "فضة") return "silver";
    if (phoneme == "هضبة") return "hill";
    if (phoneme == "مرض") return "diesea"; // what does this mean?
    if (phoneme == "طفل") return "baby";
    if (phoneme == "طير") return "bird";
    if (phoneme == "حطب") return "wood_for_fire";
    if (phoneme == "قطار") return "train";
    if (phoneme == "مشط") return "comb";
    if (phoneme == "ظرف") return "envelope";
    if (phoneme == "ظبي") return "fawn";
    if (phoneme == "نظارة") return "eyeglasses";
    if (phoneme == "مظلة") return "umbrella";
    if (phoneme == "غليظ") return "thick";
    if (phoneme == "عين") return "eye";
    if (phoneme == "عسل") return "honey";
    if (phoneme == "رعد") return "thunder";
    if (phoneme == "ثعلب") return "fox";
    if (phoneme == "مصنع") return "factory";
    if (phoneme == "غيمة") return "cloud";
    if (phoneme == "غزال") return "deer";
    if (phoneme == "نغم") return "tune";
    if (phoneme == "مغني") return "singer";
    if (phoneme == "صمغ") return "glue";
    if (phoneme == "فم") return "mouth";
    if (phoneme == "فول") return "bean";
    if (phoneme == "قفل") return "a_lock";
    if (phoneme == "فلفل") return "pepper";
    if (phoneme == "صيف") return "summer";
    if (phoneme == "قلم") return "pencil";
    if (phoneme == "قفص") return "cage";
    if (phoneme == "عقد") return "necklacey";
    if (phoneme == "ملعقة") return "spoon";
    if (phoneme == "بندق") return "nut";
    if (phoneme == "كلب") return "dog";
    if (phoneme == "كرسي") return "chair";
    if (phoneme == "سمكة") return "fish";
    if (phoneme == "ديك") return "rooster";
    if (phoneme == "مفك") return "screwdriver";
    if (phoneme == "لبن") return "yougurt";
    if (phoneme == "لقلق") return "stork";
    if (phoneme == "تلفاز") return "tv";
    if (phoneme == "قلب") return "heart";
    if (phoneme == "سهل") return "plain";
    if (phoneme == "مطر") return "rain";
    if (phoneme == "مدرسة") return "school";
    if (phoneme == "رمان") return "pomegranate";
    if (phoneme == "نمل") return "ant";
    if (phoneme == "خاتم") return "ring";
    if (phoneme == "نار") return "fire";
    if (phoneme == "نجم") return "star";
    if (phoneme == "عنب") return "grapes";
    if (phoneme == "سنابل") return "wheat_spikes";
    if (phoneme == "لحن") return "melody";
    if (phoneme == "هرم") return "pyramid";
    if (phoneme == "هدية") return "gift";
    if (phoneme == "نهر") return "river";
    if (phoneme == "فهد") return "leopard";
    if (phoneme == "منبه") return "alarm_clock";
    
    CCLOG("getFilenameInEnglish %s", phoneme.c_str());
    if (TEST_ENABLED) return "getFilenameInEnglish_ERROR";
    
    return "";
    
}


std::string ArabicHelper::getInArabic(std::string phoneme) {
    
    if (phoneme == "") return "";
 

    
    // base phonemes
    std::string base = getInArabic_basePhonemes(phoneme);
    if (base != "ERROR")  return base;
    
    
    
    
    // episode 3 - accents - in games
    std::string forAccentsEpisode3 = getInArabic_accents(phoneme);
    if (forAccentsEpisode3 != "ERROR")  return forAccentsEpisode3;
    
    
    
    
    // episode 1 - in watchman and inventory
    if ( StringUtility::endsWith(phoneme, "#ep1") ){
        std::string forEp1b = phoneme.substr(0, phoneme.find("#"));
        std::string baseEp1 = getInArabic_basePhonemes(forEp1b);
        if (baseEp1 != "ERROR")  return baseEp1;
    }
    
    // episode 3 - in watchman and inventory
    if ( StringUtility::endsWith(phoneme, "#ep3") ){
        std::string forEp3b = phoneme.substr(0, phoneme.find("#"));
        std::string baseEp3 = getInArabic_basePhonemes(forEp3b);
        if (baseEp3 != "ERROR")  return baseEp3;
    }
    

    

    
    // episode 3 - blending
    std::string forBlendingEpisode3 = getInArabic_blendingEpisode3(phoneme);
    if (forBlendingEpisode3 != "ERROR")  return forBlendingEpisode3;
    
    
    // episode 4 - blending
    std::string forBlendingEpisode4 = getInArabic_blendingEpisode4(phoneme);
    if (forBlendingEpisode4 != "ERROR")  return forBlendingEpisode4;
    
    // episode 5 - blending
    std::string forBlendingEpisode5 = getInArabic_blendingEpisode5(phoneme);
    if (forBlendingEpisode5 != "ERROR")  return forBlendingEpisode5;
    
    
    
    
    // episode 4 - wordreading
    std::string forWordreadingEpisode4 = getInArabic_wordreadingEpisode4(phoneme);
    if (forWordreadingEpisode4 != "ERROR")  return forWordreadingEpisode4;
    
    // episode 5 - sentencereading
    std::string forSentencereadingEpisode5 = getInArabic_sentencereadingEpisode5(phoneme);
    if (forSentencereadingEpisode5 != "ERROR")  return forSentencereadingEpisode5;
    
    
    
    CCLOG("getInArabic - UTF8_ERROR %s", phoneme.c_str());
    if (TEST_ENABLED) return "UTF8_ERROR";
   
    return "";
}

std::string ArabicHelper::getInLetter(std::string phoneme) {
    if (phoneme == "\xd8\xa7") return "a";
    if (phoneme == "\xd8\xa8") return "b";
    if (phoneme == "\xd8\xaa") return "t";
    if (phoneme == "\xd8\xab") return "th";
    if (phoneme == "\xd8\xac") return "g";
    if (phoneme == "\xd8\xad") return "ha";
    if (phoneme == "\xd8\xae") return "ja";
    if (phoneme == "\xd8\xaf") return "d";
    if (phoneme == "\xd8\xb0") return "dh";
    if (phoneme == "\xd8\xb1") return "r";
    if (phoneme == "\xd8\xb2") return "z";
    if (phoneme == "\xd8\xb3") return "s";
    if (phoneme == "\xd8\xb4") return "sh";
    if (phoneme == "\xd8\xb5") return "sad";
    if (phoneme == "\xd8\xb6") return "daad";
    if (phoneme == "\xd8\xb7") return "taa";
    if (phoneme == "\xd8\xb8") return "zaa";
    if (phoneme == "\xd8\xb9") return "aa";
    if (phoneme == "\xd8\xba") return "gh";
    if (phoneme == "\xd9\x81") return "f";
    if (phoneme == "\xd9\x82") return "q";
    if (phoneme == "\xd9\x83") return "k";
    if (phoneme == "\xd9\x84") return "l";
    if (phoneme == "\xd9\x85") return "m";
    if (phoneme == "\xd9\x86") return "n";
    if (phoneme == "\xd9\x87") return "h";
    if (phoneme == "\xd9\x88") return "w";
    if (phoneme == "\xd9\x8a") return "y";
    
    
    
    
    
    /////accents
    
    
    
    if (phoneme == "اا") return "a_a";
    if (phoneme ==  "اي") return "a_i";
    if (phoneme == "او") return  "a_u";
    
    if (phoneme == "با") return "b_a";
    if (phoneme ==  "بي") return "b_i";
    if (phoneme ==  "بو") return "b_u";
    
    if (phoneme ==  "تا") return "t_a";
    if (phoneme ==  "تي") return "t_i";
    if (phoneme ==  "تو") return "t_u";
    
    if (phoneme == "ثا") return "th_a";
    if (phoneme == "ثي") return "th_i";
    if (phoneme == "ثو") return "th_u";
    
    if (phoneme == "جا") return "g_a";
    if (phoneme == "جي") return "g_i";
    if (phoneme == "جو") return "g_u";
    
    if (phoneme == "حا") return "ha_a";
    if (phoneme == "حي") return "ha_i";
    if (phoneme == "حو") return "ha_u";
    
    if (phoneme == "خا") return "ja_a";
    if (phoneme == "خي") return "ja_i";
    if (phoneme == "خو") return "ja_u";
    
    if (phoneme == "دا")    return "d_a";
    if (phoneme == "دي")    return "d_i";
    if (phoneme == "دو")    return "d_u";
    
    if (phoneme == "ذا")   return "dh_a";
    if (phoneme == "ذي")   return "dh_i";
    if (phoneme == "ذو")   return "dh_u";
    
    if (phoneme == "را")    return "r_a";
    if (phoneme == "ري")    return "r_i";
    if (phoneme == "رو")    return "r_u";
    
    if (phoneme == "زا")    return "z_a";
    if (phoneme == "زي")    return "z_i";
    if (phoneme == "زو")    return "z_u";
    
    if (phoneme == "سا")    return "s_a";
    if (phoneme == "سي")    return "s_i";
    if (phoneme == "سو")    return "s_u";
    
    if (phoneme == "شا")   return "sh_a";
    if (phoneme == "شي")   return "sh_i";
    if (phoneme == "شو")   return "sh_u";
    
    if (phoneme == "صا")  return "sad_a";
    if (phoneme == "صي")  return "sad_i";
    if (phoneme == "صو")  return "sad_u";
    
    if (phoneme == "ضا") return "daad_a";
    if (phoneme == "ضي") return "daad_i";
    if (phoneme == "ضو") return "daad_u";
    
    if (phoneme == "طا")  return "taa_a";
    if (phoneme == "طي")  return "taa_i";
    if (phoneme == "طو")  return "taa_u";
    
    if (phoneme == "ظا")  return "zaa_a";
    if (phoneme == "ظي")  return "zaa_i";
    if (phoneme == "ظو")  return "zaa_u";
    
    if (phoneme == "عا")   return "aa_a";
    if (phoneme == "عي")   return "aa_i";
    if (phoneme == "عو")   return "aa_u";
    
    if (phoneme == "غا")   return "gh_a";
    if (phoneme == "غي")   return "gh_i";
    if (phoneme == "غو")   return "gh_u";
    
    if (phoneme == "فا")    return "f_a";
    if (phoneme == "في")    return "f_i";
    if (phoneme == "فو")    return "f_u";
    
    if (phoneme == "قا")    return "q_a";
    if (phoneme == "قي")    return "q_i";
    if (phoneme == "قو")    return "q_u";
    
    if (phoneme == "كا")    return "k_a";
    if (phoneme == "كي")    return "k_i";
    if (phoneme == "كو")    return "k_u";
    
    if (phoneme == "لا")    return "l_a";
    if (phoneme == "لي")    return "l_i";
    if (phoneme == "لو")    return "l_u";
    
    if (phoneme == "ما")    return "m_a";
    if (phoneme == "مي")    return "m_i";
    if (phoneme == "مو")    return "m_u";
    
    if (phoneme == "نا")    return "n_a";
    if (phoneme == "ني")    return "n_i";
    if (phoneme == "نو")    return "n_u";
    
    if (phoneme == "ها")    return "h_a";
    if (phoneme == "هي")    return "h_i";
    if (phoneme == "هو")    return "h_u";
    
    if (phoneme == "وا")    return "w_a";
    if (phoneme == "وي")    return "w_i";
    if (phoneme == "وو")    return "w_u";
    
    if (phoneme == "يا")    return "y_a";
    if (phoneme == "يي")    return "y_i";
    if (phoneme == "يو")    return "y_u";
    
    // end accents
    
    
    CCLOG("getInLetter - UTF8_ERROR %s", phoneme.c_str());
    if (TEST_ENABLED) return "UTF8_ERROR";
    
    return "";
}

std::string ArabicHelper::getInArabic_basePhonemes(std::string phoneme) {
    
    if (phoneme == "a") return "\xd8\xa7";
    if (phoneme == "b")    return "\xd8\xa8";
    if (phoneme == "t")    return "\xd8\xaa";
    if (phoneme == "th")   return "\xd8\xab";
    if (phoneme == "g")    return "\xd8\xac";
    if (phoneme == "ha")   return "\xd8\xad";
    if (phoneme == "ja")   return "\xd8\xae";
    if (phoneme == "d")    return "\xd8\xaf";
    if (phoneme == "dh")   return "\xd8\xb0";
    if (phoneme == "r")    return "\xd8\xb1";
    if (phoneme == "z")    return "\xd8\xb2";
    if (phoneme == "s")    return "\xd8\xb3";
    if (phoneme == "sh")   return "\xd8\xb4";
    if (phoneme == "sad")  return "\xd8\xb5";
    if (phoneme == "daad") return "\xd8\xb6";
    if (phoneme == "taa")  return "\xd8\xb7";
    if (phoneme == "zaa")  return "\xd8\xb8";
    if (phoneme == "aa")   return "\xd8\xb9";
    if (phoneme == "gh")   return "\xd8\xba";
    if (phoneme == "f")    return "\xd9\x81";
    if (phoneme == "q")    return "\xd9\x82";
    if (phoneme == "k")    return "\xd9\x83";
    if (phoneme == "l")    return "\xd9\x84";
    if (phoneme == "m")    return "\xd9\x85";
    if (phoneme == "n")    return "\xd9\x86";
    if (phoneme == "h")    return "\xd9\x87";
    if (phoneme == "w")    return "\xd9\x88";
    if (phoneme == "y")    return "\xd9\x8a";
    
    
    //extra
    if (phoneme == "hamza")    return "ء";
    
    if (phoneme == "forkeyboard1")    return "ى";
    if (phoneme == "forkeyboard2")    return "ئ";
    if (phoneme == "forkeyboard3")    return "ؤ";
    if (phoneme == "forkeyboard4")    return "ة";
    if (phoneme == "forkeyboard5")    return "آ";
    if (phoneme == "forkeyboard6")    return "إ";
    if (phoneme == "forkeyboard7")    return "أ";
    
    return "ERROR";
}

std::string ArabicHelper::getInArabic_accents(std::string phoneme) {
    
    if (phoneme == "a_a")    return "اا";
    if (phoneme == "a_i")    return "اي";
    if (phoneme == "a_u")    return "او";
    
    if (phoneme == "b_a")    return "با";
    if (phoneme == "b_i")    return "بي";
    if (phoneme == "b_u")    return "بو";
    
    if (phoneme == "t_a")    return "تا";
    if (phoneme == "t_i")    return "تي";
    if (phoneme == "t_u")    return "تو";
    
    if (phoneme == "th_a")   return "ثا";
    if (phoneme == "th_i")   return "ثي";
    if (phoneme == "th_u")   return "ثو";
    
    if (phoneme == "g_a")    return "جا";
    if (phoneme == "g_i")    return "جي";
    if (phoneme == "g_u")    return "جو";
    
    if (phoneme == "ha_a")   return "حا";
    if (phoneme == "ha_i")   return "حي";
    if (phoneme == "ha_u")   return "حو";
    
    if (phoneme == "ja_a")   return "خا";
    if (phoneme == "ja_i")   return "خي";
    if (phoneme == "ja_u")   return "خو";
    
    if (phoneme == "d_a")    return "دا";
    if (phoneme == "d_i")    return "دي";
    if (phoneme == "d_u")    return "دو";
    
    if (phoneme == "dh_a")   return "ذا";
    if (phoneme == "dh_i")   return "ذي";
    if (phoneme == "dh_u")   return "ذو";
    
    if (phoneme == "r_a")    return "را";
    if (phoneme == "r_i")    return "ري";
    if (phoneme == "r_u")    return "رو";
    
    if (phoneme == "z_a")    return "زا";
    if (phoneme == "z_i")    return "زي";
    if (phoneme == "z_u")    return "زو";
    
    if (phoneme == "s_a")    return "سا";
    if (phoneme == "s_i")    return "سي";
    if (phoneme == "s_u")    return "سو";
    
    if (phoneme == "sh_a")   return "شا";
    if (phoneme == "sh_i")   return "شي";
    if (phoneme == "sh_u")   return "شو";
    
    if (phoneme == "sad_a")  return "صا";
    if (phoneme == "sad_i")  return "صي";
    if (phoneme == "sad_u")  return "صو";
    
    if (phoneme == "daad_a") return "ضا";
    if (phoneme == "daad_i") return "ضي";
    if (phoneme == "daad_u") return "ضو";
    
    if (phoneme == "taa_a")  return "طا";
    if (phoneme == "taa_i")  return "طي";
    if (phoneme == "taa_u")  return "طو";
    
    if (phoneme == "zaa_a")  return "ظا";
    if (phoneme == "zaa_i")  return "ظي";
    if (phoneme == "zaa_u")  return "ظو";
    
    if (phoneme == "aa_a")   return "عا";
    if (phoneme == "aa_i")   return "عي";
    if (phoneme == "aa_u")   return "عو";
    
    if (phoneme == "gh_a")   return "غا";
    if (phoneme == "gh_i")   return "غي";
    if (phoneme == "gh_u")   return "غو";
    
    if (phoneme == "f_a")    return "فا";
    if (phoneme == "f_i")    return "في";
    if (phoneme == "f_u")    return "فو";
    
    if (phoneme == "q_a")    return "قا";
    if (phoneme == "q_i")    return "قي";
    if (phoneme == "q_u")    return "قو";
    
    if (phoneme == "k_a")    return "كا";
    if (phoneme == "k_i")    return "كي";
    if (phoneme == "k_u")    return "كو";
    
    if (phoneme == "l_a")    return "لا";
    if (phoneme == "l_i")    return "لي";
    if (phoneme == "l_u")    return "لو";
    
    if (phoneme == "m_a")    return "ما";
    if (phoneme == "m_i")    return "مي";
    if (phoneme == "m_u")    return "مو";
    
    if (phoneme == "n_a")    return "نا";
    if (phoneme == "n_i")    return "ني";
    if (phoneme == "n_u")    return "نو";
    
    if (phoneme == "h_a")    return "ها";
    if (phoneme == "h_i")    return "هي";
    if (phoneme == "h_u")    return "هو";
    
    if (phoneme == "w_a")    return "وا";
    if (phoneme == "w_i")    return "وي";
    if (phoneme == "w_u")    return "وو";
    
    if (phoneme == "y_a")    return "يا";
    if (phoneme == "y_i")    return "يي";
    if (phoneme == "y_u")    return "يو";
    
    return "ERROR";
}


std::string ArabicHelper::getInArabic_blendingEpisode3(std::string phoneme) {
    
     // episode 3 - blending
    
    // watchman 1
    
    if (phoneme == "Blending_ep3_w1_1_p1") return "و#ا";
    if (phoneme == "Blending_ep3_w1_1_p2") return "ا#ي";
    if (phoneme == "Blending_ep3_w1_1_p3") return "ا#و";
    if (phoneme == "Blending_ep3_w1_1_p4") return "ي#ا";
    
    if (phoneme == "Blending_ep3_w1_2_p1") return "ب#و";
    if (phoneme == "Blending_ep3_w1_2_p2") return "ب#ا#ب#ا";
    if (phoneme == "Blending_ep3_w1_2_p3") return "ب#ا#ب";
    
    if (phoneme == "Blending_ep3_w1_3_p1") return "ب#ت";
    if (phoneme == "Blending_ep3_w1_3_p2") return "ب#ي#ت";
    if (phoneme == "Blending_ep3_w1_3_p3") return "ت#ا#ب";
    if (phoneme == "Blending_ep3_w1_3_p4") return "ت#و#ت";
    if (phoneme == "Blending_ep3_w1_3_p5") return "ب#ا#ت";
    
    if (phoneme == "Blending_ep3_w1_4_p1") return "ب#ث";
    if (phoneme == "Blending_ep3_w1_4_p2") return "ث#و#ب";
    if (phoneme == "Blending_ep3_w1_4_p3") return "ث#ا#ب#ت";
    if (phoneme == "Blending_ep3_w1_4_p4") return "و#ث#ب";
    if (phoneme == "Blending_ep3_w1_4_p5") return "ا#ث#ا#ث";
    
    // watchman 2
    
    if (phoneme == "Blending_ep3_w2_1_p1") return "ت#ا#ج";
    if (phoneme == "Blending_ep3_w2_1_p2") return "ج#ب";
    if (phoneme == "Blending_ep3_w2_1_p3") return " ج#و#ا#ب";
    if (phoneme == "Blending_ep3_w2_1_p4") return "ج#و";
    
    if (phoneme == "Blending_ep3_w2_2_p1") return "ح#ب";
    if (phoneme == "Blending_ep3_w2_2_p2") return "ح#ج#ر";
    if (phoneme == "Blending_ep3_w2_2_p3") return "ح#ج";
    if (phoneme == "Blending_ep3_w2_2_p4") return "ح#و#ت";
    
    if (phoneme == "Blending_ep3_w2_3_p1") return "خ#ا#ب";
    if (phoneme == "Blending_ep3_w2_3_p2") return "خ#و#خ";
    if (phoneme == "Blending_ep3_w2_3_p3") return "ت#خ#ت";
    if (phoneme == "Blending_ep3_w2_3_p4") return "خ#ب#ث";
    
    if (phoneme == "Blending_ep3_w2_4_p1") return "د#ا#خ";
    if (phoneme == "Blending_ep3_w2_4_p2") return "ج#د#ي";
    if (phoneme == "Blending_ep3_w2_4_p3") return "د#ب";
    if (phoneme == "Blending_ep3_w2_4_p4") return "د#ج#ا#ج";
    if (phoneme == "Blending_ep3_w2_4_p5") return "ي#د";
    
    if (phoneme == "Blending_ep3_w2_5_p1") return "ذ#ا#ب";
    if (phoneme == "Blending_ep3_w2_5_p2") return "ذ#ا#ق";
    if (phoneme == "Blending_ep3_w2_5_p3") return "ذ#م";
    if (phoneme == "Blending_ep3_w2_5_p4") return "ا#خ#ذ";
  
    if (phoneme == "Blending_ep3_w2_6_p1") return "و#ر#د";
    if (phoneme == "Blending_ep3_w2_6_p2") return "د#ا#ر";
    if (phoneme == "Blending_ep3_w2_6_p3") return "ح#ب#ر";
    if (phoneme == "Blending_ep3_w2_6_p4") return "ج#ا#ر";
    if (phoneme == "Blending_ep3_w2_6_p5") return "ب#ر#ج";
    
    // watchman 3
    
    if (phoneme == "Blending_ep3_w3_1_p1") return "ج#ز#ر";
    if (phoneme == "Blending_ep3_w3_1_p2") return "خ#ب#ز";
    if (phoneme == "Blending_ep3_w3_1_p3") return "ز#ج#ا#ج";
    if (phoneme == "Blending_ep3_w3_1_p4") return "ز#ر";
    if (phoneme == "Blending_ep3_w3_1_p5") return "ز#ي#ت";
    
    if (phoneme == "Blending_ep3_w3_2_p1") return "س#ا#ح";
    if (phoneme == "Blending_ep3_w3_2_p2") return "د#ب#س";
    if (phoneme == "Blending_ep3_w3_2_p3") return "س#ر#ب";
    if (phoneme == "Blending_ep3_w3_2_p4") return "س#د";
    if (phoneme == "Blending_ep3_w3_2_p5") return "د#ر#س";
    
    if (phoneme == "Blending_ep3_w3_3_p1") return "خ#ش#ب";
    if (phoneme == "Blending_ep3_w3_3_p2") return "ش#ر#ا#ب";
    if (phoneme == "Blending_ep3_w3_3_p3") return "ش#ا#ب";
    if (phoneme == "Blending_ep3_w3_3_p4") return "ش#ا#ي";
    if (phoneme == "Blending_ep3_w3_3_p5") return "ش#ي#خ";
    
    if (phoneme == "Blending_ep3_w3_4_p1") return "ص#و#ص";
    if (phoneme == "Blending_ep3_w3_4_p2") return "ب#ا#ص";
    if (phoneme == "Blending_ep3_w3_4_p3") return "ص#ا#ح";
    if (phoneme == "Blending_ep3_w3_4_p4") return "ص#ب#ي";
    if (phoneme == "Blending_ep3_w3_4_p5") return "ص#ي#ف";
    
    if (phoneme == "Blending_ep3_w3_5_p1") return "ض#ر#س";
    if (phoneme == "Blending_ep3_w3_5_p2") return "ض#ب";
    if (phoneme == "Blending_ep3_w3_5_p3") return "ض#ب#ا#ب";
    if (phoneme == "Blending_ep3_w3_5_p4") return "ض#ج#ي#ج";
    if (phoneme == "Blending_ep3_w3_5_p5") return "ب#ي#ض";
    
    if (phoneme == "Blending_ep3_w3_6_p1") return "ح#ط#ب";
    if (phoneme == "Blending_ep3_w3_6_p2") return "ط#ب#ق";
    if (phoneme == "Blending_ep3_w3_6_p3") return "ط#و#ق";
    if (phoneme == "Blending_ep3_w3_6_p4") return "س#ط#ر";
    if (phoneme == "Blending_ep3_w3_6_p5") return "خ#ي#ط";
    
    // watchman 4
    
    if (phoneme == "Blending_ep3_w4_1_p1") return "ظ#ب#ي";
    if (phoneme == "Blending_ep3_w4_1_p2") return "ح#ظ";
    if (phoneme == "Blending_ep3_w4_1_p3") return "ح#ظ#ر";
    if (phoneme == "Blending_ep3_w4_1_p4") return "م#ظ#لة";
    if (phoneme == "Blending_ep3_w4_1_p5") return "ل#ف#ظ";
    
    if (phoneme == "Blending_ep3_w4_2_p1") return "ع#و#د";
    if (phoneme == "Blending_ep3_w4_2_p2") return "ر#ع#د";
    if (phoneme == "Blending_ep3_w4_2_p3") return "ع#ر#ق";
    if (phoneme == "Blending_ep3_w4_2_p4") return "ع#ش";
    if (phoneme == "Blending_ep3_w4_2_p5") return "ز#ر#ع";
    
    if (phoneme == "Blending_ep3_w4_3_p1") return "غ#ا#بة";
    if (phoneme == "Blending_ep3_w4_3_p2") return "غ#س#ق";
    if (phoneme == "Blending_ep3_w4_3_p3") return "غ#و#ل";
    if (phoneme == "Blending_ep3_w4_3_p4") return "غ#ض#ب";
    if (phoneme == "Blending_ep3_w4_3_p5") return "ت#ب#غ";
    
    if (phoneme == "Blending_ep3_w4_4_p1") return "ف#ج#ل";
    if (phoneme == "Blending_ep3_w4_4_p2") return "خ#ف#ا#ش";
    if (phoneme == "Blending_ep3_w4_4_p3") return "ر#ف";
    if (phoneme == "Blending_ep3_w4_4_p4") return "ظ#ف#ر";
    if (phoneme == "Blending_ep3_w4_4_p5") return "ض#ف#د#ع";
    
    if (phoneme == "Blending_ep3_w4_5_p1") return "ق#ص#ر";
    if (phoneme == "Blending_ep3_w4_5_p2") return "ق#ط#ا#ر";
    if (phoneme == "Blending_ep3_w4_5_p3") return "ق#ط#ن";
    if (phoneme == "Blending_ep3_w4_5_p4") return "ع#ق#د";
    if (phoneme == "Blending_ep3_w4_5_p5") return "ق#ر#د";
    
    if (phoneme == "Blending_ep3_w4_6_p1") return "ك#ر#ز";
    if (phoneme == "Blending_ep3_w4_6_p2") return "ك#ت#ا#ب";
    if (phoneme == "Blending_ep3_w4_6_p3") return "ك#ف";
    if (phoneme == "Blending_ep3_w4_6_p4") return "ك#و#خ";
    if (phoneme == "Blending_ep3_w4_6_p5") return "ك#ت#ف";
    
    // watchman 5
    
    if (phoneme == "Blending_ep3_w5_1_p1") return "و#ل#د";
    if (phoneme == "Blending_ep3_w5_1_p2") return "ج#ب#ل";
    if (phoneme == "Blending_ep3_w5_1_p3") return "ف#ج#ل";
    if (phoneme == "Blending_ep3_w5_1_p4") return "ل#و#ح";
    if (phoneme == "Blending_ep3_w5_1_p5") return "ك#ل#ب";
    
    if (phoneme == "Blending_ep3_w5_2_p1") return "ق#ل#م";
    if (phoneme == "Blending_ep3_w5_2_p2") return "م#ل#ح";
    if (phoneme == "Blending_ep3_w5_2_p3") return "م#ط#ر";
    if (phoneme == "Blending_ep3_w5_2_p4") return "ق#م#ر";
    if (phoneme == "Blending_ep3_w5_2_p5") return "م#ش#ط";
    
    if (phoneme == "Blending_ep3_w5_3_p1") return "ع#ن#ب";
    if (phoneme == "Blending_ep3_w5_3_p2") return "ن#ج#م";
    if (phoneme == "Blending_ep3_w5_3_p3") return "ن#ف#ق";
    if (phoneme == "Blending_ep3_w5_3_p4") return "ن#و#ر";
    if (phoneme == "Blending_ep3_w5_3_p5") return "ن#ا#ر";
    
    if (phoneme == "Blending_ep3_w5_4_p1") return "و#ج#ه";
    if (phoneme == "Blending_ep3_w5_4_p2") return "ه#ر#م";
    if (phoneme == "Blending_ep3_w5_4_p3") return "ه#د#ه#د";
    if (phoneme == "Blending_ep3_w5_4_p4") return "ن#ه#ر";
    if (phoneme == "Blending_ep3_w5_4_p5") return "س#ه#ل";
    
    if (phoneme == "Blending_ep3_w5_5_p1") return "و#ق#ت";
    if (phoneme == "Blending_ep3_w5_5_p2") return "ك#و#خ";
    if (phoneme == "Blending_ep3_w5_5_p3") return "د#ل#و";
    if (phoneme == "Blending_ep3_w5_5_p4") return "و#ز#ن";
    if (phoneme == "Blending_ep3_w5_5_p5") return "و#ر#ق";
    
    if (phoneme == "Blending_ep3_w5_6_p1") return "ي#د";
    if (phoneme == "Blending_ep3_w5_6_p2") return "س#ي#ف";
    if (phoneme == "Blending_ep3_w5_6_p3") return "ي#خ#ت";
    if (phoneme == "Blending_ep3_w5_6_p4") return "ف#ي#ل";
    if (phoneme == "Blending_ep3_w5_6_p5") return "ذ#ي#ل";
    
    
    return "ERROR";
}

std::string ArabicHelper::getInArabic_blendingEpisode4(std::string phoneme) {
    
    // episode 4 - blending
    
    if (phoneme == "bubble1_ep4_blending_p1") return "ا#ن#ف";
    if (phoneme == "bubble1_ep4_blending_p2") return "ا#ر#ن#ب";
    if (phoneme == "bubble1_ep4_blending_p3") return "م#ا#ل";
    if (phoneme == "bubble1_ep4_blending_p4") return "ح#ب#ا";
    if (phoneme == "bubble1_ep4_blending_p5") return "غ#ف#ا";
    
    if (phoneme == "bubble2_ep4_blending_p1") return "ب#ا#ب";
    if (phoneme == "bubble2_ep4_blending_p2") return "ب#طة";
    if (phoneme == "bubble2_ep4_blending_p3") return "ن#ب#ع";
    if (phoneme == "bubble2_ep4_blending_p4") return "ح#س#ا#ب";
    if (phoneme == "bubble2_ep4_blending_p5") return " ح#ط#ب";
    
    if (phoneme == "bubble3_ep4_blending_p1") return "ت#م#ر";
    if (phoneme == "bubble3_ep4_blending_p2") return "ت#ف#ا#ح";
    if (phoneme == "bubble3_ep4_blending_p3") return "م#ف#ت#ا#ح";
    if (phoneme == "bubble3_ep4_blending_p4") return "ي#خ#ت";
    if (phoneme == "bubble3_ep4_blending_p5") return " و#ق#ت";
    
    if (phoneme == "bubble4_ep4_blending_p1") return "ث#ع#ب#ا#ن";
    if (phoneme == "bubble4_ep4_blending_p2") return "ث#و#ب";
    if (phoneme == "bubble4_ep4_blending_p3") return "ك#ث#ي";
    if (phoneme == "bubble4_ep4_blending_p4") return "غ#ي#ث";
    if (phoneme == "bubble4_ep4_blending_p5") return "ح#ا#د#ث";
    
    if (phoneme == "bubble5_ep4_blending_p1") return "ج#ر#س";
    if (phoneme == "bubble5_ep4_blending_p2") return "ج#ب#ن";
    if (phoneme == "bubble5_ep4_blending_p3") return "ش#ج#رة";
    if (phoneme == "bubble5_ep4_blending_p4") return "م#ر#ج";
    if (phoneme == "bubble5_ep4_blending_p5") return "م#ه#ر#ج";
    
    if (phoneme == "bubble6_ep4_blending_p1") return "ح#ب#ر";
    if (phoneme == "bubble6_ep4_blending_p2") return "ح#ص#ا#ن";
    if (phoneme == "bubble6_ep4_blending_p3") return "ب#ح#ر";
    if (phoneme == "bubble6_ep4_blending_p4") return "م#ل#ح";
    if (phoneme == "bubble6_ep4_blending_p5") return "ر#ي#ح";
    
    if (phoneme == "bubble7_ep4_blending_p1") return "خ#ش#ب";
    if (phoneme == "bubble7_ep4_blending_p2") return "خ#س";
    if (phoneme == "bubble7_ep4_blending_p3") return "ن#خ#ي#ل";
    if (phoneme == "bubble7_ep4_blending_p4") return "خ#و#خ";
    if (phoneme == "bubble7_ep4_blending_p5") return "س#ي#خ";
    
    if (phoneme == "bubble8_ep4_blending_p1") return "د#ي#ك";
    if (phoneme == "bubble8_ep4_blending_p2") return "د#و#ل#ا#ب";
    if (phoneme == "bubble8_ep4_blending_p3") return "ع#د#د";
    if (phoneme == "bubble8_ep4_blending_p4") return "و#ر#د";
    if (phoneme == "bubble8_ep4_blending_p5") return "م#ق#ع#د";
    
    if (phoneme == "bubble9_ep4_blending_p1") return "ذ#ه#ب";
    if (phoneme == "bubble9_ep4_blending_p2") return "ذ#ب#ا#ب";
    if (phoneme == "bubble9_ep4_blending_p3") return "ج#ذ#ر";
    if (phoneme == "bubble9_ep4_blending_p4") return "ت#ل#م#ي#ذ";
    if (phoneme == "bubble9_ep4_blending_p5") return "ق#ن#ف#ذ";
    
    if (phoneme == "bubble10_ep4_blending_p1") return "ر#ع#د";
    if (phoneme == "bubble10_ep4_blending_p2") return "ر#م#ا#ن";
    if (phoneme == "bubble10_ep4_blending_p3") return "ح#ر#ف";
    if (phoneme == "bubble10_ep4_blending_p4") return "خ#ض#ا#ر";
    if (phoneme == "bubble10_ep4_blending_p5") return "ج#س#ر";

    if (phoneme == "bubble11_ep4_blending_p1") return "ز#ه#رة";
    if (phoneme == "bubble11_ep4_blending_p2") return "ز#ر#ا#فة";
    if (phoneme == "bubble11_ep4_blending_p3") return "م#ي#ز#ا#ن";
    if (phoneme == "bubble11_ep4_blending_p4") return "ك#ن#ز";
    if (phoneme == "bubble11_ep4_blending_p5") return "ك#ر#ز";
    
    if (phoneme == "bubble12_ep4_blending_p1") return "س#ل#م";
    if (phoneme == "bubble12_ep4_blending_p2") return "س#ح#ا#ب";
    if (phoneme == "bubble12_ep4_blending_p3") return "ا#س#م";
    if (phoneme == "bubble12_ep4_blending_p4") return "ج#ر#س";
    if (phoneme == "bubble12_ep4_blending_p5") return "د#ر#س";
    
    if (phoneme == "bubble13_ep4_blending_p1") return "ش#م#ع";
    if (phoneme == "bubble13_ep4_blending_p2") return "ش#ا#ل";
    if (phoneme == "bubble13_ep4_blending_p3") return "م#ش#ط";
    if (phoneme == "bubble13_ep4_blending_p4") return "ق#م#ا#ش";
    if (phoneme == "bubble13_ep4_blending_p5") return "ع#ش";
    
    if (phoneme == "bubble14_ep4_blending_p1") return "ص#ا#ر#و#خ";
    if (phoneme == "bubble14_ep4_blending_p2") return "ص#ن#د#و#ق";
    if (phoneme == "bubble14_ep4_blending_p3") return "ع#ص#ف#و#ر";
    if (phoneme == "bubble14_ep4_blending_p4") return "ص#ا#ب#و#ن";
    if (phoneme == "bubble14_ep4_blending_p5") return "م#ق#ص";
    
    if (phoneme == "bubble15_ep4_blending_p1") return "ض#ب#ع";
    if (phoneme == "bubble15_ep4_blending_p2") return "ض#ف#د#ع";
    if (phoneme == "bubble15_ep4_blending_p3") return "ا#ب#ي#ض";
    if (phoneme == "bubble15_ep4_blending_p4") return "ب#ي#ض";
    
    if (phoneme == "bubble16_ep4_blending_p1") return "ط#ب#ل";
    if (phoneme == "bubble16_ep4_blending_p2") return "ط#ا#وو#س";
    if (phoneme == "bubble16_ep4_blending_p3") return "م#ن#ط#ا#د";
    if (phoneme == "bubble16_ep4_blending_p4") return "و#س#ط";
    if (phoneme == "bubble16_ep4_blending_p5") return "س#و#ط";
    
    if (phoneme == "bubble17_ep4_blending_p1") return "ظ#ف#ر";
    if (phoneme == "bubble17_ep4_blending_p2") return "ظ#ل";
    if (phoneme == "bubble17_ep4_blending_p3") return "ع#ظ#م";
    if (phoneme == "bubble17_ep4_blending_p4") return "ح#ف#ظ";
    if (phoneme == "bubble17_ep4_blending_p5") return "ح#ظ";
    
    if (phoneme == "bubble18_ep4_blending_p1") return "ع#و#د";
    if (phoneme == "bubble18_ep4_blending_p2") return "ع#ص#ف#و#ر";
    if (phoneme == "bubble18_ep4_blending_p3") return "م#ل#ع#قة";
    if (phoneme == "bubble18_ep4_blending_p4") return "ن#ب#ع";
    if (phoneme == "bubble18_ep4_blending_p5") return "ش#م#ع";
    
    if (phoneme == "bubble19_ep4_blending_p1") return "غ#ر#فة";
    if (phoneme == "bubble19_ep4_blending_p2") return "غ#ص#ن";
    if (phoneme == "bubble19_ep4_blending_p3") return "ر#غ#ي#ف";
    if (phoneme == "bubble19_ep4_blending_p4") return "ص#د#غ";
    if (phoneme == "bubble19_ep4_blending_p5") return "ت#ب#غ";
    
    if (phoneme == "bubble20_ep4_blending_p1") return "ف#ي#ل";
    if (phoneme == "bubble20_ep4_blending_p2") return "ف#ر#س";
    if (phoneme == "bubble20_ep4_blending_p3") return "ر#ف#ي#ق";
    if (phoneme == "bubble20_ep4_blending_p4") return "ه#ا#ت#ف";
    if (phoneme == "bubble20_ep4_blending_p5") return "ر#ف";
    
    if (phoneme == "bubble21_ep4_blending_p1") return "ق#ر#د";
    if (phoneme == "bubble21_ep4_blending_p2") return "ق#م#ر";
    if (phoneme == "bubble21_ep4_blending_p3") return "ب#ق#رة";
    if (phoneme == "bubble21_ep4_blending_p4") return "س#ا#ق";
    if (phoneme == "bubble21_ep4_blending_p5") return "ب#و#ق";
    
    if (phoneme == "bubble22_ep4_blending_p1") return "ك#رة";
    if (phoneme == "bubble22_ep4_blending_p2") return "ك#ت#ا#ب";
    if (phoneme == "bubble22_ep4_blending_p3") return "س#ك#ي#ن";
    if (phoneme == "bubble22_ep4_blending_p4") return "ش#ب#ا#ك";
    if (phoneme == "bubble22_ep4_blending_p5") return "ش#و#ك";
    
    if (phoneme == "bubble23_ep4_blending_p1") return "ل#و#ح";
    if (phoneme == "bubble23_ep4_blending_p2") return "ل#ع#بة";
    if (phoneme == "bubble23_ep4_blending_p3") return "م#ل#ع#ب";
    if (phoneme == "bubble23_ep4_blending_p4") return "ل#ي#ل";
    if (phoneme == "bubble23_ep4_blending_p5") return "ف#ج#ل";
    
    if (phoneme == "bubble24_ep4_blending_p1") return "م#و#ز";
    if (phoneme == "bubble24_ep4_blending_p2") return "م#ل#ا#ب#س";
    if (phoneme == "bubble24_ep4_blending_p3") return "ن#م#ر";
    if (phoneme == "bubble24_ep4_blending_p4") return "ر#ق#م";
    if (phoneme == "bubble24_ep4_blending_p5") return "ع#ل#م";
    
    if (phoneme == "bubble25_ep4_blending_p1") return "ن#ف#ق";
    if (phoneme == "bubble25_ep4_blending_p2") return "ن#ه#ر";
    if (phoneme == "bubble25_ep4_blending_p3") return "م#ن#ز#ل";
    if (phoneme == "bubble25_ep4_blending_p4") return "ل#س#ا#ن";
    if (phoneme == "bubble25_ep4_blending_p5") return "ج#ر#ن";
    
    if (phoneme == "bubble26_ep4_blending_p1") return "ه#رة";
    if (phoneme == "bubble26_ep4_blending_p2") return "ه#د#ه#د";
    if (phoneme == "bubble26_ep4_blending_p3") return "س#ه#م";
    if (phoneme == "bubble26_ep4_blending_p4") return "و#ج#ه";
    
    return "ERROR";
}

std::string ArabicHelper::getInArabic_blendingEpisode5(std::string phoneme) {
    // jonathan
    // episode 5 - blending
    if (phoneme == "extraBlending_ep5_w1_1") return "ا#ر#ن#ب";
    if (phoneme == "extraBlending_ep5_w1_2") return "ب#طة";
    if (phoneme == "extraBlending_ep5_w1_3") return "ت#م#ر";
    if (phoneme == "extraBlending_ep5_w1_4") return "ث#ع#ل#ب";
    if (phoneme == "extraBlending_ep5_w1_5") return "ج#ز#ر";
    
    if (phoneme == "extraBlending_ep5_w2_1") return "ز#ي#ت#و#ن";
    if (phoneme == "extraBlending_ep5_w2_2") return "س#ل#ح#ف#ا#ة";
    if (phoneme == "extraBlending_ep5_w2_3") return "ش#ج#ر";
    if (phoneme == "extraBlending_ep5_w2_4") return "ص#ن#د#و#ق";
    if (phoneme == "extraBlending_ep5_w2_5") return "ض#ف#د#ع";
    
    if (phoneme == "extraBlending_ep5_w3_1") return "ق#م#ر";
    if (phoneme == "extraBlending_ep5_w3_2") return "ك#ل#ب";
    if (phoneme == "extraBlending_ep5_w3_3") return "ل#ب#ن";
    if (phoneme == "extraBlending_ep5_w3_4") return "م#ا#ع#ز";
    if (phoneme == "extraBlending_ep5_w3_5") return "ن#م#ر";
    
    if (phoneme == "extraBlending_ep5_w4_1") return "ح#ص#ا#ن";
    if (phoneme == "extraBlending_ep5_w4_2") return "خ#ب#ز";
    if (phoneme == "extraBlending_ep5_w4_3") return "د#ج#ا#جة";
    if (phoneme == "extraBlending_ep5_w4_4") return "ذ#ب#ا#ب";
    if (phoneme == "extraBlending_ep5_w4_5") return "ر#م#ل";
    
    if (phoneme == "extraBlending_ep5_w5_1") return "ط#ا#وو#س";
    if (phoneme == "extraBlending_ep5_w5_2") return "ظ#ب#ي";
    if (phoneme == "extraBlending_ep5_w5_3") return "ع#ج#ل";
    if (phoneme == "extraBlending_ep5_w5_4") return "ح#ق#ل";
    if (phoneme == "extraBlending_ep5_w5_5") return "ص#ح#ن";
    
    if (phoneme == "extraBlending_ep5_w6_1") return "ق#طة";
    if (phoneme == "extraBlending_ep5_w6_2") return "و#ر#ق";
    if (phoneme == "extraBlending_ep5_w6_3") return "ي#د";
    if (phoneme == "extraBlending_ep5_w6_4") return "م#ر#ب#ع";
    if (phoneme == "extraBlending_ep5_w6_5") return "س#ك#ي#ن";
    
    if (phoneme == "extraBlending_ep5_w7_1") return "ف#م";
    if (phoneme == "extraBlending_ep5_w7_2") return "ق#ر#د";
    if (phoneme == "extraBlending_ep5_w7_3") return "س#م#ك";
    if (phoneme == "extraBlending_ep5_w7_4") return "ر#م#ا#ل";
    if (phoneme == "extraBlending_ep5_w7_5") return "ب#ا#ر#د";
    
    if (phoneme == "extraBlending_ep5_w8_1") return "ح#م#ا#ر";
    if (phoneme == "extraBlending_ep5_w8_2") return "ح#م#ا#م";
    if (phoneme == "extraBlending_ep5_w8_3") return "ش#م#ا#ل";
    if (phoneme == "extraBlending_ep5_w8_4") return "ن#ب#ا#ح";
    if (phoneme == "extraBlending_ep5_w8_5") return "ب#ا#ب";
    
    if (phoneme == "extraBlending_ep5_w9_1") return "ن#خ#ي#ل";
    if (phoneme == "extraBlending_ep5_w9_2") return "ق#ل#م";
    if (phoneme == "extraBlending_ep5_w9_3") return "ش#م#س";
    if (phoneme == "extraBlending_ep5_w9_4") return "ج#م#ل";
    if (phoneme == "extraBlending_ep5_w9_5") return "ز#ر#ا#فة";
    
    if (phoneme == "extraBlending_ep5_w10_1") return "س#ه#م";
    if (phoneme == "extraBlending_ep5_w10_2") return "ش#م#و#ع";
    if (phoneme == "extraBlending_ep5_w10_3") return "ش#ر#ا#ع";
    if (phoneme == "extraBlending_ep5_w10_4") return "ا#ز#ر#ق";
    if (phoneme == "extraBlending_ep5_w10_5") return "ب#ن#ت";
    
    if (phoneme == "extraBlending_ep5_w11_1") return "ق#ف#ل";
    if (phoneme == "extraBlending_ep5_w11_2") return "ش#ر#ط#ي";
    if (phoneme == "extraBlending_ep5_w11_3") return "س#و#ق";
    if (phoneme == "extraBlending_ep5_w11_4") return "ا#ب#ي#ض";
    if (phoneme == "extraBlending_ep5_w11_5") return "ب#ر#ت#ق#ا#ل";
    
    if (phoneme == "extraBlending_ep5_w12_1") return "ز#ه#و#ر";
    if (phoneme == "extraBlending_ep5_w12_2") return "ر#م#ا#ن";
    if (phoneme == "extraBlending_ep5_w12_3") return "ه#ل#ا#ل";
    if (phoneme == "extraBlending_ep5_w12_4") return "م#ف#ت#ا#ح";
    if (phoneme == "extraBlending_ep5_w12_5") return "ح#ق#ي#بة";
    
    if (phoneme == "extraBlending_ep5_w13_1") return "م#ن#ش#ا#ر";
    if (phoneme == "extraBlending_ep5_w13_2") return "س#ب#ا#ق";
    if (phoneme == "extraBlending_ep5_w13_3") return "ج#ب#ل";
    if (phoneme == "extraBlending_ep5_w13_4") return "و#س#ا#دة";
    if (phoneme == "extraBlending_ep5_w13_5") return "ه#ا#ت#ف";
    
    if (phoneme == "extraBlending_ep5_w14_1") return "م#د#ر#سة";
    if (phoneme == "extraBlending_ep5_w14_2") return "س#ب#و#رة";
    if (phoneme == "extraBlending_ep5_w14_3") return "س#ا#حة";
    if (phoneme == "extraBlending_ep5_w14_4") return "ق#ص#ص";
    if (phoneme == "extraBlending_ep5_w14_5") return "ت#ف#ا#ح";
    
    if (phoneme == "extraBlending_ep5_w15_1") return "ت#ي#ن";
    if (phoneme == "extraBlending_ep5_w15_2") return "م#ط#ر";
    if (phoneme == "extraBlending_ep5_w15_3") return "ا#م#و#ا#ج";
    if (phoneme == "extraBlending_ep5_w15_4") return "ث#و#م";
    if (phoneme == "extraBlending_ep5_w15_5") return "ف#س#ت#ا#ن";
    
    if (phoneme == "extraBlending_ep5_w16_1") return "ص#و#رة";
    if (phoneme == "extraBlending_ep5_w16_2") return "ف#ا#ر#س";
    if (phoneme == "extraBlending_ep5_w16_3") return "ق#ط#ن";
    if (phoneme == "extraBlending_ep5_w16_4") return "ا#خ#ض#ر";
    if (phoneme == "extraBlending_ep5_w16_5") return "ز#ج#ا#جة";
    
    if (phoneme == "extraBlending_ep5_w17_1") return "و#ج#ه";
    if (phoneme == "extraBlending_ep5_w17_2") return "ط#ف#ل";
    if (phoneme == "extraBlending_ep5_w17_3") return "ب#ر#ج";
    if (phoneme == "extraBlending_ep5_w17_4") return "ص#د#ي#ق";
    if (phoneme == "extraBlending_ep5_w17_5") return "ب#ط#ي#خ";
    
    if (phoneme == "extraBlending_ep5_w18_1") return "ظ#ل";
    if (phoneme == "extraBlending_ep5_w18_2") return "ق#ا#ر#ب";
    if (phoneme == "extraBlending_ep5_w18_3") return "ث#ع#ب#ا#ن";
    if (phoneme == "extraBlending_ep5_w18_4") return "م#ر#ي#ض";
    if (phoneme == "extraBlending_ep5_w18_5") return "ج#ز#ر";
    
    if (phoneme == "extraBlending_ep5_w19_1") return "ط#ب#ي#ب";
    if (phoneme == "extraBlending_ep5_w19_2") return "غ#ص#ن";
    if (phoneme == "extraBlending_ep5_w19_3") return "ح#و#ض";
    if (phoneme == "extraBlending_ep5_w19_4") return "ق#ط#ا#ر";
    if (phoneme == "extraBlending_ep5_w19_5") return "ح#ا#ر#ث";
    
    if (phoneme == "extraBlending_ep5_w20_1") return "ق#ف#ص";
    if (phoneme == "extraBlending_ep5_w20_2") return "ب#ع#د";
    if (phoneme == "extraBlending_ep5_w20_3") return "م#ل#ك";
    if (phoneme == "extraBlending_ep5_w20_4") return "ث#ل#ج";
    if (phoneme == "extraBlending_ep5_w20_5") return "ا#خ#ت#ي";
    
    if (phoneme == "extraBlending_ep5_w21_1") return "ي#م#ي#ن";
    if (phoneme == "extraBlending_ep5_w21_2") return "ش#ر#ا#ع";
    if (phoneme == "extraBlending_ep5_w21_3") return "ص#غ#ي#ر";
    if (phoneme == "extraBlending_ep5_w21_4") return "ش#م#ا#ل";
    if (phoneme == "extraBlending_ep5_w21_5") return "ع#ش#ب";
    
    if (phoneme == "extraBlending_ep5_w22_1") return "ظ#ر#ف";
    if (phoneme == "extraBlending_ep5_w22_2") return "ذ#ر#ا#ع";
    if (phoneme == "extraBlending_ep5_w22_3") return "ك#ر#س#ي";
    if (phoneme == "extraBlending_ep5_w22_4") return "و#س#ا#م";
    if (phoneme == "extraBlending_ep5_w22_5") return "ت#م#س#ا#ح";
    
    if (phoneme == "extraBlending_ep5_w23_1") return "ل#ح#و#م";
    if (phoneme == "extraBlending_ep5_w23_2") return "خ#ي#ا#ر";
    if (phoneme == "extraBlending_ep5_w23_3") return "ر#ج#ل";
    if (phoneme == "extraBlending_ep5_w23_4") return "س#ي#دة";
    if (phoneme == "extraBlending_ep5_w23_5") return "ع#ص#ف#و#ر";
    
    if (phoneme == "extraBlending_ep5_w24_1") return "ك#ت#ا#ب";
    if (phoneme == "extraBlending_ep5_w24_2") return "ك#ب#ي#ر";
    if (phoneme == "extraBlending_ep5_w24_3") return "ن#و#ر";
    if (phoneme == "extraBlending_ep5_w24_4") return "ل#و#ن";
    if (phoneme == "extraBlending_ep5_w24_5") return "ع#ج#و#ز";
    
    if (phoneme == "extraBlending_ep5_w25_1") return "ط#و#ي#ل";
    if (phoneme == "extraBlending_ep5_w25_2") return "ن#ا#ف#ذة";
    if (phoneme == "extraBlending_ep5_w25_3") return "ط#ا#و#لة";
    if (phoneme == "extraBlending_ep5_w25_4") return "ع#ص#ي#ر";
    if (phoneme == "extraBlending_ep5_w25_5") return "ض#ل#ع";
    
    if (phoneme == "extraBlending_ep5_w26_1") return "م#ن#ز#ل";
    if (phoneme == "extraBlending_ep5_w26_2") return "د#م#ية";
    if (phoneme == "extraBlending_ep5_w26_3") return "ح#ا#س#و#ب";
    if (phoneme == "extraBlending_ep5_w26_4") return "ا#ح#م#ر";
    if (phoneme == "extraBlending_ep5_w26_5") return "ق#ص#ي#ر";
    
    return "ERROR";
}
std::string ArabicHelper::getInArabic_wordreadingEpisode4(std::string phoneme) {
    
    // episode 4 - wordreading
    
    if (phoneme == "bubble1_ep4_wordreading_p1") return "ا#س#د";
    if (phoneme == "bubble1_ep4_wordreading_p2") return "ا#م#ي#ر";
    if (phoneme == "bubble1_ep4_wordreading_p3") return "س#ا#ق";
    if (phoneme == "bubble1_ep4_wordreading_p4") return "ب#ا#ص";
    if (phoneme == "bubble1_ep4_wordreading_p5") return "ع#ص#ا";
    
    if (phoneme == "bubble2_ep4_wordreading_p1") return "ب#ي#ت";
    if (phoneme == "bubble2_ep4_wordreading_p2") return "ب#ر#د";
    if (phoneme == "bubble2_ep4_wordreading_p3") return "ح#ب#ل";
    if (phoneme == "bubble2_ep4_wordreading_p4") return "س#ب#ع";
    if (phoneme == "bubble2_ep4_wordreading_p5") return "ذ#ب#ا#ب";
    
    if (phoneme == "bubble3_ep4_wordreading_p1") return "ت#ي#ن";
    if (phoneme == "bubble3_ep4_wordreading_p2") return "ت#ا#ج";
    if (phoneme == "bubble3_ep4_wordreading_p3") return "ك#ت#ا#ب";
    if (phoneme == "bubble3_ep4_wordreading_p4") return "ب#ر#ت#ق#ا#ل";
    if (phoneme == "bubble3_ep4_wordreading_p5") return "ت#و#ت";
    
    if (phoneme == "bubble4_ep4_wordreading_p1") return "ث#ل#ج";
    if (phoneme == "bubble4_ep4_wordreading_p2") return "ث#و#ر";
    if (phoneme == "bubble4_ep4_wordreading_p3") return "م#ث#ل#ث";
    if (phoneme == "bubble4_ep4_wordreading_p4") return "م#م#ث#ل#";
    if (phoneme == "bubble4_ep4_wordreading_p5") return "ل#ي#ث";
    
    if (phoneme == "bubble5_ep4_wordreading_p1") return "ج#م#ل";
    if (phoneme == "bubble5_ep4_wordreading_p2") return "ج#ب#ل";
    if (phoneme == "bubble5_ep4_wordreading_p3") return "ح#ج#ر";
    if (phoneme == "bubble5_ep4_wordreading_p4") return "ف#ج#ل";
    if (phoneme == "bubble5_ep4_wordreading_p5") return "ب#ر#ج";
    
    if (phoneme == "bubble6_ep4_wordreading_p1") return "ح#و#ت";
    if (phoneme == "bubble6_ep4_wordreading_p2") return "ح#ق#ل";
    if (phoneme == "bubble6_ep4_wordreading_p3") return "ف#ح#م";
    if (phoneme == "bubble6_ep4_wordreading_p4") return "ل#ح#م";
    if (phoneme == "bubble6_ep4_wordreading_p5") return "ت#م#س#ا#ح";
    
    if (phoneme == "bubble7_ep4_wordreading_p1") return "خ#ي#ط";
    if (phoneme == "bubble7_ep4_wordreading_p2") return "خ#ب#ز";
    if (phoneme == "bubble7_ep4_wordreading_p3") return "ص#خ#ر";
    if (phoneme == "bubble7_ep4_wordreading_p4") return "ب#خ#ي#ل";
    if (phoneme == "bubble7_ep4_wordreading_p5") return "ف#خ";
    
    if (phoneme == "bubble8_ep4_wordreading_p1") return "د#ا#ر";
    if (phoneme == "bubble8_ep4_wordreading_p2") return "د#ب";
    if (phoneme == "bubble8_ep4_wordreading_p3") return "ج#د#ي";
    if (phoneme == "bubble8_ep4_wordreading_p4") return "ب#د#ر";
    if (phoneme == "bubble8_ep4_wordreading_p5") return "س#د";
    
    if (phoneme == "bubble9_ep4_wordreading_p1") return "ذ#ي#ل";
    if (phoneme == "bubble9_ep4_wordreading_p2") return "ذ#رة";
    if (phoneme == "bubble9_ep4_wordreading_p3") return "ا#ذ#ن";
    if (phoneme == "bubble9_ep4_wordreading_p4") return "ب#ذ#و#ر";
    if (phoneme == "bubble9_ep4_wordreading_p5") return "ج#ر#ذ";
    
    if (phoneme == "bubble10_ep4_wordreading_p1") return "ر#م#ل";
    if (phoneme == "bubble10_ep4_wordreading_p2") return "ر#ج#ل";
    if (phoneme == "bubble10_ep4_wordreading_p3") return "ك#ر#س#ي";
    if (phoneme == "bubble10_ep4_wordreading_p4") return "ب#ر#ج";
    if (phoneme == "bubble10_ep4_wordreading_p5") return "ق#م#ر";
    
    if (phoneme == "bubble11_ep4_wordreading_p1") return "ز#ي#ت";
    if (phoneme == "bubble11_ep4_wordreading_p2") return "ز#ر";
    if (phoneme == "bubble11_ep4_wordreading_p3") return "ج#ز#ر";
    if (phoneme == "bubble11_ep4_wordreading_p4") return "ا#ز#ر#ق";
    if (phoneme == "bubble11_ep4_wordreading_p5") return "ل#و#ز";
    
    if (phoneme == "bubble12_ep4_wordreading_p1") return "س#م#ك";
    if (phoneme == "bubble12_ep4_wordreading_p2") return "س#ل#ك";
    if (phoneme == "bubble12_ep4_wordreading_p3") return "ن#س#ر";
    if (phoneme == "bubble12_ep4_wordreading_p4") return "ر#س#م";
    if (phoneme == "bubble12_ep4_wordreading_p5") return "ف#ر#س";
   
    if (phoneme == "bubble13_ep4_wordreading_p1") return "ش#م#س";
    if (phoneme == "bubble13_ep4_wordreading_p2") return "ش#ب#ل";
    if (phoneme == "bubble13_ep4_wordreading_p3") return "ف#ر#ا#شة";
    if (phoneme == "bubble13_ep4_wordreading_p4") return "م#ش#م#ش";
    if (phoneme == "bubble13_ep4_wordreading_p5") return "ع#ط#ش";
    
    if (phoneme == "bubble14_ep4_wordreading_p1") return "ص#ح#ن";
    if (phoneme == "bubble14_ep4_wordreading_p2") return "ص#ق#ر";
    if (phoneme == "bubble14_ep4_wordreading_p3") return "ب#ص#ل";
    if (phoneme == "bubble14_ep4_wordreading_p4") return "ق#صة";
    if (phoneme == "bubble14_ep4_wordreading_p5") return "ص#و#ص";
    
    if (phoneme == "bubble15_ep4_wordreading_p1") return "ض#ب#ا#ب";
    if (phoneme == "bubble15_ep4_wordreading_p2") return "ض#ر#س";
    if (phoneme == "bubble15_ep4_wordreading_p3") return "ف#ضة";
    if (phoneme == "bubble15_ep4_wordreading_p4") return "ه#ض#بة";
    if (phoneme == "bubble15_ep4_wordreading_p5") return "م#ر#ض";
    
    if (phoneme == "bubble16_ep4_wordreading_p1") return "ط#ف#ل";
    if (phoneme == "bubble16_ep4_wordreading_p2") return "ط#ي#ر";
    if (phoneme == "bubble16_ep4_wordreading_p3") return "ح#ط#ب";
    if (phoneme == "bubble16_ep4_wordreading_p4") return "ق#ط#ا#ر";
    if (phoneme == "bubble16_ep4_wordreading_p5") return "م#ش#ط";
    
    if (phoneme == "bubble17_ep4_wordreading_p1") return "ظ#ر#ف";
    if (phoneme == "bubble17_ep4_wordreading_p2") return "ظ#ب#ي";
    if (phoneme == "bubble17_ep4_wordreading_p3") return "ن#ظ#ا#رة";
    if (phoneme == "bubble17_ep4_wordreading_p4") return "م#ظ#لة";
    if (phoneme == "bubble17_ep4_wordreading_p5") return "غ#ل#ي#ظ";
    
    if (phoneme == "bubble18_ep4_wordreading_p1") return "ع#ي#ن";
    if (phoneme == "bubble18_ep4_wordreading_p2") return "ع#س#ل";
    if (phoneme == "bubble18_ep4_wordreading_p3") return "ر#ع#د";
    if (phoneme == "bubble18_ep4_wordreading_p4") return "ث#ع#ل#ب";
    if (phoneme == "bubble18_ep4_wordreading_p5") return "م#ص#ن#ع";
    
    if (phoneme == "bubble19_ep4_wordreading_p1") return "غ#ي#م";
    if (phoneme == "bubble19_ep4_wordreading_p2") return "غ#ز#ا#ل";
    if (phoneme == "bubble19_ep4_wordreading_p3") return "ن#غ#م";
    if (phoneme == "bubble19_ep4_wordreading_p4") return "م#غ#ن#ي";
    if (phoneme == "bubble19_ep4_wordreading_p5") return "ص#م#غ";
    
    if (phoneme == "bubble20_ep4_wordreading_p1") return "ف#م";
    if (phoneme == "bubble20_ep4_wordreading_p2") return "ف#و#ل";
    if (phoneme == "bubble20_ep4_wordreading_p3") return "ق#ف#ل";
    if (phoneme == "bubble20_ep4_wordreading_p4") return "ف#ل#ف#ل";
    if (phoneme == "bubble20_ep4_wordreading_p5") return "ص#ي#ف";
    
    if (phoneme == "bubble21_ep4_wordreading_p1") return "ق#ل#م";
    if (phoneme == "bubble21_ep4_wordreading_p2") return "ق#ف#ص";
    if (phoneme == "bubble21_ep4_wordreading_p3") return "ع#ق#د";
    if (phoneme == "bubble21_ep4_wordreading_p4") return "م#ل#ع#قة";
    if (phoneme == "bubble21_ep4_wordreading_p5") return "ب#ن#د#ق";
    
    if (phoneme == "bubble22_ep4_wordreading_p1") return "ك#ل#ب";
    if (phoneme == "bubble22_ep4_wordreading_p2") return "ك#ر#س#ي";
    if (phoneme == "bubble22_ep4_wordreading_p3") return "س#م#كة";
    if (phoneme == "bubble22_ep4_wordreading_p4") return "د#ي#ك";
    if (phoneme == "bubble22_ep4_wordreading_p5") return "م#ف#ك";
    
    if (phoneme == "bubble23_ep4_wordreading_p1") return "ل#ب#ن";
    if (phoneme == "bubble23_ep4_wordreading_p2") return "ل#ق#ل#ق";
    if (phoneme == "bubble23_ep4_wordreading_p3") return "ت#ل#ف#ا#ز";
    if (phoneme == "bubble23_ep4_wordreading_p4") return "ق#ل#ب";
    if (phoneme == "bubble23_ep4_wordreading_p5") return "س#ه#ل";
    
    if (phoneme == "bubble24_ep4_wordreading_p1") return "م#ط#ر";
    if (phoneme == "bubble24_ep4_wordreading_p2") return "م#د#ر#سة";
    if (phoneme == "bubble24_ep4_wordreading_p3") return "ر#م#ا#ن";
    if (phoneme == "bubble24_ep4_wordreading_p4") return "ن#م#ل";
    if (phoneme == "bubble24_ep4_wordreading_p5") return "خ#ا#ت#م";
    
    if (phoneme == "bubble25_ep4_wordreading_p1") return "ن#ا#ر";
    if (phoneme == "bubble25_ep4_wordreading_p2") return "ن#ج#م";
    if (phoneme == "bubble25_ep4_wordreading_p3") return "ع#ن#ب";
    if (phoneme == "bubble25_ep4_wordreading_p4") return "س#ن#ا#ب#ل";
    if (phoneme == "bubble25_ep4_wordreading_p5") return "ل#ح#ن";
    
    if (phoneme == "bubble26_ep4_wordreading_p1") return "ه#ر#م";
    if (phoneme == "bubble26_ep4_wordreading_p2") return "ه#د#ية";
    if (phoneme == "bubble26_ep4_wordreading_p3") return "ن#ه#ر";
    if (phoneme == "bubble26_ep4_wordreading_p4") return "ف#ه#د";
    if (phoneme == "bubble26_ep4_wordreading_p5") return "م#ن#ب#ه";
    
    
    return "ERROR";
}

std::string ArabicHelper::getInArabic_sentencereadingEpisode5(std::string phoneme) {
    
    // episode 5 - sentencereading
    
    if (phoneme == "bubble1_ep5_sentencereading_p1") return "هذه قطتي";
    if (phoneme == "bubble1_ep5_sentencereading_p2") return "القطة تلعب";
    if (phoneme == "bubble2_ep5_sentencereading_p1") return "احب قطتي نونو";
    if (phoneme == "bubble2_ep5_sentencereading_p2") return "القطة تشرب";
    if (phoneme == "bubble3_ep5_sentencereading_p1") return "انا احب المدرسة";
    if (phoneme == "bubble3_ep5_sentencereading_p2") return "تامر يحب التوت";
    if (phoneme == "bubble4_ep5_sentencereading_p1") return "العصفور يطير";
    if (phoneme == "bubble4_ep5_sentencereading_p2") return "القمر بدر";
    if (phoneme == "bubble5_ep5_sentencereading_p1") return " في دار ادم بلبل";
    if (phoneme == "bubble5_ep5_sentencereading_p2") return "بلبل اصفر";
    if (phoneme == "bubble6_ep5_sentencereading_p1") return "رياض يسبح";
    if (phoneme == "bubble6_ep5_sentencereading_p2") return "ماجد صديق عامر";
    if (phoneme == "bubble7_ep5_sentencereading_p1") return "القطة فوق الطاولة";
    if (phoneme == "bubble7_ep5_sentencereading_p2") return "الطيور تاكل";
    if (phoneme == "bubble8_ep5_sentencereading_p1") return "البيت نظيف";
    if (phoneme == "bubble8_ep5_sentencereading_p2") return "القطار سريع";
    if (phoneme == "bubble9_ep5_sentencereading_p1") return "عامر في المدرسة";
    if (phoneme == "bubble9_ep5_sentencereading_p2") return "ماما تغسل";
    if (phoneme == "bubble10_ep5_sentencereading_p1") return "في دارنا بطة";
    if (phoneme == "bubble10_ep5_sentencereading_p2") return "في دار وداد ورد";
    if (phoneme == "bubble11_ep5_sentencereading_p1") return "في النهر سمكة";
    if (phoneme == "bubble11_ep5_sentencereading_p2") return "بيتي في اعلى الجبل";
    if (phoneme == "bubble12_ep5_sentencereading_p1") return "المطر ينزل";
    if (phoneme == "bubble12_ep5_sentencereading_p2") return "الورد احمر";
    if (phoneme == "bubble13_ep5_sentencereading_p1") return "الجو بارد";
    if (phoneme == "bubble13_ep5_sentencereading_p2") return "شادي عطشان";
    if (phoneme == "bubble14_ep5_sentencereading_p1") return "ابي يزرع التفاح";
    if (phoneme == "bubble14_ep5_sentencereading_p2") return "انا اسمي باسم";
    if (phoneme == "bubble15_ep5_sentencereading_p1") return "الفراشة تطير";
    if (phoneme == "bubble15_ep5_sentencereading_p2") return "سليم شرطي";
    if (phoneme == "bubble16_ep5_sentencereading_p1") return "الباب مفتوح";
    if (phoneme == "bubble16_ep5_sentencereading_p2") return "في دار جدي ديك";
    if (phoneme == "bubble17_ep5_sentencereading_p1") return "الكتاب على الطاولة";
    if (phoneme == "bubble17_ep5_sentencereading_p2") return "أرنب ابيض صغير";
    if (phoneme == "bubble18_ep5_sentencereading_p1") return "ناهد تلميذة ";
    if (phoneme == "bubble18_ep5_sentencereading_p2") return "أمل تحب العنب";
    if (phoneme == "bubble19_ep5_sentencereading_p1") return "ناهد تلبس";
    if (phoneme == "bubble19_ep5_sentencereading_p2") return "عندي لعبة";
    if (phoneme == "bubble20_ep5_sentencereading_p1") return "التفاحة في اعلى الشجرة";
    if (phoneme == "bubble20_ep5_sentencereading_p2") return "العب مع اختي";
    if (phoneme == "bubble21_ep5_sentencereading_p1") return "الهرة تحت السرير";
    if (phoneme == "bubble21_ep5_sentencereading_p2") return "ذهب سعيد ";
    if (phoneme == "bubble22_ep5_sentencereading_p1") return "القرد فوق الشجرة";
    if (phoneme == "bubble22_ep5_sentencereading_p2") return "القطار يسير";
    if (phoneme == "bubble23_ep5_sentencereading_p1") return "رباب تلعب بالكرة";
    if (phoneme == "bubble23_ep5_sentencereading_p2") return "لولو جاع";
    if (phoneme == "bubble24_ep5_sentencereading_p1") return "يرسم بالالوان";
    if (phoneme == "bubble24_ep5_sentencereading_p2") return "ضاع قلم مازن";
    if (phoneme == "bubble25_ep5_sentencereading_p1") return "يزرع القمح";
    if (phoneme == "bubble25_ep5_sentencereading_p2") return "هذا قلم مازن";
    if (phoneme == "bubble26_ep5_sentencereading_p1") return "وليد داخل الصف";
    if (phoneme == "bubble26_ep5_sentencereading_p2") return "حزن شادي";
    
    return "ERROR";
}
