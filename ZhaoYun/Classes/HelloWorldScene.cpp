#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    //修改背景图片
    Sprite* pSprite = Sprite::create("background_1.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);//这里的0表示放在最底层
    
	//添加摇杆
	rocker = HRocker::createHRocker("Direction_bt.png","Direction_bc.png",ccp(110,60));//其中第一张图片为摇杆的按钮，第二张为背景
	this->addChild(rocker,2);
	rocker->startRocker(true);


	//添加赵云精灵
	hero=Hero::create();
	hero->InitHeroSprite("zhoayun.png");
	hero->setPosition(ccp(200,200));
	this->addChild(hero,1);
	//hero->SetAnimation("run_animation.plist","run_animation.png",8,true);//8表示plist中的图片数目,false表示脸朝右


	//启动updata事件
	this->scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float delta)
{
    int newX = 0;
    int newY = 0;
	//判断是否按下摇杆及其类型
	switch(rocker->rocketDirection)
	{
	case 1:
        hero->SetAnimationAdv("run_animation.plist","run_animation.png", "run_", 2, 8, rocker->rocketRun);
        if(hero->getPosition().x+2 + hero->GetHeroSprite()->getContentSize().width/2 > visibleSize.width)
        {
            break;
        }
        hero->setPosition(ccp(hero->getPosition().x+2,hero->getPosition().y)); //向右走
		break;
	case  2:
        hero->SetAnimationAdv("run_animation.plist","run_animation.png", "run_", 2, 8, rocker->rocketRun);
        if(hero->getPosition().y+2 + hero->GetHeroSprite()->getContentSize().height/2 > visibleSize.height)
        {
            break;
        }
        hero->setPosition(ccp(hero->getPosition().x, hero->getPosition().y+2));   //向上走
		break;
	case 3:
        hero->SetAnimationAdv("run_animation.plist","run_animation.png", "run_", 2, 8, rocker->rocketRun);
        if(hero->getPosition().x-2 - hero->GetHeroSprite()->getContentSize().width/2 < 0)
        {
            break;
        }
        hero->setPosition(ccp(hero->getPosition().x-2,hero->getPosition().y));   //向左走
		break;
	case 4:
        if(hero->getPosition().y-2 - hero->GetHeroSprite()->getContentSize().height/2 < 0)
        {
            break;
        }
        hero->SetAnimationAdv("run_animation.plist","run_animation.png", "run_", 2, 8, rocker->rocketRun);
        hero->setPosition(ccp(hero->getPosition().x,hero->getPosition().y-2));   //向下走
		break;
	default:
		hero->StopAnimation();//停止所有动画和运动
		break;

    }

}
