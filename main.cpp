#include <ObjBase.h>
#include <Rpc.h>
#include <ShlObj.h>
#include <direct.h>

#include "SQLite.h"

#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Rpcrt4.lib")

using namespace std;

void PrintStartTime(time_t&);
void PrintEndTime(time_t&);
void PrintDiffTime(time_t&, time_t&, time_t&);
char *GenerateGUID();

#define sizeOfRecords 420000

int main()
{
	//char *argvPath;
	char szDBPath[MAX_PATH] = "";
	if(false){
		//argvPath = argv[1];
	}
	else{
		if(false){

		}else{
			_getcwd(szDBPath, MAX_PATH);
		}
#ifdef USE_SQLCIPHER
			strcat(szDBPath, "\\sqlcipher.OPT");
#endif
#ifdef USE_SQLITE
			strcat(szDBPath, "\\sqlite.OPT");
#endif
	}

	char szInvoiceLineCreateQuery[8888] = "CREATE TABLE \"tblInvoiceLine\" (\"TxnID\" VARCHAR(36) COLLATE NOCASE NOT NULL UNIQUE PRIMARY KEY, \"TimeCreated\" NUMERIC(8) COLLATE BINARY NULL, \"TimeModified\" NUMERIC(8) COLLATE BINARY NULL, \"EditSequence\" VARCHAR(16) COLLATE NOCASE NULL, \"TxnNumber\" INTEGER(4) COLLATE BINARY NULL, \"CustomerRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"CustomerRefFullName\" VARCHAR(209) COLLATE NOCASE NULL, \"ClassRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"ClassRefFullName\" VARCHAR(159) COLLATE NOCASE NULL, \"ARAccountRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"ARAccountRefFullName\" VARCHAR(159) COLLATE NOCASE NULL, \"TemplateRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"TemplateRefFullName\" VARCHAR(159) COLLATE NOCASE NULL, \"TxnDate\" INTEGER(4) COLLATE BINARY NULL, \"TxnDateMacro\" VARCHAR(23) COLLATE NOCASE NULL, \"RefNumber\" VARCHAR(11) COLLATE NOCASE NULL, \"BillAddressAddr1\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressAddr2\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressAddr3\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressAddr4\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressAddr5\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressCity\" VARCHAR(31) COLLATE NOCASE NULL, \"BillAddressState\" VARCHAR(21) COLLATE NOCASE NULL, \"BillAddressProvince\" VARCHAR(21) COLLATE NOCASE NULL, \"BillAddressCounty\" VARCHAR(21) COLLATE NOCASE NULL, \"BillAddressPostalCode\" VARCHAR(13) COLLATE NOCASE NULL, \"BillAddressCountry\" VARCHAR(31) COLLATE NOCASE NULL, \"BillAddressNote\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressBlockAddr1\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressBlockAddr2\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressBlockAddr3\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressBlockAddr4\" VARCHAR(41) COLLATE NOCASE NULL, \"BillAddressBlockAddr5\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressAddr1\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressAddr2\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressAddr3\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressAddr4\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressAddr5\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressCity\" VARCHAR(31) COLLATE NOCASE NULL, \"ShipAddressState\" VARCHAR(21) COLLATE NOCASE NULL, \"ShipAddressProvince\" VARCHAR(21) COLLATE NOCASE NULL, \"ShipAddressCounty\" VARCHAR(21) COLLATE NOCASE NULL, \"ShipAddressPostalCode\" VARCHAR(13) COLLATE NOCASE NULL, \"ShipAddressCountry\" VARCHAR(31) COLLATE NOCASE NULL, \"ShipAddressNote\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressBlockAddr1\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressBlockAddr2\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressBlockAddr3\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressBlockAddr4\" VARCHAR(41) COLLATE NOCASE NULL, \"ShipAddressBlockAddr5\" VARCHAR(41) COLLATE NOCASE NULL, \"IsPending\" INTEGER(1) COLLATE BINARY NULL, \"IsFinanceCharge\" INTEGER(1) COLLATE BINARY NULL, \"PONumber\" VARCHAR(25) COLLATE NOCASE NULL, \"TermsRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"TermsRefFullName\" VARCHAR(31) COLLATE NOCASE NULL, \"DueDate\" INTEGER(4) COLLATE BINARY NULL, \"SalesRepRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"SalesRepRefFullName\" VARCHAR(5) COLLATE NOCASE NULL, \"FOB\" VARCHAR(13) COLLATE NOCASE NULL, \"ShipDate\" INTEGER(4) COLLATE BINARY NULL, \"ShipMethodRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"ShipMethodRefFullName\" VARCHAR(15) COLLATE NOCASE NULL, \"Subtotal\" NUMERIC(4) COLLATE BINARY NULL, \"ItemSalesTaxRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"ItemSalesTaxRefFullName\" VARCHAR(31) COLLATE NOCASE NULL, \"SalesTaxPercentage\" NUMERIC(4) COLLATE BINARY NULL, \"SalesTaxTotal\" NUMERIC(4) COLLATE BINARY NULL, \"AppliedAmount\" NUMERIC(4) COLLATE BINARY NULL, \"BalanceRemaining\" NUMERIC(4) COLLATE BINARY NULL, \"CurrencyRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"CurrencyRefFullName\" VARCHAR(64) COLLATE NOCASE NULL, \"ExchangeRate\" NUMERIC(4) COLLATE BINARY NULL, \"BalanceRemainingInHomeCurrency\" NUMERIC(4) COLLATE BINARY NULL, \"Memo\" VARCHAR(4095) COLLATE NOCASE NULL, \"IsPaid\" INTEGER(1) COLLATE BINARY NULL, \"CustomerMsgRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"CustomerMsgRefFullName\" VARCHAR(101) COLLATE NOCASE NULL, \"IsToBePrinted\" INTEGER(1) COLLATE BINARY NULL, \"IsToBeEmailed\" INTEGER(1) COLLATE BINARY NULL, \"IsTaxIncluded\" INTEGER(1) COLLATE BINARY NULL, \"CustomerSalesTaxCodeRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"CustomerSalesTaxCodeRefFullName\" VARCHAR(3) COLLATE NOCASE NULL, \"CustomerTaxCodeRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"SuggestedDiscountAmount\" NUMERIC(4) COLLATE BINARY NULL, \"SuggestedDiscountDate\" INTEGER(4) COLLATE BINARY NULL, \"CustomFieldOther\" VARCHAR(29) COLLATE NOCASE NULL, \"LinkToTxnID1\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineType\" VARCHAR(11) COLLATE NOCASE NULL, \"InvoiceLineSeqNo\" INTEGER(4) COLLATE BINARY NULL, \"InvoiceLineGroupTxnLineID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineGroupItemGroupRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineGroupItemGroupRefFullName\" VARCHAR(31) COLLATE NOCASE NULL, \"InvoiceLineGroupDesc\" VARCHAR(4095) COLLATE NOCASE NULL, \"InvoiceLineGroupQuantity\" NUMERIC(4) COLLATE BINARY NULL, \"InvoiceLineGroupUnitOfMeasure\" VARCHAR(31) COLLATE NOCASE NULL, \"InvoiceLineGroupOverrideUOMSetRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineGroupOverrideUOMSetRefFullName\" VARCHAR(31) COLLATE NOCASE NULL, \"InvoiceLineGroupIsPrintItemsInGroup\" INTEGER(1) COLLATE BINARY NULL, \"InvoiceLineGroupTotalAmount\" NUMERIC(4) COLLATE BINARY NULL, \"InvoiceLineGroupServiceDate\" INTEGER(4) COLLATE BINARY NULL, \"InvoiceLineGroupSeqNo\" INTEGER(4) COLLATE BINARY NULL, \"InvoiceLineTxnLineID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineItemRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineItemRefFullName\" VARCHAR(159) COLLATE NOCASE NULL, \"InvoiceLineDesc\" VARCHAR(4095) COLLATE NOCASE NULL, \"InvoiceLineQuantity\" NUMERIC(4) COLLATE BINARY NULL, \"InvoiceLineUnitOfMeasure\" VARCHAR(31) COLLATE NOCASE NULL, \"InvoiceLineOverrideUOMSetRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineOverrideUOMSetRefFullName\" VARCHAR(31) COLLATE NOCASE NULL, \"InvoiceLineRate\" NUMERIC(4) COLLATE BINARY NULL, \"InvoiceLineRatePercent\" NUMERIC(4) COLLATE BINARY NULL, \"InvoiceLinePriceLevelRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLinePriceLevelRefFullName\" VARCHAR(159) COLLATE NOCASE NULL, \"InvoiceLineClassRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineClassRefFullName\" VARCHAR(159) COLLATE NOCASE NULL, \"InvoiceLineAmount\" NUMERIC(4) COLLATE BINARY NULL, \"InvoiceLineInventorySiteRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineInventorySiteRefFullName\" VARCHAR(31) COLLATE NOCASE NULL, \"InvoiceLineInventorySiteLocationRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineInventorySiteLocationRefFullName\" VARCHAR(31) COLLATE NOCASE NULL, \"InvoiceLineSerialNumber\" VARCHAR(4095) COLLATE NOCASE NULL, \"InvoiceLineLotNumber\" VARCHAR(40) COLLATE NOCASE NULL, \"InvoiceLineTaxAmount\" NUMERIC(4) COLLATE BINARY NULL, \"InvoiceLineServiceDate\" INTEGER(4) COLLATE BINARY NULL, \"InvoiceLineSalesTaxCodeRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineSalesTaxCodeRefFullName\" VARCHAR(3) COLLATE NOCASE NULL, \"InvoiceLineTaxCodeRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineTaxCodeRefFullName\" VARCHAR(3) COLLATE NOCASE NULL, \"InvoiceLineOverrideItemAccountRefListID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineOverrideItemAccountRefFullName\" VARCHAR(159) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineOther1\" VARCHAR(29) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineOther2\" VARCHAR(29) COLLATE NOCASE NULL, \"InvoiceLineLinkToTxnTxnID\" VARCHAR(36) COLLATE NOCASE NULL, \"InvoiceLineLinkToTxnTxnLineID\" VARCHAR(36) COLLATE NOCASE NULL, \"Tax1Total\" NUMERIC(4) COLLATE BINARY NULL, \"Tax2Total\" NUMERIC(4) COLLATE BINARY NULL, \"AmountIncludesVAT\" INTEGER(1) COLLATE BINARY NULL, \"FQSaveToCache\" INTEGER(1) COLLATE BINARY NULL, \"FQPrimaryKey\" VARCHAR(110) COLLATE NOCASE NULL, \"FQTxnLinkKey\" VARCHAR(110) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineColor\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineMaterial\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineGroupColor\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineGroupMaterial\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineGroupLineColor\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldInvoiceLineGroupLineMaterial\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldBDay\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldContract\" VARCHAR(30) COLLATE NOCASE NULL, \"CustomFieldSpousesName\" VARCHAR(30) COLLATE NOCASE NULL)";
	char szInvoiceLineViewQuery[11111] = "CREATE VIEW \"InvoiceLine\" AS SELECT \"tblInvoiceLine\".\"TxnID\" AS \"TxnID\", \"tblInvoiceLine\".\"TimeCreated\" AS \"TimeCreated\", \"tblInvoiceLine\".\"TimeModified\" AS \"TimeModified\", \"tblInvoiceLine\".\"EditSequence\" AS \"EditSequence\", \"tblInvoiceLine\".\"TxnNumber\" AS \"TxnNumber\", \"tblInvoiceLine\".\"CustomerRefListID\" AS \"CustomerRefListID\", \"tblInvoiceLine\".\"CustomerRefFullName\" AS \"CustomerRefFullName\", \"tblInvoiceLine\".\"ClassRefListID\" AS \"ClassRefListID\", \"tblInvoiceLine\".\"ClassRefFullName\" AS \"ClassRefFullName\", \"tblInvoiceLine\".\"ARAccountRefListID\" AS \"ARAccountRefListID\", \"tblInvoiceLine\".\"ARAccountRefFullName\" AS \"ARAccountRefFullName\", \"tblInvoiceLine\".\"TemplateRefListID\" AS \"TemplateRefListID\", \"tblInvoiceLine\".\"TemplateRefFullName\" AS \"TemplateRefFullName\", \"tblInvoiceLine\".\"TxnDate\" AS \"TxnDate\", \"tblInvoiceLine\".\"TxnDateMacro\" AS \"TxnDateMacro\", \"tblInvoiceLine\".\"RefNumber\" AS \"RefNumber\", \"tblInvoiceLine\".\"BillAddressAddr1\" AS \"BillAddressAddr1\", \"tblInvoiceLine\".\"BillAddressAddr2\" AS \"BillAddressAddr2\", \"tblInvoiceLine\".\"BillAddressAddr3\" AS \"BillAddressAddr3\", \"tblInvoiceLine\".\"BillAddressAddr4\" AS \"BillAddressAddr4\", \"tblInvoiceLine\".\"BillAddressAddr5\" AS \"BillAddressAddr5\", \"tblInvoiceLine\".\"BillAddressCity\" AS \"BillAddressCity\", \"tblInvoiceLine\".\"BillAddressState\" AS \"BillAddressState\", \"tblInvoiceLine\".\"BillAddressProvince\" AS \"BillAddressProvince\", \"tblInvoiceLine\".\"BillAddressCounty\" AS \"BillAddressCounty\", \"tblInvoiceLine\".\"BillAddressPostalCode\" AS \"BillAddressPostalCode\", \"tblInvoiceLine\".\"BillAddressCountry\" AS \"BillAddressCountry\", \"tblInvoiceLine\".\"BillAddressNote\" AS \"BillAddressNote\", \"tblInvoiceLine\".\"BillAddressBlockAddr1\" AS \"BillAddressBlockAddr1\", \"tblInvoiceLine\".\"BillAddressBlockAddr2\" AS \"BillAddressBlockAddr2\", \"tblInvoiceLine\".\"BillAddressBlockAddr3\" AS \"BillAddressBlockAddr3\", \"tblInvoiceLine\".\"BillAddressBlockAddr4\" AS \"BillAddressBlockAddr4\", \"tblInvoiceLine\".\"BillAddressBlockAddr5\" AS \"BillAddressBlockAddr5\", \"tblInvoiceLine\".\"ShipAddressAddr1\" AS \"ShipAddressAddr1\", \"tblInvoiceLine\".\"ShipAddressAddr2\" AS \"ShipAddressAddr2\", \"tblInvoiceLine\".\"ShipAddressAddr3\" AS \"ShipAddressAddr3\", \"tblInvoiceLine\".\"ShipAddressAddr4\" AS \"ShipAddressAddr4\", \"tblInvoiceLine\".\"ShipAddressAddr5\" AS \"ShipAddressAddr5\", \"tblInvoiceLine\".\"ShipAddressCity\" AS \"ShipAddressCity\", \"tblInvoiceLine\".\"ShipAddressState\" AS \"ShipAddressState\", \"tblInvoiceLine\".\"ShipAddressProvince\" AS \"ShipAddressProvince\", \"tblInvoiceLine\".\"ShipAddressCounty\" AS \"ShipAddressCounty\", \"tblInvoiceLine\".\"ShipAddressPostalCode\" AS \"ShipAddressPostalCode\", \"tblInvoiceLine\".\"ShipAddressCountry\" AS \"ShipAddressCountry\", \"tblInvoiceLine\".\"ShipAddressNote\" AS \"ShipAddressNote\", \"tblInvoiceLine\".\"ShipAddressBlockAddr1\" AS \"ShipAddressBlockAddr1\", \"tblInvoiceLine\".\"ShipAddressBlockAddr2\" AS \"ShipAddressBlockAddr2\", \"tblInvoiceLine\".\"ShipAddressBlockAddr3\" AS \"ShipAddressBlockAddr3\", \"tblInvoiceLine\".\"ShipAddressBlockAddr4\" AS \"ShipAddressBlockAddr4\", \"tblInvoiceLine\".\"ShipAddressBlockAddr5\" AS \"ShipAddressBlockAddr5\", \"tblInvoiceLine\".\"IsPending\" AS \"IsPending\", \"tblInvoiceLine\".\"IsFinanceCharge\" AS \"IsFinanceCharge\", \"tblInvoiceLine\".\"PONumber\" AS \"PONumber\", \"tblInvoiceLine\".\"TermsRefListID\" AS \"TermsRefListID\", \"tblInvoiceLine\".\"TermsRefFullName\" AS \"TermsRefFullName\", \"tblInvoiceLine\".\"DueDate\" AS \"DueDate\", \"tblInvoiceLine\".\"SalesRepRefListID\" AS \"SalesRepRefListID\", \"tblInvoiceLine\".\"SalesRepRefFullName\" AS \"SalesRepRefFullName\", \"tblInvoiceLine\".\"FOB\" AS \"FOB\", \"tblInvoiceLine\".\"ShipDate\" AS \"ShipDate\", \"tblInvoiceLine\".\"ShipMethodRefListID\" AS \"ShipMethodRefListID\", \"tblInvoiceLine\".\"ShipMethodRefFullName\" AS \"ShipMethodRefFullName\", \"tblInvoiceLine\".\"Subtotal\" AS \"Subtotal\", \"tblInvoiceLine\".\"ItemSalesTaxRefListID\" AS \"ItemSalesTaxRefListID\", \"tblInvoiceLine\".\"ItemSalesTaxRefFullName\" AS \"ItemSalesTaxRefFullName\", \"tblInvoiceLine\".\"SalesTaxPercentage\" AS \"SalesTaxPercentage\", \"tblInvoiceLine\".\"SalesTaxTotal\" AS \"SalesTaxTotal\", \"tblInvoiceLine\".\"AppliedAmount\" AS \"AppliedAmount\", \"tblInvoiceLine\".\"BalanceRemaining\" AS \"BalanceRemaining\", \"tblInvoiceLine\".\"CurrencyRefListID\" AS \"CurrencyRefListID\", \"tblInvoiceLine\".\"CurrencyRefFullName\" AS \"CurrencyRefFullName\", \"tblInvoiceLine\".\"ExchangeRate\" AS \"ExchangeRate\", \"tblInvoiceLine\".\"BalanceRemainingInHomeCurrency\" AS \"BalanceRemainingInHomeCurrency\", \"tblInvoiceLine\".\"Memo\" AS \"Memo\", \"tblInvoiceLine\".\"IsPaid\" AS \"IsPaid\", \"tblInvoiceLine\".\"CustomerMsgRefListID\" AS \"CustomerMsgRefListID\", \"tblInvoiceLine\".\"CustomerMsgRefFullName\" AS \"CustomerMsgRefFullName\", \"tblInvoiceLine\".\"IsToBePrinted\" AS \"IsToBePrinted\", \"tblInvoiceLine\".\"IsToBeEmailed\" AS \"IsToBeEmailed\", \"tblInvoiceLine\".\"IsTaxIncluded\" AS \"IsTaxIncluded\", \"tblInvoiceLine\".\"CustomerSalesTaxCodeRefListID\" AS \"CustomerSalesTaxCodeRefListID\", \"tblInvoiceLine\".\"CustomerSalesTaxCodeRefFullName\" AS \"CustomerSalesTaxCodeRefFullName\", \"tblInvoiceLine\".\"CustomerTaxCodeRefListID\" AS \"CustomerTaxCodeRefListID\", \"tblInvoiceLine\".\"SuggestedDiscountAmount\" AS \"SuggestedDiscountAmount\", \"tblInvoiceLine\".\"SuggestedDiscountDate\" AS \"SuggestedDiscountDate\", \"tblInvoiceLine\".\"CustomFieldOther\" AS \"CustomFieldOther\", \"tblInvoiceLine\".\"LinkToTxnID1\" AS \"LinkToTxnID1\", \"tblInvoiceLine\".\"InvoiceLineType\" AS \"InvoiceLineType\", \"tblInvoiceLine\".\"InvoiceLineSeqNo\" AS \"InvoiceLineSeqNo\", \"tblInvoiceLine\".\"InvoiceLineGroupTxnLineID\" AS \"InvoiceLineGroupTxnLineID\", \"tblInvoiceLine\".\"InvoiceLineGroupItemGroupRefListID\" AS \"InvoiceLineGroupItemGroupRefListID\", \"tblInvoiceLine\".\"InvoiceLineGroupItemGroupRefFullName\" AS \"InvoiceLineGroupItemGroupRefFullName\", \"tblInvoiceLine\".\"InvoiceLineGroupDesc\" AS \"InvoiceLineGroupDesc\", \"tblInvoiceLine\".\"InvoiceLineGroupQuantity\" AS \"InvoiceLineGroupQuantity\", \"tblInvoiceLine\".\"InvoiceLineGroupUnitOfMeasure\" AS \"InvoiceLineGroupUnitOfMeasure\", \"tblInvoiceLine\".\"InvoiceLineGroupOverrideUOMSetRefListID\" AS \"InvoiceLineGroupOverrideUOMSetRefListID\", \"tblInvoiceLine\".\"InvoiceLineGroupOverrideUOMSetRefFullName\" AS \"InvoiceLineGroupOverrideUOMSetRefFullName\", \"tblInvoiceLine\".\"InvoiceLineGroupIsPrintItemsInGroup\" AS \"InvoiceLineGroupIsPrintItemsInGroup\", \"tblInvoiceLine\".\"InvoiceLineGroupTotalAmount\" AS \"InvoiceLineGroupTotalAmount\", \"tblInvoiceLine\".\"InvoiceLineGroupServiceDate\" AS \"InvoiceLineGroupServiceDate\", \"tblInvoiceLine\".\"InvoiceLineGroupSeqNo\" AS \"InvoiceLineGroupSeqNo\", \"tblInvoiceLine\".\"InvoiceLineTxnLineID\" AS \"InvoiceLineTxnLineID\", \"tblInvoiceLine\".\"InvoiceLineItemRefListID\" AS \"InvoiceLineItemRefListID\", \"tblInvoiceLine\".\"InvoiceLineItemRefFullName\" AS \"InvoiceLineItemRefFullName\", \"tblInvoiceLine\".\"InvoiceLineDesc\" AS \"InvoiceLineDesc\", \"tblInvoiceLine\".\"InvoiceLineQuantity\" AS \"InvoiceLineQuantity\", \"tblInvoiceLine\".\"InvoiceLineUnitOfMeasure\" AS \"InvoiceLineUnitOfMeasure\", \"tblInvoiceLine\".\"InvoiceLineOverrideUOMSetRefListID\" AS \"InvoiceLineOverrideUOMSetRefListID\", \"tblInvoiceLine\".\"InvoiceLineOverrideUOMSetRefFullName\" AS \"InvoiceLineOverrideUOMSetRefFullName\", \"tblInvoiceLine\".\"InvoiceLineRate\" AS \"InvoiceLineRate\", \"tblInvoiceLine\".\"InvoiceLineRatePercent\" AS \"InvoiceLineRatePercent\", \"tblInvoiceLine\".\"InvoiceLinePriceLevelRefListID\" AS \"InvoiceLinePriceLevelRefListID\", \"tblInvoiceLine\".\"InvoiceLinePriceLevelRefFullName\" AS \"InvoiceLinePriceLevelRefFullName\", \"tblInvoiceLine\".\"InvoiceLineClassRefListID\" AS \"InvoiceLineClassRefListID\", \"tblInvoiceLine\".\"InvoiceLineClassRefFullName\" AS \"InvoiceLineClassRefFullName\", \"tblInvoiceLine\".\"InvoiceLineAmount\" AS \"InvoiceLineAmount\", \"tblInvoiceLine\".\"InvoiceLineInventorySiteRefListID\" AS \"InvoiceLineInventorySiteRefListID\", \"tblInvoiceLine\".\"InvoiceLineInventorySiteRefFullName\" AS \"InvoiceLineInventorySiteRefFullName\", \"tblInvoiceLine\".\"InvoiceLineInventorySiteLocationRefListID\" AS \"InvoiceLineInventorySiteLocationRefListID\", \"tblInvoiceLine\".\"InvoiceLineInventorySiteLocationRefFullName\" AS \"InvoiceLineInventorySiteLocationRefFullName\", \"tblInvoiceLine\".\"InvoiceLineSerialNumber\" AS \"InvoiceLineSerialNumber\", \"tblInvoiceLine\".\"InvoiceLineLotNumber\" AS \"InvoiceLineLotNumber\", \"tblInvoiceLine\".\"InvoiceLineTaxAmount\" AS \"InvoiceLineTaxAmount\", \"tblInvoiceLine\".\"InvoiceLineServiceDate\" AS \"InvoiceLineServiceDate\", \"tblInvoiceLine\".\"InvoiceLineSalesTaxCodeRefListID\" AS \"InvoiceLineSalesTaxCodeRefListID\", \"tblInvoiceLine\".\"InvoiceLineSalesTaxCodeRefFullName\" AS \"InvoiceLineSalesTaxCodeRefFullName\", \"tblInvoiceLine\".\"InvoiceLineTaxCodeRefListID\" AS \"InvoiceLineTaxCodeRefListID\", \"tblInvoiceLine\".\"InvoiceLineTaxCodeRefFullName\" AS \"InvoiceLineTaxCodeRefFullName\", \"tblInvoiceLine\".\"InvoiceLineOverrideItemAccountRefListID\" AS \"InvoiceLineOverrideItemAccountRefListID\", \"tblInvoiceLine\".\"InvoiceLineOverrideItemAccountRefFullName\" AS \"InvoiceLineOverrideItemAccountRefFullName\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineOther1\" AS \"CustomFieldInvoiceLineOther1\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineOther2\" AS \"CustomFieldInvoiceLineOther2\", \"tblInvoiceLine\".\"InvoiceLineLinkToTxnTxnID\" AS \"InvoiceLineLinkToTxnTxnID\", \"tblInvoiceLine\".\"InvoiceLineLinkToTxnTxnLineID\" AS \"InvoiceLineLinkToTxnTxnLineID\", \"tblInvoiceLine\".\"Tax1Total\" AS \"Tax1Total\", \"tblInvoiceLine\".\"Tax2Total\" AS \"Tax2Total\", \"tblInvoiceLine\".\"AmountIncludesVAT\" AS \"AmountIncludesVAT\", \"tblInvoiceLine\".\"FQSaveToCache\" AS \"FQSaveToCache\", \"tblInvoiceLine\".\"FQPrimaryKey\" AS \"FQPrimaryKey\", \"tblInvoiceLine\".\"FQTxnLinkKey\" AS \"FQTxnLinkKey\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineColor\" AS \"CustomFieldInvoiceLineColor\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineMaterial\" AS \"CustomFieldInvoiceLineMaterial\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineGroupColor\" AS \"CustomFieldInvoiceLineGroupColor\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineGroupMaterial\" AS \"CustomFieldInvoiceLineGroupMaterial\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineGroupLineColor\" AS \"CustomFieldInvoiceLineGroupLineColor\", \"tblInvoiceLine\".\"CustomFieldInvoiceLineGroupLineMaterial\" AS \"CustomFieldInvoiceLineGroupLineMaterial\", \"tblInvoiceLine\".\"CustomFieldBDay\" AS \"CustomFieldBDay\", \"tblInvoiceLine\".\"CustomFieldContract\" AS \"CustomFieldContract\", \"tblInvoiceLine\".\"CustomFieldSpousesName\" AS \"CustomFieldSpousesName\" FROM \"tblInvoiceLine\"";
	char szInsertQuery[16384] = "INSERT OR REPLACE INTO \"tblInvoiceLine\" (\"TxnID\", \"TimeCreated\", \"TimeModified\", \"EditSequence\", \"TxnNumber\", \"CustomerRefListID\", \"CustomerRefFullName\", \"ClassRefListID\", \"ClassRefFullName\", \"ARAccountRefListID\", \"ARAccountRefFullName\", \"TemplateRefListID\", \"TemplateRefFullName\", \"TxnDate\", \"TxnDateMacro\", \"RefNumber\", \"BillAddressAddr1\", \"BillAddressAddr2\", \"BillAddressAddr3\", \"BillAddressAddr4\", \"BillAddressAddr5\", \"BillAddressCity\", \"BillAddressState\", \"BillAddressProvince\", \"BillAddressCounty\", \"BillAddressPostalCode\", \"BillAddressCountry\", \"BillAddressNote\", \"BillAddressBlockAddr1\", \"BillAddressBlockAddr2\", \"BillAddressBlockAddr3\", \"BillAddressBlockAddr4\", \"BillAddressBlockAddr5\", \"ShipAddressAddr1\", \"ShipAddressAddr2\", \"ShipAddressAddr3\", \"ShipAddressAddr4\", \"ShipAddressAddr5\", \"ShipAddressCity\", \"ShipAddressState\", \"ShipAddressProvince\", \"ShipAddressCounty\", \"ShipAddressPostalCode\", \"ShipAddressCountry\", \"ShipAddressNote\", \"ShipAddressBlockAddr1\", \"ShipAddressBlockAddr2\", \"ShipAddressBlockAddr3\", \"ShipAddressBlockAddr4\", \"ShipAddressBlockAddr5\", \"IsPending\", \"IsFinanceCharge\", \"PONumber\", \"TermsRefListID\", \"TermsRefFullName\", \"DueDate\", \"SalesRepRefListID\", \"SalesRepRefFullName\", \"FOB\", \"ShipDate\", \"ShipMethodRefListID\", \"ShipMethodRefFullName\", \"Subtotal\", \"ItemSalesTaxRefListID\", \"ItemSalesTaxRefFullName\", \"SalesTaxPercentage\", \"SalesTaxTotal\", \"AppliedAmount\", \"BalanceRemaining\", \"CurrencyRefListID\", \"CurrencyRefFullName\", \"ExchangeRate\", \"BalanceRemainingInHomeCurrency\", \"Memo\", \"IsPaid\", \"CustomerMsgRefListID\", \"CustomerMsgRefFullName\", \"IsToBePrinted\", \"IsToBeEmailed\", \"IsTaxIncluded\", \"CustomerSalesTaxCodeRefListID\", \"CustomerSalesTaxCodeRefFullName\", \"CustomerTaxCodeRefListID\", \"SuggestedDiscountAmount\", \"SuggestedDiscountDate\", \"CustomFieldOther\", \"LinkToTxnID1\", \"InvoiceLineType\", \"InvoiceLineSeqNo\", \"InvoiceLineGroupTxnLineID\", \"InvoiceLineGroupItemGroupRefListID\", \"InvoiceLineGroupItemGroupRefFullName\", \"InvoiceLineGroupDesc\", \"InvoiceLineGroupQuantity\", \"InvoiceLineGroupUnitOfMeasure\", \"InvoiceLineGroupOverrideUOMSetRefListID\", \"InvoiceLineGroupOverrideUOMSetRefFullName\", \"InvoiceLineGroupIsPrintItemsInGroup\", \"InvoiceLineGroupTotalAmount\", \"InvoiceLineGroupServiceDate\", \"InvoiceLineGroupSeqNo\", \"InvoiceLineTxnLineID\", \"InvoiceLineItemRefListID\", \"InvoiceLineItemRefFullName\", \"InvoiceLineDesc\", \"InvoiceLineQuantity\", \"InvoiceLineUnitOfMeasure\", \"InvoiceLineOverrideUOMSetRefListID\", \"InvoiceLineOverrideUOMSetRefFullName\", \"InvoiceLineRate\", \"InvoiceLineRatePercent\", \"InvoiceLinePriceLevelRefListID\", \"InvoiceLinePriceLevelRefFullName\", \"InvoiceLineClassRefListID\", \"InvoiceLineClassRefFullName\", \"InvoiceLineAmount\", \"InvoiceLineInventorySiteRefListID\", \"InvoiceLineInventorySiteRefFullName\", \"InvoiceLineInventorySiteLocationRefListID\", \"InvoiceLineInventorySiteLocationRefFullName\", \"InvoiceLineSerialNumber\", \"InvoiceLineLotNumber\", \"InvoiceLineTaxAmount\", \"InvoiceLineServiceDate\", \"InvoiceLineSalesTaxCodeRefListID\", \"InvoiceLineSalesTaxCodeRefFullName\", \"InvoiceLineTaxCodeRefListID\", \"InvoiceLineTaxCodeRefFullName\", \"InvoiceLineOverrideItemAccountRefListID\", \"InvoiceLineOverrideItemAccountRefFullName\", \"CustomFieldInvoiceLineOther1\", \"CustomFieldInvoiceLineOther2\", \"InvoiceLineLinkToTxnTxnID\", \"InvoiceLineLinkToTxnTxnLineID\", \"Tax1Total\", \"Tax2Total\", \"AmountIncludesVAT\", \"FQSaveToCache\", \"FQPrimaryKey\", \"FQTxnLinkKey\", \"CustomFieldInvoiceLineColor\", \"CustomFieldInvoiceLineMaterial\", \"CustomFieldInvoiceLineGroupColor\", \"CustomFieldInvoiceLineGroupMaterial\", \"CustomFieldInvoiceLineGroupLineColor\", \"CustomFieldInvoiceLineGroupLineMaterial\", \"CustomFieldBDay\", \"CustomFieldContract\", \"CustomFieldSpousesName\") VALUES (\"";
	char szSelectInvoieLineLongQuery[10000] = "SELECT \"InvoiceLine\".\"TxnID\" AS \"FQALIAS_1\", \"InvoiceLine\".\"TimeCreated\" AS \"FQALIAS_2\", \"InvoiceLine\".\"TimeModified\" AS \"FQALIAS_3\", \"InvoiceLine\".\"EditSequence\" AS \"FQALIAS_4\", \"InvoiceLine\".\"TxnNumber\" AS \"FQALIAS_5\", \"InvoiceLine\".\"CustomerRefListID\" AS \"FQALIAS_6\", \"InvoiceLine\".\"CustomerRefFullName\" AS \"FQALIAS_7\", \"InvoiceLine\".\"ClassRefListID\" AS \"FQALIAS_8\", \"InvoiceLine\".\"ClassRefFullName\" AS \"FQALIAS_9\", \"InvoiceLine\".\"ARAccountRefListID\" AS \"FQALIAS_10\", \"InvoiceLine\".\"ARAccountRefFullName\" AS \"FQALIAS_11\", \"InvoiceLine\".\"TemplateRefListID\" AS \"FQALIAS_12\", \"InvoiceLine\".\"TemplateRefFullName\" AS \"FQALIAS_13\", \"InvoiceLine\".\"TxnDate\" AS \"FQALIAS_14\", \"InvoiceLine\".\"TxnDateMacro\" AS \"FQALIAS_15\", \"InvoiceLine\".\"RefNumber\" AS \"FQALIAS_16\", \"InvoiceLine\".\"BillAddressAddr1\" AS \"FQALIAS_17\", \"InvoiceLine\".\"BillAddressAddr2\" AS \"FQALIAS_18\", \"InvoiceLine\".\"BillAddressAddr3\" AS \"FQALIAS_19\", \"InvoiceLine\".\"BillAddressAddr4\" AS \"FQALIAS_20\", \"InvoiceLine\".\"BillAddressAddr5\" AS \"FQALIAS_21\", \"InvoiceLine\".\"BillAddressCity\" AS \"FQALIAS_22\", \"InvoiceLine\".\"BillAddressState\" AS \"FQALIAS_23\", \"InvoiceLine\".\"BillAddressProvince\" AS \"FQALIAS_24\", \"InvoiceLine\".\"BillAddressCounty\" AS \"FQALIAS_25\", \"InvoiceLine\".\"BillAddressPostalCode\" AS \"FQALIAS_26\", \"InvoiceLine\".\"BillAddressCountry\" AS \"FQALIAS_27\", \"InvoiceLine\".\"BillAddressNote\" AS \"FQALIAS_28\", \"InvoiceLine\".\"BillAddressBlockAddr1\" AS \"FQALIAS_29\", \"InvoiceLine\".\"BillAddressBlockAddr2\" AS \"FQALIAS_30\", \"InvoiceLine\".\"BillAddressBlockAddr3\" AS \"FQALIAS_31\", \"InvoiceLine\".\"BillAddressBlockAddr4\" AS \"FQALIAS_32\", \"InvoiceLine\".\"BillAddressBlockAddr5\" AS \"FQALIAS_33\", \"InvoiceLine\".\"ShipAddressAddr1\" AS \"FQALIAS_34\", \"InvoiceLine\".\"ShipAddressAddr2\" AS \"FQALIAS_35\", \"InvoiceLine\".\"ShipAddressAddr3\" AS \"FQALIAS_36\", \"InvoiceLine\".\"ShipAddressAddr4\" AS \"FQALIAS_37\", \"InvoiceLine\".\"ShipAddressAddr5\" AS \"FQALIAS_38\", \"InvoiceLine\".\"ShipAddressCity\" AS \"FQALIAS_39\", \"InvoiceLine\".\"ShipAddressState\" AS \"FQALIAS_40\", \"InvoiceLine\".\"ShipAddressProvince\" AS \"FQALIAS_41\", \"InvoiceLine\".\"ShipAddressCounty\" AS \"FQALIAS_42\", \"InvoiceLine\".\"ShipAddressPostalCode\" AS \"FQALIAS_43\", \"InvoiceLine\".\"ShipAddressCountry\" AS \"FQALIAS_44\", \"InvoiceLine\".\"ShipAddressNote\" AS \"FQALIAS_45\", \"InvoiceLine\".\"ShipAddressBlockAddr1\" AS \"FQALIAS_46\", \"InvoiceLine\".\"ShipAddressBlockAddr2\" AS \"FQALIAS_47\", \"InvoiceLine\".\"ShipAddressBlockAddr3\" AS \"FQALIAS_48\", \"InvoiceLine\".\"ShipAddressBlockAddr4\" AS \"FQALIAS_49\", \"InvoiceLine\".\"ShipAddressBlockAddr5\" AS \"FQALIAS_50\", \"InvoiceLine\".\"IsPending\" AS \"FQALIAS_51\", \"InvoiceLine\".\"IsFinanceCharge\" AS \"FQALIAS_52\", \"InvoiceLine\".\"PONumber\" AS \"FQALIAS_53\", \"InvoiceLine\".\"TermsRefListID\" AS \"FQALIAS_54\", \"InvoiceLine\".\"TermsRefFullName\" AS \"FQALIAS_55\", \"InvoiceLine\".\"DueDate\" AS \"FQALIAS_56\", \"InvoiceLine\".\"SalesRepRefListID\" AS \"FQALIAS_57\", \"InvoiceLine\".\"SalesRepRefFullName\" AS \"FQALIAS_58\", \"InvoiceLine\".\"FOB\" AS \"FQALIAS_59\", \"InvoiceLine\".\"ShipDate\" AS \"FQALIAS_60\", \"InvoiceLine\".\"ShipMethodRefListID\" AS \"FQALIAS_61\", \"InvoiceLine\".\"ShipMethodRefFullName\" AS \"FQALIAS_62\", \"InvoiceLine\".\"Subtotal\" AS \"FQALIAS_63\", \"InvoiceLine\".\"ItemSalesTaxRefListID\" AS \"FQALIAS_64\", \"InvoiceLine\".\"ItemSalesTaxRefFullName\" AS \"FQALIAS_65\", \"InvoiceLine\".\"SalesTaxPercentage\" AS \"FQALIAS_66\", \"InvoiceLine\".\"SalesTaxTotal\" AS \"FQALIAS_67\", \"InvoiceLine\".\"AppliedAmount\" AS \"FQALIAS_68\", \"InvoiceLine\".\"BalanceRemaining\" AS \"FQALIAS_69\", \"InvoiceLine\".\"CurrencyRefListID\" AS \"FQALIAS_70\", \"InvoiceLine\".\"CurrencyRefFullName\" AS \"FQALIAS_71\", \"InvoiceLine\".\"ExchangeRate\" AS \"FQALIAS_72\", \"InvoiceLine\".\"BalanceRemainingInHomeCurrency\" AS \"FQALIAS_73\", \"InvoiceLine\".\"Memo\" AS \"FQALIAS_74\", \"InvoiceLine\".\"IsPaid\" AS \"FQALIAS_75\", \"InvoiceLine\".\"CustomerMsgRefListID\" AS \"FQALIAS_76\", \"InvoiceLine\".\"CustomerMsgRefFullName\" AS \"FQALIAS_77\", \"InvoiceLine\".\"IsToBePrinted\" AS \"FQALIAS_78\", \"InvoiceLine\".\"IsToBeEmailed\" AS \"FQALIAS_79\", \"InvoiceLine\".\"IsTaxIncluded\" AS \"FQALIAS_80\", \"InvoiceLine\".\"CustomerSalesTaxCodeRefListID\" AS \"FQALIAS_81\", \"InvoiceLine\".\"CustomerSalesTaxCodeRefFullName\" AS \"FQALIAS_82\", \"InvoiceLine\".\"CustomerTaxCodeRefListID\" AS \"FQALIAS_83\", \"InvoiceLine\".\"SuggestedDiscountAmount\" AS \"FQALIAS_84\", \"InvoiceLine\".\"SuggestedDiscountDate\" AS \"FQALIAS_85\", \"InvoiceLine\".\"CustomFieldOther\" AS \"FQALIAS_86\", \"InvoiceLine\".\"LinkToTxnID1\" AS \"FQALIAS_87\", \"InvoiceLine\".\"InvoiceLineType\" AS \"FQALIAS_88\", \"InvoiceLine\".\"InvoiceLineSeqNo\" AS \"FQALIAS_89\", \"InvoiceLine\".\"InvoiceLineGroupTxnLineID\" AS \"FQALIAS_90\", \"InvoiceLine\".\"InvoiceLineGroupItemGroupRefListID\" AS \"FQALIAS_91\", \"InvoiceLine\".\"InvoiceLineGroupItemGroupRefFullName\" AS \"FQALIAS_92\", \"InvoiceLine\".\"InvoiceLineGroupDesc\" AS \"FQALIAS_93\", \"InvoiceLine\".\"InvoiceLineGroupQuantity\" AS \"FQALIAS_94\", \"InvoiceLine\".\"InvoiceLineGroupUnitOfMeasure\" AS \"FQALIAS_95\", \"InvoiceLine\".\"InvoiceLineGroupOverrideUOMSetRefListID\" AS \"FQALIAS_96\", \"InvoiceLine\".\"InvoiceLineGroupOverrideUOMSetRefFullName\" AS \"FQALIAS_97\", \"InvoiceLine\".\"InvoiceLineGroupIsPrintItemsInGroup\" AS \"FQALIAS_98\", \"InvoiceLine\".\"InvoiceLineGroupTotalAmount\" AS \"FQALIAS_99\", \"InvoiceLine\".\"InvoiceLineGroupServiceDate\" AS \"FQALIAS_100\", \"InvoiceLine\".\"InvoiceLineGroupSeqNo\" AS \"FQALIAS_101\", \"InvoiceLine\".\"InvoiceLineTxnLineID\" AS \"FQALIAS_102\", \"InvoiceLine\".\"InvoiceLineItemRefListID\" AS \"FQALIAS_103\", \"InvoiceLine\".\"InvoiceLineItemRefFullName\" AS \"FQALIAS_104\", \"InvoiceLine\".\"InvoiceLineDesc\" AS \"FQALIAS_105\", \"InvoiceLine\".\"InvoiceLineQuantity\" AS \"FQALIAS_106\", \"InvoiceLine\".\"InvoiceLineUnitOfMeasure\" AS \"FQALIAS_107\", \"InvoiceLine\".\"InvoiceLineOverrideUOMSetRefListID\" AS \"FQALIAS_108\", \"InvoiceLine\".\"InvoiceLineOverrideUOMSetRefFullName\" AS \"FQALIAS_109\", \"InvoiceLine\".\"InvoiceLineRate\" AS \"FQALIAS_110\", \"InvoiceLine\".\"InvoiceLineRatePercent\" AS \"FQALIAS_111\", \"InvoiceLine\".\"InvoiceLinePriceLevelRefListID\" AS \"FQALIAS_112\", \"InvoiceLine\".\"InvoiceLinePriceLevelRefFullName\" AS \"FQALIAS_113\", \"InvoiceLine\".\"InvoiceLineClassRefListID\" AS \"FQALIAS_114\", \"InvoiceLine\".\"InvoiceLineClassRefFullName\" AS \"FQALIAS_115\", \"InvoiceLine\".\"InvoiceLineAmount\" AS \"FQALIAS_116\", \"InvoiceLine\".\"InvoiceLineInventorySiteRefListID\" AS \"FQALIAS_117\", \"InvoiceLine\".\"InvoiceLineInventorySiteRefFullName\" AS \"FQALIAS_118\", \"InvoiceLine\".\"InvoiceLineInventorySiteLocationRefListID\" AS \"FQALIAS_119\", \"InvoiceLine\".\"InvoiceLineInventorySiteLocationRefFullName\" AS \"FQALIAS_120\", \"InvoiceLine\".\"InvoiceLineSerialNumber\" AS \"FQALIAS_121\", \"InvoiceLine\".\"InvoiceLineLotNumber\" AS \"FQALIAS_122\", \"InvoiceLine\".\"InvoiceLineTaxAmount\" AS \"FQALIAS_123\", \"InvoiceLine\".\"InvoiceLineServiceDate\" AS \"FQALIAS_124\", \"InvoiceLine\".\"InvoiceLineSalesTaxCodeRefListID\" AS \"FQALIAS_125\", \"InvoiceLine\".\"InvoiceLineSalesTaxCodeRefFullName\" AS \"FQALIAS_126\", \"InvoiceLine\".\"InvoiceLineTaxCodeRefListID\" AS \"FQALIAS_127\", \"InvoiceLine\".\"InvoiceLineTaxCodeRefFullName\" AS \"FQALIAS_128\", \"InvoiceLine\".\"InvoiceLineOverrideItemAccountRefListID\" AS \"FQALIAS_129\", \"InvoiceLine\".\"InvoiceLineOverrideItemAccountRefFullName\" AS \"FQALIAS_130\", \"InvoiceLine\".\"CustomFieldInvoiceLineOther1\" AS \"FQALIAS_131\", \"InvoiceLine\".\"CustomFieldInvoiceLineOther2\" AS \"FQALIAS_132\", \"InvoiceLine\".\"InvoiceLineLinkToTxnTxnID\" AS \"FQALIAS_133\", \"InvoiceLine\".\"InvoiceLineLinkToTxnTxnLineID\" AS \"FQALIAS_134\", \"InvoiceLine\".\"Tax1Total\" AS \"FQALIAS_135\", \"InvoiceLine\".\"Tax2Total\" AS \"FQALIAS_136\", \"InvoiceLine\".\"AmountIncludesVAT\" AS \"FQALIAS_137\", \"InvoiceLine\".\"FQSaveToCache\" AS \"FQALIAS_138\", \"InvoiceLine\".\"FQPrimaryKey\" AS \"FQALIAS_139\", \"InvoiceLine\".\"FQTxnLinkKey\" AS \"FQALIAS_140\", \"InvoiceLine\".\"CustomFieldInvoiceLineColor\" AS \"FQALIAS_141\", \"InvoiceLine\".\"CustomFieldInvoiceLineMaterial\" AS \"FQALIAS_142\", \"InvoiceLine\".\"CustomFieldInvoiceLineGroupColor\" AS \"FQALIAS_143\", \"InvoiceLine\".\"CustomFieldInvoiceLineGroupMaterial\" AS \"FQALIAS_144\", \"InvoiceLine\".\"CustomFieldInvoiceLineGroupLineColor\" AS \"FQALIAS_145\", \"InvoiceLine\".\"CustomFieldInvoiceLineGroupLineMaterial\" AS \"FQALIAS_146\", \"InvoiceLine\".\"CustomFieldBDay\" AS \"FQALIAS_147\", \"InvoiceLine\".\"CustomFieldContract\" AS \"FQALIAS_148\", \"InvoiceLine\".\"CustomFieldSpousesName\" AS \"FQALIAS_149\" FROM \"InvoiceLine\"";
	char szSelectInvoieLineShortQuery[4196] = "SELECT \"ROWID\", \"FQALIAS_1\", \"FQALIAS_2\", \"FQALIAS_3\", \"FQALIAS_4\", \"FQALIAS_5\", \"FQALIAS_6\", \"FQALIAS_7\", \"FQALIAS_8\", \"FQALIAS_9\", \"FQALIAS_10\", \"FQALIAS_11\", \"FQALIAS_12\", \"FQALIAS_13\", \"FQALIAS_14\", \"FQALIAS_15\", \"FQALIAS_16\", \"FQALIAS_17\", \"FQALIAS_18\", \"FQALIAS_19\", \"FQALIAS_20\", \"FQALIAS_21\", \"FQALIAS_22\", \"FQALIAS_23\", \"FQALIAS_24\", \"FQALIAS_25\", \"FQALIAS_26\", \"FQALIAS_27\", \"FQALIAS_28\", \"FQALIAS_29\", \"FQALIAS_30\", \"FQALIAS_31\", \"FQALIAS_32\", \"FQALIAS_33\", \"FQALIAS_34\", \"FQALIAS_35\", \"FQALIAS_36\", \"FQALIAS_37\", \"FQALIAS_38\", \"FQALIAS_39\", \"FQALIAS_40\", \"FQALIAS_41\", \"FQALIAS_42\", \"FQALIAS_43\", \"FQALIAS_44\", \"FQALIAS_45\", \"FQALIAS_46\", \"FQALIAS_47\", \"FQALIAS_48\", \"FQALIAS_49\", \"FQALIAS_50\", \"FQALIAS_51\", \"FQALIAS_52\", \"FQALIAS_53\", \"FQALIAS_54\", \"FQALIAS_55\", \"FQALIAS_56\", \"FQALIAS_57\", \"FQALIAS_58\", \"FQALIAS_59\", \"FQALIAS_60\", \"FQALIAS_61\", \"FQALIAS_62\", \"FQALIAS_63\", \"FQALIAS_64\", \"FQALIAS_65\", \"FQALIAS_66\", \"FQALIAS_67\", \"FQALIAS_68\", \"FQALIAS_69\", \"FQALIAS_70\", \"FQALIAS_71\", \"FQALIAS_72\", \"FQALIAS_73\", \"FQALIAS_74\", \"FQALIAS_75\", \"FQALIAS_76\", \"FQALIAS_77\", \"FQALIAS_78\", \"FQALIAS_79\", \"FQALIAS_80\", \"FQALIAS_81\", \"FQALIAS_82\", \"FQALIAS_83\", \"FQALIAS_84\", \"FQALIAS_85\", \"FQALIAS_86\", \"FQALIAS_87\", \"FQALIAS_88\", \"FQALIAS_89\", \"FQALIAS_90\", \"FQALIAS_91\", \"FQALIAS_92\", \"FQALIAS_93\", \"FQALIAS_94\", \"FQALIAS_95\", \"FQALIAS_96\", \"FQALIAS_97\", \"FQALIAS_98\", \"FQALIAS_99\", \"FQALIAS_100\", \"FQALIAS_101\", \"FQALIAS_102\", \"FQALIAS_103\", \"FQALIAS_104\", \"FQALIAS_105\", \"FQALIAS_106\", \"FQALIAS_107\", \"FQALIAS_108\", \"FQALIAS_109\", \"FQALIAS_110\", \"FQALIAS_111\", \"FQALIAS_112\", \"FQALIAS_113\", \"FQALIAS_114\", \"FQALIAS_115\", \"FQALIAS_116\", \"FQALIAS_117\", \"FQALIAS_118\", \"FQALIAS_119\", \"FQALIAS_120\", \"FQALIAS_121\", \"FQALIAS_122\", \"FQALIAS_123\", \"FQALIAS_124\", \"FQALIAS_125\", \"FQALIAS_126\", \"FQALIAS_127\", \"FQALIAS_128\", \"FQALIAS_129\", \"FQALIAS_130\", \"FQALIAS_131\", \"FQALIAS_132\", \"FQALIAS_133\", \"FQALIAS_134\", \"FQALIAS_135\", \"FQALIAS_136\", \"FQALIAS_137\", \"FQALIAS_138\", \"FQALIAS_139\", \"FQALIAS_140\", \"FQALIAS_141\", \"FQALIAS_142\", \"FQALIAS_143\", \"FQALIAS_144\", \"FQALIAS_145\", \"FQALIAS_146\", \"FQALIAS_147\", \"FQALIAS_148\", \"FQALIAS_149\" FROM \"InvoiceLine\"";
	char szSelectInvoieLineCountQuery[512] = "SELECT COUNT(\"ROWID\") FROM \"InvoiceLine\"";
	char Key[32] = "";
	int iChoice;
	long lCountRecords = 0;

	SQLite sqliteObject; /* create sqlite object */
	 
	time_t tStartTime, tEndTime, tDiffrence;
	
	//char *szGUID = GenerateGUID();

	/* Perfomance comparison of SQLite, SQLCrypt and SQLCipher */
	cout << "\t\t ********************************************"<< endl;
	cout << "\t\t Welcome to Perfomance comparison of ";

#ifdef USE_SQLCIPHER
	cout << "SQLCipher \n\n" << endl;
#endif
#ifdef USE_SQLITE
	cout << "SQLite \n\n" << endl;
#endif

	do
	{
		cout << "\t\t 1. Open and Create Database."<<endl;
		cout << "\t\t 2. Open and Create InvoiceLine table."<<endl;
		cout << "\t\t 3. Insert dummy records in the InvoiceLine table."<<endl;
		cout << "\t\t 4. Dump the data to memory InvoiceLine table."<<endl;
		cout << "\t\t 5. Read data one my one from InvoiceLine table."<<endl;
		cout << "\t\t 6. Exit."<<endl;
		cin >>iChoice;
		switch(iChoice){
		case 1:
			{
				cout << "\t\t You have selected 1 option." << endl;
				cout << "\t\t 1. Insert dummy records in the tables." << endl;
				PrintStartTime(tStartTime);
				/* 1. Insert dummy records in the tables. */

				// open Database and apply key and pragama
				sqliteObject.Open(szDBPath); 
				sqliteObject.SetEncryptionKey(NULL);
				sqliteObject.ApplyStanardQuery(NULL);

				PrintEndTime(tEndTime);
				PrintDiffTime(tEndTime, tStartTime, tDiffrence);
				cout<< endl;
			}
			break;

		case 2:
			{
				/* Create a table */
				cout << "\t\t You have selected 2 option." << endl;
				cout << "\t\t 2. Open and Create Customer Table." << endl;
				PrintStartTime(tStartTime);
				sqliteObject.BeginTransaction();
				sqliteObject.ExecuteNonQuery(szInvoiceLineCreateQuery);
				sqliteObject.ExecuteNonQuery(szInvoiceLineViewQuery);
				sqliteObject.CommitTransaction();
				PrintEndTime(tEndTime);
				PrintDiffTime(tEndTime, tStartTime, tDiffrence);
				cout<< endl;
			}
			break;

		case 3:
			{
				cout << "\t\t You have selected 3 option." << endl;
				cout << "\t\t 3. Insert dummy records in the tables." << endl;
				PrintStartTime(tStartTime);
				sqliteObject.BeginTransaction();
				char szInsertQueryValue[2500] = "\", \"2017-12-15 18:53:28.000\", \"2017-12-15 18:53:28.000\", \"1513344208\",  1778, \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\", \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\", \"40000-933270541\", \"Accounts Receivable\", \"E0000-1071499861\", \"Rock Castle Invoice\", \"2015-01-29\", \"All\", \"12000\", \"Semtech International AG\", \"Saentisstrasse 2A\", \"Saentisstrasse 2A\", \"Saentisstrasse 2A\", \"Saentisstrasse 2A\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Switzerland\", \"Wil 9500\", \"Semtech International AG\", \"Saentisstrasse 2A\", \"Wil 9500\", \"Switzerland\", \"Wil 9500\", \"Semtech International AG\", \"Saentisstrasse 2A\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Wil 9500\", \"Switzerland\", \"Wil 9500\", \"Semtech International AG\", \"Saentisstrasse 2A\", \"Wil 9500\", \"Switzerland\", \"Wil 9500\", 0, 0, \"123\", \"10000-933272658\", \"Net 30\", \"2015-02-28\", \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\", \"DA383100\", \"2015-01-29\", \"40000-933272660\", \"UPS\", \"317.75\", \"2D0000-933272656\", \"San Domingo\", \"7.50\", \"0.00\", \"0.00\", \"317.75\", \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\",  NULL,  NULL, \"Prentice Adelaide:Bay Window\",  0, \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\",  1, 0, NULL, \"10000-999022286\", \"Tax\", \"10000-999022286\",  NULL,  NULL, \"SPZ21018R5FCN\",  NULL, \"Item\",  1, NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL, \"1AD71-1513344208\", \"320000-1071525597\", \"Concrete Slab\", \"RC0521Z.N.A05 (SPZ21018R5FCN) Bag #26302 Lot #12347.1A 12347.1B 12347.1C (3 Wafers)(364412) Date Code 1503 Bag #26300 Lot #12347.1D 12347.1E 12347.1F (3 Wafers)(367623) Date Code 1502 Bag #26303 Lot #12347.1G 12347.1H 12347.1I12347.1J 1234567890123 Bag 123456789 Bag 123456789 Bag 123456789\",  NULL,  NULL, \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\", \"317.75\",  NULL, \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\", \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\", \"317.75\", \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\", \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\",  NULL,  NULL,  NULL,  NULL, \"20000-999022286\", \"Non\", \"20000-999022286\", \"Non\", \"800000B8-1197707458\", \"Prentice Adelaide:Bay Window\",  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  0, \"1AD6F-1513344208|1AD71-1513344208|\", \"1AD6F-1513344208|1AD71-1513344208\",  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL)";
				char *szInsertQueryName = new char[20000]();
				char szTxnID[10] = "";
				for(long i=0; i<sizeOfRecords; i++)
				{
					memset(szInsertQueryName, 0, sizeof(szInsertQueryName));
					strcpy(szInsertQueryName, szInsertQuery);
					sprintf(szTxnID, "%ld", i+1);
					strcat(szInsertQueryName, szTxnID);
					//strcat(szInsertQueryName, "\"");
					strcat(szInsertQueryName, szInsertQueryValue);
					 
					if(sqliteObject.ExecuteNonQuery(szInsertQueryName) < 0){
						cout << "\t\t Faild to Insert" << endl;
						break;
					}

					//cout << " " << i+1 << ",";
				}
				delete [] szInsertQueryName;
				sqliteObject.CommitTransaction();
				PrintEndTime(tEndTime);
				PrintDiffTime(tEndTime, tStartTime, tDiffrence);
				cout << "\t\t\tAll Rows inserted." << endl;
				cout<< endl;
			}
			break;

		case 4:
			{
				cout << "\t\t You have selected 4 option." << endl;
				cout << "\t\t 4. Dump the data to memory table." << endl;
				PrintStartTime(tStartTime);
				/* 4. Dump the data to memory table. */
				sqliteObject.OpenMemory(szDBPath, szSelectInvoieLineLongQuery, szSelectInvoieLineShortQuery, "InvoiceLine", NULL);
				PrintEndTime(tEndTime);
				PrintDiffTime(tEndTime, tStartTime, tDiffrence);
				cout<< endl;
			}
			break;

		case 5:
			{
				cout << "\t\t You have selected 5 option." << endl;
				cout << "\t\t 5. Read data one by one from invoice table." << endl;
				PrintStartTime(tStartTime);
				char szCustomSQL[4196] = "";
				/* 5. Read data one my one from invoice table. */
				lCountRecords = sqliteObject.CountSQLValue(szSelectInvoieLineCountQuery);
				for(long i = 0; i< lCountRecords; i++){
					/* Open record one by one */
					strcpy(szCustomSQL, szSelectInvoieLineShortQuery);
					sqliteObject.OpenOneRecord("InvoiceLine", szCustomSQL, i+1);
					for(long j = 1; j<150; j++){
						char szColumnData[4096] = "";
						sqliteObject.GetColumnText(j, szColumnData, sizeof(szColumnData));
						//cout << szColumnData << endl;
					}
					//cout << " " << i << ",";
				}
				sqliteObject.CloseOneRecord();
				sqliteObject.Close(TRUE);
				PrintEndTime(tEndTime);
				PrintDiffTime(tEndTime, tStartTime, tDiffrence);
				//cout << endl;
				cout << "\t\t\tAll Rows Got." << endl;
				cout<< endl;
			}
			break;
		case 6:
			cout << "\t\tGoodBye ... \n\n" <<endl;
			cout<< endl;
			break;
		default:
			cout << "\t\t Invalid choice \n\n" << endl;
			cout<< endl;
			break;
		}
	}while(iChoice < 6);

	sqliteObject.Close(FALSE);
	cout << "\t\tIn 20 seconds" << endl;
	Sleep(20000);
	return 0;
}

