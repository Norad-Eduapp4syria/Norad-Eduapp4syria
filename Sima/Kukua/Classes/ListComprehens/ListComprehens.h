#ifndef __ListComprehens_SCENE_H__
#define __ListComprehens_SCENE_H__

#include "cocos2d.h"
#include "ListComp_DragGO.h"
#include "ListComp_RoundManager.h"

//using namespace CocosDenshion;

// globals
const int N_ALL_DRAG_OBJS = 40;
const int N_DRAG_OBJS = 9;
const int N_BIG_OBJS = 10;
const int N_BIG_TRIGS_NAMES = 6;
const int N_BIG_TRIGS_OBJS = 4;
const int N_COLORS = 6;
const int N_CHARS = 6;
const int N_ROUNDS = 5;

// correct object and color ID
static int rightObjID, rightColorID, chosenGridID;

// limbo ID
static int limbo = -99;

// total objects name and id
const std::string objNames[N_ALL_DRAG_OBJS] =
{
	"banana", "boat", "book", "boots", "broom",
	"bucket", "car", "clock", "crab", "dish",
	"dog", "doll", "duck", "fan", "fish",
	"fork", "frog", "glass", "glasses", "gress",
	"hat", "hen", "jug", "lamp", "mouse",
	"pan", "pen", "pig", "plant", "rug",
	"shell", "shorts", "sock", "spoon", "star",
	"sun", "train", "trumpet", "umbrella", "watch"
};

// color filenames
const std::string objColors[N_COLORS] =
{
	"_b", "_bl", "_g", "_r", "_w", "_y"
};
// color names
const std::string objColorNames[N_COLORS] =
{
	"blue", "black", "green", "red", "white", "yellow"
};

// characters csd names
const std::string objChars[N_CHARS] =
{
	"boy", "girl", "man", "woman", "oldman", "oldwoman"
};
// characters names
const std::string objCharNames[N_CHARS] =
{
	"young boy", "young girl", "man", "woman", "old man", "old woman"
};

// big objects names
const std::string objBigNames[N_BIG_OBJS] =
{
	"blackboard", "bridge", "desk",
	"horse", "house", "rock", "table",
	"tree", "truck", "window"
};

// big objects triggers
const std::string objBigTriggerNames[N_BIG_TRIGS_NAMES] =
{
	"on the", 
	"next to the",
	"under the",
	"to the right of the",
	"to the left of the",
	"on top of the"
};



// sentence
static string sentence;
static string sentenceToRead;
static string prefix = "GIVE THE";
static string conc = "TO THE";
static string suffix;

// objects on screen 
static GameObject *objFade;
static Sprite *fadeSprite;
static ListComp_DragGO *cDraggableObj[N_DRAG_OBJS];
static GameObject *objSign;
static GameObject *objHelpHand;
static GameObject *characterObj[2];
static GameObject *objBig;
static GameObject *bigTriggersObj[N_BIG_TRIGS_OBJS];
static Label * lblSentence;
static Vec2 bigObjOriginalPos,
char1OriginalPos,
char2OriginalPos;

static int roundBalancer = 50;
static int roundNumbers = 5, roundNumber = 0;



// struct for round management
struct RoundSettings
{
	int number;					// round number
	bool isRandom;				// isRandom
	int rightCharacterID;		// character ID (0...5) for obj dropping
	int rightTriggerID;			// trigger ID (0...3) for obj dropping
	int rightDragObjID;         // objID (0...N_ALL_DRAG_OBJS - 1) to drag
	int rightColorID;           // colorID (0...5) to set

	RoundSettings(int _num)
	{
		number = _num;
		isRandom = true;
		rightCharacterID = limbo;
		rightTriggerID = limbo;
		rightDragObjID = limbo;
		rightColorID = limbo;
	}
	~RoundSettings(){}
};
static RoundSettings *rounds[5];

class ListComprehens : public cocos2d::Layer
{
    
private:
    GameObject *objFondale;
    GameObject *objBig;
    GameObject *objSign;
    GameObject *objWell;
    GameObject *objTry;
    //GameObject *listenBtn;
    void playAudioCommand();
    void playAudioCommandPart(string _name);
    void addListenButton();
    
public:

	 ListComprehens();
	~ListComprehens();
    
    float scorePercent;
    float scoreToSubtract;
    float roundScorePercent[5];

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    static const std::string PATH;
    static std::string NAME;
    
    Node* rootNode;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void startGame();
	void setGridObjects();
	void setDraggableObjects();
	void resetScene();
	void setNewRound();
	void setSign();
	void callback_NewRound(Ref* pSender);
	void callback_TouchBegan();
	void callback_SUCCESS();
	void callback_FAIL();

    int getRandomWithExclusion(int start, int end, vector<int> exclude);
    
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    
    void addBackToHomeButton();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ListComprehens);
};

#endif // __ListComprehens_SCENE_H__
