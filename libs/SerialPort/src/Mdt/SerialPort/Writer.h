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

#include "Mdt/SerialPort/AbstractWriter.h"
#include "Mdt/SerialPort/SendByteByByteSettings.h"
#include "mdt_serialport_export.h"
#include <QIODevice>
#include <QByteArray>
#include <QPointer>
#include <memory>

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

    /*! \brief Construct a null writer
     *
     * \pre \a device must be a valid pointer
     */
    explicit
    Writer(QIODevice *device);

    /*! \brief set settings
     *
     * Depending on \a settings, this writer will become
     * a direct writer or a byte by byte writer.
     */
    void setSettings(const SendByteByByteSettings & settings);

    /*! \brief Writes the content of data to the device
     *
     * If this is a direct writer, QIODevice::write() will be called.
     *
     * \note If using QSerialPort, and all preconditions are ok
     * (f.ex. port is writable), write should only copy the data
     * into an internal buffer and return data's size.
     *
     * If this is a byte by byte writer, data will be copied
     * into an internal buffer of this writer,
     * and QIODevice::putChar() will be called at the defined intervall.
     * data's size is returned.
     *
     * \pre this must be a valid writer,
     * meaning setSettings() must have been called at least once.
     * \sa setSettings()
     * \pre The device must be open in a mode that allows writing
     */
    qint64 write(const QByteArray & data);

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

  protected:

    /*! \internal
     */
    AbstractWriter *impl() const noexcept
    {
      return mImpl.get();
    }

  private:

    void instanciateDirectWriterIf();
    void instanciateByteByByteWriterIf();

    std::unique_ptr<AbstractWriter> mImpl;
    QPointer<QIODevice> mDevice;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_WRITER_H
