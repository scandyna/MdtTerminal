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
    mUi->RXsignal->setText( QLatin1String("OFF") );
  }
}

}} // namespace Mdt{ namespace SerialPort{
