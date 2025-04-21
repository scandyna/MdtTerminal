// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SEND_BYTE_BY_BYTE_SETTINGS_H
#define MDT_SERIAL_PORT_SEND_BYTE_BY_BYTE_SETTINGS_H

#include "mdt_serialport_export.h"
#include <optional>
#include <chrono>
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \brief Send byte by byte settings
   */
  class MDT_SERIALPORT_EXPORT SendByteByByteSettings
  {
   public:

    /*! \brief Check if sending byte by byte is enabled
     *
     * \sa interval()
     */
    bool isEnabled() const noexcept
    {
      return mInterval.has_value();
    }

    /*! \brief Get the interval between bytes
     *
     * \pre send byte by byte must be enabled
     * \sa isEnabled()
     */
    std::chrono::milliseconds interval() const noexcept
    {
      assert( isEnabled() );

      return *mInterval;
    }

    /*! \brief Get the interval between bytes
     *
     * \pre send byte by byte must be enabled
     * \sa isEnabled()
     */
    int rawIntervalInMilliseconds() const noexcept
    {
      assert( isEnabled() );

      // We know interval is (far) from int limits
      return static_cast<int>( interval().count() );
    }

    /*! \brief Construct disabled settings
     */
    static
    SendByteByByteSettings disabled() noexcept;

    /*! \brief Construct settings with given interval
     *
     * \pre \a interval must be valid
     * \sa intervalIsValid()
     */
    static
    SendByteByByteSettings enabledWithInterval(std::chrono::milliseconds interval) noexcept;

    /*! \brief Construct settings with given interval
     *
     * \pre \a interval must be valid
     * \sa rawIntervalInMillisecondsIsValid()
     */
    static
    SendByteByByteSettings enabledWithRawIntervalInMilliseconds(int interval) noexcept;

    /*! \brief Check if given interval is valid
     */
    static
    bool intervalIsValid(std::chrono::milliseconds interval) noexcept;

    /*! \brief Check if given interval is valid
     */
    static
    bool rawIntervalInMillisecondsIsValid(int interval) noexcept;

    /*! \brief Get the minimum allowed interval
     */
    static
    std::chrono::milliseconds minimumInterval() noexcept;

    /*! \brief Get the maximum allowed interval
     */
    static
    std::chrono::milliseconds maximumInterval() noexcept;

    /*! \brief Get the minimum allowed interval
     */
    static
    int minimumRawIntervalInMilliseconds() noexcept;

    /*! \brief Get the maximum allowed interval
     */
    static
    int maximumRawIntervalInMilliseconds() noexcept;

   private:

    SendByteByByteSettings() /*noexcept*/ = default;

    SendByteByByteSettings(std::chrono::milliseconds interval) noexcept
     : mInterval(interval)
    {
    }

    std::optional<std::chrono::milliseconds> mInterval;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SEND_BYTE_BY_BYTE_SETTINGS_H
