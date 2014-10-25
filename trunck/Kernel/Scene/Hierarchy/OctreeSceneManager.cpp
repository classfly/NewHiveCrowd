#include <OgreException.h>
#include "OctreeSceneManager.h"
#include "OctreeNode.h"
#include "Octree.h"
#include "OctreeCamera.h"
#include "SceneVolumeBatch.h"
using namespace hiveCrowd::Kernel;

COctreeSceneManager::COctreeSceneManager(const Ogre::String& vName)
	: Ogre::SceneManager(vName)
{

}

COctreeSceneManager::~COctreeSceneManager(void)
{

}

Ogre::SceneNode* COctreeSceneManager::createSceneNodeImpl(void)
{
	return OGRE_NEW COctreeNode(this);
}

Ogre::SceneNode* COctreeSceneManager::createSceneNodeImpl(const Ogre::String& vName)
{
	return OGRE_NEW COctreeNode(this, vName);
}

void COctreeSceneManager::destroySceneNode(const Ogre::String& vName)
{
	try
	{
		COctreeNode* TargetNode = dynamic_cast<COctreeNode*>(getSceneNode(vName));
		if (TargetNode != nullptr)
			_removeNode(TargetNode);
		Ogre::SceneManager::destroySceneNode(TargetNode);
	}
	catch (Ogre::Exception* vException)
	{
		
	}
}

Ogre::Camera* COctreeSceneManager::createCamera(const Ogre::String& vName)
{
	if (mCameras.find(vName) != mCameras.end())
		OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, "A camera with the name " + vName + " already exists", "CDynamicSceneManager::createCamera()");
	Ogre::Camera* NewCamera = OGRE_NEW COctreeCamera(vName, this);
	mCameras.insert(CameraList::value_type(vName, NewCamera));
	mCamVisibleObjectsMap[NewCamera] = Ogre::VisibleObjectsBoundsInfo();

	return NewCamera;
}

void COctreeSceneManager::findNodesIn(const Ogre::AxisAlignedBox& vBox, Ogre::list<Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode /*= nullptr*/)
{

}

void COctreeSceneManager::findNodesIn(const Ogre::Sphere& vSphere, Ogre::list<Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode /*= nullptr*/)
{

}

void COctreeSceneManager::findNodesIn(const Ogre::PlaneBoundedVolume& vVolume, Ogre::list<Ogre::SceneNode*>::type& voList, const Ogre::SceneNode* vExcludeNode /*= nullptr*/)
{

}

void COctreeSceneManager::_addNode(Ogre::SceneNode* vNode)
{
	boost::mutex::scoped_lock Lock(m_Mutex);
	if (vNode == nullptr)
		return ;

	m_VolumeBatch->__addNode(vNode);
}

void COctreeSceneManager::_addNode(Ogre::SceneNode* vNode, COctree* vOctree, size_t vDepth /*= 0*/)
{
	boost::mutex::scoped_lock Lock(m_Mutex);
	if (vNode == nullptr)
		return ;

	m_VolumeBatch->__addNode(vNode, vOctree, vDepth);
}

void COctreeSceneManager::_removeNode(Ogre::SceneNode* vNode)
{
	boost::mutex::scoped_lock Lock(m_Mutex);
	if (vNode == nullptr)
		return ;

	m_VolumeBatch->__removeNode(vNode);
}

void COctreeSceneManager::_updateNode(Ogre::SceneNode* vNode)
{
	COctreeNode* OctreeNode = dynamic_cast<COctreeNode*>(vNode);
	const COctree* Octree   = OctreeNode->getOctant();
	if (Octree == nullptr)
	{
		if (!OctreeNode->isInBox(m_Octree->getAABB()))
			_addNode(vNode);
		else
			_addNode(vNode, m_Octree);

		return ;
	}

	if (!OctreeNode->isInBox(Octree->getAABB()))
	{
		_removeNode(vNode);
		if (!OctreeNode->isInBox(m_Octree->getAABB()))
			_addNode(vNode);
		else
			_addNode(vNode, m_Octree);
	}
}
