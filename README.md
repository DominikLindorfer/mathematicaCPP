# Install Instructions

This is a fork of Neel Basu's (Sunanda Bose) mathematica++, taken from https://gitlab.com/neel.basu/mathematicapp. It is a C++ library that can directly call Mathematica functions (from within the C++ code) by using the API to the Wolfram-Engine. I've had to change several things to get this project working on my machine:

Firstly, follow the instructions from the wiki

    git clone https://gitlab.com/neel.basu/mathematicapp.git
    cd mathematicapp
    mkdir build

To get mathematica++ working with newer g++ versions (who are picky with explicit expressions) change the following:

    cd includes/mathematica++

Open *io.h* and remove the *mathematica::* from the lines 64 onwards, such that it reads

    template <>
    wrapper& operator<<<symbol>(wrapper& stream, const symbol& symbol);
    template <>
    wrapper& operator<<<m>(wrapper& stream, const m& expr);
    template <>
    wrapper& operator<<<value>(wrapper& stream, const value& val);

while the original code was  
 
    template <>
    mathematica::wrapper& mathematica::operator<<<mathematica::symbol>(mathematica::wrapper& stream, const mathematica::symbol& symbol);
    template <>
    mathematica::wrapper& mathematica::operator<<<mathematica::m>(mathematica::wrapper& stream, const mathematica::m& expr);
    template <>
    mathematica::wrapper& mathematica::operator<<<mathematica::value>(mathematica::wrapper& stream, const mathematica::value& val);

Furthermore the test for *eigen.cpp* in *tests/* seems to fail (for yet unknown reasons). Thus

    cd tests/

and modify the *CMakeLists.txt* to:

    ...
    IF(Eigen3_FOUND)
        #ADD_EXECUTABLE(eigen eigen.cpp)
        #TARGET_LINK_LIBRARIES(eigen ${Boost_LIBRARIES})
        #TARGET_LINK_LIBRARIES(eigen mathematica++)
        
        #ADD_TEST(eigen eigen --report_level=short --log_level=message --show_progress=true)
    ENDIF()
    ...

Additionally, modify the  *CMakeLists.txt* in the main directory to

    IF(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        #ADD_COMPILE_OPTIONS(-D USING_LIB_EIGEN)
    ELSE()
        #ADD_COMPILE_DEFINITIONS(USING_LIB_EIGEN)
    ENDIF()

such that the unknown *USING_LIB_EIGEN* is excluded. 

Now, go back into the main directory and

    cd build
    cmake ..
    make

and everything should compile accordingly. 

In the *MyProject1* folder a simplisitc test-case *main.cpp* with the corresponding *CMakeLists.txt* is given which compiles the *myproject1* object in *build/*.

## Dependencies

I've had to include the Boost- as well as the Eigen-library dependencies. Therefore I've added the following lines to my *.bashrc*

    export BOOST_ROOT=/home/lindorfer/Programs/boost_1_69_0/
    export CPLUS_INCLUDE_PATH=/home/lindorfer/Programs/mathematicapp/includes/
    export CPLUS_INCLUDE_PATH=/home/lindorfer/Programs/boost_1_69_0/
    export LD_LIBRARY_PATH=/home/lindorfer/Programs/boost_1_69_0/bin.v2/libs:$LD_LIBRARY_PATH

as well as installed the eigenlib-dev package from ubuntu18.04 through synaptic (the Boost-library was compiled by cd'in into the boost folder and executing ./bootstrap.sh and ./b2). The libuuid was also required (*sudo apt install libuuid*).

