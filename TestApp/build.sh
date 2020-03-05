if [[ "$OSTYPE" == "linux-gnu" ]]; then
	gen="Unix Makefiles"
	com="make"
elif [[ "$OSTYPE" == "msys" ]]; then
	gen="Ninja"
	com="ninja"
fi

cd ../Engine/
cmake -DCMAKE_BUILD_TYPE=Debug -G "$gen" -B build
cd build/
$com
cd ../../TestApp/
cmake -DCMAKE_BUILD_TYPE=Debug -G "$gen" -B build
cd build/
$com
cd ../

if [[ "$OSTYPE" == "linux-gnu" ]]; then
	cp ../Engine/build/debug/yeno.dll build/debug/
	cp ../Engine/vendor/SDL2/lib/x64/SDL2.dll build/debug/
	cp ../Engine/vendor/LauJit/lib/x64/lua51.dll build/debug/
fi
