//#include <iostream>
//#include <mathematica++/mathematica++.h>
//
//using namespace mathematica;
//
//int main(){
//    connector shell;
//    if(shell.connected()){
//        std::cout << "connected to Mathematica !!" << std::endl;
//    }
//    
//    return 0;
//}


#include <iostream>
#include <mathematica++/mathematica++.h>

using namespace mathematica;

MATHEMATICA_DECLARE(Divisors)

// Declare Mathematica functions 
MATHEMATICA_DECLARE(Table)
MATHEMATICA_DECLARE(Mod)
MATHEMATICA_DECLARE(Dot)

MATHEMATICA_DECLARE(Det)
MATHEMATICA_DECLARE(Print)

int main(){
    connector shell;
    if(!shell.connected()){
        std::cout << "Failed to connect to Mathematica !!" << std::endl;
        return 1;
    }
    
    value result;
    
    shell << Divisors(1729);
    shell >> result;
    
    std::cout << result << std::endl;
    
    typedef std::vector<int> divisors_type;
    divisors_type divisors;
    
    divisors = cast<divisors_type>(result);
    
    for(int n: divisors){
        std::cout << n << std::endl;
    }
	

    // Declare symbols
    mathematica::symbol i("i");
    mathematica::symbol j("j");
                                                                                 
    // declare variable to contain mathematica output                        
    mathematica::value determinant;                                          
    
    // create mathematica constructs
    mathematica::m mata = Table(Mod(i + j, 2), List(i, 1, 2), List(j, 1, 2));
    mathematica::m matb = Table(Mod(i + j, 3), List(i, 1, 2), List(j, 1, 2));
    mathematica::m matc = Dot(mata, matb);
    mathematica::m matd = Det(matc);
   
    mathematica::m testl = Table(10*i + j , List(i,1,3), List(j,1,3));
    mathematica::m matl  = Det(testl);

    // Execute mathematica constructs and fetch the response
    shell << matd;
    shell >> determinant;
    
    mathematica::value value2;
    shell << matl;
    shell >> value2;
    
    std::cout << value2 << std::endl;

    // determinant can be converted to C++ machine sized types
    std::cout << determinant << std::endl; // Prints -2
    return 0;
}
