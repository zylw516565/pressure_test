#!/bin/sh

# set -x

Help()
{
  # Display Help
  echo "Usage: $0     :build only"
  echo "Usage: $0 tar :build and creat a tar archive"
  echo ""
}

Help
SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-./build}
BUILD_TYPE=${BUILD_TYPE:-release}
INSTALL_DIR=${INSTALL_DIR:-./${BUILD_TYPE}-install-cpp11}
CXX=${CXX:-g++}

CRYPTO_LIB=libcrypto.so.1.0.2k
SSL_LIB=libssl.so.1.0.2k

# ln -sf $SOURCE_DIR/thirdparty/openssl/lib/linux/$CRYPTO_LIB \
# $SOURCE_DIR/thirdparty/openssl/lib/linux/libcrypto.so

# ln -sf $SOURCE_DIR/thirdparty/openssl/lib/linux/$SSL_LIB \
# $SOURCE_DIR/thirdparty/openssl/lib/linux/libssl.so

# build
mkdir -p $BUILD_DIR/$BUILD_TYPE-cpp11 \
  && cd $BUILD_DIR/$BUILD_TYPE-cpp11 \
  && cmake \
           -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
           -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
           -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
           $SOURCE_DIR \
  && make $*

TARGET_DIR=$SOURCE_DIR/bin
mkdir -p $TARGET_DIR
#copy binary
cp -f PressureTest $TARGET_DIR

#copy start script, library and readme
cd $SOURCE_DIR
chmod +x $TARGET_DIR/run.sh
cp $SOURCE_DIR/src/thirdparty/google/protobuf/lib/libprotobuf.so $TARGET_DIR/libprotobuf.so.9
cp $SOURCE_DIR/src/thirdparty/openssl/lib/linux/$CRYPTO_LIB  $SOURCE_DIR/src/thirdparty/openssl/lib/linux/$SSL_LIB $TARGET_DIR

Tar()
(
  cd $SOURCE_DIR
  tar -czf PressureTest.tar.gz ./bin
)

case $# in
  0 )
    ;;
  1 )
    Tar
    ;;
  * ) Help && exit 1
esac



# Use the following command to run all the unit tests
# at the dir $BUILD_DIR/$BUILD_TYPE :
# CTEST_OUTPUT_ON_FAILURE=TRUE make test

# cd $SOURCE_DIR && doxygen