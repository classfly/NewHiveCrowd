#include "OctreeCamera.h"
using namespace hiveCrowd::Kernel;

COctreeCamera::COctreeCamera(const Ogre::String& vName, Ogre::SceneManager* vCreator)
	: Ogre::Camera(vName, vCreator)
{

}

COctreeCamera::~COctreeCamera(void)
{

}

COctreeCamera::VISIBILITY_FLAG COctreeCamera::getVisibility(const Ogre::AxisAlignedBox& vBox) const
{
	return NONE;
}
