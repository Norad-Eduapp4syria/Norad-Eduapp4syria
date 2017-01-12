#ifndef __ARABIC_HELPER_H__
#define __ARABIC_HELPER_H__

#include "cocos2d.h"
#include "../Singleton.h"

USING_NS_CC;


class ArabicHelper : public Singleton<ArabicHelper> {
    friend class Singleton<ArabicHelper>;
    
public:
    Label* createLabel(std::string text, float fontSize, bool setInArabic = false);
    std::string getInArabic(std::string phoneme);
    std::string getInLetter(std::string phoneme);
    std::string getFilenameInEnglish(std::string phoneme);    
    
protected:
    ArabicHelper();
    
private:
    std::string getInArabic_accents(std::string phoneme);
    std::string getInArabic_basePhonemes(std::string phoneme);
    std::string getInArabic_blendingEpisode3(std::string phoneme);
    std::string getInArabic_blendingEpisode4(std::string phoneme);
    std::string getInArabic_blendingEpisode5(std::string phoneme);
    std::string getInArabic_wordreadingEpisode4(std::string phoneme);
    std::string getInArabic_sentencereadingEpisode5(std::string phoneme);
    
    
};

#endif // __ARABIC_HELPER_H__
