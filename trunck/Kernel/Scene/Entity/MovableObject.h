#pragma once
#include <OgreMovableObject.h>
#include <OgreResourceGroupManager.h>
#include "Common/Object.h"
#include "Common/ObjectFactory.h"
#include "Common/CommonMirco.h"
#include "KernelExport.h"
namespace hiveCrowd
{
	namespace Kernel
	{
		class CMovableObjectFactory;
		class KERNEL_DLL_API CMovableObject : public Common::CObject
		{
		public:
			CMovableObject(void);
			CMovableObject(const char* vName, const Ogre::String& vGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			CMovableObject(const Ogre::String& vName, const Ogre::String& vGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			virtual ~CMovableObject(void);

			const Ogre::String& getGroup(void) const{ return m_Group; }
			size_t				getTypeFlag(void) const;
		protected:
			virtual CMovableObject* _clone(const Ogre::String& vName);
			virtual void			_update(Ogre::Real vDeltaTime);
		protected:
			Ogre::String		   m_Group;
			Ogre::SceneNode*	   m_SceneNode;
			Ogre::MovableObject*   m_MovableObject;
			CMovableObjectFactory* m_Creator;
		};

		class KERNEL_DLL_API CMovableObjectFactory : public Common::CObjectFactory<CMovableObject>
		{
		public:
			CMovableObjectFactory(void){}
			virtual ~CMovableObjectFactory(void){}

			void   notifyTypeFlag(size_t vTypeFlag){ m_TypeFlag = vTypeFlag; }
			size_t getTypeFlag(void) const{ return m_TypeFlag; }
		protected:
			virtual Common::CObject* _createProductImpl(const Ogre::String& vName) const override = 0;
			virtual Common::CObject* _createProductImpl(const char* vName)		   const override = 0;
		protected:
			size_t m_TypeFlag;
		};
	}
}
