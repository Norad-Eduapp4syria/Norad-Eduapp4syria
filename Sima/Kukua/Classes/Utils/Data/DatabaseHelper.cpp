#include "DatabaseHelper.h"
#include "../StringUtility.h"
#include "../CocosCamera/CocosCamera.h"

using namespace cocos2d;
using namespace std;




DatabaseHelper::DatabaseHelper(string dbName)
{
  
   
    CCLOG("DatabaseHelper()");
  
    pdb=NULL;
  
    std::string path = FileUtils::getInstance()->getWritablePath();
    path.append(dbName);
    path.append(".db3");
    
    
    
    std::string sql;
    int result;
    result=sqlite3_open(path.c_str(),&pdb);
    if(result!=SQLITE_OK) {
        CCLOG("open database failed,  number%d",result);
        /*
        Data dbFile =  FileUtils::getInstance()->getDataFromFile("common/KukuaDB.db3");
        FILE* dest = fopen(path.c_str(), "wb");
        fwrite(dbFile.getBytes(), 1, dbFile.getSize(), dest);
        fclose(dest);
        */
        
    }
    
    supportTables = new DatabaseSupportTables(pdb);
    
    initUsersTable();
}

void DatabaseHelper::initUsersTable() {
    
    int result;
    result=sqlite3_exec(pdb,"BEGIN TRANSACTION;",NULL,NULL,NULL);
    
    result=sqlite3_exec(pdb,"create table users(ID integer primary key autoincrement,userId text,photoPath text)",NULL,NULL,NULL);
    if(result!=SQLITE_OK) {
        result=sqlite3_exec(pdb,"ROLLBACK",NULL,NULL,NULL);
        CCLOG("-Create table failed: users table already exists");
    } else {
        result=sqlite3_exec(pdb,"COMMIT;",NULL,NULL,NULL);
        CCLOG("-users table created!");
        // sqlite3_exec(pdb, "INSERT INTO users (userId,photoPath) VALUES ('id01','sdcard/img.png')" ,NULL,NULL,NULL);
        
    }
}


void DatabaseHelper::initEpisodesTable(string suffixName) {
    
    string creationString = string("create") + " table episodes_"+suffixName+"(ID integer primary key autoincrement,episode integer,watchman integer,phoneme text,locked integer,game text,skin integer,score real)";
    
    int result;
    result=sqlite3_exec(pdb,"BEGIN TRANSACTION;",NULL,NULL,NULL);
    result=sqlite3_exec(pdb,creationString.c_str(),NULL,NULL,NULL);
    
    if(result!=SQLITE_OK) {
        result=sqlite3_exec(pdb,"ROLLBACK",NULL,NULL,NULL);
        CCLOG("-Create table failed: episodes_%s table already exists.", suffixName.c_str());
    } else {
        result=sqlite3_exec(pdb,"COMMIT;",NULL,NULL,NULL);
        CCLOG("-table episodes_%s created!.", suffixName.c_str());
        populateEpisodesTable(suffixName); // non ha senso popolare il db (coi dati nostri) se non esiste... devo mettere un flag nel costruttore per scegliere se voglio o meno popolarlo
    }
}



/* old
void DatabaseHelper::insertInEpisodesTable(string suffixName, string episode, string watchman, string locked, string score, string skin, string phoneme, string game) {
    
    string command = string("INSERT INTO") + " episodes_"+suffixName+" (episode,watchman,phoneme,locked,game,skin,score) VALUES ("+episode+","+watchman+",'"+phoneme+"',"+locked+",'"+game+"',"+skin+","+score+")";
        
    sqlite3_exec(pdb, command.c_str() ,NULL,NULL,NULL);
}
*/

