#pragma once
#include <OgreInstancedEntity.h>
#include "MovableObject.h"
namespace hiveCrowd
{
	namespace Kernel
	{
		class KERNEL_DLL_API CInstanceEntity : public CMovableObject
		{
		public:
			CInstanceEntity(void);
			CInstanceEntity(const char* vName, const Ogre::String& vGroup = "");
			CInstanceEntity(const Ogre::String& vName, const Ogre::String& vGroup = "");
			virtual ~CInstanceEntity(void);

		private:
			Ogre::InstancedEntity* m_Entity;
		};

		class KERNEL_DLL_API CInstanceEntityFactory : public CMovableObjectFactory
		{
		public:
			CInstanceEntityFactory(void){}
			virtual ~CInstanceEntityFactory(){}
		protected:
			virtual Common::CObject* _createProductImpl(const Ogre::String& vName) const override;
			virtual Common::CObject* _createProductImpl(const char* vName)		   const override;
		};
	}
}
