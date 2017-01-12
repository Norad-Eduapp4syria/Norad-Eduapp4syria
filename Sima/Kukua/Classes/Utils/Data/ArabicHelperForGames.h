#ifndef __ARABIC_HELPER_FOR_GAMES_H__
#define __ARABIC_HELPER_FOR_GAMES_H__

#include "cocos2d.h"
#include "../Singleton.h"

USING_NS_CC;


class ArabicHelperForGames : public Singleton<ArabicHelperForGames> {
    friend class Singleton<ArabicHelperForGames>;
    
public:
    std::string getInArabic(std::string word);
    std::string getInArabic_wordDictation(std::string word);
    std::string getInArabic_sentenceDictation(std::string word);
    
    std::string getFilenameInEnglish_sentenceReading(std::string phoneme);
    std::string getFilenameInEnglish_sentenceDictation(std::string phoneme);
    std::string getFilenameInEnglish_wordDictation(std::string phoneme);
    std::string getFilenameInEnglish_shuffledSentence(std::string phoneme);
    std::string getFilenameInEnglish_blending(std::string phoneme);
    
protected:
    ArabicHelperForGames();
    
private:

    
};

#endif // __ARABIC_HELPER_FOR_GAMES_H__
