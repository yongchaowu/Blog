# _com_error


try
{
}
catch (_com_error &e)
{
	CString erromessage;
	erromessage = e.ErrorMessage();
	AfxMessageBox(erromessage); 
	//return S_FALSE;
}
