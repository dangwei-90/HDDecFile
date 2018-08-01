
// HDDecFileDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "HDDecFile.h"
#include "HDDecFileDlg.h"
#include "afxdialogex.h"
#include "HDCryption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHDDecFileDlg 对话框



CHDDecFileDlg::CHDDecFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HDDECFILE_DIALOG, pParent)
	, m_csPassword1(_T(""))
	, m_csPassword2(_T(""))
	, m_csPassword3(_T(""))
	, m_csPassword4(_T(""))
	, m_csPassword5(_T(""))
	, m_csPassword6(_T(""))
	, m_csPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHDDecFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PW1, m_csPassword1);
	DDX_Text(pDX, IDC_EDIT_PW2, m_csPassword2);
	DDX_Text(pDX, IDC_EDIT_PW3, m_csPassword3);
	DDX_Text(pDX, IDC_EDIT_PW4, m_csPassword4);
	DDX_Text(pDX, IDC_EDIT_PW5, m_csPassword5);
	DDX_Text(pDX, IDC_EDIT_PW6, m_csPassword6);

	DDX_Control(pDX, IDC_EDIT_PW1, m_ctpw1);
	DDX_Control(pDX, IDC_EDIT_PW2, m_ctpw2);
	DDX_Control(pDX, IDC_EDIT_PW3, m_ctpw3);
	DDX_Control(pDX, IDC_EDIT_PW4, m_ctpw4);
	DDX_Control(pDX, IDC_EDIT_PW5, m_ctpw5);
	DDX_Control(pDX, IDC_EDIT_PW6, m_ctpw6);
	DDX_Control(pDX, IDC_STATIC_OPTION, m_ltextoption);
}

BEGIN_MESSAGE_MAP(CHDDecFileDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CHDDecFileDlg::OnBnClickedButtonDec)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CHDDecFileDlg::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// CHDDecFileDlg 消息处理程序

BOOL CHDDecFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	// 执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 设置字体
	m_HDEditFont.CreatePointFont(280, "宋体");
	m_ctpw1.SetFont(&m_HDEditFont); 
	m_ctpw2.SetFont(&m_HDEditFont); 
	m_ctpw3.SetFont(&m_HDEditFont); 
	m_ctpw4.SetFont(&m_HDEditFont); 
	m_ctpw5.SetFont(&m_HDEditFont); 
	m_ctpw6.SetFont(&m_HDEditFont); 

	m_LTextFont.CreatePointFont(150, "宋体");
	m_ltextoption.SetFont(&m_LTextFont);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHDDecFileDlg::OnPaint()
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
HCURSOR CHDDecFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHDDecFileDlg::EncryptBufer(unsigned char* buffer, int len)
{
	unsigned char mask[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	int i = 0;
	for(i = 0; i < len; i++)
	{
		buffer[i]^=mask[i%16];
	}
}


//解密文件，刻录用
int CHDDecFileDlg::Encrypt(char *filename,  char *tfilename)
{
	FILE *rp=NULL,*wp=NULL;
	unsigned char buffer[4096]={0x00};
	int readlen=0;

	char BackupFileName[260]={0x00};
	char strFileName[260]={0x00};
	memcpy(strFileName,filename,strlen(filename));

	rp=fopen(strFileName,"rb");
	if(!rp)
	{
		goto end;
	}
	wp=fopen(tfilename,"wb");
	if(!wp)
	{
		goto end;
	}
	while(1)
	{
		readlen=fread(buffer,1,4096,rp);
		if(readlen<=0)
			break;
		else
		{
			EncryptBufer(buffer,readlen);
			fwrite(buffer,1,readlen,wp);
		}
	}
end:
	if(rp)
		fclose(rp);
	if(wp)
		fclose(wp);
	//DeleteFileA(BackupFileName);
	return 0;
}



void CHDDecFileDlg::OnBnClickedButtonDec()
{
	// 验证口令
	AddPassword();

	// 获取文件MD5值
	CString csMD5;
	csMD5 = GetFileMD5("C//HD//SecFile//HDBurndate.hd");

	// 解析MD5，获取口令
	CString csGetPw;
	csGetPw = GetPassWord(csMD5.GetBuffer());
	csMD5.ReleaseBuffer();

	// 判断口令是否正确
	BOOL bPass = TRUE;
	bPass = CheckPassWord(csGetPw.GetBuffer(), m_csPassword.GetBuffer());
	
	// 处理
	if (bPass == TRUE)
	{
		// 解密文件到指定路径
		BROWSEINFO browseInfo;
		LPITEMIDLIST pItemID;
 
		memset(&browseInfo, 0, sizeof(BROWSEINFO));
 
		browseInfo.hwndOwner = m_hWnd;
		browseInfo.pidlRoot = NULL;
		browseInfo.lpszTitle = "航盾光盘解密存放路径：";
 
		pItemID = SHBrowseForFolder(&browseInfo);
		if(pItemID)
		{
			TCHAR szPath[2*MAX_PATH] = {0x00};
			if(SHGetPathFromIDList(pItemID, szPath))
			{
				// 获取用户存放路径
				sprintf_s(szPath, 2*MAX_PATH, "%s\\Burndate.rar", szPath);
				DeleteFile(szPath);
				Encrypt("C://HD//SecFiles//HDBurndate.hd", szPath);
				DeleteFile("C://HD//SecFiles//HDBurndate.hd");
				MessageBox("解密成功,请在指定路径解压文件即可！");
			} 
		}
		else
		{
			// 取消
			MessageBox(_T("解密光盘内容操作已取消！"));
		}

		// 解密
	}
	else
	{
		MessageBox(_T("口令校验失败，请重新输入"));
	}

	ClearShowWindow();
}


void CHDDecFileDlg::OnBnClickedButtonQuit()
{
	// QUIT
	CDialogEx::OnCancel();
}


void CHDDecFileDlg::ClearShowWindow()
{
	m_csPassword = "";
	m_csPassword1 = "";
	m_csPassword2 = "";
	m_csPassword3 = "";
	m_csPassword4 = "";
	m_csPassword5 = "";
	m_csPassword6 = "";

	m_ctpw1.SetWindowTextA(m_csPassword1);
	m_ctpw2.SetWindowTextA(m_csPassword2);
	m_ctpw3.SetWindowTextA(m_csPassword3);
	m_ctpw4.SetWindowTextA(m_csPassword4);
	m_ctpw5.SetWindowTextA(m_csPassword5);
	m_ctpw6.SetWindowTextA(m_csPassword6);
}


void CHDDecFileDlg::AddPassword()
{
	//UpdateData(FALSE);
	//UpdateData(TRUE);

	m_ctpw1.GetWindowTextA(m_csPassword1);
	m_ctpw2.GetWindowTextA(m_csPassword2);
	m_ctpw3.GetWindowTextA(m_csPassword3);
	m_ctpw4.GetWindowTextA(m_csPassword4);
	m_ctpw5.GetWindowTextA(m_csPassword5);
	m_ctpw6.GetWindowTextA(m_csPassword6);

	m_csPassword = m_csPassword1 + 
		m_csPassword2 + 
		m_csPassword3 + 
		m_csPassword4 + 
		m_csPassword5 + 
		m_csPassword6;
}


char* CHDDecFileDlg::GetFileMD5(char* szfile)
{
	
	return "1234567890";
}


char* CHDDecFileDlg::GetPassWord(char* szMd5)
{
	return "123ABC";
}


BOOL CHDDecFileDlg::CheckPassWord(char* szPw1, char* szPw2)
{
	if(strcmp(szPw1, szPw2) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

