#include "DatabaseSupportTables.h"
#include "../StringUtility.h"

using namespace cocos2d;
using namespace std;




DatabaseSupportTables::DatabaseSupportTables(sqlite3 *_pdb)
{
  
    pdb = _pdb;
}

void DatabaseSupportTables::populateBlendingTable() {
    
//    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w1_1','a#s')" ,NULL,NULL,NULL);
sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    // ep. 1
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w1_1','a')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w1_1','b')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w1_1','t')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w1_1','th')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w2_1','g')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w2_1','ha')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w2_1','ja')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w2_2','d')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w2_2','dh')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w2_2','r')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w3_1','z')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w3_1','s')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w3_1','sh')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w3_2','sad')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w3_2','daad')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w3_2','taa')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w4_1','zaa')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w4_1','aa')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w4_1','gh')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w4_2','f')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w4_2','q')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w4_2','k')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w5_1','l')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w5_1','m')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w5_1','n')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w5_2','h')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w5_2','w')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep1_w5_2','y')" ,NULL,NULL,NULL);
    
    
    // ep.2
    // no blending game!
    
    //ep3
    // 3.1
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_1','Blending_ep3_w1_1_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_1','Blending_ep3_w1_1_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_1','Blending_ep3_w1_1_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_1','Blending_ep3_w1_1_p4')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_2','Blending_ep3_w1_2_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_2','Blending_ep3_w1_2_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_2','Blending_ep3_w1_2_p3')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_3','Blending_ep3_w1_3_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_3','Blending_ep3_w1_3_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_3','Blending_ep3_w1_3_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_3','Blending_ep3_w1_3_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_3','Blending_ep3_w1_3_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_4','Blending_ep3_w1_4_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_4','Blending_ep3_w1_4_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_4','Blending_ep3_w1_4_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_4','Blending_ep3_w1_4_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w1_4','Blending_ep3_w1_4_p5')" ,NULL,NULL,NULL);
    
    //3.2
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_1','Blending_ep3_w2_1_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_1','Blending_ep3_w2_1_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_1','Blending_ep3_w2_1_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_1','Blending_ep3_w2_1_p4')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_2','Blending_ep3_w2_2_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_2','Blending_ep3_w2_2_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_2','Blending_ep3_w2_2_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_2','Blending_ep3_w2_2_p4')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_3','Blending_ep3_w2_3_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_3','Blending_ep3_w2_3_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_3','Blending_ep3_w2_3_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_3','Blending_ep3_w2_3_p4')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_4','Blending_ep3_w2_4_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_4','Blending_ep3_w2_4_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_4','Blending_ep3_w2_4_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_4','Blending_ep3_w2_4_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_4','Blending_ep3_w2_4_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_5','Blending_ep3_w2_5_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_5','Blending_ep3_w2_5_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_5','Blending_ep3_w2_5_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_5','Blending_ep3_w2_5_p4')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_6','Blending_ep3_w2_6_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_6','Blending_ep3_w2_6_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_6','Blending_ep3_w2_6_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_6','Blending_ep3_w2_6_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w2_6','Blending_ep3_w2_6_p5')" ,NULL,NULL,NULL);
    
    //3.3
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_1','Blending_ep3_w3_1_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_1','Blending_ep3_w3_1_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_1','Blending_ep3_w3_1_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_1','Blending_ep3_w3_1_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_1','Blending_ep3_w3_1_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_2','Blending_ep3_w3_2_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_2','Blending_ep3_w3_2_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_2','Blending_ep3_w3_2_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_2','Blending_ep3_w3_2_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_2','Blending_ep3_w3_2_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_3','Blending_ep3_w3_3_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_3','Blending_ep3_w3_3_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_3','Blending_ep3_w3_3_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_3','Blending_ep3_w3_3_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_3','Blending_ep3_w3_3_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_4','Blending_ep3_w3_4_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_4','Blending_ep3_w3_4_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_4','Blending_ep3_w3_4_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_4','Blending_ep3_w3_4_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_4','Blending_ep3_w3_4_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_5','Blending_ep3_w3_5_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_5','Blending_ep3_w3_5_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_5','Blending_ep3_w3_5_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_5','Blending_ep3_w3_5_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_5','Blending_ep3_w3_5_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_6','Blending_ep3_w3_6_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_6','Blending_ep3_w3_6_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_6','Blending_ep3_w3_6_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_6','Blending_ep3_w3_6_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w3_6','Blending_ep3_w3_6_p5')" ,NULL,NULL,NULL);
    
    //3.4
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_1','Blending_ep3_w4_1_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_1','Blending_ep3_w4_1_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_1','Blending_ep3_w4_1_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_1','Blending_ep3_w4_1_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_1','Blending_ep3_w4_1_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_2','Blending_ep3_w4_2_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_2','Blending_ep3_w4_2_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_2','Blending_ep3_w4_2_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_2','Blending_ep3_w4_2_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_2','Blending_ep3_w4_2_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_3','Blending_ep3_w4_3_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_3','Blending_ep3_w4_3_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_3','Blending_ep3_w4_3_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_3','Blending_ep3_w4_3_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_3','Blending_ep3_w4_3_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_4','Blending_ep3_w4_4_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_4','Blending_ep3_w4_4_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_4','Blending_ep3_w4_4_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_4','Blending_ep3_w4_4_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_4','Blending_ep3_w4_4_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_5','Blending_ep3_w4_5_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_5','Blending_ep3_w4_5_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_5','Blending_ep3_w4_5_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_5','Blending_ep3_w4_5_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_5','Blending_ep3_w4_5_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_6','Blending_ep3_w4_6_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_6','Blending_ep3_w4_6_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_6','Blending_ep3_w4_6_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_6','Blending_ep3_w4_6_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w4_6','Blending_ep3_w4_6_p5')" ,NULL,NULL,NULL);
    
    //w5
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_1','Blending_ep3_w5_1_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_1','Blending_ep3_w5_1_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_1','Blending_ep3_w5_1_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_1','Blending_ep3_w5_1_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_1','Blending_ep3_w5_1_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_2','Blending_ep3_w5_2_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_2','Blending_ep3_w5_2_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_2','Blending_ep3_w5_2_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_2','Blending_ep3_w5_2_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_2','Blending_ep3_w5_2_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_3','Blending_ep3_w5_3_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_3','Blending_ep3_w5_3_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_3','Blending_ep3_w5_3_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_3','Blending_ep3_w5_3_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_3','Blending_ep3_w5_3_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_4','Blending_ep3_w5_4_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_4','Blending_ep3_w5_4_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_4','Blending_ep3_w5_4_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_4','Blending_ep3_w5_4_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_4','Blending_ep3_w5_4_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_5','Blending_ep3_w5_5_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_5','Blending_ep3_w5_5_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_5','Blending_ep3_w5_5_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_5','Blending_ep3_w5_5_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_5','Blending_ep3_w5_5_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_6','Blending_ep3_w5_6_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_6','Blending_ep3_w5_6_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_6','Blending_ep3_w5_6_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_6','Blending_ep3_w5_6_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('Blending_ep3_w5_6','Blending_ep3_w5_6_p5')" ,NULL,NULL,NULL);
    
    
    
    // ep4
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_blending_p4')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_blending_p4')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_blending_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_blending_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_blending_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_blending_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_blending_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_blending_p4')" ,NULL,NULL,NULL);
    
    
    
    
    
    // episode 5
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w1_1','extraBlending_ep5_w1_1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w1_2','extraBlending_ep5_w1_2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w1_3','extraBlending_ep5_w1_3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w1_4','extraBlending_ep5_w1_4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w1_5','extraBlending_ep5_w1_5')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w1_6','extraBlending_ep5_w1_6')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w1_7','extraBlending_ep5_w1_7')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w2_1','extraBlending_ep5_w2_1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w2_2','extraBlending_ep5_w2_2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w2_3','extraBlending_ep5_w2_3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w2_4','extraBlending_ep5_w2_4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w2_5','extraBlending_ep5_w2_5')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w2_6','extraBlending_ep5_w2_6')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w2_7','extraBlending_ep5_w2_7')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w3_1','extraBlending_ep5_w3_1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w3_2','extraBlending_ep5_w3_2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w3_3','extraBlending_ep5_w3_3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w3_4','extraBlending_ep5_w3_4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w3_5','extraBlending_ep5_w3_5')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w3_6','extraBlending_ep5_w3_6')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w4_1','extraBlending_ep5_w4_1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w4_2','extraBlending_ep5_w4_2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w4_3','extraBlending_ep5_w4_3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w4_4','extraBlending_ep5_w4_4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w4_5','extraBlending_ep5_w4_5')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO blending (phoneme,word) VALUES ('extraBlending_ep5_w4_6','extraBlending_ep5_w4_6')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
}


