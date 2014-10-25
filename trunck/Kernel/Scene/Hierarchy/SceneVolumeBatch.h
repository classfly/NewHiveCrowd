#pragma once
#include "SceneVolume.h"
namespace Ogre{ class SceneNode; }
namespace hiveCrowd
{
	namespace Kernel
	{
		class COctree;
		class COctreeSceneManager;
		class KERNEL_DLL_API CSceneVolumeBatch
		{
		public:
			explicit CSceneVolumeBatch(void);
			~CSceneVolumeBatch(void);
			
			void slice(size_t vLengthLevel, size_t vWidthLevel, size_t vHeightLevel);
			void scaleBatch(Ogre::Real vScale);
			void scaleBatch(const Ogre::Vector3& vScale);
			void findVolumes(const Ogre::SceneNode* vNode, Ogre::list<const CSceneVolume*>::type& voList) const;
			void findNodesIn(const Ogre::AxisAlignedBox& vBox, Ogre::list<const Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode = nullptr) const;
			void findNodesIn(const Ogre::Sphere& vSphere, Ogre::list<const Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode = nullptr) const;
			void findNodesIn(const Ogre::PlaneBoundedVolume& vVolume, Ogre::list<const Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode = nullptr) const;
		private:
			void __addNode(Ogre::SceneNode* vNode);
			void __addNode(Ogre::SceneNode* vNode, COctree* vOctree, size_t vDepth = 0);
			void __removeNode(Ogre::SceneNode* vNode);
			void __fetchVolumes(const Ogre::SceneNode* vNode, Ogre::list<CSceneVolume*>::type& voList) const;
			bool __clamp(void);
			void __rebuildBatch(size_t vNewLengthLevel, size_t vNewWidthLevel, size_t vNewHeightLevel);

			friend class COctreeSceneManager;
		private:
			size_t							  m_HierarchicalDepth;
			size_t							  m_LengthLevel, m_WidthLevel, m_HeightLevel;
			Ogre::Vector3					  m_LeftTop, m_RightBottom;
			Ogre::vector<CSceneVolume*>::type m_VolumeList;
		};
	}
}
