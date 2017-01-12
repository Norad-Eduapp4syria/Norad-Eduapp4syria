#include "EmoTextProvider.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <string>

#include "../Utils/StringUtility.h"

#include "../Utils/Data/DataProvider.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;



EmoTextProvider::EmoTextProvider(int chosenMood)
{
    CCLOG("chosenMood = %d", chosenMood);
    
    if (chosenMood == 0) mood = "PAURA";
    else if (chosenMood == 1) mood = "TRISTEZZA";
    else if (chosenMood == 2) mood = "DELUSIONE";
    else if (chosenMood == 3) mood = "RABBIA";
    else if (chosenMood == 4) mood = "INDIFFERENZA";
    else if (chosenMood == 5) mood = "DISPREZZO";
    else if (chosenMood == 6) mood = "RASSEGNAZIONE";
    else if (chosenMood == 7) mood = "DISGUSTO";
    else if (chosenMood == 8) mood = "NOSTALGIA";
    
    CCLOG("mood = %s", mood.c_str());

}


EmoTextProvider::~EmoTextProvider() {
    
}


string EmoTextProvider::getQuestion() {
    string question = "";
    
    if (mood == "PAURA")             question = "ممتاز ! شكرا على مساعدة سيما في ايجاد الشجاعة . برأيك لما كانت سيما خائفة ؟";
    else if (mood == "TRISTEZZA")    question = "ممتاز! شكرا على مساعدة سيما في ايجاد بعض السعادة . برأيك لما سيما الان سعيدة ؟";
    else if (mood == "DELUSIONE")    question = "TODO";
    else if (mood == "RABBIA")       question = "TODO";
    else if (mood == "INDIFFERENZA") question = "TODO";
    else if (mood == "DISPREZZO")    question = "TODO";
    else if (mood == "RASSEGNAZIONE")question = "TODO";
    else if (mood == "DISGUSTO")     question = "TODO";
    else if (mood == "NOSTALGIA")    question = "TODO";
    
    return question;
}

string EmoTextProvider::getAnswer1() {
    string answer = "";
    
    if (mood == "PAURA")             answer = "La fine della guerra.";
    else if (mood == "TRISTEZZA")    answer = "TODO";
    else if (mood == "DELUSIONE")    answer = "TODO";
    else if (mood == "RABBIA")       answer = "TODO";
    else if (mood == "INDIFFERENZA") answer = "TODO";
    else if (mood == "DISPREZZO")    answer = "TODO";
    else if (mood == "RASSEGNAZIONE")answer = "TODO";
    else if (mood == "DISGUSTO")     answer = "TODO";
    else if (mood == "NOSTALGIA")    answer = "TODO";
    
    return answer;
}

string EmoTextProvider::getAnswer2() {
    string answer = "";
    
    if (mood == "PAURA")             answer = "L'amore per gli animali.";
    else if (mood == "TRISTEZZA")    answer = "TODO";
    else if (mood == "DELUSIONE")    answer = "TODO";
    else if (mood == "RABBIA")       answer = "TODO";
    else if (mood == "INDIFFERENZA") answer = "TODO";
    else if (mood == "DISPREZZO")    answer = "TODO";
    else if (mood == "RASSEGNAZIONE")answer = "TODO";
    else if (mood == "DISGUSTO")     answer = "TODO";
    else if (mood == "NOSTALGIA")    answer = "TODO";
    
    return answer;
}

string EmoTextProvider::getAnswer3() {
    string answer = "";
    
    if (mood == "PAURA")             answer = "Persone buone che le\nhannofatto compagnia.";
    else if (mood == "TRISTEZZA")    answer = "TODO";
    else if (mood == "DELUSIONE")    answer = "TODO";
    else if (mood == "RABBIA")       answer = "TODO";
    else if (mood == "INDIFFERENZA") answer = "TODO";
    else if (mood == "DISPREZZO")    answer = "TODO";
    else if (mood == "RASSEGNAZIONE")answer = "TODO";
    else if (mood == "DISGUSTO")     answer = "TODO";
    else if (mood == "NOSTALGIA")    answer = "TODO";
    
    return answer;
}


string EmoTextProvider::getAnswer4() {
    string answer = "";
    
    if (mood == "PAURA")             answer = "La nuova luce nella\nsua cameretta.";
    else if (mood == "TRISTEZZA")    answer = "TODO";
    else if (mood == "DELUSIONE")    answer = "TODO";
    else if (mood == "RABBIA")       answer = "TODO";
    else if (mood == "INDIFFERENZA") answer = "TODO";
    else if (mood == "DISPREZZO")    answer = "TODO";
    else if (mood == "RASSEGNAZIONE")answer = "TODO";
    else if (mood == "DISGUSTO")     answer = "TODO";
    else if (mood == "NOSTALGIA")    answer = "TODO";
    
    return answer;
}


string EmoTextProvider::getAnswer5() {
    string answer = "";
    
    if (mood == "PAURA")             answer = "Il sole.";
    else if (mood == "TRISTEZZA")    answer = "TODO";
    else if (mood == "DELUSIONE")    answer = "TODO";
    else if (mood == "RABBIA")       answer = "TODO";
    else if (mood == "INDIFFERENZA") answer = "TODO";
    else if (mood == "DISPREZZO")    answer = "TODO";
    else if (mood == "RASSEGNAZIONE")answer = "TODO";
    else if (mood == "DISGUSTO")     answer = "TODO";
    else if (mood == "NOSTALGIA")    answer = "TODO";
    
    return answer;
}


string EmoTextProvider::getAnswer6() {
    string answer = "";
    
    if (mood == "PAURA")             answer = "La presenza dei suoi amici.";
    else if (mood == "TRISTEZZA")    answer = "TODO";
    else if (mood == "DELUSIONE")    answer = "TODO";
    else if (mood == "RABBIA")       answer = "TODO";
    else if (mood == "INDIFFERENZA") answer = "TODO";
    else if (mood == "DISPREZZO")    answer = "TODO";
    else if (mood == "RASSEGNAZIONE")answer = "TODO";
    else if (mood == "DISGUSTO")     answer = "TODO";
    else if (mood == "NOSTALGIA")    answer = "TODO";
    
    return answer;
}


