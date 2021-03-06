#include "LoginScene.h"
#include "GameData/PlayerMrg.h"
#include "Component/GamingLayer.h"
#include "Config/NotificationNameConfig.h"
#include "GameData/MonsterMrg.h"
#include "Config/BaseConfig.h"
#include "Utils/AudioManager.h"
#include "Component/TipLayer.h"
bool LoginScene::init()
{
	_nowSate = MenuState_Star;
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *bg = CCSprite::spriteWithFile("actor_gamingbg.png");
	bg->setPosition(ccp(size.width / 2, size.height / 2));
	addChild(bg);
	//logo
	std::string tempstr = s_language + "logo.png";
	CCSprite *logo = CCSprite::spriteWithFile(tempstr.c_str());
	logo->setPosition(ccp(size.width / 2, size.height / 2 + size.height / 4));
	addChild(logo);

	//chenbao
	CCSprite *chenbao = CCSprite::spriteWithFile("actor_controllBg.png");
	chenbao->setAnchorPoint(ccp(0, 0));
	addChild(chenbao);
	//menu
	std::string nemuOneName = "";
	std::string nemuTwoName = "";
	nemuOneName = s_touchfile + s_language + "kaishi.png";
	nemuTwoName = s_touchfile + s_language + "tuichu.png";
	_pStarMenu = CCMenuItemImage::itemFromNormalImage(
		nemuOneName.c_str(),
		NULL,
		this,
		menu_selector(LoginScene::clickStar));
	_pStarMenu->setPosition(ccp(size.width / 2, size.height / 2 - 15));
	_pExitMenu = CCMenuItemImage::itemFromNormalImage(
		nemuTwoName.c_str(),
		NULL,
		this,
		menu_selector(LoginScene::clickExit));
	_pExitMenu->setPosition(ccp(size.width / 2, size.height / 2  - 20 - _pStarMenu->getContentSize().height));
	CCMenu *pMenu = CCMenu::menuWithItems(_pStarMenu, _pExitMenu, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCLayer::setIsKeypadEnabled(true); 


	//row
	_rowSp = CCSprite::spriteWithFile("shouzi.png");
	_rowSp->setAnchorPoint(ccp(1, 0.5));
	ChangeRowPosition();
	addChild(_rowSp);

	//music btn
	std::string str = s_touchfile  + "actor_btn_music_on.png";
	m_pMusicItem = CCMenuItemSprite::itemFromNormalSprite(
		CCSprite::spriteWithFile(str.c_str()),
		NULL,
		this,
		menu_selector(LoginScene::musicBtnClick)
		);
	CCMenu *pMusicMenu = CCMenu::menuWithItem(m_pMusicItem);
	pMusicMenu->setPosition(ccp(size.width - 50, size.height - 50));
	addChild(pMusicMenu);
	//set music is on or off
	setMusicBtnState();
	//init data 
	//PlayerMrg::getInstance()->Init();
	return true;
}

CCScene* LoginScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	LoginScene *layer = LoginScene::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void LoginScene::onEnter()
{
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(LoginScene::resumeGame), NOTIFY_RESUME_GAME, NULL);
	CCLayer::onEnter();
}

void LoginScene::onExit()
{
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_RESUME_GAME);
	CCLayer::onExit();
}

void LoginScene::resumeGame(CCObject *pSender)
{
	this->setIsKeypadEnabled(true);
}

bool LoginScene::keyAllClicked(int iKeyID, cocos2d::CCKeypadStatus iKeyState)
{


	if (iKeyID == 'w' || iKeyID == 'W' || iKeyID == HANDSET_UP || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_UP)
	{
		onClickW(iKeyState);
	}
	else if (iKeyID == 's' || iKeyID == 'S' || iKeyID == HANDSET_DOWN || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_DOWN)
	{
		onClickS(iKeyState);
	}
	else if (iKeyID == 'a' || iKeyID == 'A' || iKeyID == HANDSET_LEFT || iKeyID == HANDSET_LEFT_ || iKeyID == KEY_LEFT)
	{
		onClickA(iKeyState);
	}
	else if (iKeyID == 'd' || iKeyID == 'D' || iKeyID == HANDSET_RIGHT || iKeyID == HANDSET_RIGHT_ || iKeyID == KEY_RIGHT)
	{
		onClickD(iKeyState);
	}
	else if (iKeyID == 'j' || iKeyID == 'J' || iKeyID == HANDSET_Y || iKeyID == HANDSET_Y_ || iKeyID == KEY_Y)
	{
		onClickJ(iKeyState);
	}
	else if (iKeyID == 'i' || iKeyID == 'I' || iKeyID == HANDSET_A || iKeyID == HANDSET_A_ || iKeyID == KEY_A)
	{
		onClickI(iKeyState);
	}
	else if (iKeyID == 'k' || iKeyID == 'K' || iKeyID == HANDSET_B || iKeyID == HANDSET_B_ || iKeyID == KEY_B)
	{
		onClickK(iKeyState);
	}
	else if (iKeyID == 'l' || iKeyID == 'L' || iKeyID == HANDSET_X || iKeyID == HANDSET_X_ || iKeyID == KEY_X)
	{
		onClickL(iKeyState);
	}
	else 
	{
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, iKeyState);
		return false;
	}
	return true;
}

