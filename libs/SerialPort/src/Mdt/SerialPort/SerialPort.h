// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SERIAL_PORT_H
#define MDT_SERIAL_PORT_SERIAL_PORT_H

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/PortOpenError.h"
#include "Mdt/SerialPort/Writer.h"
#include "Mdt/SerialPort/PinoutSignals.h"
#include "mdt_serialport_export.h"
#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <memory>

namespace Mdt{ namespace SerialPort{

  class PinoutSignalsEventNotifier;

  /*! \brief Helper around QSerialPort with some additions
   *
   * Here we will use a simplified example, based on Qt Serial Terminal example and MdtTerminal.
   * \sa https://doc.qt.io/qt-6/qtserialport-terminal-example.html
   * \sa https://gitlab.com/scandyna/mdtterminal
   *
   * The main window class is declared in MainWindow.h:
   * \code
   * #include <Mdt/SerialPort/SerialPort.h>
   *
   * class MainWindow : public QMainWindow
   * {
   *   Q_OBJECT
   *
   *  public:
   *
   *   explicit
   *   MainWindow(QWidget *parent = nullptr);
   *
   *  private slots:
   *
   *   void setupSerialPort();
   *   bool hasSerialPortSettings() const;
   *   void openSerialPort();
   *   void closeSerialPort();
   *   void submitCommand(const QString & command);
   *   void readFromPort();
   *
   *  private:
   *
   *   Mdt::SerialPort::SerialPort mSerialPort;
   *
   *   // Optional: if you want to display pinout signals, like RTS, CTS
   *   Mdt::SerialPort::PinoutSignalsUiController mPinoutSignalsUiController;
   * };
   * \endcode
   *
   * Here is the top part of MainWindow.cpp:
   * \code
   * #include <Mdt/SerialPort/SettingsDialog.h>
   * #include <cassert>
   *
   * using namespace Mdt::SerialPort;
   * \endcode
   *
   * \todo Complete and document constructor
   *
   * \code
   * MainWindow::MainWindow(QWidget* parent)
   *  : QMainWindow(parent)
   * {
   *   ...
   *   connect(&mSerialPort, &SerialPort::readyRead, this, &MainWindow::readFromPort);
   * }
   * \endcode
   *
   * It is also possible to display pinout signals:
   * \code
   * MainWindow::MainWindow(QWidget* parent)
   *  : QMainWindow(parent)
   * {
   *   ...
   *   mSerialPort.setPinoutSignalsEventNotifierEnabled(true);
   *   connect(&mSerialPort, &SerialPort::aboutToClose, &mPinoutSignalsUiController, &PinoutSignalsUiController::setAboutToCloseEvent);
   *   connect(&mSerialPort, &SerialPort::pinoutSignalsChanged, &mPinoutSignalsUiController, &PinoutSignalsUiController::setSignals);
   *
   *   // Connect the various pinout signals to your widgets, f.ex.:
   *   connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::receiveDataChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setReceiveDataOn);
   *   ...
   * }
   * \endcode
   *
   * For more information about pinout signals,
   * see the dedicated section:
   * \ref SerialPort_PinoutSignals
   *
   * To setup the serial port, we use Mdt::SerialPort::SettingsDialog:
   * \code
   * void MainWindow::setupSerialPort()
   * {
   *   assert( !mSerialPort.isOpen() );
   *
   *   Mdt::SerialPort::SettingsDialog dialog(this);
   *
   *   dialog.setSettings( mSerialPort.settings() );
   *
   *   const int result = dialog.exec();
   *   if(result == QDialog::Accepted){
   *     mSerialPort.setSettings( dialog.buildSettings() );
   *   }
   * }
   * \endcode
   *
   * Here is a simple helper that will be used below:
   * \code
   * bool MainWindow::hasSerialPortSettings() const
   * {
   *   return mSerialPort.hasRequiredSettings();
   * }
   * \endcode
   *
   * If no settings are available, for example at the first call to open the serial port,
   * we will ask the user to, at least, choose a serial port.
   * If the user do not accept the settings dialog (f.ex. by clicking Cancel),
   * we don't try to open the port:
   * \code
   * void MainWindow::openSerialPort()
   * {
   *   assert( !mSerialPort.isOpen() );
   *
   *   if( !hasSerialPortSettings() ){
   *     setupSerialPort();
   *   }
   *   if( !hasSerialPortSettings() ){
   *     return;
   *   }
   *
   *   try{
   *     mSerialPort.openReadWrite();
   *   }catch(const Mdt::SerialPort::PortOpenError & error){
   *     displayError(error);
   *     return;
   *   }
   * }
   * \endcode
   *
   * To close the serial port,
   * we can simply call close(),
   * that will take care to only close the port if it is open:
   * \code
   * void MainWindow::closeSerialPort()
   * {
   *   mSerialPort.close();
   * }
   * \endcode
   *
   * \section Mdt_SerialPort_SerialPort_WriteAndRead Writing and reading
   *
   * \todo Review this part. See https://doc.qt.io/qt-6/qtserialport-terminal-example.html
   * The writer should also help here.
   *
   * SerialPort exposes the asynchronous API of QSerialPort,
   * that is the most reliable way to communicate using a full duplex bus.
   *
   * \subsection Mdt_SerialPort_SerialPort_WriteToPort Write to port
   *
   * Sending data using write() will most probably add the given data
   * to an internal buffer, then return.
   * In the event loop, chunks of data will be sent using
   * low level API at appropriate time.
   * (looking at the %Unix and Windows implementation of QSerialPortPrivate::writeData(),
   *  this is how it is implemented, at least in Qt6.8.3).
   * Also, QSerialPort::write() will probably not return an amount < 0
   * on serial port errors, but maybe buffering errors.
   * Example:
   * \code
   * void MainWindow::submitCommand(const QByteArray & command)
   * {
   *   assert( mSerialPort.isOpen() );
   *
   *   const auto written = mSerialPort.write(command);
   *   if(written < 0){
   *     displayError(...);
   *     return;
   *   }
   * }
   * \endcode
   * Try above code with an usb-serial interface:
   * - Plug the device
   * - open the port
   * - unplug the device
   * - call %submitCommand()
   *
   * \a %written will probably be >= 0.
   * But, at some time, QSerialPort::errorOccurred() will be emitted
   * with a QSerialPort::ResourceError argument.
   *
   * Checking the returned value of write() is still a good practice.
   * It could happen that a value < 0 is returned,
   * but it could also return a value less than the given buffer's size,
   * especially when using QSerialPort::setWriteBufferSize(), introduced int Qt 6.10.
   * \sa https://doc.qt.io/qt-6/qserialport.html#setWriteBufferSize
   *
   * Example:
   * \code
   * void MainWindow::submitCommand(const QByteArray & command)
   * {
   *   assert( mSerialPort.isOpen() );
   *
   *   const qsizetype written = mSerialPort.write(command);
   *   if( written < command.size() ){
   *     handleWriteError(...);
   *     return;
   *   }
   * }
   * \endcode
   *
   * \todo Maybe some notes about bytesWritten() signal and bytesToWrite()
   *
   * \sa Mdt::SerialPort::Writer
   *
   * \subsection Mdt_SerialPort_SerialPort_ReadFromPort Read from port
   *
   * Reading from port should be done every time the readyRead() signal has been emitted.
   * For some cases, bytesAvailable() can be useful.
   * bytesAvailable() should always return a value >= 0.
   * ( I did look the implementation of QSerialPort::bytesAvailable(),
   *   QSerialPort::isSequential() and QIODevice::bytesAvailable() ).
   *
   * Example of a read slot called by readyRead():
   * \code
   * void MainWindow::readFromPort()
   * {
   *   QByteArray data = mSerialPort.readAll();
   *
   *   doSomething(data);
   * }
   * \endcode
   *
   * When reading from port only when readyRead() has been emitted,
   * it is mostly probable that errors are not returned by QSerialPort::read().
   * Here is some debug code:
   * \code
   * void MainWindow::readFromPort()
   * {
   *   assert( mSerialPort.isOpen() );
   *
   *   qDebug() << "readFromPort...";
   *
   *   const auto size = mSerialPort.bytesAvailable();
   *   qDebug() << " size (bytesAvailable): " << size;
   *
   *   // Don't do this so blindly in production code !
   *   QByteArray data(size, Qt::Uninitialized);
   *   const auto readen = mSerialPort.read(data.data(), size);
   *   qDebug() << " readen: " << readen;
   * }
   * \endcode
   * Try above code like this:
   * - launch the app with above code
   * - choose a usb-serial based port with default settings
   * - write to another port: cat /dev/random > /dev/ttyS0
   * - look data comes to the app
   * - unplug the usb-serial device
   *
   * Depending on the system, nothing will probably happen to the app,
   * unless we produce some event, like try to write to the port, or close it.
   *
   * When using the pinout signal event notifier,
   * QSerialPort::pinoutSignals() is called at regular time.
   * In this situation, QSerialPort::errorOccurred() will be emited soon.
   * \sa setPinoutSignalsEventNotifierEnabled()
   *
   * Checking read errors could be a good practice anyway:
   * \code
   * void MainWindow::readFromPort()
   * {
   *   QByteArray data = mSerialPort.readAll();
   *   if( data.isEmpty() && mSerialPort.error() != QSerialPort::NoError ){
   *     handleReadError();
   *     return;
   *   }
   *
   *   doSomething(data);
   * }
   * \endcode
   *
   *
   * \todo Timout timer currently not implemented
   *
   * For some applications, you may want to produce an error if the device does not respond
   * (or the serial cable has been unplugged, or is defect):
   * \code
   * void MainWindow::submitCommand(const QByteArray & command)
   * {
   *   assert( mSerialPort.isOpen() );
   *
   *   const qsizetype written = mSerialPort.write(command);
   *   if( written < command.size() ){
   *     handleWriteError(...);
   *     return;
   *   }
   *
   *   mSerialPort.startReadTimeoutTimer();
   *  OR
   *   mSerialPort.restartReadTimeoutTimer();
   * }
   * \endcode
   * In above example, the timer starts after having sent a command.
   * Depending on the application, it may should be started at some other point,
   * or never at all.
   * SerialPort will take care to stop the timeout timer at appropriate time
   * (in read methods, timeout occurred, close, ...).
   * The read timeout timer will not block the current thread.
   * It is based on QTimer, it does NOT use QSerialPort::waitForReadyRead()
   * nor QSerialPort::waitForBytesWritten().
   *
   * \section Mdt_SerialPort_SerialPort_ErrorHandling Error handling
   *
   * \code
   * void MainWindow::onSerialPortErrorOccured(QSerialPort::SerialPortError error)
   * {
   *   if(error == QSerialPort::NoError){
   *     return;
   *   }
   *
   *   QString serialPortErrorString = mSerialPort.errorString();
   *
   *   if(error == QSerialPort::ResourceError){
   *     // This error can occur when using an usb-serial adapter,
   *     // and it has been unplugged.
   *     // Once plugged in again, the system could map it to another serial port
   *     // (like ttyUSB0 -> ttyUSB2, COM3 -> COM5).
   *     // The best we can do is probably to close the port and show an error to the user.
   *     closeSerialPort();
   *     QString text = tr("The port %1 is no more available.").arg( mSerialPort.portName() );
   *     QString informativeText = tr("The port is probably an usb-serial adapter that has been unplugged.");
   *     QString detailedText = tr("System returned: %1").arg(serialPortErrorString);
   *     displayErrorMessage(text, informativeText, detailedText);
   *     return;
   *   }
   *
   *   // We don't know how to handle other errors yet.
   *   closeSerialPort();
   *   QString text = tr("An unexpected error occurred.");
   *   QString informativeText = tr("System returned: %1").arg(serialPortErrorString);
   *   displayErrorMessage(text, informativeText);
   * }
   * \endcode
   *
   * \sa https://doc.qt.io/qt-6/qserialport.html
   *
   * ## Some personal notes
   *
   * \todo Below are only som notes. Remove those
   *
   * Maybe, option to filter out break ? hmm...
   *
   * Maybe, do not emit errorOccurred() during open / close ??
   *
   * Set pinout signals.
   *
   * Get pinout signals.
   *
   * Error handling.
   *
   * Functions returning an error: exception
   * Async function: errorOccurred() signal.
   */
  class MDT_SERIALPORT_EXPORT SerialPort : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructs a new serial port object with the given parent
     */
    explicit
    SerialPort(QObject *parent = nullptr);

