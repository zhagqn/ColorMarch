//
//  NewRecordLayer.h
//  ColorMarch
//
//  Created by zhagqn on 2/4/15.
//
//

#ifndef __ColorMarch__NewRecordLayer__
#define __ColorMarch__NewRecordLayer__

#include <stdio.h>
#include <cocos2d.h>
#include <cocos-ext.h>

USING_NS_CC;
USING_NS_CC_EXT;

class NewRecordLayer : public Layer, public EditBoxDelegate
{
private:
    Size visibleSize;
    
public:
    CREATE_FUNC(NewRecordLayer);
    virtual void onExit();
    virtual void editBoxEditingDidBegin(EditBox* editBox);

    virtual void editBoxEditingDidEnd(EditBox* editBox);

    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);

    virtual void editBoxReturn(EditBox* editBox);
    bool init();
};

#endif /* defined(__ColorMarch__NewRecordLayer__) */
