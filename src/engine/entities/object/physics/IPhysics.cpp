/*
	File: IPhysics.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IPhysics.h"

//-----------------------------------------------------------------------------
// Activates IPhysics initalization process
//-----------------------------------------------------------------------------
void IPhysics::Start(IInterfaces* interfaces, IObject* object)
{
	m_Interface = interfaces;

	m_Object = object;
}

//-----------------------------------------------------------------------------
// Activates IPhysics shutdown process
//-----------------------------------------------------------------------------
void IPhysics::Stop()
{
	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of IPhysics
//-----------------------------------------------------------------------------
void IPhysics::Run(float dt)
{
}

//-----------------------------------------------------------------------------
// Sets an object physics dynamic state
//-----------------------------------------------------------------------------
void IPhysics::SetBodyDynamic(bool dynamic)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(m_Object->m_Entity);

	if (dynamic)
	{
		if (physicscomponent == nullptr)
		{
			wiScene::RigidBodyPhysicsComponent& rigidbody = scene.rigidbodies.Create(m_Object->m_Entity);
		}
	}
	else
	{
		if (physicscomponent != nullptr)
		{
			scene.rigidbodies.Remove(m_Object->m_Entity);
		}
	}
}

//-----------------------------------------------------------------------------
// Sets an object physics active state
//-----------------------------------------------------------------------------
void IPhysics::SetBodyActive(bool active)
{

}

//-----------------------------------------------------------------------------
// Sets an object damping
//-----------------------------------------------------------------------------
void IPhysics::SetBodyDamping(float linearDamping, float angularDamping)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->setDamping(linearDamping, angularDamping);
	}
}

//-----------------------------------------------------------------------------
// Sets an object impulse
//-----------------------------------------------------------------------------
void IPhysics::SetBodyImpulse(Vector impulse)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->applyCentralImpulse(Point2btVector(impulse));
	}
}

//-----------------------------------------------------------------------------
// Sets an object impulse at a specified position
//-----------------------------------------------------------------------------
void IPhysics::SetBodyImpulseAt(Vector impulse, Vector position)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->applyImpulse(Point2btVector(impulse), btVector3(position.x, position.y, position.z));
	}
}

//-----------------------------------------------------------------------------
// Sets an object force
//-----------------------------------------------------------------------------
void IPhysics::SetBodyForce(Vector force)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->applyCentralForce(Vector2btVector(force));
	}
}

//-----------------------------------------------------------------------------
// Sets an object torque
//-----------------------------------------------------------------------------
void IPhysics::SetBodyTorque(Vector torque)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->applyTorque(Vector2btVector(torque));
	}
}

//-----------------------------------------------------------------------------
// Sets an object torque impulse
//-----------------------------------------------------------------------------
void IPhysics::SetBodyTorqueImpulse(Vector torque)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->applyTorqueImpulse(Vector2btVector(torque));
	}
}

//-----------------------------------------------------------------------------
// Sets an object force at a specified position
//-----------------------------------------------------------------------------
void IPhysics::SetBodyForceAt(Vector force, Vector position)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->applyForce(Vector2btVector(force), btVector3(position.x, position.y, position.z));
	}
}

//-----------------------------------------------------------------------------
// Sets an object mass
//-----------------------------------------------------------------------------
void IPhysics::SetMass(float mass)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		physicscomponent->mass = mass;
	}
}

//-----------------------------------------------------------------------------
// Returns an object mass
//-----------------------------------------------------------------------------
float IPhysics::GetMass()
{
	return 0.0f;
}

//-----------------------------------------------------------------------------
// Sets an object velocity
//-----------------------------------------------------------------------------
void IPhysics::SetVelocity(Vector velocity)
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		rigidBody->setLinearVelocity(Vector2btVector(velocity));
	}
}

//-----------------------------------------------------------------------------
// Returns an object velocity
//-----------------------------------------------------------------------------
Vector IPhysics::GetVelocity()
{
	wiScene::Scene& scene = wiScene::GetScene();
	wiScene::RigidBodyPhysicsComponent* physicscomponent = scene.rigidbodies.GetComponent(wiScene::GetScene().Entity_FindByName("Cube_Cube.001"));

	btRigidBody* rigidBody = (btRigidBody*)physicscomponent->physicsobject;
	if (rigidBody)
	{
		const btVector3& vel = rigidBody->getLinearVelocity();
		return Vector(vel.getX(), vel.getY(), vel.getZ());
	}

	return Vector();
}
