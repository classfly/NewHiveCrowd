#include "MovableObject.h"
using namespace hiveCrowd::Kernel;

CMovableObject::CMovableObject( void )
{

}

CMovableObject::CMovableObject( const Ogre::String& vName, const Ogre::String& vGroup )
{

}

CMovableObject::CMovableObject(const char* vName, const Ogre::String& vGroup /*= Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME*/)
{

}

CMovableObject::~CMovableObject( void )
{

}

size_t CMovableObject::getTypeFlag( void ) const
{
	return (m_Creator == nullptr ? 0xFFFFFFFF : m_Creator->getTypeFlag());
}

CMovableObject* CMovableObject::_clone( const Ogre::String& vName )
{
	return new CMovableObject(vName);
}

void CMovableObject::_update( Ogre::Real vDeltaTime )
{

}
