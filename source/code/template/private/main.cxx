#include <iostream>
#include <CLI/CLI.hpp>

int main(int argc, char** argv)
{
    CLI::App app{"App description"};

    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");

    CLI11_PARSE(app, argc, argv);
    std::cout << "Hello IceShard!" << std::endl;
    return 0;
}
