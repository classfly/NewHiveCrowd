#pragma once
#include <OgreSceneManager.h>
#include <boost/thread/mutex.hpp>
#include "KernelExport.h"
namespace hiveCrowd
{
	namespace Kernel
	{
		class COctreeNode;
		class COctree;
		class CSceneVolumeBatch;
		class KERNEL_DLL_API COctreeSceneManager : Ogre::SceneManager
		{
		public:
			explicit COctreeSceneManager(const Ogre::String& vName);
			virtual ~COctreeSceneManager(void);

			Ogre::SceneNode* createSceneNodeImpl(void)						override;
			Ogre::SceneNode* createSceneNodeImpl(const Ogre::String& vName) override;
			void			 destroySceneNode(const Ogre::String& vName)	override;
			Ogre::Camera*	 createCamera(const Ogre::String& vName)		override;
			void			 findNodesIn(const Ogre::AxisAlignedBox& vBox, Ogre::list<Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode = nullptr);
			void			 findNodesIn(const Ogre::Sphere& vSphere, Ogre::list<Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode = nullptr);
			void			 findNodesIn(const Ogre::PlaneBoundedVolume& vVolume, Ogre::list<Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode = nullptr);
		protected:
			void _addNode(Ogre::SceneNode* vNode);
			void _addNode(Ogre::SceneNode* vNode, COctree* vOctree, size_t vDepth = 0);
			void _removeNode(Ogre::SceneNode* vNode);
			void _updateNode(Ogre::SceneNode* vNode);
		protected:
			boost::mutex       m_Mutex;
			COctree*		   m_Octree;
			CSceneVolumeBatch* m_VolumeBatch;

			friend class COctreeNode;
		};
	}
}
