#pragma once
#include <OgreSceneNode.h>
#include "KernelExport.h"
namespace hiveCrowd
{
	namespace Kernel
	{
		class CSceneVolumeBatch;
		class CSceneEntity;
		class COctree;
		class KERNEL_DLL_API CSceneVolume
		{
		public:
			explicit CSceneVolume(const Ogre::Vector3& vLeftTop, const Ogre::Vector3& vRightBottom);
			virtual ~CSceneVolume(void);

			Ogre::Real size(void) const;
		protected:
			void _updateVolume(void);
			void _addNode(Ogre::SceneNode* vNode);
			void _removeNode(Ogre::SceneNode* vNode);

			friend class CSceneVolumeBatch;
		private:
			Ogre::Vector3						  m_LeftTop, m_RightBottom;
			Ogre::Vector3						  m_HalfSize;
			Ogre::list<const CSceneEntity*>::type m_EntityList;
			COctree*							  m_Octree;
		};
	}
}
