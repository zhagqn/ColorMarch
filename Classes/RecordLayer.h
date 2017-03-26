//
//  RecordLayer.h
//  ColorMarch
//
//  Created by zhagqn on 2/3/15.
//
//

#ifndef __ColorMarch__RecordLayer__
#define __ColorMarch__RecordLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class RecordLayer : public Layer
{
private:
    Size visibleSize;
    int mode;
    
public:
    static RecordLayer* create(int mode);
    bool init(int mode);
    
    RecordLayer();
    ~RecordLayer();
    
    void addRecord();
    void hideMask(float dt);
};

#endif /* defined(__ColorMarch__RecordLayer__) */
