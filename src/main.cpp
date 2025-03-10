// Description: The main entry point for the Santa extension
#include <osquery/core/system.h>
#include <osquery/sdk/sdk.h>

// Include the Santa table implementations
#include "santarulestable.h"
#include "santadecisionstable.h"

using namespace osquery;

// Register the tables with osquery
REGISTER_EXTERNAL(SantaRulesTablePlugin, "table", "santa_rules");
REGISTER_EXTERNAL(SantaAllowedDecisionsTablePlugin, "table", "santa_allowed");
REGISTER_EXTERNAL(SantaDeniedDecisionsTablePlugin, "table", "santa_denied");

int main(int argc, char* argv[]) {
  // This extension is meant to be registered with osqueryi or osqueryd.
  osquery::Initializer runner(argc, argv, ToolType::EXTENSION);

  // Start the extension - this communicates with the osquery process
  auto status = startExtension("santa", "0.1.0");
  if (!status.ok()) {
    LOG(ERROR) << status.getMessage();
    runner.requestShutdown(status.getCode());
  }

  // Finally wait for a signal / interrupt to shutdown.
  runner.waitForShutdown();
  return runner.shutdown(0);
}
