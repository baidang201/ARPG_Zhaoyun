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

   // 修改背景图片
	//更改为自己定义的地图
    mymap=MyMap::create();
	mymap->InitMap("12.png",visibleSize);
	this->addChild(mymap,0);//这里的0表示放在最底层
    
	//添加摇杆
	rocker = HRocker::createHRocker("Direction_bt.png","Direction_bc.png",ccp(110,60));//其中第一张图片为摇杆的按钮，第二张为背景
	this->addChild(rocker,2);
	rocker->startRocker(false);//true表示只能响应这层的触摸


	//添加赵云精灵
	hero=Hero::create();
    hero->InitHeroSprite("hero.png");
	hero->setPosition(ccp(200,200));
	this->addChild(hero,1);

	//添加攻击按钮
    btn=MyControlButton::create();
    btn->CreateButton("bt.png");
    btn->setPosition(ccp(visibleSize.width-50,50));
    this->addChild(btn,2);


	//设置英雄的血条 
	m_pProgressView = new ProgressView();  
	m_pProgressView->setPosition(ccp(150, 450));  
	m_pProgressView->setScale(2.2f);  
	m_pProgressView->setBackgroundTexture("xue_back.png");  
	m_pProgressView->setForegroundTexture("xue_fore.png");  
	m_pProgressView->setTotalProgress(100.0f);  
	m_pProgressView->setCurrentProgress(100.0f); 
	//下面两个是为了让血条更好好看
	CCSprite *xuekuang=CCSprite::create("kuang.png");//添加血条的框架
	xuekuang->setPosition(ccp(m_pProgressView->getPositionX(),m_pProgressView->getPositionY()));
	CCSprite *touxiang=CCSprite::create("touxiang.png");//添加英雄的左上角的小头像
	touxiang->setPosition(ccp(m_pProgressView->getPositionX()-120,m_pProgressView->getPositionY()));
	this->addChild(touxiang,2);
	this->addChild(xuekuang,2);
	this->addChild(m_pProgressView, 2);  

	//添加怪物
	monster1=Monster::create();
	//monster1->InitMonsterSprite("monster.png");
	monster1->InitMonsterSprite("monster.png","xue_back.png","xue_fore.png");
	monster1->setPosition(ccp(visibleSize.width-150,visibleSize.height/2));
	this->addChild(monster1,1);
	
    auto listenerKey = EventListenerKeyboard::create();//创建一个触摸监听
    listenerKey->onKeyPressed = [this](EventKeyboard::KeyCode code, Event* event)
    {
        //isCanMove = true;
        switch(code)
        {
        case EventKeyboard::KeyCode::KEY_X:
            btn->isTouch = true;
            break;
        default:
            break;
        }
    };

    listenerKey->onKeyReleased = [this](EventKeyboard::KeyCode code, Event* event)
    {
        btn->isTouch = false;
    };

    //将触摸监听添加到eventDispacher中去
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey ,this);


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

	//判断是否按下摇杆及其类型
	switch(rocker->rocketDirection)
	{
	case 1:
        //CCLog("move %f   %f", hero->getPosition().x, hero->getPosition().y);
        hero->SetAnimationAdv("hero_run.plist","hero_run.png", "hero_run", 1, 8, rocker->rocketRun);
        if(hero->getPosition().x+2 + hero->GetHeroSprite()->getContentSize().width/2 < visibleSize.width)
        {
            if( mymap->JudgeMapNotEnd(visibleSize, true))
            {
                if(
                        hero->JudgePositona(visibleSize) //hero  in middle
                   )
                {
                    //下面是移动地图
                    mymap->MoveMap(hero,visibleSize, true);
                    break;
                }
            }
            //精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
            hero->setPosition(ccp(hero->getPosition().x+2,hero->getPosition().y)); //向右走
            CCLog("move right");
        }        
		break;
	case  2:
        //CCLog("move  %f   %f", hero->getPosition().x, hero->getPosition().y);
        hero->SetAnimationAdv("hero_run.plist","hero_run.png", "hero_run", 1, 8, rocker->rocketRun);
        if(hero->getPosition().y+2 + hero->GetHeroSprite()->getContentSize().height/2 > visibleSize.height)
        {
            break;
        }
        hero->setPosition(ccp(hero->getPosition().x, hero->getPosition().y+2));   //向上走
		break;
	case 3:
        //CCLog("move  %f   %f", hero->getPosition().x, hero->getPosition().y);
        hero->SetAnimationAdv("hero_run.plist","hero_run.png", "hero_run", 1, 8, rocker->rocketRun);
        if(hero->getPosition().x-2 - hero->GetHeroSprite()->getContentSize().width/2 > 0)
        {
            if( mymap->JudgeMapNotEnd(visibleSize, false))
            {
                if(
                        hero->JudgePositona(visibleSize) //hero  in middle
                   )
                {
                    //下面是移动地图
                    mymap->MoveMap(hero,visibleSize, false);
                    break;
                }
            }

            hero->setPosition(ccp(hero->getPosition().x-2,hero->getPosition().y));   //向左走
            CCLog("move left");
        }        
		break;
	case 4:
        //CCLog("move  %f   %f", hero->getPosition().x, hero->getPosition().y);
        hero->SetAnimationAdv("hero_run.plist","hero_run.png", "hero_run", 1, 8, rocker->rocketRun);
        if(hero->getPosition().y-2 - hero->GetHeroSprite()->getContentSize().height/2 < 0)
        {
            break;
        }
        hero->setPosition(ccp(hero->getPosition().x,hero->getPosition().y-2));   //向下走
		break;
	default:
		hero->StopAnimation();//停止所有动画和运动
		break;

    }
	if(btn->isTouch)
	{
		if(hero->IsAttack)//英雄没在攻击
			return;
        hero->AttackAnimation("hero_attack.plist","hero_attack.png","hero_attack",20,rocker->rocketRun);
		m_pProgressView->setCurrentProgress(m_pProgressView->getCurrentProgress()-10); //更改血量
	}
}
