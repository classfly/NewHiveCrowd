#pragma once
#include "KernelExport.h"
#include "MovableObject.h"
namespace Ogre{ class AnimationStateSet; }
namespace hiveCrowd
{
	namespace Kernel
	{
		class CScene;
		class KERNEL_DLL_API CEntity : public CMovableObject
		{
		public:
			CEntity(void);
			CEntity(const Ogre::String& vName, const Ogre::String& vGroup);
			virtual ~CEntity(void){}


		protected:
			void					_fadeAnimations(Ogre::Real vDeltaTime);
			virtual CMovableObject* _clone(const Ogre::String& vName) override;
		protected:
			CScene*					 m_Scene;
			Ogre::AnimationStateSet* m_AnimationStateSet;
			Ogre::vector<bool>::type m_AnimationFadeInGroup;
			Ogre::vector<bool>::type m_AnimationFadeOutGroup;
		};

		class KERNEL_DLL_API CEntityFactory : public CMovableObjectFactory
		{
			CEntityFactory(void){}
			virtual ~CEntityFactory(void){}
		protected:
			virtual Common::CObject* _createProductImpl(const Ogre::String& vName) const override;
			virtual Common::CObject* _createProductImpl(const char* vName)		   const override;
		};
	}
}