    /*! \brief Closes the serial port, if necessary, and then destroys object
     */
    virtual
    ~SerialPort() noexcept;

    /*! \brief Enable pinout signals event notification
     *
     * When enabled, the pinoutSignalsChanged() signal
     * will be emitted when a pinout signal changes.
     *
     * \pre This port must not be open
     * \sa isOpen()
     *
     * \sa \ref SerialPort_PinoutSignals
     */
    void setPinoutSignalsEventNotifierEnabled(bool enable);

    /*! \brief Set the settings
     *
     * \pre This port must not be open
     * \sa isOpen()
     */
    void setSettings(const Settings & settings);

    /*! \brief Get the settings
     */
    const Settings & settings() const noexcept
    {
      return mSettings;
    }

    /*! \brief Get the port name
     */
    QString portName() const
    {
      return mSettings.portName();
    }

    /*! \brief Get the flow control
     */
    QSerialPort::FlowControl flowControl() const
    {
      return mPort.flowControl();
    }

    /*! \brief Check if this port has required settings
     *
     * Returns true if this port has the required settings
     * to open the serial port.
     */
    bool hasRequiredSettings() const
    {
      return mSettings.hasPortInfo();
    }

    /*! \brief Open this port
     *
     * \pre This port must not already be open
     * \sa isOpen()
     * \pre This port must have required settings
     * \sa hasRequiredSettings()
     * \exception PortOpenError
     * \sa openReadOnly()
     * \sa openWriteOnly()
     * \sa openReadWrite()
     */
    void open(QIODeviceBase::OpenMode mode);

