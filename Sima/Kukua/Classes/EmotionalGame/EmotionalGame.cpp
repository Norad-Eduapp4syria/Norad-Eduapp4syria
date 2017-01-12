#include "EmotionalGame.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../MapScene/MapScene.h"
#include "../AppMacros.h"
#include "../Utils/Data/ArabicHelper.h"


USING_NS_CC;

using namespace cocostudio::timeline;

// Le Emoticon sono:
// CORAGGIO, GIOIA, SODDISFAZIONE, SERENITA, 
// SORPRESA, STIMA, REAZIONE, PIACERE, FUTURO 

Scene* EmotionalGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EmotionalGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


EmotionalGame::~EmotionalGame() {
    
    CCLOG("~EmotionalGame");
    delete objSema;
    delete objTable;
    delete objAudioBtn;
    delete textProvider;
    this->unscheduleUpdate();
    
    int c;
    for (c = 0; c < 9; c++) {
        delete objEmoticon[c];
    }

    delete objBoxQuestion;
    for (c = 0; c < 6; c++) {
        delete objAnswer[c];
    }
}

// on "init" you need to initialize your instance
bool EmotionalGame::init()
{

    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
	PATH = "Salute_Emotiva/";
    rootNode = CSLoader::createNode(PATH + "MainScene.csb");
	rootNode->setAnchorPoint(Point(0.5, 0.5));
	rootNode->setPosition(Point(_director->getWinSize().width / 2,
		_director->getWinSize().height / 2));

	addChild(rootNode);

    gameIsClosing = false;
    
    
	// sema
	objSema = new GameObject(*rootNode, "sima",	PATH + "csd/Sima.csb");
	objSema->bringToFront();
	
	// randomize mood
	objSema->play("enter", [=]() { objSema->play("standing", nullptr, false); }, nullptr, false);
	chosenMood = RandomHelper::random_int(0, 8);
	setSemaBadState(chosenMood);

    textProvider = new EmoTextProvider(chosenMood);
    
	// table
	objTable = new GameObject(*rootNode, "table",
							   PATH + "csd/table.csb", 
							   "table/table");
	// 2 secondi e parte il tavolo
	objTable->bringToFront();

	// audiobutton
	audioButton = static_cast<cocos2d::ui::Button*>(rootNode->getChildByName("audio_Btn")->getChildByName("audio_btn")->getChildByName("Button"));
	objAudioBtn = new GameObject(*rootNode, "audio_Btn", PATH + "csd/Audio_Btn.csb");
    audioButton->addClickEventListener(([=](Ref *) {  playAudioCommand(); }));

	// 9 emoticon
	for (int c = 0; c < 9; c++)
	{
		objEmoticon[c] = new EmoCustomDragGameObject(*rootNode, "emo_" + StringUtility::toString(c),
			PATH + "csd/Emotions_" + StringUtility::toString(c) + ".csb", 
			"emo_" + StringUtility::toString(c) + "/" + "emo_" + StringUtility::toString(c), 
			_eventDispatcher);

		objEmoticon[c]->originalPos = convertToNodeSpace(objEmoticon[c]->getPosition());
		objEmoticon[c]->bringToFront();
		objEmoticon[c]->setTouchable(true);
		objEmoticon[c]->setSwallow(true);
		objEmoticon[c]->index = c;
		objEmoticon[c]->isActive = false;
		
		Sprite *colliderEmo = static_cast<Sprite*>(rootNode->getChildByName("emo_" + StringUtility::toString(c))->
															 getChildByName("emo_" + StringUtility::toString(c))->
															 getChildByName("emo_" + StringUtility::toString(c)));

		//set callback
		std::function<void(Sprite*, int)> callback = std::bind(&EmotionalGame::callback_TouchEnd, this, colliderEmo, objEmoticon[c]->index);
		objEmoticon[c]->setTouchEndCallBack(callback);
	}

	// box question
	objBoxQuestion = new GameObject(*rootNode, "Box_question", PATH + "csd/Box_question.csb", "box_question/box_question");
	objBoxQuestion->bringToFront();
	//auto textQuestionRef = static_cast<cocos2d::ui::Text*>(rootNode->getChildByName("Box_question")->getChildByName("box_question")->getChildByName("Text"));
	
    auto txtRef2 = static_cast<Node*>(rootNode->getChildByName("Box_question")->getChildByName("box_question"));
    textQuestion = ArabicHelper::getInstance()->createLabel("", 35);
    txtRef2->addChild(textQuestion);
    textQuestion->setVerticalAlignment(TextVAlignment::TOP) ;
    textQuestion->setHorizontalAlignment(TextHAlignment::CENTER);
    textQuestion->setColor(Color3B(31, 106, 215));
    textQuestion->setWidth( 850.0 );
    textQuestion->setHeight(150.0);
    
    
	// 6 answers
	for (int c = 0; c < 6; c++)
	{
        objAnswer[c] = new GameObject(*rootNode, "answer_" + StringUtility::toString(c), PATH + "csd/Box_answer.csb", "box_answer/box_answer");
        btnAnswer[c] = static_cast<cocos2d::ui::Button*>(rootNode->getChildByName("answer_" + StringUtility::toString(c))->getChildByName("box_answer")->getChildByName("Button"));
        btnAnswer[c]->addClickEventListener(([=](Ref *) {  endScene(); }));
        
        auto txtRef = static_cast<Node*>(rootNode->getChildByName("answer_" + StringUtility::toString(c))->getChildByName("box_answer"));
        textAnswer[c] = ArabicHelper::getInstance()->createLabel("", 30);
        txtRef->addChild(textAnswer[c]);
        textAnswer[c]->setVerticalAlignment(TextVAlignment::CENTER) ;
        textAnswer[c]->setHorizontalAlignment(TextHAlignment::CENTER);
        textAnswer[c]->setColor(Color3B(73, 38, 88));
        textAnswer[c]->setWidth( 380.0 );
        textAnswer[c]->setHeight(80.0);
         //textAnswer[c] = static_cast<cocos2d::ui::Text*>(rootNode->getChildByName("answer_" + StringUtility::toString(c))->getChildByName("box_answer")->getChildByName("Text"));
	}
	
	// do not start update until the scene is set
	this->unscheduleUpdate();

	// table appears
	float audioDuration = 2;
	runAction(Sequence::create(DelayTime::create(audioDuration), CallFunc::create(
		[=]() {
		objTable->play("enter", nullptr, false);
		objAudioBtn->play("enter");
	}), 
		DelayTime::create(1),
		CallFunc::create(
		[=]() {
            playAudioCommand();
            this->scheduleUpdate();
	}), nullptr));

    return true;
}

