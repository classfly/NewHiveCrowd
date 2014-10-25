#include <OgreAnimation.h>
#include <OgreResourceGroupManager.h>
#include <boost/algorithm/string.hpp>
#include "Entity.h"
#include "Scene.h"
using namespace hiveCrowd::Kernel;

CEntity::CEntity(void) : CMovableObject()
{
	m_Type = typeid(*this).name();
}

CEntity::CEntity(const Ogre::String& vName, const Ogre::String& vGroup) : CMovableObject(vName)
{
	m_Type = typeid(*this).name();
}

void CEntity::_fadeAnimations(Ogre::Real vDeltaTime)
{
	Ogre::AnimationStateIterator AnimationItr(m_AnimationStateSet->getAnimationStateIterator());
	size_t AnimationIndex = 0;
	while (AnimationItr.hasMoreElements())
	{
		Ogre::AnimationState* AnimationState(AnimationItr.getNext());
		Ogre::Real NewAnimationWeight(0.0f);
		if (m_AnimationFadeInGroup[AnimationIndex])
		{
			NewAnimationWeight = AnimationState->getWeight() + vDeltaTime;
			AnimationState->setWeight(Ogre::Math::Clamp<Ogre::Real>(NewAnimationWeight, 0.0f, 1.0f));
			if (NewAnimationWeight > 1.0f)
				m_AnimationFadeInGroup[AnimationIndex] = true;
		}
		else if (m_AnimationFadeOutGroup[AnimationIndex])
		{
			NewAnimationWeight = AnimationState->getWeight() - vDeltaTime;
			AnimationState->setWeight(Ogre::Math::Clamp<Ogre::Real>(NewAnimationWeight, 0.0f, 1.0f));
			if (NewAnimationWeight < 0.0f)
			{
				AnimationState->setEnabled(false);
				m_AnimationFadeOutGroup[AnimationIndex] = false;
			}
		}
	}
}

CMovableObject* CEntity::_clone( const Ogre::String& vName )
{
	return new CMovableObject(vName);
}

hiveCrowd::Common::CObject* CEntityFactory::_createProductImpl( const Ogre::String& vName ) const 
{
	return new CEntity(vName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
}

hiveCrowd::Common::CObject* CEntityFactory::_createProductImpl( const char* vName ) const 
{
	return new CEntity(vName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
}
