
// AdmissionDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Admission.h"
#include "AdmissionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAdmissionDlg dialog



CAdmissionDlg::CAdmissionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMISSION_DIALOG, pParent)
	, m_strStudentName(_T(""))
	, m_strCollage(_T(""))
	, m_strDepartment(_T(""))
	, m_nRegno(0)
	, m_nGPA(0)
	, m_nYearOfStudy(0)
	, m_strActivities(_T(""))
	, m_strAchievements(_T(""))
	, m_strResult(_T(""))
{
	m_Flag = DBCtrlStatus::Search;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdmissionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strStudentName);
	DDX_Text(pDX, IDC_EDIT_COLLAGE, m_strCollage);
	DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_strDepartment);
	DDX_Text(pDX, IDC_EDIT_REGNO, m_nRegno);
	DDX_Text(pDX, IDC_EDIT_GPA, m_nGPA);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_nYearOfStudy);
	DDX_Text(pDX, IDC_EDIT_ACTIVITY, m_strActivities);
	DDX_Text(pDX, IDC_EDIT_ACHIEVE, m_strAchievements);
	DDX_Text(pDX, IDC_EDIT1, m_strResult);
}

BEGIN_MESSAGE_MAP(CAdmissionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CAdmissionDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAdmissionDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CAdmissionDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CAdmissionDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdmissionDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAdmissionDlg message handlers

BOOL CAdmissionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LoadMySQL();

	// Input sample data

// 	g_BTree.insert(CStudent(_T("aaa1"),_T("ABC1"),_T("IT"),1,6,3,_T("a"),_T("h")));
// 	g_BTree.insert(CStudent(_T("aaa2"),_T("ABC1"),_T("IT"),2,7,3,_T("b"),_T("g")));
// 	g_BTree.insert(CStudent(_T("aaa3"),_T("ABC1"),_T("IT"),3,8,3,_T("c"),_T("f")));
// 	g_BTree.insert(CStudent(_T("aaa4"),_T("ABC1"),_T("IT"),4,9,3,_T("d"),_T("d")));
// 	g_BTree.insert(CStudent(_T("aaa5"),_T("ABC1"),_T("IT"),5,8,3,_T("f"),_T("c")));
// 	g_BTree.insert(CStudent(_T("bbb1"),_T("ABC2"),_T("IT"),1,7,3,_T("g"),_T("b")));
// 	g_BTree.insert(CStudent(_T("bbb2"),_T("ABC2"),_T("IT"),2,6,3,_T("h"),_T("a")));
// 	//////////////////////////////////////////////////////////////////////////
// 	// Input sample data
// 	g_BinaryTree.insert(CStudent(_T("aaa1"),_T("ABC1"),_T("IT"),1,6,3,_T("a"),_T("h")));
// 	g_BinaryTree.insert(CStudent(_T("aaa2"),_T("ABC1"),_T("IT"),2,7,3,_T("b"),_T("g")));
// 	g_BinaryTree.insert(CStudent(_T("aaa3"),_T("ABC1"),_T("IT"),3,8,3,_T("c"),_T("f")));
// 	g_BinaryTree.insert(CStudent(_T("aaa4"),_T("ABC1"),_T("IT"),4,9,3,_T("d"),_T("d")));
// 	g_BinaryTree.insert(CStudent(_T("aaa5"),_T("ABC1"),_T("IT"),5,8,3,_T("f"),_T("c")));
// 	g_BinaryTree.insert(CStudent(_T("bbb1"),_T("ABC2"),_T("IT"),1,7,3,_T("g"),_T("b")));
// 	g_BinaryTree.insert(CStudent(_T("bbb2"),_T("ABC2"),_T("IT"),2,6,3,_T("h"),_T("a")));

	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	ChangeCtrlEnable();
	m_strResult = "";
	g_BinaryTree.inorder_print(&m_strResult);
	g_BinaryTree.postorder_print(&m_strResult);
	g_BinaryTree.preorder_print(&m_strResult);

	this->UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAdmissionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAdmissionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAdmissionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CAdmissionDlg::OnBnClickedButton1()
{
	this->UpdateData(TRUE);
	if(m_strStudentName.IsEmpty())
	{
		::AfxMessageBox(_T("Input Student Name."));
	}
	CStudent student;
	student.SetName(m_strStudentName);
	student.SetCollage(m_strCollage);
	student.SetDepartment(m_strDepartment);
	Examcell examcell;
	examcell.Regno = m_nRegno;
	examcell.GPA = m_nGPA;
	examcell.YearOfStudy = m_nYearOfStudy;
	student.SetExamcell(examcell);
	Extracurricular extra;
	extra.Activities = m_strActivities;
	extra.Achievement = m_strAchievements;
	student.SetExtracurricular(extra);

	int index = 0;

// 	BTreeNode *pNode = g_BTree.search(student, index);
// 	if(pNode)
// 	{
// 		student = pNode->getItem(index);
// 	}

	switch (m_Flag)
	{
	case CAdmissionDlg::Search:
		SearchStudent(student);
		break;
	case CAdmissionDlg::Insert:
		InsertStudent(student);
		SaveMySQL();
		break;
	case CAdmissionDlg::Update:
		DeleteStudent(student);
		InsertStudent(student);
		SaveMySQL();
		break;
	case CAdmissionDlg::Delete:
		DeleteStudent(student);
		SaveMySQL();
		break;
	default:
		break;
	}

	m_strResult = "";
	g_BinaryTree.inorder_print(&m_strResult);
	g_BinaryTree.postorder_print(&m_strResult);
	g_BinaryTree.preorder_print(&m_strResult);

	this->UpdateData(FALSE);

}


void CAdmissionDlg::OnBnClickedRadio1()
{
	m_Flag = DBCtrlStatus::Search;
	ChangeCtrlEnable();
}


void CAdmissionDlg::OnBnClickedRadio2()
{
	m_Flag = DBCtrlStatus::Update;
	ChangeCtrlEnable();
}


void CAdmissionDlg::OnBnClickedRadio3()
{
	m_Flag = DBCtrlStatus::Insert;
	ChangeCtrlEnable();
}


void CAdmissionDlg::OnBnClickedRadio4()
{
	m_Flag = DBCtrlStatus::Delete;
	ChangeCtrlEnable();
}

void CAdmissionDlg::ChangeCtrlEnable()
{
	CWnd *pEditName			= GetDlgItem(IDC_EDIT_NAME);
	CWnd *pEditCollage		= GetDlgItem(IDC_EDIT_COLLAGE);
	CWnd *pEditDepartment	= GetDlgItem(IDC_EDIT_DEPARTMENT);
	CWnd *pEditRegno		= GetDlgItem(IDC_EDIT_REGNO);
	CWnd *pEditGPA			= GetDlgItem(IDC_EDIT_GPA);
	CWnd *pEditYear			= GetDlgItem(IDC_EDIT_YEAR);
	CWnd *pEditActivity		= GetDlgItem(IDC_EDIT_ACTIVITY);
	CWnd *pEditAchieve		= GetDlgItem(IDC_EDIT_ACHIEVE);
	CWnd *pButton			= GetDlgItem(IDC_BUTTON1);

	switch (m_Flag)
	{
	case DBCtrlStatus::Search:
		pButton->SetWindowText(_T("Search"));
		break;
	case DBCtrlStatus::Insert:
		pButton->SetWindowText(_T("Insert"));
		break;
	case DBCtrlStatus::Update:
		pButton->SetWindowText(_T("Update"));
		break;
	case DBCtrlStatus::Delete:
		pButton->SetWindowText(_T("Delete"));
		break;
	}
	switch (m_Flag)
	{
	case DBCtrlStatus::Search:
	case DBCtrlStatus::Delete:
		pEditCollage->EnableWindow(FALSE);
		pEditDepartment->EnableWindow(FALSE);
		pEditRegno->EnableWindow(FALSE);
		pEditGPA->EnableWindow(FALSE);
		pEditYear->EnableWindow(FALSE);
		pEditActivity->EnableWindow(FALSE);
		pEditAchieve->EnableWindow(FALSE);
		break;
	case DBCtrlStatus::Insert:
	case DBCtrlStatus::Update:
		pEditCollage->EnableWindow(TRUE);
		pEditDepartment->EnableWindow(TRUE);
		pEditRegno->EnableWindow(TRUE);
		pEditGPA->EnableWindow(TRUE);
		pEditYear->EnableWindow(TRUE);
		pEditActivity->EnableWindow(TRUE);
		pEditAchieve->EnableWindow(TRUE);
		break;
	}
}

void CAdmissionDlg::DeleteStudent(CStudent student)
{
	BinaryNode *pNode = g_BinaryTree.search(student);
	if(!pNode)
	{
		::AfxMessageBox(_T("There is no student with the name."));
		return;
	}
	g_BinaryTree.remove(student);
}

void CAdmissionDlg::SearchStudent(CStudent student)
{
	BinaryNode *pNode = g_BinaryTree.search(student);
	if(!pNode)
	{
		::AfxMessageBox(_T("There is no student with the name."));
		return;
	}
	student = pNode->value;

	m_strCollage = student.GetCollage();
	m_strDepartment = student.GetDepartment();
	m_nRegno = student.GetExamcell().Regno;
	m_nGPA = student.GetExamcell().GPA;
	m_nYearOfStudy = student.GetExamcell().YearOfStudy;
	m_strActivities = student.GetExtracurricular().Activities;
	m_strAchievements = student.GetExtracurricular().Achievement;

}
void CAdmissionDlg::InsertStudent(CStudent student)
{
	BinaryNode *pNode = g_BinaryTree.search(student);
	if(pNode)
	{
		::AfxMessageBox(_T("There is student with the same name."));
		return;
	}
	g_BinaryTree.insert(student);
}

void CAdmissionDlg::UpdateStudent(CStudent student)
{
	BinaryNode *pNode = g_BinaryTree.search(student);
	if(!pNode)
	{
		::AfxMessageBox(_T("There is no student with the name."));
		return;
	}
	pNode->value = student;

}
// Load data in MySQL database
void CAdmissionDlg::LoadMySQL()
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
//	sql::PreparedStatement *pstmt;

	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "star");
		con->setSchema("admission");
		stmt = con->createStatement();
		res = stmt->executeQuery("select * from student");
		while(res->next())
		{
			CString str =CString(res->getString("name").c_str());
			g_BinaryTree.insert(CStudent(CString(res->getString("name").c_str())
				,CString(res->getString("collage").c_str())
				,CString(res->getString("department").c_str())
				,res->getInt("regno")
				,res->getInt("gpa")
				,res->getInt("year_study")
				,CString(res->getString("activity").c_str())
				,CString(res->getString("achieve").c_str())
				));
		}
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}


