from conans import ConanFile, CMake, tools

class MinimalDaemon(ConanFile):
    
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"
    options = {"shared": [True, False],
               "port": ["mingw-test", "raspberrypi"]}
    default_options = {"shared": True,
                       "port": "raspberrypi"}
    

    def build(self):

        cmake = CMake(self)
        cmake.definitions["PORT"] = self.options.port
        cmake.configure()
        cmake.build()

