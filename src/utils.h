
#pragma once

#include <string>
#include <vector>

struct ProcessOutput final {
  std::string std_output;
  std::string std_error;
  int exit_code;
};

bool ExecuteProcess(ProcessOutput& output,
                    const std::string& path,
                    const std::vector<std::string>& args);
