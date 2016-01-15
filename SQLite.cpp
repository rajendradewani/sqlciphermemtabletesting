#include "SQLite.h"


SQLite::SQLite(void)
{
	lRC = 0;
	lTransactionCount = 0;

	sqlHandle = NULL;
	sqlStmt = NULL;
	sqlMemoryHandle = NULL;
	sqlTableOneRecordStmt = NULL;

	memset(szPassword, 0, sizeof(szPassword));
	memset(szMasterQuery, 0, sizeof(szMasterQuery));
	memset(szPragmaQuery, 0, sizeof(szPragmaQuery));

	strcpy(szPassword, "(åWöù¶(¤ôWÓýWfK0ÈWÅ¬ÿ¯Áx(¼9øe°üÇî©vò§©-¾ø©$óR©Þû¬R©­:7-[©Ü'Ýê„<WÞŸÚŠ³Î5Óøe°üÇî©vò§©-¾ø©$óR©Þû¬R©­:7-[©Ü'Ýê„<WÞŸÚŠ³Î5Ó");
	strcpy(szMasterQuery, "SELECT \"type\", \"tbl_name\" FROM \"SQLite_MASTER\"");
	strcpy(szPragmaQuery, "PRAGMA cache_size = 20000");
}


SQLite::~SQLite(void)
{

}

bool SQLite::Open(char* szPath)
{
	lRC = sqlite3_open((const char*)szPath, (sqlite3**)&sqlHandle);
	if(lRC != SQLITE_OK){
		PrintError("Open", sqlHandle);
		return FALSE;
	}
	return TRUE;
}

bool SQLite::Close(bool memory = FALSE)
{
	if(!memory){

		if(sqlHandle == NULL){
			return FALSE;
		}

		lRC = sqlite3_close(sqlHandle);
		if(lRC != SQLITE_OK){
			PrintError("Close", sqlHandle);
			return FALSE;
		}

		sqlHandle = NULL;
	}
	else{
		if(sqlMemoryHandle == NULL){
			return FALSE;
		}

		lRC = sqlite3_close(sqlMemoryHandle);
		if(lRC != SQLITE_OK){
			PrintError("Close", sqlMemoryHandle);
			return FALSE;
		}
		sqlMemoryHandle = NULL;
	}

	return TRUE;
}

bool SQLite::SetEncryptionKey(char* szKey = NULL)
{
	if(sqlHandle == NULL){
		return FALSE;
	}

#ifdef USE_SQLCIPHER
	if(szKey){
		lRC = sqlite3_key(sqlHandle, (const void*)szKey, strlen(szKey));
	}
	else{
		lRC = sqlite3_key(sqlHandle, (const void*)szPassword, strlen(szPassword));
	}
	if(lRC != SQLITE_OK){
		PrintError("SetEncryptionKey", sqlHandle);
		Close(TRUE);
		return FALSE;
	}
#endif
	return TRUE;
}

bool SQLite::ApplyStanardQuery(char *szStandardQuery = NULL)
{
	if(szStandardQuery){
		lRC = sqlite3_prepare(sqlHandle, (const char*)szStandardQuery, -1, (sqlite3_stmt**)&sqlStmt, NULL);
	}
	else{
		lRC = sqlite3_prepare(sqlHandle, (const char*)szPragmaQuery, -1, (sqlite3_stmt**)&sqlStmt, NULL);
	}

	if(sqlStmt == NULL){
		if(lRC != SQLITE_OK){
			PrintError("SetEncryptionKey", sqlHandle);
			Close();
			return FALSE;
		}
		return FALSE;
	}

	lRC = sqlite3_finalize(sqlStmt);
	if(lRC != SQLITE_OK){
		PrintError("SetEncryptionKey", sqlHandle);
		Close();
		return FALSE;
	}

	return TRUE;
}

bool SQLite::BeginTransaction()
{
	sqlite3	*hDBHandle = NULL;

	hDBHandle = (sqlite3 *) sqlHandle;
	if (hDBHandle == NULL) {
		return FALSE;
	}

	lTransactionCount++;
	if(lTransactionCount == 1){
		if(ExecuteNonQuery("BEGIN IMMEDIATE TRANSACTION") < 0){
			lTransactionCount = 0;
			return FALSE;
		}
	}

	return TRUE;
}

