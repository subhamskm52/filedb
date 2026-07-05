# FileDB

FileDB is a modern C++ library for loading, querying, transforming, and exporting structured data.

It enables applications to work with data from multiple file formats—including CSV, Excel, JSON, and others—through a unified interface. FileDB imports data into an embedded SQLite database, allowing developers and users to perform SQL queries, join datasets, filter records, aggregate data, and transform it efficiently.

Designed to compile to WebAssembly, FileDB can power web applications built with frameworks such as React, enabling fast, in-browser data processing without requiring a backend. After manipulating data, it can be exported to multiple file formats, making FileDB suitable for ETL workflows, data analysis tools, and low-code data transformation applications.

## Vision

Build a lightweight, embeddable data engine that enables developers to:

* Import data from multiple structured file formats.
* Query data using SQL.
* Join and transform datasets from different sources.
* Infer and customize column data types.
* Export transformed data to multiple file formats.
* Run entirely in the browser via WebAssembly.
* Prioritize data privacy by processing data locally whenever possible, ensuring users retain control of their data without needing to upload it to external servers.
