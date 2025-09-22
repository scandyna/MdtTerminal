// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_WRITER_H
#define MDT_SERIAL_PORT_WRITER_H

#include "Mdt/SerialPort/SendByteByByteSettings.h"
#include "mdt_serialport_export.h"
#include <QIODevice>
#include <QByteArray>

namespace Mdt{ namespace SerialPort{

  /*! \brief Serial port writer
   *
   * \code
   * class MySerialPort
   * {
   *  public:
   *
   *   MySerialPort();
   *   void setSettings(const Mdt::SerialPort::Settings & settings);
   *   void submitCommand(const QByteArray & command);
   *   void cancelSendCommand();
   *   void close();
   *
   *  private slots:
   *
   *   void onSerialPortErrorOccured(QSerialPort::SerialPortError error);
   *
   *  private:
   *
   *   QSerialPort mSerialPort;
   *   Mdt::SerialPort::Writer mWriter;
   * };
   * \endcode
   *
   * \code
   * MySerialPort::MySerialPort()
   *  : mWriter(&mSerialPort)
   * {
   *   connect(&mSerialPort, &QSerialPort::errorOccurred, this, &MySerialPort::onSerialPortErrorOccured);
   * }
   *
   * void MySerialPort::setSettings(const Mdt::SerialPort::Settings & settings)
   * {
   *   // Setup mSerialPort - omitted here
   *   mWriter.setSettings( settings.sendByteByByteSettings() );
   * }
   *
   * void MySerialPort::submitCommand(const QByteArray & command)
   * {
   *   const qint64 r = mWriter.write(command);
   *   if(r < 0){
   *     // error handling
   *   }
   *
   *   OR, because we assume QSerialPort, that is an async device:
   *
   *   if( !mWriter.submitData(command) ){
   *     // error handling
   *   }
   *
   *   OR
   *
   *   mWriter.write(command);
   * }
   *
   * void MySerialPort::cancelSendCommand()
   * {
   *   mWriter.clear();
   *   mSerialPort.clear(QSerialPort::Output);
   * }
   *
   * void MySerialPort::close()
   * {
   *   mSerialPort.close();
   *   // this also calls Writer::clear()
   * }
   *
   * void MySerialPort::onSerialPortErrorOccured(QSerialPort::SerialPortError error)
   * {
   *   // Here, error handling regarding the serial port (f.ex. USB datapter unplugged)
   * }
   * \endcode
   *
   * \todo error handling with the specific IO device.
   *
   * \todo Clarify the write API in QIODevice
   *
   * \note QIODevice is not very clear about how much the %write() methods will write.
   * The %write() documentations says:
   * Writes at most maxSize bytes of data from data to the device. Returns the number of bytes that were actually written, or -1 if an error occurred.
   * The writeData() documentations says:
   * When reimplementing this function it is important that this function writes all the data available before returning.
   * QSerialPort::writeData() copies the data into an internal buffer and returns maxSize.
   * \sa https://doc.qt.io/qt-6/qiodevice.html#write
   * \sa https://doc.qt.io/qt-6/qiodevice.html#writeData
   */
  class MDT_SERIALPORT_EXPORT Writer
  {
   public:


    /*! \brief
     *
     * If this is a direct writer, QIODevice::write() will be called.
     *
     * \note If using QSerialPort, and all preconditions are ok
     * (f.ex. port is writable), write should only copy the data
     * into an internal buffer and return max size.
     *
     * If this is a byte by byte writer, data will be copied
     * into an internal buffer of this writer,
     * and QIODevice::putChar() will be called at the defined intervall.
     * Max size is returned.
     *
     * \note It is assumed that the QIODevice is an asynchronous device,
     * like QSerialPort, that copies data to an internal buffer and returns the max size.
     *
     * \todo return qint64 and document that, with QSerialPort, this should always return max size.
     *
     * \todo hmm... and byte by byte writer ?
     *
     * \todo use write() name
     */
    qint64 write();

    /*! \brief Clear this writer
     *
     * If this is a byte by byte writer,
     * will abort the current write, if any,
     * and clear the internal buffer of this writer.
     *
     * This slot is also called when the device is about to close.
     *
     * \note QIODevice::clear() does not exist.
     * If you use QSerialPort, you should also call QSerialPort::clear(QSerialPort::Output).
     */
    void clear();
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_WRITER_H
