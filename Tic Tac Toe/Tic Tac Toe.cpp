/********************************************************************************************* 
 *	This program is Tic Tac Toe Game, in which you are play against another user			 *
 *  or against the machine. Depending on how you place your piece, either X or O			 *	
 *  you will win or you will loose.															 *
 *  All the precompiled thing from Microsoft Visual Studio 2008 have been removed		     *
 *  for confortability.																		 *	
 *																							 *
 *  Developed by: Santiago De La Torre.														 *
 *  Educational Center: Bunker Hill Community College.										 *
 *  Last Modification: Sat 6 of November 2010.												 *
 *																							 *
 ********************************************************************************************/
#include <afxwin.h>
#include "Tic Tac Toe.h"
#include "resource.h"


tttoe tictactoe;


BOOL tttoe::InitInstance()
{
m_pMainWnd  = new CMainWindow;
m_pMainWnd->ShowWindow(m_nCmdShow);
m_pMainWnd->UpdateWindow();
return true;
}

BEGIN_MESSAGE_MAP(CMainWindow,CWnd)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_COMMAND(ID_PLAY_USER,OnAgainstUser)
ON_COMMAND(ID_PLAY_MACHINE, OnAgainstMachine)
ON_COMMAND(ID_APP_EXIT,OnExit)
ON_COMMAND(ID_SCORE_DISPLAY, DisplayScore)
ON_COMMAND(ID_SCORE_DELETE,DeleteScore)
ON_CONTROL_RANGE(BN_CLICKED,ID_SQUARE0,ID_SQUARE8,OnButton)
END_MESSAGE_MAP()

const CRect CMainWindow::cSquares[9]={
//Top Row   
	CRect ( 16,  16, 112, 112),
    CRect (128,  16, 224, 112),
    CRect (240,  16, 336, 112),
//Middle Row
	CRect ( 16, 128, 112, 224),
    CRect (128, 128, 224, 224),
    CRect (240, 128, 336, 224),
//Bottom Row
	CRect ( 16, 240, 112, 336),
    CRect (128, 240, 224, 336),
    CRect (240, 240, 336, 336)
};


CMainWindow::CMainWindow()
{
	//Filling the iGrid array with 0's		
	for(int index=0; index<9;index++)iGrid[index] = START; 
 	//Initializing some variables to 0.
	iClicks = iMenuChoice = iX = iScoreX = iScoreO = iScoreDraw = START;
	
	CString strWndClass = AfxRegisterWndClass (
        CS_VREDRAW | CS_HREDRAW,
        AfxGetApp ()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        (HBRUSH) (COLOR_3DFACE + 1),					// Background brush
		AfxGetApp ()->LoadIconW ( IDI_ICON1 )	// Class icon
    );
CreateEx(0,strWndClass, _T("Tic Tac Toe"), WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,
		 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		 NULL);
CRect size(0,0,350,370);
CalcWindowRect(&size);

Menu.LoadMenuW(IDR_MAINFRAME);
SetMenu(&Menu);

SetWindowPos(NULL,0,0,size.Width(),size.Height(),
		 SWP_NOZORDER | SWP_NOMOVE| SWP_NOREDRAW);



	//Drawing buttons on the client area.
	for(int index=0; index<9;index++)
			buttons[index].Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, cSquares[index], this, (index+100));
};

void CMainWindow::Destroy()
{
	delete this;
}

void CMainWindow::OnPaint()
{
	CPaintDC cpDeviceContext (this);
	DrawBoard(&cpDeviceContext);
}

//The Next Function Draws the lines
void CMainWindow::DrawBoard(CDC *pDC)
{
	CPen penSquares(PS_SOLID,12,RGB(0,0,0));
	CPen *pOldPen = pDC->SelectObject(&penSquares);

	pDC->MoveTo(120,16);
	pDC->LineTo(120,336);

	pDC->MoveTo(232,16);
	pDC->LineTo(232,336);

	pDC->MoveTo(16,120);
	pDC->LineTo(336,120);

	pDC->MoveTo(15,232);
	pDC->LineTo(336,232);

}
/* The next function is the one that is going to be
 * executed when any of the buttons are clicked. By 
 * passing the id of the button we are going to know 
 * which button has been cliecked.
 */
