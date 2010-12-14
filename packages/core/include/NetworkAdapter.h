/*
 * Copyright (C) 2010 Robotics at Maryland
 * Copyright (C) 2010 Jonathan Sternberg <jsternbe@umd.edu>
 * All rights reserved.
 *
 * Author: Jonathan Sternberg <jsternbe@umd.edu>
 * File:  packages/core/include/NetworkAdapter.h
 */

#ifndef RAM_CORE_NETWORKADAPTER_H_12_12_2010
#define RAM_CORE_NETWORKADAPTER_H_12_12_2010

// Library Includes
#include <Ice/Ice.h>

// Project Includes
#include "core/include/ConfigNode.h"
#include "core/include/Subsystem.h"

namespace ram {
namespace core {

typedef Ice::ObjectPtr ObjectPtr;
typedef Ice::ObjectPrx ObjectPrx;

class NetworkAdapter : public Subsystem
{
public:
    NetworkAdapter(ConfigNode config, SubsystemList deps);

    virtual ~NetworkAdapter();

    ObjectPrx add(ObjectPtr object, std::string identity);

    void remove(std::string identity);

    /* IUpdatable interface */
    virtual void setPriority(Priority priority) {
    }

    virtual Priority getPriority() {
        return IUpdatable::NORMAL_PRIORITY;
    }

    virtual void setAffinity(size_t core) {
    }

    virtual int getAffinity() {
        return -1;
    }

    virtual void update(double timestep) {
    }

    virtual void background(int interval = -1);

    virtual void unbackground(bool join = false);

    virtual bool backgrounded() {
        /* always in the background */
        return true;
    }

private:
    Ice::CommunicatorPtr m_ic;
    Ice::ObjectAdapterPtr m_adapter;
};

} // namespace core
} // namespace ram

#endif // RAM_CORE_NETWORKADAPTER_H_12_12_2010
