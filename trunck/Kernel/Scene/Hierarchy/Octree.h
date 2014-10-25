#pragma once
#include <OgreAxisAlignedBox.h>
#include "KernelExport.h"
namespace hiveCrowd
{
	namespace Kernel
	{
		class COctreeNode;
		class KERNEL_DLL_API COctree : public Ogre::NodeAlloc
		{
		public:
			explicit COctree(COctree* vParent);
			~COctree(void);

			void						addNode(COctreeNode* vNode);
			void						removeNode(COctreeNode* vNode);
			void						findChildIndex(const Ogre::AxisAlignedBox& vBox, size_t& voAxisX, size_t& voAxisY, size_t& voAxisZ) const;
			const Ogre::AxisAlignedBox& getAABB(void) const{ return m_Box; }
			static size_t OCTREE_CHILREN_COUNT;
		private:
			void __addNode(COctreeNode* vNode);
			void __addNode(COctreeNode* vNode, COctree* vOctree);
			inline void __increaseOverallNodeCount(void)
			{
				m_NumNodes++;
				if (m_Parent)
					m_Parent->__increaseOverallNodeCount();
			}
			inline void __decreaseOverallNodeCount(void)
			{
				m_NumNodes--;
				if (m_Parent)
					m_Parent->__decreaseOverallNodeCount();
			}
			bool __isTwiceSize(const Ogre::AxisAlignedBox& vBox) const;
		private:
			size_t						   m_NumNodes;
			COctree*					   m_Parent;
			COctree*					   m_Children[2][2][2];
			Ogre::list<COctreeNode*>::type m_NodeList;
			Ogre::Vector3				   m_HalfSize;
			Ogre::AxisAlignedBox		   m_Box;
		};
	}
}
