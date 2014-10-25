#include "InstanceEntity.h"
using namespace hiveCrowd::Kernel;

CInstanceEntity::CInstanceEntity(void)
{

}

CInstanceEntity::CInstanceEntity(const char* vName, const Ogre::String& vGroup /*= ""*/)
{

}

CInstanceEntity::CInstanceEntity(const Ogre::String& vName, const Ogre::String& vGroup /*= ""*/)
{

}

CInstanceEntity::~CInstanceEntity(void)
{

}

hiveCrowd::Common::CObject* CInstanceEntityFactory::_createProductImpl( const Ogre::String& vName ) const 
{
	// TODO:

	return nullptr;
}

hiveCrowd::Common::CObject* CInstanceEntityFactory::_createProductImpl( const char* vName ) const 
{
	// TODO:

	return nullptr;
}
