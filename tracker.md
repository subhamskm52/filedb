# FileDB MVP Roadmap

> **Goal:** Build a lightweight C++ library that lets users import local files into an embedded SQLite database, query them with SQL, and export the results.

---

# Milestone 1 - Database Layer

## Goal

Build a clean wrapper around SQLite.

### Features

* [ ] Open a database
* [ ] Close a database
* [ ] Create an in-memory database
* [ ] Create a database on disk
* [ ] Execute SQL statements
* [ ] Execute prepared statements
* [ ] Execute transactions
* [ ] Return query results
* [ ] Handle SQLite errors
* [ ] Expose a clean C++ API

---

# Milestone 2 - Schema Management

## Goal

Allow FileDB to create and manage tables.

### Features

* [ ] Create tables
* [ ] Drop tables
* [ ] Rename tables
* [ ] List tables
* [ ] Get table schema
* [ ] Detect if a table exists
* [ ] Clear table data

---

# Milestone 3 - CSV Import

## Goal

Convert CSV files into SQLite tables.

### Features

* [ ] Read CSV files
* [ ] Detect delimiter
* [ ] Detect header row
* [ ] Infer column types
* [ ] Create SQLite table automatically
* [ ] Bulk insert rows
* [ ] Handle malformed rows
* [ ] Import very large CSV files

---

# Milestone 4 - JSON Import

## Goal

Import JSON documents.

### Features

* [ ] Import JSON arrays
* [ ] Import JSON objects
* [ ] Flatten nested objects
* [ ] Create SQLite tables
* [ ] Bulk insert data

---

# Milestone 5 - Query Engine

## Goal

Run SQL against imported files.

### Features

* [ ] Execute SELECT queries
* [ ] Execute INSERT queries
* [ ] Execute UPDATE queries
* [ ] Execute DELETE queries
* [ ] Execute DDL statements
* [ ] Return query results
* [ ] Return execution statistics

---

# Milestone 6 - Result API

## Goal

Represent SQL results in C++.

### Features

* [ ] QueryResult object
* [ ] Iterate rows
* [ ] Access columns
* [ ] Access values by name
* [ ] Access values by index
* [ ] Column metadata
* [ ] Row count

---

# Milestone 7 - Export

## Goal

Save query results.

### Features

* [ ] Export to CSV
* [ ] Export to JSON
* [ ] Export complete tables
* [ ] Export arbitrary query results

---

# Milestone 8 - Workspace

## Goal

Manage imported files.

### Features

* [ ] Import multiple files
* [ ] Associate files with tables
* [ ] Remove imported tables
* [ ] Refresh imported files
* [ ] List imported datasets

---

# Milestone 9 - Convenience API

## Goal

Provide a simple developer experience.

### Features

* [ ] Import file with one function
* [ ] Execute SQL with one function
* [ ] Export results with one function
* [ ] Get table information
* [ ] Preview table data

---

# Milestone 10 - Performance

## Goal

Handle large datasets efficiently.

### Features

* [ ] Batch inserts
* [ ] Prepared statements
* [ ] Streaming CSV import
* [ ] Progress callbacks
* [ ] Transaction optimization

---

# Milestone 11 - Reliability

## Goal

Make FileDB production ready.

### Features

* [ ] Error handling
* [ ] Logging
* [ ] Unit tests
* [ ] Integration tests
* [ ] Benchmarks

---

# Future

## Additional Importers

* [ ] Excel
* [ ] SQLite
* [ ] Parquet
* [ ] XML
* [ ] YAML

---

## Additional Exporters

* [ ] Excel
* [ ] Parquet

---

## AI

* [ ] Natural language → SQL
* [ ] Query explanation
* [ ] Join suggestions

---

## Connectors

* [ ] PostgreSQL
* [ ] MySQL
* [ ] MongoDB

---

## GUI

* [ ] File explorer
* [ ] SQL editor
* [ ] Table viewer
* [ ] Query history
* [ ] Export wizard
