#include "Monster.h"
USING_NS_CC; 
Monster::Monster(void)
{
	IsRunning=false;//没在放动画
    MonsterDirecton=true;//向右运动
	Monster_name=NULL;
	IsAttack=false;
	Monster_xue=NULL;
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
	Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()+25, m_MonsterSprite->getPositionY()+50));//设置在怪物上头  
	//Monster_xue->setScale(2.2f);  
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

