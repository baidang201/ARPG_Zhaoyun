#ifndef __MAP_H__
#define __MAP_H__
#include "cocos2d.h"
USING_NS_CC; 
class MyMap:public CCNode
{
public:
     MyMap();
    ~MyMap();
	//初始化地图,window_sizeo为控制台大小
    void InitMap(const char *map_name,const CCSize &window_size);
	//根据精灵的位置移动地图，visibleSize为当前窗口的大小
    void MoveMap(CCNode *hero,CCSize visibleSize, bool directRight);
	//判断地图是否到达边缘
    bool JudgeMapNotEnd(CCSize visibleSize, bool directRight);
	//virtual void update(float delta);
    CREATE_FUNC(MyMap);
	
private:
	CCSprite *m_map;//地图精灵

};
#endif // __MAP_H__
