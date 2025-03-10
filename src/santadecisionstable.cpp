
#include <osquery/logger/logger.h>
#include <osquery/sql/dynamic_table_row.h>

#include "santa.h"
#include "santadecisionstable.h"

osquery::TableColumns decisionTablesColumns() {
  // clang-format off
  return {
      std::make_tuple("timestamp",
                      osquery::TEXT_TYPE,
                      osquery::ColumnOptions::DEFAULT),

      std::make_tuple("path",
                      osquery::TEXT_TYPE,
                      osquery::ColumnOptions::DEFAULT),

      std::make_tuple("shasum",
                      osquery::TEXT_TYPE,
                      osquery::ColumnOptions::DEFAULT),

      std::make_tuple("reason",
                      osquery::TEXT_TYPE,
                      osquery::ColumnOptions::DEFAULT)
  };
  // clang-format on
}

osquery::TableRows decisionTablesGenerate(osquery::QueryContext& request,
                                          SantaDecisionType decision) {
  LogEntries log_entries;
  if (!scrapeSantaLog(log_entries, decision)) {
    return {};
  }

  osquery::TableRows result;
  for (const auto& entry : log_entries) {
    osquery::DynamicTableRowHolder row;
    row["timestamp"] = entry.timestamp;
    row["path"] = entry.application;
    row["shasum"] = entry.sha256;
    row["reason"] = entry.reason;

    result.emplace_back(row);
  }

  return result;
}

osquery::TableRows SantaAllowedDecisionsTablePlugin::generate(
    osquery::QueryContext& request) {
  auto rows = decisionTablesGenerate(request, decision);
  return rows;
}

osquery::TableRows SantaDeniedDecisionsTablePlugin::generate(
    osquery::QueryContext& request) {
  auto rows = decisionTablesGenerate(request, decision);
  return rows;
}

osquery::TableColumns SantaAllowedDecisionsTablePlugin::columns() const {
  return decisionTablesColumns();
}

osquery::TableColumns SantaDeniedDecisionsTablePlugin::columns() const {
  return decisionTablesColumns();
}
