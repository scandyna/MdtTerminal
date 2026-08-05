// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortSetup.h"
#include <memory>

namespace Mdt{ namespace SerialPort{

class PortSetupImpl
{
};


PortSetup::PortSetup(QObject *parent)
 : QObject(parent),
   mImpl( std::make_unique<PortSetupImpl>() )
{
}

PortSetup::~PortSetup() noexcept = default;

void PortSetup::fetchPortInformations(const PortInfo & /*portInfo*/)
{
  // assert(mImpl != nullptr);
  // assert( !portInfo.systemLocation().isEmpty() );
}

bool PortSetup::shouldConfigureInterfaceBeforeOpenPort() const
{
  // assert(mImpl != nullptr);
  return false;
}

void PortSetup::configureInterfaceBeforeOpenPort(const Interface & /*interface*/)
{
}

void PortSetup::configureInterfaceOncePortOpen(const Interface & /*interface*/, QSerialPort & /*port*/)
{
  // assert( port.isOpen() );
}

}} // namespace Mdt{ namespace SerialPort{
