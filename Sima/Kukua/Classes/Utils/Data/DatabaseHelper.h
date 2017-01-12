#pragma once

#include "sqlite3.h"
#include "cocos2d.h"
#include "DatabaseSupportTables.h"

using namespace std;

class DatabaseHelper {
    
public:
    DatabaseHelper(string dbName);
    //virtual ~DatabaseHelper();

    void close();
    string getCell(char **table, int columnRef, int rowNum, int columnNum );
    bool isBlending(string phoneme);
    void initBlendingTable();
    void initWordsForPhonemesTable();
    void initWordDictationTable();
    void initEpisodesTable(string suffixName);
    void initUsersTable();
  
    void initShapeIdentifTable();
    void initShapeNamingTable();
    void initBodyPartsTable();
    
    void initTablesForGames();
    
    sqlite3 *pdb;
    
private:
   
   void populateEpisodesTable(string suffixName);
    void insertInEpisodesTable(string suffixName, string episode, string watchman, string locked, string score, string skin, string phoneme, string game);
    
    DatabaseSupportTables *supportTables;
};
