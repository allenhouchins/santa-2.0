/*
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
