#pragma once
#include <bq.h>



struct castle_rights {
	bool wks,bks,wqs,bqs;

	castle_rights(bool wks, bool bks, bool wqs, bool bqs): 
		wks(wks),bks(bks), wqs(wqs), bqs(bqs)
	{}
};