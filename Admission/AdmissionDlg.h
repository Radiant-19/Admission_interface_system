
// AdmissionDlg.h : header file
//

#pragma once


// CAdmissionDlg dialog
class CAdmissionDlg : public CDialogEx
{
// Construction
public:
	CAdmissionDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMISSION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	void ChangeCtrlEnable();
	void SearchStudent(CStudent student);
	void InsertStudent(CStudent student);
	void DeleteStudent(CStudent student);
	void UpdateStudent(CStudent student);
	void LoadMySQL();
	void SaveMySQL();
	void SaveMySQL(sql::PreparedStatement* prep_stmt, BinaryNode* leaf);
public:

	//	
	enum DBCtrlStatus { Search = 0, Insert, Update, Delete };
	DBCtrlStatus m_Flag;
	CString m_strStudentName;
	CString m_strCollage;
	CString m_strDepartment;
	int m_nRegno;
	int m_nGPA;
	int m_nYearOfStudy;
	CString m_strActivities;
	CString m_strAchievements;
	CString m_strResult;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton1();
};