    /*! \brief Open this port read only
     *
     * \pre This port must not already be open
     * \sa isOpen()
     * \sa open()
     */
    void openReadOnly();

    /*! \brief Open this port write only
     *
     * \pre This port must not already be open
     * \sa isOpen()
     * \sa open()
     */
    void openWriteOnly();

    /*! \brief Open this port read and write
     *
     * \pre This port must not already be open
     * \sa isOpen()
     * \sa open()
     */
    void openReadWrite();

    /*! \brief Check if this port is open
     */
    bool isOpen() const
    {
      return mPort.isOpen();
    }

    /*! \brief Close this port
     *
     * This method can also be called when the port is not open
     * (in which case it does nothing).
     */
    void close();

    /*! \brief Writes the content of \a data to the serial port
     *
     * Returns the number of bytes that were actually written, or -1 if an error occurred.
     *
     * \sa \ref Mdt_SerialPort_SerialPort_WriteToPort
     * \sa bytesWritten()
     */
    qint64 write(const QByteArray &data);

    /*! \brief Reads all remaining data from the serial port, and returns it as a byte array
     *
     * Reading data should be done every time \a readyRead() has been emitted.
     *
     * \sa readyRead()
     * \sa \ref Mdt_SerialPort_SerialPort_ReadFromPort
     */
    QByteArray readAll();

