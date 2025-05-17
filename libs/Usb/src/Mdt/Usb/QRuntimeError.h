// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_QRUNTIME_ERROR_H
#define MDT_USB_QRUNTIME_ERROR_H

#include "mdt_usb_export.h"
#include <QString>
#include <QByteArray>
#include <stdexcept>

namespace Mdt{ namespace Usb{

  /*! \brief Base class for runtime exceptions using QString messages
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
  class MDT_USB_EXPORT QRuntimeError : public std::runtime_error
  {
   public:

    QRuntimeError() = delete;

    /*! \brief Constructor
     */
    explicit
    QRuntimeError(const QString & text) noexcept
     : runtime_error( text.toLocal8Bit().toStdString() )
    {
    }

    /*! \brief Copy construct an error from \a other
     */
    QRuntimeError(const QRuntimeError & other) noexcept = default;

    /*! \brief Copy assign \a other to this error
     */
    QRuntimeError & operator=(const QRuntimeError & other) noexcept = default;

    /*! \brief Get the text of this error
     */
    QString text() const noexcept
    {
      return QString::fromLocal8Bit( QByteArray::fromStdString( what() ) );
    }

  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_QRUNTIME_ERROR_H
