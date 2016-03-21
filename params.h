#ifndef PARAMS_H
#define	PARAMS_H

#include "program.h"
#include <unistd.h>

string AppPath() {
    char path[255];
    return (getcwd(path, 255) ? std::string(path) : "");
}

enum Param {
    param_none,
    param_version,
    param_help,
    param_name,
    param_path,
    param_example,
    param_print,
    param_extra,
    param_output,
    param_testrun,
    param_retention,
    param_square
};

// uses this
Param GetParam(char* value) {
    string s = value;
    if (s == "--help")                return param_help;
    if (s == "--version")             return param_version;
    if (s == "--name")                return param_name;
    if (s == "--path")                return param_path;
    if (s == "--example")             return param_example;
    if (s == "--output")              return param_output;
    if (s.substr(0, 8) == "--square") return param_square;
    if (s == "-retention")            return param_retention;
    if (s == "-testrun")              return param_testrun;
    if (s == "-print")                return param_print;
    if (s == "-extra")                return param_extra;
    //std::cout << "No such parameter " << s << std::endl;
    return param_none;
}

void PrintHelp() {
    std::cout << "Usage:\t" << program_name << " [ARGUMENT] CONFIG\t"
            << "Run the program with current settings" << std::endl;
    std::cout << "\t" << program_name << " --help\t\t"
            << "Display this help and exit" << std::endl;
    std::cout << "\t" << program_name << " --version\t\t"
            << "Output version information and exit" << std::endl;
    std::cout << "\t" << program_name << " --name\t\t"
            << "Display program name and exit" << std::endl;
    std::cout << "\t" << program_name << " --path\t\t"
            << "Display program path and exit" << std::endl;
    std::cout << "\t" << program_name << " --example\t\t"
            << "Generate example of configuration file and exit" << std::endl;
    std::cout << "\t" << program_name << " --output filename\t"
            << "Print half-life in output file and exit" << std::endl;
    std::cout << "\t" << program_name << " --squareNx-Ny-Nz filename\t"
            << "Print surface square in output file and exit" << std::endl;
    std::cout << std::endl;
    std::cout << "\t" << program_name << " [filename]\t\t"
            << "Use filename configuration file" << std::endl;
    std::cout << std::endl;
    std::cout << "\t" << program_name << " [] -extra\t\t"
            << "Use express database out" << std::endl;
    std::cout << "\t" << program_name << " [] -retention\t"
            << "Use retention out" << std::endl;
    std::cout << "\t" << program_name << " [] -print\t\t"
            << "Print field parameters" << std::endl;
    std::cout << "\t" << program_name << " -testrun\t\t"
            << "Run test calculation" << std::endl;
}

void PrintVersion() {
    std::cout << program_name << "-" << program_version << std::endl;
}

#endif	/* PARAMS_H */