void DatabaseHelper::insertInEpisodesTable(string suffixName, string episode, string watchman, string locked, string score, string skin, string phoneme, string game) {
    
    /*
     string command = string("INSERT INTO") + " episodes_"+suffixName+" (episode,watchman,phoneme,locked,game,skin,score) VALUES ("+episode+","+watchman+",'"+phoneme+"',"+locked+",'"+game+"',"+skin+","+score+")";
     
     sqlite3_exec(pdb, command.c_str() ,NULL,NULL,NULL);
     */
    
    sqlite3_stmt *stmt;
    string cmd = "INSERT INTO episodes_" + suffixName + " (episode, watchman, phoneme, locked, game, skin,score) VALUES (@episode, @watchman, @phoneme, @locked, @game, @skin, @score)";
    
    int result;
    result = sqlite3_prepare_v2(pdb, cmd.c_str(), -1, &stmt, NULL);
    
    if(result != SQLITE_OK) {
        CCLOG("Database returned error %d: %s ", sqlite3_errcode(pdb), sqlite3_errmsg(pdb));
        CCLOG("Built statement SQL error");
    }
    
    // stmt resta null
    sqlite3_bind_text(stmt, 1, episode.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, watchman.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, phoneme.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, locked.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, game.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, skin.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, score.c_str(), -1, SQLITE_TRANSIENT);
    
    
    sqlite3_step(stmt);
    
    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
    
}

