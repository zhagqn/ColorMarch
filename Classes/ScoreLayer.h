//
//  ScoreLayer.h
//  ColorMarch
//
//  Created by zhagqn on 11/1/14.
//
//

#ifndef __ColorMarch__ScoreLayer__
#define __ColorMarch__ScoreLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class ScoreLayer : public Layer
{
private:
    int score;
    LabelAtlas* scoreLabel;
    
public:
    CREATE_FUNC(ScoreLayer);
    
    ScoreLayer();
    ~ScoreLayer();
    virtual void onEnter();
    
    int updateScore();
    
    void removing(Action* action);
    
};
#endif /* defined(__ColorMarch__ScoreLayer__) */
