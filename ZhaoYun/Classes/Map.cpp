#include "Map.h"
MyMap::MyMap():m_map(NULL)
{

}
MyMap::~MyMap()
{

}
void MyMap::InitMap(const char *map_name,const CCSize &window_size)
{
	this->m_map=CCSprite::create(map_name);
	m_map->setAnchorPoint(ccp(0,0));//设置锚点
	this->setAnchorPoint(ccp(0,0));//设置锚点
	this->addChild(m_map);



}
void MyMap::MoveMap(CCNode *hero,CCSize visibleSize, bool directRight)//
{
	if(hero->getPositionX()==visibleSize.width/2)//精灵运动到中间，地图才移动
	{
        if( directRight )
        {
            if(this->getPositionX()!=-(m_map->getContentSize().width-visibleSize.width))//防止地图右边运动后超出边缘
                this->setPosition(this->getPositionX()-1,this->getPositionY());
        }
        else
        {
            if(this->getPositionX()!= 0)//防止地图左边运动后超出边缘
                this->setPosition(this->getPositionX()+1,this->getPositionY());
        }
	}
}

bool MyMap::JudgeMapNotEnd(CCSize visibleSize, bool directRight)
{   
    if(this->getPositionX() == -(m_map->getContentSize().width-visibleSize.width)  && directRight)//move right 地图已经移动到达边缘
        return false;
    else if(this->getPositionX() == 0 && !directRight)//move left 地图已经移动到达边缘
        return false;
    else
        return true;
}

