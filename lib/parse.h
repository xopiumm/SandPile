#pragma once
#include <iostream>
#include <cstdint>
#include <filesystem>
#include <cstring>

struct Arguments {
    const char* input_path = nullptr;
    const char* output_path = nullptr;
    int64_t iterations = -1;
    int64_t frequency = -1;
};

struct ConstArguments {
    static constexpr const char* kLongInputArgument = "--input=";
    static constexpr const char* kLongOutputArgument = "--output=";
    static constexpr const char* kLongIterationsArgument = "--max-iter=";
    static constexpr const char* kLongFrequencyArgument = "--freq=";
    static constexpr const char* kShortInputArgument = "-i";
    static constexpr const char* kShortOutputArgument = "-o";
    static constexpr const char* kShortIterationsArgument = "-m";
    static constexpr const char* kShortFrequencyArgument = "-f";
};

enum class ErrorCode {
    InvalidInputPath,
    InvalidOutputPath,
    InvalidIterations,
    InvalidFrequency,
    TooManyArguments,
    CanNotOpenTheFile
};

void ParseArguments(int argc, char* argv[], Arguments& arguments);
bool AreParametersCorrect(Arguments& arguments);
void ShowError(ErrorCode error);