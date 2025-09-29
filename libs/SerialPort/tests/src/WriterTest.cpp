// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Writer.h"
#include "Mdt/SerialPort/ByteByByteWriter.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <QBuffer>
#include <chrono>


using namespace Mdt::SerialPort;
using namespace std::chrono_literals;


class TestWriter : public Writer
{
 public:

  explicit
  TestWriter(QIODevice *device)
   : Writer(device)
  {
  }

  AbstractWriter *impl() const noexcept
  {
    return Writer::impl();
  }
};


TEST_CASE("DefaultConstructed")
{
  QBuffer buffer;
  TestWriter writer(&buffer);

  CHECK( writer.impl() == nullptr );
}

TEST_CASE("SetupAdirectWriter")
{
  QBuffer buffer;
  TestWriter writer(&buffer);

  const auto settings = SendByteByByteSettings::disabled();
  writer.setSettings(settings);

  REQUIRE( writer.impl() != nullptr );
  CHECK( writer.impl()->isDirectWriter() );
}

TEST_CASE("SetupAbyteByByteWriter")
{
  QBuffer buffer;
  TestWriter writer(&buffer);

  const auto settings = SendByteByByteSettings::enabledWithInterval(25ms);
  writer.setSettings(settings);

  REQUIRE( writer.impl() != nullptr );
  CHECK( writer.impl()->isByteByByteWriter() );
  const auto *bbbWriter = dynamic_cast<ByteByByteWriter*>( writer.impl() );
  REQUIRE( bbbWriter != nullptr );
  CHECK( bbbWriter->rawIntervalInMilliseconds() == 25 );
}

TEST_CASE("SetupMultipleTimes")
{
  QBuffer buffer;
  TestWriter writer(&buffer);

  SECTION("starting with a direct writer")
  {
    const auto settings = SendByteByByteSettings::disabled();
    writer.setSettings(settings);

    REQUIRE( writer.impl() != nullptr );
    REQUIRE( writer.impl()->isDirectWriter() );

    SECTION("setup a direct writer again not changes anything")
    {
      writer.setSettings(settings);

      REQUIRE( writer.impl() != nullptr );
      CHECK( writer.impl()->isDirectWriter() );
    }

    SECTION("change to a byte by byte writer works")
    {
      writer.setSettings( SendByteByByteSettings::enabledWithInterval(30ms) );

      REQUIRE( writer.impl() != nullptr );
      CHECK( writer.impl()->isByteByByteWriter() );
    }
  }

  SECTION("starting with a byte by byte writer")
  {
    const auto settings = SendByteByByteSettings::enabledWithInterval(25ms);
    writer.setSettings(settings);

    REQUIRE( writer.impl() != nullptr );
    REQUIRE( writer.impl()->isByteByByteWriter() );

    SECTION("setup a byt by byte writer again not changes anything")
    {
      writer.setSettings(settings);

      REQUIRE( writer.impl() != nullptr );
      CHECK( writer.impl()->isByteByByteWriter() );
    }

    SECTION("change to a direct writer works")
    {
      writer.setSettings( SendByteByByteSettings::disabled() );

      REQUIRE( writer.impl() != nullptr );
      CHECK( writer.impl()->isDirectWriter() );
    }
  }
}

TEST_CASE("write_Direct")
{
  QBuffer buffer;
  Writer writer(&buffer);
  REQUIRE( buffer.open(QBuffer::ReadWrite) );

  writer.setSettings( SendByteByByteSettings::disabled() );

  CHECK( writer.write("ABC") == 3 );
  CHECK( buffer.data() == "ABC" );
}

TEST_CASE("clear_canBeCalledWithoutAnImplementation")
{
  QBuffer buffer;
  TestWriter writer(&buffer);

  CHECK( writer.impl() == nullptr );

  writer.clear();
}