void DatabaseSupportTables::populateWordsForPhonemesTable() {
    
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
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


void DatabaseSupportTables::populateWordDictationTable() {
    
    sqlite3_exec(pdb,"BEGIN TRANSACTION;",NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble1_ep5','bubble1_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble1_ep5','bubble1_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble1_ep5','bubble1_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble2_ep5','bubble2_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble2_ep5','bubble2_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble2_ep5','bubble2_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble3_ep5','bubble3_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble3_ep5','bubble3_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble3_ep5','bubble3_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble4_ep5','bubble4_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble4_ep5','bubble4_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble4_ep5','bubble4_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble5_ep5','bubble5_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble5_ep5','bubble5_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble5_ep5','bubble5_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble6_ep5','bubble6_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble6_ep5','bubble6_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble6_ep5','bubble6_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble7_ep5','bubble7_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble7_ep5','bubble7_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble7_ep5','bubble7_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble8_ep5','bubble8_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble8_ep5','bubble8_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble8_ep5','bubble8_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble9_ep5','bubble9_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble9_ep5','bubble9_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble9_ep5','bubble9_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble10_ep5','bubble10_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble10_ep5','bubble10_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble10_ep5','bubble10_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble11_ep5','bubble11_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble11_ep5','bubble11_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble11_ep5','bubble11_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble12_ep5','bubble12_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble12_ep5','bubble12_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble12_ep5','bubble12_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble13_ep5','bubble13_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble13_ep5','bubble13_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble13_ep5','bubble13_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble14_ep5','bubble14_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble14_ep5','bubble14_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble14_ep5','bubble14_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble15_ep5','bubble15_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble15_ep5','bubble15_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble15_ep5','bubble15_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble16_ep5','bubble16_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble16_ep5','bubble16_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble16_ep5','bubble16_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble17_ep5','bubble17_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble17_ep5','bubble17_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble17_ep5','bubble17_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble18_ep5','bubble18_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble18_ep5','bubble18_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble18_ep5','bubble18_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble19_ep5','bubble19_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble19_ep5','bubble19_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble19_ep5','bubble19_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble20_ep5','bubble20_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble20_ep5','bubble20_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble20_ep5','bubble20_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble21_ep5','bubble21_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble21_ep5','bubble21_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble21_ep5','bubble21_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble22_ep5','bubble22_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble22_ep5','bubble22_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble22_ep5','bubble22_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble23_ep5','bubble23_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble23_ep5','bubble23_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble23_ep5','bubble23_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble24_ep5','bubble24_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble24_ep5','bubble24_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble24_ep5','bubble24_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble25_ep5','bubble25_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble25_ep5','bubble25_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble25_ep5','bubble25_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble26_ep5','bubble26_ep5_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble26_ep5','bubble26_ep5_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble26_ep5','bubble26_ep5_wordDictation_p3')" ,NULL,NULL,NULL);
    
    // ep7
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble1_ep7','bubble1_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble1_ep7','bubble1_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble1_ep7','bubble1_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble2_ep7','bubble2_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble2_ep7','bubble2_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble2_ep7','bubble2_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble3_ep7','bubble3_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble3_ep7','bubble3_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble3_ep7','bubble3_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble4_ep7','bubble4_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble4_ep7','bubble4_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble4_ep7','bubble4_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble5_ep7','bubble5_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble5_ep7','bubble5_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble5_ep7','bubble5_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble6_ep7','bubble6_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble6_ep7','bubble6_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble6_ep7','bubble6_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble7_ep7','bubble7_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble7_ep7','bubble7_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble7_ep7','bubble7_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble8_ep7','bubble8_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble8_ep7','bubble8_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble8_ep7','bubble8_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble9_ep7','bubble9_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble9_ep7','bubble9_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble9_ep7','bubble9_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble10_ep7','bubble10_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble10_ep7','bubble10_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble10_ep7','bubble10_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble11_ep7','bubble11_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble11_ep7','bubble11_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble11_ep7','bubble11_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble12_ep7','bubble12_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble12_ep7','bubble12_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble12_ep7','bubble12_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble13_ep7','bubble13_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble13_ep7','bubble13_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble13_ep7','bubble13_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble14_ep7','bubble14_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble14_ep7','bubble14_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble14_ep7','bubble14_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble15_ep7','bubble15_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble15_ep7','bubble15_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble15_ep7','bubble15_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble16_ep7','bubble16_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble16_ep7','bubble16_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble16_ep7','bubble16_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble17_ep7','bubble17_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble17_ep7','bubble17_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble17_ep7','bubble17_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble18_ep7','bubble18_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble18_ep7','bubble18_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble18_ep7','bubble18_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble19_ep7','bubble19_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble19_ep7','bubble19_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble19_ep7','bubble19_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble20_ep7','bubble20_ep7_wordDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble20_ep7','bubble20_ep7_wordDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordDictation (phoneme,word) VALUES ('bubble20_ep7','bubble20_ep7_wordDictation_p3')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb,"COMMIT;",NULL,NULL,NULL);
}

void DatabaseSupportTables::populateSentenceDictationTable() {
    
    sqlite3_exec(pdb,"BEGIN TRANSACTION;",NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble1_ep8','bubble1_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble1_ep8','bubble1_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble2_ep8','bubble2_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble2_ep8','bubble2_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble3_ep8','bubble3_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble3_ep8','bubble3_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble4_ep8','bubble4_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble4_ep8','bubble4_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble5_ep8','bubble5_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble5_ep8','bubble5_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble6_ep8','bubble6_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble6_ep8','bubble6_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble7_ep8','bubble7_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble7_ep8','bubble7_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble8_ep8','bubble8_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble8_ep8','bubble8_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble9_ep8','bubble9_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble9_ep8','bubble9_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble10_ep8','bubble10_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble10_ep8','bubble10_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble11_ep8','bubble11_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble11_ep8','bubble11_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble12_ep8','bubble12_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble12_ep8','bubble12_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble13_ep8','bubble13_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble13_ep8','bubble13_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble14_ep8','bubble14_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble14_ep8','bubble14_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble15_ep8','bubble15_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble15_ep8','bubble15_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble16_ep8','bubble16_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble16_ep8','bubble16_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble17_ep8','bubble17_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble17_ep8','bubble17_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble18_ep8','bubble18_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble18_ep8','bubble18_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble19_ep8','bubble19_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble19_ep8','bubble19_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble20_ep8','bubble20_ep8_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble20_ep8','bubble20_ep8_sentenceDictation_p2')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble1_ep9','bubble1_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble1_ep9','bubble1_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble2_ep9','bubble2_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble2_ep9','bubble2_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble3_ep9','bubble3_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble3_ep9','bubble3_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble4_ep9','bubble4_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble4_ep9','bubble4_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble5_ep9','bubble5_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble5_ep9','bubble5_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble6_ep9','bubble6_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble6_ep9','bubble6_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble7_ep9','bubble7_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble7_ep9','bubble7_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble8_ep9','bubble8_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble8_ep9','bubble8_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble9_ep9','bubble9_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble9_ep9','bubble9_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble10_ep9','bubble10_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble10_ep9','bubble10_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble11_ep9','bubble11_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble11_ep9','bubble11_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble12_ep9','bubble12_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble12_ep9','bubble12_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble13_ep9','bubble13_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble13_ep9','bubble13_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble14_ep9','bubble14_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble14_ep9','bubble14_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble15_ep9','bubble15_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble15_ep9','bubble15_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble16_ep9','bubble16_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble16_ep9','bubble16_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble17_ep9','bubble17_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble17_ep9','bubble17_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble18_ep9','bubble18_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble18_ep9','bubble18_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble19_ep9','bubble19_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble19_ep9','bubble19_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble20_ep9','bubble20_ep9_sentenceDictation_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceDictation (phoneme,word) VALUES ('bubble20_ep9','bubble20_ep9_sentenceDictation_p2')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb,"COMMIT;",NULL,NULL,NULL);
}





void DatabaseSupportTables::populateShapeIdentifTable() {
    
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble1_ep6','circle')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble2_ep6','triangle')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble3_ep6','square')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble4_ep6','rectangle')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble5_ep6','trapezoid')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble6_ep6','rhombus')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble7_ep6','pentagon')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble8_ep6','hexagon')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble9_ep6','octagon')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble10_ep6','oval')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble11_ep6','parallelogram')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeIdentif (phoneme,word) VALUES ('bubble12_ep6','triangle')" ,NULL,NULL,NULL); // TODO: dovrebbe essere rafforzativo
    
    sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
}