bool SQLite::CommitTransaction()
{
	sqlite3	*hDBHandle = NULL;

	hDBHandle = (sqlite3 *) sqlHandle;
	if (hDBHandle == NULL) {
		return FALSE;
	}

	lTransactionCount--;
	if(lTransactionCount == 0){
		if(ExecuteNonQuery("COMMIT TRANSACTION") < 0){
			lTransactionCount = 0;
			return FALSE;
		}
	}

	return TRUE;
}

bool SQLite::OpenMemory(char* szPath, char* szLongQuery, char* szShortQuery, char *szTableName, char *szKey = NULL){
	char szAttachQuery[2048] = "";
	char szQuery[512] = "";
	char szInsertSQL[16538] = "";
	sqlite3_stmt *tSQL3Stmt = NULL;

	lRC = sqlite3_open(":memory:", &sqlMemoryHandle);
	if(lRC != SQLITE_OK){
		PrintError("OpenMemory", sqlMemoryHandle);
		return FALSE;
	}

#ifdef USE_SQLCIPHER
	strcpy(szAttachQuery, "ATTACH DATABASE \"");
	strcat(szAttachQuery, szPath);
	strcat(szAttachQuery, "\" AS encrypted KEY \"");
	if(szKey){
		strcat(szAttachQuery, szKey);
	}else{
		strcat(szAttachQuery, szPassword);
	}
	strcat(szAttachQuery, "\";");

#endif
#ifdef USE_SQLITE
	strcpy(szAttachQuery, "ATTACH DATABASE \"");
	strcat(szAttachQuery, szPath);
	strcat(szAttachQuery, "\" AS \"FQBase\"");
#endif
	
	if(ExecuteNonQueryFromMemory(szAttachQuery) < 0){
		PrintError("OpenMemory", sqlMemoryHandle);
		return FALSE;
	}

	strcpy(szQuery, "PRAGMA cache_size = 20000");

	lRC = sqlite3_prepare(sqlMemoryHandle, szQuery, -1, &tSQL3Stmt, NULL);
	if(lRC != SQLITE_OK){
		PrintError("OpenMemory", sqlMemoryHandle);
		Close(TRUE);
		return FALSE;
	}

	if(tSQL3Stmt == NULL){
		PrintError("OpenMemory", sqlMemoryHandle);
		Close(TRUE);
		return FALSE;
	}

	lRC = sqlite3_finalize(tSQL3Stmt);
	if(lRC != SQLITE_OK){
		PrintError("OpenMemory", sqlMemoryHandle);
		Close(TRUE);
		return FALSE;
	}
	tSQL3Stmt = NULL;

	strcpy(szInsertSQL, "CREATE TABLE \"");
	strcat(szInsertSQL, szTableName);
	strcat(szInsertSQL, "\" AS ");
	strcat(szInsertSQL, szLongQuery);
	if(ExecuteNonQueryFromMemory(szInsertSQL) < 0){
		Close(TRUE);
		return FALSE;
	}

	memset(szInsertSQL, 0, sizeof(szInsertSQL));
#ifdef USE_SQLCIPHER
	strcpy(szInsertSQL, "DETACH DATABASE \"encrypted\"");
#endif
#ifdef USE_SQLITE
	strcpy(szInsertSQL, "DETACH DATABASE \"FQBase\"");
#endif

	if(ExecuteNonQueryFromMemory(szInsertSQL) < 0){
		Close(TRUE);
		return FALSE;
	}

	// send our short query
	memset(szInsertSQL, 0, sizeof(szInsertSQL));
	strcpy(szInsertSQL, szShortQuery);
	tSQL3Stmt = NULL;
	lRC = sqlite3_prepare(sqlMemoryHandle, szInsertSQL, -1, &tSQL3Stmt, NULL);
	if(lRC != SQLITE_OK){
		PrintError("OpenMemory", sqlMemoryHandle);
		Close(TRUE);
		return FALSE;
	}

	if(tSQL3Stmt == NULL){
		PrintError("OpenMemory", sqlMemoryHandle);
		Close(TRUE);
		return FALSE;
	}

	lRC = sqlite3_step(tSQL3Stmt);
	if(lRC == SQLITE_ROW){
		sqlTableOneRecordStmt = tSQL3Stmt;
		tSQL3Stmt = NULL;
		return TRUE;
	}
	else{
		PrintError("OpenMemory", sqlMemoryHandle);
		Close(TRUE);
		return FALSE;
	}
	return TRUE;
}