void EmotionalGame::endScene()
{
      /*
    int c;
     for (int c = 0; c < 6; c++) {
     btnAnswer[c]->removeEventListener(); // TODO
     }
     */
    CCLOG("....end Game!");
    //MessageBox("Fine", "Fine");
    
    
    closeGame();
}


void EmotionalGame::setSemaGoodState(int state)
{
	string filename;
	
	//CORAGGIO, GIOIA, SODDISFAZIONE, SERENITA, SORPRESA, STIMA, REAZIONE, PIACERE, FUTURO
	//forse qui servono le head_ e non le emo, ma non le ho ...

	switch (state)
	{
	case (int)CORAGGIO:
		filename = "head_coraggio.png";
		break;
	case (int)GIOIA:
		filename = "head_gioia.png";
		break;
	case (int)SODDISFAZIONE:
		filename = "head_soddisfazione.png";
		break;
	case (int)SERENITA:
		filename = "head_serenita.png";
		break;
	case (int)SORPRESA:
		filename = "head_sorpresa.png";
		break;
	case (int)STIMA:
		filename = "head_stima.png";
		break;
	case (int)REAZIONE:
		filename = "head_reazione.png";
		break;
	case (int)PIACERE:
		filename = "head_piacere.png";
		break;
	case (int)FUTURO:
		filename = "head_futuro.png";
		break;
	}

	//sema sprite
	static_cast<Sprite*>(rootNode->getChildByName("sima")->
		getChildByName("Master")->
		getChildByName("Head_master")->
		getChildByName("head_rabbia")->
		getChildByName("head_rabbia"))->
		setTexture(PATH + "png/Sima/" + filename);
}