void DatabaseSupportTables::populateShapeNamingTable() {
    
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble1_ep6','circle')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble2_ep6','triangle')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble3_ep6','square')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble4_ep6','rectangle')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble5_ep6','trapezoid')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble6_ep6','rhombus')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble7_ep6','pentagon')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble8_ep6','hexagon')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble9_ep6','octagon')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble10_ep6','oval')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble11_ep6','parallelogram')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO shapeNaming (phoneme,word) VALUES ('bubble12_ep6','triangle')" ,NULL,NULL,NULL); // TODO: dovrebbe essere rafforzativo
    
    sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
}

void DatabaseSupportTables::populateBodyPartsTable() {
    
    sqlite3_exec(pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble1_ep6','nose')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble1_ep6','head')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble2_ep6','arm')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble2_ep6','chin')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble3_ep6','mouth')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble3_ep6','eye')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble4_ep6','nose')" ,NULL,NULL,NULL);  // TODO: dovrebbe essere rafforzativo
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble4_ep6','arm')" ,NULL,NULL,NULL);  // TODO: dovrebbe essere rafforzativo
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble5_ep6','hand')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble5_ep6','finger')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble6_ep6','tongue')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble6_ep6','foot')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble7_ep6','leg')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble7_ep6','ear')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble8_ep6','hand')" ,NULL,NULL,NULL);  // TODO: dovrebbe essere rafforzativo
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble8_ep6','leg')" ,NULL,NULL,NULL);  // TODO: dovrebbe essere rafforzativo
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble9_ep6','tongue')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble9_ep6','hair')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble10_ep6','neck')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble10_ep6','knee')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble11_ep6','shoulder')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble11_ep6','eye')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble12_ep6','hair')" ,NULL,NULL,NULL);  // TODO: dovrebbe essere rafforzativo
    sqlite3_exec(pdb, "INSERT INTO bodyParts (phoneme,word) VALUES ('bubble12_ep6','knee')" ,NULL,NULL,NULL);  // TODO: dovrebbe essere rafforzativo
    
    sqlite3_exec(pdb, "COMMIT;", NULL, NULL, NULL);
    
}