bool SQLite::CloseOneRecord()
{
	LONG			lRC = 0L;
	sqlite3_stmt	*tSQL3Stmt = NULL;
	sqlite3			*hOneSQLDBHandle = NULL;

	tSQL3Stmt = (sqlite3_stmt *)sqlTableOneRecordStmt;
	if(tSQL3Stmt == NULL){
		return FALSE;
	}

	lRC = sqlite3_finalize(tSQL3Stmt);
	sqlTableOneRecordStmt = NULL;
	return TRUE;
}

bool SQLite::OpenOneRecord(char* szTableName, char* szShortQuery, long rowID){
	LONG			lRC = 0L;
	LONG			lSizeOfInsertSQL = 0L;
	sqlite3_stmt	*tSQL3Stmt = NULL;
	sqlite3			*hDBHandle = NULL;
	char			szInsertSQL[4196] = "";
	char			szRowID[10] = "";
	LONG			lRetryCnt = 0L;

	hDBHandle = (sqlite3 *) sqlMemoryHandle;
	if (hDBHandle == NULL) {
		return(FALSE);
	}

	CloseOneRecord();

	strcpy(szInsertSQL, szShortQuery);
	sprintf(szRowID, "%ld", rowID);
	strcat(szInsertSQL, " WHERE \"ROWID\" = ");
	strcat(szInsertSQL, szRowID);

	while (lRetryCnt < RETRYLOOPCOUNT) {
		lRC = sqlite3_prepare((sqlite3 *) sqlMemoryHandle, (LPSTR) szInsertSQL, -1, &tSQL3Stmt, NULL);
		if ((lRC != SQLITE_OK) || (tSQL3Stmt == NULL)) {
			if (lRC != SQLITE_OK) {
				PrintError("OpenOneRecord", sqlMemoryHandle);
				return(FALSE);
			}
		}

		sqlTableOneRecordStmt = tSQL3Stmt;

		lRC = sqlite3_step (tSQL3Stmt);
		if ((lRC != SQLITE_SCHEMA) && (lRC != SQLITE_ERROR)) {
			break;
		}
		Sleep(10);
		lRC = sqlite3_finalize (tSQL3Stmt);
		tSQL3Stmt = NULL;
		sqlTableOneRecordStmt = tSQL3Stmt;
		lRetryCnt++;
	}
	if ((lRC != SQLITE_DONE) && (lRC != SQLITE_ROW)) {
		PrintError("OpenOneRecord", sqlMemoryHandle);
		lRC = sqlite3_finalize(tSQL3Stmt);
		tSQL3Stmt = NULL;

		sqlTableOneRecordStmt = tSQL3Stmt;

		if (lRC != SQLITE_OK) {
			PrintError("OpenOneRecord", sqlMemoryHandle);
		}
		return(FALSE);
	}
	if (lRC == SQLITE_ROW) {
		return(TRUE);
	}
	lRC = sqlite3_finalize(tSQL3Stmt);
	tSQL3Stmt = NULL;
	sqlTableOneRecordStmt = tSQL3Stmt;
	if (lRC != SQLITE_OK) {
		PrintError("OpenOneRecord", sqlMemoryHandle);
	}
	
	return FALSE;
}

