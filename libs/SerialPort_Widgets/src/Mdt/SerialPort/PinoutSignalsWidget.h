// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_WIDGET_H
#define MDT_SERIAL_PORT_PINOUT_SIGNALS_WIDGET_H

#include "mdt_serialport_widgets_export.h"
#include <QWidget>
#include <memory>

namespace Mdt{ namespace SerialPort{

  namespace Ui{
    class PinoutSignalsWidget;
  } // namespace Ui{

  /*! \brief Widget to display pinout signals
   *
   * \sa PinoutSignals
   */
  class MDT_SERIALPORT_WIDGETS_EXPORT PinoutSignalsWidget : public QWidget
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    PinoutSignalsWidget(QWidget *parent = nullptr);

    ~PinoutSignalsWidget() noexcept;

   public Q_SLOTS:

    /*! \brief Set RX (Receive Data) signal ON or OFF
     */
    void setReceiveDataOn(bool on);

    /*! \brief Set TX (Transmit Data) signal ON or OFF
     */
    void setTransmitDataOn(bool on);

    /*! \brief Set DTR (Data Terminal Ready) signal ON or OFF
     */
    void setDataTerminalReadyOn(bool on);

    /*! \brief Set RTS (Request To Send) ON or OFF
     */
    void setRequestToSendOn(bool on);

   private:

    std::unique_ptr<Ui::PinoutSignalsWidget> mUi;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_WIDGET_H
