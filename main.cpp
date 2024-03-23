#include <iostream>
#include <assert.h>
#include <unistd.h>
#include "App/App.h"


int main(int argc, char *argv[])
{

    App::App app(3, 1);

    app.Start();

    auto count = 0;
    while(count < 25) {
        count++;

        usleep(1000000);
    }

    return 0;
}