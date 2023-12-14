# Install vcpkg:
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat

# Install required libs:
.\vcpkg\vcpkg install libpqxx
.\vcpkg\vcpkg install gtest

# To get path for
# cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake:
# Ex.: cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/Users/palchukovsky/Desktop/Projects/otus/webinar/vcpkg/scripts/buildsystems/vcpkg.cmake
.\vcpkg\vcpkg integrate install

# Start PostgreSQL and MongoDB databases:
docker-compose --file .\db\docker-compose.yml up -d