void LoginScene::onClickA(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		_nowSate = MenuState(_nowSate + 1);
		if (_nowSate == MenuState_End)
		{
			_nowSate = MenuState_Star;
		}
		ChangeRowPosition();
	}
}

void LoginScene::onClickS(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		_nowSate = MenuState(_nowSate + 1);
		if (_nowSate == MenuState_End)
		{
			_nowSate = MenuState_Star;
		}
		ChangeRowPosition();
	}
	
}

void LoginScene::onClickD(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
	}
}

void LoginScene::onClickW(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		_nowSate = MenuState(_nowSate - 1);
		if (_nowSate == MenuState_Begin)
		{
			_nowSate = MenuState_Exit;
		}
		ChangeRowPosition();
	}
	
}

void LoginScene::onClickI(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
	}
}

void LoginScene::onClickL(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		clickExit(NULL);
	}
}

void LoginScene::onClickJ(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		switch (_nowSate)
		{
		case MenuState_Star:
			clickStar(NULL);
			break;
		case MenuState_Exit:
		{
			CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
		break;
		default:
			break;
	}
	}
	
}

void LoginScene::onClickK(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		musicBtnClick(NULL);
	}
}

void LoginScene::clickStar(CCObject* pSender)
{

	PlayerMrg::getInstance()->Init();
	CCScene *scene = CCScene::node();
	GamingLayer*layer = GamingLayer::createGamingLayer();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(scene);
	//PlayerMrg::getInstance()->Init();
	/*CCString str = CCString("100");
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATEGRADE, &str);*/
	/*MonsterMrg *monster = MonsterMrg::Create(1001);
	addChild(monster);*/
}

void LoginScene::clickExit(CCObject* pSender)
{
	this->setIsKeypadEnabled(false);
	CCDirector::sharedDirector()->getRunningScene()->addChild(TipLayer::Create());
	//this->removeFromParentAndCleanup(true);
}

void LoginScene::ChangeRowPosition()
{
	switch (_nowSate)
	{
	case MenuState_Star:
	    {
			_rowSp->setPosition(ccp(_pStarMenu->getPosition().x - _pStarMenu->getContentSize().width / 2 - 20, _pStarMenu->getPosition().y));
	    }
		break;
	case MenuState_Exit:
	   {
		   _rowSp->setPosition(ccp(_pExitMenu->getPosition().x - _pExitMenu->getContentSize().width / 2 - 20, _pExitMenu->getPosition().y));
	   }
		break;
	default:
		break;
	}
}


void LoginScene::musicBtnClick(CCObject *pSender)
{
	AudioManager::getInstance()->setMusicState(!AudioManager::getInstance()->getMusicState());
	AudioManager::getInstance()->setEffectState(!AudioManager::getInstance()->getEffectState());
	this->setMusicBtnState();
}

void LoginScene::setMusicBtnState()
{
	if (AudioManager::getInstance()->getMusicState())
	{
		std::string str = s_touchfile  + "actor_btn_music_on.png";
		AudioManager::getInstance()->playMusic("audio/background.mp3", true);
		AudioManager::getInstance()->resumeAllEffects();
		m_pMusicItem->setNormalImage(CCSprite::spriteWithFile(str.c_str()));
	}
	else
	{
		std::string str = s_touchfile  + "actor_btn_music_off.png";
		AudioManager::getInstance()->stopMusic();
		AudioManager::getInstance()->pauseAllEffects();
		m_pMusicItem->setNormalImage(CCSprite::spriteWithFile(str.c_str()));
	}
}
