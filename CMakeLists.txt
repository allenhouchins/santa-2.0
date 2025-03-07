# Santa Extension for osquery
project(santa)

# Set source files
set(SOURCES
  src/santa.cpp
  src/santarulestable.cpp
  src/santadecisionstable.cpp
  src/utils.cpp
  src/main.cpp
)

# Add the extension using osquery's extension macro
addOsqueryExtension(external_extension_santa ${SOURCES})

# Add any required include directories
target_include_directories(external_extension_santa PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link with required libraries
target_link_libraries(external_extension_santa PRIVATE
  thirdparty_boost
)