void EmotionalGame::setSemaBadState(int state)
{
	string filename;
	 //PAURA, TRISTEZZA, DELUSIONE, RABBIA, INDIFFERENZA, DISPREZZO, RASSEGNAZIONE, DISGUSTO, NOSTALGIA
	
	switch (state)
	{
	case (int)PAURA:
		filename = "head_paura.png";
		break;
	case (int)TRISTEZZA:
		filename = "head_tristezza.png";
		break;
	case (int)DELUSIONE:
		filename = "head_delusione.png";
		break;
	case (int)RABBIA:
		filename = "head_rabbia.png";
		break;
	case (int)INDIFFERENZA:
		filename = "head_indifferente.png";
		break;
	case (int)DISPREZZO:
		filename = "head_disprezzo.png";
		break;
	case (int)RASSEGNAZIONE:
		filename = "head_rassegnazione.png";
		break;
	case (int)DISGUSTO:
		filename = "head_disgusto.png";
		break;
	case (int)NOSTALGIA:
		filename = "head_nostalgia.png";
		break;
	}

	//sema sprite
	static_cast<Sprite*>(rootNode->getChildByName("sima")->
		getChildByName("Master")->
		getChildByName("Head_master")->
		getChildByName("head_rabbia")->
		getChildByName("head_rabbia"))->
		setTexture(PATH + "png/Sima/" + filename);
}


void EmotionalGame::callback_TouchEnd(Sprite* dragCollider, int emoIndex)
{
    std:stringstream ss;
	ss << "HEALTH Callback - onTouchEnded : ";
	ss << emoIndex;
	
	// su logcat il cclog nn si legge?
	//MessageBox(ss.str().c_str(), "suca");

	CCLOG("HEALTH Callback - onTouchEnded : %d", emoIndex);
	printf("HEALTH Callback - onTouchEnded : %d", emoIndex);

	if (checkIntersection(dragCollider))
	{
		if (emoIndex == chosenMood)
		{
			isRolling = false;
			objSema->play("feedback");
			objTable->play("exit");
			for (int c = 0; c < 9; c ++)
				objEmoticon[c]->play("fall", 
					[=]() { objEmoticon[c]->setVisible(false); }, false);
			
			// change ema good expression
			setSemaGoodState(emoIndex);

			runAction(Sequence::create(DelayTime::create(2), CallFunc::create([=]() { showQuestion(); }), nullptr));
		}
		else 
			objEmoticon[emoIndex]->jumpBack();
	}
	else
		// emo jumps back
		objEmoticon[emoIndex]->jumpBack();
}

Rect EmotionalGame::getAbsPos(const Sprite *spr, int w, int h)
{
	return Rect(spr->convertToWorldSpace(spr->getPosition()).x,
		spr->convertToWorldSpace(spr->getPosition()).y,
		w, h);
}

bool EmotionalGame::checkIntersection(Sprite *dragCollider)
{
	if (dragCollider != nullptr)
	{
		Sprite* semaHead = static_cast<Sprite*>(rootNode->getChildByName("sima")->
			getChildByName("Master")->
			getChildByName("Head_master")->
			getChildByName("head_rabbia")->
			getChildByName("head_rabbia"));

		Rect charRect = semaHead->getBoundingBox();
		Rect dragRect = dragCollider->getBoundingBox();

		Rect absoluteTrigBox = getAbsPos(semaHead, charRect.size.width, charRect.size.height);
		Rect absoluteDragBox = getAbsPos(dragCollider, dragRect.size.width, dragRect.size.height);

		if (absoluteTrigBox.intersectsRect(absoluteDragBox))
		{
			return true;
		}
	}
	// dont intersect: fail back
	return false;
}

void EmotionalGame::showQuestion()
{
    
    playAudioQuestion();
    
	// set text for questions and answers
	setText();

	// first the question, the the answers
	runAction(Sequence::create(
		CallFunc::create([=]() 
	            { 
					objSema->play("exit", [=]() { objSema->setVisible(false); }, false);
					objBoxQuestion->play("enter"); 
				}),
		DelayTime::create(1), 
		CallFunc::create([=]() 
				{
				   for (int c = 0; c < 6; c++)
				   {
					   objAnswer[c]->setVisible(true);
					   objAnswer[c]->bringToFront();
					   objAnswer[c]->play("enter");
				   }
				}),
		nullptr));
}

