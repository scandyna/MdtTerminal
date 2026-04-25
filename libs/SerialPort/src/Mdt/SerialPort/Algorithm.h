// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ALGORITHM_H
#define MDT_SERIAL_PORT_ALGORITHM_H

#include <QCollator>
#include <QList>
#include <algorithm>

namespace Mdt{ namespace SerialPort{

  /*! \brief Compare port info a and b
   *
   * Returns true if port name form \a a is < port name from \a b .
   *
   * The comparison is done with the help of given \a collator.
   * If configured properly, the order can be numerically correct
   * (f.ex. ttyS2 < ttyS10, or COM2 < COM10).
   *
   * \tparam PortInfo Object that has a method of this form:
   * \code
   * QString portName() const;
   * \endcode
   *
   */
  template <typename PortInfo>
  bool isLessThanByPortName(const PortInfo & a, const PortInfo & b, const QCollator & collator)
  {
    return collator.compare( a.portName(), b.portName() ) < 0;
  }

  /*! \brief Sort given port info list by port name
   *
   * \tparam PortInfo Object that has a method of this form:
   * \code
   * QString portName() const;
   * \endcode
   */
  template <typename PortInfo>
  void sortPortInfoListByPortName(QList<PortInfo> & list)
  {
    QCollator collator;
    collator.setNumericMode(true);

    const auto cmp = [&collator](const PortInfo & a, const PortInfo & b) -> bool
    {
      return isLessThanByPortName(a, b, collator);
    };

    std::sort(list.begin(), list.end(), cmp);
  }

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ALGORITHM_H