    /*! \brief Set Data Terminal Ready (DTR) high or low
     *
     * Returns true on success, false otherwise.
     * If the flag is true then the DTR signal is set to high; otherwise low.
     *
     * \pre This port must be open
     * \sa isOpen()
     */
    bool setDataTerminalReady(bool set);

    /*! \brief Set Request To Send (RTS) high or low
     *
     * Returns true on success, false otherwise.
     * If the flag is true then the RTS signal is set to high; otherwise low.
     *
     * \pre This port must be open
     * \sa isOpen()
     */
    bool setRequestToSend(bool set);

    /*! \brief Set transmission line break high or low
     *
     * Returns true on success, false otherwise.
     * If the flag is true then the transmission line is in break state; otherwise is in non-break state.
     *
     * \pre This port must be open
     * \sa isOpen()
     */
    bool setBreakEnabled(bool set = true);

    /*! \brief Get the error status of the serial port
     */
    QSerialPort::SerialPortError error() const
    {
      return mPort.error();
    }

    /*! \brief Returns a human-readable description of the last serial port error that occurred
     */
    QString errorString() const
    {
      return mPort.errorString();
    }

   Q_SIGNALS:

    /*! \brief This signal is emitted when the serial port is about to close
     */
    void aboutToClose();

    /*! \brief This signal is emitted every time a payload of data has been written to the serial port
     */
    void bytesWritten(qint64 bytes);

    /*! \brief This signal is emitted once every time new data is available for reading from the serial port
     */
    void readyRead();

    /*! \brief Emitted everytime at least 1 pinout signal changed
     *
     * \note This signal will only be emitted
     * if the pinout signals event notifier is enabled.
     * \sa setPinoutSignalsEventNotifierEnabled()
     */
    void pinoutSignalsChanged(const PinoutSignals & ps);

    /*! \brief This signal is emitted when an error occurs in the serial port
     */
    void errorOccurred(QSerialPort::SerialPortError error);

   private:

    void throwPermissionPortOpenError();

    QSerialPort mPort;
    Writer mWriter;
    Settings mSettings;
    std::unique_ptr<PinoutSignalsEventNotifier> mPinoutSignalsEventNotifier;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SERIAL_PORT_H
