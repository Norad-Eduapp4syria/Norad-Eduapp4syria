#pragma once

#include "sqlite3.h"
#include "cocos2d.h"

using namespace std;

class DatabaseSupportTables {
    
public:
    DatabaseSupportTables(sqlite3 *_pdb);
    sqlite3 *pdb;
    
    void populateBlendingTable();
    void populateWordsForPhonemesTable();
    void populateWordDictationTable();
    void populateSentenceDictationTable();
    
    void populateShapeIdentifTable();
    void populateShapeNamingTable();
    void populateBodyPartsTable();
    
    void populateWordReadingTable();
    void populateSentenceReadingTable();
    
private:
   
  
};
