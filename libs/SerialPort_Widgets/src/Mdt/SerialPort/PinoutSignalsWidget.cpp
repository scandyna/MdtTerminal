// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PinoutSignalsWidget.h"
#include "ui_PinoutSignalsWidget.h"
#include <QLatin1String>

namespace Mdt{ namespace SerialPort{


PinoutSignalsWidget::PinoutSignalsWidget(QWidget *parent)
 : QWidget(parent),
   mUi( std::make_unique<Ui::PinoutSignalsWidget>() )
{
  mUi->setupUi(this);
}

PinoutSignalsWidget::~PinoutSignalsWidget() noexcept = default;

void PinoutSignalsWidget::setReceiveDataOn(bool on)
{
  if(on){
    mUi->RXsignal->setText( QLatin1String("ON") );
  }else{
    mUi->RXsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setTransmitDataOn(bool on)
{
  if(on){
    mUi->TXsignal->setText( QLatin1String("ON") );
  }else{
    mUi->TXsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setRequestToSendOn(bool on)
{
  if(on){
    mUi->RTSsignal->setText( QLatin1String("ON") );
  }else{
    mUi->RTSsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setClearToSendOn(bool on)
{
  if(on){
    mUi->CTSsignal->setText( QLatin1String("ON") );
  }else{
    mUi->CTSsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setDataCarrierDetectOn(bool on)
{
  if(on){
    mUi->DCDsignal->setText( QLatin1String("ON") );
  }else{
    mUi->DCDsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setDataSetReadyOn(bool on)
{
  if(on){
    mUi->DSRsignal->setText( QLatin1String("ON") );
  }else{
    mUi->DSRsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setDataTerminalReadyOn(bool on)
{
  if(on){
    mUi->DTRsignal->setText( QLatin1String("ON") );
  }else{
    mUi->DTRsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setRingIndicatorOn(bool on)
{
  if(on){
    mUi->RIsignal->setText( QLatin1String("ON") );
  }else{
    mUi->RIsignal->setText( QLatin1String("  ") );
  }
}

void PinoutSignalsWidget::setBreakOn(bool on)
{
  if(on){
    mUi->BreakSignal->setText( QLatin1String("ON") );
  }else{
    mUi->BreakSignal->setText( QLatin1String("  ") );
  }
}

}} // namespace Mdt{ namespace SerialPort{