void CAdmissionDlg::SaveMySQL(sql::PreparedStatement* prep_stmt, BinaryNode* leaf)
{
	if (leaf == NULL) return;
	CStudent* pStudent = &leaf->value;

	prep_stmt->setString(1, pStudent->GetName().GetBuffer(0));
	prep_stmt->setString(2, pStudent->GetCollage().GetBuffer(0));
	prep_stmt->setString(3, pStudent->GetDepartment().GetBuffer(0));

	Examcell examcell = pStudent->GetExamcell();
	prep_stmt->setInt(4, examcell.Regno);
	prep_stmt->setInt(5, examcell.GPA);
	prep_stmt->setInt(6, examcell.YearOfStudy);

	Extracurricular extra = pStudent->GetExtracurricular();
	prep_stmt->setString(7, extra.Activities.GetBuffer(0));
	prep_stmt->setString(8, extra.Achievement.GetBuffer(0));
	prep_stmt->executeUpdate();
	SaveMySQL(prep_stmt, leaf->left);
	SaveMySQL(prep_stmt, leaf->right);

}
// Save data in MySQL database
void CAdmissionDlg::SaveMySQL()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* prep_stmt;

	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "star");
		con->setSchema("admission");
		stmt = con->createStatement();
		stmt->execute("delete from student");
		prep_stmt = con->prepareStatement("Insert into student(name, collage, department, regno, gpa, year_study, activity, achieve) values(?,?,?,?,?,?,?,?)");

		SaveMySQL(prep_stmt, g_BinaryTree.root);

		delete prep_stmt;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

}
