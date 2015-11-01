#include "Cannon.h"
#include "Config/KeyCodeCOnfig.h"
#include "Config/NotificationNameConfig.h"

USING_NS_CC;

Cannon* Cannon::createCannon()
{
	Cannon* pCannon = new Cannon();
	if (pCannon && pCannon->initCannon()) 
	{
		//pCannon->autorelease();
		return pCannon;
	}
	else
	{
		CC_SAFE_DELETE(pCannon);
		return NULL;
	}
}

Cannon::Cannon():m_fRotation(0.0f)
{
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(Cannon::setRotationLeft), NOTIFY_BARREL_TURN_LEFT, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(Cannon::setRotationRight), NOTIFY_BARREL_TURN_RIGHT, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(Cannon::fire), NOTIFY_BARREL_FIRE, NULL);
}

Cannon::~Cannon() 
{
	this->m_pCannon->removeFromParentAndCleanup(true);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_BARREL_TURN_LEFT);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_BARREL_TURN_RIGHT);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_BARREL_FIRE);
}


bool Cannon::initCannon()
{	
	CCSpriteFrame *pCannonPedestalSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon_pedestal.png");
	CCSpriteFrame *pCannonBarrelSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon_barrel.png");

	this->m_pCannon = new CCLayer();
	this->m_pPedestal = CCSprite::spriteWithSpriteFrame(pCannonPedestalSpriteFrame);
	this->m_pBarrel = CCSprite::spriteWithSpriteFrame(pCannonBarrelSpriteFrame);

	this->m_pCannon->addChild(this->m_pBarrel);
	this->m_pCannon->addChild(this->m_pPedestal);

	//this->m_pBarrel->setPositionY(this->m_pPedestal->getContentSize().height/2);
	this->m_pBarrel->setAnchorPoint(ccp(0.5, 0));
	return true;

}

void Cannon::rotateToPoint(CCPoint ptTo)
{
	CCPoint ptFrom = m_pCannon->getPosition();
	float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x) / M_PI *180.0f;
	this->setRotation(90.0f - angle);
	this->m_pDirection = ptTo;
}

void  Cannon::setRotationLeft(CCObject *pSender) {
	this->setRotation(-10.0f);
}

void  Cannon::setRotationRight(CCObject *pSender) {
	this->setRotation(10.0f);
}

void Cannon::setRotation(float rotation) 
{
	m_fRotation = this->m_pBarrel->getRotation()+rotation;
	m_fRotation = m_fRotation <= -80 ? -80 : m_fRotation;
	m_fRotation = m_fRotation >= 80 ? 80 : m_fRotation;
	float absf_rotation = fabsf(rotation);
	float duration = absf_rotation / 180.0f*0.2f;
	CCFiniteTimeAction *pAction = CCRotateTo::actionWithDuration(duration, m_fRotation);
	this->m_pBarrel->runAction(pAction);
}

void Cannon::fire(CCObject *pSender)
{
	CCLog("shoot!!!!");

}

CCLayer* Cannon::getConnon() 
{
	return this->m_pCannon;
}

void Cannon::keyboardHook(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		return;
	case WM_KEYUP:
		CCLog("key code:%d",wParam);
		switch (wParam)
		{
		case KEY_CODE_LEFT:
			CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TURN_LEFT);
			break;
		case KEY_CODE_RIGHT:
			CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TURN_RIGHT);
			break;
		case KEY_CODE_FIRE:
			CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_FIRE);
			break;
		}
		break;
	}
}