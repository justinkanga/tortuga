/*
 * Copyright (C) 2007 Robotics at Maryland
 * Copyright (C) 2007 Joseph Lisee <jlisee@umd.edu>
 * All rights reserved.
 *
 * Author: Joseph Lisee <jlisee@umd.edu>
 * File:  packages/packages/vehicle/test/include/MockDevice.h
 */

#ifndef RAM_VEHICLE_MOCKDEVICE_10_29_2007
#define RAM_VEHICLE_MOCKDEVICE_10_29_2007

// Project Includes
#include "vehicle/include/device/Device.h"
#include "vehicle/include/device/IDevice.h"
#include "core/include/ConfigNode.h"

// Must Be Included last
//#include "vehicle/include/Export.h"

class MockDevice : public ram::vehicle::device::IDevice,
                   public ram::vehicle::device::Device
{
public:
    MockDevice(std::string name) :
        IDevice(ram::core::EventHubPtr()),
        Device(name) {}
    
    MockDevice(ram::core::ConfigNode config,
               ram::core::EventHubPtr eventHub =
               ram::core::EventHubPtr(),
               ram::vehicle::IVehiclePtr vehicle_ =
               ram::vehicle::IVehiclePtr()) :
        IDevice(eventHub),
        Device(config["name"].asString())
    {
        vehicle = vehicle_;
    }

    virtual std::string getName() {
        return ram::vehicle::device::Device::getName();
    }

    virtual void setPriority(ram::core::IUpdatable::Priority) {};
    virtual ram::core::IUpdatable::Priority getPriority() {
        return ram::core::IUpdatable::NORMAL_PRIORITY;
    };
    virtual void setAffinity(size_t) {};
    virtual int getAffinity() {
        return -1;
    };
    virtual void update(double) {}
    virtual void background(int) {}
    virtual void unbackground(bool) {}
    virtual bool backgrounded() { return false; }

    ram::vehicle::IVehiclePtr vehicle;
};

#endif // RAM_VEHICLE_MOCKDEVICE_10_29_2007
