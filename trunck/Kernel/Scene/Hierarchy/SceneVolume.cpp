#include <OgreMovableObject.h>
#include "SceneVolume.h"
#include "Octree.h"
#include "OctreeNode.h"
#include "Common/CommonMirco.h"
using namespace hiveCrowd::Kernel;

CSceneVolume::CSceneVolume( const Ogre::Vector3& vLeftTop, const Ogre::Vector3& vRightBottom )
	: m_LeftTop(vLeftTop), m_RightBottom(vRightBottom), 
	  m_Octree(nullptr)
{
	m_HalfSize = 0.5 * (m_RightBottom - m_LeftTop);
}

CSceneVolume::~CSceneVolume( void )
{
	SAFE_DELETE(m_Octree);
}

void CSceneVolume::_updateVolume( void )
{
	// TODO:



}

void CSceneVolume::_addNode( Ogre::SceneNode* vNode )
{
	if (vNode == nullptr)
		return ;
	m_Octree->addNode(dynamic_cast<COctreeNode*>(vNode));
}

void CSceneVolume::_removeNode( Ogre::SceneNode* vNode )
{
	if (vNode == nullptr)
		return ;
	m_Octree->removeNode(dynamic_cast<COctreeNode*>(vNode));
}
