#pragma once
#include "basedialog.h"
#include "SearchInfo.h"
#include "DlgResizer.h"
#include <string>
#include <vector>

using namespace std;

#define SEARCH_FOUND		(WM_APP+1)
#define SEARCH_START		(WM_APP+2)
#define SEARCH_PROGRESS		(WM_APP+3)
#define SEARCH_END			(WM_APP+4)


/**
 * search dialog.
 */
class CSearchDlg : public CDialog
{
public:
	CSearchDlg(HWND hParent);
	~CSearchDlg(void);

	DWORD					SearchThread();
	void					SetSearchPath(const wstring& path) {m_searchpath = path;}

protected:
	LRESULT CALLBACK		DlgFunc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT					DoCommand(int id, int msg);

	int						SearchFile(CSearchInfo& sinfo, bool bUseRegex, bool bCaseSensitive, const wstring& searchString);

	bool					InitResultList();
	bool					AddFoundEntry(CSearchInfo * pInfo, bool bOnlyListControl = false);
	void					ShowContextMenu(int x, int y);
	void					DoListNotify(LPNMITEMACTIVATE lpNMItemActivate);
	void					UpdateInfoLabel();
	void					UpdateSearchButton();
private:
	static bool				NameCompareAsc(const CSearchInfo Entry1, const CSearchInfo Entry2);
	static bool				SizeCompareAsc(const CSearchInfo Entry1, const CSearchInfo Entry2);
	static bool				MatchesCompareAsc(const CSearchInfo Entry1, const CSearchInfo Entry2);
	static bool				PathCompareAsc(const CSearchInfo Entry1, const CSearchInfo Entry2);

	static bool				NameCompareDesc(const CSearchInfo Entry1, const CSearchInfo Entry2);
	static bool				SizeCompareDesc(const CSearchInfo Entry1, const CSearchInfo Entry2);
	static bool				MatchesCompareDesc(const CSearchInfo Entry1, const CSearchInfo Entry2);
	static bool				PathCompareDesc(const CSearchInfo Entry1, const CSearchInfo Entry2);

private:
	HWND					m_hParent;
	volatile LONG			m_dwThreadRunning;
	volatile LONG			m_Cancelled;
	wstring					m_searchpath;
	wstring					m_searchString;
	wstring					m_replaceString;
	vector<wstring>			m_patterns;
	bool					m_bUseRegex;
	bool					m_bAllSize;
	DWORD					m_lSize;
	int						m_sizeCmp;
	bool					m_bIncludeSystem;
	bool					m_bIncludeHidden;
	bool					m_bIncludeSubfolders;
	bool					m_bCreateBackup;
	bool					m_bCaseSensitive;

	HANDLE					m_hSearchThread;

	vector<CSearchInfo>		m_items;
	int						m_totalitems;
	int						m_searchedItems;
	bool					m_bAscending;

	CDlgResizer				m_resizer;
};
