from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake

# This recipe is only to install dependencies to build MdtTerminal
# The recipes to create packages are in packaging/conan/ subfolder
class MdtTerminalConan(ConanFile):
  name = "mdtterminal"
  license = "LGPL-3.0-or-later"
  url = "https://gitlab.com/scandyna/mdtterminal"
  description = "Terminal to experiment with some devices using some ports, like serial port."
  settings = "os", "compiler", "build_type", "arch"
  options = {
    "shared": [True, False],
    "enable_serialport_userspace_usb_support": [True, False]
  }
  default_options = {
    "shared": True,
    "enable_serialport_userspace_usb_support": True
  }
  generators = "CMakeDeps", "VirtualBuildEnv"

  def configure(self):
    if self.settings.os == "Windows":
      self.options.enable_serialport_userspace_usb_support = False

  def requirements(self):
    self.requires("qt/6.8.3")
    self.requires("mdtitemmodel/0.0.7@scandyna/testing")
    if self.options.enable_serialport_userspace_usb_support:
      self.requires("libusb/1.0.29")

  def build_requirements(self):
    self.test_requires("catch2/2.13.10")
    self.test_requires("mdtcmakemodules/0.22.0@scandyna/testing")

  def generate(self):
    tc = CMakeToolchain(self)
    if self.options.enable_serialport_userspace_usb_support:
      tc.variables["ENABLE_SERIALPORT_USERSPACE_USB_SUPPORT"] = "ON"
    else:
      tc.variables["ENABLE_SERIALPORT_USERSPACE_USB_SUPPORT"] = "OFF"
    tc.generate()
