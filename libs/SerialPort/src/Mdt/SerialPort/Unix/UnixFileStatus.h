// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_UNIX_FILE_STATUS_H
#define MDT_SERIAL_PORT_UNIX_FILE_STATUS_H

#include "Mdt/SerialPort/FileOpenError.h"
#include "Mdt/SerialPort/Unix/FileStatusFileType.h"
#include "mdt_serialport_export.h"
#include <sys/stat.h>
#include <filesystem>

namespace Mdt{ namespace SerialPort{

  /*! \brief Unix file status (stat)
   *
   * This is a helper class around Unix stat
   *
   * \sa https://man7.org/linux/man-pages/man3/stat.3type.html
   * \sa https://man7.org/linux/man-pages/man2/stat.2.html
   */
  class MDT_SERIALPORT_EXPORT UnixFileStatus
  {
   public:

    /// \todo deal with copy and move

    /*! \brief Get the ID of the device containing the file (st_dev)
     */
    dev_t deviceId() const noexcept
    {
      return mStat.st_dev;
    }

    /*! \brief Get the ID of the represented device (st_rdev)
     *
     * If this file status is a special file representing a device,
     * return the ID of the represented device.
     */
    dev_t representedDeviceId() const noexcept
    {
      return mStat.st_rdev;
    }

    /*! \brief Get the file type (extracted from st_mode)
     */
    Unix::FileStatusFileType fileType() const noexcept;

    /*! \brief Check if the file is a block device (extracted from st_mode)
     */
    bool isBlockDevice() const noexcept
    {
      return S_ISBLK(mStat.st_mode);
    }

    /*! \brief Check if the file is a character device (extracted from st_mode)
     */
    bool isCharacterDevice() const noexcept
    {
      return S_ISCHR(mStat.st_mode);
    }

    /*! \brief Get a file status from given stat struct
     *
     * \todo Should do some validation an throw an exception on failure.
     * Example: check if the file status type is a known one.
     */
    static
    UnixFileStatus fromStatStruct(const struct stat & st) noexcept;

    /*! \brief Get a file status from given path
     *
     * \exception FileOpenError
     *
     * \todo see fromStatStruct()
     */
    static
    UnixFileStatus fromPath(const std::filesystem::path & path);

   private:

    explicit
    UnixFileStatus(const struct stat & st) noexcept;

    struct stat mStat;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_UNIX_FILE_STATUS_H