void DatabaseSupportTables::populateWordReadingTable() {
    sqlite3_exec(pdb,"BEGIN TRANSACTION;",NULL,NULL,NULL);
    
    // 4.1
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble1_ep4','bubble1_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble2_ep4','bubble2_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble3_ep4','bubble3_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble4_ep4','bubble4_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble5_ep4','bubble5_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble6_ep4','bubble6_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble7_ep4','bubble7_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble8_ep4','bubble8_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble9_ep4','bubble9_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble10_ep4','bubble10_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble11_ep4','bubble11_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble12_ep4','bubble12_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble13_ep4','bubble13_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble14_ep4','bubble14_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble15_ep4','bubble15_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble16_ep4','bubble16_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble17_ep4','bubble17_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble18_ep4','bubble18_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble19_ep4','bubble19_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble20_ep4','bubble20_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble21_ep4','bubble21_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble22_ep4','bubble22_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble23_ep4','bubble23_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble24_ep4','bubble24_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble25_ep4','bubble25_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_wordreading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_wordreading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_wordreading_p3')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_wordreading_p4')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO wordreading (phoneme,word) VALUES ('bubble26_ep4','bubble26_ep4_wordreading_p5')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb,"COMMIT;",NULL,NULL,NULL);
}


