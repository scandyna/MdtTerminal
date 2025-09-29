// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Writer.h"
#include "DirectWriter.h"
#include "ByteByByteWriter.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

Writer::Writer(QIODevice *device)
 : mDevice(device)
{
  assert(device != nullptr);
}

void Writer::setSettings(const SendByteByByteSettings & settings)
{
  if( settings.isEnabled() ){
    instanciateByteByByteWriterIf();
    assert( dynamic_cast<ByteByByteWriter*>( mImpl.get() ) != nullptr );
    static_cast<ByteByByteWriter*>( mImpl.get() )->setInterval( settings.interval() );
  }else{
    instanciateDirectWriterIf();
  }
}

qint64 Writer::write(const QByteArray & data)
{
  assert(mImpl != nullptr);
  assert( !mDevice.isNull() );
  assert( mDevice->isOpen() );
  assert( mDevice->isWritable() );

  return mImpl->write(data);
}

void Writer::clear()
{
  if(mImpl){
    mImpl->clear();
  }
}

void Writer::instanciateDirectWriterIf()
{
  assert( !mDevice.isNull() );

  if( mImpl && mImpl->isDirectWriter() ){
    return;
  }

  mImpl = std::make_unique<DirectWriter>(mDevice);
}

void Writer::instanciateByteByByteWriterIf()
{
  assert( !mDevice.isNull() );

  if( mImpl && mImpl->isByteByByteWriter() ){
    return;
  }

  mImpl = std::make_unique<ByteByByteWriter>(mDevice);
}

}} // namespace Mdt{ namespace SerialPort{
