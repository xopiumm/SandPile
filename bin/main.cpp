#include "lib/parse.h"
#include "lib/pile.h"
#include "lib/image.h"

int main(const int argc, char* argv[]) {
    Arguments arguments;
    Field field;
    ParseArguments(argc, argv, arguments);
    GenerateModel(arguments);

    EXIT_SUCCESS;
}