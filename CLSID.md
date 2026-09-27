# CLSID

USES_CONVERSION;

##StringFromCLSID
CString temp;
LPOLESTR lpszOleUuidstr1 = NULL;
StringFromCLSID(clsid,&lpszOleUuidstr1);
LPTSTR lpszUuidstr1 = OLE2T(lpszOleUuidstr1);
temp.Format(_T("%s"),lpszUuidstr1);

##CLSIDFromString
LPTSTR tempL = "{C14D1400-D13A-11D2-93B9-0060B067C684}";
LPOLESTR tempLp = T2OLE(tempL);
CLSIDFromString((LPOLESTR)tempLp, (LPCLSID)&clsid);
