#include "Monster.h"
#include <sys/time.h>
USING_NS_CC; 
Monster::Monster(void)
{
	IsRunning=false;//没在放动画
    MonsterDirecton=true;//向右运动
	Monster_name=NULL;
	IsAttack=false;
	Monster_xue=NULL;
	my_hero=NULL;//当前英雄
	my_map=NULL;//当前地图
	dis=10000;
}

Monster::~ Monster(void)
{

}
CCSprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}
void  Monster::InitMonsterSprite(char *name)
{
	Monster_name=name;
	this->m_MonsterSprite=CCSprite::create(name);
		m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
}
void Monster::InitMonsterSprite(char *name,char *xue_back,char* xue_fore)
{
	InitMonsterSprite(name);
	//设置怪物的血条 
	Monster_xue = new ProgressView();  
	if(MonsterDirecton)//因为怪物中心不在图片中心，所以只能根据怪物的脸朝向，设置血条的横坐标
		Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()+20, m_MonsterSprite->getPositionY()+50));//设置在怪物上头  
	else
		Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()-20, m_MonsterSprite->getPositionY()+50));  
	Monster_xue->setBackgroundTexture(xue_back);  
	Monster_xue->setForegroundTexture(xue_fore);  
	Monster_xue->setTotalProgress(300.0f);  
	Monster_xue->setCurrentProgress(300.0f); 
	this->addChild(Monster_xue);
}
void  Monster::SetAnimation(const char *name_each,unsigned int num,bool run_directon)
{
	if(MonsterDirecton!=run_directon)
	{   MonsterDirecton=run_directon;
	m_MonsterSprite->setFlipX(run_directon);
	}
	if(IsRunning||IsAttack)
		return;
	CCAnimation* animation = CCAnimation::create();  
	for( int i=1;i<=num;i++)  
	{  
		char szName[100] = {0};  
		sprintf(szName,"%s%d.png",name_each,i);  
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}  
	animation->setDelayPerUnit(2.8f / 14.0f);  
	animation->setRestoreOriginalFrame(true);  
	animation->setLoops(-1); //动画循环
	//将动画包装成一个动作
	CCAnimate* act=CCAnimate::create(animation);
	m_MonsterSprite->runAction(act);
	IsRunning=true;

}
//原地奔跑动画
void Monster::SetAnimationAdv(const char *name_plist,const char *name_png, const char * actNameInNamePng, unsigned int startIndex, unsigned int num,bool run_directon)
{
    if(MonsterDirecton!=run_directon)
    {
        MonsterDirecton=run_directon;
        m_MonsterSprite->setFlipX(run_directon);//trun the sprite
    }
    if(IsRunning)
    {
        return;
    }
    //将图片加载到精灵帧缓存池
   CCSpriteFrameCache *m_frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    m_frameCache->addSpriteFramesWithFile(name_plist,name_png);
    //用一个列表保存所有的CCSpriteFrameCache
    Vector<CCSpriteFrame*>  frameArray = Vector<CCSpriteFrame*>();
    unsigned int i;
    for(i=startIndex;i<=num;i++)
    {
        CCSpriteFrame* frame=m_frameCache->spriteFrameByName(CCString::createWithFormat("%s%d.png", actNameInNamePng, i)->getCString());
        frameArray.pushBack(frame);
    }
    //使用列表创建动画对象
    Animation* animation=Animation::createWithSpriteFrames(frameArray);
    if(MonsterDirecton!=run_directon)
    {   MonsterDirecton=run_directon;

    }
    animation->setLoops(-1);//表示无限循环播放
    animation->setDelayPerUnit(2.8f / 14.0f);//每两张图片的时间隔，图片数目越少，间隔最小就越小
    animation->setRestoreOriginalFrame(true);//动画播放结束后，回到初始帧

    //将动画包装成一个动作
    CCAnimate* act=CCAnimate::create(animation);


    m_MonsterSprite->runAction(act);
    IsRunning=true;


}

void  Monster::StopAnimation()
{
	if(!IsRunning)
		return;
	m_MonsterSprite->stopAllActions();//当前精灵停止所有动画
	//恢复精灵原来的初始化贴图 
    this->removeChild(m_MonsterSprite,true);//把原来的精灵删除掉
	m_MonsterSprite=CCSprite::create(Monster_name);//恢复精灵原来的贴图样子
	m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
	IsRunning=false;

	//存在血条
	if(Monster_xue!=NULL)
	{
		if(MonsterDirecton)//因为怪物中心不在图片中心，所以只能根据怪物的脸朝向，设置血条的横坐标
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()+20, m_MonsterSprite->getPositionY()+50));//设置在怪物上头  
		else
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()-20, m_MonsterSprite->getPositionY()+50)); 
	}
}
void Monster::AttackAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,bool run_directon)
{
    if(IsAttack)
        return;


    //将图片加载到精灵帧缓存池
   CCSpriteFrameCache *m_frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
   m_frameCache->addSpriteFramesWithFile(name_plist,name_png);
    Vector<CCSpriteFrame*>  frameArray = Vector<CCSpriteFrame*>();
    unsigned int i;
    for(i=1;i<=num;i++)
    {
        CCSpriteFrame* frame=m_frameCache->spriteFrameByName(CCString::createWithFormat("%s%d.png",name_each,i)->getCString());
        frameArray.pushBack(frame);
    }
    //使用列表创建动画对象
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(frameArray);
    if(MonsterDirecton!=run_directon)
    {   MonsterDirecton=run_directon;

    }
    animation->setLoops(1);//表示循环播放次
    animation->setDelayPerUnit(2.8f / 14.0f);//每两张图片的时间隔，图片数目越少，间隔最小就越小
	animation->setRestoreOriginalFrame(true); 
    //将动画包装成一个动作
    CCAnimate* act=CCAnimate::create(animation);
    //创建回调动作，攻击结束后调用AttackEnd()
    CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Monster::AttackEnd));
    //创建连续动作
   CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);
    IsAttack=true;
    m_MonsterSprite->runAction(attackact);

}
void Monster::AttackEnd()
{
	//恢复精灵原来的初始化贴图 
    this->removeChild(m_MonsterSprite,true);//把原来的精灵删除掉
	m_MonsterSprite=CCSprite::create(Monster_name);//恢复精灵原来的贴图样子
	m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
	IsAttack=false;
}