void DatabaseHelper::populateEpisodesTable(string suffixName) {
    CCLOG("----populate db episodes_%s", suffixName.c_str());
    
    string locked = "1";
    string score = "101";
    string episode = "TO_SET";
    string watchman = "TO_SET";
    string skin = "1";
    
    // suffixName, episode, watchman, locked, score, skin, phoneme, game
    
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    // -- EPISODE 1 --
    
    episode = "1";
    
    
    insertInEpisodesTable(suffixName, episode, "0", "0",    score, "1", "Video1",                 "Video1" );
    
    // watchman 1.1
   
    watchman = "1";
    
    skin = "1";
    
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame1",      "IntensifierGame1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w1_1",     "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame2",      "IntensifierGame2" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep1_w1",          "Photo_ep1_w1" );
 
    watchman = "2";
    skin = "2";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ha#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ha#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ha#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame3",       "IntensifierGame3" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w2_1",     "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame4",      "IntensifierGame4" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "r#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "r#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "r#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w2_2",     "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_1",          "HealthGame" );
    
    watchman = "3";
    skin = "3";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "s#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "s#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "s#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame5",      "IntensifierGame5" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w3_1",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad#ep1",               "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad#ep1",               "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad#ep1",               "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame6",       "IntensifierGame6" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "taa#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "taa#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "taa#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w3_2",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_1",        "EmotionalGame" );
    
    watchman = "4";
    skin = "4";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "aa#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "aa#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "aa#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame7",       "IntensifierGame7" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w4_1",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame8",       "IntensifierGame8" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "k#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "k#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "k#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w4_2",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_1",           "SocialWeal" );
    
    
    watchman = "5";
    skin = "5";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "m#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "m#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "m#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame9",     "IntensifierGame9" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w5_1",    "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w#ep1",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w#ep1",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w#ep1",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame10",    "IntensifierGame10" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "y#ep1",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "y#ep1",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "y#ep1",                "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep1_w5_2",     "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_2",          "HealthGame" );
    
    
    
    // -- EPISODE 2 --
    
    episode = "2";
    
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "2", "Video2",                 "Video2" );
    
    // watchman 2.1
    
    watchman = "1";
    
    skin = "6";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "a",                          "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b",                          "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame11",          "IntensifierGame11" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "t",                          "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th",                         "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame12",          "IntensifierGame12" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep2_w1",               "Photo_ep2_w1" );
    
    // watchman 2.2
    
    watchman = "2";
    
    skin = "7";
    
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g",                          "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ha_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ha_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ha_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "ha",                         "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame13",          "IntensifierGame13" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja",                         "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d",                          "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "dh",                         "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame14",          "IntensifierGame14" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "r_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "r_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "r_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin,  "r",                        "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_3",              "HealthGame" );
 
    
    // watchman 2.3
    
    watchman = "3";
    
    skin = "8";
    
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z_writing",                  "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z_writing",                  "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z",                          "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "s_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "s_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "s_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "s",                         "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame15",         "IntensifierGame15" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh",                         "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad",                        "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad_writing",               "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad_writing",               "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad_writing",               "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "daad",                       "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame16",          "IntensifierGame16" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "taa_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "taa_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "taa_writing",                 "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin,  "taa",                        "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_2",            "EmotionalGame" );
    
    
    // watchman 2.4
    
    watchman = "4";
    
    skin = "9";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa_writing",            "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa_writing",            "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa_writing",            "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa",                    "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "aa_writing",             "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "aa_writing",             "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "aa_writing",             "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "4",  "aa",                     "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame17",      "IntensifierGame17" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh_writing",             "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh_writing",             "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh_writing",             "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh",                     "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f",                      "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "4",  "q",                      "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame18",      "IntensifierGame18" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "k_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "k_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "k_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin,  "k",                     "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_2",           "SocialWeal" );
    
    
    // watchman 2.5
    
    watchman = "5";
    
    skin = "10";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l",                      "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "m_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "m_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "m_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "m",                      "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame19",      "IntensifierGame19" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n",                      "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h",                      "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "w",                      "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame20",      "IntensifierGame20" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "y_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "y_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "y_writing",              "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin,  "y",                     "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_4",           "HealthGame" );
    
    
    // -- EPISODE 3 --
    
    episode = "3";
    
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "3", "Video3",                 "Video3" );
    
    // watchman 3.1
    
    watchman = "1";
    
    skin = "1";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "a#ep3",                  "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1", "a#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#a",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w1_1",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "b#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1", "b#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1", "b#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#b",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w1_2",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame21",      "IntensifierGame21" );
    skin = "2";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "t#ep3",                  "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1", "t#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#t",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w1_3",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "th#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1", "th#ep3",                 "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1", "th#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#th",         "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w1_4",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame22",      "IntensifierGame22" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep3_w1",           "Photo_ep3_w1" );

    
    // watchman 3.2
    
    watchman = "2";
    
    skin = "3";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "g#ep3",                  "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "g#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#g",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w2_1",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ha#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "ha#ep3",                 "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "ha#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#ha",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w2_2",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame23",      "IntensifierGame23" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "ja#ep3",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "ja#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#ja",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w2_3",      "Blending1" );
    skin = "4";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "d#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "d#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "d#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#d",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w2_4",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "dh#ep3",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "dh#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#dh",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w2_5",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame24",      "IntensifierGame24" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "r#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "r#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "r#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#r",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w2_6",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_5",           "HealthGame" );
    
    
    
    // watchman 3.3
    
    watchman = "3";
    
    skin = "5";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z#ep3",                   "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "z#ep3",                   "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "z#ep3",                   "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#z",            "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w3_1",       "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "s#ep3",                   "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "s#ep3",                    "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "s#ep3",                    "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#s",             "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w3_2",        "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame25",        "IntensifierGame25" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh#ep3",                   "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sh#ep3",                   "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "sh#ep3",                   "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#sh",            "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w3_3",        "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "sad#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "sad#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "sad#ep3",                  "TubGame" );
    skin = "6";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#sad",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w3_4",        "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "daad#ep3",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "daad#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#daad",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w3_5",        "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame26",        "IntensifierGame26" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "taa#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "taa#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "taa#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#taa",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w3_6",        "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_3",          "EmotionalGame" );
    
    // watchman 3.4
    
    watchman = "4";
    
    skin = "7";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa#ep3",                "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "zaa#ep3",                "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "zaa#ep3",                "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#zaa",         "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w4_1",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "aa#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "4",  "aa#ep3",                 "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "aa#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#aa",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w4_2",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame27",      "IntensifierGame27" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "gh#ep3",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "gh#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#gh",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w4_3",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "f#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "4",  "f#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "f#ep3",                  "TubGame" );
    skin = "8";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#f",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w4_4",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "q#ep3",                  "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "q#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#q",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w4_5",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame28",      "IntensifierGame28" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "k#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "4",  "k#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "k#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#k",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w4_6",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_3",           "SocialWeal" );
    
    // watchman 3.5
    
    
    watchman = "5";
    
    skin = "9";
    
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "l#ep3",                  "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "l#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#l",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w5_1",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "m#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "m#ep3",                 "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "m#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#m",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w5_2",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame29",      "IntensifierGame29" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "n#ep3",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "n#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#n",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w5_3",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "h#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "h#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "h#ep3",                  "TubGame" );
    skin = "10";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#h",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w5_4",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w#ep3",                 "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "w#ep3",                 "Platform" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "w#ep3",                 "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#w",          "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w5_5",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame30",      "IntensifierGame30" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "y#ep3",                  "PenaltyKick" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "y#ep3",                  "FallingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "y#ep3",                  "TubGame" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "WritingEp3#y",           "WritingLetters" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Blending_ep3_w5_6",      "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_6",           "HealthGame" );
    
    
    // -- EPISODE 4 --
    
    episode = "4";
    
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "4", "Video4",                 "Video4" );
    
    // watchman 4.1
    
    watchman = "1";
    skin = "1";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame31",          "IntensifierGame31" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame32",          "IntensifierGame32" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame33",          "IntensifierGame33" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame34",          "IntensifierGame34" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame35",          "IntensifierGame35" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame36",          "IntensifierGame36" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame37",          "IntensifierGame37" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep4_w1",               "Photo_ep4_w1" );
    // qui gioco fisico
    
    watchman = "2";
    skin = "2";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame38",          "IntensifierGame38" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep4",                "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep4",                "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame39",          "IntensifierGame39" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame40",          "IntensifierGame40" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame41",          "IntensifierGame41" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame42",          "IntensifierGame42" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame43",          "IntensifierGame43" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame44",          "IntensifierGame44" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_7",               "HealthGame" );
    
    watchman = "3";
    skin = "3";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame45",          "IntensifierGame45" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame46",          "IntensifierGame46" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame47",          "IntensifierGame47" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame48",          "IntensifierGame48" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame49",          "IntensifierGame49" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame50",          "IntensifierGame50" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_4",            "EmotionalGame" );
    
    watchman = "4";
    skin = "4";
    
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble21_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble21_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame51",          "IntensifierGame51" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble22_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble22_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame52",          "IntensifierGame52" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble23_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble23_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame53",          "IntensifierGame53" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble24_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble24_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame54",          "IntensifierGame54" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble25_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble25_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame55",          "IntensifierGame55" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble26_ep4",               "WordReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble26_ep4",               "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "IntensifierGame56",          "IntensifierGame56" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_4",               "SocialWeal" );
    
    
    // -- EPISODE 5 --
    episode = "5";
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "5", "Video5",                 "Video5" );
    
    // watchman 5.1
    watchman = "1";
    skin = "1";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "extraBlending_ep5_w1_1",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "extraBlending_ep5_w1_2",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "extraBlending_ep5_w1_3",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "5",  "extraBlending_ep5_w1_4",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "6",  "extraBlending_ep5_w1_5",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "6",  "extraBlending_ep5_w1_6",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "6",  "extraBlending_ep5_w1_7",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep5_w1",                   "Photo_ep5_w1" );
    
    // watchman 5.2
    watchman = "2";
    skin = "2";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "6",  "extraBlending_ep5_w2_1",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "7",  "extraBlending_ep5_w2_2",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "7",  "extraBlending_ep5_w2_3",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "7",  "extraBlending_ep5_w2_4",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "7",  "extraBlending_ep5_w2_5",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "7",  "extraBlending_ep5_w2_6",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "8",  "extraBlending_ep5_w2_7",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_8",                   "HealthGame" );
    
    // watchman 5.3
    watchman = "3";
    skin = "3";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "8",  "extraBlending_ep5_w3_1",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "8",  "extraBlending_ep5_w3_2",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "8",  "extraBlending_ep5_w3_3",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "8",  "extraBlending_ep5_w3_4",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "9",  "extraBlending_ep5_w3_5",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "9",  "extraBlending_ep5_w3_6",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_5",                 "EmotionalGame" );
    
    
    // watchman 5.4
    watchman = "4";
    skin = "4";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble21_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble21_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble21_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "9",  "extraBlending_ep5_w4_1",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble22_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble22_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble22_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "9",  "extraBlending_ep5_w4_2",          "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble23_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble23_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble23_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "10",  "extraBlending_ep5_w4_3",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble24_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble24_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble24_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "10",  "extraBlending_ep5_w4_4",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble25_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble25_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble25_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "10",  "extraBlending_ep5_w4_5",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble26_ep5",                    "SentenceReading" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble26_ep5",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble26_ep5",                    "ListComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "10",  "extraBlending_ep5_w4_6",         "Blending1" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_5",                     "SocialWeal" );
    
    
    // -- EPISODE 6 --
    episode = "6";
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "6", "Video6",                 "Video6" );
    
    // watchman 6.1
    watchman = "1";
    skin = "1";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep6",                    "ShapeIdentifier" ); // ShapesGame2, bugs
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep6",                    "ShapeNaming" );  // ShapesGame, gorilla
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "bubble1_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "bubble2_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "bubble3_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep6_w1",                   "Photo_ep6_w1" );
    
    // watchman 6.2
    watchman = "2";
    skin = "2";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "bubble4_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "bubble5_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "bubble6_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_9",                   "HealthGame" );
    
    // watchman 6.3
    watchman = "3";
    skin = "3";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "bubble7_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "bubble8_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "bubble9_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_6",                "EmotionalGame" );
    
    // watchman 6.4
    watchman = "4";
    skin = "4";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "bubble10_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "bubble11_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep6",                    "ShapeIdentifier" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep6",                    "ShapeNaming" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "bubble12_ep6",                    "BodyParts" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_6",                    "SocialWeal" );
    
    // -- EPISODE 7 --
    episode = "7";
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "7", "Video7",                 "Video7" );
    
    // watchman 7.1
    watchman = "1";
    skin = "1";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame72",              "IntensifierGame72" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame73",              "IntensifierGame73" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame74",              "IntensifierGame74" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame75",              "IntensifierGame75" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame76",              "IntensifierGame76" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "extraOralPassagebubble5_ep7",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep7_w1",                   "Photo_ep7_w1" );
    
    // watchman 7.2
    watchman = "2";
    skin = "2";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame77",              "IntensifierGame77" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame78",              "IntensifierGame78" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame79",              "IntensifierGame79" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame80",              "IntensifierGame80" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep7",                   "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep7",                   "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame81",              "IntensifierGame81" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "extraOralPassagebubble10_ep7",   "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_10",                  "HealthGame" );
    
    // watchman 7.3
    watchman = "3";
    skin = "3";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame82",              "IntensifierGame82" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame83",              "IntensifierGame83" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame84",              "IntensifierGame84" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame85",              "IntensifierGame85" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep7",                   "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep7",                   "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame86",              "IntensifierGame86" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "extraOralPassagebubble15_ep7",   "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_7",                "EmotionalGame" );
    
    // watchman 7.4
    watchman = "4";
    skin = "4";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame87",              "IntensifierGame87" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame88",              "IntensifierGame88" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame89",              "IntensifierGame89" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep7",                    "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep7",                    "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame90",              "IntensifierGame90" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep7",                   "ReadComprehens" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep7",                   "WordDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame91",              "IntensifierGame91" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "extraOralPassagebubble20_ep7",   "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_7",                   "SocialWeal" );
    
    // -- EPISODE 8 --
    episode = "8";
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "8", "Video8",                 "Video8" );
    
    // watchman 8.1
    watchman = "1";
    skin = "1";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame94",              "IntensifierGame94" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame95",              "IntensifierGame95" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame96",              "IntensifierGame96" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame97",              "IntensifierGame97" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame98",              "IntensifierGame98" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame99",              "IntensifierGame99" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame100",              "IntensifierGame100" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame101",              "IntensifierGame101" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame102",              "IntensifierGame102" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame103",              "IntensifierGame103" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "extraOralPassagebubble5_ep8",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep8_w1",                   "Photo_ep8_w1" );
    
    // watchman 8.2
    watchman = "2";
    skin = "2";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame104",              "IntensifierGame104" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame105",              "IntensifierGame105" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame106",              "IntensifierGame106" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame107",              "IntensifierGame107" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame108",              "IntensifierGame108" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame109",              "IntensifierGame109" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame110",              "IntensifierGame110" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame111",              "IntensifierGame111" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame112",              "IntensifierGame112" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame113",              "IntensifierGame113" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "extraOralPassagebubble10_ep8",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_11",                   "HealthGame" );
    
    // watchman 8.3
    watchman = "3";
    skin = "3";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame114",              "IntensifierGame114" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame115",              "IntensifierGame115" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame116",              "IntensifierGame116" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame117",              "IntensifierGame117" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame118",              "IntensifierGame118" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame119",              "IntensifierGame119" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame120",              "IntensifierGame120" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame121",              "IntensifierGame121" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame122",              "IntensifierGame122" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame123",              "IntensifierGame123" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "extraOralPassagebubble15_ep8",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_8",                 "EmotionalGame" );
    
    // watchman 8.4
    watchman = "4";
    skin = "4";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame124",              "IntensifierGame124" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame125",              "IntensifierGame125" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame126",              "IntensifierGame126" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame127",              "IntensifierGame127" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame128",              "IntensifierGame128" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame129",              "IntensifierGame129" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame130",              "IntensifierGame130" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame131",              "IntensifierGame131" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep8",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame132",              "IntensifierGame132" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame133",              "IntensifierGame133" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "2",  "extraOralPassagebubble20_ep8",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_8",                    "SocialWeal" );
    
    
    // -- EPISODE 9 --
    episode = "9";
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "9", "Video9",                 "Video9" );
    
    // watchman 9.1
    watchman = "1";
    skin = "1";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble1_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame136",             "IntensifierGame136" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble2_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame137",             "IntensifierGame137" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble3_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame138",             "IntensifierGame138" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble4_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame139",             "IntensifierGame139" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble5_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame140",             "IntensifierGame140" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "extraOralPassagebubble5_ep9",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "Photo_ep9_w1",                   "Photo_ep9_w1" );
    
    // watchman 9.2
    watchman = "2";
    skin = "2";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble6_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame141",             "IntensifierGame141" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble7_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame142",             "IntensifierGame142" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble8_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame143",             "IntensifierGame143" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble9_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame144",             "IntensifierGame144" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep9",                   "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble10_ep9",                   "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame145",             "IntensifierGame145" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "extraOralPassagebubble10_ep9",   "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "HealthGame_12",                  "HealthGame" );
    
    
    // watchman 9.3
    watchman = "3";
    skin = "3";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble11_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame146",             "IntensifierGame146" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble12_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame147",             "IntensifierGame147" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble13_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame148",             "IntensifierGame148" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble14_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame149",             "IntensifierGame149" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble15_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame150",             "IntensifierGame150" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "extraOralPassagebubble15_ep9",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "EmotionalGame_9",                 "EmotionalGame" );
    
    
    // watchman 9.4
    watchman = "4";
    skin = "4";
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble16_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame151",             "IntensifierGame151" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble17_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame152",             "IntensifierGame152" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble18_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame153",             "IntensifierGame153" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble19_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame154",             "IntensifierGame154" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep9",                    "SentenceDictation" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "bubble20_ep9",                    "ShuffledSentence" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "1",  "IntensifierGame155",             "IntensifierGame155" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, "3",  "extraOralPassagebubble20_ep9",    "OralPassage" );
    insertInEpisodesTable(suffixName, episode, watchman, locked, score, skin, "SocialWeal_9",                    "SocialWeal" );
    
    
    // -- EPISODE 10 --
    episode = "10";
    
    insertInEpisodesTable(suffixName, episode, "0", locked,    score, "10", "Video10",                 "Video10" );
    
    sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
    
}

