#include <OgreSceneNode.h>
#include "SceneVolumeBatch.h"
#include "Common/CommonMirco.h"
using namespace hiveCrowd::Kernel;

CSceneVolumeBatch::CSceneVolumeBatch(void)
{

}

CSceneVolumeBatch::~CSceneVolumeBatch(void)
{

}

void CSceneVolumeBatch::slice( size_t vLengthLevel, size_t vWidthLevel, size_t vHeightLevel )
{
	m_LengthLevel = vLengthLevel;
	m_WidthLevel  = vWidthLevel;
	m_HeightLevel = vHeightLevel;
	__rebuildBatch(m_LengthLevel, m_WidthLevel, m_HeightLevel);
}

void CSceneVolumeBatch::scaleBatch( Ogre::Real vScale )
{
	m_LengthLevel *= vScale;
	m_WidthLevel  *= vScale;
	m_HeightLevel *= vScale;
	__rebuildBatch(m_LengthLevel, m_WidthLevel, m_HeightLevel);
}

void CSceneVolumeBatch::scaleBatch( const Ogre::Vector3& vScale )
{
	m_LengthLevel *= vScale.x;
	m_WidthLevel  *= vScale.z;
	m_HeightLevel *= vScale.y;
	__rebuildBatch(m_LengthLevel, m_WidthLevel, m_HeightLevel);
} 

void CSceneVolumeBatch::findVolumes(const Ogre::SceneNode* vNode, Ogre::list<const CSceneVolume*>::type& voList) const
{

}

void CSceneVolumeBatch::findNodesIn(const Ogre::AxisAlignedBox& vBox, Ogre::list<const Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode /*= nullptr*/) const
{

}

void CSceneVolumeBatch::findNodesIn(const Ogre::Sphere& vSphere, Ogre::list<const Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode /*= nullptr*/) const
{

}

void CSceneVolumeBatch::findNodesIn(const Ogre::PlaneBoundedVolume& vVolume, Ogre::list<const Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode /*= nullptr*/) const
{

}

void CSceneVolumeBatch::__addNode(Ogre::SceneNode* vNode)
{
	if (vNode == nullptr)
		return ;

	Ogre::list<CSceneVolume*>::type VolumeList;
	__fetchVolumes(vNode, VolumeList);
	for (Ogre::list<CSceneVolume*>::iterator itr=VolumeList.begin() ; itr != VolumeList.end(); ++itr)
		(*itr)->_addNode(vNode);
}

void CSceneVolumeBatch::__addNode(Ogre::SceneNode* vNode, COctree* vOctree, size_t vDepth /*= 0*/)
{

}

void CSceneVolumeBatch::__removeNode(Ogre::SceneNode* vNode)
{
	if (vNode == nullptr)
		return ;

	Ogre::list<CSceneVolume*>::type VolumeList;
	__fetchVolumes(vNode, VolumeList);
	for (Ogre::list<CSceneVolume*>::iterator itr=VolumeList.begin() ; itr != VolumeList.end() ; ++itr)
		(*itr)->_removeNode(vNode);
}

void CSceneVolumeBatch::__fetchVolumes(const Ogre::SceneNode* vNode, Ogre::list<CSceneVolume*>::type& voList) const
{
	if (vNode == nullptr)
		return ;
	// TODO:


}

void CSceneVolumeBatch::__rebuildBatch( size_t vNewLengthLevel, size_t vNewWidthLevel, size_t vNewHeightLevel )
{
	volatile size_t VolumeCount = m_LengthLevel * m_WidthLevel * m_HeightLevel;
	m_LengthLevel				= vNewHeightLevel;
	m_WidthLevel				= vNewWidthLevel;
	m_HeightLevel				= vNewHeightLevel;
	if (__clamp())
	{
		for (size_t i=0 ; i!=VolumeCount ; ++i)
			SAFE_DELETE((m_VolumeList[i]));
		m_VolumeList.clear();
		VolumeCount = m_LengthLevel * m_WidthLevel * m_HeightLevel;
		m_VolumeList.resize(VolumeCount);
		// TODO: Update Scene Volume !!!
		for (size_t i=0 ; i<VolumeCount ; ++i)
			m_VolumeList[i]->_updateVolume();
	}
}

bool CSceneVolumeBatch::__clamp( void )
{
	size_t VolumeCount			= m_LengthLevel * m_WidthLevel * m_HeightLevel;
	size_t NewHierarchicalDepth = (size_t)(logf(VolumeCount) / logf(8));
	bool Result					= (NewHierarchicalDepth != m_HierarchicalDepth);
	// TODO: Scale (length, width, height)

	return Result;
}