void DatabaseSupportTables::populateSentenceReadingTable() {
    sqlite3_exec(pdb,"BEGIN TRANSACTION;",NULL,NULL,NULL);
    
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble1_ep5','bubble1_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble1_ep5','bubble1_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble2_ep5','bubble2_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble2_ep5','bubble2_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble3_ep5','bubble3_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble3_ep5','bubble3_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble4_ep5','bubble4_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble4_ep5','bubble4_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble5_ep5','bubble5_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble5_ep5','bubble5_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble6_ep5','bubble6_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble6_ep5','bubble6_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble7_ep5','bubble7_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble7_ep5','bubble7_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble8_ep5','bubble8_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble8_ep5','bubble8_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble9_ep5','bubble9_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble9_ep5','bubble9_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble10_ep5','bubble10_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble10_ep5','bubble10_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble11_ep5','bubble11_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble11_ep5','bubble11_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble12_ep5','bubble12_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble12_ep5','bubble12_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble13_ep5','bubble13_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble13_ep5','bubble13_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble14_ep5','bubble14_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble14_ep5','bubble14_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble15_ep5','bubble15_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble15_ep5','bubble15_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble16_ep5','bubble16_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble16_ep5','bubble16_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble17_ep5','bubble17_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble17_ep5','bubble17_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble18_ep5','bubble18_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble18_ep5','bubble18_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble19_ep5','bubble19_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble19_ep5','bubble19_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble20_ep5','bubble20_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble20_ep5','bubble20_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble21_ep5','bubble21_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble21_ep5','bubble21_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble22_ep5','bubble22_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble22_ep5','bubble22_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble23_ep5','bubble23_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble23_ep5','bubble23_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble24_ep5','bubble24_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble24_ep5','bubble24_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble25_ep5','bubble25_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble25_ep5','bubble25_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble26_ep5','bubble26_ep5_sentencereading_p1')" ,NULL,NULL,NULL);
    sqlite3_exec(pdb, "INSERT INTO sentenceReading (phoneme,word) VALUES ('bubble26_ep5','bubble26_ep5_sentencereading_p2')" ,NULL,NULL,NULL);
    
    sqlite3_exec(pdb,"COMMIT;",NULL,NULL,NULL);
}
