
:: clears CMake build cache
:: useful for clean builds

pushd "%~dp0.."

rmdir /s /q build

popd
