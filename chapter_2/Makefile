PROJECT_NAME = $(notdir $(CURDIR))
release = release
debug = "debug"

ifeq ($(config), release)
	config = Release
else
	config = Debug
endif

.PHONY: dir_make
dir_make:
	mkdir build 2>nul || echo build already exists

.PHONY: conan_install
conan_install: dir_make
	cd build && \
	conan install .. -s build_type=Release --build=missing && \
	conan install .. -s build_type=Debug --build=missing

.PHONY: format
format:
	clang-format src/**/*.cpp src/**/*.h test/**/*.cpp -i

.PHONY: build-test
build-test: conan_install
	cd build && \
	cmake .. -DCMAKE_CONFIGURATION_TYPES=Debug;Release -DBUILD_APP=OFF -DBUILD_TEST=ON -DBUILD_DOC=OFF && \
	cmake --build .

.PHONY: build-app
build-app: conan_install
	cd build && \
	cmake .. -DCMAKE_CONFIGURATION_TYPES=Debug;Release -DBUILD_APP=ON -DBUILD_TEST=OFF -DBUILD_DOC=OFF && \
	cmake --build .

.PHONY: build-doc
build-doc: dir_make
	cd build && \
	cmake .. -DBUILD_APP=OFF -DBUILD_TEST=OFF -DBUILD_DOC=ON && \
	cmake --build .

.PHONY: run-test
run-test:
	cd build && \
	bin\$(PROJECT_NAME)_test.exe

.PHONY: test
test: build-test run-test

.PHONY: run-app
run-app:
	cd build && \
	Debug\$(PROJECT_NAME)_app.exe

.PHONY: app
app: build-app run-app

.PHONY: doc
doc: build-doc
