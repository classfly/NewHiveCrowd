#include <OgreRenderQueue.h>
#include "OctreeNode.h"
#include "OctreeSceneManager.h"
using namespace hiveCrowd::Kernel;

COctreeNode::COctreeNode( Ogre::SceneManager* vCreator )
	: Ogre::SceneNode(vCreator)
{

}

COctreeNode::COctreeNode( Ogre::SceneManager* vCreator, const Ogre::String& vName )
	: Ogre::SceneNode(vCreator, vName)
{

}

COctreeNode::~COctreeNode( void )
{
	// TODO:


}

Ogre::Node* COctreeNode::removeChild( Ogre::Node* vChild )
{
	COctreeNode* OctreeNode = dynamic_cast<COctreeNode*>(Ogre::SceneNode::removeChild(vChild));
	OctreeNode->removeAllChildren();

	return OctreeNode;
}

Ogre::Node* COctreeNode::removeChild( unsigned short vIndex )
{
	COctreeNode* OctreeNode = dynamic_cast<COctreeNode*>(Ogre::SceneNode::removeChild(vIndex));
	OctreeNode->removeAllChildren();

	return OctreeNode;
}

Ogre::Node* COctreeNode::removeChild( const Ogre::String& vName )
{
	COctreeNode* OctreeNode = dynamic_cast<COctreeNode*>(Ogre::SceneNode::removeChild(vName));
	OctreeNode->removeAllChildren();

	return OctreeNode;
}

void COctreeNode::removeAllChildren( void )
{
	Ogre::SceneNode::ChildNodeMap::iterator itr(mChildren.begin()), end(mChildren.end());
	while (itr != end)
	{
		COctreeNode* OctreeNode = dynamic_cast<COctreeNode*>(itr->second);
		OctreeNode->removeAllChildren();
		OctreeNode->setParent(nullptr);

		++itr;
	}
	mChildren.clear();
	mChildrenToUpdate.clear();
}

void COctreeNode::__updateBounds( void )
{
	m_LocalAABB.setNull();
	mWorldAABB.setNull();
	Ogre::SceneNode::ObjectMap::iterator itr(mObjectsByName.begin()), end(mObjectsByName.end());
	while (itr != end)
	{
		m_LocalAABB.merge(itr->second->getBoundingBox());
		mWorldAABB.merge(itr->second->getWorldBoundingBox());
	}

	if (!mWorldAABB.isNull() && mIsInSceneGraph)
		dynamic_cast<COctreeSceneManager*>(mCreator)->_updateNode(this);
}

void COctreeNode::__removeNodeAndChildren( void )
{
	dynamic_cast<COctreeSceneManager*>(mCreator)->_removeNode(this);
	Ogre::SceneNode::ChildNodeMap::iterator itr(mChildren.begin()), end(mChildren.end());
	while (itr != end)
	{
		dynamic_cast<COctreeNode*>(itr->second)->__removeNodeAndChildren();

		++itr;
	}
}

bool COctreeNode::isInBox( const Ogre::AxisAlignedBox& vBox )
{
	if (!mIsInSceneGraph || vBox.isNull())
		return false;
	if (vBox.isInfinite())
		return false;

	const Ogre::Vector3 CenterPos = mWorldAABB.getMaximum().midPoint(mWorldAABB.getMinimum());
	const Ogre::Vector3 MinCood   = vBox.getMinimum();
	const Ogre::Vector3 MaxCoord  = vBox.getMaximum();
	bool PreFlag				  = (MaxCoord > CenterPos && MinCood < CenterPos);
	if (!PreFlag)
		return false;

	const Ogre::Vector3 NodeSize   = mWorldAABB.getMaximum() - mWorldAABB.getMinimum();
	const Ogre::Vector3 OctreeSize = MaxCoord - MinCood;

	return (NodeSize < OctreeSize);
}

void COctreeNode::__addToRenderQueue( Ogre::Camera* vCamera, Ogre::RenderQueue* vRenderQueue, bool vShadowCasterFlag, Ogre::VisibleObjectsBoundsInfo* vVisibleBoundsInfo )
{
	Ogre::SceneNode::ObjectMap::iterator itr = mObjectsByName.begin();
	while (itr != mObjectsByName.end())
	{
		Ogre::MovableObject* MovableObject = itr->second;
		vRenderQueue->processVisibleObject(MovableObject, vCamera, vShadowCasterFlag, vVisibleBoundsInfo);

		++itr;
	}
}