bool SQLite::GetColumnText(LONG lCol, char* sText, LONG lMaxTextLen)
{
	sqlite3_stmt			*tSQL3Stmt = NULL;
	const unsigned char		*lpText = NULL;

	tSQL3Stmt = (sqlite3_stmt *) sqlTableOneRecordStmt;
	if(tSQL3Stmt == NULL){
		return FALSE;
	}

	if (sText != NULL) {
		strcpy(sText, "");
	}
	if ((sText != NULL) && (lMaxTextLen > 0)) {
		lpText = sqlite3_column_text(tSQL3Stmt, (int) lCol);
		if (lpText != NULL) {
			strncpy(sText, (char*)lpText, lMaxTextLen);
		}
	}
	return TRUE;
}

long SQLite::ExecuteNonQuery(char *szSQLString)
{
	LONG			lRC = 0L;
	sqlite3_stmt	*tSQL3Stmt = NULL;
	sqlite3			*hDBHandle = NULL;
	LONG			lRetryCnt = 0L;
	LONG			lCount = 0L;
	CHAR			sSQLStr[8];

	hDBHandle = (sqlite3 *) sqlHandle;
	if (hDBHandle == NULL) {
		return(FALSE);
	}

	lCount = -1L;
	lRetryCnt = 0L;
	while (lRetryCnt < RETRYLOOPCOUNT) {
		lCount = -1L;
		tSQL3Stmt = NULL;
		lRC = sqlite3_prepare(hDBHandle, szSQLString, -1, &tSQL3Stmt, NULL);
		if ((lRC != SQLITE_OK) || (tSQL3Stmt == NULL)) {
			if (lRC != SQLITE_OK) {
				PrintError("ExecuteNonQuery", hDBHandle);
				return(lCount);
			}
		}

		lRC = sqlite3_step(tSQL3Stmt);
		if ((lRC == SQLITE_LOCKED) || (lRC == SQLITE_BUSY) || (lRC == SQLITE_SCHEMA)) {
			Sleep(10);
			lRetryCnt++;
			lRC = sqlite3_finalize(tSQL3Stmt);
			tSQL3Stmt = NULL; 
			continue;
		}
		if ((lRC != SQLITE_OK) && (lRC != SQLITE_DONE)) {
			if (lRC != SQLITE_OK) {
				PrintError("ExecuteNonQuery", hDBHandle);
			}
			lRC = sqlite3_finalize (tSQL3Stmt);
			tSQL3Stmt = NULL; 
			return(lCount);
		}
		lRC = sqlite3_finalize(tSQL3Stmt);
		tSQL3Stmt = NULL; 
		if (lRC != SQLITE_OK) {
			PrintError("ExecuteNonQuery", hDBHandle);
			return(lCount);
		}
		strncpy(sSQLStr, szSQLString, sizeof(sSQLStr));
		lCount = (LONG) sqlite3_changes(hDBHandle);	
		if ((strcmpi(sSQLStr, "DELETE ") == 0) || (strcmpi(sSQLStr, "INSERT ") == 0) || (strcmpi(sSQLStr, "UPDATE ") == 0) || (strcmpi(sSQLStr, "REPLACE") == 0)) {
			
		}
		else {
			lCount = 0;
		}
		return(lCount);
	}
	return(lCount);
}

