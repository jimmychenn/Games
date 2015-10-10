#include "InputManager.h"
#include <SDL/SDL.h>

void InputManager::HandleKeyPressed(int key)
{
    auto iterAction = mKeyToActionMap.find(key);
    if( iterAction != mKeyToActionMap.end() )
    {
        if(iterAction->second->mPressedDelegate != nullptr)
        {
            iterAction->second->mPressedDelegate->Execute();
        }
    }
    
    auto iterAxis = mKeyToAxisMap.find(key);
    if( iterAxis != mKeyToAxisMap.end() )
    {
        auto AxisMapPtr = iterAxis->second;
        if(AxisMapPtr->mDelegate != nullptr)
        {
            if(AxisMapPtr->mPositiveKey == key)
            {
                AxisMapPtr->mValue += 1.0f;
            }
            else if(AxisMapPtr->mNegativeKey == key)
            {
                AxisMapPtr->mValue -= 1.0f;
            }
            AxisMapPtr->mDelegate->Execute(AxisMapPtr->mValue);
        }
    }
}

void InputManager::HandleKeyReleased(int key)
{
    auto iterAction = mKeyToActionMap.find(key);
    if( iterAction != mKeyToActionMap.end())
    {
        if( iterAction->second->mReleasedDelegate != nullptr)
        {
            iterAction->second->mReleasedDelegate->Execute();
        }
    }
    
    auto iterAxis = mKeyToAxisMap.find(key);
    if( iterAxis != mKeyToAxisMap.end() )
    {
        auto AxisMapPtr = iterAxis->second;
        if(AxisMapPtr->mDelegate != nullptr)
        {
            if( iterAxis->second->mPositiveKey == key)
            {
                AxisMapPtr->mValue -= 1.0f;
            }
            else if (iterAxis->second->mNegativeKey == key)
            {
                AxisMapPtr->mValue += 1.0f;
            }
            AxisMapPtr->mDelegate->Execute(AxisMapPtr->mValue);
        }
    }
}

void InputManager::AddActionMapping(const std::string& name, int key)
{
    ActionMappingPtr ptr = std::make_shared<ActionMapping>();
    ptr->mKey = key;
    ptr->mName = name;
    mNameToActionMap.emplace(name,ptr);
    mKeyToActionMap.emplace(key,ptr);
}

void InputManager::AddAxisMapping(const std::string& name, int positiveKey, int negativeKey)
{
    AxisMappingPtr ptr = std::make_shared<AxisMapping>();
    ptr->mName = name;
    ptr->mPositiveKey = positiveKey;
    ptr->mNegativeKey = negativeKey;
    ptr->mValue = 0.0f;
    mNameToAxisMap.emplace(name,ptr);
    mKeyToAxisMap.emplace(positiveKey,ptr);
    mKeyToAxisMap.emplace(negativeKey,ptr);
}

int InputManager::GetMousexPos()
{
    SDL_GetMouseState(&xpos, &ypos);
    return xpos;
}
int InputManager::GetMouseyPos()
{
    SDL_GetMouseState(&xpos, &ypos);
    return ypos;
}

void InputManager::BindActionInternal(const std::string& name, InputEvent event, ActionDelegatePtr delegate)
{
    auto iter = mNameToActionMap.find(name);
    if ( iter != mNameToActionMap.end() )
    {
        if(event == IE_Pressed)
        {
            iter->second->mPressedDelegate = delegate;
        }
        else if(event == IE_Released)
        {
            iter->second->mReleasedDelegate = delegate;
        }
    }
}

void InputManager::BindAxisInternal(const std::string& name, AxisDelegatePtr delegate)
{
    auto iter = mNameToAxisMap.find(name);
    if ( iter != mNameToAxisMap.end() )
    {
        iter->second->mDelegate = delegate;
    }
}
