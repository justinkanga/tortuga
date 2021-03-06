/*
 * Copyright (C) 2008 Robotics at Maryland
 * Copyright (C) 2008 Joseph Lisee <jlisee@umd.edu>
 * All rights reserved.
 *
 * Author: Joseph Lisee <jlisee@umd.edu>
 * File:  packages/vision/include/device/ITempSensor.h
 */

#ifndef RAM_VEHICLE_DEVICE_ITEMPSENSOR_06_24_2008
#define RAM_VEHICLE_DEVICE_ITEMPSENSOR_06_24_2008

// STD Includesb
#include <string>

// Project Includes
#include "vehicle/include/device/IDevice.h"

// Must Be Included last
#include "vehicle/include/Export.h"

namespace ram {
namespace vehicle {
namespace device {
    
class RAM_EXPORT ITempSensor : public IDevice         // For getName
             // boost::noncopyable
{
public:
    /** Fired when the temperature updates */
    static const core::Event::EventType UPDATE;
    
    virtual ~ITempSensor();

    virtual int getTemp() = 0;
    
protected:
    ITempSensor(core::EventHubPtr eventHub = core::EventHubPtr(),
                std::string name = "UNNAMED");
};
    
} // namespace device
} // namespace vehicle
} // namespace ram

#endif // RAM_VEHICLE_DEVICE_ITEMPSENSOR_06_24_2008
