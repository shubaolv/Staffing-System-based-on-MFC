
// 员工个人信息查询Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "员工个人信息查询.h"
#include "员工个人信息查询Dlg.h"
#include "afxdialogex.h"
#include "stdio.h"
#include <string.h>  
#include <string>
#include <algorithm>  
#include <iostream>  
#include "winsock.h"  
//#include "trans.h"
#include "mysql.h"  
using namespace std;  
#pragma comment (lib, "libmysql.lib")  
#pragma comment (lib, "mysqlclient.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C员工个人信息查询Dlg 对话框



C员工个人信息查询Dlg::C员工个人信息查询Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C员工个人信息查询Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C员工个人信息查询Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C员工个人信息查询Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C员工个人信息查询Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// C员工个人信息查询Dlg 消息处理程序

BOOL C员工个人信息查询Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C员工个人信息查询Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C员工个人信息查询Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C员工个人信息查询Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C员工个人信息查询Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;
	CString id;
	GetDlgItemText(IDC_EDIT1,name);
	GetDlgItemText(IDC_EDIT2,id);
	//int aa=_ttoi(a);
	//aa=aa*aa;
	//b.Format(_T("%d"),aa);
	//SetDlgItemText(IDC_EDIT2,b);
	char *host = "localhost";  
    char *user = "root";//mysql的用户名  
    char *pass = "root";//你的mysql服务器密码  
    char *db = "employee";  
    unsigned int port = 3306; //server port  
    MYSQL *sock;  
    sock=mysql_init(0);  
    if(sock &&mysql_real_connect(sock,host,user,pass,db,0,NULL,0))  
    {  
		mysql_query(sock,"SET NAMES 'gbk'");
        std:string name1,id1,father_id1,father_name1,father_ab1; 
		name1=(char *)_bstr_t(name);
		id1=(char *)_bstr_t(id);
		char name3[100],id3[100];
		const char *name2,*id2;
		name2=name1.c_str();
		id2=id1.c_str();
		strcpy(name3,name2);
		strcpy(id3,id2);
		char sql[300];
		sprintf( sql,"select father_id,father_name,father_ab from users where id='%s'and name='%s';",id3,name3);
		//sprintf(sql,"insert into %s",bbb);
		//b=name.c_str();
		mysql_query(sock,sql);
		MYSQL_RES *res; 
		MYSQL_ROW row;
		res=mysql_store_result( sock) ;//取得查询结果,保存查询到的数据到res 
		int num=0;
		if(row=mysql_fetch_row(res))
		{
			string num1=row[0],num2=row[1],num3=row[2];
			CString father_name;
			CString father_id;
			CString father_ab;
			father_id=num1.c_str();
			father_name=num2.c_str();
			father_ab=num3.c_str();
			SetDlgItemText(IDC_EDIT3,father_name);
			SetDlgItemText(IDC_EDIT4,father_id);
			SetDlgItemText(IDC_EDIT5,father_ab);
		}
		else
		{
			CString retu(_T("输入信息有误！"));
			SetDlgItemText(IDC_EDIT3,retu);
		}
    }  
    else  
    {  
         CString retu(_T("连接数据库错误！"));
		 SetDlgItemText(IDC_EDIT2,retu);
    }   
}
