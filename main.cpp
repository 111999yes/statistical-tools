#include <iostream>

#include "execute.h"

int main(){
    Data data;
    std::string input;
    StartApp(data);
    while(true){
        std::cout << ">";
        std::getline(std::cin, input);

        COMMAND cmd = Parser(input);
        Execute(cmd, input, data);
        
        if(cmd == COMMAND::EXIT) break;
    }
    EndApp(data);

    return 0;
}