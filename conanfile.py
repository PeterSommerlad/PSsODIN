import os

from conans import ConanFile, tools


class PSsODINConan(ConanFile):
    name = "pssodin"
    version = "0.1"
    license = "MIT license"
    author = "Peter Sommerlad peter.cpp@sommerlad.ch"
    url = "https://github.com/PeterSommerlad/PSsODIN"
    description = "A single header library for overflow detecting integers"
    topics = ("C++", "MISRA-C++ compliance", "Safe C++")
    no_copy_source = True
    exports_sources = "include/*"
    # No settings/options are necessary, this is header only

    def source(self):
         '''retrieval of the source code here. Remember you can also put the code
         in the folder and use exports instead of retrieving it with this
         source() method
         '''
         self.run("git clone https://github.com/PeterSommerlad/PSsODIN.git") 

    def package(self):
        self.copy("*.h")

    def package_id(self):
        self.info.header_only()
