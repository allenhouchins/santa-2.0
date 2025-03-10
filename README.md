# A Refactored Santa Extension for osquery

 Somehow, this works 🤷🏼🎅🏼🦌

This extension allows osquery to interact with Santa binary authorization system for macOS.

The extension uses osquery's SDK headers and libraries.
The extension cannot be built standalone without the osquery source code. The build process integrates with osquery's build system to properly link against the required dependencies and produce a compatible extension binary.

## Features

- Query Santa rules through the `santa_rules` table
- Query allowed decisions through the `santa_allowed` table
- Query denied decisions through the `santa_denied` table

## Prerequisites

- Follow [the guide](https://osquery.readthedocs.io/en/stable/development/building/) listed on osquery's official site and install necessary prerequisites.

## Setting up to build

1. Clone the osquery repository: `git clone https://github.com/osquery/osquery.git`
2. Create the extension directory: `mkdir -p osquery/external/extension_santa/src`
3. Copy contents of this repo's `/src` directory into `osquery/external/extension_santa/src`
4. Copy the CMakeLists.txt file to `osquery/external/extension_santa/`

The file structure should look like such:

```
osquery/
└── external/
    └── extension_santa/
        ├── CMakeLists.txt
        └── src/
            ├── main.cpp 
            ├── santa.cpp   # Modified to remove boost::iostreams dependency
            ├── santa.h
            ├── santadecisionstable.cpp
            ├── santadecisionstable.h
            ├── santarulestable.cpp
            ├── santarulestable.h
            ├── utils.cpp   # Modified to remove boost::process dependency
            └── utils.h
```

## Building

1. Make sure you're in the root directory of the osquery repository
```
cd ~/src/osquery
```

2. Create and enter a build directory
```
mkdir -p build
cd build
```

3. Configure build with CMake
```
cmake ..
```

4. Build the Claus
```
cmake --build . --target santa
```

You'll find the built binary at:
`/src/osquery/build/external/extension_santa/santa.ext`

To run locally with Fleet, `sudo orbit shell -- --extension santa.ext --allow-unsafe`

or with standard osqueryi:
`osqueryi --extension=/path/to/santa.ext`

## Limitations (Determined to make these work 🧐)

- The extension can read Santa rules, but modifying rules through the extension has limitations due to how Santa locks its database

## Modifications from Original Code

This repository contains a modified version of the Santa extension for osquery originally developed by Trail of Bits, Inc. (https://github.com/trailofbits/osquery-extensions).

Key modifications include:
- Removed dependency on boost::iostreams, replacing gzip handling with zlib
- Removed dependency on boost::process, replacing popen-based implementation
- Updated SQL queries to work with newer Santa database schema
- Added a main.cpp entry point - proper entry point file that registers the extension tables with osquery
- Fixed table registration - Added the proper REGISTER_EXTERNAL macros
- Added debugging and logging (may be removed at some point)

All modifications maintain the original Apache 2.0 license.