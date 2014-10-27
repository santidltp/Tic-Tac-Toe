
#define START 0
#define X 111
#define O 112
#define USER 113
#define MACHINE 114

#define ID_SQUARE0  100
#define ID_SQUARE1  101
#define ID_SQUARE2  102
#define ID_SQUARE3  103
#define ID_SQUARE4  104
#define ID_SQUARE5  105
#define ID_SQUARE6  106
#define ID_SQUARE7  107
#define ID_SQUARE8  108

class tttoe: public CWinApp
{
public :
	virtual BOOL InitInstance();

};
class CMainWindow: public CWnd
{
protected:
	static const CRect cSquares[9];
	int iGrid[9];
	int iClicks;
	int iMenuChoice;
	int iX;
	int iScoreX, iScoreO, iScoreDraw;

	CButton buttons[9];
	CMenu Menu;

	void DrawBoard(CDC*pDC);
	//void DrawX(CDC*pDC,int iPos);
	//void DrawO(CDC*pDC, int iPost);
	void Reset();
	int getSquare(CPoint point);
	void isGameOver();
	void Again(wchar_t*  msg);
	void ArtificialIntelligence();
	void DisplayScore();
	void DeleteScore();
	

public:
CMainWindow();
protected:
	virtual void Destroy();
	afx_msg void OnAgainstUser();
	afx_msg void OnAgainstMachine();
	afx_msg void OnExit();
	afx_msg void OnPaint();
	afx_msg void OnButton(UINT nID);
	//afx_msg void OnLButtonDown(UINT iFlags,CPoint point);
	DECLARE_MESSAGE_MAP()
};

