#include "Octree.h"
#include "OctreeNode.h"
#include "Common/CommonMirco.h"
using namespace hiveCrowd::Kernel;

size_t COctree::OCTREE_CHILREN_COUNT = 8;

COctree::COctree( COctree* vParent )
	: m_NumNodes(0), 
	  m_Parent(vParent), 
	  m_HalfSize(Ogre::Vector3::ZERO)
{
	for (size_t AxisXItr=0 ; AxisXItr<2 ; ++AxisXItr)
	{
		for (size_t AxisYItr=0 ; AxisYItr<2 ; ++AxisYItr)
		{
			for (size_t AxisZItr=0 ; AxisZItr<2 ; ++AxisZItr)
			{
				m_Children[AxisXItr][AxisYItr][AxisZItr] = nullptr;
			}
		}
	}
}

COctree::~COctree( void )
{
	for (size_t AxisXItr=0 ; AxisXItr<2 ; ++AxisXItr)
	{
		for (size_t AxisYItr=0 ; AxisYItr<2 ; ++AxisYItr)
		{
			for (size_t AxisZItr=0 ; AxisZItr<2 ; ++AxisZItr)
			{
				SAFE_DELETE(m_Children[AxisXItr][AxisYItr][AxisZItr]);
			}
		}
	}

	for (Ogre::list<COctreeNode*>::iterator itr=m_NodeList.begin() ; itr!=m_NodeList.end() ; ++itr)
		SAFE_DELETE((*itr));
	m_NodeList.clear();
}

void COctree::addNode( COctreeNode* vNode)
{
	if (vNode == nullptr)
		return ;

	__addNode(vNode, this);
}

void COctree::__addNode( COctreeNode* vNode, COctree* vOctree )
{
	const Ogre::AxisAlignedBox& Box = vNode->_getWorldAABB();
	if (vOctree->__isTwiceSize(Box))
	{
		size_t AxisX(0), AxisY(0), AxisZ(0);
		findChildIndex(Box, AxisX, AxisY, AxisZ);
		COctree* Child = vOctree->m_Children[AxisX][AxisY][AxisZ];
		if (Child == nullptr)
		{
			Child = OGRE_NEW COctree(this);
			const Ogre::Vector3& OctantMinCoord = vOctree->m_Box.getMinimum();
			const Ogre::Vector3& OctantMaxCoord = vOctree->m_Box.getMaximum();
			Ogre::Vector3 MinCoord, MaxCoord;
			
			if (AxisX == 0)
			{
				MinCoord.x = OctantMinCoord.x;
				MaxCoord.x = 0.5 * (OctantMinCoord.x + OctantMaxCoord.x);
			}
			else
			{
				MinCoord.x = 0.5 * (OctantMaxCoord.x + OctantMaxCoord.x);
				MaxCoord.x = OctantMaxCoord.x;
			}

			if (AxisY == 0)
			{
				MinCoord.y = OctantMinCoord.y;
				MaxCoord.y = 0.5 * (OctantMinCoord.y + OctantMaxCoord.y);
			}
			else
			{
				MinCoord.y = 0.5 * (OctantMinCoord.y + OctantMaxCoord.y);
				MaxCoord.y = OctantMaxCoord.y;
			}

			if (AxisZ == 0)
			{
				MinCoord.z = OctantMinCoord.z;
				MaxCoord.z = 0.5 * (OctantMinCoord.z + OctantMaxCoord.z);
			}
			else
			{
				MinCoord.z = 0.5 * (OctantMinCoord.z + OctantMaxCoord.z);
				MaxCoord.z = OctantMaxCoord.z;
			}

			Child->m_Box.setExtents(MinCoord, MaxCoord);
			Child->m_HalfSize = 0.5 * (MaxCoord - MinCoord);
		}

		__addNode(vNode, Child);
	}
	else
		__addNode(vNode);
}

void COctree::__addNode(COctreeNode* vNode)
{
	m_NodeList.push_back(vNode);
	vNode->setOctant(this);
	__increaseOverallNodeCount();
}

void COctree::removeNode( COctreeNode* vNode )
{
	if (vNode == nullptr)
		return ;

	m_NodeList.erase(std::find(m_NodeList.begin(), m_NodeList.end(), vNode));
	vNode->setOctant(nullptr);
	__decreaseOverallNodeCount();
}

void COctree::findChildIndex( const Ogre::AxisAlignedBox& vBox, size_t& voAxisX, size_t& voAxisY, size_t& voAxisZ ) const
{
	const Ogre::Vector3 CurrentCenter = m_Box.getMaximum().midPoint(m_Box.getMinimum());
	const Ogre::Vector3 NewCenter	  = vBox.getMaximum().midPoint(vBox.getMinimum());
	
	voAxisX = (NewCenter.x > CurrentCenter.x ? 1 : 0);
	voAxisY = (NewCenter.y > CurrentCenter.y ? 1 : 0);
	voAxisZ = (NewCenter.z > CurrentCenter.z ? 1 : 0);
}

bool COctree::__isTwiceSize( const Ogre::AxisAlignedBox& vBox ) const
{
	if (vBox.isInfinite())
		return false;

	const Ogre::Vector3 HalfBoxSize = m_Box.getHalfSize();
	const Ogre::Vector3 BoxSize		= vBox.getHalfSize();

	return (HalfBoxSize.x >= BoxSize.x && HalfBoxSize.y >= BoxSize.y && HalfBoxSize.z >= BoxSize.z);
}