void DatabaseHelper::close() {
    sqlite3_close(pdb); // serve per chiudere le connessioni col db?
}

string DatabaseHelper::getCell(char **table, int columnRef, int rowNum, int columnNum ) {
    return (table[rowNum*columnRef+columnNum]);
}

bool DatabaseHelper::isBlending(string phoneme) {
    
    if (StringUtility::startsWith(phoneme, "satip") ) return true; // todo agosto.. sistemare questo trick.. basta togliere la riga quando ho fatto bene la tabella del blending
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from blending WHERE " +
    "phoneme = '" + phoneme + "'";
    
    sqlite3_get_table(pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    sqlite3_free_table(table);
    
    if (rowTot == 0) return false;
    return true;
}
///

void DatabaseHelper::initTablesForGames() {
    
    int result;
    
    initBlendingTable(); // create BlendingDB
    initWordsForPhonemesTable();  // create WordsForPhonemesDB
    initWordDictationTable();
    initShapeIdentifTable();
    initShapeNamingTable();
    initBodyPartsTable();
    
    
    result=sqlite3_exec(pdb,"create table wordReading (ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result==SQLITE_OK) supportTables->populateWordReadingTable();
    
    result=sqlite3_exec(pdb,"create table sentenceReading (ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result==SQLITE_OK) supportTables->populateSentenceReadingTable();
        
    result=sqlite3_exec(pdb,"create table sentenceDictation (ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result==SQLITE_OK) supportTables->populateSentenceDictationTable();
}

void DatabaseHelper::initBlendingTable() {
 
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    int result=sqlite3_exec(pdb,"create table blending(ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result!=SQLITE_OK) {
        sqlite3_exec(pdb, "ROLLBACK;", NULL, NULL, NULL);
        CCLOG("-Create table failed: blending table already exists");
    } else {
       supportTables->populateBlendingTable();
       sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
    }
    
}


void DatabaseHelper::initShapeIdentifTable() {
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    int result=sqlite3_exec(pdb,"create table shapeIdentif (ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result==SQLITE_OK)
    {
        sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
        supportTables->populateShapeIdentifTable();
    }else
    {
         sqlite3_exec(pdb, "ROLLBACK;", NULL, NULL, NULL);
    }
}

void DatabaseHelper::initShapeNamingTable() {
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    int result=sqlite3_exec(pdb,"create table shapeNaming (ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result==SQLITE_OK)
    {
        sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
        supportTables->populateShapeNamingTable();
    }
    else
    {
         sqlite3_exec(pdb, "ROLLBACK;", NULL, NULL, NULL);
    }
}

void DatabaseHelper::initBodyPartsTable() {
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    int result=sqlite3_exec(pdb,"create table bodyParts (ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result==SQLITE_OK)
    {
        sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
        supportTables->populateBodyPartsTable();
    }
    else
    {
        sqlite3_exec(pdb, "ROLLBACK;", NULL, NULL, NULL);
    }
}




///
void DatabaseHelper::initWordsForPhonemesTable() {
    
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    int result=sqlite3_exec(pdb,"create table wordsForPhonemes(ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result!=SQLITE_OK)
    {
        sqlite3_exec(pdb, "ROLLBACK;", NULL, NULL, NULL);
        CCLOG("-Create table failed: wordsForPhonemes table already exists");
    } else {
        
        //------Episode 1
        
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('s','sack')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('a','ant')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('t','tail')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('i','it')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('p','paint')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('n','nap')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('c','cat')" ,NULL,NULL,NULL);
        
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('k','ink')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ck','jacket')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('e','pen')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('h','hen')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('r','red')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('m','map')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('d','dad')" ,NULL,NULL,NULL);
        
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('g','pig')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('o','hot')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('u','sun')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('l','lip')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ll','hill')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('f','fat')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ff','puff')" ,NULL,NULL,NULL);
        
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('b','bed')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ss','kiss')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('j','jet')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('qu','quiz')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('v','van')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('w','win')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('x','fox')" ,NULL,NULL,NULL);
        
        //------Episode 2
        
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('y','yap')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('z','zip')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('zz','fizzya')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ai','rain')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('oa','boat')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ie','pie')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ee','bee')" ,NULL,NULL,NULL);
        
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('or','fork')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ng','ring')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('oo1','zoo')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('oo2','book')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ch','chin')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('sh','ship')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('th1','this')" ,NULL,NULL,NULL);
        
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('th2','thin')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ou','loud')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('oi','oil')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ue','blue')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('er','sister')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ar','car')" ,NULL,NULL,NULL);
        sqlite3_exec(pdb, "INSERT INTO wordsForPhonemes (phoneme,word) VALUES ('ay','play')" ,NULL,NULL,NULL);
        
        
        sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
        // fin qui ok
        // ————— il “like in” c’è solo per episodio 1 e episiodio 2
      
    }
    
}

void DatabaseHelper::initWordDictationTable() {
    
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    int result=sqlite3_exec(pdb,"create table wordDictation(ID integer primary key autoincrement,phoneme text,word text)",NULL,NULL,NULL);
    if(result!=SQLITE_OK) {
        sqlite3_exec(pdb, "ROLLBACK;", NULL, NULL, NULL);
        CCLOG("-Create table failed: wordDictation table already exists");
    } else {
        sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
        supportTables->populateWordDictationTable();
    }
}

