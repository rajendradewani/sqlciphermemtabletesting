#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <Windows.h>

#ifdef USE_SQLCIPHER
#include "sqlite_headers\SQLCipher\sqlite3.h"
#endif
#ifdef USE_SQLITE
#include "sqlite_headers\SQLite\sqlite3.h"
#endif

using namespace std;

#define RETRYLOOPCOUNT	1000

#ifdef USE_SQLCIPHER
#pragma comment(lib, "sqlite_libs\\SQLCipher\\sqlite3.lib")
#endif
#ifdef USE_SQLITE
#pragma comment(lib, "sqlite_libs\\SQLite\\sqlite3.lib")
#endif

class SQLite
{
	long lRC;
	long lTransactionCount;
	sqlite3 *sqlHandle;
	sqlite3 *sqlMemoryHandle;
	sqlite3_stmt *sqlStmt;
	sqlite3_stmt *sqlTableOneRecordStmt;
	char szPassword[128];
	char szMasterQuery[128];
	char szPragmaQuery[128];
	char szSalesReceiptQuery[2048];
	char szInvoiceQuery[2048];

public:
	SQLite(void);
	~SQLite(void);
	bool Open(char* szPath);
	bool Close(bool memory);
	bool SetEncryptionKey(char *szKey);
	bool ApplyStanardQuery(char *szStandardQuery); /* As Like Pragma query or master query */
	bool BeginTransaction();
	bool CommitTransaction();
	bool OpenMemory(char* szPath, char* szLongQuery, char* szShortQuery, char *szTableName, char *szKey);
	bool CloseOneRecord();
	bool OpenOneRecord(char* szTableName, char* szShortQuery, long rowID);
	bool GetColumnText(LONG lCol, char* sText, LONG lMaxTextLen);
	long ExecuteNonQuery(char *szQuery);
	long ExecuteNonQueryFromMemory(char *szQuery);
	long CountSQLValue(char *szQuery);
	void PrintError(char *functionName, sqlite3*);
};