void EmotionalGame::update(float delta)
{
	if (!isRolling)
		return;

	// scrolls emoticons
	for (int c = 0; c < 9; c++)
	{
		Vec2 pos;

		pos = objEmoticon[c]->tapisPosition;
		pos.x -= emoScrollSpeed * delta;

		//reset position while exiting from right
		if (pos.x < -140)
			pos = objEmoticon[3]->originalPos;

		objEmoticon[c]->tapisPosition = convertToNodeSpace(pos);

		if (!objEmoticon[c]->isActive)
			 objEmoticon[c]->setPosition(convertToNodeSpace(pos));
	}
}


void EmotionalGame::playAudioCommand()
{

    int skin = chosenMood;
    
    CCLOG("playAudioCommand.. skin = %d", skin);
    
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    string linkAudio = PATH + "audio/0" + StringUtility::toString(skin) + "_1.mp3";
    audioEngine->playEffect(linkAudio.c_str());
}


void EmotionalGame::playAudioQuestion()
{
    
    int skin = chosenMood;
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    string linkAudio = PATH + "audio/0" + StringUtility::toString(skin) + "_2.mp3";
    audioEngine->playEffect(linkAudio.c_str());
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//-------   ------   ------   -------  ---
//   |      |____	|_____		 | 	    |
//   |		|			  |      |      |
//   -		------   -----       -     ---

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void EmotionalGame::setText()
{	
    // set font size?
    /*
	int questionFontSize = 35;
	int answerFontSize = 30;
	textQuestion->setFontSize(questionFontSize);
	textAnswer[0]->setFontSize(answerFontSize);
	textAnswer[1]->setFontSize(answerFontSize);
	textAnswer[2]->setFontSize(answerFontSize);
	textAnswer[3]->setFontSize(answerFontSize);
	textAnswer[4]->setFontSize(answerFontSize);
	textAnswer[5]->setFontSize(answerFontSize);
     */
    
     /*
    textQuestion->setString( textProvider->getQuestion() );
    textAnswer[0]->setString( textProvider->getAnswer1() );
    textAnswer[1]->setString( textProvider->getAnswer2() );
    textAnswer[2]->setString( textProvider->getAnswer3() );
    textAnswer[3]->setString( textProvider->getAnswer4() );
    textAnswer[4]->setString( textProvider->getAnswer5() );
    textAnswer[5]->setString( textProvider->getAnswer6() );
    
    return;
   */
    
	switch (chosenMood)
	{       
		case (int)PAURA:
			textQuestion->setString("ممتاز ! شكرا على مساعدة سيما في ايجاد الشجاعة . برأيك لما كانت سيما خائفة ؟");

			textAnswer[0]->setString("من الحرب");
			textAnswer[1]->setString("من بعض الحيوانات");
			textAnswer[2]->setString("من الظلمة");
			textAnswer[3]->setString("من بعض الاطفال الاشرار");
			textAnswer[4]->setString("من البرق والرعد");
			textAnswer[5]->setString("من ان تبقى وحيدة");

			break;
	
		case (int)TRISTEZZA:
			textQuestion->setString("ممتاز! شكرا على مساعدة سيما في ايجاد بعض السعادة . برأيك لما سيما الان سعيدة ؟");

			textAnswer[0]->setString("لديها الكثير من الاصدقاء");
			textAnswer[1]->setString("ربحت جائزة كبيرة");
			textAnswer[2]->setString("انتهت الحرب");
			textAnswer[3]->setString("شفيت من مرضها");
			textAnswer[4]->setString("حصلت على علامات جيدة في المدرسة");
			textAnswer[5]->setString("غدا هو يوم العيد");

			break;
	
		case (int)DELUSIONE:
			textQuestion->setString("ممتاز ! بمساعدك سيما راضية عن نفسها من جديد . برأيك لما كانت تشعر بالخيبة ؟");

			textAnswer[0]->setString("خسرت في مسابقة");
			textAnswer[1]->setString("اساءت لها صديقة بتصرفاتها");
			textAnswer[2]->setString("العالم شرير");
			textAnswer[3]->setString("الناس اشرار");
			textAnswer[4]->setString("لم تكن تلك هي الهدية التي كانت تنتظرها");
			textAnswer[5]->setString("لن تكون هناك حفلة مع الاصدقاء");

			break;
	
		case (int)RABBIA:
			textQuestion->setString("ممتاز ! شكرا على مساعدة سيما في العودة الى صفائها . برأيك لما كانت سيما غاضبة ؟");

			textAnswer[0]->setString("الحرب");
			textAnswer[1]->setString("اختلفت مع صديقتها");
			textAnswer[2]->setString("لم تحصل على الهدية التي كانت تتمناها");
			textAnswer[3]->setString("تشعر بألم ما في جسمها");
			textAnswer[4]->setString("تعرضت للظلم");
			textAnswer[5]->setString("تعرضت الى مزحة ثقيلة   ");

			break;
	
		case (int)INDIFFERENZA:
			textQuestion->setString("ممتاز ! شكرا بمساعدتك استطعنا ان نحضر مفاجأة جميلة لسيما! برأيك ماذا كانت المفاجأة ؟");

			textAnswer[0]->setString("حصلت على هدية لم تكن تتوقعها");
			textAnswer[1]->setString("حصلت على معاملة لطيفة");
			textAnswer[2]->setString("ولادة حيوان صغير");
			textAnswer[3]->setString("اشرقت الشمس");
			textAnswer[4]->setString("حصلت على خبر جميل");
			textAnswer[5]->setString("رأت نجما يسطع في السماء");

			break;
	
		case (int)DISPREZZO:
			textQuestion->setString("ممتاز! شكرا على مساعدة في ايجاد اشخاص تقدرهم . برأيك لما تحتقر سيما بعض الاشخاص؟");

			textAnswer[0]->setString("اساؤوا معاملة قط صغير");
			textAnswer[1]->setString("لانهم ضربوها");
			textAnswer[2]->setString("اساؤوا معاملة اشخاص ابرياء");
			textAnswer[3]->setString("سرقوا بعض الألعاب");
			textAnswer[4]->setString("اهانوا سيدة عجوز");
			textAnswer[5]->setString("كانوا غير مؤدبين");

			break;
	
		case (int)RASSEGNAZIONE:
			textQuestion->setString("ممتاز! بمساعدك استطاعت سيما ايجاد القوة للمواجهة . برأيك لما كانت سيما تشعر بالاستسلام ؟");

			textAnswer[0]->setString("كانت خائفة من تغيير شيء ما");
			textAnswer[1]->setString("كانت خائفة من يتم توبيخها ان تكلمت");
			textAnswer[2]->setString("تعتقد ان لا احد يود الاصغاء لها");
			textAnswer[3]->setString("تعتقد ان لا قيمة لها");
			textAnswer[4]->setString("تعتقد انها صغيرة جدا لعمل اي شيء");
			textAnswer[5]->setString("يقرر الاخرون دوما بدلا عنها");

			break;
	
		case (int)DISGUSTO:
			textQuestion->setString("ممتاز! شكرا بمساعدك استطاعت سميا ايجاد اشياء كثيرة تعجبها . برأيك لما كانت سيما تشعر بالقرف؟");

			textAnswer[0]->setString("لم يعجبها طعم الفاكهة");
			textAnswer[1]->setString("هناك راتحة كريهة جدا");
			textAnswer[2]->setString("رأت ما حدث في الحرب");
			textAnswer[3]->setString("رأت رجلا مسلحا");
			textAnswer[4]->setString("شربت ماء مالح");
			textAnswer[5]->setString("تشعر بوجع في المعدة");

			break;
	
		case (int)NOSTALGIA:
			textQuestion->setString("ممتاز ! شكرا بمساعدتك استطاعت سيما ايجاد بعض الامل من اجل المستقبل. برأيك لما كانت سيما تشعر بالحنين؟");

			textAnswer[0]->setString("اشتاقت الى منزلها القدي");
			textAnswer[1]->setString("اشتاقت الى اصدقاءها");
			textAnswer[2]->setString("Hاشتاقت الى اقاربها");
			textAnswer[3]->setString("اشتاقت الى الماضي");
			textAnswer[4]->setString("اشتاقت الى بلدها");
			textAnswer[5]->setString("اشتاقت الى اقاربها");

			break;
	}
}


void EmotionalGame::closeGame()
{
    if (gameIsClosing) return;
    gameIsClosing = true;
    Logger::getInstance()->logEvent("EmotionalGame", Logger::CLOSE, "");
    audioEngine->stopAllEffects();
    audioEngine->stopBackgroundMusic();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, MapScene::createScene(), TRANSITION_COLOR));
}
