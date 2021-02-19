/*
    File: IPhysics.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btVector3.h>

class IInterfaces;

class IObject;

class IPhysics
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IPhysics initalization process
    void Start(IInterfaces* interfaces, IObject* object);

    // Activates IPhysics shutdown process
    void Stop();

    // Processing a single frame of IPhysics
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------
    
    inline static btVector3 Point2btVector(const Vector& vec)
    {
        return btVector3(vec.x, vec.y, vec.z);
    }

    inline static btVector3 Vector2btVector(const Vector& vec)
    {
        return btVector3(vec.x, vec.y, vec.z);
    }

    void SetBodyDynamic(bool dynamic);
    void SetBodyActive(bool active);

    void SetBodyDamping(float linearDamping, float angularDamping);

    void SetBodyImpulse(Vector impulse);
    void SetBodyImpulseAt(Vector impulse, Vector position);

    void SetBodyForce(Vector force);
    void SetBodyForceAt(Vector force, Vector position);

    void SetBodyTorque(Vector torque);
    void SetBodyTorqueImpulse(Vector torque);

    void SetMass(float mass);
    float GetMass();

    void SetVelocity(Vector velocity);
    Vector GetVelocity();

protected:
    IInterfaces* m_Interface;
protected:
    template <class T> void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            *ppT = nullptr;
        }
    }
public:
    IObject* m_Object;
};