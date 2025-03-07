
#include "utils.h"
#include <array>
#include <cstdio>
#include <memory>
#include <string>
#include <osquery/logger/logger.h>

bool ExecuteProcess(ProcessOutput& output,
  const std::string& path,
  const std::vector<std::string>& args) {
output = {};

try {
// Build command string
std::string cmd = path;
for (const auto& arg : args) {
cmd += " \"" + arg + "\"";
}

// Create pipe for reading output
std::array<char, 128> buffer;
std::string result;

std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
if (!pipe) {
return false;
}

// Read output
while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
result += buffer.data();
}

// Get exit code
int status = pclose(pipe.release());
output.std_output = result;
output.exit_code = WEXITSTATUS(status);

return true;
} catch (...) {
return false;
}
}
