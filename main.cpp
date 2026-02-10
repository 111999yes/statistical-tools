#include <iostream>

#include "app.h"

int main(){
    Data data;
    History history;
    StartApp(data);
    RunApp(data, history);
    EndApp(data);
    std::cout << history << std::endl;
    return 0;
}