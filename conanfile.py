from conan import ConanFile
from conan.tools.files import copy


class PSsODINConan(ConanFile):
    name = "pssodin"
    version = "0.1"
    exports_sources = "include/*"
    no_copy_source = True
    license = "MIT license"
    author = "Peter Sommerlad peter.cpp@sommerlad.ch"
    url = "https://github.com/PeterSommerlad/PSsODIN"
    description = "A single header library for overflow detecting integers"
    topics = ("C++", "MISRA-C++ compliance", "Safe C++")
    # No settings/options are necessary, this is header only


    def package(self):
        copy(self,"*.h", self.source_folder, self.package_folder)

    def package_info(self):
        # For header-only packages, libdirs and bindirs are not used
        # so it's necessary to set those as empty.
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []