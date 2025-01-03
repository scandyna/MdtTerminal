// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_QRUNTIME_ERROR_H
#define MDT_SERIAL_PORT_QRUNTIME_ERROR_H

#include "mdt_serialport_export.h"
#include <QString>
#include <QByteArray>
#include <stdexcept>

namespace Mdt{ namespace SerialPort{

  /*! \brief Base class for runtime exceptions using QString messages
   *
   * The concept of text, informativeText and detailedText are used.
   * They are inspired from QMessageBox.
   *
   * The text alerts the user to a situation and is always used.
   * It will also be displayed when an exception has been thrown.
   *
   * Informative text can be used to expand upon text to give more information to the user,
   * for example describing the consequences of the situation, or suggestion of alternative solutions.
   *
   * Detailed text can give more information to help the user to choose an appropriate action.
   *
   * Usage example:
   * \code
   * class MyError : public QRuntimeError
   * {
   *  public:
   *
   *    explicit
   *    MyError(const QString & text)
   *     : QRuntimeError(text)
   *    {
   *    }
   * };
   * \endcode
   *
   * \sa https://doc.qt.io/qt-6/qmessagebox.html#details
   * \sa https://en.cppreference.com/w/cpp/error/runtime_error
   */
  class MDT_SERIALPORT_EXPORT QRuntimeError : public std::runtime_error
  {
   public:

    QRuntimeError() = delete;

    /*! \brief Constructor
     */
    explicit
    QRuntimeError(const QString & text)
     : runtime_error( text.toLocal8Bit().toStdString() )
    {
    }

    /*! \brief Copy construct an error from \a other
     */
    QRuntimeError(const QRuntimeError & other) noexcept = default;

    /*! \brief Copy assign \a other to this error
     */
    QRuntimeError & operator=(const QRuntimeError & other) noexcept = default;

    /*! \brief Move construct an error from \a other
     */
    QRuntimeError(QRuntimeError && other) noexcept = default;

    /*! \brief Move assign \a other to this error
     */
    QRuntimeError & operator=(QRuntimeError && other) noexcept = default;

    /*! \brief Get the text of this error
     */
    QString text() const noexcept
    {
      return QString::fromLocal8Bit( QByteArray::fromStdString( what() ) );
    }

    /*! \brief Set the informative text of this error
     */
    void setInformativeText(const QString & text) noexcept
    {
      mInformativeText = text.trimmed();
    }

    /*! \brief Check if this error has an informative text
     *
     * \sa informativeText()
     */
    bool hasInformativeText() const noexcept
    {
      return !mInformativeText.isEmpty();
    }

    /*! \brief Get the informative text of this error
     *
     * \sa hasInformativeText()
     */
    const QString & informativeText() const noexcept
    {
      return mInformativeText;
    }

    /*! \brief Set the detailed text of this error
     */
    void setDetailedText(const QString & text) noexcept
    {
      mDetailedText = text.trimmed();
    }

    /*! \brief Check if this error has a detailed text
     */
    bool hasDetailedText() const noexcept
    {
      return !mDetailedText.isEmpty();
    }

    /*! \brief Get the detailed text of this error
     *
     * \sa hasDetailedText()
     */
    const QString & detailedText() const noexcept
    {
      return mDetailedText;
    }

   private:

    QString mInformativeText;
    QString mDetailedText;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_QRUNTIME_ERROR_H
