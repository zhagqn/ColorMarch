//
//  CoverLayer.h
//  ColorMarch
//
//  Created by zhagqn on 2/9/15.
//
//

#ifndef __ColorMarch__CoverLayer__
#define __ColorMarch__CoverLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class CoverLayer : public Layer
{
private:
    Size visibleSize;
    
public:
    CREATE_FUNC(CoverLayer);
    bool init();
};


#endif /* defined(__ColorMarch__CoverLayer__) */
