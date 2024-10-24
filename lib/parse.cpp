#include "parse.h"

void ShowError(ErrorCode error) {
    switch (error) {
        case ErrorCode::InvalidInputPath:
            std::cerr << "\nError: Invalid Input Path\nTry Again\n";
            break;
        case ErrorCode::InvalidOutputPath:
            std::cerr << "\nError: Invalid Output Path\nTry Again\n";
            break;
        case ErrorCode::InvalidIterations:
            std::cerr << "\nError: Invalid Iterations\nTry Again\n";
            break;
        case ErrorCode::InvalidFrequency:
            std::cerr << "\nError: Invalid Frequency\nTry Again\n";
            break;
        case ErrorCode::TooManyArguments:
            std::cerr << "\nError: Too MAny Arguments\nTry Again\n";
            break;
        case ErrorCode::CanNotOpenTheFile:
            std::cerr << "\nError: Can Not Open The Input File\nTry Again\n";
            break;
    }
}

bool AreParametersCorrect(Arguments& arguments) {
    if (!std::filesystem::exists(arguments.input_path)) {
        ShowError(ErrorCode::InvalidInputPath);
        return false;

    } else if (!std::filesystem::exists(arguments.output_path)) {
        ShowError(ErrorCode::InvalidOutputPath);
        return false;

    } else if (arguments.iterations <= 0) {
        ShowError(ErrorCode::InvalidIterations);
        return false;

    } else if (arguments.frequency < 0) {
        ShowError(ErrorCode::InvalidFrequency);
        return false;
    }

    return true;
}

bool IsPrefix(const char* argument, const char* compare_to) {
    return std::strncmp(argument, compare_to, strlen(compare_to));
}

void ParseArguments(int argc, char* argv[], Arguments& arguments) {
    for (int i = 1; i < argc; ++i) {
        if ((IsPrefix(argv[i], ConstArguments::kShortInputArgument) == 0) && (i + 1 < argc))  {
            arguments.input_path = argv[++i];

        } else if ((IsPrefix(argv[i], ConstArguments::kLongInputArgument) == 0)  && (i + 1 < argc)) {
            arguments.input_path = argv[i] + strlen(ConstArguments::kLongInputArgument);

        } else if ((IsPrefix(argv[i], ConstArguments::kShortOutputArgument) == 0)  && (i + 1 < argc)) {
            arguments.output_path = argv[++i];

        } else if ((IsPrefix(argv[i], ConstArguments::kLongOutputArgument) == 0)  && (i + 1 < argc)) {
            arguments.output_path = argv[i] + strlen(ConstArguments::kLongOutputArgument);

        } else if (IsPrefix(argv[i], ConstArguments::kShortIterationsArgument) == 0) {
            arguments.iterations = std::strtoll(argv[++i], nullptr,10);

        } else if (IsPrefix(argv[i], ConstArguments::kLongIterationsArgument) == 0) {
            arguments.iterations = std::strtoll(argv[i] + strlen(ConstArguments::kLongIterationsArgument), nullptr, 10);

        } else if (IsPrefix(argv[i], ConstArguments::kShortFrequencyArgument) == 0) {
            arguments.frequency = std::strtoll(argv[++i], nullptr,10);

        }  else if (IsPrefix(argv[i], ConstArguments::kLongFrequencyArgument) == 0) {
            arguments.frequency = std::strtoll(argv[i] + strlen(ConstArguments::kLongFrequencyArgument), nullptr, 10);

        } else {
            ShowError(ErrorCode::TooManyArguments);
        }
    }
    if (!AreParametersCorrect(arguments)) {
        EXIT_FAILURE;
    }
}