long SQLite::ExecuteNonQueryFromMemory(char *szSQLString)
{
	LONG			lRC = 0L;
	sqlite3_stmt	*tSQL3Stmt = NULL;
	sqlite3			*hDBHandle = NULL;
	LONG			lRetryCnt = 0L;
	LONG			lCount = 0L;
	CHAR			sSQLStr[8];

	hDBHandle = (sqlite3 *) sqlMemoryHandle;
	if (hDBHandle == NULL) {
		return(FALSE);
	}

	lCount = -1L;
	lRetryCnt = 0L;
	while (lRetryCnt < RETRYLOOPCOUNT) {
		lCount = -1L;
		tSQL3Stmt = NULL;
		lRC = sqlite3_prepare(hDBHandle, szSQLString, -1, &tSQL3Stmt, NULL);
		if ((lRC != SQLITE_OK) || (tSQL3Stmt == NULL)) {
			if (lRC != SQLITE_OK) {
				PrintError("ExecuteNonQueryFromMemory", hDBHandle);
				return(lCount);
			}
		}

		lRC = sqlite3_step(tSQL3Stmt);
		if ((lRC == SQLITE_LOCKED) || (lRC == SQLITE_BUSY) || (lRC == SQLITE_SCHEMA)) {
			Sleep(10);
			lRetryCnt++;
			lRC = sqlite3_finalize(tSQL3Stmt);
			tSQL3Stmt = NULL; 
			continue;
		}
		if ((lRC != SQLITE_OK) && (lRC != SQLITE_DONE)) {
			if (lRC != SQLITE_OK) {
				PrintError("ExecuteNonQueryFromMemory", hDBHandle);
			}
			lRC = sqlite3_finalize (tSQL3Stmt);
			tSQL3Stmt = NULL; 
			return(lCount);
		}
		lRC = sqlite3_finalize(tSQL3Stmt);
		tSQL3Stmt = NULL; 
		if (lRC != SQLITE_OK) {
			PrintError("ExecuteNonQueryFromMemory", hDBHandle);
			return(lCount);
		}
		strncpy(sSQLStr, szSQLString, sizeof(sSQLStr));
		lCount = (LONG) sqlite3_changes(hDBHandle);	
		if ((strcmpi(sSQLStr, "DELETE ") == 0) || (strcmpi(sSQLStr, "INSERT ") == 0) || (strcmpi(sSQLStr, "UPDATE ") == 0) || (strcmpi(sSQLStr, "REPLACE") == 0)) {
			
		}
		else {
			lCount = 0;
		}
		return(lCount);
	}
	return(lCount);
}

long SQLite::CountSQLValue(char *sSQL)
{
	LONG			lRC = 0L;
	sqlite3_stmt	*tSQL3Stmt = NULL;
	sqlite3			*hDBHandle = NULL;
	LONG			lCount = -1L;
	LONG			lRetryCnt = 0L;
	

	lCount = -1L;
	//hDBHandle = (sqlite3 *) lpISAM->hOptimizeSQLiteDataBase;
	hDBHandle = (sqlite3 *) sqlMemoryHandle;
	if (hDBHandle == NULL) {
		return(FALSE);
	}

	tSQL3Stmt = NULL;
	lRetryCnt = 0L;
	while (lRetryCnt < RETRYLOOPCOUNT) {
		lRC = sqlite3_prepare(hDBHandle, sSQL, -1, &tSQL3Stmt, NULL);
		if ((lRC != SQLITE_OK) || (tSQL3Stmt == NULL)) {
			if (lRC != SQLITE_OK) {
				PrintError("CountSQLValue", hDBHandle);	
			}
			return(lCount);
		}
		lRC = sqlite3_step(tSQL3Stmt);
		if ((lRC != SQLITE_SCHEMA) && (lRC != SQLITE_ERROR)) {
			break;
		}
		Sleep(10);
		lRC = sqlite3_finalize(tSQL3Stmt);
		tSQL3Stmt = NULL;
		lRetryCnt++;
	}
	if ((lRC != SQLITE_DONE) && (lRC != SQLITE_ROW)) {
		if (lRC != SQLITE_OK) {
			PrintError("CountSQLValue", hDBHandle);	
		}
		lRC = sqlite3_finalize(tSQL3Stmt);
		tSQL3Stmt = NULL; 
		if (lRC != SQLITE_OK) {
			PrintError("CountSQLValue", hDBHandle);	
		}
		return(lCount);
	}
	if (lRC == SQLITE_ROW) {
		lCount = sqlite3_column_int(tSQL3Stmt, 0);
		lRC = sqlite3_finalize(tSQL3Stmt);
		tSQL3Stmt = NULL; 
		if (lRC != SQLITE_OK) {
			PrintError("CountSQLValue", hDBHandle);	
		}
		return(lCount);
	}
	lRC = sqlite3_finalize (tSQL3Stmt);
	tSQL3Stmt = NULL; 
	if (lRC != SQLITE_OK) {
		PrintError("CountSQLValue", hDBHandle);	
	}
	return(lCount);
}

void SQLite::PrintError(char* szFunctionName, sqlite3* handle)
{
	const char *errorMsg = sqlite3_errmsg(handle);
	std::cout << "\t\t" << szFunctionName << " = " << errorMsg << endl;
}