void CMainWindow::OnButton(UINT nID)
{
	int index = nID - 100;
	/*If non of the menu choices have been chose then
	  don't do anything. You need to choose who would 
	  you like to play with before even start.
	  */
	if(iMenuChoice == START) return;
	
	/*If there's anything in that button already don't do anything.
	  You can't draw in the same button twice.
	*/
	if(iGrid[index] == X || iGrid[index]== O  )
		return;

/* Depending on how many clicks you have done
   you are going to print either X or O.
*/	
if(iClicks == 0)
{
	buttons[index].SetWindowTextW(L"X");
	iGrid[index] = X ;
	(iMenuChoice == MACHINE)?ArtificialIntelligence() : iClicks++;
	
}
	else if(iClicks == 1)
{
	buttons[index].SetWindowTextW(L"O");
	iGrid[index] = O ;
	iClicks =0;
	
	}
	
	isGameOver();


}
/* Next Fucntion checks; if there's a winner, and if the 
   game is over.
*/
void CMainWindow::isGameOver()
{
				
	int iRules[8][3]={
	0,1,2,
	3,4,5,
	6,7,8,
	0,3,6,
	1,4,7,
	2,5,8,
	0,4,8,
	2,4,6

	};
	for (int i = 0;i<8; i++){
		if(iGrid[iRules[i][0]]== X && iGrid[iRules[i][1]] == X && iGrid[iRules[i][2]] == X)
		{
			
				Again(_T("X Wins! Do you want to play again?"));
				iScoreX++;
				return;
		}

		if(iGrid[iRules[i][0]]== O && iGrid[iRules[i][1]] == O && iGrid[iRules[i][2]] == O)
		{
			Again(_T("O Wins! Do you want to play again?"));
			iScoreO++;
			return;
		}
	}
	
	for(int index=0; index<9;index++)
		if(iGrid[index] == START)return; 
	Again(_T("It's a draw! Do you want to play again?"));
	iScoreDraw++;


}
//Let's start all over again.
void CMainWindow::Reset()
{
	for(int index=0; index<9;index++){
		iGrid[index] = START; 
		buttons[index].SetWindowTextW(L"");
	}
	
	iClicks = iX = START;
	

	
}
//Play against another user.
void CMainWindow::OnAgainstUser()
{
	Reset();
	iMenuChoice = USER;
}
//Play against the machine.
void CMainWindow::OnAgainstMachine()
{
	Reset();
	iMenuChoice = MACHINE;
}
//Are you sure you want to quit?
void CMainWindow::OnExit()
{
	int iMsg = MessageBox(L"Are you sure you want to quit?",L"Exit", MB_ICONEXCLAMATION |MB_OKCANCEL);

	if(iMsg == IDOK)AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);

}
//Do you want to play again?
void CMainWindow::Again(wchar_t* msg)
{
	int	iMsg = MessageBox(msg,L"Game Over",MB_ICONINFORMATION |MB_OKCANCEL);
	if(iMsg != IDOK)  iMenuChoice = START;
	Reset();
}
//Score
void CMainWindow::DisplayScore()
{
CString msg;

msg.FormatMessage(_T("Score:\n-X Wins: %1!d!\n-O Wins:  %2!d!\n-Draw: %3!d!"), 
   iScoreX, iScoreO, iScoreDraw);


MessageBox(msg);
}


void CMainWindow::DeleteScore()
{
	iScoreX = iScoreO = iScoreDraw = START;
}

/* The next function is the one that makes the machine to choose a button
   when you are playing again it. I called artificial intelligence because 
   deep inside that's what it is.
*/
void CMainWindow::ArtificialIntelligence()
{
	iX++;	
	CClientDC DeviceContext(this);
	int iRules[8][3]={
	0,1,2,
	3,4,5,
	6,7,8,
	0,3,6,
	1,4,7,
	2,5,8,
	0,4,8,
	2,4,6

	};
	
	/*Is the centered square empty?
	 It is a good strategy to have the one
	 in the middle, you are more prone to win
	*/
	if(iGrid[4]==START){
		iGrid[4] = O;
		buttons[4].SetWindowTextW(L"O");;		
		return;	
	}

	srand((unsigned)time(NULL));
	int rnd = rand()%9;



	

//start ramdomly, and you want to do it in the corners.
while(iX==1){
	if(rnd == 0 || rnd == 2 || rnd == 6 || rnd == 8 && iGrid[rnd] == START){
		
		iGrid[rnd] = O;
		buttons[rnd].SetWindowTextW(L"O");		
		return;	
	}
	else{
		rnd = rand()%9;
	}

}		
		
//atack mode

if(iX>2)
for(int index=0; index<8; index++){
	if(iGrid[iRules[index][0]] == O && iGrid[iRules[index][1]]==O ){

			if(iGrid[iRules[index][2]] != START)continue;
			iGrid[iRules[index][2]] = O;
				buttons[iRules[index][2]].SetWindowTextW(L"O");
				return;
			}
				
			else if (iGrid[iRules[index][0]] == O && iGrid[iRules[index][2]]==O){
			
				if(iGrid[iRules[index][1]] != START)continue;
				iGrid[iRules[index][1]] = O;
				buttons[iRules[index][1]].SetWindowTextW(L"O");
				return;
			
			}
			
			
			else if	(iGrid[iRules[index][1]] == O && iGrid[iRules[index][2]]==O ){

				if(iGrid[iRules[index][0]] != START)continue;
				iGrid[iRules[index][0]] = O;
				buttons[iRules[index][0]].SetWindowTextW(L"O"); 
				return;
		
			}
}




//defense mode
for(int index=0; index<8; index++){
	if(iGrid[iRules[index][0]] == X && iGrid[iRules[index][1]]==X ){

			if(iGrid[iRules[index][2]] != START)continue;
			iGrid[iRules[index][2]] = O;
				buttons[iRules[index][2]].SetWindowTextW(L"O"); 
				return;
			}
				
			else if (iGrid[iRules[index][0]] == X && iGrid[iRules[index][2]]==X){
			
				if(iGrid[iRules[index][1]] != START)continue;
				iGrid[iRules[index][1]] = O;
				buttons[iRules[index][1]].SetWindowTextW(L"O");
				return;
			
			}
			
			
			else if	(iGrid[iRules[index][1]] == X && iGrid[iRules[index][2]]==X ){

				if(iGrid[iRules[index][0]] != START)continue;
				iGrid[iRules[index][0]] = O ;
				buttons[ iRules[index][0]].SetWindowTextW(L"O");
				return;
		
			}
}


for(int index=0; index<9; index++)
{
	if(iGrid[index] == START){
		iGrid[index] = O ;
		buttons[index].SetWindowTextW(L"O");
		return;
		
	}
		
}

}