void PrintStartTime(time_t &tStartTime){
	char szStartTime[256] = "Start Time : ";
	time(&tStartTime);
	struct tm * dt;
	dt = localtime(&tStartTime);
	strftime(szStartTime, sizeof(szStartTime), "%Y-%m-%d %H:%M:%S", dt);
	//sprintf(szStartTime, "Start Time : %I64u", tStartTime);
	std::cout << "\t\t\t" <<"Start Time : "<< szStartTime << endl;
}

void PrintEndTime(time_t &tEndTime){
	char szEndTime[256] = "End Time : ";
	time(&tEndTime);
	struct tm * dt;
	dt = localtime(&tEndTime);
	strftime(szEndTime, sizeof(szEndTime), "%Y-%m-%d %H:%M:%S", dt);
	//sprintf(szEndTime, "End Time : %I64u", tEndTime);
	std::cout << "\t\t\t" << "End Time :" << szEndTime << endl;
}

void PrintDiffTime(time_t &tEndTime, time_t &tStartTime, time_t &tDiffrence){
	char szDiffenceTime[256] = "End Time - Start Time = ";
	tDiffrence = tEndTime - tStartTime;
	sprintf(szDiffenceTime, "End Time - Start Time = %I64u", tDiffrence);
	std::cout << "\t\t\t" << szDiffenceTime << endl;
}

char *GenerateGUID()
{
	GUID guid;
	CoCreateGuid(&guid);

	// Convert the GUID to a string
	BYTE * str;
	UuidToString((UUID*)&guid, &str);
	char strGuid[128] = "";
	strcpy(strGuid, (char*)str);
	RpcStringFree(&str);
	return strGuid;
}