void Monster::FollowRun(CCNode* m_hero,CCNode* m_map)
{
	//得到两点x的距离,记得怪物的坐标要加上地图的
	float x = m_hero->getPositionX()-(this->getPositionX()+m_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的
	float y = m_hero->getPositionY()-(this->getPositionY()+m_map->getPositionY());

   //先计算怪物和英雄的距离
	dis = sqrt(pow(x,2) + pow(y,2));

	if(dis>=300)//当怪物与英雄距离超过300
		return;
	if(dis<=100)//在怪物攻击范围内，怪物停止移动
	{
		this->StopAnimation();//停止跑动
		JudegeAttack();//以一定的概率判断是是否出动攻击
		return;
	}

	if(x<-100)//判断怪物横坐标和英雄的距离
		{
			
			MonsterDirecton=true;
			m_MonsterSprite->setFlipX(MonsterDirecton);//设置方向
			if(IsAttack)
				return;
			 this->setPosition(this->getPositionX()-1,this->getPositionY());//怪物向英雄移动
             this->SetAnimationAdv("monster_run.plist","monster_run.png", "monster_run", 1, 6, MonsterDirecton);//播放动画

	}
	else if(x>100)
		{
			
			MonsterDirecton=false;
			m_MonsterSprite->setFlipX(MonsterDirecton);//设置方向
			if(IsAttack)
				return;
			this->setPosition(this->getPositionX()+1,this->getPositionY());
            this->SetAnimationAdv("monster_run.plist","monster_run.png", "monster_run", 1, 6, MonsterDirecton);//播放动画
    }
	else if(x<=100)//怪物橫坐標和英雄相差在100以内时，开始移动怪物纵坐标
	{

		if(m_hero->getPositionY()>this->getPositionY())
		{
			m_MonsterSprite->setFlipX(MonsterDirecton);//设置方向
			if(IsAttack)
				return;
			this->setPosition(this->getPositionX(),this->getPositionY()+1);
            this->SetAnimationAdv("monster_run.plist","monster_run.png", "monster_run", 1, 6, MonsterDirecton);//播放动画
		}
		else if(m_hero->getPositionY()<this->getPositionY())
		{
			m_MonsterSprite->setFlipX(MonsterDirecton);//设置方向
			if(IsAttack)
				return;
			this->setPosition(this->getPositionX(),this->getPositionY()-1);
            this->SetAnimationAdv("monster_run.plist","monster_run.png", "monster_run", 1, 6, MonsterDirecton);//播放动画
		}
	}

}
unsigned long long GetCurrentTime()
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  unsigned long long sec = tv.tv_sec;
  sec = sec * 1000;
  unsigned long long usec = tv.tv_usec;
  usec = usec / 1000;
  unsigned long long cur = sec + usec;
  return cur;
}

void Monster::JudegeAttack()
{
    srand((uint)GetCurrentTime());
	int x = rand()%100;
	if(x>98)
	{
        this->AttackAnimation("monster_attack.plist", "monster_attack.png", "monster_attack", 5,MonsterDirecton);
	}

}
void  Monster::MonsterSeeRun()
{
	if(dis<300)
		return;
	 this->SetAnimation("monster_run",6,MonsterDirecton);//播放动画
	 CCMoveBy *moveby1;
	 if(MonsterDirecton==true)
     moveby1=CCMoveBy::create(2,ccp(-100,0));
	 else
     moveby1=CCMoveBy::create(2,ccp(100,0));
	//创建回调动作，巡逻路线完后
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Monster::StopAnimation));
	//创建连续动作
	CCActionInterval* xunluo=CCSequence::create(moveby1,callFunc,NULL);
	this->runAction(xunluo);
}
//启动监听
void Monster::StartListen(CCNode* m_hero,CCNode* m_map)
{
	 my_hero=m_hero;
	 my_map=m_map;
	this->schedule(schedule_selector(Monster::updateMonster),3.0f);//每隔3秒计算距离
	this->scheduleUpdate();//英雄一旦进入可视范围，怪物追着英雄打
}
//监听函数,每隔3秒检测下
void Monster::updateMonster(float delta)
{
	//得到两点x的距离,记得怪物的坐标要加上地图的
	float x = my_hero->getPositionX()-(this->getPositionX()+my_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的
	float y = my_hero->getPositionY()-(this->getPositionY()+my_map->getPositionY());
	//先计算怪物和英雄的距离
	dis = sqrt(pow(x,2) + pow(y,2));
	if(dis>=300)
	{
		if(!IsRunning)
		MonsterSeeRun();
	}
}
void Monster::update(float delta)
{
	if(dis<300)///当英雄在它的可视范围内，不断追着英雄
	FollowRun(my_hero,my_map);
}


